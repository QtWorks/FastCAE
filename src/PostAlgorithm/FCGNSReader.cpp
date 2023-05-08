#include "FCGNSReader.h"
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkSetGet.h>
#include <QFile>
#include <cgnslib.h>
#include <cgns_io.h>
#include "FCGNSUnStructureZoneReader.h"
#include "FCGNSStructureZoneReader.h"

FCGNSReader* FCGNSReader::New()
{
    auto reader = new FCGNSReader;
    reader->InitializeObjectBase();
    return reader;
}

void FCGNSReader::PrintSelf(ostream& os, vtkIndent indent)
{
    Q_UNUSED(os)
    Q_UNUSED(indent)
}

FCGNSReader::FCGNSReader()
{
    this->SetNumberOfInputPorts(0);
    this->SetNumberOfOutputPorts(1);
    this->FileName = nullptr;
}

FCGNSReader::~FCGNSReader()
{
}

void FCGNSReader::readZone(int fileIndex, int baseIndex, int zoneIndex, vtkMultiBlockDataSet* output)
{
    CGNS_ENUMT(ZoneType_t) zonetype;
    if (CG_OK != cg_zone_type(fileIndex, baseIndex, zoneIndex, &zonetype))
        return ;

    if (zonetype == CGNS_ENUMV(Structured))
    {
        FCGNSStructeGridReader r(output);
        r.setInfo(fileIndex, baseIndex, zoneIndex);
        r.setReadBC(_readBC);
        r.read();
    }
    else if (zonetype == CGNS_ENUMV(Unstructured))
    {
        FCGNSUnStructeGridReader r(output);
        r.setInfo(fileIndex, baseIndex, zoneIndex);
        r.read();
    }
}

int FCGNSReader::ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
    if (request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
    {
        return this->RequestInformation(request, inputVector,
            outputVector);
    }
    if (request->Has(
        vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT()))
    {
        return this->RequestUpdateExtent(request, inputVector,
            outputVector);
    }
    if (request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
    {
        return this->RequestData(request, inputVector, outputVector);
    }
    return this->Superclass::ProcessRequest(request, inputVector,
        outputVector);
}

int FCGNSReader::RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector* outputVector)
{
    auto output = vtkMultiBlockDataSet::GetData(outputVector);

    bool ok = canReadFile();
    if (!ok) return 0;

    int currentFileIndex = 0;
    if (cg_open(FileName, CG_MODE_READ, &currentFileIndex))
    {
        return 0;
    }
    

    int nBase = 0;
    if (cg_nbases(currentFileIndex, &nBase))
    {
        return 0;
    }

    for (int ibase = 1; ibase <= nBase; ++ibase)
    {
        int zone_node_number = 0;
        if (cg_nzones(currentFileIndex, ibase, &zone_node_number))
        {
            return false;
        }
        for (int izone = 1; izone <= zone_node_number; ++izone)
        {
            readZone(currentFileIndex, ibase, izone, output);
        }

    }
    cgio_close_file(currentFileIndex);
    return 1;
}

bool FCGNSReader::canReadFile()
{ 
    int cgioFile;
    int ierr = 1;
    double rootNodeId;
    double childId;
    float FileVersion = 0.0;
    int intFileVersion = 0;
    char dataType[CGIO_MAX_DATATYPE_LENGTH + 1];
    char errmsg[CGIO_MAX_ERROR_LENGTH + 1];
    int ndim = 0;
    cgsize_t dimVals[12];
    int fileType = CG_FILE_NONE;

    if (cgio_open_file(FileName, CG_MODE_READ, CG_FILE_NONE, &cgioFile) != CG_OK)
    {
        cgio_error_message(errmsg);
        vtkErrorMacro(<< "vtkCGNSReader::CanReadFile : " << errmsg);
        return 0;
    }

    cgio_get_root_id(cgioFile, &rootNodeId);
    cgio_get_file_type(cgioFile, &fileType);

    if (cgio_get_node_id(cgioFile, rootNodeId, "CGNSLibraryVersion", &childId))
    {
        cgio_error_message(errmsg);
        vtkErrorMacro(<< "vtkCGNSReader::CanReadFile : " << errmsg);
        ierr = 0;
        goto CanReadError;
    }

    if (cgio_get_data_type(cgioFile, childId, dataType))
    {
        vtkErrorMacro(<< "CGNS Version data type");
        ierr = 0;
        goto CanReadError;
    }

    if (cgio_get_dimensions(cgioFile, childId, &ndim, dimVals))
    {
        vtkErrorMacro(<< "cgio_get_dimensions");
        ierr = 0;
        goto CanReadError;
    }

    // check data type
    if (strcmp(dataType, "R4") != 0)
    {
        vtkErrorMacro(<< "Unexpected data type for CGNS-Library-Version=" << dataType);
        ierr = 0;
        goto CanReadError;
    }

    // check data dim
    if ((ndim != 1) || (dimVals[0] != 1))
    {
        vtkDebugMacro(<< "Wrong data dimension for CGNS-Library-Version");
        ierr = 0;
        goto CanReadError;
    }

    // read data
    if (cgio_read_all_data_type(cgioFile, childId, "R4", &FileVersion))
    {
        vtkErrorMacro(<< "read CGNS version number");
        ierr = 0;
        goto CanReadError;
    }

    // Check that the library version is at least as recent as the one used
    //   to create the file being read

    intFileVersion = static_cast<int>(FileVersion * 1000 + 0.5);

    if (intFileVersion > CGNS_VERSION)
    {
        // This code allows reading version newer than the lib,
        // as long as the 1st digit of the versions are equal
        if ((intFileVersion / 1000) > (CGNS_VERSION / 1000))
        {
            vtkErrorMacro(<< "The file " << FileName
                << " was written with a more recent version"
                "of the CGNS library.  You must update your CGNS"
                "library before trying to read this file.");
            ierr = 0;
        }
        // warn only if different in second digit
        if ((intFileVersion / 100) > (CGNS_VERSION / 100))
        {
            vtkWarningMacro(<< "The file being read is more recent"
                "than the CGNS library used");
        }
    }
    if ((intFileVersion / 10) < 255)
    {
        vtkWarningMacro(<< "The file being read was written with an old version"
            "of the CGNS library. Please update your file"
            "to a more recent version.");
    }
    vtkDebugMacro(<< "FileVersion=" << FileVersion << "\n");

CanReadError:
    cgio_close_file(cgioFile);
    return ierr ? true : false;

}

void FCGNSReader::setReadBC(bool read)
{
    _readBC = read;
    this->Modified();
}

bool FCGNSReader::isReadBC()
{
    return _readBC;
}
