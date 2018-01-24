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
#include <future>
#include <thread>
#include <chrono>

#include "console.h"
#include "utils.h"

namespace Terminal {

static char *buffer = nullptr;

const char* Console::readline()
{
	std::promise<std::string> p;
	std::future<std::string> f = p.get_future();
	
	/*
	    Run a separate thread, which will collect input events
	    until the input string is ready. This is done so that
	    user interaction is not blocked by calls cb.timeout() below.
	 */
	std::thread th(&Screen::get_input, &scr, std::ref(p));

	/*
	    While waiting for user input, call back into the application.
	 */
	std::future_status status;
	callbacks_t cb = Terminal::config.callbacks;
	auto timeout = std::chrono::milliseconds(100);
	while((status = f.wait_for(timeout)) != std::future_status::ready) {
		if (cb.timeout != NULL) {
			cb.timeout();
		}
	}

	/*
	    Input is ready. Copy it to the static buffer
	    to be accessed by the application.
	 */
	std::string str = f.get();
	Utils::copy_string_to_buffer(str, &buffer);

	th.join();
	return buffer;
}


const char* Console::readstream()
{
	// read input noninteractively from a redirected stdin
	// TODO
	return nullptr;
}


}
