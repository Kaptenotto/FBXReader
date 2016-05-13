#include "MorphAnimation.h"





bool MorphAnimation::isATargetMesh(const char * name)
{


	char compare[12];
	char target[12];
	target[0] = 'A';
	target[1] = 'N';
	target[2] = 'I';
	target[3] = 'M';
	target[4] = '_';
	target[5] = 'T';
	target[6] = 'A';
	target[7] = 'R';
	target[8] = 'G';
	target[9] = 'E';
	target[10] = 'T';
	target[11] = '\0';

	for (int i = 0; i < 11; i++)
	{
		compare[i] = name[i];
	}
	compare[11] = '\0';
	if (strcmp(compare, target) == 0)
	{
		std::cout << "TARGET MESH FOUND" << std::endl;
		return true;
	}
	else
		return false;


	return true;
}

void MorphAnimation::ExtractSourceMesh(FbxNode * pNode)
{
	/* Here we process all the data for the mesh,

	position
	normals
	UV
	tangent
	bitangent
	*/


	MeshExport* targetMesh =  new MeshExport(false);





	FbxMesh* pMesh = pNode->GetMesh();
	unsigned int vertCount = pMesh->GetControlPointsCount();
	

	//trying to find the material
	//FbxNode * pNode = (FbxNode*)pMesh->GetDstObject();


	unsigned int polyCount = pMesh->GetPolygonCount();


	std::vector<int> polyVertices;
	std::vector<FbxVector4> polyNormals;
	for (int i = 0; i < polyCount; i++)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); j++)
		{
			FbxVector4 tempNormal;
			polyVertices.push_back(pMesh->GetPolygonVertex(i, j));
			pMesh->GetPolygonVertexNormal(i, j, tempNormal);
			polyNormals.push_back(tempNormal);
		}
	}
	
	

	std::vector<int> uvIndex;
	for (int i = 0; i < polyCount; ++i)
	{
		std::vector<FbxVector2> tempValues;
		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		{
			int UVIndex = pMesh->GetTextureUVIndex(i, j);
			uvIndex.push_back(UVIndex);
	
		}
	
	}
	


	
		//outPutMesh->verticesNoSkeleton->resize(34);
		//unsigned int index = 0;
		for (int i = 0; i < polyVertices.size(); ++i)
		{
			
			//VertexHeaderNoSkeleton tempVertex;
			VertexHeaderNoSkeleton tempVertex;

			FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
			pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

			GetVertPositions(pMesh, polyVertices.at(i), tempVertex.pos);
			//GetVertNormals(pMesh->GetElementNormal(), polyVertices.at(i), tempVertex.normal);
			GetPolygonNormals(tempVertex.normal, &polyNormals.at(i));
			GetVertBiNormals(pMesh->GetElementBinormal(), polyVertices.at(i), tempVertex.biTangent);
			GetVertTangents(pMesh->GetElementTangent(), polyVertices.at(i), tempVertex.tangent);
			GetVertTextureUV(pMesh->GetElementUV(), uvIndex.at(i), tempVertex.uv);
			
			targetMesh->verticesNoSkeleton->push_back(tempVertex);
		}
	
	

	std::cout << "Source mesh :" << pMesh->GetName() << std::endl;
	std::cout << "Total amount of vertices on mesh : " << targetMesh->verticesNoSkeleton->size() << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t t = 0; t < 3; t++)
		{
			std::cout << targetMesh->verticesNoSkeleton->at(i).pos[t] << " , ";

		}
		std::cout << "\n";
	}
	std::cout << "\n";


	sourceMesh = targetMesh;


}

BlendMesh* MorphAnimation::ExtractTargetMesh(FbxNode * pNode)
{

	/* Here we process all the data for the mesh,

	position
	normals
	UV
	tangent
	bitangent
	*/


	BlendMesh* targetMesh = new BlendMesh();





	FbxMesh* pMesh = pNode->GetMesh();
	unsigned int vertCount = pMesh->GetControlPointsCount();


	//trying to find the material
	//FbxNode * pNode = (FbxNode*)pMesh->GetDstObject();


	unsigned int polyCount = pMesh->GetPolygonCount();


	std::vector<int> polyVertices;
	std::vector<FbxVector4> polyNormals;
	for (int i = 0; i < polyCount; i++)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); j++)
		{
			FbxVector4 tempNormal;
			polyVertices.push_back(pMesh->GetPolygonVertex(i, j));
			pMesh->GetPolygonVertexNormal(i, j, tempNormal);
			polyNormals.push_back(tempNormal);
		}
	}



	std::vector<int> uvIndex;
	for (int i = 0; i < polyCount; ++i)
	{
		std::vector<FbxVector2> tempValues;
		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		{
			int UVIndex = pMesh->GetTextureUVIndex(i, j);
			uvIndex.push_back(UVIndex);

		}

	}




	//outPutMesh->verticesNoSkeleton->resize(34);
	//unsigned int index = 0;
	for (int i = 0; i < polyVertices.size(); ++i)
	{

		//VertexHeaderNoSkeleton tempVertex;
		BlendVertexHeader tempVertex;

		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		GetVertPositions(pMesh, polyVertices.at(i), tempVertex.pos);
		//GetVertNormals(pMesh->GetElementNormal(), polyVertices.at(i), tempVertex.normal);
		GetPolygonNormals(tempVertex.normal, &polyNormals.at(i));
		GetVertBiNormals(pMesh->GetElementBinormal(), polyVertices.at(i), tempVertex.biTangent);
		GetVertTangents(pMesh->GetElementTangent(), polyVertices.at(i), tempVertex.tangent);
	

		targetMesh->vertices.push_back(tempVertex);
	}



	std::cout << "Source mesh :" << pMesh->GetName() << std::endl;
	std::cout << "Total amount of vertices on mesh : " << targetMesh->vertices.size() << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t t = 0; t < 3; t++)
		{
			std::cout << targetMesh->vertices.at(i).pos[t] << " , ";

		}
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "Total amount of vertices on mesh : " << targetMesh->vertices.size() << std::endl;
	blendMeshes.push_back(targetMesh);
	return targetMesh;
}

void MorphAnimation::ExtractAllMeshesInAnimation(FbxNode * pNode)
{
	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
			ExtractAllMeshesInAnimation(pNode->GetChild(i)); //recursively go down the hierarchy and search for blendshape animations
	}
	if (isATargetMesh(pNode->GetName()))
	{
		std::cout << pNode->GetName() << std::endl;
		
		const char* name = pNode->GetName();
		int i = name[12] - '0';
		blendShapeMap[i] = ExtractTargetMesh(pNode); //get the number in the name and map it.
	}




#pragma region
		
		if (pNode->GetGeometry())			 //if we find source mesh
		{
			FbxGeometry* pGeo = pNode->GetGeometry();
			if (pGeo->GetDeformerCount(FbxDeformer::eBlendShape) > 0)	 //if there is any blendshapes
			{
				ExtractSourceMesh(pNode);
				int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);	 //get amount of targets
				int morphChannelCount;
				int targetShapeCount;
				for (unsigned int i = 0; i < morphAnimCount; i++) //for each blendshape
				{

					FbxBlendShape* morphAnim;
					morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape); //Get the blend shape #i

					morphChannelCount = morphAnim->GetBlendShapeChannelCount(); //Get how many channels the blend shape #i has
					std::cout << "ChannelCount: " << morphChannelCount << "\n\n";

						BlendAnimation* tempAnimation = new BlendAnimation();
					for (unsigned int j = 0; j < morphChannelCount; j++) //for every channel
					{
						std::cout << "channel nr: " << j << "\n";

						FbxBlendShapeChannel* morphChannel;
						morphChannel = morphAnim->GetBlendShapeChannel(j);
						//morphChannel->GetBlendShapeDeformer();

						std::cout << "ChannelName: " << morphChannel->GetNameWithoutNameSpacePrefix() << "\n\n";   //usually blendshapeName.meshName

						targetShapeCount = morphChannel->GetTargetShapeCount();
						std::cout << "Target Shape Count: " << targetShapeCount << "\n\n";
						for (unsigned int k = 0; k < targetShapeCount; k++) //for every shape in this channel
						{
							FbxShape* shape;
							shape = morphChannel->GetTargetShape(k);
							std::cout << shape->GetName() << std::endl;

							
							
							//processKeyFrames(pNode, output, morphChannel);
							//shape->GetElementPolygonGroupCount()

							FbxScene * scene = pNode->GetScene();

							//Getting the number of animation stacks for this mesh
							//seeing as you can have different ones such as (running, walking...)
							int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();

							for (int animIndex = 0; animIndex < numAnimations; animIndex++)
							{

								//getting the current stack and evaluator
								FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
								FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();
								std::cout << animStack->GetName() << "\n";
								//so far so good

								//put control here to se if its the same animation layer
								//int layerTest = getLayerID((FbxString)animStack->GetName());
								int numLayers = animStack->GetMemberCount();

								for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
								{
									FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);

									FbxAnimCurve * deformCurve = morphChannel->DeformPercent.GetCurve(animLayer);
									if (deformCurve != nullptr)
									{
										int numKeys = deformCurve->KeyGetCount();
										for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
										{
											fbxsdk::FbxAnimCurveKey key = deformCurve->KeyGet(keyIndex);

											const char* name = shape->GetName();											 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame
											int in = name[12] - '0';															 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame

											

											

											FbxTime frameTime = deformCurve->KeyGetTime(keyIndex);

											//framerate �r 41 med mode eFrames1000 :S:S:S:S:S
											unsigned int frame = frameTime.GetFieldCount(FbxTime::EMode::eFrames1000) / 41 / 2;
											std::cout <<"frame :" << frame << "\n"; //ful l�sning, f�r att hitta r�tt keyframe. inte helt exakt. men n�ra!
											

											double deform = morphChannel->DeformPercent.EvaluateValue(frameTime);
											std::cout << "\n influece: " << deform << "\n";
											if (frame > tempAnimation->animationTime)
												tempAnimation->animationTime = frame;
											
											bool	frameExists = false;
											int		frameIndex = 0;
											for (size_t i = 0; i < tempAnimation->frames.size(); i++)
											{
												if (tempAnimation->frames.at(i).frameTime == frame)
												{
													frameExists = true;
													frameIndex  = (int)i;
													break;
												}

											}
											if (frameExists)
											{
												tempAnimation->frames.at(frameIndex).meshIDs.push_back(in);
												tempAnimation->frames.at(frameIndex).influence.push_back(float(deform));
											}
											else
											{

										    tempAnimation->frames.push_back(BlendFrame());									 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame
											tempAnimation->frames.at(tempAnimation->frames.size() - 1).frameTime = frame; //STORING THE FRAME NUMBER
											tempAnimation->frames.at(tempAnimation->frames.size()-1).meshIDs.push_back(in);	 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame
											tempAnimation->frames.at(tempAnimation->frames.size() - 1).influence.push_back(float(deform));																   // STORING THE INFLUENCE AT THIS FRAME
											}
										}
									}
								}
							}
						}
					}
								animations.push_back(tempAnimation);

				}
				//ExtractTargetMesh(pNode->GetChild(i));		 //extract it
			}
		}
#pragma endregion

}

void MorphAnimation::GetMorphAnimation(FbxNode * pNode)
{
	
		ExtractAllMeshesInAnimation(pNode);

	


	//FbxGeometry* pGeo = pNode->GetGeometry();								 // get Source
	//int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);	 //get amount of targets
	//int morphChannelCount;
	//int targetShapeCount;
	//for (unsigned int i = 0; i < morphAnimCount; i++) //for each target
	//{
	//	FbxBlendShape* morphAnim;
	//	morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape); //Get the blend shape #i

	//	morphChannelCount = morphAnim->GetBlendShapeChannelCount(); //Get how many channels the blend shape #i has
	//	std::cout << "ChannelCount: " << morphChannelCount << "\n\n";
	//
	//	for (unsigned int j = 0; j < morphChannelCount; j++) //for every channel
	//	{
	//		std::cout << "channel nr: " << j << "\n";

	//		FbxBlendShapeChannel* morphChannel;
	//		morphChannel = morphAnim->GetBlendShapeChannel(j);
	//		morphChannel->GetBlendShapeDeformer();
	//		std::cout << "ChannelName: " << morphChannel->GetName() << "\n\n";   //usually blendshapeName.meshName

	//		targetShapeCount = morphChannel->GetTargetShapeCount();
	//		std::cout << "Target Shape Count: " << targetShapeCount << "\n\n";
	//		for (unsigned int k = 0; k < targetShapeCount; k++) //for every shape in this channel
	//		{
	//			FbxShape* shape;svb
	//		
	//			shape = morphChannel->GetTargetShape(k);
	//		}
	//	
	//	}



	//}

}


MorphAnimation::MorphAnimation()
{
}


MorphAnimation::~MorphAnimation()
{
	if (sourceMesh)
		delete sourceMesh;

	for (size_t i = 0; i < animations.size(); i++)
	{
		delete animations.at(i);
	}
	for (size_t i = 0; i < blendMeshes.size(); i++)
	{
		delete blendMeshes.at(i);

	}
}



void MorphAnimation::GetVertPositions(FbxMesh * pMesh, int index, double * targetPos)
{
	FbxVector4 position = pMesh->GetControlPointAt(index);

	targetPos[0] = (double)position[0];
	targetPos[1] = (double)position[1];
	targetPos[2] = (double)position[2];
}

void MorphAnimation::GetVertNormals(fbxsdk::FbxGeometryElementNormal * pNElement, int index, double * targetNormal)
{
	FbxVector4 normal = pNElement->GetDirectArray().GetAt(index);

	targetNormal[0] = normal[0];
	targetNormal[1] = normal[1];
	targetNormal[2] = normal[2];
}

void MorphAnimation::GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal * pBNElement, int index, double * targetBiNormal)
{
	FbxVector4 biNormal = pBNElement->GetDirectArray().GetAt(index);
	targetBiNormal[0] = biNormal[0];
	targetBiNormal[1] = biNormal[1];
}

void MorphAnimation::GetVertTangents(fbxsdk::FbxGeometryElementTangent * pTElement, int index, double * targetTangent)
{
	FbxVector4 tangent = pTElement->GetDirectArray().GetAt(index);
	targetTangent[0] = tangent[0];
	targetTangent[1] = tangent[1];
}

void MorphAnimation::GetVertTextureUV(fbxsdk::FbxGeometryElementUV* uvElement, int index, double * targetUV)
{
	FbxVector2 uvs = uvElement->GetDirectArray().GetAt(index);
	targetUV[0] = uvs[0];
	targetUV[1] = 1 - uvs[1];
}

void MorphAnimation::GetPolygonNormals(double * targetNormal, FbxVector4 * sourceNormals)
{
	targetNormal[0] = sourceNormals->mData[0];
	targetNormal[1] = sourceNormals->mData[1];
	targetNormal[2] = sourceNormals->mData[2];
}