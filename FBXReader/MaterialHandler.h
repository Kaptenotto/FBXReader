#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "BrfExporter.h"
#include "MaterialExport.h"


class MaterialHandler
{
public:
	MaterialHandler();
	~MaterialHandler();

	void GetMaterialData(FbxNode* pNode, MaterialExport* outputMat,SceneMap* sceneMap);
	void MapMaterials(FbxNode* pNode, SceneMap* sceneMap);

private:
	void ProcessData(FbxSurfaceMaterial* pMaterial, unsigned int matCount, MaterialExport* outputMat, SceneMap* sceneMap);

	//get RGB(A) values
	void GetDiffuse(FbxSurfaceMaterial* pMaterial, double *pTargetDiffuse);
	void GetSpecular(FbxSurfaceMaterial* pMaterial, double *pTargetSpecular);

	//GetMaps
	const char* GetTextureMap(FbxProperty diffMapProp);
	const char* GetSpecularMap(FbxProperty specMapProp);
	const char* GetNormalMap(FbxProperty normMapProp);
	const char* GetGlowMap(FbxProperty glowMapProp);

	//filepath names
	FbxString textureString;
	FbxString specularString;
	FbxString normalString;
	FbxString glowString;
};


#endif // !MATERIALHANDLER_H