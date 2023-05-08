#include "AnimationToolBar.h"
#include "PostTreeWidget.h"
#include "AniThread.h"
#include "AniGlobalVar.h"
#include "GenerateAnimation.h"
#include "RenderWindowManager.h"
#include "GraphWidget.h"
#include "MainWindow/MainWindow.h"
#include "MainWidgets/ControlPanel.h"
#include "PostRenderData/RenderDataImportUnSteady.h"
#include "PythonModule/PyAgent.h"
#include <QLabel>
#include <QSpinBox>
#include <QApplication>
#include <QDebug>

namespace Post
{
	AnimationToolBar::AnimationToolBar(GUI::MainWindow *mainWindow, PostTreeWidget *tree)
		: QToolBar(mainWindow), _mainWindow(mainWindow), _treeWidget(tree)
	{
		_aniAviTool = new aviSetting;

		initToolBar();

		_generateAni = new GenerateAnimation(_aniAviTool);
		connect(_treeWidget, SIGNAL(currentRenderDataChanged(RenderDataObject *)), this, SLOT(on_currentRenderDataChanged(RenderDataObject *)));
		connect(this, SIGNAL(sig_generateAvi()), _generateAni, SLOT(on_generate()));
		connect(this, SIGNAL(sig_terminateGenerateAvi()), _generateAni, SLOT(on_finishSaveAvi()));
	}

	bool AnimationToolBar::SetCurrObj(RenderDataObject *obj)
	{
		_unSteadyObj = dynamic_cast<RenderDataImportUnSteady *>(obj->getRootViewObject());
		//		_unSteadyObj = dynamic_cast<RenderDataImportUnSteady*>(obj);
		if (_unSteadyObj == nullptr)
			return false;
		return true;
	}

	void AnimationToolBar::on_currentRenderDataChanged(RenderDataObject *vobj)
	{
		auto rObj = vobj->getRootViewObject();
		if (_unSteadyObj == rObj)
			return;
		_unSteadyObj = dynamic_cast<RenderDataImportUnSteady *>(rObj);
		// 		if (_unSteadyObj == vobj) return;
		// 		_unSteadyObj = dynamic_cast<RenderDataImportUnSteady*>(vobj);
		this->setEnabled(false);
		if (_unSteadyObj == nullptr)
			return;

		const int n = _unSteadyObj->getTotalCount();
		if (n < 2)
			return;
		this->setEnabled(true);

		_totalLabel->setText(QString(tr("Total: %1")).arg(n));
		_spinBox->setMaximum(n - 1);
		const int currentIndex = _unSteadyObj->getCurrentIndex();
		_spinBox->setValue(currentIndex);
	}

	void AnimationToolBar::on_FirstFrame()
	{
		int totalCount = _unSteadyObj->getTotalCount();
		if (totalCount < 2)
			return;
		_spinBox->setValue(0);
	}

	void AnimationToolBar::on_FirstFrame(RenderDataObject *obj)
	{
		if (SetCurrObj(obj))
			on_FirstFrame();
	}

	void AnimationToolBar::on_PreviousFrame()
	{
		int totalCount = _unSteadyObj->getTotalCount();
		if (totalCount < 2)
			return;
		int currIndex = _spinBox->value();
		if (currIndex <= 0)
			return;
		_spinBox->setValue(currIndex - 1);
	}

	void AnimationToolBar::on_PreviousFrame(RenderDataObject *obj)
	{
		if (SetCurrObj(obj))
			on_PreviousFrame();
	}

	void AnimationToolBar::on_RunAnimation()
	{
		int totalCount = _unSteadyObj->getTotalCount();
		if (totalCount < 2)
			return;

		if (_aniAction->text() == tr("run"))
		{
			_aniThread = new AniThread;
			_aniAction->setIcon(QIcon("://QUI/post/stop.png"));
			_aniAction->setText(tr("stop"));
			_runAnimation = true;
		}
		else
		{
			_aniAction->setIcon(QIcon("://QUI/post/run.png"));
			_aniAction->setText(tr("run"));
			_runAnimation = false;

			_spinBox->setValue(_unSteadyObj->getCurrentIndex());
			_aniThread->stop(true);
			_aniThread->quit();
			delete _aniThread;
			_aniThread = nullptr;

			emit sig_terminateGenerateAvi();

			return; //返回
		}

		int currIndex = _unSteadyObj->getCurrentIndex();

		if (currIndex == totalCount - 1)
		{
			currIndex = -1; // 从索引0开始播放
		}

		g_qUnSteady.clear();
		_aniThread->initThread(currIndex, totalCount - 1, _unSteadyObj);
		_aniThread->start();
		QThread::msleep(20);

		while ((currIndex < totalCount - 1) && _runAnimation)
		{
			while (true)
			{
				if (g_qUnSteady.size() == 1)
				{
					g_mutex.lock();
					_unSteadyObj = g_qUnSteady.dequeue();
					_unSteadyObj->update();
					int winID = _unSteadyObj->getRenderWinID();
					auto graphWindow = RenderWindowManager::getInstance()->getRenderWindowByID(winID);
					if (graphWindow == nullptr)
					{
						g_mutex.unlock();
						return;
					}
					_spinBox->blockSignals(true);
					_spinBox->setValue(_unSteadyObj->getCurrentIndex());
					_spinBox->blockSignals(false);
					_generateAni->setRenderWindow(graphWindow->getRenderWindow());
					graphWindow->reRender();
					emit sig_generateAvi();
					g_mutex.unlock();
					break;
				}

				if (!_runAnimation)
				{
					_spinBox->setValue(_unSteadyObj->getCurrentIndex());
					_aniThread->stop(true);
					_aniThread->quit();
					delete _aniThread;
					_aniThread = nullptr;
					emit sig_terminateGenerateAvi();
					return;
				}

				qApp->processEvents();
			}

			currIndex++;
			/* 单线程
			_spinBox->setValue(++currIndex);
			qApp->processEvents();
			*/
		}

		//播放完一轮之后恢复为可播放状态
		if (currIndex == totalCount - 1)
		{
			//线程关闭
			if (_aniThread != nullptr)
			{
				_spinBox->setValue(_unSteadyObj->getCurrentIndex());
				_aniThread->stop(true);
				_aniThread->quit();
				delete _aniThread;
				_aniThread = nullptr;
			}

			_aniAction->setIcon(QIcon("://QUI/post/run.png"));
			_aniAction->setText(tr("run"));

			//发送结束信号
			emit sig_terminateGenerateAvi();
		}
	}

	void AnimationToolBar::on_RunAnimation(RenderDataObject *obj, int index)
	{
		if (SetCurrObj(obj))
		{
			this->frameTo(index);
			qApp->processEvents();
		}
	}

	void AnimationToolBar::on_NextFrame()
	{
		int totalCount = _unSteadyObj->getTotalCount();
		if (totalCount < 2)
			return;
		int currIndex = _spinBox->value();
		if (currIndex >= (totalCount - 1))
			return;
		_spinBox->setValue(currIndex + 1);
	}

	void AnimationToolBar::on_NextFrame(RenderDataObject *obj)
	{
		if (SetCurrObj(obj))
			on_NextFrame();
	}

	void AnimationToolBar::on_LastFrame()
	{
		int totalCount = _unSteadyObj->getTotalCount();
		if (totalCount < 2)
			return;
		_spinBox->setValue(totalCount - 1);
	}

	void AnimationToolBar::on_LastFrame(RenderDataObject *obj)
	{
		if (SetCurrObj(obj))
			on_LastFrame();
	}

	void AnimationToolBar::slot_saveAnimation(RenderDataObject *obj, QString file, int fps)
	{
		if (SetCurrObj(obj))
		{
			this->setAviSetting(file, fps);
			on_RunAnimation();
		}
	}

	void AnimationToolBar::on_stopAnimation(RenderDataObject *obj, int index)
	{
		if (SetCurrObj(obj))
			this->frameTo(index);
	}

	void AnimationToolBar::slot_runAnimation()
	{
		if (_aniAction->text() == tr("run"))
		{
			_aniAction->setIcon(QIcon("://QUI/post/stop.png"));
			_aniAction->setText(tr("stop"));
			_runAnimation = true;
		}
		else
		{
			_aniAction->setIcon(QIcon("://QUI/post/run.png"));
			_aniAction->setText(tr("run"));
			_runAnimation = false;
		}

		int totalCount = _unSteadyObj->getTotalCount();
		if (totalCount < 2)
			return;

		auto index = _spinBox->value();
		if (index < 0 || index >= totalCount)
			return;
		if (index == (totalCount - 1))
			index = 0;

		for (index; index < totalCount; index++)
		{
			if (!_runAnimation)
				break;
			_runFinished = false;
			QString code = QString("PostProcess.runAnimation(%1,%2)").arg(_unSteadyObj->getID()).arg(index);
			Py::PythonAgent::getInstance()->submit(code);
			_runFinished = true;
		}

		// 		if (_runFinished && !_runAnimation)
		// 		{
		// 			QString code = QString("PostProcess.stopAnimation(%1,%2)").arg(_unSteadyObj->getID()).arg(_spinBox->value());
		// 			Py::PythonAgent::getInstance()->submit(code);
		//
		// 			return;
		// 		}

		if (index == totalCount)
		{
			_aniAction->setIcon(QIcon("://QUI/post/run.png"));
			_aniAction->setText("run");
			_runAnimation = false;
		}
	}

	void AnimationToolBar::initToolBar()
	{
		auto addAction = [=](QString icon, QString text) -> QAction *
		{
			auto act = new QAction(this);
			act->setObjectName("QAction");
			act->setText(text);
			act->setIcon(QIcon(icon));
			this->addAction(act);
			return act;
		};

		_firstAction = addAction("://QUI/post/first.png", QString(tr("first")));
		_preAction = addAction("://QUI/post/previous.png", QString(tr("previous")));
		_aniAction = addAction("://QUI/post/run.png", QString(tr("run")));
		_nextAction = addAction("://QUI/post/next.png", QString(tr("next")));
		_lastAction = addAction("://QUI/post/end.png", QString(tr("last")));

		connect(_firstAction, &QAction::triggered, [=]
				{
			auto id = _unSteadyObj->getID();
			QString code = QString("PostProcess.firstFrame(%1)").arg(id);
			Py::PythonAgent::getInstance()->submit(code); });
		connect(_preAction, &QAction::triggered, [=]
				{
			auto id = _unSteadyObj->getID();
			QString code = QString("PostProcess.proviousFrame(%1)").arg(id);
			Py::PythonAgent::getInstance()->submit(code); });
		connect(_aniAction, SIGNAL(triggered()), this, SLOT(slot_runAnimation()));
		connect(_nextAction, &QAction::triggered, [=]
				{
			auto id = _unSteadyObj->getID();
			QString code = QString("PostProcess.nextFrame(%1)").arg(id);
			Py::PythonAgent::getInstance()->submit(code); });
		connect(_lastAction, &QAction::triggered, [=]
				{
			auto id = _unSteadyObj->getID();
			QString code = QString("PostProcess.lastFrame(%1)").arg(id);
			Py::PythonAgent::getInstance()->submit(code); });
		// 		connect(actFirst, SIGNAL(triggered()), this, SLOT(on_FirstFrame()));
		// 		connect(actPre, SIGNAL(triggered()), this, SLOT(on_PreviousFrame()));
		// 		connect(_aniAction, SIGNAL(triggered()), this, SLOT(on_RunAnimation()));
		// 		connect(actNext, SIGNAL(triggered()), this, SLOT(on_NextFrame()));
		// 		connect(actLast, SIGNAL(triggered()), this, SLOT(on_LastFrame()));

		this->addSeparator();

		QAction *action = nullptr;
		_stepLabel = new QLabel(this);
		_stepLabel->setText(tr("Step:"));
		action = this->addWidget(_stepLabel);
		action->setObjectName("QWidget");

		_spinBox = new QSpinBox(this);
		_spinBox->setMaximum(1);
		_spinBox->setSingleStep(1);
		action = this->addWidget(_spinBox);
		action->setObjectName("QWidget");
		connect(_spinBox, SIGNAL(valueChanged(int)), this, SLOT(on_SpinBoxValueChanged(int)));

		_totalLabel = new QLabel(this);
		_totalLabel->setText(QString(tr("Total: 0")));
		action = this->addWidget(_totalLabel);
		action->setObjectName("QWidget");

		this->addSeparator();
		this->setEnabled(false);
	}

	void AnimationToolBar::on_SpinBoxValueChanged(int i)
	{
		auto rootObj = _unSteadyObj->getRootViewObject();
		auto rootObject = dynamic_cast<RenderDataImportUnSteady *>(rootObj);
		if (rootObject == nullptr)
			return;
		rootObject->setAnimationIndex(i);
		_unSteadyObj->update();

		// refresh window
		int winID = _unSteadyObj->getRenderWinID();
		auto graphWindow = RenderWindowManager::getInstance()->getRenderWindowByID(winID);
		if (graphWindow == nullptr)
			return;
		graphWindow->reRender();
	}

	void AnimationToolBar::setAviSetting(QString aviSavePath, int fps)
	{
		_aniAviTool->saveFlag = true;
		_aniAviTool->aviFilePath = aviSavePath;
		_aniAviTool->frameRate = fps;
	}

	void AnimationToolBar::getAviSetting(QString &aviSavePath, int &fps)
	{
		aviSavePath = _aniAviTool->aviFilePath;
		fps = _aniAviTool->frameRate;
	}

	void AnimationToolBar::frameTo(int index)
	{
		int totalCount = _unSteadyObj->getTotalCount();
		if (index < 0 || index >= totalCount)
			return;
		_spinBox->setValue(index);
	}

	int AnimationToolBar::getCurrentObjectID()
	{
		if (_unSteadyObj == nullptr)
			return -1;
		return _unSteadyObj->getID();
	}

	void AnimationToolBar::reTranslate()
	{
		_aniAction->setText(tr("run"));
		_firstAction->setText(tr("first"));
		_preAction->setText(tr("previous"));
		_nextAction->setText(tr("next"));
		_lastAction->setText(tr("last"));
		_stepLabel->setText(tr("Step:"));
		_totalLabel->setText(tr("Total: 0"));
	}

}
