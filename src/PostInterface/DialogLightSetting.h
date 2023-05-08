/**
* @file   DialogLightSetting.h
* @brief  渲染窗口的灯光设置
* @author XuXinwei
*/
#ifndef DIALOGLIGHTSETTING_H
#define DIALOGLIGHTSETTING_H

#include "PostRenderData/Macros.hxx"
#include <QDialog>
#include <QList>

ForwardDeclarNS(Ui,LightSettingDialog)
ForwardDeclar(vtkRenderer)
ForwardDeclar(vtkRenderWindow)
ForwardDeclar(vtkLight)
ForwardDeclar(QListWidgetItem)

class LightSettingDialog : public QDialog
{
    Q_OBJECT

public:
	explicit LightSettingDialog(vtkRenderer* renderer, vtkRenderWindow* renderWindow, QWidget *parent = nullptr);
    ~LightSettingDialog();

private:
	/**
	* @brief 初始化灯光列表
	*/
	void initLightList();

private slots:
	/**
	* @brief 添加按钮点击槽函数
	*/
	void on_addPushButton_clicked();
	/**
	* @brief 删除按钮点击槽函数
	*/
	void on_deletePushButton_clicked();
	/**
	* @brief 确认/刷新按钮点击槽函数
	*/
	void on_okPushButton_clicked();
	/**
	* @brief 颜色按钮点击槽函数
	*/
	void on_colorPushButton_clicked();
	/**
	* @brief 灯光列表项目点击槽函数
	*/
	void listWidgetItemClicked();

private:
    /**
    * @brief 灯光设置界面ui
    */
    Ui::LightSettingDialog *_ui;
	/**
	* @brief 灯光列表
	*/
	QList<vtkLight*> _lightList;
	/**
	* @brief 当前灯光
	*/
	vtkLight* _currentLight{ nullptr };
	/**
	* @brief 渲染画布
	*/
	vtkRenderer* _renderer;
	/**
	* @brief 渲染窗口
	*/
	vtkRenderWindow* _renderWindow;
};

#endif // DIALOGLIGHTSETTING_H
