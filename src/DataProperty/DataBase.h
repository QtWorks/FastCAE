/**
 * @file DataBase.h
 * @brief 数据基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-15 13:36
 * @copyright Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 *
 * ============================================================================
 * Program:   FastCAE
 *
 * Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 * See License or http://www.fastcae.com/ for details.
 *
 * BSD 3-Clause License
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.
 * ==================================================================================
 */
#ifndef PROPDATABASE_H
#define PROPDATABASE_H

#include "PropertyList.h"
#include "ParameterList.h"
#include "DataPropertyAPI.h"
#include <QString>
#include <QList>
#include <QStringList>
#include <QObject>

class QDomDocument;
class QDomElement;

/**
 * @brief 按钮信息结构体
 * @since 2.5.0
 */
struct ButtonInfo
{
	QString text{};	   ///< 按钮文本
	QString chinese{}; ///< 按钮中文文本
	QString command{}; ///< 按钮的响应命令
};

namespace DataProperty
{
	class ParameterGroup;

	/**
	 * @brief 数据基类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI DataBase : public QObject, public PropertyList, public ParameterList
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		DataBase() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~DataBase() = default;
		/**
		 * @brief 设置数据所属的模块
		 * @param t 枚举值模块
		 * @since 2.5.0
		 */
		void setModuleType(ModuleType t);
		/**
		 * @brief 获取数据所述的模块
		 * @return ModuleType 返回枚举值模块
		 * @since 2.5.0
		 */
		ModuleType getModuleType();
		/**
		 * @brief 拷贝数据值
		 * @param data 要拷贝的源数据
		 * @since 2.5.0
		 */
		virtual void copy(DataBase *data);
		/**
		 * @brief 设置数据的ID值
		 * @param id ID值
		 * @since 2.5.0
		 */
		virtual void setID(int id);
		/**
		 * @brief 获取数据的ID值
		 * @return int 返回ID值
		 * @since 2.5.0
		 */
		int getID();
		/**
		 * @brief 设置数据的索引值
		 * @param index 索引值
		 * @since 2.5.0
		 */
		void setIndex(int index);
		/**
		 * @brief 获取数据的索引值
		 * @return int 返回索引值
		 * @since 2.5.0
		 */
		int getIndex();
		/**
		 * @brief 设置数据的名称
		 * @param name 名称
		 * @since 2.5.0
		 */
		virtual void setName(const QString &name);
		/**
		 * @brief 获取数据的名称
		 * @return QString 返回名称
		 * @since 2.5.0
		 */
		QString getName();
		/**
		 * @brief 将参数组添加到参数组列表中
		 * @param g 要添加的参数组
		 * @since 2.5.0
		 */
		void appendParameterGroup(ParameterGroup *g);
		/**
		 * @brief 获取参数组列表中索引为index的参数组
		 * @param index 要获取参数组的索引值
		 * @return ParameterGroup* 返回获取到的参数组
		 * @since 2.5.0
		 */
		ParameterGroup *getParameterGroupAt(const int index);
		/**
		 * @brief 获取参数组列表中参数组的个数
		 * @return int 返回参数组的个数
		 * @since 2.5.0
		 */
		int getParameterGroupCount();
		/**
		 * @brief 获取参数组列表中可见参数组的个数
		 * @return int 返回可见参数组的个数
		 * @since 2.5.0
		 */
		int getVisiableParameterGroupCount();
		/**
		 * @brief 在参数组列表中移除指定的参数组
		 * @param g 要移除的参数组
		 * @since 2.5.0
		 */
		virtual void removeParameterGroup(ParameterGroup *g);
		/**
		 * @brief 移除参数组列表中索引为i的参数组
		 * @param i 要移除参数组的索引值
		 * @since 2.5.0
		 */
		void removeParameterGroupAt(int i);
		/**
		 * @brief 向参数列表追加参数
		 * @param p 要追加的参数
		 * @since 2.5.0
		 */
		void appendParameter(ParameterBase *p) override;
		/**
		 * @brief 根据类型创建新的参数，并追加到参数列表
		 * @param type 要创建参数的类型
		 * @return ParameterBase* 返回创建的参数
		 * @since 2.5.0
		 */
		ParameterBase *appendParameter(ParaType type) override;
		/**
		 * @brief 将参数从参数列表中移除
		 * @param p 要移除的参数
		 * @since 2.5.0
		 */
		virtual void removeParameter(ParameterBase *p) override;
		/**
		 * @brief 将参数列表转换为二进制流
		 * @param datas 转换后的二进制流
		 * @since 2.5.0
		 */
		virtual void dataToStream(QDataStream *datas) override;
		///数据写入工程文件
		virtual QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *parent);
		///从工程文件读入数据
		virtual void readDataFromProjectFile(QDomElement *e);
		//读取参数
		virtual void readParameters(QDomElement *ele);
		//写出参数
		virtual void writeParameters(QDomDocument *doc, QDomElement *parent);
		///根据名称获取参数
		ParameterBase *getParameterByName(QString name) override;
		/**
		 * @brief 根据名称获取参数组
		 * @param name 要获取参数组的名称
		 * @return ParameterGroup* 返回获取到的参数组
		 * @since 2.5.0
		 */
		virtual ParameterGroup *getParameterGroupByName(QString name);
		/**
		 * @brief 判断数据对象是否包含按钮
		 * @return bool 返回是否包含按钮的布尔值
		 * @since 2.5.0
		 */
		bool isContainsButton();
		/**
		 * @brief 获取按钮列表中所有按钮的英文文本组成的列表
		 * @return QStringList 返回包含所有按钮英文文本的列表
		 * @since 2.5.0
		 */
		QStringList getButtonText();
		/**
		 * @brief 获取按钮列表中所有按钮的中文文本组成的列表
		 * @return QStringList 返回包含所有按钮中文文本的列表
		 * @since 2.5.0
		 */
		QStringList getButtonChinese();
		/**
		 * @brief 获取按钮列表
		 * @return QList<ButtonInfo> 返回按钮列表
		 * @since 2.5.0
		 */
		QList<ButtonInfo> getButtonList();
		//填充所有参数信息，包括模块，ID Index等
		virtual void generateParaInfo();

	private slots:
		/**
		 * @brief 按钮单击响应槽函数
		 * @param b 按钮的文本（或中文文本）
		 * @since 2.5.0
		 */
		virtual void onButtonClicked(QString b);

	protected:
		int _id{-1};
		int _index{-1};
		QString _name{"FFFFFF"};
		/**
		 * @brief 参数组列表
		 * @since 2.5.0
		 */
		QList<ParameterGroup *> _paraGroupList{};
		/**
		 * @brief 按钮列表
		 * @since 2.5.0
		 */
		QList<ButtonInfo> _buttons{};

		ModuleType _moduleType{Module_None};
	};

}

#endif
