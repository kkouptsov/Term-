/*
 * This file is part of the Term++ project, https://github.com/kkouptsov/term-plus-plus.
 *
 * Copyright (c) 2018 by Konstantin Kouptsov <konstantin@kouptsov.com>.
 *
 * Licensed under GNU Lesser General Public License 3.0 or later.
 * For the full license information, see LICENSE
 * or go to https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef CONIG_H
#define CONIG_H


typedef void(*terminate_t)(void);
typedef void(*timeout_t)(void);


typedef struct callbacks {
	timeout_t timeout;
	terminate_t terminate;
} callbacks_t;


typedef struct term_config {
	callbacks_t callbacks;
} term_config_t;


#endif /* CONIG_H */
