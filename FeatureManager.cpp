#pragma once

#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	_features[0] = Feature(FEATURE_HEAD); //headPoint
	_nodes[0].setValue(_features[0]);
	_features[L_FEATURES_STORED + 1] = Feature(FEATURE_TAIL); //tailPoint
	_nodes[L_FEATURES_STORED + 1].setValue(_features[L_FEATURES_STORED + 1]);
	_featureList = &_nodes[0];
	_featureList->insertAfter(_nodes[L_FEATURES_STORED + 1]);
	for (int i = 0; i < L_FEATURES_STORED; i++)
	{
		_features[i + 1] = Feature(FEATURE_NULL);
		_nodes[i + 1].setValue(_features[i + 1]);
		_featureList->insertAfter(_nodes[i + 1]);
	}
}

void FeatureManager::addFeature(Pattern* entryPattern, Pattern* exitPattern)
{
	//manageFeatureList();
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureList);
	iter = iter.first();
	for (iter; iter.getNode()->getValue().getState() != FEATURE_NULL; iter++)
	{
		//goes to the next FEATURE_NULL
	}
	iter.getNode()->getValue().setFeature(entryPattern, exitPattern);
}

int FeatureManager::featureListSize()
{
	int count = 0;
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureList);
	iter = iter.first();
	iter++;
	for (iter; iter.getNode()->getValue().getState() != FEATURE_NULL; iter++)
	{
		//goes to the next FEATURE_NULL
		count++;
	}
	return count;
}

void FeatureManager::manageFeatureList()
{
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureList);
	iter++;
	int size = featureListSize();
	for (int i = 0; i < size; i++)
	{
		iter.getNode()->getValue().loseLife();
		iter++;
	}
	iter = iter.first();
	iter++;
	for (int i = 0; i < size; i++)
	{
		if (iter.getNode()->getValue().getLife() <= 0)
		{
			iter.getNode()->getValue().setState(FEATURE_NULL);
			removeFeatures(i);
		}
		iter++;
	}
}

void FeatureManager::removeFeatures(int position)
{
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureList);
	iter++;
	for (position; position > 0; position--)
	{
		iter++;
	}
	FeatureNode* node = iter.getNode();
	iter.getNode()->dropNode();
	iter = iter.last();
	iter.getNode()->insertBefore(*node);
}

FeatureNode* FeatureManager::getFeatureList()
{
	return _featureList;
}

bool FeatureManager::isAnchor()
{

}