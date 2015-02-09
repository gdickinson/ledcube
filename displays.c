#include "displays.h"
#include "libcube.h"
#include <Arduino.h>

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

void columns(int* columnPins, int* layerPins, int duration) {
  long endTime = millis() + duration;
  int pattern[NUM_LAYERS][NUM_COLUMNS] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };


  int column = 0;
  while(millis < endTime) {
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
