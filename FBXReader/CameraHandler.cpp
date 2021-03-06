#include "CameraHandler.h"


CameraHandler::CameraHandler()
{

}

CameraHandler::~CameraHandler()
{

}



void CameraHandler::GetCameraData(FbxNode* pNode, CameraExporter* outCamera)
{
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetCameraData(pNode->GetChild(j), outCamera);

	if (pNode->GetCamera())
	{
		std::cout << pNode->GetName() << std::endl;
		ProcessCameraData(pNode->GetCamera(), outCamera);
	}
}

void CameraHandler::ProcessCameraData(FbxCamera* pCamera, CameraExporter* outCamera)
{
	BRFImporter::CameraHeader cameras;

	memcpy(cameras.camName, pCamera->GetName(), sizeof(char) * 256);

	GetCamPos(pCamera, cameras.position);
	GetCamRotation(pCamera->GetNode(), cameras.rotation);

	outCamera->cameras->push_back(cameras);
}

void CameraHandler::GetCamPos(FbxCamera* pCamera, double* pTargetPos)
{
	FbxDouble3 tmp = pCamera->Position.Get();

	pTargetPos[0] = (double)tmp[0];
	pTargetPos[1] = (double)tmp[1];
	pTargetPos[2] = (double)tmp[2];
}

void CameraHandler::GetCamRotation(FbxNode* pCamNode, double* pTargetRotation)
{
	FbxDouble3 tmp = pCamNode->LclRotation;

	pTargetRotation[0] = (double)tmp[0];
	pTargetRotation[1] = (double)tmp[1];
	pTargetRotation[2] = (double)tmp[2];
}