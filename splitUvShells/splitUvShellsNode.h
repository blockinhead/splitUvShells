#pragma once
#include "polymodifiernode.h"
#include "splitUvShellsFty.h"

class splitUvShellsNode :
	public polyModifierNode
{
public:
	splitUvShellsNode(void);
	virtual ~splitUvShellsNode(void);

	virtual MStatus compute( const MPlug& plug, MDataBlock& dataBlock );

	static void* creator();
	static MStatus initialize();
	static MTypeId id;

	splitUvShellsFty m_splitUvShellsFty;	
};

