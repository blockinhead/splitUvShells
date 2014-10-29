#pragma once
#include "polymodifierfty.h"
#include <maya/MObject.h>

class splitUvShellsFty : public polyModifierFty
{
public:
	splitUvShellsFty(void);
	~splitUvShellsFty(void);
	
	void setMesh(MObject oMesh);
	MStatus doIt();

private:
	MObject m_oMesh;
};

