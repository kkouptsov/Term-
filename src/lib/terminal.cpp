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
#include "terminal.h"
#include "console.h"
#include "screen.h"

namespace Terminal {

term_config_t config;

static void init_config(term_config_t *cnf)
{
	config = *cnf;
}

} // namespace Terminal


EXTERN_C LIBAPI const char* version(void)
{
	return VERSION;
}


EXTERN_C LIBAPI int initialize(term_config_t *config)
{
	Terminal::init_config(config);
	return 1;
}


EXTERN_C LIBAPI const char* readline(void)
{
	try {
		Terminal::Console & cons = Terminal::Console::getInstance();
		if (cons.isatty()) {
			return cons.readline();
		}
		else {
			return cons.readstream();
		}
	}
	catch (...) {
		return nullptr;
	}
}
