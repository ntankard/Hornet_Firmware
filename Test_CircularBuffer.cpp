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

}

String Test_CircularBuffer::run()
{
	ASSERT_ISEQUAL(1,1);

	return "HELLO";
}

void Test_CircularBuffer::cleanUp()
{

}

#endif