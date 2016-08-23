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
#ifndef YAPS_H
#define YAPS_H

#include <SPI.h>

class Yaps{
private:
	// analog values of controller sticks
	int8_t mSticks[4];
	// delay between consecutive bytes in spi transfer
	// PSX controllers are somewhat slow and require a short delay to decode commands
	uint32_t mDelay;
	// buttons state in a bit field
	uint16_t mButtonsState;
	// pin number of active low chip select line
	uint8_t mPinCSN;
	// whether current controller is is in analog mode
	bool mIsAnalog;
	// spi setting used in transactions
	SPISettings mSpiSettings;
public:
	// constructor, chip select pin, spi clock frequency in Hz, and delay between bytes
	Yaps(int pinCSN = 10, uint32_t clockFrequency = 250000, uint32_t delayUs = 50);
	// reads controller state and stores it
	void read();
	// whether controller is working as analog or not
	bool isAnalog(){ return mIsAnalog; }
	// return buttons bit field
	// to check if a button is pressed test it with a flag or multiple flags
	// e.g. bool crossPressed = (yaps.getButtons() & yaps.BUTTON_CROSS) != 0;
	uint16_t getButtons(){ return mButtonsState; }
	
	// helper functions, pass button flags as argument
	bool isDown(uint16_t mask){
		return (mButtonsState & mask) != 0;
	}
	// helper functions, pass button flags as argument
	bool isUp(uint16_t mask){
		return (mButtonsState & mask) == 0;
	}
	// returns analog stick state as signed integer
	// pass a combination of flags as parameter or use integer indicies
	// e.g. int8_t value = yaps.getStick(STICK_LEFT | AXIS_X);
	int8_t getStick(int index){ return mSticks[index]; }
	// returns analog stick state as floating point number in <-1, 1) range
	float getStickFloat(int index){ return mSticks[index] / 128.0f; }
	
	// flags used with getButtons(), isDown(), isUp(), getStick(), getStickFloat()
	enum {
		BUTTON_SELECT = 0x0001,
		BUTTON_STICKRIGHT = 0x0002,
		BUTTON_STICKLEFT = 0x0004,
		BUTTON_START = 0x0008,
		
		BUTTON_UP = 0x0010,
		BUTTON_RIGHT = 0x0020,
		BUTTON_DOWN = 0x0040,
		BUTTON_LEFT = 0x0080,
		
		BUTTON_L2 = 0x0100,
		BUTTON_R2 = 0x0200,
		BUTTON_L1 = 0x0400,
		BUTTON_R1 = 0x0800,
		
		BUTTON_TRIANGLE = 0x1000,
		BUTTON_CIRCLE = 0x2000,
		BUTTON_CROSS = 0x4000,
		BUTTON_SQUARE = 0x8000,
		
		STICK_RIGHT = 0x0,
		STICK_LEFT = 0x2,
		AXIS_X = 0x0,
		AXIS_Y = 0x1,
	};
};

#endif // YAPS_H