/*
This is a simple serial relay script.
All it does is read from the serial port and write everything straight back.
*/

try
{
	while(Serial.available())
	{	
		Serial.write(Serial.read());
	}

}
catch(error)
{
	while(true)
	{
		print(error);
		delay(1000);
	}
}

