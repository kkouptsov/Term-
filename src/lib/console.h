/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include <memory>
#include <utility>

namespace Terminal {


class Console {
public:
	bool isatty();
	bool is_raw_mode();
	const char* readline();
	const char* readstream();
	std::pair<uint16_t, uint16_t> get_screen_size();
private:
	class ConsoleImpl;
	std::unique_ptr<ConsoleImpl> impl; // platform-specific data

	void set_raw_mode(bool);
	Console();
	~Console();
public:
	static Console & getInstance() {
		static Console instance;
		return instance;
	}

	Console(const Console &) = delete;
	Console& operator=(const Console &) = delete;
	class RawModeGuard;
};


class Console::RawModeGuard {
private:
	Terminal::Console & c_;
public:
	RawModeGuard(Terminal::Console & c) : c_{c} {
		c_.set_raw_mode(true);
	}
	~RawModeGuard() {
		try { c_.set_raw_mode(false); } catch (...) {}
	}
	RawModeGuard(const RawModeGuard &) = delete;
	RawModeGuard& operator=(const RawModeGuard &) = delete;
};


}

#endif /* CONSOLE_H */
