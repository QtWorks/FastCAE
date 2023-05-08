/**
 * 
 * @file AnimationToolBar.h
 * @brief 动画工具条
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2021-12-05
 * 
 */
#ifndef _ANIMATIONTOOL_BAR_H_
#define _ANIMATIONTOOL_BAR_H_

#include <QToolBar>
#include "PostInterfaceAPI.h"
#include "PostRenderData/Macros.hxx"
#include <QAction>
#include <QQueue>
#include <QMutex>
#include "AniGlobalVar.h"

ForwardDeclar(QSpinBox)
ForwardDeclar(QLabel)
ForwardDeclar(GenerateAnimation)
ForwardDeclarNS(GUI, MainWindow)
ForwardDeclarNS(Post,RenderDataObject)
ForwardDeclarNS(Post,RenderDataImportUnSteady)
ForwardDeclarNS(Post,AniThread)
ForwardDeclarNS(Post,PostTreeWidget)

extern QMutex g_mutex;
extern QQueue<Post::RenderDataImportUnSteady*> g_qUnSteady;

namespace Post {
	class POSTINTERFACEAPI  AnimationToolBar : public QToolBar
	{
		Q_OBJECT
	public:
		AnimationToolBar(GUI::MainWindow* mainWindow, PostTreeWidget* tree);
		~AnimationToolBar() = default;

		bool SetCurrObj(RenderDataObject* obj);

		void setAviSetting(QString aviSavePath, int fps);
		void getAviSetting(QString& aviSavePath, int& fps);

		void frameTo(int index);

		int getCurrentObjectID();

		void reTranslate();

	signals:
		/**
		 * @brief 保存avi信号
		 */
		void sig_generateAvi();

		/**
		 * @brief 结束保存avi信号
		 */
		void sig_terminateGenerateAvi();

	public Q_SLOTS:
		/**
		 * @brief 当前数据对象发生改变
		 * @param  vobj    当前的数据对象
		 */
		void on_currentRenderDataChanged(RenderDataObject* vobj);

		/**
		 * @brief 第一帧
		 */
		void on_FirstFrame();

		/**
		 * @brief 上一帧
		 * @param vobj 当前的数据对象
		 */
		void on_PreviousFrame();

		/**
		 * @brief 播放动画
		 */
		void on_RunAnimation();

		/**
		 * @brief 下一帧
		 * @param vobj 前的数据对象
		 */
		void on_NextFrame();

		/**
		 * @brief 最后一帧
		 */
		void on_LastFrame();

		void slot_saveAnimation(RenderDataObject* obj, QString file, int fps);

	private:
		void initToolBar();

	private Q_SLOTS:
		/**
		 * @brief spinBox值改变
		 */
		void on_SpinBoxValueChanged(int i);
		void on_FirstFrame(RenderDataObject* obj);
		void on_PreviousFrame(RenderDataObject* obj);
		void on_RunAnimation(RenderDataObject* obj, int index = 0);
		void on_NextFrame(RenderDataObject* obj);
		void on_LastFrame(RenderDataObject* obj);
		void on_stopAnimation(RenderDataObject* obj,int index);
		void slot_runAnimation();


	private:
		GUI::MainWindow* _mainWindow{};
		PostTreeWidget* _treeWidget{};
		//当前的文件编号
		QSpinBox* _spinBox{};
		//总共数目Label
		QLabel* _totalLabel{};
		QLabel* _stepLabel{};
		//当前数据对象
		RenderDataImportUnSteady* _unSteadyObj{};

		//动画播放action
		QAction* _aniAction{};
		QAction* _firstAction{};
		QAction* _lastAction{};
		QAction* _nextAction{};
		QAction* _preAction{};
		//动画的暂停播放标志
		volatile bool _runAnimation{ true };

		//文件读取线程
		AniThread* _aniThread{};

		//动画生成信息
		AviSetting* _aniAviTool{};
		//生成动画
		GenerateAnimation* _generateAni{};

		bool _runFinished{ false };
	};

}
#endif
