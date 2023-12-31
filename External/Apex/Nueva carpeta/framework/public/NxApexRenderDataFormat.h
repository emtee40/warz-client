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

#ifndef NX_APEX_RENDER_DATA_FORMAT_H
#define NX_APEX_RENDER_DATA_FORMAT_H

#include "NxApexUsingNamespace.h"
#include "foundation/PxAssert.h"
#include "foundation/PxMat33.h"

namespace physx
{
namespace apex
{

PX_PUSH_PACK_DEFAULT

/**
\brief Enumeration of possible formats of various buffer semantics

N.B.: DO NOT CHANGE THE VALUES OF OLD FORMATS.
*/
struct NxRenderDataFormat
{
	/** \brief the enum type */
	enum Enum
	{
		UNSPECIFIED =			0,	//!< No format (semantic not used)

		//!< Integer formats
		UBYTE1 =				1,	//!< One unsigned 8-bit integer (PxU8[1])
		UBYTE2 =				2,	//!< Two unsigned 8-bit integers (PxU8[2])
		UBYTE3 =				3,	//!< Three unsigned 8-bit integers (PxU8[3])
		UBYTE4 =				4,	//!< Four unsigned 8-bit integers (PxU8[4])

		USHORT1 =				5,	//!< One unsigned 16-bit integer (PxU16[1])
		USHORT2 =				6,	//!< Two unsigned 16-bit integers (PxU16[2])
		USHORT3 =				7,	//!< Three unsigned 16-bit integers (PxU16[3])
		USHORT4 =				8,	//!< Four unsigned 16-bit integers (PxU16[4])

		SHORT1 =				9,	//!< One signed 16-bit integer (PxI16[1])
		SHORT2 =				10,	//!< Two signed 16-bit integers (PxI16[2])
		SHORT3 =				11,	//!< Three signed 16-bit integers (PxI16[3])
		SHORT4 =				12,	//!< Four signed 16-bit integers (PxI16[4])

		UINT1 =					13,	//!< One unsigned integer (PxU32[1])
		UINT2 =					14,	//!< Two unsigned integers (PxU32[2])
		UINT3 =					15,	//!< Three unsigned integers (PxU32[3])
		UINT4 =					16,	//!< Four unsigned integers (PxU32[4])

		//!< Color formats
		R8G8B8A8 =				17,	//!< Four unsigned bytes (PxU8[4]) representing red, green, blue, alpha
		B8G8R8A8 =				18,	//!< Four unsigned bytes (PxU8[4]) representing blue, green, red, alpha
		R32G32B32A32_FLOAT =	19,	//!< Four floats (PxF32[4]) representing red, green, blue, alpha
		B32G32R32A32_FLOAT =	20,	//!< Four floats (PxF32[4]) representing blue, green, red, alpha

		//!< Normalized formats
		BYTE_UNORM1 =			21,	//!< One unsigned normalized value in the range [0,1], packed into 8 bits (PxU8[1])
		BYTE_UNORM2 =			22,	//!< Two unsigned normalized value in the range [0,1], each packed into 8 bits (PxU8[2])
		BYTE_UNORM3 =			23,	//!< Three unsigned normalized value in the range [0,1], each packed into bits (PxU8[3])
		BYTE_UNORM4 =			24,	//!< Four unsigned normalized value in the range [0,1], each packed into 8 bits (PxU8[4])

		SHORT_UNORM1 =			25,	//!< One unsigned normalized value in the range [0,1], packed into 16 bits (PxU16[1])
		SHORT_UNORM2 =			26,	//!< Two unsigned normalized value in the range [0,1], each packed into 16 bits (PxU16[2])
		SHORT_UNORM3 =			27,	//!< Three unsigned normalized value in the range [0,1], each packed into 16 bits (PxU16[3])
		SHORT_UNORM4 =			28,	//!< Four unsigned normalized value in the range [0,1], each packed into 16 bits (PxU16[4])

		BYTE_SNORM1 =			29,	//!< One signed normalized value in the range [-1,1], packed into 8 bits (PxU8[1])
		BYTE_SNORM2 =			30,	//!< Two signed normalized value in the range [-1,1], each packed into 8 bits (PxU8[2])
		BYTE_SNORM3 =			31,	//!< Three signed normalized value in the range [-1,1], each packed into bits (PxU8[3])
		BYTE_SNORM4 =			32,	//!< Four signed normalized value in the range [-1,1], each packed into 8 bits (PxU8[4])

		SHORT_SNORM1 =			33,	//!< One signed normalized value in the range [-1,1], packed into 16 bits (PxU16[1])
		SHORT_SNORM2 =			34,	//!< Two signed normalized value in the range [-1,1], each packed into 16 bits (PxU16[2])
		SHORT_SNORM3 =			35,	//!< Three signed normalized value in the range [-1,1], each packed into 16 bits (PxU16[3])
		SHORT_SNORM4 =			36,	//!< Four signed normalized value in the range [-1,1], each packed into 16 bits (PxU16[4])

		//!< Float formats
		HALF1 =					37,	//!< One 16-bit floating point value
		HALF2 =					38,	//!< Two 16-bit floating point values
		HALF3 =					39,	//!< Three 16-bit floating point values
		HALF4 =					40,	//!< Four 16-bit floating point values

		FLOAT1 =				41,	//!< One 32-bit floating point value
		FLOAT2 =				42,	//!< Two 32-bit floating point values
		FLOAT3 =				43,	//!< Three 32-bit floating point values
		FLOAT4 =				44,	//!< Four 32-bit floating point values

		FLOAT3x4 =				45,	//!< A 3x4 matrix (see PxMat34)
		FLOAT3x3 =				46,	//!< A 3x3 matrix (see PxMat33)

		FLOAT4_QUAT =			47,	//!< A quaternion (see PxQuat)
		BYTE_SNORM4_QUATXYZW =	48,	//!< A normalized quaternion with signed byte elements, X,Y,Z,W format (PxU8[4])
		SHORT_SNORM4_QUATXYZW =	49,	//!< A normalized quaternion with signed short elements, X,Y,Z,W format (PxU16[4])

		NUM_FORMATS
	};

	/// Get byte size of format type
	static PX_INLINE physx::PxU32 getFormatDataSize(Enum format)
	{
		switch (format)
		{
		default:
			PX_ALWAYS_ASSERT();
		case UNSPECIFIED:
			return 0;

		case UBYTE1:
		case BYTE_UNORM1:
		case BYTE_SNORM1:
			return sizeof(physx::PxU8);
		case UBYTE2:
		case BYTE_UNORM2:
		case BYTE_SNORM2:
			return sizeof(physx::PxU8) * 2;
		case UBYTE3:
		case BYTE_UNORM3:
		case BYTE_SNORM3:
			return sizeof(physx::PxU8) * 3;
		case UBYTE4:
		case BYTE_UNORM4:
		case BYTE_SNORM4:
		case BYTE_SNORM4_QUATXYZW:
			return sizeof(physx::PxU8) * 4;

		case USHORT1:
		case SHORT1:
		case HALF1:
		case SHORT_UNORM1:
		case SHORT_SNORM1:
			return sizeof(physx::PxU16);
		case USHORT2:
		case SHORT2:
		case HALF2:
		case SHORT_UNORM2:
		case SHORT_SNORM2:
			return sizeof(physx::PxU16) * 2;
		case USHORT3:
		case SHORT3:
		case HALF3:
		case SHORT_UNORM3:
		case SHORT_SNORM3:
			return sizeof(physx::PxU16) * 3;
		case USHORT4:
		case SHORT4:
		case HALF4:
		case SHORT_UNORM4:
		case SHORT_SNORM4:
		case SHORT_SNORM4_QUATXYZW:
			return sizeof(physx::PxU16) * 4;

		case UINT1:
			return sizeof(physx::PxU32);
		case UINT2:
			return sizeof(physx::PxU32) * 2;
		case UINT3:
			return sizeof(physx::PxU32) * 3;
		case UINT4:
			return sizeof(physx::PxU32) * 4;

		case R8G8B8A8:
		case B8G8R8A8:
			return sizeof(physx::PxU8) * 4;

		case R32G32B32A32_FLOAT:
		case B32G32R32A32_FLOAT:
			return sizeof(physx::PxF32) * 4;

		case FLOAT1:
			return sizeof(physx::PxF32);
		case FLOAT2:
			return sizeof(physx::PxF32) * 2;
		case FLOAT3:
			return sizeof(physx::PxF32) * 3;
		case FLOAT4:
			return sizeof(physx::PxF32) * 4;

		case FLOAT3x4:
			return sizeof(physx::PxF32) * 12;

		case FLOAT3x3:
			return sizeof(physx::PxMat33);

		case FLOAT4_QUAT:
			return sizeof(physx::PxQuat);
		}
	}
};

PX_POP_PACK

}
} // end namespace physx::apex

#endif	// NX_APEX_RENDER_DATA_FORMAT_H
