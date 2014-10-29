#include "splitUvShellsNode.h"
#include <maya/MFnTypedAttribute.h>

MTypeId splitUvShellsNode::id(0x00000111);

splitUvShellsNode::splitUvShellsNode(void)
{}


splitUvShellsNode::~splitUvShellsNode(void)
{}

void* splitUvShellsNode::creator()
{
	return new splitUvShellsNode();
}

MStatus splitUvShellsNode::initialize()
{
	MStatus status;
	MFnTypedAttribute fnTypedAttribute;

	inMesh = fnTypedAttribute.create("inMesh", "im", MFnData::kMesh);
	fnTypedAttribute.setStorable(true);

	outMesh = fnTypedAttribute.create("outMesh", "om", MFnData::kMesh);
	fnTypedAttribute.setStorable(false);
	fnTypedAttribute.setWritable(false);

	status = addAttribute(inMesh);
	status = addAttribute(outMesh);
	status = attributeAffects(inMesh, outMesh);

	return status;
}

MStatus splitUvShellsNode::compute( const MPlug& plug, MDataBlock& dataBlock )
{
	MStatus status;

	if(plug != outMesh)
	{
		return MS::kUnknownParameter;
	}

	MDataHandle dhState = dataBlock.outputValue(state);
	MDataHandle dhInMesh = dataBlock.inputValue(inMesh);
	MDataHandle dhOutMesh = dataBlock.outputValue(outMesh);
	dhOutMesh.set(dhInMesh.asMesh());

	//state of node is not HasNoEffect/PassThrough
	if(dhState.asShort() != 1)
	{
		MObject oMesh = dhOutMesh.asMesh();
		m_splitUvShellsFty.setMesh(oMesh);
		m_splitUvShellsFty.doIt();
	}

	return MS::kSuccess;
}
