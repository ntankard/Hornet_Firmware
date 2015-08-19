#if BUILD_TYPE == FOR_TEST

#pragma once
#include <Arduino.h>
#include "Error.h"

#define _TEST_ASSERT_ISEQUAL_MESSAGE(x, y) __FILE__+(String)" Line:"+(String)__LINE__ +(String)('\n')+(String)"ASSERT_ISEQUAL Failed: "+(String)x + (String)"!="+(String)y
#define ASSERT_ISEQUAL(x, y) do {if(x!=y){return _TEST_ASSERT_ISEQUAL_MESSAGE(x,y);} } while(0) 

#define _TEST_ASSERT_NOTEQUAL_MESSAGE(x, y) __FILE__+(String)" Line:"+(String)__LINE__ +(String)('\n')+(String)"ASSERT_NOTEQUAL Failed: "+(String)x + (String)"=="+(String)y
#define ASSERT_NOTEQUAL(x, y) do {if(x==y){return _TEST_ASSERT_NOTEQUAL_MESSAGE(x,y);} } while(0) 

#define _TEST_ASSERT_ISTRUE_MESSAGE __FILE__+(String)" Line:"+(String)__LINE__ +(String)('\n')+(String)"ASSERT_ISTRUE Failed: "
#define ASSERT_ISTRUE(x) do {if(!x){return _TEST_ASSERT_ISTRUE_MESSAGE;} } while(0) 

#define _TEST_ASSERT_ISFALSE_MESSAGE __FILE__+(String)" Line:"+(String)__LINE__ +(String)('\n')+(String)"ASSERT_ISFALSE Failed: "
#define ASSERT_ISFALSE(x) do {if(x){return _TEST_ASSERT_ISFALSE_MESSAGE;} } while(0) 

class Test
{
public:
	virtual void setup() = 0;

	virtual String run() = 0;

	virtual void cleanUp() = 0;

protected:
	Error *_e;
};

#endif

