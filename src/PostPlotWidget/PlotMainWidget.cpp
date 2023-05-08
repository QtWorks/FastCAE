#include "PlotMainWidget.h"
#include "ui_PlotMainWidget.h"
#include <QContextMenuEvent>

namespace PostPlot {


PlotMainWidget::PlotMainWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::PlotMainWidget)
{
    _ui->setupUi(this);
    _menu = new QMenu(this);
    _datasetting = new QAction("DataSetting",this);
    _curvesetting = new QAction("CurveSetting",this);
    _titlesetting = new QAction("TitleSetting",this);
    _axisetting = new QAction("AxisSetting",this);
    _backgroundsetting = new QAction("BackgroundSetting",this);

    _menu->addAction(_datasetting);
    _menu->addAction(_titlesetting);
    _menu->addAction(_axisetting);
    _menu->addAction(_backgroundsetting);
    _menu->addAction(_curvesetting);
    _plotwidget = new PlotWidget(this);
    _prowidget = new PropertyWidget(_plotwidget,this);
    _ui->Layout->addWidget(_plotwidget);
    _ui->Layout->addWidget(_prowidget);
    _prowidget->setVisible(false);
}

PlotMainWidget::~PlotMainWidget()
{
    if(_plotwidget != nullptr) delete _plotwidget;
    if(_prowidget != nullptr) delete _prowidget;
    delete _ui;
}

void PlotMainWidget::init()
{
    this->setMinimumSize(80, 60);
    _plotwidget = new PlotWidget(this);
    _prowidget = new PropertyWidget(_plotwidget,this);
    _ui->Layout->addWidget(_plotwidget);
    _ui->Layout->addWidget(_prowidget);
    _prowidget->setVisible(false);

}

void PlotMainWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)
    _menu->move(cursor().pos());
    _menu->show();

    connect(_datasetting,SIGNAL(triggered()),this,SLOT(DataSetting()));
    connect(_titlesetting,SIGNAL(triggered()),this,SLOT(TitleSetting()));
    connect(_axisetting,SIGNAL(triggered()),this,SLOT(AxisSetting()));
    connect(_backgroundsetting,SIGNAL(triggered()),this,SLOT(BackSetting()));
    connect(_curvesetting,SIGNAL(triggered()),this,SLOT(CurveSetting()));
    _prowidget->datainit();
}

void PlotMainWidget::DataSetting()
{
    _prowidget->showSetting(0);
    _prowidget->show();
}

void PlotMainWidget::TitleSetting()
{
    _prowidget->showSetting(1);
    _prowidget->show();
}

void PlotMainWidget::AxisSetting()
{
    _prowidget->showSetting(2);
    _prowidget->show();

}

void PlotMainWidget::BackSetting()
{
    _prowidget->showSetting(3);
    _prowidget->show();
}

void PlotMainWidget::CurveSetting()
{
    _prowidget->showSetting(4);
    _prowidget->show();
}

void PlotMainWidget::readfile(QString fileName)
{
    _prowidget->read(fileName);
}

void PlotMainWidget::post2DaddCurve(QVector<double> data_x, QVector<double> data_y,QString curvename)
{

    _plotwidget->plot_addCurve(curvename,data_x,data_y);
    _prowidget->addCaseCurve(curvename);
    _prowidget->datainit();

}

void PlotMainWidget::post2DdelCurve(QString curvename)
{

    _plotwidget->plot_removeCurve(curvename);
    _prowidget->delCaseCurve(curvename);

}

}
