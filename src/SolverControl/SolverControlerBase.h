/**
 * @file SolverControlerBase.h
 * @brief 求解器控制基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-12 15:34
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

#ifndef SOLVERCONTROLBASE_H_
#define SOLVERCONTROLBASE_H_

#include "solverControlAPI.h"
#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>

namespace GUI
{
	class MainWindow;
}
namespace ModuleBase
{
	class ProcessBar;
}
namespace Post
{
	class RealTimeWindowBase;
}
namespace ConfigOption
{
	class SolverInfo;
}
namespace ModelData
{
	class ModelDataBase;
}

namespace SolverControl
{
	/**
	 * @brief 求解器控制基类
	 * @since 2.5.0
	 */
	class SOLVERCONTROLAPI SolverControlBase : public QObject
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param mainwindow 主窗口对象
		 * @param solver 求解器对象
		 * @param model 模型对象
		 * @param sollveOnly 
		 * @since 2.5.0
		 */
		SolverControlBase(GUI::MainWindow* mainwindow, ConfigOption::SolverInfo* solver, ModelData::ModelDataBase* model,bool sollveOnly = false);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~SolverControlBase();
		/**
		 * @brief 用构造的求解器启动求解
		 * @since 2.5.0
		 */
		void startSolver();
		/**
		 * @brief 设置求解器的名称（描述）
		 * @param des 
		 * @since 2.5.0
		 */
		void setSolverDescription(QString des);
		/**
		 * @brief 结束求解
		 * @since 2.5.0
		 */
		void stopSolver();
		/**
		 * @brief 以并行的方式启动求解器
		 * @param nprocess 并行所使用的核数
		 * @since 2.5.0
		 */
		void startMPI(int nprocess);
		/**
		 * @brief 设置求解器启动时的参数
		 * @param arg 求解器运行参数
		 * @since 2.5.0
		 */
		void setSolveArgs(QString arg);
		/**
		 * @brief 清爽启动求解器
		 * @note 该方式启动不会有前置检查
		 * @since 2.5.0
		 */
		void startSolverClear();


	signals:
		/**
		 * @brief 求解器启动之后会触发该信号
		 * @param processBar 
		 * @since 2.5.0
		 */
		void solverStarted(QWidget* processBar);
		/**
		 * @brief 发送消息的信号
		 * @param mess 要发送的消息
		 * @since 2.5.0
		 */
		void sendMessage(QString mess);
		void processFinish(int pid);
		void openRealTime(Post::RealTimeWindowBase* w, int proID);
		void removeSolver(int pid);

	protected slots:
		virtual void readSolverOutput();
		//程序运行完成
		void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
		/**
		 * @brief 强行终止求解器
		 * @param w 
		 * @since 2.5.0
		 */
		void stopSolver(QWidget* w);

	protected:
		/**
		 * @brief 写出求解器输入文件
		 * @return bool 返回写出结果
		 * @since 2.5.0
		 */
		bool preProcess();
		/**
		 * @brief 求解器输出文件转换
		 * @return bool 返回转换结果
		 * @since 2.5.0
		 */
		bool postPorocess();

	protected:
		bool _solveOnly = false;
		/**
		 * @brief 启动求解器的进程
		 * @since 2.5.0
		 */
		QProcess _process{};
		/**
		 * @brief 主窗口
		 * @since 2.5.0
		 */
		GUI::MainWindow* _mainWindow{};
		/**
		 * @brief 求解器名称（描述）
		 * @since 2.5.0
		 */
		QString _description{};
		/**
		 * @brief 求解器启动参数
		 * @since 2.5.0
		 */
		QString _args{};
		/**
		 * @brief 求解进度条
		 * @since 2.5.0
		 */
		ModuleBase::ProcessBar* _processBar{};
		QString _outputBuffer{};
		/**
		 * @brief 求解计算是否结束
		 * @since 2.5.0
		 */
		bool _processFinished{ false };
		/**
		 * @brief 求解器信息
		 * @since 2.5.0
		 */
		ConfigOption::SolverInfo* _solver{};
		ModelData::ModelDataBase* _model{};
	
	};
}


#endif
