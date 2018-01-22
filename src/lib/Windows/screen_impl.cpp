/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#include <windows.h>

#include <iostream>
#include <string>
#include <utility>
#include <memory>

#include "screen.h"
#include "except.h"
#include "utils.h"


namespace Terminal {

class Screen::ScreenImpl {
private:
	DWORD mode;
	bool raw_flag;
public:
	ScreenImpl() : mode {}, raw_flag {false} {}
	~ScreenImpl() = default;
	bool isatty();
	bool is_raw_mode();
	void set_raw_mode(bool);
	void get_mode(DWORD &);
private:
};


Screen::Screen() : impl{std::make_unique<Screen::ScreenImpl>()} {}
Screen::~Screen() = default;

bool Screen::isatty() { return impl->isatty(); }
bool Screen::is_raw_mode() { return impl->is_raw_mode(); }
void Screen::set_raw_mode(bool flag) { return impl->set_raw_mode(flag); }


std::pair<uint16_t, uint16_t> Screen::get_size()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	Utils::get_screen_dimensions(info);
	return std::make_pair<uint16_t, uint16_t>(
		uint16_t(info.srWindow.Right - info.srWindow.Left + 1),
		uint16_t(info.srWindow.Bottom - info.srWindow.Top + 1)
		);
}


bool Screen::ScreenImpl::isatty() {
	try {
		DWORD mode;
		CONSOLE_SCREEN_BUFFER_INFO info;
		get_mode(mode);
		Utils::get_screen_dimensions(info);
	}
	catch (ConsoleException &) {
		return false;
	}
	return true;
}


bool Screen::ScreenImpl::is_raw_mode() {
	return raw_flag;
}


void Screen::ScreenImpl::get_mode(DWORD &mode)
{
	HANDLE in = Utils::get_handle(STD_INPUT_HANDLE);
	if (!GetConsoleMode(in, &mode)) {
		throw ConsoleException(Utils::get_last_error());
	}
}


void Screen::ScreenImpl::set_raw_mode(bool flag)
{
	if (flag == raw_flag)
		return;
	else if (flag) {
		// switch to raw mode
		HANDLE in = Utils::get_handle(STD_INPUT_HANDLE);
		if (!GetConsoleMode(in, &mode)) {
			throw ConsoleException(Utils::get_last_error());
		}
		DWORD raw = (mode
			& ~ENABLE_LINE_INPUT        // ReadConsoleInput reads one character at a time
			& ~ENABLE_ECHO_INPUT        // do not automatically echo characters
			& ~ENABLE_PROCESSED_INPUT)  // no special handling of certain characters
			| ENABLE_WINDOW_INPUT;      // get windows resize events
		if (!SetConsoleMode(in, raw)) {
			throw ConsoleException(Utils::get_last_error());
		}
	}
	else {
		// switch to cooked mode
		HANDLE in = Utils::get_handle(STD_INPUT_HANDLE);
		if (!SetConsoleMode(in, mode)) {
			throw ConsoleException(Utils::get_last_error());
		}
	}
	raw_flag = flag;
}

} // namespace Terminal
