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
TODO!