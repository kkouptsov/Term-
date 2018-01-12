/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#include <windows.h>

#include <string>
#include <cassert>
#include "utils.h"

namespace Terminal {
namespace Utils {


std::string format_error_as_string(DWORD msgid)
{
	assert(msgid != 0);
	LPTSTR buffer = NULL;
	DWORD len = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, msgid,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &buffer, 0, NULL);
	std::string res(buffer, len);
	LocalFree(buffer);
	return res;
}


std::string get_last_error()
{
	DWORD msgid = GetLastError();
	if (msgid == 0) {
		return std::string();
	}
	return format_error_as_string(msgid);
}


}
}
