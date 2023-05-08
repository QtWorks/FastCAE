#ifndef _GENERATEANIMATION_H_
#define _GENERATEANIMATION_H_

#include <QObject>
#include "AniGlobalVar.h"

class vtkAVIWriter;
class vtkRenderWindow;

class GenerateAnimation : public QObject
{
	Q_OBJECT
public:
	GenerateAnimation(AviSetting* setting);
	~GenerateAnimation();

	void setRenderWindow(vtkRenderWindow* renderWindow);

public Q_SLOTS:

	/**
	 * @brief 生成动画
	 * @param index 帧索引
	**/
	void on_generate();

	/**
	 * @brief 终止生成
	**/
	void on_finishSaveAvi();

private:

	//开始生成标志
	bool _startGenerate{ false };

	AviSetting* _aviSetting;

	vtkAVIWriter* _aviWriter{};
	
	vtkRenderWindow* _renderWindow{};
};

#endif