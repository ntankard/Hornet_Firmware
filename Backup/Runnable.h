#pragma once
class Runnable
{
public:
	//Runnable();
	virtual bool start()=0;
	virtual void run() = 0;
};

