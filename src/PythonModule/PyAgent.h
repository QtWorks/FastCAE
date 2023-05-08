#ifndef _PYAGENT_H_
#define _PYAGENT_H_

#include "PythonModuleAPI.h"
#include <QObject>
#include <QStringList>
#include "Common/Types.h"

namespace GUI
{
	class MainWindow;
}

namespace Py
{
	class PyInterpreter;
	class ScriptReader;
	class RecordThread;

	class PYTHONMODULEAPI PythonAgent : public QObject
	{
		Q_OBJECT
	public:
		static PythonAgent *getInstance();
		void initialize(GUI::MainWindow *m);
		void finalize();
		void submit(QString code, bool save = true);
		//后台执行，不在界面显示，也不保存
		void backstageExec(QString code);
		void submit(QStringList codes, bool save = true);
		void saveScript(QString fileName);
		bool execScript(QString fileName);
		void appCodeList(QString code);
		void lock();
		void unLock();
		bool isLocked();
		void appendOn();
		void appendOff();
		void execMessWinCode(QString code);
		QStringList getcodelist();
		void setNoGUI(bool nogui);

	signals:
		void printInfo(Common::Message type, QString m);
		void closeMainWindow();

	private:
		PythonAgent();
		~PythonAgent() = default;
		void connectSignals();

	private slots:
		void readerFinished();

	private:
		static PythonAgent *_instance;
		PyInterpreter *_interpreter{};
		RecordThread *_recordScript{};
		GUI::MainWindow *_mainWindow{};
		ScriptReader *_reader{};
		bool _islock{false};
		bool _append{true};

		bool _noGUI{false};
	};
}

#endif