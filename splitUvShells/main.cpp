#include "splitUvShellsCmd.h"
#include "splitUvShellsNode.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin fnPlugin(obj, "ilya radovilsky", "1.0", "any");
	
	status = fnPlugin.registerCommand("splitUvShells", splitUvShellsCmd::creator);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = fnPlugin.registerNode("splitUvShellsNode", splitUvShellsNode::id, splitUvShellsNode::creator, splitUvShellsNode::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin fnPlugin(obj);

	status = fnPlugin.deregisterCommand("splitUvShells");
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = fnPlugin.deregisterNode(splitUvShellsNode::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return status;
}