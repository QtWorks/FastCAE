/**
 * @file ColorCombobox.cpp
 * @brief 颜色选择下拉框类源(.cpp)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 17:40
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

// -*- Mode: c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2  -*-
//---------------------------------------------------------------------------
#include <QToolTip>
#include <QPainter>
#include <QColorDialog>
#include "ColorCombobox.h"

ColorCombobox::ColorCombobox(QWidget *parent) : QComboBox(parent)
{
	setEditable(false);
	_colorDialogEnabled = false;
	connect(this, SIGNAL(activated(int)), SLOT(emitActivatedColor(int)));
	connect(this, SIGNAL(highlighted(int)), SLOT(emitHighlightedColor(int)));
}

void ColorCombobox::enableColorDialog(bool enabled)
{
	if (_colorDialogEnabled == enabled)
		return;
	if (enabled)
		addItem(tr("More ..."));
	else
		removeItem(count() - 1);
	_colorDialogEnabled = enabled;
}

bool ColorCombobox::hasColor(const QColor &c)
{
	int num = count();
	if (_colorDialogEnabled)
		num--;
	for (int i = 0; i < num; i++)
		if (color(i) == c)
			return true;
	return false;
}

void ColorCombobox::appendColor(const QColor &c, const QString &n)
{
	if (!c.isValid() || hasColor(c))
		return;
	// 准备位图
	QPixmap pix(16, 16);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(Qt::gray);
	painter.setBrush(QBrush(c));
	painter.drawRect(1, 1, 13, 13);
	// 添加到列表末尾
	int i = count();
	QString tn = n.isEmpty() ? c.name().toUpper() : n;
	if (!_colorDialogEnabled)
		addItem(tn, QVariant(c.name()));
	else
		insertItem(--i, tn, QVariant(c.name()));
	setItemIcon(i, QIcon(pix));
	setCurrentIndex(i);
}
void ColorCombobox::appendOtherColor()
{
	// QColor color=QColorDialog::getColor(Qt::red,this,tr("other"));
	// QColor color=Qt::red;
	QPixmap pix(16, 16);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(Qt::gray);
	QConicalGradient conicalGradient(6, 6, 0);
	conicalGradient.setColorAt(0, QColor(255, 0, 0));
	conicalGradient.setColorAt(0.166, QColor(255, 255, 0));
	conicalGradient.setColorAt(0.333, QColor(0, 255, 0));
	conicalGradient.setColorAt(0.5, QColor(0, 255, 255));
	conicalGradient.setColorAt(0.666, QColor(0, 0, 255));
	conicalGradient.setColorAt(0.833, QColor(255, 0, 255));
	conicalGradient.setColorAt(1, QColor(255, 0, 0));

	painter.setBrush(QBrush(conicalGradient));
	painter.drawRect(1, 1, 13, 13);
	int i = count();
	// addItem(tr("other"),3);
	insertItem(i, tr("Custom..."), 3);
	setItemIcon(i, QIcon(pix));
	// setCurrentIndex(i);
}
// Added by jingzhe tao. 2013/07/25
void ColorCombobox::updateOtherColor(const QColor &color)
{
	QPixmap pix(16, 16);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(Qt::gray);
	painter.setBrush(QBrush(color));
	painter.drawRect(1, 1, 13, 13);
	int i = count() - 1;
	// addItem(tr("other"),3);
	setItemText(i, QString(tr("Custom(%1)...")).arg(color.name()));
	setItemData(i, color.name());
	setItemIcon(i, QIcon(pix));
	setCurrentIndex(i);
}
void ColorCombobox::insertColor(const QColor &c, const QString &n, int i)
{
	if (!c.isValid() || hasColor(c))
		return;
	int num = count();
	if (_colorDialogEnabled)
		num--;
	if (i >= 0 && i < num)
	{
		QPixmap pix(18, 18);
		QPainter painter(&pix);
		painter.setPen(Qt::gray);
		painter.setBrush(QBrush(c));
		painter.drawRect(1, 1, 13, 13);
		QString tn = n.isEmpty() ? c.name().toUpper() : n;
		insertItem(i, tn, QVariant(c.name()));
		setItemIcon(i, QIcon(pix));
		setCurrentIndex(i);
	}
	else
		appendColor(c, n);
}

QColor ColorCombobox::currentColor() const
{
	int index = currentIndex();
	return color(index);
}

void ColorCombobox::setCurrentColor(const QColor &c)
{
	bool existed = false;
	for (int i = 0; i < (int)count(); i++)
	{
		if (color(i) == c)
		{
			setCurrentIndex(i);
			_lastActivated = c;
			existed = true;
			break;
		}
	}
	if (!existed)
	{
		_lastActivated = c;
		updateOtherColor(c);
	}
}

QColor ColorCombobox::color(int index) const
{
	if (_colorDialogEnabled && index >= count() - 1)
		return QColor();
	else if (index < 0)
		return QColor();
	else
		return QColor(itemData(index).toString());
}

void ColorCombobox::emitActivatedColor(int index)
{
	if (index == count() - 1)
	{
		QColor color = QColorDialog::getColor(_lastActivated, this, tr("Custom Color"));
		if (color.isValid())
		{
			this->updateOtherColor(color);
			_lastActivated = QColor(itemData(index).toString());
		}
		else
		{
			setCurrentColor(_lastActivated);
		}
	}
	else
		_lastActivated = QColor(itemData(index).toString());
	emit activated(_lastActivated);
}

void ColorCombobox::emitHighlightedColor(int index)
{
	if (!_colorDialogEnabled || index != count() - 1)
		emit highlighted(color(index));
}

QSize ColorCombobox::sizeHint() const
{
	QFontMetrics fm(font());
	return QSize(fm.horizontalAdvance(tr("#RRGGBB")) + 16 + 4 + 20, fm.height() + 4);
}

void ColorCombobox::appendPredefinedColors()
{
	appendColor(Qt::black, tr("Black"));
	appendColor(Qt::darkBlue, tr("Dark blue"));
	appendColor(Qt::darkGreen, tr("Dark green"));
	appendColor(Qt::darkCyan, tr("Dark cyan"));
	appendColor(Qt::darkRed, tr("Dark red"));
	appendColor(Qt::darkMagenta, tr("Dark magenta"));
	appendColor(Qt::darkYellow, tr("Dark yellow"));
	appendColor(Qt::darkGray, tr("Dark gray"));
	appendColor(Qt::gray, tr("Gray"));
	appendColor(Qt::blue, tr("Blue"));
	appendColor(Qt::green, tr("Green"));
	appendColor(Qt::cyan, tr("Cyan"));
	appendColor(Qt::red, tr("Red"));
	appendColor(Qt::magenta, tr("Magenta"));
	appendColor(Qt::yellow, tr("Yellow"));
	appendColor(Qt::white, tr("White"));
	this->appendOtherColor();
}
void ColorCombobox::appendBackgroundColors()
{
	appendColor(Qt::black, tr("Black"));
	appendColor(Qt::gray, tr("Gray"));
	appendColor(Qt::white, tr("White"));
	this->appendOtherColor();
}
void ColorCombobox::clearAllColors()
{
	clear();
	if (_colorDialogEnabled)
		addItem(tr("More ..."));
}

bool ColorCombobox::colorDialogEnabled() const
{
	return _colorDialogEnabled;
}
