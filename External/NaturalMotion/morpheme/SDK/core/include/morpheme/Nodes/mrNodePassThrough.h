// Copyright (c) 2010 NaturalMotion.  All Rights Reserved.
// Not to be copied, adapted, modified, used, distributed, sold,
// licensed or commercially exploited in any manner without the
// written consent of NaturalMotion.
//
// All non public elements of this software are the confidential
// information of NaturalMotion and may not be disclosed to any
// person nor used for any purpose not expressly approved by
// NaturalMotion in writing.

//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
#ifndef MR_NODE_PASSTHROUGH_H
#define MR_NODE_PASSTHROUGH_H
//----------------------------------------------------------------------------------------------------------------------
#include "morpheme/mrNetwork.h"
//----------------------------------------------------------------------------------------------------------------------

#define IK_NODE_PASS_THROUGH_WEIGHT 0.0001f

namespace MR
{

//----------------------------------------------------------------------------------------------------------------------
// Queuing function declarations
Task* queuePassThroughChild0(NodeDef* node, TaskQueue* queue, Network* net, TaskParameter* dependentParameter);
Task* queuePassThroughChild1(NodeDef* node, TaskQueue* queue, Network* net, TaskParameter* dependentParameter);

//----------------------------------------------------------------------------------------------------------------------
Task* queuePassThroughOnChildNodeID(
  NodeID          activeChildNodeID,
  NodeDef*        node,
  TaskQueue*      queue,
  Network*        net,
  TaskParameter*  dependentParameter);

//----------------------------------------------------------------------------------------------------------------------
NodeID filterNodeFindGeneratingNodeForSemantic(
  NodeID              callingNodeID,
  bool                fromParent,   // Was this query from a parent or child node.
  AttribDataSemantic  semantic,
  NodeDef*            node,
  Network*            net);

}
//----------------------------------------------------------------------------------------------------------------------
#endif // MR_NODE_PASSTHROUGH_H
//----------------------------------------------------------------------------------------------------------------------
