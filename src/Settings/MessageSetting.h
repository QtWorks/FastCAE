/**
 * @file MessageSetting.h
 * @brief 输出消息配置信息类头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 17:35
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
#include "QColor"
class QSettings;

namespace Setting
{
	class MessageSetting
	{
	public:
		MessageSetting() = default;
		~MessageSetting() = default;

		void writeINI(QSettings *setting);
		void readINI(QSettings *setting);

		int getShowMode() const;

		void setShowMode(int showMode);

		bool getShowType() const;

		void setShowType(bool showType);

		bool getShowTime() const;

		void setShowTime(bool showTime);

		int getFontPts() const;

		void setFontPts(int fontPts);

		QColor getBkColor() const;

		void setBkColor(const QColor &bkColor);

	private:
		///< MG setting if show normal . warning . error message
		int m_showMode;

		///< MG if show the message type
		bool m_showType;

		///< MG if show the message time
		bool m_showTime;

		///< MG font size in pts
		int m_fontPts;

		///< MG background color of the message window
		QColor m_bkColor;
	};
}
