/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/
#ifndef SCREEN_H
#define SCREEN_H

#include <memory>

namespace Terminal {

class Screen {
public:
	bool is_raw_mode();
	void set_raw_mode(bool flag);
	bool isatty();
	void resize();
	std::pair<uint16_t, uint16_t> get_size();
	void get_input(std::promise<std::string> &);
	Screen();
	~Screen();
private:
	class ScreenImpl;
	std::unique_ptr<ScreenImpl> impl; // platform-specific code
	class RawModeGuard;
};


class Screen::RawModeGuard {
private:
	Screen & c_;
public:
	RawModeGuard(Screen & c) : c_ {c} {
		c_.set_raw_mode(true);
	}
	~RawModeGuard() {
		try { c_.set_raw_mode(false); }
		catch (...) {}
	}
	RawModeGuard(const RawModeGuard &) = delete;
	RawModeGuard& operator=(const RawModeGuard &) = delete;
};


}

#endif /* SCREEN_H */
