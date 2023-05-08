#include "PostDataPart.h"

namespace PostData {


PostDataPart::PostDataPart(PostType type)
{
    _type = type;
}

PostDataPart::~PostDataPart()
{
}



PostType PostDataPart::getPostType()
{
    return _type;
}

}
