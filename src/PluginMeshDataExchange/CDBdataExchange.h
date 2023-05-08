#ifndef _CDBDATAEXCHANGE_H_
#define _CDBDATAEXCHANGE_H_

#include "meshDataExchangePlugin.h"
#include "MeshThreadBase.h"
#include <QHash>

class vtkUnstructuredGrid;
class vtkPoints;

namespace MeshData
{
	class MeshData;

	class MESHDATAEXCHANGEPLUGINAPI CDBdataExchange:public MeshThreadBase
	{
	public:
		CDBdataExchange(const QString &filename, MeshOperation operation, GUI::MainWindow *mw, int modelId = -1);
		~CDBdataExchange();

		void run();
		bool read();
		bool write();

	private:
		bool readNode(QString line,QStringList lineList, vtkPoints* points);
		bool readElement(QStringList lineList);
	private:
		MeshOperation m_operation = MESH_NONE;
		QString m_filePath = {};
		MeshData* m_meshData = nullptr;
		vtkUnstructuredGrid* m_grid = nullptr;
		int m_modelId = -1;
		QHash<int,int> m_pointHash;
		int m_pointId = 0;
	};
}

#endif
