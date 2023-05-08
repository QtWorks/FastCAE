#include "PostData.h"

namespace PostData {

PostData* PostData::_instance = nullptr;

void PostData::appendPostDataPart(PostDataPart* part)
{
    _partList.append(part);
}

QList<PostDataPart*> PostData::getPostDataPart(){
    return _partList;
}

void PostData::initialize()
{

}

int PostData::getPostDataPartCount()
{
    return _partList.size();
}

void PostData::delDataPartFromindex(int index)
{
    _partList.removeAt(index);
}

}

