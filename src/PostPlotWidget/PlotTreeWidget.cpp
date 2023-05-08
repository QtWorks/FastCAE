#include "PlotTreeWidget.h"
#include "MainWindow/MainWindow.h"
#include <QContextMenuEvent>
#include <PostCurveDataManager/PostDataPart.h>
#include <QList>
#include "PostCurveDataManager/PostData.h"
#include "PostCurveDataManager/PostCurveData.h"
namespace PostPlot
{

	PlotTreeWidget::PlotTreeWidget(GUI::MainWindow *m, QWidget *parent)
	{
		Q_UNUSED(parent)
		_mainWindow = m;
		this->setHeaderHidden(true);
		init();
	}

	PlotTreeWidget::~PlotTreeWidget()
	{
	}

	void PlotTreeWidget::init()
	{
		_root = new QTreeWidgetItem(this);
		_root->setText(0, tr("Curve item"));
		QVariant root(0);
		_root->setData(0, Qt::UserRole, root);
		this->addTopLevelItem(_root);
		_root->setExpanded(true);
	}

	void PlotTreeWidget::contextMenuEvent(QContextMenuEvent *event)
	{
		QMenu *_menu;
		_menu = new QMenu(this);
		auto item = this->itemAt(event->pos());
		_currentItem = item;
		if (item == nullptr)
			return;
		QVariant var = item->data(0, Qt::UserRole);
		if (0 == var)
		{
			QAction *_openfile;
			_openfile = new QAction("OpenFile", this);
			_menu->addAction(_openfile);
			_menu->move(cursor().pos());
			_menu->show();
			connect(_openfile, SIGNAL(triggered()), _mainWindow, SIGNAL(openPlot()));
		}

		if (1 == var)
		{
			QAction *_deletefile;
			_deletefile = new QAction("Delete", this);
			_menu->addAction(_deletefile);
			_menu->move(cursor().pos());
			_menu->show();
			connect(_deletefile, &QAction::triggered, [=]
					{ deleteFile(item); });
		}
	}

	void PlotTreeWidget::deleteFile(QTreeWidgetItem *item)
	{
		if (item == nullptr)
			return;
		QList<PostData::PostDataPart *> _datapartlist = PostData::PostData::getInstance()->getPostDataPart();
		for (int i = 0; i < _datapartlist.size(); i++)
		{
			PostData::PostCurveData *_postcurvedata = dynamic_cast<PostData::PostCurveData *>(_datapartlist[i]);
			if (_postcurvedata == nullptr)
				return;
			QString name = _postcurvedata->getName();
			QStringList list = name.split("/");
			if (item->text(0) == list[list.size() - 1])
			{
				PostData::PostData::getInstance()->delDataPartFromindex(i);
				delete item;
				return;
			}
		}
	}

	void PlotTreeWidget::updatePlotTree()
	{
		if (this->topLevelItem(0)->childCount() != 0)
		{
			this->clear();
			init();
			/*
			int count = this->topLevelItem(0)->childCount();
			for(int g = 0;g<count; g++)
			{
				this->topLevelItem(0)->removeChild(this->topLevelItem(0)->child(g));
			}
			*/
		}
		QList<PostData::PostDataPart *> _datapartlist = PostData::PostData::getInstance()->getPostDataPart();
		for (int i = 0; i < _datapartlist.size(); i++)
		{
			PostData::PostCurveData *_postcurvedata = dynamic_cast<PostData::PostCurveData *>(_datapartlist[i]);
			if (_postcurvedata == nullptr)
				return;
			QString name = _postcurvedata->getName();
			QStringList list = name.split("/");
			QTreeWidgetItem *item = new QTreeWidgetItem(_root);
			item->setText(0, list[list.size() - 1]);
			QVariant child(1);
			item->setData(0, Qt::UserRole, child);
			// this->topLevelItem(0)->addChild(item);
			QList<QString> variableNamelist; //变量名
			variableNamelist = _postcurvedata->getDataNames();
			for (int j = 0; j < variableNamelist.size(); j++)
			{
				QTreeWidgetItem *itemchild = new QTreeWidgetItem(_root->child(i));
				itemchild->setText(0, variableNamelist[j]);
				// this->topLevelItem(0)->child(i)->addChild(itemchild);
			}
		}
	}

}
