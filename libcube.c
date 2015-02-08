// The MIT License (MIT)
// Copyright (c) 2015 Guy Dickinson
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <Arduino.h>
#include "libcube.h"

void cube_init(int *cPins, int *lPins) {
  int colPin, layerPin;
  for(colPin = 0; colPin < NUM_COLUMNS; colPin++) {
    pinMode(cPins[colPin], OUTPUT);
  }
  for(layerPin = 0; layerPin < NUM_LAYERS; layerPin++) {
    pinMode(lPins[layerPin], OUTPUT);
  }
  cube_reset(cPins, lPins);
}

void cube_display(int* cPins, int* lPins, int pattern[NUM_LAYERS][NUM_COLUMNS], int duration) {
  long startTime = millis();
  long endTime = startTime + duration;

  while(millis() < endTime) {
    int layerPin;
    int colPin;
    for (layerPin = 0; layerPin < NUM_LAYERS; layerPin++) {
      digitalWrite(lPins[layerPin], LOW);

      for (colPin = 0; colPin < NUM_COLUMNS; colPin++){
        digitalWrite(cPins[colPin], pattern[layerPin][colPin]);
      }
      delay(1);
      digitalWrite(lPins[layerPin], HIGH);
    }
  }
}

void cube_reset(int* cPins, int* lPins) {
  int i;
  for (i = 0; i < NUM_LAYERS; i++) {
    digitalWrite(lPins[i], LOW);
  }
}