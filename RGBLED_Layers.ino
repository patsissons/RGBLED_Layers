#include <FastLED.h>
#include <LinkedList.h>

// PWM output pins
#define PIN_R 5
#define PIN_G 6
#define PIN_B 3

#define MAX 255
#define HALF 128
#define QUARTER 64

// LED Brightness (0 - 255)
#define BRIGHTNESS 255

// Active Color
CRGB color;

struct Layer {
  virtual void apply() = 0;
};

struct BreathLayer : Layer {
  uint8_t channelIndex;
  uint8_t frameOffset;
  uint8_t frameCount;
  uint8_t brightness;
  uint8_t frame;

  BreathLayer(uint8_t _channelIndex, uint8_t _frameOffset, uint8_t _frameCount, uint8_t _brightness) {
    channelIndex = _channelIndex;
    frameOffset = _frameOffset;
    frameCount = _frameCount;
    brightness = _brightness;
  }
  
  void apply() {
    if (brightness > 0) {
      uint8_t f = frame + frameOffset;
      
      if (f < frameCount) {
        double r = (MAX + 1) / frameCount;
        uint8_t x = f * r - QUARTER;
        uint8_t val = sin8(x);
        color[channelIndex] |=  scale8(val, brightness);
      }
    }

    frame++;
  }
};

void breath(uint8_t wait, uint8_t min, uint8_t max) {
  int cycles = random(min, max + 1);

  LinkedList<Layer*> layers = LinkedList<Layer*>();
  layers.add(new BreathLayer(0, 0, MAX, MAX));
  layers.add(new BreathLayer(1, HALF, HALF, MAX));
  layers.add(new BreathLayer(2, HALF, MAX, 16));
  
  for (int c = 0; c < cycles; ++c) {
    for (int f = 0; f < MAX; ++f) {
      color = 0;
      
      for (int i = 0; i < layers.size(); ++i) {
        layers.get(i)->apply();
      }
  
      show();
      delay(wait);
    }
  }

  for (int i = 0; i < layers.size(); ++i) {
    delete layers.get(i);
  }

  layers.clear();
}

void show()
{
  analogWrite(PIN_R, scale8(color.r, BRIGHTNESS));
  analogWrite(PIN_G, scale8(color.g, BRIGHTNESS));
  analogWrite(PIN_B, scale8(color.b, BRIGHTNESS));
}

void setup() {
  // setup RGB channel output pins
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
}

void loop() {
  breath(10, 1, 1);
}

