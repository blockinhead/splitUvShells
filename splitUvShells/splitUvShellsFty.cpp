#include "splitUvShellsFty.h"
#include <maya/MFnMesh.h>
#include <maya/MIntArray.h>
#include <maya/MItMeshPolygon.h>


splitUvShellsFty::splitUvShellsFty(void)
{}

splitUvShellsFty::~splitUvShellsFty(void)
{}

void splitUvShellsFty::setMesh(MObject	oMesh)
{
	m_oMesh = oMesh;
}

MStatus splitUvShellsFty::doIt()
{
	MStatus status;

	MFnMesh fnMesh(m_oMesh);

	MIntArray uvShellIds;
	unsigned int nbUvShells = 0;
	fnMesh.getUvShellsIds(uvShellIds, nbUvShells);

	if (nbUvShells > 1)
	{
		//build array if int-arrays - separate uv-shell faces, skipping 0th uv-shell
		MIntArray *piaUvShellFaces = new MIntArray[nbUvShells - 1];
		int currentUVIndex = 0;
		int currentUVShell;
		MItMeshPolygon itMeshPolygon(m_oMesh);
		for(; !itMeshPolygon.isDone(); itMeshPolygon.next())
		{
			itMeshPolygon.getUVIndex(0, currentUVIndex);
			currentUVShell = uvShellIds[currentUVIndex];
			if (currentUVShell > 0)
				piaUvShellFaces[currentUVShell - 1].append(itMeshPolygon.index());
		}

		//extract faces of every separated uv-shell
		unsigned int i;
		MFloatVector fvZero;
		for (i = 0; i < nbUvShells - 1; i++)
			fnMesh.extractFaces(piaUvShellFaces[i], &fvZero);

		delete [] piaUvShellFaces;
	}

	return MS::kSuccess;
}


