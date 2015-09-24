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
	void cleanList();
	void removeFeatures(int position);
	int featureListSize();
	void manageFeatureList();
	bool isAnchor();
	FeatureNode* getFeatureList();
private:
	FeatureNode* _featureList;
	Feature _features[L_FEATURES_STORED + 2];
	FeatureNode _nodes[L_FEATURES_STORED + 2];
};