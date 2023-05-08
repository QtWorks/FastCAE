/*
*
* @file   PostData.h
* @brief  数据管理类
* @author Sundaobo
*
*/
#ifndef POSTDATA_H
#define POSTDATA_H

#include "PostDataPart.h"
#include "PostCurveDataManagerAPI.h"
#include <QList>

namespace PostData {

class POSTCURVEDATAMANAGERAPI PostData
   {
   private:
    static PostData* _instance;

    PostData(){this->initialize();}

    ~PostData()  = default;

public:
    //设置单例模式
    static PostData* getInstance(){

    if(_instance == nullptr)

     _instance = new PostData;

     return _instance;}

   public:
       /**
       * @brief 添加后处理数据块
       * @param part 数据块
       * @since Version: 1.0.0
       */
       void appendPostDataPart(PostDataPart* part);
       //获取列表
       QList<PostDataPart*> getPostDataPart();
       //获取列表大小
       int getPostDataPartCount();
       //根据索引删除节点
       void delDataPartFromindex(int index);

   private:
        void initialize();

   private:
       /**
       * @brief 后处理数据块id
       * @since Version: 1.0.0
       */
       QList<PostDataPart*> _partList{};
   };
}
#endif // POSTDATA_H
