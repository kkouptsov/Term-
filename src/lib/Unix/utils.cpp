/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/


#include <cerrno>
#include <cstring>
#include "utils.h"

namespace Terminal {
namespace Utils {


std::string format_error_as_string(int err)
{
	if (err == 0)
		return std::string();
	return std::string(std::strerror(err));
}


std::string get_last_error(void)
{
	return format_error_as_string(errno);
}


}
}

