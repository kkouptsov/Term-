/*
* This file is part of the Term++ project, <URL>.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE.txt
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/


#include <stdio.h>

#include "term.h"
#include "libload.h"

#ifdef _WIN32
#define LIBNAME "term.dll"
#else
#define LIBNAME "./libterm.so"
#endif


int main(void)
{
	lib_handle_t  handle;
	version_fun_t version;
	initialize_fun_t init;

	handle = load_library(LIBNAME);
	if (handle == NULL)
		return 1;
	version = (version_fun_t) get_library_function(handle, "version");
	if (version != NULL) {
		printf("%s\n", version());
	}
	init = (initialize_fun_t) get_library_function(handle, "initialize");
	if (init != NULL) {
		init();
	}
	close_library(handle);
	return 0;
}
