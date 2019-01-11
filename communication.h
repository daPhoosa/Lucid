

void start_serial()
{
   Serial.begin(250000);
   int i = 0;
   while( !Serial && i++ < 1000 ) delay(1); // wait up to 1s for serial to connect
}