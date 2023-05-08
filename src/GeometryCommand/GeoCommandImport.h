#ifndef GEOCOMMANDIMPORT_H_
#define GEOCOMMANDIMPORT_H_

#include "GeoCommandBase.h"
#include "ModuleBase/messageWindowBase.h"
//#include "Geometry/GeometrySet.h"

namespace GUI
{
	class MainWindow;
}

namespace Command
{
	class GEOMETRYCOMMANDAPI GeoCommandImport : public GeoCommandBase
	{
		Q_OBJECT
	public:
		GeoCommandImport(GUI::MainWindow *m, MainWidget::PreWindow *p);
		~GeoCommandImport() = default;

		void setFileName(QStringList name);
		void setExportFile(QString name);

		bool execute() override;
		void undo() override;
		void redo() override;
		void releaseResult() override;
		void IsRead(bool s);

	private:
		bool importGeometry();
		bool exportGeometry();
	signals:
		void showMessage(ModuleBase::Message);

	private:
		QStringList _importfileNames{};
		QString _exportfile{};
		QList<Geometry::GeometrySet *> _resSet{};
		GUI::MainWindow *_mw;
		bool _isRead{};
	};
}

#endif
