/**
 * @file TreeItemData.h
 * @brief 配置文件中树节点信息类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 11:00
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
#ifndef TREEITEMDATA_H
#define TREEITEMDATA_H

#include <QString>
#include <QStringList>
#include <QIcon>
#include "DataProperty/modelTreeItemType.h"
#include "ConfigOptionsAPI.h"

namespace ConfigOption
{
	/**
	 * @brief 配置文件中树节点信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI TreeItem
	{
	public:
		TreeItem() = default;
		~TreeItem() = default;

		void copy(TreeItem *item);

		void setText(const QString &text);
		void setType(const QString &type);
		void SetParent(const QString &parent);
		void appendContextMenu(const QString &menu);
		QString getText();
		QString getParent();
		TreeItemType getType();
		int getContextMenuCount();
		QString getContextMenuAt(const int index);
		void setIcon(const QString &icon);
		QString getIcon();
		void setChinese(QString c);
		QString getChinese();
		QStringList getContextMenu();
		void setDataID(int id);
		int getDataID();

	private:
		QString _text{};
		QString _parent{};
		QString _chinese{};
		QString _icon{};
		TreeItemType _type{TreeItemType::Undefined};
		QStringList _contextMenu{};
		int _dataID{-1};
	};

}

#endif
