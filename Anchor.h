#pragma once

#include "Line.h"

class Anchor
{
public:
	Anchor();
	void setLines(Line start, Line end);
private:
	Line _start;
	Line _end;
};

