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

#include "libcube.h";

int columnPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int layerPins[] = {16, 17, 18, 19};

// XXX: Remove me
int pattern[NUM_LAYERS][NUM_COLUMNS] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  cube_init(columnPins, layerPins);
  //Serial.println("got here!");
  //cube->display(pattern, 1000);
}

int layer = 0;
void nextPattern() {
  int i, j;
  for(i = 0; i < NUM_LAYERS; i++) {
    int k;
    if (i == layer) {
      k = 1;
    } else {
      k = 0;
    }
    for(j = 0; j < NUM_COLUMNS; j++) {
      pattern[i][j] = k;
    }
  }
  layer = (layer + 1) % NUM_LAYERS;
}

void loop() {
  // cube->display(pattern, 1000);
  nextPattern();
  cube_display(columnPins, layerPins, pattern, 500);
}