/* 
* 
* @file   DialogRenderTitle.h
* @brief  后处理渲染标题设置
* @author XuXinwei
* 
*/
#ifndef DIALOGRENDERTITLE_H
#define DIALOGRENDERTITLE_H

#include "PostRenderData/Macros.hxx"
#include <QDialog>

ForwardDeclarNS(Ui,RenderTitleDialog)
ForwardDeclar(vtkTextWidget)
ForwardDeclar(vtkRenderWindow)

class RenderTitleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenderTitleDialog(vtkTextWidget* textWidget,vtkRenderWindow* renderWindow,QWidget *parent = nullptr);
    ~RenderTitleDialog();

private:
	/**
	* @brief 初始化标题设置界面
	*/
	void init();
	/**
	* @brief 确认修改
	*/
	void accept() override;

private slots:
	/**
	* @brief 颜色选择
	*/
	void on_colorPushButton_clicked();

private:
	/**
	* @brief 字体颜色
	*/
	QColor _color;

private:
    /**
    * @brief 标题设置界面
    */
    Ui::RenderTitleDialog *_ui;
	/**
	* @brief 标题
	*/
	vtkTextWidget* _textWidget{ nullptr };
	/**
	* @brief 渲染窗口
	*/
	vtkRenderWindow* _renderWindow{ nullptr };
};

#endif // DIALOGRENDERTITLE_H
