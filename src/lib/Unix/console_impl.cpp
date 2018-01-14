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
#include "console_impl.h"
#include "except.h"
#include "utils.h"

namespace Terminal {

class Console::ConsoleImpl {
private:
	struct termios mode;
	bool raw_flag;
public:
	ConsoleImpl();
	~ConsoleImpl();
	bool isatty();
	bool is_raw_mode();
	void set_raw_mode(bool);
};


Console::Console() : impl{std::make_unique<ConsoleImpl>()} {}
Console::~Console() = default;

bool Console::isatty() { return impl->isatty(); }
bool Console::is_raw_mode() { return impl->is_raw_mode(); }
void Console::set_raw_mode(bool flag) { return impl->set_raw_mode(flag); }


Console::ConsoleImpl::ConsoleImpl() : raw_flag{false} {
}


Console::ConsoleImpl::~ConsoleImpl() {
}


bool Console::ConsoleImpl::isatty() {
	if (::isatty(fileno(stdin)) && ::isatty(fileno(stdout)))
		return true;
	return false;
}


bool Console::ConsoleImpl::is_raw_mode() {
	return raw_flag;
}


void Console::ConsoleImpl::set_raw_mode(bool flag)
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

}

