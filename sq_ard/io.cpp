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

#include "io.h"
#include <Arduino.h>

void io_init(HSQUIRRELVM v)
{
	register_global_func(v, io_pinmode, "pinMode");
	register_global_func(v, io_digitalwrite, "digitalWrite");
	register_global_func(v, io_digitalread, "digitalRead");
	register_global_func(v, io_analogwrite, "analogWrite");
	register_global_func(v, io_analogread, "analogRead");
}

SQInteger io_pinmode(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v); //number of arguments
	if(nargs >= 3)
	{
		if((sq_gettype(v, 2) != OT_INTEGER) || (sq_gettype(v, 3) != OT_INTEGER))
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		int pm, pin;
		sq_getinteger(v, 2, &pin);
		sq_getinteger(v, 3, &pm);

		switch(pm)
		{
			case 0:
			{
				pinMode(pin, INPUT);	
			}
			break;
			case 1:
			{
				pinMode(pin, OUTPUT);
			}
			break;
			case 2:
			{
				pinMode(pin, INPUT_PULLUP);
			}
			break;
			default:
				sq_throwerror(v, "bad parameter");
		}
	}
	return 0;
}

SQInteger io_digitalwrite(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	if(nargs >= 3)
	{
		if((sq_gettype(v, 2) != OT_INTEGER) || (sq_gettype(v, 3) != OT_BOOL))
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		int pin;
		SQBool hl;
		sq_getinteger(v, 2, &pin);
		sq_getbool(v, 3, &hl);
		digitalWrite(pin, hl);
	}
	return 0;
}


SQInteger io_digitalread(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	if(nargs >= 2)
	{
		if(sq_gettype(v, 2) != OT_INTEGER)
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		int pin;
		sq_getinteger(v, 2, &pin);
		sq_pushbool(v,digitalRead(pin));
		return 1;
	}
    return 0;
}

SQInteger io_analogwrite(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	if(nargs >= 3)
	{
		if((sq_gettype(v, 2) != OT_INTEGER) || (sq_gettype(v, 3) != OT_INTEGER))
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		int pin, val;
		sq_getinteger(v, 2, &pin);
		sq_getinteger(v, 3, &val);
		analogWrite(pin, val);
	}
	return 0;
}


SQInteger io_analogread(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	if(nargs >= 2)
	{
		if(sq_gettype(v, 2) != OT_INTEGER)
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		int pin;
		sq_getinteger(v, 2, &pin);
		sq_pushinteger(v,analogRead(pin));
		return 1;
	}
    return 0;
}
