//Devan Al Fauzi
#include <Servo.h>

Servo servo1;  // MyObject
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void setup() {
  servo1.attach(12); // Untuk attach pin
  servo2.attach(11);
  servo3.attach(10);
  servo4.attach(9);
  servo5.attach(8);
}

void loop() {
  servo1.write(0); // Untuk menggerakkan servo
  servo2.write(30);
  servo3.write(60);
  servo4.write(90);
  servo5.write(180);
}
