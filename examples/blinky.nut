pinMode(13, 1);

while(true)
{
	print(millis());
	print("\n");
	digitalWrite(13, true);
	delay(200);
	digitalWrite(13, false);
	delay(200);
}

