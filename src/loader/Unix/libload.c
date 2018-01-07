/*
* This file is part of the Term++ project, <URL>.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE.txt
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#include <dlfcn.h>
#include <stdlib.h>

#include "libload.h"


lib_handle_t load_library(const char *name)
{
	return (lib_handle_t) dlopen(name, RTLD_LAZY);
}


void* get_library_function(lib_handle_t handle, const char *name)
{
	return dlsym(handle, name);
}


void close_library(lib_handle_t handle)
{
	dlclose(handle);
}
