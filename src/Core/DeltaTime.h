#pragma once


class Time
{

public:
	Time();

	static Time* GetInstance();

	// DeltaTime Get/Set
	static float DeltaTime()
	{ 
		return Time::GetInstance()->deltatime;
	}
	static void DeltaTime(float& dt)
	{
		Time::GetInstance()->deltatime = dt;
	}

private:
	void init();

	float deltatime;

	
};