/*
MIT License

Copyright (c) 2016 Roman Chomik romanchom@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "SPI.h"
#include "Yaps.h"

enum {
	pinCSN = 10,
	pinMOSI = 11,
	pinMISO = 12,
	pinSCK = 14,
};

Yaps pad(pinCSN);

void setup() {
	SPI.setSCK(pinSCK);
	SPI.setMOSI(pinMOSI);
	SPI.setMISO(pinMISO);
	SPI.begin();
}

void loop() {
	
	pad.read();
	
	if(pad.isAnalog()){
		Serial.print(pad.getStickFloat(Yaps::STICK_LEFT | Yaps::AXIS_X));
		Serial.print("\t");
		
		Serial.print(pad.getStickFloat(Yaps::STICK_LEFT | Yaps::AXIS_Y));
		Serial.print("\t");
		
		Serial.print(pad.getStickFloat(Yaps::STICK_RIGHT | Yaps::AXIS_X));
		Serial.print("\t");
		
		Serial.print(pad.getStickFloat(Yaps::STICK_RIGHT | Yaps::AXIS_Y));
		Serial.print("\t");
	}else{
		Serial.print("Not an analog pad");
	}
	
	Serial.println();
	
	
	delay(100);
}
