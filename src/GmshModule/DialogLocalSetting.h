/**
 * @file DialogLocalSetting.h
 * @brief 局部网格加密对话框类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-04-01 09:23
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
#ifndef LOCALSETTING_DIALOG_H_
#define LOCALSETTING_DIALOG_H_

#include <QDialog>
#include <QList>
#include <QButtonGroup>
#include <QMultiHash>

class QTableWidget;

namespace Ui
{
	class LocalSettingDialog;
}

namespace GUI
{
	class MainWindow;
}

namespace MainWidget
{
	class PreWindow;
}

namespace GeometryWidget
{
	class GeoPointWidget;
}

namespace Geometry
{
	class GeometrySet;
}

enum LocalSettingType
{
	UnDefineType = 0,
	Points,
	FieldsBox,
	FieldsBall,
	FieldsCylinder,
	FieldsSolid,
	FieldsFrustum,
};

namespace Gmsh
{
	class LocalPoint;
	class GmshDialogBase;
	class LocalField;
	class LocalDensity;
	class Cylinder;
	/**
	 * @brief 局部网格加密对话框类
	 * @since 2.5.0
	 */
	class LocalSettingDialog : public QDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父级对话框
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @since 2.5.0
		 */
		LocalSettingDialog(GmshDialogBase *parent, GUI::MainWindow *m, MainWidget::PreWindow *p);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~LocalSettingDialog();

	signals:
		/**
		 * @brief 当使用指定实体区域进行网格加密，选中实体时会触发此信号
		 * @since 2.5.0
		 */
		void setSelectMode(int);
		/**
		 * @brief 选中实体时触发此信号
		 * @since 2.5.0
		 */
		void highLightGeometrySolidSig(Geometry::GeometrySet *, int, bool);
		//清空所有高亮对象
		void clearGeometryHighLightSig();

	private slots:
		/**
		 * @brief 确认按键响应槽函数
		 * @since 2.5.0
		 */
		void on_okPushButton_clicked();
		/**
		 * @brief 取消按键响应槽函数
		 * @since 2.5.0
		 */
		void on_cancelPushButton_clicked();
		/**
		 * @brief 实体拾取按键响应槽函数
		 * @since 2.5.0
		 */
		void on_geoSelectSurface_clicked();
		/**
		 * @brief 加密类型选择下拉框选项切换响应槽函数
		 * @param type 下拉框选项的选择项索引
		 * @since 2.5.0
		 */
		void updateInterface(int type);
		/**
		 * @brief 自定义轴线响应槽函数
		 * @since 2.5.0
		 */
		void onCustomChecked();
		// void changeData(int, int);
		void shapeSlected(Geometry::GeometrySet *set, int index);

	private:
		void showEvent(QShowEvent *e) override;

		/**
		 * @brief 根据不同的下拉选项更新对话框界面
		 * @since 2.5.0
		 */
		void updateLocalInterface();
		void updatePointsInterface();
		void updateBoxInterface();
		void updateBallInterface();
		void updateCylinderInterface();
		void updateCylinderAxisData(double xa, double ya, double za);
		void updateValueInterface(int n);
		void showValueInterface(int n);
		void hideValueInterface(int n);
		void updateSolidFieldInterface();
		void updateFrustumFieldInterface();
		void clearInterfaceData();
		void cylinderSelectVisiable(bool b = false);
		void cylinderAxisVisiable(bool b = false);
		/*更新不同类型的局部密度界面*/

		/*添加局部密度数据，修改局部密度数据*/
		void addLocalData(LocalDensity *loc);
		void addPointsData();
		void addBoxData();
		void addBallData();
		void addCylinderData();
		void addSolidFieldsData();
		void addFrustumFieldData();
		/*添加局部密度数据，修改局部密度数据*/

		/*数据信息展示*/
		// void updateTab();
		// void updateLocals(int n);
		// void deleteItem(int row);
		// void operateLocalData(int row);
		/*数据信息展示*/

	private:
		Ui::LocalSettingDialog *_ui{};
		QList<LocalPoint *> *_points{};
		GeometryWidget::GeoPointWidget *_pointWidget{};
		// QTableWidget* _tab{};
		QList<LocalField *> *_fields{};
		LocalSettingType _localType{Points};
		QList<LocalDensity *> *_locals{};
		LocalDensity *_currentLocal{};
		bool _selectSolid{false};

		QMultiHash<Geometry::GeometrySet *, int> _solidHash{};
	};
}

#endif