#pragma once

#include "HornetManager.h"
#include "Error.h"
#include "DoublyLinkedNodeIterator.h"
#include "Point.h"
#include "Pattern.h"

typedef DoublyLinkedNode<Point>::Node PointNode;
typedef DoublyLinkedNode<Pattern>::Node PatternNode;

class LidarNavigation
{
public:
	LidarNavigation(HornetManager *theHornetManager, Error *theError);

	LidarNavigation();//used for testing

	void initPointList();

	void initPatternList();

	void setupPoints(float angle, float distance);

	void processLidarData(float angle, float distance);

	void newLidarPoint(float angle, float distance);

	void EOSweep(float pitch, float roll, float yaw);

	PointNode* getHead();

	PatternNode* getPatternList();

	Pattern* getPattern(int index);

	void removePoint(); //removes a point from the start of the linkednodes, ONLY gets called when list is full

	int getSize(); //gets the size of the doublylinkednodes *excludes head and tail

	bool isPattern();

	void createPattern();

	bool isFeature(Pattern* startPattern, Pattern* endPattern);

	void createFeature();

	bool isAnchor();

	void createAnchor();

private:
	bool _setup = false;
	HornetManager *_hornetManager;
	Error *_e;
	PointNode* head;
	PatternNode* patternList;
};


