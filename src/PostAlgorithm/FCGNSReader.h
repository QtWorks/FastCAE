#ifndef _FCGNSREADER_H__
#define _FCGNSREADER_H__

#include <vtkMultiBlockDataSetAlgorithm.h>

class  FCGNSReader : public vtkMultiBlockDataSetAlgorithm
{
public:
    static FCGNSReader* New();
    vtkTypeMacro(FCGNSReader, vtkMultiBlockDataSetAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    vtkSetStringMacro(FileName);
    vtkGetStringMacro(FileName);

    

    int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
    int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);

    bool canReadFile();

    void setReadBC(bool read);

    bool isReadBC();

private:
    FCGNSReader();
    ~FCGNSReader();

    void readZone(int fileIndex, int baseIndex, int zoneIndex, vtkMultiBlockDataSet* output);

protected:
    char* FileName;
    bool _readBC{true};
};

#endif