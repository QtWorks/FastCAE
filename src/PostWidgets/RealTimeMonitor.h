/**
 * @file RealTimeMonitor.h
 * @brief 文件监控类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 17:17
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
#ifndef REALTIMEMONITOR_H
#define REALTIMEMONITOR_H

#include <QThread>
#include <QHash>
#include <QString>
#include <QDateTime>

class QTimer;

namespace Post
{
	/**
	 * @brief 文件监控类
	 * @since 2.5.0
	 */
	class RealTimeMonitor : public QThread
	{
		Q_OBJECT
	public:
		RealTimeMonitor();
		~RealTimeMonitor();
		/**
		 * @brief 追加监控文件
		 * @param file 监控文件
		 * @since 2.5.0
		 */
		void appendFile(const QString &file);
		/**
		 * @brief 设置时间间隔步
		 * @param t 间隔时间
		 * @since 2.5.0
		 */
		void setTimeStep(int t);
		void run() override;
		void stop();

	signals:
		void fileChanged(QString file);

	private slots:
		void onTimeout();

	private:
		/**
		 * @brief 记录每个监控文件最后修改时间的哈希表
		 * @since 2.5.0
		 */
		QHash<QString, QDateTime> _fileTimeHash;
		int _timeStep{-1};
		QTimer *_timer{};
	};
}

#endif