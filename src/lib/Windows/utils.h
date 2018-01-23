/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/


#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <string>

namespace Terminal {
namespace Utils {

std::string get_last_error(void);
std::string format_error_as_string(DWORD);
HANDLE get_handle(DWORD);
void get_screen_dimensions(CONSOLE_SCREEN_BUFFER_INFO &);
bool isatty();
void get_mode(DWORD &);

}
}

#endif /* SRC_LIB_WINDOWS_UTILS_H_ */
