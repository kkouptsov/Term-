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
#include <utility>
#include "console.h"

namespace Terminal {

const char* Console::readline()
{
	std::cout << is_raw_mode() << std::endl;
	{
		RawModeGuard guard{*this};
		std::cout << is_raw_mode() << std::endl;
		std::pair<uint16_t, uint16_t> size = get_screen_size();
		std::cout << size.first << " x " << size.second << std::endl;
	}
	std::cout << is_raw_mode() << std::endl;
	return "quit";
}


const char* Console::readstream()
{
	// read input noninteractively, e.g. from a pipe
	// TODO
	return nullptr;
}


}
