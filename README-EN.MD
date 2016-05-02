# Arduino-cor

This program uses the TCS230 color sensor connected to an Arduino to read RGB color information presented to the sensor
and convert them into HSL (http://en.wikipedia.org/wiki/HSL_color_space).
In this format it can detect the colors trying to maintain independence brightness level
environment. I have used Arduino pro mini but works on any model.

The progrma uses a push button to carry out the white calibration.
The calibration is used to adjust the gain of each color of the sensor. The color calibration
is saved in the internal memory of the arduino so do not lose on the power cycle.
The white calibration is required because changing the ambient light changes
the amount of light reaching the sensor.

The program allows the connection of an RGB LED  that produces up
6 colors that are: red, green, blue, cyan, magenta and yellow, plus white.

The program has an output to connect to the control module of PETE (http://loja.pete.com.br/)
allowing it to function as the color sensor manufactured by them.

The program displays all information on the serial console. and to accommodate the data output speed was adjusted
to 57600 bps.

## Credits

This code was quite inspired by the article published in
http://www.arduinoecia.com.br/2014/02/sensor-de-reconhecimento-de-cor-tcs230.html

## License

 Copyright (c) 2016 - Masaki Kawabata Neto e outros

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
