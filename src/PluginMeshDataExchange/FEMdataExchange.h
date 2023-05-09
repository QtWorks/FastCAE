#ifndef _FEMDATAEXCHANGE_H_
#define _FEMDATAEXCHANGE_H_

#include "meshDataExchangePlugin.h"
#include "MeshThreadBase.h"

#include <QHash>
#include <vtkCellType.h>

class vtkUnstructuredGrid;
class vtkPoints;

namespace MeshData {
	class MeshData;

	class MESHDATAEXCHANGEPLUGINAPI FEMdataExchange : public MeshThreadBase {
	public:
		FEMdataExchange(const QString& filename, MeshOperation operation, GUI::MainWindow* mw,
						int modelId = -1);
		~FEMdataExchange();

		bool read();
		bool write();
		void run();

	private:
		void appendNode(QStringList lineList, vtkPoints* vtkPoint);
		void appendElement(QStringList lineList);
		void elementTypeSelect(QString elementName, VTKCellType& type);

	private:
		QString				 m_fileName = {};
		MeshData*			 m_meshData = nullptr;
		int					 m_modelId;
		MeshOperation		 m_operation;
		vtkUnstructuredGrid* m_grid		 = nullptr;
		int					 Num		 = 0;
		QHash<int, int>		 m_pointHash = {};
		int					 m_pointId	 = 0;
	};
} // namespace MeshData

#endif
