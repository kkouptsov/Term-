/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE.txt
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include <memory>

namespace Terminal {

class Console {
public:
	bool isatty();
private:
	struct ConsoleImpl;
	std::unique_ptr<ConsoleImpl> impl;

	Console();
	~Console();
public:
	static Console & getInstance() {
		static Console instance;
		return instance;
	}

	Console(const Console &) = delete;
	Console& operator=(const Console &) = delete;
};

}

#endif /* CONSOLE_H */
