#pragma once

#if BUILD_TYPE == FOR_TEST

#include "PatternManager.h"

test(PatternManager_Setup)
{
	PatternManager _patternManager;
	assertEqual(_patternManager.getEntryPattern()->getState(), NOT_SET);
	assertEqual(_patternManager.getExitPattern()->getState(), NOT_SET);
}

test(PatternManager_Setup_Patterns)
{
	PatternManager _patternManager;
	Point point;
	point.setXY(0, 0);
	_patternManager.addPattern(&point, &point);
	point.setXY(2, 2);
	_patternManager.addPattern(&point, &point);
	assertTrue(_patternManager.isSetup());
	assertEqual(_patternManager.getEntryPattern()->getStartCoordX(), 0);
	assertEqual(_patternManager.getExitPattern()->getStartCoordX(), 2);
}

//FEATURE FINDING

//              |
//		Q4	    |      Q1
//		        |
//   		    |
//   ------------------------
//   		    |
//   		    |
//   	Q3	    |      Q2
//    		    |

//  FEATURE ORIENTATION F1
//
//
//               -
//            -     -
//          -         -
//       -               -
//     -                   -
//
//

test(PatternManager_isFeature_RightAngleCorner_Q1_F1)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(105, 105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, 105);
	endPoint.setXY(110, 100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F1)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(105, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, -95);
	endPoint.setXY(110, -100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F1)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-105, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-105, -95);
	endPoint.setXY(-110, -100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F1)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-105, 105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-105, 105);
	endPoint.setXY(-110, 100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

//  FEATURE ORIENTATION F2
//
//
//     -                    -
//       -               -
//          -         -
//            -     -      
//               -          
//
//

test(PatternManager_isFeature_RightAngleCorner_Q1_F2)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(105, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, 95);
	endPoint.setXY(110, 100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F2)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(105, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, -105);
	endPoint.setXY(110, -100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F2)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-105, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-105, -105);
	endPoint.setXY(-110, -100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F2)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-105, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-105, 95);
	endPoint.setXY(-110, 100);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

//  FEATURE ORIENTATION F3
//
//      -                    
//        -              
//           -        
//             -         
//                -          
//             -
//           -
//        -
//     -

test(PatternManager_isFeature_RightAngleCorner_Q1_F3)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(105, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, 95);
	endPoint.setXY(100, 90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F3)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(105, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, -95);
	endPoint.setXY(100, -90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F3)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-95, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-95, -95);
	endPoint.setXY(-100, -90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F3)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-95, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-95, 95);
	endPoint.setXY(-100, 90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

//  FEATURE ORIENTATION F4
//
//                 -             
//              -           
//           -        
//        -              
//     -                     
//        -     
//           -
//              - 
//                 -

test(PatternManager_isFeature_RightAngleCorner_Q1_F4)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(95, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(95, 95);
	endPoint.setXY(100, 90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F4)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(95, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(95, -95);
	endPoint.setXY(100, -90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F4)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-105, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-105, -95);
	endPoint.setXY(-100, -90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F4)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-105, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-105, 95);
	endPoint.setXY(-100, 90);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

//  FEATURE ORIENTATION F5
//
//   -                           
//   -                      
//   -           
//   -                   
//   -                        
//   -          
//   - - - - - - - -        
//                          

test(PatternManager_isFeature_RightAngleCorner_Q1_F5)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(100, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(100, 95);
	endPoint.setXY(105, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F5)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(100, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(100, -105);
	endPoint.setXY(105, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F5)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-100, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-100, -105);
	endPoint.setXY(-95, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F5)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-100, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-100, 95);
	endPoint.setXY(-95, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

//  FEATURE ORIENTATION F6
//
//                 -             
//                 -        
//                 -
//                 -     
//                 -          
//                 -
//   - - - - - - - -        
//                          

test(PatternManager_isFeature_RightAngleCorner_Q1_F6)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(100, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(100, 95);
	endPoint.setXY(95, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F6)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(100, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(100, -105);
	endPoint.setXY(95, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F6)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-100, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-100, -105);
	endPoint.setXY(-105, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F6)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-100, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-100, 95);
	endPoint.setXY(-105, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

//  FEATURE ORIENTATION F7
//
//   - - - - - - - -                            
//                 -        
//                 -
//                 -     
//                 -          
//                 -
//                 -        
//                          

test(PatternManager_isFeature_RightAngleCorner_Q1_F7)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(105, 100);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, 100);
	endPoint.setXY(105, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F7)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(105, -100);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(105, -100);
	endPoint.setXY(105, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F7)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-95, -100);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-95, -100);
	endPoint.setXY(-95, -105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F7)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-95, 100);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-95, 100);
	endPoint.setXY(-95, 95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

//  FEATURE ORIENTATION F8
//
//   - - - - - - - -                            
//   -                      
//   -              
//   -                   
//   -                        
//   -              
//   -                      
//   -                       

test(PatternManager_isFeature_RightAngleCorner_Q1_F8)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, 100);
	Point endPoint(DATA);
	endPoint.setXY(100, 105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(100, 105);
	endPoint.setXY(105, 105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q2_F8)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(100, -100);
	Point endPoint(DATA);
	endPoint.setXY(100, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(100, -95);
	endPoint.setXY(105, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q3_F8)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, -100);
	Point endPoint(DATA);
	endPoint.setXY(-100, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-100, -95);
	endPoint.setXY(-95, -95);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_RightAngleCorner_Q4_F8)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(-100, 100);
	Point endPoint(DATA);
	endPoint.setXY(-100, 105);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(-100, 105);
	endPoint.setXY(-95, 105);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_OnYBoundRange)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5, 5 + L_PATTERN_RANGE_IN_FEATURE);
	endPoint.setXY(10, 0 + L_PATTERN_RANGE_IN_FEATURE);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_OnXBoundRange)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5 + L_PATTERN_RANGE_IN_FEATURE, 5);
	endPoint.setXY(10 + L_PATTERN_RANGE_IN_FEATURE, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_OnXYBoundRange)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5 + L_PATTERN_RANGE_IN_FEATURE, 5 + L_PATTERN_RANGE_IN_FEATURE);
	endPoint.setXY(10 + L_PATTERN_RANGE_IN_FEATURE, 0 + L_PATTERN_RANGE_IN_FEATURE);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_OutsideYBoundRange)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5, 5 + L_PATTERN_RANGE_IN_FEATURE + 1);
	endPoint.setXY(10, 0 + L_PATTERN_RANGE_IN_FEATURE + 1);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertFalse(_patternManager.isFeature());
}

test(PatternManager_isFeature_OutsideXBoundRange)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5 + L_PATTERN_RANGE_IN_FEATURE + 1, 5);
	endPoint.setXY(10 + L_PATTERN_RANGE_IN_FEATURE + 1, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertFalse(_patternManager.isFeature());
}

test(PatternManager_isFeature_OutsideXYBoundRange)
{
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5 + L_PATTERN_RANGE_IN_FEATURE + 1, 5 + L_PATTERN_RANGE_IN_FEATURE + 1);
	endPoint.setXY(10 + L_PATTERN_RANGE_IN_FEATURE + 1, 0 + L_PATTERN_RANGE_IN_FEATURE + 1);
	_patternManager.addPattern(&startPoint, &endPoint);
	assertFalse(_patternManager.isFeature());
}

//TODO ADD MORE TESTS (IMPERFECT CORNERS ETC ETC)

#endif