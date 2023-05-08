#include "ScriptReader.h"
#include "PyAgent.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegExp>
#include "Common/Types.h"

namespace Py
{

	ScriptReader::ScriptReader(QString fileName, PythonAgent *agent)
	{
		_fileName = fileName;
		_agent = agent;
	}

	ScriptReader::~ScriptReader()
	{
	}

	void ScriptReader::run()
	{
		QFile file(_fileName);
		if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
		{
			emit _agent->printInfo(Common::Message::Error, tr("Script open failed"));
			return;
		}
		QTextStream stream(&file);
		while (!stream.atEnd())
		{
			if (_stop)
				return;
			if (_lockCount > 0)
				continue;
			QString line = stream.readLine().simplified();

			qDebug() << "read: " << line;
			if (line.isEmpty())
				continue;
			pause();
			_agent->submit(line, true);

			if (isPythonObj(line) && !line.toLower().contains("thread"))
				restart();
		}
		file.close();
		if (_stop)
			return;

		while (_lockCount > 0)
			this->sleep(1);

		if (_stop)
			return;
		emit _agent->printInfo(Common::Message::Normal, tr("Script Executed %1").arg(_fileName));
	}

	void ScriptReader::pause()
	{
		//	_mutex.lock();
		_lockCount++;
		qDebug() << "lock";
	}
	void ScriptReader::restart()
	{
		// 		_mutex.tryLock();
		// 		_mutex.unlock();
		_lockCount--;
		if (_lockCount < 0)
			_lockCount = 0;
		qDebug() << "unlock";
	}

	void ScriptReader::stop()
	{
		_stop = true;
		this->quit();
		//		this->wait();
	}

	bool ScriptReader::isPythonObj(QString line)
	{
		if (line.contains("="))
			return true;
		QStringList cs = line.split(".");
		if (cs.at(0).toLower() == cs.at(0))
			return true;
		return false;
	}

}