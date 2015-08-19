#if BUILD_TYPE == FOR_TEST

#include "Test_CircularBuffer.h"
// Macro to define cursor lines 
#define CURSOR(top, bottom) (((top) << 8) | (bottom))

#define ASSERT_ISEQUAL_MESSAGE(x, y) __FILE__+(String)" Line:"+(String)__LINE__ +(String)('\n')+(String)"ASSERT_ISEQUAL Failed: "+(String)x + (String)"!="+(String)y
#define ASSERT_ISEQUAL(x, y) do {if(x!=y){return ASSERT_ISEQUAL_MESSAGE(x,y);} } while(0)  
//#define YYYY return "Yes"

//#define min(X, Y)  ((X) < (Y) ? YYYY : (Y))

#define POW2_UNUSED(x) do { (void)(x);return "Hello"; } while(0)  


void Test_CircularBuffer::setup()
{
	_e = new Error();
	_testBuffer = new CircularBuffer<int, 10>(_e);
}

String Test_CircularBuffer::run()
{
	// check to see that the buffer starts empty
	ASSERT_ISTRUE(_testBuffer->isEmpty());
	ASSERT_ISFALSE(_testBuffer->isFull());
	ASSERT_ISEQUAL(_testBuffer->size(), 0);

	// check to see if the buffer can be filled to capacity
	for (int i = 0; i < 9; i++)
	{
		_testBuffer->add(i);
		ASSERT_ISFALSE(_testBuffer->isEmpty());
		ASSERT_ISFALSE(_testBuffer->isFull());
		ASSERT_ISEQUAL(_testBuffer->size(), i+1);
	}

	// check to see if size stays corect as the buffer movfes around its barier
	delete _testBuffer;
	_testBuffer = new CircularBuffer<int, 10>(_e);
	for (int i = 0; i < 5; i++)
	{
		_testBuffer->add(i);

		ASSERT_ISFALSE(_testBuffer->isEmpty());
		ASSERT_ISFALSE(_testBuffer->isFull());
		ASSERT_ISEQUAL(_testBuffer->size(), i + 1);
	}

	for (int i = 0; i < 100; i++)
	{
		_testBuffer->remove();
		_testBuffer->add(1);

		ASSERT_ISFALSE(_testBuffer->isEmpty());
		ASSERT_ISFALSE(_testBuffer->isFull());
		ASSERT_ISEQUAL(_testBuffer->size(),5);
	}

	return "Pass";
}

void Test_CircularBuffer::cleanUp()
{
	delete _testBuffer;
	delete _e;
}

#endif