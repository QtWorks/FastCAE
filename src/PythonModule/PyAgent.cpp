#include <Python.h>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <wchar.h>
#include "PyAgent.h"
#include "MainWindow/MainWindow.h"
#include "PyInterpreter.h"
#include "RecordScript.h"
#include "ScriptReader.h"

#ifdef Q_OS_WIN32
#include <atlconv.h>
#endif

#include <locale.h>

namespace Py {
	PythonAgent* PythonAgent::_instance = nullptr;

	PythonAgent* PythonAgent::getInstance()
	{
		if(_instance == nullptr)
			_instance = new PythonAgent;

		return _instance;
	}

	void PythonAgent::connectSignals()
	{
		connect(this, SIGNAL(printInfo(Common::Message, QString)), _mainWindow,
				SIGNAL(printMessageSig(Common::Message, QString)));
		connect(this, SIGNAL(closeMainWindow()), _mainWindow, SIGNAL(closeMainWindow()));
	}

	void PythonAgent::appCodeList(QString code)
	{
		if(!_append)
			return;
		emit printInfo(Common::Message::Python, code);
		_interpreter->codeListAppend(code);
	}

	PythonAgent::PythonAgent()
	{
		_interpreter = new PyInterpreter;
	}

	void PythonAgent::initialize(GUI::MainWindow* m)
	{
		_mainWindow = m;
		connectSignals();
		Py_SetProgramName(L"FastCAE");
		Py_Initialize();
		if(!_interpreter->init(this))
			emit printInfo(Common::Message::Error, tr("Python Initialize failed!"));
		else
			emit printInfo(Common::Message::Normal, tr("Python Initialized"));
		_recordScript = new RecordThread;
		_recordScript->start();
	}

	void PythonAgent::finalize()
	{
		if(_reader != nullptr) {
			if(_reader->isRunning()) {
				_reader->stop();
				_reader->quit();
				_reader->wait();
			}
			while(_reader->isRunning())
				;
			delete _reader;
			_reader = nullptr;
		}

		_recordScript->stop();
		_recordScript->quit();
		_recordScript->wait();
		delete _recordScript;

		if(_interpreter != nullptr)
			delete _interpreter;

		if(Py_IsInitialized())
			Py_Finalize();
	}

	void PythonAgent::submit(QString code, bool s)
	{
		emit printInfo(Common::Message::Python, code);
		//		lock();
		int	 ok = _interpreter->execCode(code, s);
		if(ok == -1) {
			if(_reader != nullptr)
				_reader->restart();
		}
	}

	void PythonAgent::submit(QStringList codes, bool save /*= true*/)
	{
		const int n = codes.size();
		for(int i = 0; i < n; ++i) {
			this->submit(codes.at(i), save);
		}
	}

	void PythonAgent::saveScript(QString fileName)
	{
		QFile file(fileName);
		if(!file.open(QIODevice::Text | QIODevice::WriteOnly)) {
			emit printInfo(Common::Message::Error, tr("Script open failed"));
			return;
		}
		QTextStream stream(&file);
		const int	n = _interpreter->getCodeCount();
		for(int i = 0; i < n; ++i) {
			QString s = _interpreter->getCodeAt(i);
			stream << s << endl;
		}
		file.close();
		emit printInfo(Common::Message::Normal, tr("Script Saved %1").arg(fileName));
	}

	bool PythonAgent::execScript(QString fileName)
	{
		if(_reader != nullptr)
			return false;
		_reader = new ScriptReader(fileName, this);
		_recordScript->pause();
		connect(_reader, SIGNAL(finished()), this, SLOT(readerFinished()));
		_reader->start();
		return true;
	}

	void PythonAgent::readerFinished()
	{
		if(_reader != nullptr)
			delete _reader;
		_reader = nullptr;
		_recordScript->reStart();
		if(_noGUI)
			emit closeMainWindow();
	}

	void PythonAgent::lock()
	{
		if(_reader != nullptr)
			_reader->pause();
	}

	void PythonAgent::unLock()
	{
		if(_reader != nullptr)
			_reader->restart();
	}

	bool PythonAgent::isLocked()
	{
		return _islock;
	}

	QStringList PythonAgent::getcodelist()
	{
		if(_interpreter != nullptr)
			return _interpreter->getCode();
		return QStringList();
	}

	void PythonAgent::setNoGUI(bool nogui)
	{
		_noGUI = nogui;
	}

	void PythonAgent::appendOn()
	{
		_append = true;
	}
	void PythonAgent::appendOff()
	{
		_append = false;
	}

	void PythonAgent::execMessWinCode(QString code)
	{
		_interpreter->execCode(code);
	}

	void PythonAgent::backstageExec(QString code)
	{
		_interpreter->execCode(code, false);
	}
} // namespace Py