/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#include <termios.h>
#include <unistd.h>

#include <iostream>
#include "screen_impl.h"
#include "except.h"
#include "utils.h"

namespace Terminal {

class Screen::ScreenImpl {
private:
	struct termios mode;
	bool raw_flag;
public:
	ScreenImpl();
	~ScreenImpl();
	bool isatty();
	bool is_raw_mode();
	void set_raw_mode(bool);
};


Screen::Screen() : impl{std::make_unique<ScreenImpl>()} {
	// setupterm(NULL, fileno(stdout), &error);
}


bool Screen::isatty() { return impl->isatty(); }
bool Screen::is_raw_mode() { return impl->is_raw_mode(); }
void Screen::set_raw_mode(bool flag) { return impl->set_raw_mode(flag); }


Screen::ScreenImpl::ConsoleImpl() : raw_flag{false} {
}


Screen::ScreenImpl::~ConsoleImpl() {
}


bool Screen::ScreenImpl::isatty() {
	if (::isatty(fileno(stdin)) && ::isatty(fileno(stdout)))
		return true;
	return false;
}


bool Screen::ScreenImpl::is_raw_mode() {
	return raw_flag;
}


void Screen::ScreenImpl::set_raw_mode(bool flag)
{
	if (flag == raw_flag)
		return;
	else if (flag) {
		// switch to raw mode
		if (tcgetattr(fileno(stdin), &mode)) {
			throw ConsoleException(Utils::get_last_error());
		}
		struct termios raw = mode;
		/*
		   see 'man tcsetattr'
		*/
		raw.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		raw.c_oflag &= ~OPOST;
		raw.c_cflag &= ~(CSIZE | PARENB);
		raw.c_cflag |= CS8;
		raw.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
		/*
		   control characters: read() with 0.1 sec timeout, do not block
		*/
		raw.c_cc[VMIN] = 0;
		raw.c_cc[VTIME] = 1;
		if (tcsetattr(fileno(stdin), TCSAFLUSH, &raw)) {
			throw ConsoleException(Utils::get_last_error());
		}
		raw_flag = true;
	}
	else {
		// switch to cooked mode
		if (tcsetattr(fileno(stdin), TCSAFLUSH, &mode)) {
			throw ConsoleException(Utils::get_last_error());
		}
		raw_flag = false;
	}
}

} // namespace Terminal
