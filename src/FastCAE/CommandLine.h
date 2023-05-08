/**
 * @file CommandLine.h
 * @brief 命令行参数类的头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 15:38
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
#ifndef _COMMANDLINE_H__
#define _COMMANDLINE_H__

#include <QString>

namespace GUI
{
	class MainWindow;
}

/**
 * @brief 命令行参数类
 * @since 2.5.0
 */
class CommandPara
{
public:
	/**
	 * @brief 构造一个命令行参数类对象
	 * @param argc 命令行参数的个数
	 * @param argv 命令行参数数组
	 * @since 2.5.0
	 */
	CommandPara(int argc, char *argv[]);
	/**
	 * @brief 析构函数
	 * @since 2.5.0
	 */
	~CommandPara() = default;
	/**
	 * @brief 判断命令行参数是否含有“-help”
	 * @return bool 如果参数包含“-help”，则返回true，否则返回false
	 * @since 2.5.0
	 */
	bool isHelp();
	/**
	 * @brief 执行主窗口程序
	 * @param window 主窗口对象
	 * @return bool 返回执行结果、
	 * @note 此函数会根据参数是否含有“-nogui”决定是否启动界面
	 * @since 2.5.0
	 */
	bool exec(GUI::MainWindow *window);

private:
	/**
	 * @brief 自定义文件错误处理函数
	 * @param f 文件的全路径
	 * @param w 主窗口对象
	 * @note 该函数用来根据是否启动界面决定文件不存在时错误信息的显示方式
	 * @since 2.5.0
	 */
	void fileWarning(QString f, GUI::MainWindow *w);
	/**
	 * @brief 将程序输入信息附件到命令行
	 * @attention 该函数仅在windows环境有效
	 * @since 2.5.0
	 */
	void connectToConsole();

private:
	/**
	 * @brief 是否显示图形界面
	 * @since 2.5.0
	 */
	bool _showGUI{true};
	/**
	 * @brief 是否输出帮助信息
	 * @since 2.5.0
	 */
	bool _help{false};
	/**
	 * @brief python脚本文件
	 * @since 2.5.0
	 */
	QString _scriptFile{};
	/**
	 * @brief FastCAE工程文件
	 * @since 2.5.0
	 */
	QString _projectFile{};
};

#endif
