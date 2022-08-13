#pragma once
class Pin
{
public:
	Pin(void*);
	~Pin();
	bool isSource;
	bool PinState;
	Pin* pinFrom;
	Pin* pinTo;
	void* parent;
	int processPin();
	static int connectPin(Pin* pin1,Pin* pin2);
	bool isBound();
};

