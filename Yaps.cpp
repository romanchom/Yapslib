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
#include "Yaps.h"

Yaps::Yaps(int pinCSN, uint32_t clockFrequency, uint32_t delayUs) : 
	mDelay(delayUs),
	mButtonsState(0),
	mPinCSN(pinCSN),
	mIsAnalog(false),
	mSpiSettings(clockFrequency, LSBFIRST, SPI_MODE3)
{
	// set pin as output and drive it high
	// pin is active low
	pinMode(mPinCSN, OUTPUT);
	digitalWrite(mPinCSN, 1);
}

void Yaps::read(){
	uint8_t response;
	mButtonsState = 0;
	
	SPI.beginTransaction(mSpiSettings);
	digitalWrite(mPinCSN, 0);
	delayMicroseconds(mDelay);

	SPI.transfer(0x01);
	delayMicroseconds(mDelay);
	
	response = SPI.transfer(0x42);
	delayMicroseconds(mDelay);
	mIsAnalog = (response == 0x73);
	
	SPI.transfer(0xFF);
	delayMicroseconds(mDelay);
	
	response = SPI.transfer(0xFF);
	delayMicroseconds(mDelay);
	response = ~response;
	mButtonsState |= static_cast<uint16_t>(response);
	
	response = SPI.transfer(0xFF);
	delayMicroseconds(mDelay);
	response = ~response;
	mButtonsState |= (static_cast<uint16_t>(response) << 8);
	
	if(mIsAnalog){
		for(int i = 0; i < 4; ++i){
			response = SPI.transfer(0xFF);
			delayMicroseconds(mDelay);
			mSticks[i] = reinterpret_cast<int8_t &>(response) + 128;
		}
	}
	
	digitalWrite(mPinCSN, 1);
	SPI.endTransaction();
}