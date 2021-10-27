#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"
#include "IMU.h"
#include "MetalDetector.h"
#include "LineSensor.h"
#include "PickUp.h"
#include "RobotDecisions.h"
// #define WIFI_DEBUG


#ifdef WIFI_DEBUG
#include "WiFiComms.h"
WiFiComms WiFiComm;
#endif

Robot Bot;
RobotSensors Sensors;
RobotIMU BotIMU;
RobotMetalDetector MetalDetector;
RobotLineSensor LineSensor;
RobotPickUp PickUp;
RobotDecisions Decisions;

void setup() {

  Serial.begin(9600);
  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
  // MetalDetector.SetPins(MD_pin_pulse, MD_pin_cap, MD_pin_LED1, MD_pin_LED2);
  LineSensor.SetPins(line_pin_sense, line_detect_pin);
  PickUp.SetPins(PU_servo_pin);
  BotIMU.Begin();

  LineSensor.SetThresholdValues(253, 480);

  PickUp.Sweep(180);  // initialise collection mechanism

#ifdef WIFI_DEBUG
  WiFiComm.Connect();
#endif

}

void loop() {
  // float line_sense = LineSensor.LineFollowSense();
  // bool line_detect = LineSensor.Detect();

  // Serial.println(String(line_detect) + " " + String(line_sense));

  Decisions.FollowLine(Bot, LineSensor, true);
  //Serial.println(String(analogRead(line_pin_sense)));
  // Decisions.FollowLineWithWiFi(Bot, LineSensor, WiFiComm);

  //float ir_distance = Sensors.A02.GetDistance();
  //float ultrasound_distance = Sensors.Ultrasound.GetDistance();

  // Serial.println("Ultrasound Dist: " + String(ultrasound_distance) + " IR_Sensor: " + String(ir_distance));

  Decisions.BlockCollect(Bot, Sensors, PickUp, BotIMU);

#ifdef WIFI_DEBUG
  if (WiFiComm.wl_status == WL_CONNECTED) {

    // WiFiComm.Message(String(ultrasound_distance));

  }
#endif
}