/**
 * @file PostConfigInfo.h
 * @brief 后处理配置信息类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:54
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
#ifndef _POST2DCONFIG_H_
#define _POST2DCONFIG_H_

#include "DataProperty/DataBase.h"
#include "ConfigOptionsAPI.h"
#include <QString>
#include <QStringList>
#include <QHash>

namespace ConfigOption
{
	class PostCurve;
	/**
	 * @brief 后处理配置信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI PostConfigInfo : public DataProperty::DataBase
	{
	public:
		PostConfigInfo() = default;
		~PostConfigInfo() = default;

		//		void setPost2DFile(QStringList name);
		QStringList getPost2DFile();
		QStringList get2DVariables(QString f);
		void setPost3DFile(QString f);
		QString getPost3DFile();
		// 		void set2DVariable(QStringList v);
		// 		QStringList get2DVariable();
		void setNodeScalarVariable(QStringList sca);
		QStringList getNodeScalarVariable();
		void setNodeVectorVariable(QStringList s);
		QStringList getNodeVectorVariable();
		void setCellScalarVariable(QStringList sca);
		QStringList getCellScalarVariable();
		void setCellVectorVariable(QStringList s);
		QStringList getCellVectorVariable();
		void appendPostCurve(PostCurve *c);
		QList<PostCurve *> getCurveList();
		PostCurve *getCurveByName(QString name);

	private:
		QList<PostCurve *> _curves{};
		QString _post3DFile{};
		//		QStringList _post2DVariable{};
		QStringList _postNodeScalarVariable{};
		QStringList _postCellScalarVariable{};
		QStringList _postNodeVectorVariable{};
		QStringList _postCellVectorVariable{};
	};

}

#endif
