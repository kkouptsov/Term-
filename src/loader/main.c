/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/


#include <stdio.h>
#include <string.h>

#include "terminal.h"
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
	readline_fun_t readline;

	handle = load_library(LIBNAME);
	if (handle == NULL)
		return 1;
	if ((version = (version_fun_t) get_library_function(handle, "version")) != NULL) {
		printf("%s\n", version());
	}
	if ((init = (initialize_fun_t) get_library_function(handle, "initialize")) != NULL) {
		init();
	}
	if ((readline = (readline_fun_t) get_library_function(handle, "readline")) != NULL) {
		const char *input = readline();
		while (strncmp(input, "quit", strlen("quit")) != 0) {
			printf("%s\n", input);
			input = readline();
		} 
	}
	close_library(handle);
	return 0;
}
