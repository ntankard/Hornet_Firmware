#pragma once

#include "CONFIG.h"
#include "Feature.h"
#include "DoublyLinkedNodeIterator.h"

typedef DoublyLinkedNode<Feature>::Node FeatureNode;

class FeatureManager
{
public:
	FeatureManager();
	void addFeature(Pattern* entryPattern, Pattern* exitPattern);
	void removeFeatures(int listSize);
	int featureListSize();
	void manageFeatureList();
	bool isAnchor();
	FeatureNode* getFeatureList();
private:
	FeatureNode* _featureList;
};