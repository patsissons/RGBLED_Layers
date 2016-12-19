# Analog RGB LED Layers

This sketch is designed to simplify applying lighting effects as layers so that multiple lighting effects can be overlayed upon one another in order to stack effects when outputing to a RGB LED strip.

## Getting Started

1. Install the [Arduino Software](https://www.arduino.cc/en/Main/Software) ([`choco install arduino`](https://chocolatey.org/packages/arduino))
1. Install the [FastLED Library](https://github.com/FastLED/FastLED/releases/latest)
1. Open the `RGBLED_Layers.ino` sketch
1. Initialize some effect layers
1. Update the `PIN_RED`, `PIN_GREEN`, `PIN_BLUE`, and `BRIGHTNESS` defines (if needed)
1. Compile and Upload the sketch

### Installing Arduino Libraries

1. Open the Arduino IDE
1. `Sketch` Menu `->` `Include Library` `->` `Add .ZIP Library...`
1. Locate downloaded zip file

## Layers

Currently only `BreathLayer` is built-in. However, layers are very simple to construct, simply extend `Layer` and override `apply()`.
