#include "TemplateReplacer.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include "DataProperty/DataBase.h"
#include "DataProperty/ParameterBase.h"
#include "MeshData/meshSingleton.h"
#include "MeshData/meshKernal.h"
#include "ModelData/modelDataBase.h"
#include "IOConfig.h"
#include <QDebug>

namespace IO
{
	TempalteReplacer::TempalteReplacer(DataProperty::DataBase *data)
	{
		_data = data;
	}

	void TempalteReplacer::appendFile(QString f)
	{
		_fileNames.append(f);
	}

	void TempalteReplacer::replace()
	{
		const int n = _fileNames.size();
		for (int i = 0; i < n; ++i)
		{
			_text.clear();
			QString s = _fileNames.at(i);
			qDebug() << s;
			replaceFile(s);
			write(s);
		}
	}

	void TempalteReplacer::replaceFile(QString s)
	{
		QFile file(s);
		if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
			return;
		QTextStream stream(&file);

		QRegExp regExp("%.*%");
		regExp.setMinimal(true);
		QString line;
		while (!stream.atEnd())
		{
			line = stream.readLine();
			int pos = -1;
			do
			{
				pos = regExp.indexIn(line);
				QStringList variables = regExp.capturedTexts();
				for (int i = 0; i < variables.size(); ++i)
				{
					QString variable = variables.at(i);
					if (variable.isEmpty())
						continue;
					QString va = variable.remove("%");

					QString t = this->getReplaceString(va);
					line.replace(variables.at(i), t);
				}
			} while (pos > -1);

			_text.append(line);
		}
		file.close();
	}

	void TempalteReplacer::write(QString f)
	{
		if (_text.isEmpty())
			return;

		QFile file(f);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream stream(&file);
		for (int i = 0; i < _text.size(); ++i)
		{
			QString s = _text.at(i);
			stream << s << endl;
		}
		file.close();
	}

	QString TempalteReplacer::getReplaceString(QString va)
	{
		QString res = QString("!!%1!!").arg(va);
		DataProperty::ParameterBase *p = _data->getParameterByName(va);
		if (p != nullptr)
		{
			res = p->valueToString();
		}
		else if (va == "MESHPATH")
		{
			MeshData::MeshKernal *k = MeshData::MeshData::getInstance()->getKernalAt(0);
			if (nullptr != k)
				res = k->getPath();
		}
		else if (va == "RESULTPATH")
		{
			ModelData::ModelDataBase *m = dynamic_cast<ModelData::ModelDataBase *>(_data);
			res = m->getPath();
		}
		else
		{
			REPLACEKEYWORDFUN f = IOConfigure::getKeyWordsReplacer(va);
			if (f != nullptr)
				res = f(va, dynamic_cast<ModelData::ModelDataBase *>(_data));
		}
		return res;
	}

}
