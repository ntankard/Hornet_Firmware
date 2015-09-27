#pragma once

#include "CONFIG.h"
#include "Anchor.h"
#include "DoublyLinkedNodeIterator.h"

typedef DoublyLinkedNode<Anchor>::Node AnchorNode;

class AnchorManager
{
public:
	AnchorManager();
	void addAnchor(Feature* reccuringFeature);
	AnchorNode* getAnchorList();
	int anchorListSize();
private:
	AnchorNode* _anchorList;
	Anchor _anchors[L_ANCHORS_STORED + 2];
	AnchorNode _nodes[L_ANCHORS_STORED + 2];
};