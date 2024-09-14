#include<SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // RX | TX

struct PacketData 
{
  byte lxAxisValue;
  byte lyAxisValue;
  byte rxAxisValue;
  byte ryAxisValue;
};

int value;

PacketData data;

void setup()
{
  btSerial.begin(38400); 
  Serial.begin(9600);  
}


int mapAndAdjustJoystickDeadBandValues(int value, bool reverse)
{
  //Serial.println(value);
  if (value >= 550)
  {
    value = map(value, 550, 1023, 127, 254);
  }
  else if (value <= 480)
  {
    value = map(value, 480, 0, 127, 0);  
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 254 - value;
  }
  return value;
}

void loop()
{
  data.lxAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(A3), false);
  data.lyAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(A4), false);
  
  data.rxAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(A5), false);
  data.ryAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(A6), false);



  String dataString;
  dataString = dataString 
               + data.lxAxisValue + "," 
               + data.lyAxisValue + ","  
               + data.rxAxisValue + ","  
               + data.ryAxisValue + "\n";
  
  btSerial.print(dataString);
  delay(10);
}
