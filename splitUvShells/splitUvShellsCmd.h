#pragma once
#include "polymodifiercmd.h"
#include "splitUvShellsFty.h"

class splitUvShellsCmd : public polyModifierCmd
{
public:
	splitUvShellsCmd(void);
	virtual ~splitUvShellsCmd(void);

	static void* creator();
	bool isUndoable() const;
	
	MStatus doIt( const MArgList& args );
	MStatus redoIt();
	MStatus undoIt();

	MStatus directModifier( MObject mesh );

private:
	splitUvShellsFty m_splitUvShellsFty;
};

