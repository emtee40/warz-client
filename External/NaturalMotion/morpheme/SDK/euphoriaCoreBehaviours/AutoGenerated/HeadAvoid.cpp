/*
 * Copyright (c) 2013 NaturalMotion Ltd. All rights reserved.
 *
 * Not to be copied, adapted, modified, used, distributed, sold,
 * licensed or commercially exploited in any manner without the
 * written consent of NaturalMotion.
 *
 * All non public elements of this software are the confidential
 * information of NaturalMotion and may not be disclosed to any
 * person nor used for any purpose not expressly approved by
 * NaturalMotion in writing.
 *
 */

//----------------------------------------------------------------------------------------------------------------------
//                                  This file is auto-generated
//----------------------------------------------------------------------------------------------------------------------

// module def dependencies
#include "Head.h"
#include "HeadAvoid.h"
#include "HeadAvoidPackaging.h"
#include "MyNetwork.h"
#include "HazardManagement.h"
#include "HazardResponse.h"
#include "HeadAvoidBehaviourInterface.h"
#include "HeadPackaging.h"
#include "MyNetworkPackaging.h"

// misc
#include "euphoria/erEuphoriaLogger.h"
#include "euphoria/erDebugDraw.h"
#include "physics/mrPhysicsSerialisationBuffer.h"



namespace NM_BEHAVIOUR_LIB_NAMESPACE
{

//----------------------------------------------------------------------------------------------------------------------
HeadAvoid::HeadAvoid(ER::ModuleDataAllocator* mdAllocator, ER::ModuleCon* connectionSet) : ER::Module(mdAllocator, connectionSet)
{
  data = (HeadAvoidData*)mdAllocator->alloc(ER::ModuleDataAllocator::Data, sizeof(HeadAvoidData), __alignof(HeadAvoidData));
  in = (HeadAvoidInputs*)mdAllocator->alloc(ER::ModuleDataAllocator::Inputs, sizeof(HeadAvoidInputs), __alignof(HeadAvoidInputs));
  feedOut = (HeadAvoidFeedbackOutputs*)mdAllocator->alloc(ER::ModuleDataAllocator::FeedbackOutputs, sizeof(HeadAvoidFeedbackOutputs), __alignof(HeadAvoidFeedbackOutputs));
  out = (HeadAvoidOutputs*)mdAllocator->alloc(ER::ModuleDataAllocator::Outputs, sizeof(HeadAvoidOutputs), __alignof(HeadAvoidOutputs));

  m_apiBase = (HeadAvoidAPIBase*)NMPMemoryAllocAligned(sizeof(HeadAvoidAPIBase), 16);
  m_updatePackage = (HeadAvoidUpdatePackage*)NMPMemoryAllocAligned(sizeof(HeadAvoidUpdatePackage), 16);
  m_feedbackPackage = (HeadAvoidFeedbackPackage*)NMPMemoryAllocAligned(sizeof(HeadAvoidFeedbackPackage), 16);
}

//----------------------------------------------------------------------------------------------------------------------
HeadAvoid::~HeadAvoid()
{
  owner = 0;

  NMP::Memory::memFree(m_apiBase);
  NMP::Memory::memFree(m_updatePackage);
  NMP::Memory::memFree(m_feedbackPackage);
}

//----------------------------------------------------------------------------------------------------------------------
void HeadAvoid::create(ER::Module* parent, int childIndex)
{
  ER::Module::create(parent, childIndex);
  owner = (Head*)parent;
  if (getConnections())
    getConnections()->create(this, (ER::Module*)owner);


  new(m_apiBase) HeadAvoidAPIBase( data, in, owner->m_apiBase);
  new(m_updatePackage) HeadAvoidUpdatePackage(
    data, in, out, 
    owner->m_apiBase  );
  new(m_feedbackPackage) HeadAvoidFeedbackPackage(
    data, in, feedOut, 
    owner->m_apiBase  );
}

//----------------------------------------------------------------------------------------------------------------------
void HeadAvoid::clearAllData()
{
  data->clear();
  in->clear();
  out->clear();
  feedOut->clear();
}

//----------------------------------------------------------------------------------------------------------------------
bool HeadAvoid::storeState(MR::PhysicsSerialisationBuffer& savedState)
{
  savedState.addValue(*data);
  savedState.addValue(*in);
  savedState.addValue(*feedOut);
  savedState.addValue(*out);
  storeStateChildren(savedState);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool HeadAvoid::restoreState(MR::PhysicsSerialisationBuffer& savedState)
{
  *data = savedState.getValue<HeadAvoidData>();
  *in = savedState.getValue<HeadAvoidInputs>();
  *feedOut = savedState.getValue<HeadAvoidFeedbackOutputs>();
  *out = savedState.getValue<HeadAvoidOutputs>();
  restoreStateChildren(savedState);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
const char* HeadAvoid::getChildName(int32_t) const
{
  NMP_ASSERT_FAIL();
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
void HeadAvoid::update(float timeStep)
{
  const ER::RootModule* rootModule = getRootModule();
  MR_DEBUG_MODULE_ENTER(rootModule->getDebugInterface(), getClassName());
  m_updatePackage->update(timeStep, rootModule->getDebugInterface());
#if NM_CALL_VALIDATORS
  data->validate();
#endif // NM_CALL_VALIDATORS
}

//----------------------------------------------------------------------------------------------------------------------
void HeadAvoid::feedback(float timeStep)
{
  const ER::RootModule* rootModule = getRootModule();
  MR_DEBUG_MODULE_ENTER(rootModule->getDebugInterface(), getClassName());
  m_feedbackPackage->feedback(timeStep, rootModule->getDebugInterface());
#if NM_CALL_VALIDATORS
  data->validate();
#endif // NM_CALL_VALIDATORS
}


} // namespace NM_BEHAVIOUR_LIB_NAMESPACE


