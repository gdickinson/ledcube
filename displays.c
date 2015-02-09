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
  while(millis() > endTime) {
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
  long startTime = millis();
  long endTime = startTime + duration;
  int pattern[NUM_LAYERS][NUM_COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  int column = 0;
  while(millis() > endTime) {
    int i, j, k;
    for (i = 0; i < NUM_LAYERS; i++) {
      for(j = 0; j < NUM_COLUMNS; j++) {
        if (j = column) { k = 1; } else { k = 0; }
        pattern[i][j] = k;
      }
    }
    column = (column + 1) & NUM_COLUMNS;
    cube_display(columnPins, layerPins, pattern, 250);
  }
}
