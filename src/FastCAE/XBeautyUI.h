/**
 * @file XBeautyUI.h
 * @brief 界面风格(.qss)管理类头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 16:01
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
#pragma once
#include <QObject>
#include <QStringList>

/**
 * @brief 界面风格管理单例类
 * @since 2.5.0
 */
class XBeautyUI : public QObject
{
	Q_OBJECT

public:
	/**
	 * @brief 获取单例类的单例对象
	 * @return XBeautyUI* 返回界面风格管理类的单例对象
	 * @since 2.5.0
	 */
	static XBeautyUI *instance();
	/**
	 * @brief 获取界面风格所使用的qss文件路径
	 * @return QString 返回qss的全路径
	 * @since 2.5.0
	 */
	QString qssFilePath() const;
	/**
	 * @brief 设置界面风格的qss
	 * @param _qssFilePath 要设置为风格的qss文件路径
	 * @since 2.5.0
	 */
	void setQssFilePath(const QString &_qssFilePath);
	/**
	 * @brief 获取欢迎图片的名称
	 * @return QString 返回欢迎图片的名称
	 * @since 2.5.0
	 */
	QString welcomePictureName() const;
	/**
	 * @brief 设置欢迎图片的名称
	 * @param _welcomePictureName 欢迎图片的名称
	 * @since 2.5.0
	 */
	void setWelcomePictureName(const QString &_welcomePictureName);
	/**
	 * @brief 获取当前风格的名称
	 * @return QString 返回当前使用风格的名称
	 * @since 2.5.0
	 */
	QString currentStyle() const;
	/**
	 * @brief 设置当前风格的名称
	 * @return style 设置要是用风格的名称
	 * @since 2.5.0
	 */
	void setCurrentStyle(const QString &style);
	/**
	 * @brief 返回Qt在不同平台下的内置样式
	 * @return QStringList 返回所在平台支持的QStyle的名称列表
	 * @since 2.5.0
	 */
	QStringList getStyles() const;
	/**
	 * @brief 根据不同的平台，自动设置默认风格
	 * @since 2.5.0
	 */
	void autoSetStyle() const;
	/**
	 * @brief 获取欢迎图片的停留时间
	 * @return int 返回欢迎图片的停留时间(单位：毫秒)
	 * @since 2.5.0
	 */
	int welcomePictureRemainTime() const;
	/**
	 * @brief 设置欢迎图片的停留时间
	 * @param time 要设置的停留时间(单位：毫秒)
	 * @since 2.5.0
	 */
	void setWelcomePictureRemainTime(int time = 1500);

private:
	/**
	 * @brief 构造函数
	 * @since 2.5.0
	 */
	XBeautyUI();
	/**
	 * @brief 析构函数
	 * @since 2.5.0
	 */
	~XBeautyUI();

private:
	/**
	 * @brief 风格管理类的单例对象
	 * @since 2.5.0
	 */
	static XBeautyUI *_instance;
	/**
	 * @brief 欢迎图片的名称
	 * @since 2.5.0
	 */
	QString m_welcomePictureName;
	/**
	 * @brief qss文件的路径
	 * @since 2.5.0
	 */
	QString m_qssFilePath;
	/**
	 * @brief 当前使用的风格
	 * @since 2.5.0
	 */
	QString m_currentStyle;
	/**
	 * @brief 欢迎图片的停留时间
	 * @since 2.5.0
	 */
	int m_welcomeRemainTime;
};
