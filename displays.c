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

#include "displays.h"
#include "libcube.h"
#include <alloca.h>
#include <stdlib.h>
#include <Arduino.h>

void reset_pattern(int* pattern) {
  int i;
  for (i = 0; i < NUM_LAYERS * NUM_COLUMNS; i++) {
    pattern[i] = 0;
  }
}

/**
 * Cycle through each available layer from top to bottom, one at a time
 */
void layers(int* columnPins, int* layerPins, int duration) {
  int pattern[NUM_LAYERS][NUM_COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  long endTime = millis() + duration;

  int layer = 0;
  while(millis() < endTime) {
    int i, j;
    for(i = 0; i < NUM_LAYERS; i++) {
      int k;
      if (i == layer) {
        k = 1;
      } else {
        k = 0;
      }
      for (j = 0; j < NUM_COLUMNS; j++) {
        pattern[i][j] = k;
      }
    }
    layer = (layer + 1) % NUM_LAYERS;
    cube_display(columnPins, layerPins, pattern, 500);
  }
}

/**
 * Cycle through each column, one at a time.
 */
void columns(int* columnPins, int* layerPins, int duration) {
  long endTime = millis() + duration;
  int pattern[NUM_LAYERS][NUM_COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  int column = 0;
  while(millis() < endTime) {
    int layer, col;
    for (layer = 0; layer < NUM_LAYERS; layer++) {
      for (col = 0; col < NUM_COLUMNS; col++) {
        if (col == column) {
          pattern[layer][col] = 1;
        } else {
          pattern[layer][col] = 0;
        }
      }
    }
    cube_display(columnPins, layerPins, pattern, 250);
    column = (column + 1) % NUM_COLUMNS;
  }
}

/**
 * Turn on each LED, one at a time, and then turn them all back off, one at
 * a time.
 */
void snake(int* columnPins, int* layerPins, int duration) {
  long endTime = millis() + duration;
  int pattern[NUM_LAYERS][NUM_COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  int col = 0;
  int lyr = 0;
  while(millis() < endTime) {
    pattern[lyr][col] = (pattern[lyr][col] + 1) % 2;
    cube_display(columnPins, layerPins, pattern, 90);
    col = (col + 1) % NUM_COLUMNS;
    if (col == 0) {
      lyr = (lyr + 1) % NUM_LAYERS;
    }
  }
}

/**
 * Show a random pattern, resetting quickly enough to look 'sparkly'.
 */
void sparkle(int* columnPins, int* layerPins, int duration) {
  long endTime = millis() + duration;
  int* pattern = alloca(NUM_COLUMNS * NUM_LAYERS * sizeof(int));
  int i;
  while (millis() < endTime) {
    for (i = 0; i < NUM_LAYERS * NUM_COLUMNS; i++) {
      pattern[i] = rand() & 2;
    }
    int duration = (rand() % 10) + 200;
    cube_display(columnPins, layerPins, pattern, duration);
  }
}

/**
 * A "rain" or ("Matrix", if you prefer) pattern, which drips lights down the
 * grid.
 */
void rain(int* columnPins, int* layerPins, int duration) {
  long endTime = millis() + duration;
  int pattern[NUM_LAYERS][NUM_COLUMNS] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  int dispTime = 500;
  int maxDrops = 3;
  int dropCount = 1;

  while(millis() < endTime) {
    cube_display(columnPins, layerPins, pattern, dispTime);

    int i, j;
    // Set the bottom layer to 0; those drops have fallen off. Decrement the
    // counter of active drops.
    for (i = 0; i < NUM_COLUMNS; i++) {
      dropCount = dropCount - pattern[NUM_LAYERS - 1][i];
      pattern[NUM_LAYERS - 1][i] = 0;
    }

    // Advance the other drops downward--those which haven't reached the bottom yet.
    for (i = NUM_LAYERS - 2; i >= 0; i--) {
      for (j = 0; j < NUM_COLUMNS; j++) {
        pattern[i+1][j] = pattern[i][j];
        pattern[i][j] = 0;
      }
    }

    // Start new drops if we have fewer than maxDrops.
    // We perturb this a little bit and only do this some of the time in order to keep the pattern
    // random-looking.
    if (dropCount < maxDrops) {
      for (i = 0; i < maxDrops - dropCount; i++) {
        int shouldDrop = rand() % 2;
        int dropCol = rand() % NUM_COLUMNS;
        if (shouldDrop && !pattern[0][dropCol]) {
          pattern[0][dropCol] = 1;
          dropCount++;
        }
      }
    }
  }
}
