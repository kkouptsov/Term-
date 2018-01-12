/*
* This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
*
* Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
*
* Licensed under GNU Lesser General Public License 3.0 or later.
* For the full license information, see LICENSE
* or go to https://www.gnu.org/licenses/lgpl-3.0.html
*/

#ifndef EXCEPT_H
#define EXCEPT_H

#include <exception>

class NotTTYException : public std::runtime_error {
public:
	NotTTYException() : std::runtime_error("Not a TTY") {}
	NotTTYException(std::string what) : std::runtime_error(what) {}
};


#endif /* EXCEPT_H */
