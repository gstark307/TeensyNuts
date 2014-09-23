/*
    Copyright (C) 2014  Samuel Cowen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "time.h"
#include <Arduino.h>

void time_init(HSQUIRRELVM v)
{
	register_global_func(v, time_millis, "millis");
	register_global_func(v, time_micros, "micros");
	register_global_func(v, time_delay, "delay");
	register_global_func(v, time_delayMicroseconds, "delayMicroseconds");
}

SQInteger time_millis(HSQUIRRELVM v)
{
	sq_pushinteger(v,millis()); //push the number of arguments as return value
    return 1; //1 because 1 value is returned
}

SQInteger time_micros(HSQUIRRELVM v)
{
	sq_pushinteger(v,micros());
    return 1;
}

SQInteger time_delay(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v); //number of arguments
	if(nargs >= 2)
	{
		if(sq_gettype(v, 2) == OT_INTEGER)
		{
			int ms;
			sq_getinteger(v, 2, &ms);
			delay(ms);
		}
		else
			sq_throwerror(v, "Invalid parameter for delay()");
	}
	return 0;
}

SQInteger time_delayMicroseconds(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v); //number of arguments
	if(nargs >= 2)
	{
		if(sq_gettype(v, 2) == OT_INTEGER)
		{
			int us;
			sq_getinteger(v, 2, &us);
			delayMicroseconds(us);
		}
		else
			sq_throwerror(v, "Invalid parameter for delayMicroseconds()");
	}
	return 0;
}


