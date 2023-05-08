/**
 * 
 * @file DialogSetBackgroundColor.h
 * @brief  背景颜色修改窗口
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2021-12-05
 * 
 */
#ifndef DIALOGSETBACKGROUND_H
#define DIALOGSETBACKGROUND_H

#include <QDialog>
#include "PostRenderData/Macros.hxx"
#include <QColor>

ForwardDeclarNS(Ui,SetBackgroundColorDialog)
ForwardDeclar(vtkRenderer)
ForwardDeclar(vtkRenderWindow)

class SetBackgroundColorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetBackgroundColorDialog(QWidget *parent = nullptr);
	SetBackgroundColorDialog(vtkRenderer* renderer, vtkRenderWindow* renderWin);
    ~SetBackgroundColorDialog();

	
private slots:
    /**
     * @brief 顶部颜色按钮点击事件
     */
	void on_topColorPushButton_clicked();
    /**
     * @brief 底部颜色按钮点击事件
     */
	void on_bottomColorPushButton_clicked();

private:
    /**
     * @brief 确定按钮点击事件
     */
    void accept() override;


private:
    /**
    * @brief 背景颜色设置界面ui
    */
    Ui::SetBackgroundColorDialog *_ui;
    /**
    * @brief 渲染窗口
    */
    vtkRenderWindow* _renderWindow{nullptr};
    /**
    * @brief 渲染画布
    */
    vtkRenderer* _renderer{};
    /**
    * @brief 顶部颜色
    */
    QColor _topColor{};
    /**
    * @brief 底部颜色
    */
    QColor _bottomColor{};
};

#endif // DIALOGSETBACKGROUND_H
