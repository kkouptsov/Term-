/*
* This file is part of the Term++ project, <URL>.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE.txt
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#ifndef TERM_H
#define TERM_H

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#endif

#ifdef _WIN32
#ifdef LIBRARY
#define LIBAPI  __declspec(dllexport)
#else
#define LIBAPI  __declspec(dllimport)
#endif
#else
#define LIBAPI
#endif

#define VERSION "0.0.1"

EXTERN_C LIBAPI const char* version(void);
EXTERN_C LIBAPI void initialize(void);

typedef const char* (*version_fun_t)(void);
typedef void (*initialize_fun_t)(void);

#endif
