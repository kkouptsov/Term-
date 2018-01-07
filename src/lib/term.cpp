/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE.txt
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#include <iostream>
#include "term.h"

EXTERN_C LIBAPI const char* version(void)
{
	return VERSION;
}


EXTERN_C LIBAPI void initialize(void)
{
	std::cout << VERSION << std::endl;
}
