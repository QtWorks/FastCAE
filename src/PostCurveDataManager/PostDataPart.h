/*
*
* @file   PostDataPart.h
* @brief  数据基类
* @author Sundaobo
*
*/
#ifndef POSTDATAPART_H
#define POSTDATAPART_H

#include "PostCurveDataManagerAPI.h"

namespace PostData {

enum PostType
{
    PostNone = -1,
    PostCurve,
};

class POSTCURVEDATAMANAGERAPI PostDataPart
{
public:
    PostDataPart(PostType type);

    virtual ~PostDataPart() = 0;

    /**
    * @brief 获取数据块类型
    * @return PostType 类型
    * @since Version: 1.0.0
    */
    PostType getPostType();


protected:
    /**
    * @brief 后处理数据类型
    * @since Version: 1.0.0
    */
    PostType _type{ PostNone };
};

}

#endif // POSTDATAPART_H
