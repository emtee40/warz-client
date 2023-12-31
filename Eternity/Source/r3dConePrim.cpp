#include "r3dPCH.h"
#include "r3d.h"

#include "r3dConePrim.h"

uint32_t offset;

const float g_ConeVertices[NUM_CONEPRIM_VERTICES][3] = 
{
	0.0000f,	0.0000f,	1.0000f,
	1.0000f,	0.0000f,	1.0000f,
	0.9595f,	0.2817f,	1.0000f,
	0.8413f,	0.5406f,	1.0000f,
	0.6549f,	0.7557f,	1.0000f,
	0.4154f,	0.9096f,	1.0000f,
	0.1423f,	0.9898f,	1.0000f,
	-0.1423f,	0.9898f,	1.0000f,
	-0.4154f,	0.9096f,	1.0000f,
	-0.6549f,	0.7557f,	1.0000f,
	-0.8413f,	0.5406f,	1.0000f,
	-0.9595f,	0.2817f,	1.0000f,
	-1.0000f,	0.0000f,	1.0000f,
	-0.9595f,	-0.2817f,	1.0000f,
	-0.8413f,	-0.5406f,	1.0000f,
	-0.6549f,	-0.7557f,	1.0000f,
	-0.4154f,	-0.9096f,	1.0000f,
	-0.1423f,	-0.9898f,	1.0000f,
	0.1423f,	-0.9898f,	1.0000f,
	0.4154f,	-0.9096f,	1.0000f,
	0.6549f,	-0.7558f,	1.0000f,
	0.8413f,	-0.5406f,	1.0000f,
	0.9595f,	-0.2817f,	1.0000f,
	0.0000f,	-0.0000f,	0.0000f
};

const UINT16 g_ConeIndices[ NUM_CONEPRIM_INDICES ] = 
{
    0 ,    1 ,    2 ,
    0 ,    2 ,    3 ,
    0 ,    3 ,    4 ,
    0 ,    4 ,    5 ,
    0 ,    5 ,    6 ,
    0 ,    6 ,    7 ,
    0 ,    7 ,    8 ,
    0 ,    8 ,    9 ,
    0 ,    9 ,   10 ,
    0 ,   10 ,   11 ,
    0 ,   11 ,   12 ,
    0 ,   12 ,   13 ,
    0 ,   13 ,   14 ,
    0 ,   14 ,   15 ,
    0 ,   15 ,   16 ,
    0 ,   16 ,   17 ,
    0 ,   17 ,   18 ,
    0 ,   18 ,   19 ,
    0 ,   19 ,   20 ,
    0 ,   20 ,   21 ,
    0 ,   21 ,   22 ,
    0 ,   22 ,    1 ,
    1 ,   23 ,    2 ,
    2 ,   23 ,    3 ,
    3 ,   23 ,    4 ,
    4 ,   23 ,    5 ,
    5 ,   23 ,    6 ,
    6 ,   23 ,    7 ,
    7 ,   23 ,    8 ,
    8 ,   23 ,    9 ,
    9 ,   23 ,   10 ,
   10 ,   23 ,   11 ,
   11 ,   23 ,   12 ,
   12 ,   23 ,   13 ,
   13 ,   23 ,   14 ,
   14 ,   23 ,   15 ,
   15 ,   23 ,   16 ,
   16 ,   23 ,   17 ,
   17 ,   23 ,   18 ,
   18 ,   23 ,   19 ,
   19 ,   23 ,   20 ,
   20 ,   23 ,   21 ,
   21 ,   23 ,   22 ,
   22 ,   23 ,    1
};

const UINT16 g_ConeLineIndices[ NUM_CONELINES_INDICES ] = 
{
#if 0
	23 ,    1 ,
	23 ,    2 ,
	23 ,    3 ,
	23 ,    4 ,
	23 ,    5 ,
	23 ,    6 ,
	23 ,    7 ,
	23 ,    8 ,
	23 ,    9 ,
	23 ,   10 ,
	23 ,   11 ,
	23 ,   12 ,
	23 ,   13 ,
	23 ,   14 ,
	23 ,   15 ,
	23 ,   16 ,
	23 ,   17 ,
	23 ,   18 ,
	23 ,   19 ,
	23 ,   20 ,
	23 ,   21 ,
	23 ,   22 ,
	1 ,   2  ,
	2 ,   3  ,
	3 ,   4  ,
	4 ,   5  ,
	5 ,   6  ,
	6 ,   7  ,
	7 ,   8  ,
	8 ,   9  ,
	9 ,   10 ,
	10,   11 ,
	11,   12 ,
	12,   13 ,
	13,   14 ,
	14,   15 ,
	15,   16 ,
	16,   17 ,
	17,   18 ,
	18,   19 ,
	19,   20 ,
	20,   21 ,
	21,   22 ,
	22,   1
#else
	23 ,    1 ,
	23 ,    3 ,
	23 ,    5 ,
	23 ,    7 ,
	23 ,    9 ,
	23 ,   11 ,
	23 ,   13 ,
	23 ,   15 ,
	23 ,   17 ,
	23 ,   19 ,
	23 ,   21 ,
	1 ,   2  ,
	2 ,   3  ,
	3 ,   4  ,
	4 ,   5  ,
	5 ,   6  ,
	6 ,   7  ,
	7 ,   8  ,
	8 ,   9  ,
	9 ,   10 ,
	10,   11 ,
	11,   12 ,
	12,   13 ,
	13,   14 ,
	14,   15 ,
	15,   16 ,
	16,   17 ,
	17,   18 ,
	18,   19 ,
	19,   20 ,
	20,   21 ,
	21,   22 ,
	22,   1
#endif
};

bool IsInsideCone( float radius, float padding, float zscale, const r3dPoint3D& p )
{
	padding = padding * 1.33f; // the exact value should be 1.29289321f ;]]]

	if( p.z > zscale + padding || p.z < -padding )
		return false;

	float effRadius = radius * p.Z / zscale + padding;

	float xy_sqr = p.X * p.X + p.Y * p.Y;

	if( xy_sqr < effRadius * effRadius )
		return true;
	else
	{
		// try padding from another perspective
		float r = sqrtf( xy_sqr );

		float z = zscale * r / radius;

		if( p.Z > z - padding )
			return true;
		else
			return false;
	}
}