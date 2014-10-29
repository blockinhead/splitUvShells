#include "splitUvShellsCmd.h"
#include "splitUvShellsNode.h"
#include <maya/MSelectionList.h>
#include <maya/MGlobal.h>


splitUvShellsCmd::splitUvShellsCmd(void)
{}


splitUvShellsCmd::~splitUvShellsCmd(void)
{}

void* splitUvShellsCmd::creator()
{
	return new splitUvShellsCmd();
}

bool splitUvShellsCmd::isUndoable() const
{
	return true;
}

MStatus splitUvShellsCmd::directModifier( MObject mesh )
{
	MStatus status;

	m_splitUvShellsFty.setMesh(mesh);
	status = m_splitUvShellsFty.doIt();

	return status;
}

MStatus splitUvShellsCmd::doIt( const MArgList& args )
{
	MStatus status;
	MSelectionList selectionList;
	MGlobal::getActiveSelectionList(selectionList);
	if(selectionList.length() < 1)
	{
		setResult("please select a mesh");
		return MS::kFailure;
	}

	MDagPath dagPath;
	selectionList.getDagPath(0, dagPath);
	dagPath.extendToShape();
	if(dagPath.apiType() != MFn::kMesh)
	{
		setResult("please select a mesh");
		return MS::kFailure;
	}

	setMeshNode(dagPath);
	setModifierNodeType(splitUvShellsNode::id);
	status = doModifyPoly();
	return status;
}

MStatus splitUvShellsCmd::redoIt()
{
	MStatus status;
	status = redoModifyPoly();
	return status;
}

MStatus splitUvShellsCmd::undoIt()
{
	MStatus status;
	status = undoModifyPoly();
	return status;
}