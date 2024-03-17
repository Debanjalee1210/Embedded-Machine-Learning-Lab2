/*
  Arduino LSM9DS1 - Simple Accelerometer

  This example reads the acceleration values from the LSM9DS1
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter. Also, it blinks the LED ON/OFF as many number of times
  as mentioned for each posture.

  • Turn the LED ON and OFF once if the detected posture is supine (blinking once)
  • Turn the LED ON and OFF twice if the detected posture is prone (blinking twice)
  • Turn the LED ON and OFF three times if the detected posture is side (blinking three 
    times)
  • Keep the LED OFF if none of the above postures is detected

  The circuit:
  - Arduino Nano 33 BLE Sense

  created 20 JSeptember 2023
  by Debanjalee Roy and Dheeraj Kumar
*/
//include library for IMU sensors
#include <Arduino_LSM9DS1.h>

//LED Blinking duration
const int ledBlinkDuration = 500;

//Macro defined for Supine position 
#define SUPINE 1
//Macro defined for Prone position 
#define PRONE 2
//Macro defined for Lateral Left side position 
#define LEFT 3
//Macro defined for Lateral Right side position 
#define RIGHT 4
//Macro defined for No position 
#define NO_POSTURE 5



void setup() {
  //set the baudrate for Serial Communication
  Serial.begin(9600);
  //wait in loop if serial not started
  while (!Serial);
  Serial.println("Started");

  //sanity checking for IMU sensors whether it has started
  if (!IMU.begin()) {
    //Debug logs to indicate IMU sensor initialization failed
    Serial.println("Failed to initialize IMU!");
    //wait infinitely if failed to initialise IMU 
    while (1);
  }

  //initialize digital pin-13 >> LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //default LED is turned OFF
  digitalWrite(LED_BUILTIN, LOW);

  //Data collection for accelerometer reading 
  Serial.print("Accelerometer sample rate = ");
  //IMU sensor collecting the accelerometer data
  Serial.print(IMU.accelerationSampleRate());
  //Debug logs
  Serial.println(" Hz");
  //Debug logs
  Serial.println();
  //Debug logs
  Serial.println("Acceleration in g's");
  //Print the data on teraterm to save the logs in excel
  Serial.println("X\tY\tZ");
  // calibration time 
  delay(2000); 
}

//function to detect sleeping posture
int detectPostureLying(){
  //variable to store the sensor values
  float x, y, z;
  //initialise the posture variable
  int posture = 0;
  //check if the acceleration data is available 
  if (IMU.accelerationAvailable()) {
    //read the data for x,y,and z
    IMU.readAcceleration(x, y, z);
    //print the value of x
    Serial.print(x);
    Serial.print('\t');
    //print the value of y
    Serial.print(y);
    Serial.print('\t');
    //print the value of z
    Serial.println(z);
  }
  //checking Supine Posture
  if (z > 0.95) { 
    Serial.print("Supine Posture ");
    return 1;
  }
  //checking Prone Posture
  else if (z < -0.95) {
    Serial.print("Prone Posture");
    return 2;
  }
  //checking Lateral Left
  else if (y < -1) {
    Serial.print("Lateral left ");
    return 4;
  }
  //checking Lateral Right
  else if (y > 0.95) {
    Serial.print("Lateral Right ");
    return 4;
  }
  //checking No Posture
  else if (x > 0.95) {
    Serial.print("No Posture ");
    return 5;
  }
  else {
    return 0;
  }
  //sleep for 1s
  delay(1000);

}

//function to blink LED as per the parameter given for number of times
void blinkLED(int blinkTimes){
  //for loop to blink number of times
  for (int i=0;i<blinkTimes;i++)
  {
    //turn the LED ON
    digitalWrite(LED_BUILTIN, HIGH);
    //set the blink duration to keep it high
    delay(ledBlinkDuration);
    //turn the LED OFF 
    digitalWrite(LED_BUILTIN, LOW);
    //set the blink duration to keep it low
    delay(ledBlinkDuration);
  }
}

void loop() {
  //variable to store the posture detected
  int postureDetected = detectPostureLying();

  //switch case for the posture detected
  switch(postureDetected){
    //When the posture is Supine, blink once
    case SUPINE:
    blinkLED(1);
    break;

    //When the posture is Prone, blink twice
    case PRONE:
    blinkLED(2);
    break;

    //when the posture is laterally left, blink thrice
    case LEFT: 
    blinkLED(3);
    break;

    //when the posture is laterally right, blink thrice
    case RIGHT:
    blinkLED(3);
    break;

    //when no posture, no blinking
    case NO_POSTURE:
    digitalWrite(LED_BUILTIN, LOW);
    break;
  }

  //repeat every second
  delay(2000);
}

