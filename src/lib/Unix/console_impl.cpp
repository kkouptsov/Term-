/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE.txt
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#include <unistd.h>

#include <iostream>
#include "console_impl.h"

namespace Terminal {

struct Console::ConsoleImpl {
	bool isatty();
	ConsoleImpl();
	~ConsoleImpl();
};

Console::Console() : impl{std::make_unique<ConsoleImpl>()} {}

Console::~Console() = default;

bool Console::isatty() { return impl->isatty(); }

Console::ConsoleImpl::ConsoleImpl() {
	// TODO
}

Console::ConsoleImpl::~ConsoleImpl() {
	// TODO
}

bool Console::ConsoleImpl::isatty() {
	// TODO
	return true;
}

}
