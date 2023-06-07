#include "PostInfoWidget.h"

#include "PostRenderData/RenderDataAlgorithm.h"
#include "PostRenderData/RenderDataImportSteady.h"
#include "PostRenderData/RenderDataImportUnSteady.h"
#include "PostRenderData/RenderDataManager.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/RenderProperty.h"
#include "ui_PostInfoWidget.h"

#include <QDebug>
#include <QLabel>
#include <QStringList>

namespace Post {

	PostInfoWidget::PostInfoWidget(GUI::MainWindow* m, QWidget* parent)
		: _ui(new Ui::PostInfoWidget)
		, _parent(parent)
		, _mainWindow(m)
	{
		_ui->setupUi(this);
		_dataManager = RenderDataManager::getInstance();
		_ui->tableWidget->setColumnCount(4);
		QStringList header;
		header << tr("Property") << tr("Name") << tr("Type") << tr("Range");
		_ui->tableWidget->setHorizontalHeaderLabels(header);
		_ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		_ui->tableWidget->verticalHeader()->setVisible(false);
	}

	PostInfoWidget::~PostInfoWidget()
	{
		delete _ui;
	}

	QString PostInfoWidget::enumToString(Post::ObjType type)
	{
		QString types;
		if(type == Post::ObjType::Alg) {
			types = "Alg";
		} else if(type == Post::ObjType::Imp) {
			types = tr("Imp");
		} else if(type == Post::ObjType::TNone) {
			types = "TNone";
		}
		return types;
	}

	void PostInfoWidget::reTranslate()
	{
		QStringList header;
		header.append(tr("Property"));
		header.append(tr("Name"));
		header.append(tr("Type"));
		header.append(tr("Range"));
		_ui->tableWidget->setHorizontalHeaderLabels(header);
		_ui->retranslateUi(this);
	}

	QString PostInfoWidget::getRenderDataObjectType(RenderDataObject* obj)
	{
		QString sType = "TNone";
		auto	type  = obj->getDataType();
		if(type == Post::ObjType::Alg) {
			sType	 = tr("Alg");
			auto alg = RenderDataAlgorithm::SafeDownCast(obj);
			if(alg == nullptr)
				return sType;

			switch(alg->getAlgoType()) {
				case Post::ISO:
					sType = tr("ISOSurface");
					break;
				case Post::ISOCurve:
					sType = tr("ISOCurve");
					break;
				case Post::Vector:
					sType = tr("Vector");
					break;
				case Post::Slice:
					sType = tr("Slice");
					break;
				case Post::Clip:
					sType = tr("Clip");
					break;
				case Post::StreamLine:
					sType = tr("StreamLine");
					break;
				case Post::Simplify:
					sType = tr("Simplify");
					break;
				case Post::Calculator:
					sType = tr("Calculator");
					break;
				case Post::Reflection:
					sType = tr("Reflection");
					break;
			}
		} else if(type == Post::ObjType::Imp) {
			sType		 = tr("Steady");
			auto usteady = RenderDataImportUnSteady::SafeDownCast(obj);
			if(usteady != nullptr)
				sType = tr("UnSteady");
		}

		return sType;
	}

	void PostInfoWidget::updatePostTable(QTreeWidgetItem* item)
	{
		if(item == nullptr)
			return;

		bool ok = false;

		int	 id = item->data(0, Qt::UserRole).toInt(&ok);
		if(!ok)
			return;

		auto obj = _dataManager->getObjectByID(id);
		if(obj == nullptr)
			return;

		int index = item->data(1, Qt::UserRole).toInt(&ok);
		if(!ok)
			return;

		auto setRangeItem = [=](int row, int type, QString var) {
			auto	vtype = obj->variableType(type, var);
			double	range[2]{ 0 };
			QString sRange;
			if(vtype == "scalar") {
				obj->getRange(range, type, var, -1);
				sRange = QString("[%1,%2]").arg(range[0]).arg(range[1]);
			} else if(vtype == "vector") {
				obj->getRange(range, type, var, 0);
				sRange = QString("[%1,%2];").arg(range[0]).arg(range[1]);
				obj->getRange(range, type, var, 1);
				sRange += QString("[%1,%2];").arg(range[0]).arg(range[1]);
				obj->getRange(range, type, var, 2);
				sRange += QString("[%1,%2]").arg(range[0]).arg(range[1]);
			} else
				return;

			_ui->tableWidget->setItem(row, 3, new QTableWidgetItem(sRange));
		};

		if(index == -1) {
			_ui->FileNameValue->setText(obj->getName());
			_ui->TypeValue->setText(getRenderDataObjectType(obj));
			_ui->PointNumValue->setText(QString::number(obj->getPointDataNum()));
			_ui->CellNumValue->setText(QString::number(obj->getCellDataNum()));

			QStringList PointData;
			QStringList CellData;
			PointData	 = obj->getPointDataArray();
			CellData	 = obj->getCellDataArray();

			int Rowcount = PointData.size() + CellData.size();
			_ui->tableWidget->setRowCount(Rowcount);

			for(int i = 0; i < PointData.size(); i++) {
				double range[2]{ 0 };
				obj->getRange(range, 1, PointData[i], -1);

				_ui->tableWidget->setItem(i, 0, new QTableWidgetItem(tr("PointProperty")));
				_ui->tableWidget->setItem(i, 1, new QTableWidgetItem(PointData[i]));
				_ui->tableWidget->setItem(i, 2,
										  new QTableWidgetItem(obj->variableType(1, PointData[i])));
				//	qDebug() << obj->variableType(1, PointData[i]);
				setRangeItem(i, 1, PointData[i]);
			}
			for(int j = 0; j < CellData.size(); j++) {
				_ui->tableWidget->setItem(PointData.size() + j, 0,
										  new QTableWidgetItem(tr("CellProperty")));
				_ui->tableWidget->setItem(PointData.size() + j, 1,
										  new QTableWidgetItem(CellData[j]));
				_ui->tableWidget->setItem(PointData.size() + j, 2,
										  new QTableWidgetItem(obj->variableType(2, CellData[j])));
				setRangeItem(PointData.size() + j, 2, CellData[j]);
			}
		} else {
			_ui->FileNameValue->setText(obj->getBlockName(index));
			_ui->TypeValue->setText(getRenderDataObjectType(obj));
			_ui->PointNumValue->setText(QString::number(obj->getNumberOfBlockPoints(index + 1)));
			_ui->CellNumValue->setText(QString::number(obj->getNumberOfBlockCells(index + 1)));

			QStringList PointData;
			QStringList CellData;
			PointData	 = obj->getBlockPointDataArray(index + 1);
			CellData	 = obj->getBlockCellDataArray(index + 1);

			int Rowcount = PointData.size() + CellData.size();
			_ui->tableWidget->setRowCount(Rowcount);

			for(int i = 0; i < PointData.size(); i++) {
				double range[2]{ 0 };
				obj->getRange(range, 1, PointData[i], -1);

				_ui->tableWidget->setItem(i, 0, new QTableWidgetItem(tr("PointProperty")));
				_ui->tableWidget->setItem(i, 1, new QTableWidgetItem(PointData[i]));
				_ui->tableWidget->setItem(i, 2,
										  new QTableWidgetItem(obj->variableType(1, PointData[i])));
				//	qDebug() << obj->variableType(1, PointData[i]);
				setRangeItem(i, 1, PointData[i]);
			}
			for(int j = 0; j < CellData.size(); j++) {
				_ui->tableWidget->setItem(PointData.size() + j, 0,
										  new QTableWidgetItem(tr("CellProperty")));
				_ui->tableWidget->setItem(PointData.size() + j, 1,
										  new QTableWidgetItem(CellData[j]));
				_ui->tableWidget->setItem(PointData.size() + j, 2,
										  new QTableWidgetItem(obj->variableType(2, CellData[j])));
				setRangeItem(PointData.size() + j, 2, CellData[j]);
			}
		}

		//         if(item->childCount() > 0)
		//         {
		//
		//
		// //            int idBlock = item->data(1, Qt::UserRole).toInt(&ok);
		//
		//             _ui->FileNameValue->setText(obj->getName());
		//             _ui->TypeValue->setText(enumToString(obj->getDataType()));
		//             _ui->PointNumValue->setText(QString::number(obj->getPointDataNum()));
		//             _ui->CellNumValue->setText(QString::number(obj->getCellDataNum()));
		//
		//             QStringList PointData;
		//             QStringList CellData;
		//             PointData = obj->getPointDataArray();
		//             CellData = obj->getCellDataArray();
		//
		//             int Rowcount = PointData.size()+CellData.size();
		//             _ui->tableWidget->setRowCount(Rowcount);
		//
		//             for(int i=0; i<PointData.size(); i++)
		//             {
		//
		//                 _ui->tableWidget->setItem(i,0,new QTableWidgetItem("PointProperty"));
		//                 _ui->tableWidget->setItem(i,1,new QTableWidgetItem(PointData[i]));
		//                 _ui->tableWidget->setItem(i,2,new
		//                 QTableWidgetItem(QString::number(obj->variableType(1,PointData[i]))));
		//                 qDebug()<<obj->variableType(1,PointData[i]);
		//
		//             }
		//             for(int j=0; j<CellData.size(); j++)
		//             {
		//                 _ui->tableWidget->setItem(PointData.size()+j,0,new
		//                 QTableWidgetItem("CellProperty"));
		//                 _ui->tableWidget->setItem(PointData.size()+j,1,new
		//                 QTableWidgetItem(CellData[j]));
		//                 _ui->tableWidget->setItem(PointData.size()+j,2,new
		//                 QTableWidgetItem(QString::number(obj->variableType(2,CellData[j]))));
		//             }
		//         }
		//
		//         if(item->childCount() == 0)
		//         {
		//             _ui->FileNameValue->setText(obj->getBlockName(item->parent()->indexOfChild(item)));
		//             _ui->TypeValue->setText("");
		//             _ui->PointNumValue->setText(QString::number(obj->getNumberOfBlockPoints(item->parent()->indexOfChild(item)+1)));
		//             _ui->CellNumValue->setText(QString::number(obj->getNumberOfBlockCells(item->parent()->indexOfChild(item)+1)));
		//
		//             QStringList PointData;
		//             QStringList CellData;
		//             PointData = obj->getPointDataArray();
		//             CellData = obj->getCellDataArray();
		//
		//             int Rowcount = PointData.size()+CellData.size();
		//             _ui->tableWidget->setRowCount(Rowcount);
		//
		//             for(int i=0; i<PointData.size(); i++)
		//             {
		//
		//                 _ui->tableWidget->setItem(i,0,new QTableWidgetItem("PointProperty"));
		//                 _ui->tableWidget->setItem(i,1,new QTableWidgetItem(PointData[i]));
		//                 _ui->tableWidget->setItem(i,2,new
		//                 QTableWidgetItem(QString::number(obj->variableType(1,PointData[i]))));
		//                 qDebug()<<obj->variableType(1,PointData[i]);
		//
		//             }
		//             for(int j=0; j<CellData.size(); j++)
		//             {
		//                 _ui->tableWidget->setItem(PointData.size()+j,0,new
		//                 QTableWidgetItem("CellProperty"));
		//                 _ui->tableWidget->setItem(PointData.size()+j,1,new
		//                 QTableWidgetItem(CellData[j]));
		//                 _ui->tableWidget->setItem(PointData.size()+j,2,new
		//                 QTableWidgetItem(QString::number(obj->variableType(2,CellData[j]))));
		//             }
		//
		//
		//         }
	}

} // namespace Post
