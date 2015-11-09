#pragma once

#include "AnchorManager.h"

AnchorManager::AnchorManager()
{
	_anchors[0].setState(ANCHOR_HEAD); //headnode
	_nodes[0].setValue(_anchors[0]);
	_anchors[L_ANCHORS_STORED + 1].setState(ANCHOR_TAIL); //tailnode
	_nodes[L_ANCHORS_STORED + 1].setValue(_anchors[L_ANCHORS_STORED + 1]);
	_anchorList = &_nodes[0];
	_anchorList->insertAfter(_nodes[L_ANCHORS_STORED + 1]);
	for (int i = 0; i < L_ANCHORS_STORED; i++)
	{
		_anchors[i + 1].setState(ANCHOR_NULL);
		_nodes[i + 1].setValue(_anchors[i + 1]);
		_anchorList->insertAfter(_nodes[i + 1]);
	}
}

void AnchorManager::addAnchor(Feature* recurringFeature)
{
	DoublyLinkedNodeIterator<Anchor> iter(*_anchorList);
	iter = iter.first();
	for (iter; iter.getNode()->getValue().getState() != ANCHOR_NULL; iter++)
	{
		//goes to the next ANCHOR_NULL
	}
	iter.getNode()->getValue().setAnchor(recurringFeature);
}

AnchorNode* AnchorManager::getAnchorList()
{
	return _anchorList;
}

int AnchorManager::anchorListSize()
{
	int count = 0;
	DoublyLinkedNodeIterator<Anchor> iter(*_anchorList);
	iter = iter.first();
	iter++;
	for (iter; iter.getNode()->getValue().getState() != ANCHOR_NULL; iter++)
	{
		//goes to the next ANCHOR_NULL
		count++;
	}
	return count;
}