/**
 * @file SolverConfig.h
 * @brief 求解器、网格剖分器配置信息类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 16:28
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
#ifndef _SOLVERCONFIG_H_
#define _SOLVERCONFIG_H_

#include "ConfigOptionsAPI.h"
#include <QList>
#include <QString>

namespace ConfigOption
{
	class SolverInfo;
	class MesherInfo;
	/**
	 * @brief 求解器、网格剖分器配置信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI SolverOption
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		SolverOption() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~SolverOption() = default;
		/**
		 * @brief 清除求解器、网格剖分器列表
		 * @since 2.5.0
		 */
		void clearData();
		/**
		 * @brief 向求解器列表增加求解器
		 * @param s 要增加的求解器对象
		 * @since 2.5.0
		 */
		void appendSolver(SolverInfo *s);
		/**
		 * @brief 向网格剖分器列表增加网格剖分器
		 * @param s 要增加的网格剖分器对象
		 * @since 2.5.0
		 */
		void appendMesher(MesherInfo *m);
		/**
		 * @brief 获取索引位置为index的求解器
		 * @param index 索引位置（从0开始）
		 * @return SolverInfo* 求解器对象
		 * @attention 索引超出范围会返回nullptr
		 * @since 2.5.0
		 */
		SolverInfo *getSolverAt(int index);
		/**
		 * @brief 获取索引位置为index的网格剖分器
		 * @param index 索引位置（从0开始）
		 * @return SolverInfo* 网格剖分器对象
		 * @attention 索引超出范围会返回nullptr
		 * @since 2.5.0
		 */
		MesherInfo *getMesherAt(int index);
		/**
		 * @brief 获取名为name的网格剖分器
		 * @param name 要获取网格剖分器的名称
		 * @return MesherInfo* 网格剖分器对象
		 * @attention 如果网格剖分器列表不存在名为name的对象，则返回nullptr
		 * @since 2.5.0
		 */
		MesherInfo *getMesherByName(QString name);
		/**
		 * @brief 获取求解器列表中的对象数量
		 * @return int 求解器列表中的对象数量
		 * @since 2.5.0
		 */
		int getSolverCount();
		/**
		 * @brief 获取网格剖分器列表中的对象数量
		 * @return int 网格剖分器列表中的对象数量
		 * @since 2.5.0
		 */
		int getMesherCount();
		/**
		 * @brief 移除索引位置index处的求解器
		 * @param index 索引位置（从0开始）
		 * @since 2.5.0
		 */
		void removeSolver(int index);
		/**
		 * @brief 从配置文件（xml）中获取求解器、网格剖分器的列表
		 * @param f xml配置文件的路径
		 * @return bool 返回执行结果
		 * @since 2.5.0
		 */
		bool read(QString f);
		/**
		 * @brief 将求解器、网格剖分器的列表写入xml配置文件
		 * @param f 要写入信息的xml配置文件的路径
		 * @return bool 返回执行结果
		 * @since 2.5.0
		 */
		void write(QString f);

	private:
		/**
		 * @brief 求解器列表
		 * @since 2.5.0
		 */
		QList<SolverInfo *> _solverlist{};
		/**
		 * @brief 网格剖分器列表
		 * @since 2.5.0
		 */
		QList<MesherInfo *> _mesherList{};
	};
}

#endif