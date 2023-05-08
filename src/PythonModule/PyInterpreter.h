#ifndef _PYINTERPRETER_H_
#define _PYINTERPRETER_H_

#include <QObject>
#include <QStringList>

namespace GUI
{
	class MainWindow;
}

namespace Py
{
	class PythonAgent;

	class PyInterpreter : public QObject
	{
		Q_OBJECT
	public:
		PyInterpreter() = default;
		~PyInterpreter() = default;

		bool init(PythonAgent *agent);
		int execCode(QString code, bool save = true);
		void execFile(QString file);
		int getCodeCount();
		QString getCodeAt(int i);
		void codeListAppend(QString qs);
		QStringList getCode();

	private:
		QStringList _codelist{};
		PythonAgent *_agent{};
	};

}

#endif