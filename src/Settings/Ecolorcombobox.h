/**
 * @file ecolorcombobox.h
 * @brief 颜色选择下拉框类头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 17:39
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
#ifndef ECOLORCOMBOBOX_H
#define ECOLORCOMBOBOX_H

#include <qcolor.h>
#include <qcombobox.h>
//#include "ISPostShareAPI.h"

/**
 * @brief 颜色选择下拉框类
 * @note 由于基类QComboBox的clear方法不是虚函数，因此无法重载。如果在颜色对
 *       话框激活的情况下使用了clear方法清除复合框内的内容，则打开颜色对话框
 *       的项也会被清除，必须重新激活颜色对话框项。如果需要清除内容，必须使
 *       用本类提供的方法clearAllColors()
 * @since 2.5.0
 */
class EColorComboBox : public QComboBox
{
  Q_OBJECT
  Q_PROPERTY(bool colorDialogEnabled READ colorDialogEnabled
                 WRITE enableColorDialog)
public:
  /**
   * @brief 构造函数。构造一个颜色选择复合框对象
   * @param parent 父窗口
   * @since 2.5.0
   */
  EColorComboBox(QWidget *parent = 0);
  /**
   * @brief 获取当前选择的颜色
   * @return 当前选择的颜色
   * @since 2.5.0
   */
  QColor currentColor() const;
  /**
   * @brief 获取索引index指定的颜色。如果索引无效，则返回无效的颜色
   * @param index 要获取的颜色的索引
   * @return 获取的颜色
   * @since 2.5.0
   */
  QColor color(int index) const;
  /**
   * @brief 检查是否使用颜色选择对话框
   * @return 如果使用颜色选择对话框则返回true，否则返回false
   * @since 2.5.0
   */
  bool colorDialogEnabled() const;
  /**
   * @brief 获取适合显示本控件的尺寸
   * @return 适合显示本控件的尺寸
   * @since 2.5.0
   */
  QSize sizeHint() const;
  /**
   * @brief 检查一种颜色是否已经在本控件中了
   * @param color 要检查的颜色
   * @return 如果在，返回true，否则返回false
   * @since 2.5.0
   */
  bool hasColor(const QColor &color);
  /**
   * @brief 添加自定义颜色
   * @since 2.5.0
   */
  void appendOtherColor();
public slots:
  /**
   * @brief 清除列表内的所有颜色，与clear方法不同，该方法不清除颜色对话框项
   * @since 2.5.0
   */
  void clearAllColors();
  /**
   * @brief 在列表末尾添加一种颜色。如果这种颜色已经在列表内了，则直接返回
   * @param c    要添加的颜色
   * @param name 要添加的颜色的描述
   * @since 2.5.0
   */
  void appendColor(const QColor &c, const QString &name = QString());
  /**
   * @brief 在列表指定位置添加一种颜色。如果这种颜色已经在列表内了，则直接返回。如果要添加的位置不存在，则在列表末尾添加
   * @param c     要添加的颜色
   * @param name  要添加的颜色的描述
   * @param index 要添加颜色的位置
   * @since 2.5.0
   */
  void insertColor(const QColor &c, const QString &name = QString(),
                   int index = -1);
  /**
   * @brief 在当前列表的末尾添加预定义的（前景）颜色
   * @since 2.5.0
   */
  void appendPredefinedColors();
  /**
   * @brief 在当前列表的末尾添加预定义的（背景）颜色
   * @since 2.5.0
   */
  void appendBackgroundColors();

  /**
   * @brief 更新自定义颜色的图标
   * @param color 要作为自定义样色图标的颜色
   * @since 2.5.0
   */
  void updateOtherColor(const QColor &color);
  /**
   * @brief 设置是否使用颜色选择对话框。如果使用颜色选择对话框，会在列表的最后添加一项启动颜色选择对话框的项
   * @param enabled 如果为true则使用颜色选择对话框，否则不使用
   * @since 2.5.0
   */
  void enableColorDialog(bool enabled = true);
  /**
   * @brief 设置当前选择的颜色。如果这种颜色不在列表内，则直接返回
   * @param color 要设置为当前选择的颜色
   * @since 2.5.0
   */
  void setCurrentColor(const QColor &color);
signals:
  /**
   * @brief 当某种颜色被选中时发送这个信号
   * @param color 被选中的颜色
   * @since 2.5.0
   */
  void activated(const QColor &color);
  /**
   * @brief 当列表打开并且高亮显示某一种颜色时发送这个信号
   * @param color 被高亮显示的颜色
   * @since 2.5.0
   */
  void highlighted(const QColor &color);
private slots:
  void emitActivatedColor(int index);
  void emitHighlightedColor(int index);

private:
  /**
   * @brief 是否使用自定义颜色
   * @since 2.5.0
   */
  bool _colorDialogEnabled;
  QColor _lastActivated;
};

#endif
