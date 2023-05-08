/*
*
* @file   CurveDataReader.h
* @brief  数据读取类
* @author Sundaobo
*
*/
#ifndef CURVEDATAREADER_H
#define CURVEDATAREADER_H

#include "PostCurveDataManagerAPI.h"
#include <QString>

namespace PostData {


class POSTCURVEDATAMANAGERAPI CurveDataReader
{
public:
   CurveDataReader();
   ~CurveDataReader();

   /**
   * @brief 曲线读取函数
   * @param fileName 文件：文件绝对路径+文件名称
   * @since Version: 1.0.0
   */
   int read(QString fileName);
};

}

#endif // CURVEDATAREADER_H
