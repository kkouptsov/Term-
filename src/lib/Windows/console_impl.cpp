/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/


#include <iostream>
#include <string>
#include <utility>
#include "console_impl.h"
#include "except.h"
#include "utils.h"

namespace Terminal {

class Console::ConsoleImpl {
private:
	DWORD mode;
	bool raw_flag;
public:
	ConsoleImpl();
	~ConsoleImpl();
	bool isatty();
	bool is_raw_mode();
	void set_raw_mode(bool);
	void get_mode(DWORD &);
private:
};


Console::Console() : impl{std::make_unique<ConsoleImpl>()} {}

Console::~Console() = default;

bool Console::isatty() { return impl->isatty(); }
bool Console::is_raw_mode() { return impl->is_raw_mode(); }
void Console::set_raw_mode(bool flag) { return impl->set_raw_mode(flag); }

Console::ConsoleImpl::ConsoleImpl() : mode {}, raw_flag {false} {
}


Console::ConsoleImpl::~ConsoleImpl() {
}


std::pair<uint16_t, uint16_t> Console::get_screen_size()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	Utils::get_screen_dimensions(info);
	return std::make_pair<uint16_t, uint16_t>(
		uint16_t(info.srWindow.Right - info.srWindow.Left + 1),
		uint16_t(info.srWindow.Bottom - info.srWindow.Top + 1)
		);
}


bool Console::ConsoleImpl::isatty() {
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


bool Console::ConsoleImpl::is_raw_mode() {
	return raw_flag;
}


void Console::ConsoleImpl::get_mode(DWORD &mode)
{
	HANDLE in = Utils::get_handle(STD_INPUT_HANDLE);
	if (!GetConsoleMode(in, &mode)) {
		throw ConsoleException(Utils::get_last_error());
	}
}


void Console::ConsoleImpl::set_raw_mode(bool flag)
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
