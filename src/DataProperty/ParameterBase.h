/**
 * @file ParameterBase.h
 * @brief 参数基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 17:02
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
#ifndef _EDITABLEPROPERTYBASE_H_
#define _EDITABLEPROPERTYBASE_H_

#include "DataProperty/DataPropertyAPI.h"
#include <QString>
#include <QObject>
#include <QList>

class QDomDocument;
class QDomElement;

namespace ConfigOption
{
	class ParameterObserver;
}

namespace DataProperty
{
	/**
	 * @brief 参数类型枚举值
	 * @note 未定义类型（Para_Blank）一般用于初始化，说明未指定参数类型
	 * @since 2.5.0
	 */
	enum  ParaType
	{
		Para_Blank = 0, ///< 未定义类型
		Para_Int, ///< 整型参数
		Para_Double, ///< 双精度浮点型参数
		Para_Color, ///< 颜色类型参数（=QColor）
		Para_String, ///< 字符串参数
		Para_Bool, ///< 布尔类型参数
		Para_Selectable, ///< 枚举类型参数
		Para_Path, ///< 路径类型参数
		Para_Table, ///< 表格类型参数
	};

	/**
	 * @brief 模块类型枚举值
	 * @note 未定义模块（Module_None）一般用于初始化，说明未指定参数类型
	 * @since 2.5.0
	 */
	enum ModuleType
	{
		Module_None = 0, ///< 未定义模块
		Module_Model, ///< 模型模块
		Module_BC, ///< 边界条件模块
		Module_Material, ///< 材料模块
		Module_Mesher, ///< 网格剖分器模块
		Module_MeshSet, ///< 网格模块
	};
	
	/**
	 * @brief 参数基类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI ParameterBase : public QObject
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param t 参数类型
		 * @since 2.5.0
		 */
		ParameterBase(ParaType t);
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		ParameterBase() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ParameterBase() = default;
		/**
		 * @brief 从ori中拷贝内容
		 * @param ori 要拷贝内容的源参数对象
		 * @param valueOnly 是否仅仅拷贝值
		 * @since 2.5.0
		 */
		virtual void copy(ParameterBase* ori, bool valueOnly = false);
		/**
		 * @brief 获取参数类型
		 * @return ParaType 参数的类型
		 * @since 2.5.0
		 */
		ParaType getParaType();
		/**
		 * @brief 设置参数的类型
		 * @param type 参数的类型
		 * @since 2.5.0
		 */
		void setParaType(ParaType type);
		/**
		 * @brief 获取参数的名称
		 * @return QString 参数的名称
		 * @since 2.5.0
		 */
		QString getDescribe();
		/**
		 * @brief 设置参数的名称
		 * @param s 参数的名称
		 * @since 2.5.0
		 */
		void setDescribe(QString s);
		/**
		 * @brief 设置参数是否可见
		 * @param v 参数是否可见的布尔值
		 * @since 2.5.0
		 */
		void setVisible(bool v);
		/**
		 * @brief 获取参数是否可见
		 * @return bool 参数是否可见的布尔值
		 * @since 2.5.0
		 */
		bool isVisible();
		/**
		 * @brief 设置参数是否可以被编辑
		 * @param e 参数是否可以被编辑的布尔值
		 * @since 2.5.0
		 */
		void setEditable(bool e);
		/**
		 * @brief 获取参数是否可以被编辑
		 * @return bool 参数是否可以被编辑的布尔值
		 * @since 2.5.0
		 */
		bool isEditable();
		/**
		 * @brief 设置参数的中文名称，与setDescribe()对应
		 * @param chinese 参数的中文名称
		 * @since 2.5.0
		 */
		void setChinese(QString chinese);
		/**
		 * @brief 获取参数的中文名称
		 * @return QString 参数的中文名称
		 * @since 2.5.0
		 */
		QString getChinese();
		/**
		 * @brief 将参数转换为字符串类型（QString）值
		 * @return QString 转换后得到的字符串值
		 * @since 2.5.0
		 */
		virtual QString valueToString();
		/**
		 * @brief 设置从字符串对象获取参数值（转换）
		 * @param v 要操作的字符串
		 * @note 函数定义请参考子类的重载函数
		 * @since 2.5.0
		 */
		virtual void setValueFromString(QString v);
		/**
		 * @brief 设置参数的模块类型
		 * @param t 参数的模块类型
		 * @since 2.5.0
		 */
		void setModuleType(ModuleType t);
		/**
		 * @brief 获取参数的模块类型
		 * @return ModuleType 参数的模块类型
		 * @since 2.5.0
		 */
		ModuleType getModuleType();

		//获取数据ID(DataBase)
		int getDataID();
		//设置数据ID
		void setDataID(int id);
		//获取数据索引
		int getDataIndex();
		//设置数据索引
		void setDataIndex(int index);
		/**
		 * @brief 获取参数的组名
		 * @return QString 
		 * @since 2.5.0
		 */
		QString getGroupName();
		/**
		 * @brief 设置参数所在的组
		 * @param group 要设置的组名
		 * @since 2.5.0
		 */
		void setGroupName(QString group);
		/**
		 * @brief 以<groupName>/<paraName>的格式返回名称
		 * @return QString 参数的名称
		 * @note 如果groupName为空，则返回<paraName>
		 * @since 2.5.0
		 */
		QString genAbsoluteName();
		/**
		 * @brief 追加观察者到观察者列表
		 * @param obs 要追加的观察者对象
		 * @since 2.5.0
		 */
		void appendObserver(ConfigOption::ParameterObserver* obs);
		/**
		 * @brief 获取观察者列表
		 * @return QList<ConfigOption::ParameterObserver*> 观察者列表
		 * @since 2.5.0
		 */
		QList<ConfigOption::ParameterObserver*> getObserverList();
		/**
		 * @brief 判断对象是否与参数p值相等
		 * @param p 要比较的参数对象
		 * @return bool 
		 * @since 2.5.0
		 */
		virtual bool isSameValueWith(ParameterBase* p);
		/**
		 * @brief 拷贝参数的状态（是否可见、可编辑）
		 * @param p 要拷贝状态的源参数对象
		 * @since 2.5.0
		 */
		virtual void copyStatus(ParameterBase* p);
		/**
		 * @brief 将参数对象写入到工程文件
		 * @param doc 工程文件的QDomDocument对象
		 * @param parent 要追加该参数的父节点
		 * @since 2.5.0
		 */
		virtual void writeParameter(QDomDocument* doc, QDomElement* parent);
		/**
		 * @brief 从工程文件中对应节点读取参数
		 * @param e 工程文件中对应的节点对象
		 * @since 2.5.0
		 */
		virtual void readParameter(QDomElement* e);
		/**
		 * @brief 参数类型转换为字符串
		 * @param t 参数类型
		 * @return QString 返回转换后的字符串
		 * @attention 未定义类型（Para_Blank）会返回空字符串
		 * @since 2.5.0
		 */
		static QString ParaTypeToString(ParaType t);
		/**
		 * @brief 字符串转换为参数类型
		 * @param stype 要转换的字符串
		 * @return ParaType 参数类型
		 * @attention 字符串不合法时返回未定义类型（Para_Blank）
		 * @since 2.5.0
		 */
		static ParaType StringToParaType(QString stype);

	signals:
		/**
		 * @brief 当参数值发生变化时，触发该信号
		 * @since 2.5.0
		 */
		void dataChanged();


	protected:
		/**
		 * @brief 参数类型
		 * @since 2.5.0
		 */
		ParaType _type{ Para_Blank };
		/**
		 * @brief 参数名称
		 * @since 2.5.0
		 */
		QString _describe{};
		/**
		 * @brief 参数中文名称
		 * @since 2.5.0
		 */
		QString _chinese{};
		/**
		 * @brief 参数是否可编辑
		 * @since 2.5.0
		 */
		bool _editable{ true };
		/**
		 * @brief 参数是否可见
		 * @since 2.5.0
		 */
		bool _visible{ true };
		/**
		 * @brief 观察者列表（参见观察者模式）
		 * @since 2.5.0
		 */
		QList<ConfigOption::ParameterObserver*> _observerList{};

		//****与参数隶属的模块相关信息,与DataBase相同********
		ModuleType _moduleType{ Module_None };
		int _dataID{ -1 };
		int _dataIndex{ -1 };
		QString _groupName{};
		//**************************************************
	};

}


#endif
