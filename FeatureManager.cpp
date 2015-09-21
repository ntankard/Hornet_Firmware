#pragma once

#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	Feature* headFeature = new Feature(FEATURE_HEAD);
	_featureList = new FeatureNode(*headFeature);
	Feature* tailFeature = new Feature(FEATURE_TAIL);
	FeatureNode* tail = new FeatureNode(*tailFeature);
	_featureList->insertAfter(*tail);
	for (int i = 0; i < L_FEATURES_STORED; i++)
	{
		Feature* feature = new Feature(FEATURE_NULL);
		FeatureNode* node = new FeatureNode(*feature);
		_featureList->insertAfter(*node);
	}
}

void FeatureManager::addFeature(Pattern* entryPattern, Pattern* exitPattern)
{
	manageFeatureList();
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
		}
		iter++;
	}
	removeFeatures(size);
}

void FeatureManager::removeFeatures(int listSize)
{
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureList);
	iter++;
	for (int i = 0; i < listSize; i++)
	{
		if (iter.getNode()->getValue().getState() == FEATURE_NULL)
		{
			DoublyLinkedNodeIterator<Feature> tempIter = iter;
			FeatureNode* node = tempIter.getNode();
			tempIter.getNode()->dropNode();
			iter = tempIter;
			tempIter = tempIter.last();
			tempIter.getNode()->insertBefore(*node);
		}
		iter++;
	}
}