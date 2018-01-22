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

namespace Terminal {

class Screen {
public:
	bool is_raw_mode();
	void set_raw_mode(bool);
	bool isatty();
	std::pair<uint16_t, uint16_t> get_size();
	Screen();
	~Screen();
private:
	class ScreenImpl;
	std::unique_ptr<ScreenImpl> impl; // platform-specific data
};

}

#endif /* SRC_LIB_SCREEN_H_ */
