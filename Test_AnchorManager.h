#pragma once

#if BUILD_TYPE == FOR_TEST

#include "FeatureManager.h"
#include "PatternManager.h"
#include "AnchorManager.h"

test(AnchorManager_setup)
{
	AnchorManager _anchorManager;
	DoublyLinkedNodeIterator<Anchor> iter(*_anchorManager.getAnchorList());
	assertEqual(iter.getNode()->getValue().getState(), ANCHOR_HEAD);
	iter++;
	for (int i = 0; i < L_ANCHORS_STORED; i++)
	{
		assertEqual(iter.getNode()->getValue().getState(), ANCHOR_NULL);
		iter++;
	}
	assertEqual(iter.getNode()->getValue().getState(), ANCHOR_TAIL);
}

#endif