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
#include "console_impl.h"
#include "except.h"
#include "utils.h"

namespace Terminal {

class Console::ConsoleImpl {
public:
	ConsoleImpl();
	~ConsoleImpl();
	bool isatty();
	void get_mode(DWORD&);
	void set_mode(DWORD&);
	void set_raw_mode(DWORD&);
	void get_geometry(CONSOLE_SCREEN_BUFFER_INFO&);
};


Console::Console() : impl{std::make_unique<ConsoleImpl>()} {}
Console::~Console() = default;
bool Console::isatty() { return impl->isatty(); }


Console::ConsoleImpl::ConsoleImpl() {
}


Console::ConsoleImpl::~ConsoleImpl() {
}


void Console::ConsoleImpl::get_geometry(CONSOLE_SCREEN_BUFFER_INFO &info)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	if ((out == INVALID_HANDLE_VALUE) || (out == NULL) || !GetConsoleScreenBufferInfo(out, &info)) {
		throw NotTTYException(Utils::get_last_error());
	}
}


void Console::ConsoleImpl::get_mode(DWORD &mode)
{
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
	if ((in == INVALID_HANDLE_VALUE) || (in == NULL) || !GetConsoleMode(in, &mode)) {
		throw NotTTYException(Utils::get_last_error());
	}
}


void Console::ConsoleImpl::set_mode(DWORD &mode)
{
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
	if ((in == INVALID_HANDLE_VALUE) || (in == NULL) || !SetConsoleMode(in, mode)) {
		throw NotTTYException(Utils::get_last_error());
	}
}


void Console::ConsoleImpl::set_raw_mode(DWORD &mode)
{
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
	if ((in == INVALID_HANDLE_VALUE) || (in == NULL) || !GetConsoleMode(in, &mode)) {
		throw NotTTYException(Utils::get_last_error());
	}
	DWORD new_mode = (mode
		& ~ENABLE_LINE_INPUT        // ReadConsoleInput reads one character at a time
		& ~ENABLE_ECHO_INPUT        // do not automatically echo characters
		& ~ENABLE_PROCESSED_INPUT)   // no special handling of certain characters
		| ENABLE_WINDOW_INPUT;      // get windows resize events
	if (!SetConsoleMode(in, new_mode)) {
		throw NotTTYException(Utils::get_last_error());
	}
}


bool Console::ConsoleImpl::isatty() {
	try {
		DWORD mode;
		CONSOLE_SCREEN_BUFFER_INFO info;
		get_mode(mode);
		get_geometry(info);
	}
	catch (NotTTYException &ex) {
		return false;
	}
	return true;
}


} // namespace Terminal
