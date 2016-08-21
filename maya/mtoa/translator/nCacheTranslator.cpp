#include "nCacheTranslator.h"
#include <extension/Extension.h>
#include <maya/MFnStringArrayData.h>
#include <maya/MFnStringData.h>
#include <maya/MGlobal.h>

AtNode* nCacheTranslator::Init(CArnoldSession* session,
							   MDagPath& dagPath,
							   MString outputAttr)
{
	fprintf(stderr,"nCacheTranslator::Init() XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX method called\n");
	MStatus status;
	CShapeTranslator::Init(session, dagPath, outputAttr);
    MFnDagNode fnGPUCache(dagPath);
    MPlug cachePathPlug = fnGPUCache.findPlug("cachePath");
    MObject cachePathStringObject;
    status = cachePathPlug.getValue(cachePathStringObject);
    MFnStringData cachePathStringData(cachePathStringObject);
    MString cachePathString = cachePathStringData.string(&status);

    MGlobal::displayInfo("cachePathString START");
    MGlobal::displayInfo(cachePathString);
    MGlobal::displayInfo("cachePathString END");

	return m_atNode;
}

bool nCacheTranslator::RequiresMotionData()
{
	return false;
}

void* nCacheTranslator::creator()
{
	return new nCacheTranslator();
}

void nCacheTranslator::NodeInitializer(CAbTranslator context)
{
	fprintf(stderr,"nCacheTranslator::NodeInitializer() called\n");
	
	CExtensionAttrHelper helper("cacheFile","points");
	CShapeTranslator::MakeCommonAttributes(helper);
}

AtNode* nCacheTranslator::CreateArnoldNodes()
{
	fprintf(stderr,"nCacheTranslator::CreateArnoldNodes() XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX method called\n");
	return AddArnoldNode("points");
}

void nCacheTranslator::Export(AtNode* atNode)
{
	fprintf(stderr,"nCacheTranslator::Export() XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX method called\n");
}

extern "C"
{

	/* DLLEXPORT */ void initializeExtension(CExtension& extension)
	{
		MStatus status;
		extension.Requires("cacheFile");
		status = extension.RegisterTranslator( "cacheFile", // name of Maya node which this translator is associated with
											   "nCacheTranslator",
											   nCacheTranslator::creator,
											   nCacheTranslator::NodeInitializer);
	}

	/* DLLEXPORT */ void deinitializeExtension(CExtension& extension)
	{
	}

}

// == Emacs ================
// -------------------------
// Local variables:
// tab-width: 4
// indent-tabs-mode: t
// c-basic-offset: 4
// end:
//
// == vi ===================
// -------------------------
// Format block
// ex:ts=4:sw=4:expandtab
// -------------------------