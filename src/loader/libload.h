/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE.txt
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#ifndef LIBLOAD_H
#define LIBLOAD_H

typedef void* lib_handle_t;

lib_handle_t load_library(const char *);
void* get_library_function(lib_handle_t, const char *);
void close_library(lib_handle_t);

#endif /* LIBLOAD_H */
