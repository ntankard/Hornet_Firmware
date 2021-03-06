#pragma once

#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	_features[0].setState(FEATURE_HEAD); //headPoint
	_nodes[0].setValue(_features[0]);
	_features[L_FEATURES_STORED + 1].setState(FEATURE_TAIL); //tailPoint
	_nodes[L_FEATURES_STORED + 1].setValue(_features[L_FEATURES_STORED + 1]);
	_featureList = &_nodes[0];
	_featureList->insertAfter(_nodes[L_FEATURES_STORED + 1]);
	for (int i = 0; i < L_FEATURES_STORED; i++)
	{
		_features[i + 1].setState(FEATURE_NULL);
		_nodes[i + 1].setValue(_features[i + 1]);
		_featureList->insertAfter(_nodes[i + 1]);
	}
}

void FeatureManager::addFeature(Pattern* entryPattern, Pattern* exitPattern)
{
	DoublyLinkedNodeIterator<Feature> iter(*_featureList);
	iter = iter.first();
	for (iter; iter.getNode()->getValue().getState() != FEATURE_NULL; iter++)
	{
		//goes to the next FEATURE_NULL
	}
	iter.getNode()->getValue().setFeature(entryPattern, exitPattern);
}

bool FeatureManager::featureExists(Pattern* entryPattern, Pattern* exitPattern)
{
	DoublyLinkedNodeIterator<Feature> iter(*_featureList);
	iter++;
	for (int i = featureListSize(); i > 0; i--)
	{
		if (abs(iter.getNode()->getValue().getEnterEndX() - entryPattern->getEndCoordX()) <= L_FEATURE_RANGE_TOLERANCE)
		{
			if (abs(iter.getNode()->getValue().getEnterEndY() - entryPattern->getEndCoordY()) <= L_FEATURE_RANGE_TOLERANCE)
			{
				if (abs(iter.getNode()->getValue().getExitStartX() - exitPattern->getStartCoordX()) <= L_FEATURE_RANGE_TOLERANCE)
				{
					if (abs(iter.getNode()->getValue().getExitStartY() - exitPattern->getStartCoordY()) <= L_FEATURE_RANGE_TOLERANCE)
					{
						//TODO CHECK THE ANGLES OF THE PATTERNS TO SEE IF THEY CLOSELY RESEMBLE A PREVIOUSLY KNOWN PATTERN

						iter.getNode()->getValue().updateOccurances();
						return true;
					}
				}
			}
		}
		iter++;
	}
	return false;
}

int FeatureManager::featureListSize()
{
	int count = 0;
	DoublyLinkedNodeIterator<Feature> iter(*_featureList);
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
	DoublyLinkedNodeIterator<Feature> iter(*_featureList);
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
			iter--;
			removeFeatures(i);
			iter++;
			size--;
		}
		else
		{
			iter++;
		}
		
	}
}

void FeatureManager::removeFeatures(int position)
{
	DoublyLinkedNodeIterator<Feature> iter(*_featureList);
	iter++;
	for (position; position > 0; position--)
	{
		iter++;
	}
	iter.getNode()->getValue().setState(FEATURE_NULL);
	FeatureNode* node = iter.getNode();
	iter.getNode()->dropNode();
	iter = iter.last();
	iter.getNode()->insertBefore(*node);
}

FeatureNode* FeatureManager::getFeatureList()
{
	return _featureList;
}

Feature* FeatureManager::getReccuringFeature()
{
	DoublyLinkedNodeIterator<Feature> iter(*_featureList);
	iter++;
	Feature* anchor = &iter.getNode()->getValue();
	removeFeatures(0);
	return anchor;
}

bool FeatureManager::isAnchor()
{
	DoublyLinkedNodeIterator<Feature> iter(*_featureList);
	iter++;
	for (int i = featureListSize(); i > 0; i--)
	{
		if (iter.getNode()->getValue().getOccurances() >= L_FEATURE_OCCURANCES)
		{
			//move the anchor to the start of the feature list for easy collection
			FeatureNode* node = iter.getNode();
			iter.getNode()->dropNode();
			iter = iter.first();
			iter.getNode()->insertAfter(*node);
			return true;
		}
		iter++;
	}
	return false;
}