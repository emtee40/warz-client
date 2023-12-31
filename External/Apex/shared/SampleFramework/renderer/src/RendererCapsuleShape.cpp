/*
 * Copyright 2008-2012 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */
//
// RendererCapsuleShape : convenience class for generating a capsule mesh.
//

#include <PsUtilities.h>

#include <RendererCapsuleShape.h>

#include <Renderer.h>

#include <RendererVertexBuffer.h>
#include <RendererVertexBufferDesc.h>

#include <RendererIndexBuffer.h>
#include <RendererIndexBufferDesc.h>

#include <RendererMesh.h>
#include <RendererMeshDesc.h>

#include <RendererMemoryMacros.h>
#include "PsUtilities.h"

using namespace SampleRenderer;

namespace 
{

const PxU32 g_numSlices = 8;  // along lines of longitude
const PxU32 g_numStacks = 16; // along lines of latitude

const PxU32 g_numSphereVertices = (g_numSlices*2+1)*(g_numStacks+1);
const PxU32 g_numSphereIndices = g_numSlices*2*g_numStacks*6;

const PxU32 g_numConeVertices = (g_numSlices*2+1)*2;
const PxU32 g_numConeIndices = g_numSlices*2*6;

PxVec3 g_spherePositions[g_numSphereVertices];
PxU16 g_sphereIndices[g_numSphereIndices];

PxVec3 g_conePositions[g_numConeVertices];
PxU16 g_coneIndices[g_numConeIndices];

// total vertex count
const PxU32 g_numCapsuleVertices = 2*g_numSphereVertices + g_numConeVertices;
const PxU32 g_numCapsuleIndices = 2*g_numSphereIndices + g_numConeIndices;

void generateSphereMesh(PxU16 slices, PxU16 stacks, PxVec3* positions, PxU16* indices)
{
	const PxF32 thetaStep = PxPi/stacks;
	const PxF32 phiStep = PxTwoPi/(slices*2);

	PxF32 theta = 0.0f;

	// generate vertices
	for (PxU16 y=0; y <= stacks; ++y)
	{
		PxF32 phi = 0.0f;

		PxF32 cosTheta = PxCos(theta);
		PxF32 sinTheta = PxSin(theta);

		for (PxU16 x=0; x <= slices*2; ++x)
		{			
			PxF32 cosPhi = PxCos(phi);
			PxF32 sinPhi = PxSin(phi);

			PxVec3 p(cosPhi*sinTheta, cosTheta, sinPhi*sinTheta);

			// write vertex
			*(positions++)= p;

			phi += phiStep;
		}			

		theta += thetaStep;
	}

	const PxU16 numRingQuads = 2*slices;
	const PxU16 numRingVerts = 2*slices+1;

	// add faces
	for (PxU16 y=0; y < stacks; ++y)
	{
		for (PxU16 i=0; i < numRingQuads; ++i)
		{
			// add a quad
			*(indices++) = (y+0)*numRingVerts + i;
			*(indices++) = (y+1)*numRingVerts + i;
			*(indices++) = (y+1)*numRingVerts + i + 1;

			*(indices++) = (y+1)*numRingVerts + i + 1;
			*(indices++) = (y+0)*numRingVerts + i + 1;
			*(indices++) = (y+0)*numRingVerts + i;
		}
	}
}

void generateConeMesh(PxU16 slices, PxVec3* positions, PxU16* indices, PxU16 offset)
{
	// generate vertices
	const PxF32 phiStep = PxTwoPi/(slices*2);
	PxF32 phi = 0.0f;

	// generate two rings of vertices for the cone ends
	for (int i=0; i < 2; ++i)
	{
		for (PxU16 x=0; x <= slices*2; ++x)
		{			
			PxF32 cosPhi = PxCos(phi);
			PxF32 sinPhi = PxSin(phi);

			PxVec3 p(cosPhi, 0.0f, sinPhi);

			// write vertex
			*(positions++)= p;

			phi += phiStep;
		}			
	}

	const PxU16 numRingQuads = 2*slices;
	const PxU16 numRingVerts = 2*slices+1;

	// add faces
	for (PxU16 i=0; i < numRingQuads; ++i)
	{
		// add a quad
		*(indices++) = offset + i;
		*(indices++) = offset + numRingVerts + i;
		*(indices++) = offset + numRingVerts + i + 1;

		*(indices++) = offset + numRingVerts + i + 1;
		*(indices++) = offset + i + 1;
		*(indices++) = offset + i;
	}
}

void generateCapsuleMesh()
{	
	generateSphereMesh(g_numSlices, g_numStacks, g_spherePositions, g_sphereIndices);
	generateConeMesh(g_numSlices, g_conePositions, g_coneIndices, g_numSphereVertices*2);	
}

} // anonymous namespace

RendererCapsuleShape::RendererCapsuleShape(Renderer &renderer, PxF32 halfHeight, PxF32 radius) : RendererShape(renderer)
{
	static bool meshValid = false;
	if (!meshValid)
	{
		generateCapsuleMesh();
		meshValid = true;
	}

	RendererVertexBufferDesc vbdesc;
	vbdesc.hint = RendererVertexBuffer::HINT_STATIC;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_POSITION] = RendererVertexBuffer::FORMAT_FLOAT3;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_NORMAL]   = RendererVertexBuffer::FORMAT_FLOAT3;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_TEXCOORD0] = RendererVertexBuffer::FORMAT_FLOAT2;
	vbdesc.maxVertices = g_numCapsuleVertices;
	m_vertexBuffer = m_renderer.createVertexBuffer(vbdesc);
	RENDERER_ASSERT(m_vertexBuffer, "Failed to create Vertex Buffer.");

	RendererIndexBufferDesc ibdesc;
	ibdesc.hint       = RendererIndexBuffer::HINT_STATIC;
	ibdesc.format     = RendererIndexBuffer::FORMAT_UINT16;
	ibdesc.maxIndices = g_numCapsuleIndices;
	m_indexBuffer = m_renderer.createIndexBuffer(ibdesc);
	RENDERER_ASSERT(m_indexBuffer, "Failed to create Index Buffer.");

	// set position data
	setDimensions(halfHeight, radius, radius);

	if(m_indexBuffer)
	{
		PxU16 *indices = (PxU16*)m_indexBuffer->lock();
		if(indices)
		{
			// first sphere
			for (PxU32 i=0; i < g_numSphereIndices; ++i)
				indices[i] = g_sphereIndices[i];

			indices += g_numSphereIndices;

			// second sphere
			for (PxU32 i=0; i < g_numSphereIndices; ++i)
				indices[i] = g_sphereIndices[i] + g_numSphereVertices;

			indices += g_numSphereIndices;

			// cone indices
			for (PxU32 i=0; i < g_numConeIndices; ++i)
				indices[i] = g_coneIndices[i];
		}
		m_indexBuffer->unlock();
	}

	if(m_vertexBuffer && m_indexBuffer)
	{
		RendererMeshDesc meshdesc;
		meshdesc.primitives       = RendererMesh::PRIMITIVE_TRIANGLES;
		meshdesc.vertexBuffers    = &m_vertexBuffer;
		meshdesc.numVertexBuffers = 1;
		meshdesc.firstVertex      = 0;
		meshdesc.numVertices      = g_numCapsuleVertices;
		meshdesc.indexBuffer      = m_indexBuffer;
		meshdesc.firstIndex       = 0;
		meshdesc.numIndices       = g_numCapsuleIndices;
		m_mesh = m_renderer.createMesh(meshdesc);
		RENDERER_ASSERT(m_mesh, "Failed to create Mesh.");
	}
}

RendererCapsuleShape::~RendererCapsuleShape(void)
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);
	SAFE_RELEASE(m_mesh);
}

void RendererCapsuleShape::setDimensions(PxF32 halfHeight, PxF32 radius0, PxF32 radius1)
{
	if(m_vertexBuffer)
	{
		PxU32 positionStride = 0;
		PxVec3* positions = (PxVec3*)m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride);

		PxU32 normalStride = 0;
		PxVec3* normals = (PxVec3*)m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride);

		if (positions && normals)
		{
			const PxF32 radii[2] = { radius1, radius0};
			const PxF32 offsets[2] = { halfHeight, -halfHeight };

			// write two copies of the sphere mesh scaled and offset appropriately
			for (PxU32 s=0; s < 2; ++s)
			{
				const PxF32 r = radii[s];
				const PxF32 offset = offsets[s];

				for (PxU32 i=0; i < g_numSphereVertices; ++i)
				{
					PxVec3 p = g_spherePositions[i]*r;
					p.y += offset;

					*positions = p;
					*normals = g_spherePositions[i];

					positions = (PxVec3*)(((PxU8*)positions)+positionStride);
					normals = (PxVec3*)(((PxU8*)normals)+normalStride);
				}
			}

			// calculate cone angle
			PxF32 cosTheta = (radius0-radius1)/(halfHeight*2.0f);

			// scale factor for normals to avoid re-normalizing each time
			PxF32 nscale = PxSqrt(1.0f - cosTheta*cosTheta);

			for (PxU32 s=0; s < 2; ++s)
			{
				const PxF32 y = radii[s]*cosTheta;
				const PxF32 r = PxSqrt(radii[s]*radii[s] - y*y);
				const PxF32 offset = offsets[s] + y;

				for (PxU32 i=0; i < g_numConeVertices/2; ++i)
				{		
					PxVec3 p = g_conePositions[i]*r;
					p.y += offset;
					*positions = p;

					PxVec3 n = g_conePositions[i]*nscale;
					n.y = cosTheta;
					*normals = n;

					positions = (PxVec3*)(((PxU8*)positions)+positionStride);
					normals = (PxVec3*)(((PxU8*)normals)+normalStride);
				}
			}
		}
	
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
	}
}
