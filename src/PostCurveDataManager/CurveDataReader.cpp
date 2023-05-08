#include "CurveDataReader.h"
#include "PostCurveData.h"
#include "PostData.h"
#include <QList>
#include <QFile>

namespace PostData {

CurveDataReader::CurveDataReader()
{

}

CurveDataReader::~CurveDataReader()
{

}

int CurveDataReader::read(QString fileName)
{
    QFile* file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly))
        return -1;

    auto dataPart = new PostCurveData(PostCurve);

    bool ok = false;
    QString line;
    QStringList nemeList;
    line = file->readLine().simplified();
    nemeList = line.split(" ");
    const int column = nemeList.size();
    while (!file->atEnd())
    {
        QStringList lineList;
        line = file->readLine().simplified();
        lineList = line.split(" ");
        if (lineList.size() != column)continue;
        for (int i = 0; i < column; i++)
        {
            double value = lineList.at(i).toDouble(&ok);
            //if(!ok)break;
            dataPart->appendData(nemeList.at(i), value);
            dataPart->setName(fileName);
        }
    }

    file->close();
    delete file;

    if (!dataPart->isDataEmpty())
    {
          QList<PostDataPart*> _datapartlist = PostData::PostData::getInstance()->getPostDataPart();
          if(_datapartlist.size()==0)
          {
              PostData::getInstance()->appendPostDataPart(dataPart);
              return 1;
          }
          else
          {
              for(int i = 0; i<_datapartlist.size(); i++)
              {
                  PostCurveData* _postcurvedata = dynamic_cast<PostCurveData*>(_datapartlist[i]);
                  if(_postcurvedata->getName() == dataPart->getName())
                  {
                      return -1;
                  }
              }
              PostData::getInstance()->appendPostDataPart(dataPart);
              return 1;
          }

//            APP_DataManager::getInstance()->getPostData()->appendPostDataPart(dataPart);
//            return dataPart->getID();
    }


    delete dataPart;
    return -1;
}

}
