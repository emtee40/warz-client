#include "r3dPCH.h"
#include "r3d.h"

#include "r3dChamferBox.h"

const float g_ChamferBoxVertices[NUM_CHAMFERBOX_VERTICES][3] = 
{
	-0.250*2,		+0.500*2,		-0.250*2,
	-0.250*2,		+0.500*2,		+0.250*2,
	+0.250*2,		+0.500*2,		+0.250*2,
	+0.250*2,		+0.500*2,		-0.250*2,
	-0.250*2,		+0.250*2,		-0.500*2,
	-0.500*2,		+0.250*2,		-0.250*2,
	-0.500*2,		+0.250*2,		+0.250*2,
	-0.250*2,		+0.250*2,		+0.500*2,
	+0.250*2,		+0.250*2,		+0.500*2,
	+0.500*2,		+0.250*2,		+0.250*2,
	+0.500*2,		+0.250*2,		-0.250*2,
	+0.250*2,		+0.250*2,		-0.500*2,
	-0.250*2,		-0.250*2,		-0.500*2,
	-0.500*2,		-0.250*2,		-0.250*2,
	-0.500*2,		-0.250*2,		+0.250*2,
	-0.250*2,		-0.250*2,		+0.500*2,
	+0.250*2,		-0.250*2,		+0.500*2,
	+0.500*2,		-0.250*2,		+0.250*2,
	+0.500*2,		-0.250*2,		-0.250*2,
	+0.250*2,		-0.250*2,		-0.500*2,
	-0.250*2,		-0.500*2,		-0.250*2,
	-0.250*2,		-0.500*2,		+0.250*2,
	+0.250*2,		-0.500*2,		+0.250*2,
	+0.250*2,		-0.500*2,		-0.250*2
};

const UINT16 g_ChamferBoxIndices[NUM_CHAMFERBOX_INDICES] = 
{
	 1 - 1,		 2 - 1,		 3 - 1,
	 1 - 1,		 3 - 1,		 4 - 1,
	 1 - 1,		 5 - 1,		 6 - 1,
	 1 - 1,		 6 - 1,		 7 - 1,
	 1 - 1,		 7 - 1,		 2 - 1,
	 2 - 1,		 7 - 1,		 8 - 1,
	 2 - 1,		 8 - 1,		 9 - 1,
	 2 - 1,		 9 - 1,		 3 - 1,
	 3 - 1,		 9 - 1,		10 - 1,
	 3 - 1,		10 - 1,		11 - 1,
	 3 - 1,		11 - 1,		 4 - 1,
	 4 - 1,		11 - 1,		12 - 1,
	 4 - 1,		12 - 1,		 5 - 1,
	 4 - 1,		 5 - 1,		 1 - 1,
	 5 - 1,		13 - 1,		14 - 1,
	 5 - 1,		14 - 1,		 6 - 1,
	 6 - 1,		14 - 1,		15 - 1,
	 6 - 1,		15 - 1,		 7 - 1,
	 7 - 1,		15 - 1,		16 - 1,
	 7 - 1,		16 - 1,		 8 - 1,
	 8 - 1,		16 - 1,		17 - 1,
	 8 - 1,		17 - 1,		 9 - 1,
	 9 - 1,		17 - 1,		18 - 1,
	 9 - 1,		18 - 1,		10 - 1,
	10 - 1,		18 - 1,		19 - 1,
	10 - 1,		19 - 1,		11 - 1,
	11 - 1,		19 - 1,		20 - 1,
	11 - 1,		20 - 1,		12 - 1,
	12 - 1,		20 - 1,		13 - 1,
	12 - 1,		13 - 1,		 5 - 1,
	13 - 1,		21 - 1,		14 - 1,
	14 - 1,		21 - 1,		22 - 1,
	14 - 1,		22 - 1,		15 - 1,
	15 - 1,		22 - 1,		16 - 1,
	16 - 1,		22 - 1,		23 - 1,
	16 - 1,		23 - 1,		17 - 1,
	17 - 1,		23 - 1,		18 - 1,
	18 - 1,		23 - 1,		24 - 1,
	18 - 1,		24 - 1,		19 - 1,
	19 - 1,		24 - 1,		20 - 1,
	20 - 1,		24 - 1,		21 - 1,
	20 - 1,		21 - 1,		13 - 1,
	24 - 1,		23 - 1,		22 - 1,
	24 - 1,		22 - 1,		21 - 1
};