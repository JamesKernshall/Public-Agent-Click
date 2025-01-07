#include "DeltaTime.h"

static Time* instance;

Time::Time()
{
	instance = this;
	init();
}

Time* Time::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Time();
	}

	return instance;
}

void Time::init()
{

}
