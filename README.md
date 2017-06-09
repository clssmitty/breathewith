# BreatheWith - Arduino code library for respiration detection
A library for respiration detection using the JunoVR respiration sensor. 

## Connection
The breathing sensor is built on top of an Arduino Genuino Micro which will output to a COM port on your computer.

When the device is plugged in, the Arduino will show in your device manager as such (Windows):
 ![Alt](https://cldup.com/b-T50vlH4m.thumb.png)

Additionally you can connect to the Arduino using the Arduino Development Environment found here: [https://www.arduino.cc/en/guide/environment](https://www.arduino.cc/en/guide/environment)

The code for detecting the breath is found in the `detectBreath.ino` file.

You'll find that the output just prints a line with the most recent data to the serial output on the COM port making it easy to ready into other applications (Unreal/Unity).

To make easy serial / Arduino reads in development environments the following plugins are helpful:
- [Unreal ArduinoKit](https://forums.unrealengine.com/showthread.php?118851-FREE-ArduinoKit-Cross-Platform-Arduino-Plugin-for-UE4)
- [Unity Uduino](https://forum.unity3d.com/threads/released-uduino-the-easiest-arduino-unity-communication.443788/)
