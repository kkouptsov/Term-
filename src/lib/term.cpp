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
#include <memory>
#include "term.h"
#include "console.h"


EXTERN_C LIBAPI const char* version(void)
{
	return VERSION;
}


EXTERN_C LIBAPI int initialize(void)
{
	try {
		// try learning console capabilities
		Terminal::Console & cons = Terminal::Console::getInstance();
		if (!cons.isatty()) {
			// not interactive
			return 1;
		}

		// TODO
		std::cout << cons.is_raw_mode() << std::endl;
		cons.set_raw_mode(true);
		std::cout << cons.is_raw_mode() << std::endl;
		cons.set_raw_mode(false);
		std::cout << cons.is_raw_mode() << std::endl;
		std::cout << VERSION << std::endl;
		return 0;
	}
	catch (...) {
		// no console or console is not suitable for our purpose
		return 1;
	}
}


EXTERN_C LIBAPI const char* readline(void)
{
	/* TODO */
	return "quit";
}
