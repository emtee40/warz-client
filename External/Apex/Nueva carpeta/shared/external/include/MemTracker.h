// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2012 NVIDIA Corporation. All rights reserved.

#ifndef MEM_TRACKER_H

#define MEM_TRACKER_H

#include "foundation/PxSimpleTypes.h"

#ifdef PX_WINDOWS // only compile this source code for windows!!

namespace MEM_TRACKER
{

/**
\brief The layout format for the memory report.
*/
enum MemoryReportFormat
{
	MRF_SIMPLE_HTML,       // just a very simple HTML document containing the tables.
	MRF_CSV,               // Saves the Tables out as comma seperated value text
	MRF_TEXT,              // Saves the tables out in human readable text format.
	MRF_TEXT_EXTENDED,     // Saves the tables out in human readable text format, but uses the MS-DOS style extended ASCII character set for the borders.
};

/**
\brief This enumeration indicates the type of memory allocation that is being performed.
*/
enum MemoryType
{
	MT_NEW,						// Captured new operator
	MT_NEW_ARRAY,				// Captured new array operator
	MT_MALLOC,					// Standard heap allocation
	MT_FREE,					// Standard heap free
	MT_DELETE,					// Captured delete operator
	MT_DELETE_ARRAY,			// Captured array delete
	MT_GLOBAL_NEW,				// Allocation via Global new
	MT_GLOBAL_NEW_ARRAY,		// Allocation via global new array
	MT_GLOBAL_DELETE,			// Deallocation via global delete
	MT_GLOBAL_DELETE_ARRAY,		// Deallocation via global delete array
};

/**
\brief This data structure is used to return the current state of a particular block of allocated memory.
*/
struct TrackInfo
{
	const void		*mMemory;		// Address of memory
	MemoryType		 mType;			// Type of allocation
	size_t			mSize;			// Size of the memory allocation
	const char		*mContext;		// The context of the memory allocation.
	const char		*mClassName;	// The class or type name of this allocation.
	const char		*mFileName;		// Source code file name where this allocation occured
	physx::PxU32	 mLineNo;		// Source code line number where this allocation occured
	size_t			mAllocCount; 	// Indicates which time this allocation occured at this particular source file and line number.
};


class MemTracker
{
public:

  virtual void trackAlloc(size_t threadId,
                          void *mem,
                          size_t size,
                          MemoryType type,
                          const char *context,
                          const char *className,
                          const char *fileName,
                          physx::PxU32 lineno) = 0;

  virtual void trackRealloc(size_t threadId,
	                          void *oldMem,
 	                          void *newMem,
	                          size_t newSize,
	                          const char *context,
	                          const char *className,
	                          const char *fileName,
	                          physx::PxU32 lineno) = 0;

  virtual void trackFree(size_t threadId,
                        void *mem,
                        MemoryType type,
                        const char *context,
                        const char *fileName,physx::PxU32 lineno) = 0;

  virtual const char * trackValidateFree(size_t threadId,
	  void *mem,
	  MemoryType type,
	  const char *context,
	  const char *fileName,physx::PxU32 lineno) = 0;


   virtual void trackFrame(void) = 0;


   virtual bool trackInfo(const void *mem,TrackInfo &info)  = 0;


   virtual void *generateReport(MemoryReportFormat format,const char *fname,physx::PxU32 &saveLen,bool reportAllLeaks) = 0;
   virtual void releaseReportMemory(void *mem) = 0;

    virtual void usage(void) = 0;
    virtual size_t detectLeaks(size_t &acount) = 0;
    virtual void setLogLevel(bool logEveryAllocation,bool logEveyFrame,bool verifySingleThreaded) = 0;

};

MemTracker *createMemTracker(void);
void        releaseMemTracker(MemTracker *mt);

};

#endif

#endif
