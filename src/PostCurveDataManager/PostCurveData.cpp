#include "PostCurveData.h"

namespace PostData {


PostCurveData::PostCurveData(PostType type):
    PostDataPart(type)
{

}

PostCurveData::~PostCurveData()
    {
        _dataHash.clear();
    }

void PostCurveData::appendData(QString name, double value)
{
    QList<QString> names = _dataHash.keys();
    if (names.contains(name))
        _dataHash[name].append(value);
    else
    {
        QVector<double> datas;
        datas.append(value);
        _dataHash.insert(name, datas);
    }
}

QList<QString> PostCurveData::getDataNames()
{
    return _dataHash.keys();
}

QVector<double> PostCurveData::getDataByName(QString name)
{
    return _dataHash.value(name);
}

int PostCurveData::getDataCount()
{
    if (_dataHash.isEmpty())
        return 0;
    QString name = _dataHash.keys().at(0);

    return _dataHash.value(name).size();
}

bool PostCurveData::isDataEmpty()
{
    return _dataHash.isEmpty();
}

void PostCurveData::setName(QString name)
{
    _name = name;

}

QString PostCurveData::getName()
{
    return _name;
}

}
