#include "pch.h"
#include "Pin.h"
#include "Components.h"


Pin::Pin(void* parent)
{
	pinFrom = nullptr;
	pinTo = nullptr;
	this->parent = parent;
	PinState = false;
	pinX = 0;
	pinY = 0;
	isSource = false;
}


Pin::~Pin()
{
}


int Pin::processPin()
{
	if (parent != nullptr)
		((Components*)parent)->processPin(this);
	return 0;
}

int Pin::connectPin(Pin* pin1, Pin* pin2)
{
	Pin* pinFrom;
	Pin* pinTo;

	if (!(pin1->isSource ^ pin2->isSource)) // false if same
		return 1; // pin connect error

	if (pin1->isSource) {
		pinFrom = pin1;
		pinTo = pin2;
	}else {
		pinFrom = pin2;
		pinTo = pin1;
	}

	pinTo->pinFrom = pinFrom;
	pinFrom->pinTo = pinTo;

	return 0;
}


bool Pin::isBound()
{
	return (pinFrom != nullptr || pinTo != nullptr);
}


int Pin::deletePin()
{
	if (pinTo != nullptr) {
		pinTo->pinFrom = nullptr;
	}
	if (pinFrom != nullptr) {
		pinFrom->pinTo = nullptr;
	}
	return 0;
}
