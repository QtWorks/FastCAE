/*
*
* @file   PostCurveData.h
* @brief  曲线数据类
* @author Sundaobo
*
*/
#ifndef POSTCURVEDATA_H
#define POSTCURVEDATA_H

#include "PostCurveDataManagerAPI.h"
#include "PostDataPart.h"
#include <QHash>

namespace PostData {


class POSTCURVEDATAMANAGERAPI PostCurveData : public PostDataPart
{
public:
    /**
    * @brief 构造函数，创建后处理曲线数据
    * @param type 数据类型
    */
    PostCurveData(PostType type);
    /**
    * @brief 析构
    */
    ~PostCurveData();
    /**
    * @brief 添加数据
    * @param name 数据名称
    * @param value 数据值
    * @since Version: 1.0.0
    */
    void appendData(QString name, double value);
    /**
    * @brief 获取数据名称列表
    * @return QList<QString> 数据名称列表
    * @since Version: 1.0.0
    */
    QList<QString> getDataNames();
    /**
    * @brief 根据名称获取数据
    * @param name 数据名称
    * @return QVector<double> 数据
    * @since Version: 1.0.0
    */
    QVector<double> getDataByName(QString name);
    /**
    * @brief 获取数据量
    * @return int 数据的数量
    * @since Version: 1.0.0
    */
    int getDataCount();
    /**
    * @brief 数据是否为空
    * @return bool 是否为空
    * @since Version: 1.0.0
    */
    bool isDataEmpty();

    QString getName();

    void setName(QString name);

private:
    /**
    * @brief 数据名称和数据的hash
    * @note 键值：数据名称
    * @since Version: 1.0.0
    */
    QHash<QString, QVector<double>> _dataHash{};

    //名称
    QString _name;
};

}

#endif // POSTCURVEDATA_H
