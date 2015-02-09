# About

![An LED Cube.](https://farm8.staticflickr.com/7414/16479314782_37389e6752.jpg)

There are more than a small handful of hardware examples of how to make a 4x4x4
LED display cube, but for the most part, the software is a hacked-up afterthought.
Perhaps it's because that when the implementer finally gets everything soldered
together and ready to go, they're so excited that it works at all that cleaning
up the code is just too tedious to bother with.

Instead, here's a reasonably simple and extensible model for creating
and displaying LED displays on a 4x4x4 LED display cube.

# Hardware Requirements
* A 4x4x4 LED cube with common-cathod x-axis layers and common-anode columns.
  You can find several construction examples around the Internet:
- [http://www.instructables.com/id/The-4x4x4-LED-cube-Arduino/]
- [http://www.instructables.com/id/LED-Cube-4x4x4/]
* An Arduino or compatible microcontroller with at least 20 pins. For my own
  version of this, I used a Teensy, which is substantially cheaper and has the
  advantage that you can solder the LED hookup lines directly to its board,
  rather than breaking out the headers on an Arduino board.
* The correct USB cable to program your Arduino compatible controller with.

# Usage
The code as-is will compile and run on anything with an Arduino toolchain, including
any model of Teensy (which is what I tested this on). There are a handful of
examples in `displays.c`.

If you'd like to write your own, the basic building blocks are in `libcube.c`.
The idea is that you can draw an arbitrary three dimensional image based on a
two-dimensional array. Supposing a 4x4x4 cube:

    int columnPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int layerPins[] = {16, 17, 18, 19};
    int pattern[4][16] = {
      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Display this pattern for ten seconds
    cube_display(columnPins, layerPins, pattern, 1000)
