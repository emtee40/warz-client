/*
* Copyright 2013 Autodesk, Inc. All rights reserved.
* Use of this software is subject to the terms of the Autodesk license agreement and any attachments or Appendices thereto provided at the time of installation or download,
* or which otherwise accompanies this software in either electronic or hard copy form, or which is signed by you and accepted by Autodesk.
*/

// Primary contact: MAMU - secondary contact: NOBODY
#ifndef Navigation_SegmentCanGoQuery_DisplayListBuilder_H
#define Navigation_SegmentCanGoQuery_DisplayListBuilder_H

#include "gwnavruntime/visualsystem/displaylist.h"
#include "gwnavruntime/queries/blobs/segmentcangoqueryblob.h"
#include "gwnavruntime/queries/segmentcangoquery.h"
#include "gwnavruntime/queries/blobs/querydynamicoutputdisplaylistbuilder.h"

namespace Kaim
{

class SegmentCanGoQueryDisplayListBuilder : public IDisplayListBuilder
{
	virtual void DoBuild(ScopedDisplayList* displayList, char* blob, KyUInt32 /*deepBlobSize*/ = 0)
	{
		const SegmentCanGoQueryBlob* queryBlob = (SegmentCanGoQueryBlob*) blob;
		KyFloat32 triangleZOffset = 0.1f;
		
		SegmentCanGoQueryOutputBlob* queryOutputBlob = queryBlob->m_queryOutput.Ptr();
		if (queryOutputBlob != NULL)
		{
			Vec3f offsetVector = Vec3f::UnitZ();
			KyFloat32 arrowHalfWidth = 0.05f;

			VisualShapeColor shapeColor;
			switch((SegmentCanGoQueryResult)queryOutputBlob->m_result)
			{
				case SEGMENTCANGO_NOT_INITIALIZED: break;
				case SEGMENTCANGO_NOT_PROCESSED:
					{
						shapeColor.m_triangleColor = VisualColor::Orange;
						displayList->PushArrow(queryBlob->m_startPos3f, queryBlob->m_destPos3f, arrowHalfWidth, shapeColor, 3.0f, 0.1f);

						shapeColor.SetOnlyLineColor(shapeColor.m_triangleColor);
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
				case SEGMENTCANGO_DONE_START_OUTSIDE:
					{
						shapeColor.m_lineColor = VisualColor::Red;
						displayList->PushText(queryBlob->m_startPos3f + offsetVector, shapeColor.m_lineColor, "Start outside!");
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
				case SEGMENTCANGO_DONE_START_NAVTAG_FORBIDDEN:
					{
						shapeColor.m_lineColor = VisualColor::Red;
						
						Triangle3f triangle = queryOutputBlob->m_startTriangle.m_triangle;
						triangle.A.z += triangleZOffset;
						triangle.B.z += triangleZOffset;
						triangle.C.z += triangleZOffset;
						displayList->PushTriangle(triangle, shapeColor);
						displayList->PushText(queryBlob->m_startPos3f + offsetVector, VisualColor::Red, "Start NavTag forbidden!");
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
				case SEGMENTCANGO_DONE_COLLISION_DETECTED:
					{
						shapeColor.m_lineColor = VisualColor::Lime;
						
						Triangle3f triangle = queryOutputBlob->m_startTriangle.m_triangle;
						triangle.A.z += triangleZOffset;
						triangle.B.z += triangleZOffset;
						triangle.C.z += triangleZOffset;
						displayList->PushTriangle(triangle, shapeColor);
						
						shapeColor.m_lineColor = VisualColor::Red;
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
				case SEGMENTCANGO_DONE_ARRIVAL_WRONG_FLOOR:
					{
						shapeColor.m_lineColor = VisualColor::Lime;
						
						Triangle3f triangle = queryOutputBlob->m_startTriangle.m_triangle;
						triangle.A.z += triangleZOffset;
						triangle.B.z += triangleZOffset;
						triangle.C.z += triangleZOffset;
						displayList->PushTriangle(triangle, shapeColor);

						shapeColor.m_lineColor = VisualColor::Red;
						displayList->PushText(queryBlob->m_destPos3f + offsetVector, shapeColor.m_lineColor, "Arrival in wrong floor!");
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
				case SEGMENTCANGO_DONE_LACK_OF_WORKING_MEMORY:
					{
						shapeColor.m_lineColor = VisualColor::Lime;
						
						Triangle3f triangle = queryOutputBlob->m_startTriangle.m_triangle;
						triangle.A.z += triangleZOffset;
						triangle.B.z += triangleZOffset;
						triangle.C.z += triangleZOffset;
						displayList->PushTriangle(triangle, shapeColor);

						shapeColor.m_lineColor = VisualColor::Red;
						displayList->PushText(queryBlob->m_destPos3f + offsetVector, shapeColor.m_lineColor, "Lack of working memory!");
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
				case SEGMENTCANGO_DONE_UNKNOWN_ERROR:
					{
						shapeColor.m_lineColor = VisualColor::Red;
						displayList->PushText(queryBlob->m_destPos3f + offsetVector, shapeColor.m_lineColor, "Unknown error!");
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
				case SEGMENTCANGO_DONE_SUCCESS:
					{
						shapeColor.m_lineColor = VisualColor::Lime;
						
						Triangle3f triangle = queryOutputBlob->m_startTriangle.m_triangle;
						triangle.A.z += triangleZOffset;
						triangle.B.z += triangleZOffset;
						triangle.C.z += triangleZOffset;
						displayList->PushTriangle(triangle, shapeColor);
						triangle = queryOutputBlob->m_destTriangle.m_triangle;
						triangle.A.z += triangleZOffset;
						triangle.B.z += triangleZOffset;
						triangle.C.z += triangleZOffset;
						displayList->PushQuad(queryBlob->m_startPos3f, queryBlob->m_destPos3f, queryBlob->m_radius, shapeColor);
					}
					break;
			}

			QueryDynamicOutputBlob* queryDynamicOutputBlob = queryOutputBlob->m_queryDynamicOutputBlobRef.Ptr();
			if (queryDynamicOutputBlob != NULL)
			{
				QueryDynamicOutputDisplayListBuilder dynamicOutputDLBuilder;
				dynamicOutputDLBuilder.DoBuild(displayList, (char*)queryDynamicOutputBlob, 0);
			}
		}
	}
};

}

#endif