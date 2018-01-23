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
public:
	bool is_raw_mode() { return m_raw_flag; };
	void set_raw_mode(bool);
	std::pair<uint16_t, uint16_t> get_size();
	void resize();
	ScreenImpl() : m_mode {}, m_raw_flag {false} {}
	~ScreenImpl() = default;
private:
	DWORD m_mode;
	CONSOLE_SCREEN_BUFFER_INFO m_info;
	bool m_raw_flag;
private:
};


Screen::Screen() : impl {std::make_unique<Screen::ScreenImpl>()} {}
Screen::~Screen() = default;

bool Screen::is_raw_mode() { return impl->is_raw_mode(); }
void Screen::set_raw_mode(bool flag) { return impl->set_raw_mode(flag); }
bool Screen::isatty() { return Utils::isatty(); }
void Screen::resize() { return impl->resize(); }
std::pair<uint16_t, uint16_t> Screen::get_size() { return impl->get_size(); }


std::pair<uint16_t, uint16_t> Screen::ScreenImpl::get_size()
{
	Utils::get_screen_dimensions(m_info);
	return std::make_pair<uint16_t, uint16_t>(
		uint16_t(m_info.srWindow.Right - m_info.srWindow.Left + 1),
		uint16_t(m_info.srWindow.Bottom - m_info.srWindow.Top + 1)
		);
}


void Screen::ScreenImpl::resize()
{
	Utils::get_screen_dimensions(m_info);
}


void Screen::ScreenImpl::set_raw_mode(bool flag)
{
	if (flag == m_raw_flag)
		return;
	else if (flag) {
		// switch to raw mode
		HANDLE in = Utils::get_handle(STD_INPUT_HANDLE);
		if (!GetConsoleMode(in, &m_mode)) {
			throw ConsoleException(Utils::get_last_error());
		}
		DWORD raw = (m_mode
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
		if (!SetConsoleMode(in, m_mode)) {
			throw ConsoleException(Utils::get_last_error());
		}
	}
	m_raw_flag = flag;
}

} // namespace Terminal
