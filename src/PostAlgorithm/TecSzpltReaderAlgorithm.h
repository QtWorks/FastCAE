#ifndef READDATATECSZPLT_H
#define READDATATECSZPLT_H

#include "PostAlgorithmAPI.h"
#include "PostRenderData/Macros.hxx"

#include <QString>
#include <QStringList>
#include <QHash>

#include <vtkUnstructuredGridAlgorithm.h>

//#include "ReadData_Base.h"


class POSTALGORITHMAPI TecSzpltReaderAlgorithm : public vtkUnstructuredGridAlgorithm
{
public:
	static TecSzpltReaderAlgorithm* New();
	vtkTypeMacro(TecSzpltReaderAlgorithm, vtkUnstructuredGridAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent) override;

	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

	int getNumberOfBlocks();

	void setVisible(int blockIndex, bool vis);

	QStringList getBlockNames();

	//QStringList getBlockBCTypes();

	int FillOutputPortInformation(int nPort, vtkInformation* info);

	
	void getPointArray(vtkDataSet* dataset);
	
	void getCellArray(vtkDataSet* dataset);

	void getBlocks(vtkDataObject* block, const char* cuttentName = "");
private:
	
	TecSzpltReaderAlgorithm(const TecSzpltReaderAlgorithm&);
	void operator=(const TecSzpltReaderAlgorithm&);	
	

	TecSzpltReaderAlgorithm();
	~TecSzpltReaderAlgorithm();

	int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
	int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);


protected:
	char* FileName=nullptr;


private:
	

	QStringList _blockNames{};
	QList<bool> _visibleStates{};

	QList<vtkDataSet*> _blockList;

	QHash<QString, int*> _pointDataArray{};
	
	QHash<QString, int*> _cellDataArray{};
	

};


#endif