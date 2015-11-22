#define FOR_HARDWARE 1
#define FOR_MANUAL_TEST 2
#define FOR_TEST 3
#define OTHER 4

#define BUILD_TYPE FOR_HARDWARE

#if BUILD_TYPE == FOR_HARDWARE

#include <Wire.h>
#include <Servo.h>
#include "Config.h"
#include "HornetManager.h"
#include "HardwareSerial.h"

HornetManager hornetManager;



void setup()
{
	

	// turn on one of the pins to act as a reference for a logic converter to the XBee
	pinMode(38, OUTPUT);
	digitalWrite(38, HIGH);

	// setup debug serial (also primary coms if XBee is off)
	Serial.begin(115200);
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available()!=0)
	{
		Serial.read();
	}

	// setup XBee coms
#if COM_MODE == XBEE
	XBEE_SERIAL.begin(115200);
	XBEE_SERIAL.clearWriteError();
	XBEE_SERIAL.flush();
	while (XBEE_SERIAL.available())
	{
		XBEE_SERIAL.read();
	}
#endif

	// setup LIDAR coms
#ifdef USE_LIDAR
	C_LIDAR_SERIAL.begin(115200);	//@TODO this should be in the USB serial
	C_LIDAR_SERIAL.clearWriteError();
	C_LIDAR_SERIAL.flush();
	while (C_LIDAR_SERIAL.available())
	{
		C_LIDAR_SERIAL.read();
	}
#endif

	// setup I2C coms for accelerometer
	delay(500);
	Wire.begin();	

	Serial.println(F("Start Setup"));

	hornetManager.start();

	Serial.println(F("End Setup"));
}

//-----------------------------------------------------------------------------------------------------------------------------

void loop()
{
	hornetManager.run();
}

#endif
#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>

#include "Test_MessageBuffer.h"
#include "Test_SequenceGenerator.h"
#include "Test_CircularBuffer.h"
#include "Test_CircularBuffer_Manager.h"
#include "Test_Error.h"
#include "Test_Scheduler.h" 


#include "Test_Point.h"
#include "Test_Anchor.h"
#include "Test_AnchorManager.h"
#include "Test_DoublyLinkedNodeIterator.h"
#include "Test_Feature.h"
#include "Test_FeatureManager.h"
#include "Test_Pattern.h"
#include "Test_PatternManager.h"
#include "Test_Point.h"
#include "Test_PointManager.h"


void setup()
{
	Serial.begin(115200);
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available() != 0)
	{
		Serial.read();
	}

	delay(4000);
}

void loop()
{
	Test::run();
}

#endif
#if BUILD_TYPE == FOR_MANUAL_TEST

#include <Wire.h>

//#include "MTest_DM_Indicator.h"
#include "MTest_Gyro.h"

void setup()
{
	Serial.begin(9600);	//@TODO this should be in the USB serial
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available())
	{
		Serial.read();
	}
	delay(500);
	Wire.begin();	// no idea why this needs to be here

	//MTest_DM_Indicator_Points();
	//MTest_DM_Indicator_Safe();
	//MTest_DM_Indicator_SafeWithBlink();
	//MTest_DM_Indicator_FullSettings();
	//MTest_DM_Indicator_SolidOn();
	//MTest_DM_Indicator_Blink();
	//MTest_DM_Indicator_Sequence();

	MTest_Gyro_Print();
}

void loop()
{
}

#endif

#if BUILD_TYPE == OTHER

#include "Arduino.h"
#include "PriorityManager.h"
#include "RollingcCorrelation.h"
#include "Point.h"

volatile Error e;
RollingCorrelation<10> _test(&e);

void setup()
{
	Serial.begin(115200);
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available() != 0)
	{
		Serial.read();
	}

	delay(3000); 
	Serial.println("Start");
}

int i = 0;

const float X[] = { 1814.716231,
1814.788598,
1816.005781,
1814.021486,
1809.028142,
1812.047418,
1812.108388,
1817.226497,
1820.776944,
1818.646596,
};

const float Y[] = { -46.03357679,
- 6.43302371,
32.69087291,
73.25502918,
112.1313123,
153.0568725,
192.4590363,
232.1892752,
274.147791,
312.5006395,

};


void loop()
{
	Point toAdd;

	for (int i = 0; i < 3; i++)
	{
		toAdd.setPolar(X[i], Y[i]);
		_test.newPoint(toAdd);
		if (e.isError())
		{
			TP("YES");
		}
	}
	while (true){};
}

#endif





/*

// MainTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "RollingCorrelation.h"
#include "Point.h"
#include "LineDetector.h"
#include "AnchorDetector.h"

using namespace std;

volatile Error e;
RollingCorrelation<10> _test(&e);
LineDetector _line(&e);
AnchorDetector _anch(&e);

const float A[] = { 358.5469,
359.7969,
1.0313,
2.3125,
3.5469,
4.8281,
6.0625,
7.2813,
8.5625,
9.75,
11.0313,
12.2656,
13.5,
14.7969,
16,
17.25,
18.5,
19.7031,
20.9844,
22.2031,
23.4688,
24.6563,
25.9219,
27.1563,
28.4063,
29.6563,
30.8906,
32.125,
33.375,
34.5938,
35.8594,
37.0781,
38.3438,
39.5625,
40.75,
42,
43.25,
44.5313,
45.8125,
47.0781,
48.2969,
49.5625,
50.8125,
52.0938,
53.3594,
54.5781,
55.875,
57.0938,
58.375,
59.625,
60.875,
62.125,
63.375,
64.7813,
66.0469,
67.2813,
68.5,
69.7813,
71.0469,
72.2813,
73.5781,
74.7969,
76.0781,
77.3594,
78.6094,
79.8125,
81.0938,
82.375,
83.5938,
84.8594,
86.1094,
87.3906,
88.6406,
89.9219,
91.1719,
92.4531,
93.6563,
94.9375,
96.1875,
97.3906,
98.6719,
99.8906,
101.1719,
102.4531,
103.6563,
104.8906,
106.1719,
107.4375,
108.6875,
109.9219,
110.9531,
112.2188,
113.4844,
114.7031,
115.9688,
117.2188,
118.4531,
119.7188,
120.9531,
122.2031,
123.4688,
124.8906,
126.1563,
127.3906,
128.6563,
131.1875,
132.4375,
137.3906,
138.6719,
139.9531,
141.1563,
142.3906,
143.7031,
144.9531,
146.2188,
147.4219,
148.6875,
149.9375,
151.1719,
152.4531,
153.6719,
154.9531,
156.2031,
157.4844,
158.75,
160.125,
161.3438,
162.5625,
163.75,
164.9844,
166.2813,
167.5313,
168.7813,
170.0469,
171.3125,
172.5156,
183.7969,
184.9531,
186.2188,
187.4844,
188.7188,
189.9531,
191.1719,
192.4219,
193.6719,
194.9375,
196.125,
197.4219,
198.6719,
199.9063,
201.1563,
202.3906,
203.6094,
204.8594,
206.0781,
207.3281,
208.6406,
209.8906,
211.125,
212.375,
213.5938,
214.8281,
216.0781,
217.3438,
218.6094,
219.875,
221.125,
222.4219,
223.6406,
224.8906,
226.1875,
227.4531,
228.7188,
229.9844,
231.2344,
232.5313,
233.9063,
235.1719,
236.4531,
237.7031,
238.9531,
240.1719,
241.4844,
242.75,
243.9688,
245.2656,
246.5313,
247.8125,
249.0156,
250.2813,
251.5938,
252.8281,
254.0781,
255.3281,
256.625,
257.875,
259.125,
260.375,
261.5781,
262.8906,
264.1563,
265.3438,
266.6094,
267.8906,
269.1563,
270.4219,
271.6719,
272.9219,
274.125,
275.4063,
276.6719,
277.9531,
279.1719,
280.4063,
281.6406,
282.875,
284.0781,
285.3281,
286.625,
287.8125,
289.125,
290.3281,
291.5781,
292.8438,
294.0625,
295.2969,
296.5313,
297.7656,
299.0313,
300.2969,
301.5469,
302.7813,
304.0156,
305.2031,
306.4219,
307.6875,
308.9375,
310.1563,
311.4219,
312.6406,
313.875,
315.125,
316.3438,
317.5781,
318.8438,
320.1094,
321.3594,
322.6406,
323.8906,
325.1406,
326.4219,
327.6563,
329.0156,
330.2656,
331.5469,
332.7969,
334.0781,
335.3125,
336.5938,
337.8594,
339.1094,
340.375,
341.5781,
342.8906,
344.1563,
345.375,
346.6094,
347.8906,
349.1406,
350.4375,
351.6875,
352.9063,
354.1563,
355.375,
356.6406,
357.8906
};

const float M[] = { 1815.3,
1814.8,
1816.3,
1815.5,
1812.5,
1818.5,
1822.3,
1832,
1841.3,
1845.3,
1855.5,
1866,
1882.5,
1892.8,
1905.3,
1917,
1930.5,
1945.5,
1958.8,
1979,
2000.8,
2022,
2040,
2065.3,
2092,
2117,
2136,
2169.5,
2191.8,
2219.8,
2262.3,
2301,
2350.8,
2391,
2435.5,
2405.3,
2351.5,
2297.5,
2247.5,
2204.3,
2171,
2134.3,
2095.5,
2065.8,
2035.5,
2007.5,
1976.5,
1946.3,
1928,
1898.3,
1883.8,
1855,
1840,
1818.8,
1799,
1787,
1769.3,
1759,
1744.3,
1739,
1726,
1721,
1709.5,
1705.5,
1701,
1690.3,
1684.8,
1681,
1679.5,
1678.8,
1672.8,
1672.5,
1672.3,
1673.5,
1679.3,
1682.5,
1688.3,
1689.8,
1701,
1703,
1707.8,
1716.8,
1724,
1736.8,
1741.5,
1755.8,
1766.3,
1778,
1789.8,
1810.3,
2492,
2511.8,
2538.3,
2562,
2596.5,
2621.5,
2658.8,
2695.8,
2725.8,
2754.8,
2803.8,
2113.5,
2123.3,
2131,
2118.3,
2104.3,
2104.3,
2160.5,
2045.5,
2026,
2083.8,
2148.8,
2099,
2110.3,
2110.3,
2134.8,
2179.5,
2162,
2171,
2147.8,
2124.8,
2099.5,
2090,
2066.3,
2042,
1662.5,
1723.8,
1863,
2028.8,
2022.8,
1965,
1956,
1945.8,
1930.5,
1931.3,
1928.5,
1939.8,
1937.3,
1939,
1940.8,
1943.8,
1964.3,
1968.5,
1973,
1996.8,
2003.5,
2015.8,
2034.5,
2042.5,
2063.5,
2081.3,
2095.8,
2111.8,
2128.8,
2161.3,
2186.5,
2197,
2234.3,
2267,
2312.8,
2352,
2387.8,
2421.5,
2391.3,
2357.8,
2284.5,
2224.3,
2173.8,
2133,
2091.8,
2039.3,
1991.8,
1965,
1928.8,
1892.5,
1852.8,
1822.3,
1795.8,
1761,
1788.5,
1796.5,
1776.3,
1758.3,
1745.5,
1725.5,
1709,
1697.5,
1682.3,
1670.8,
1660,
1645.5,
1635.5,
1627.3,
1618.5,
1610.5,
1602.8,
1599.3,
1593.5,
1588.3,
1585.8,
1584,
1582.5,
1582.3,
1581.5,
1582.8,
1584.3,
1584.5,
1586.8,
1589.8,
1591.3,
1602,
1604.5,
1617.8,
1625.3,
1634.3,
1643.5,
1657.3,
1667.8,
1679.5,
1695,
1705.5,
1717.5,
1733.5,
1750.5,
1767.8,
1782.3,
1816.3,
1839.8,
1862.3,
1886.5,
1916.3,
1936.8,
1967.3,
2001.5,
2036.5,
2069.5,
2109,
2156.3,
2188,
2223.3,
2282.5,
2349.8,
2406,
2387.8,
2338,
2297.5,
2259.3,
2219.3,
2190.5,
2163.5,
2145,
2119.3,
2092.5,
2065.3,
2039.5,
2022.3,
2000.8,
1972.8,
1963.3,
1943,
1929.3,
1909.5,
1903.5,
1886,
1868.3,
1864,
1855.3,
1844.5,
1841,
1832,
1828.8,
1820.5,
1819,
1818,
1816.5,
1815.8
};


int _tmain(int argc, _TCHAR* argv[])
{
cout << "Hello Wordl"<<endl;

Point toAdd;

for (int i = 0; i < 270; i++)
{
toAdd.setPolar(A[i], M[i]);
_line.newPoint(toAdd);
_test.newPoint(toAdd);
_anch.newPoint(toAdd);
if (e.isError())
{
TP("YES");
}
//" " <<A[i]
cout << i  << " " << _test.getCorrelation() << endl;
//cout << _test.getC_S() << endl;
//cout << endl;
}







getchar();
getchar();

return 0;
}

*/
