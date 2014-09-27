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

#include <Arduino.h>
#include "squirrel.h"
#include "sqstdblob.h"
#include "sqstdmath.h"
#include "sqstdstring.h"
#include "sq_ard/time.h"
#include "sq_ard/io.h"
#include "sq_ard/serial.h"
#include "main.h"
#include "vm_utils.h"

#include <SdFat.h>

#include <sys/types.h>
#include <stdlib.h>

const uint8_t chipSelect = 15;
SdFat sd;
ArduinoOutStream cout(Serial);



void printfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	char buf[256]; // resulting string limited to 128 chars
	va_list args;
	va_start (args, s);
	vsnprintf(buf, 256, s, args);
	va_end (args);
	Serial.print(buf);
}

void errorfunc(HSQUIRRELVM v,const SQChar *s,...)
{
    char buf[256]; // resulting string limited to 128 chars
	va_list args;
	va_start (args, s);
	vsnprintf(buf, 256, s, args);
	va_end (args);
	Serial.print(buf);
}


int main()
{
    Serial.begin(115200);

    SQInteger retval=0;
    HSQUIRRELVM v;
    v = sq_open(1024);

	sqstd_register_bloblib(v);
	sqstd_register_mathlib(v);
	sqstd_register_stringlib(v);

	util_init(v);
	time_init(v);
	io_init(v);
	serial_init(v);

    while(!sd.begin(chipSelect, SPI_HALF_SPEED))
    {
        Serial.println("error opening card");
        digitalWrite(13, HIGH);
        delay(300);
        digitalWrite(13, LOW);
        delay(300);
    }

    ifstream file("main");

    if (!file.is_open()) sd.errorHalt("open failed");

    if(!SQ_SUCCEEDED(sq_readclosure(v,file_read,&file))) {

        while(1)
        {
            cout << "read closure failed" << endl;
            delay(1000);
        }
    }
	file.close();

    sq_setprintfunc(v, printfunc,errorfunc); //sets the print function

    sq_pushroottable(v); //push the root table(were the globals of the script will be stored)

	Serial.print("begining");
    while(1)
    {
        sq_call(v,1,SQTrue,SQTrue);
        delay(10);
    }
}


