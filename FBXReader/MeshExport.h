#pragma once
#include <vector>
#include "BRFImporterStructs.h"
#include "AttributesExport.h"
#include <fstream>
#include <iostream>
using namespace BRFImporter;

#pragma region Explaination
/*
This class handles a single mesh

The functions are used to add the information

in the end when we write to the file. we calculate the
final amount of vertices and indices and add that to the meshInfo struct

*/
#pragma endregion

class MeshExport
{


public:
	MeshHeader meshInfo;
	MainHeader mainInfo;
	std::vector<IndexHeader>* indices						=nullptr	;
	std::vector<VertexHeader>* vertices						=nullptr	 ;
	std::vector<VertexHeaderNoSkeleton>* verticesNoSkeleton =nullptr;
	std::vector<std::vector<WeigthsHeader>> weights; // the 4 count will be controlled in the "AddWeight" function
	OOBBHeader boundingBox;

	AttributesExport* meshAttributes = nullptr;

public:
	MeshExport();
	MeshExport(bool hasSkeleton);
	~MeshExport();

	void WriteToBinaryFile(std::ofstream* outfile);

	void AddVertex(VertexHeader input);
	void Addindex(IndexHeader input);
	void AddBoundingBox(OOBBHeader input);
	void AddWeight(WeigthsHeader input);
	void AddMeshInfo(MeshHeader info);
	AttributesExport* GetAttributeHandler();
};

