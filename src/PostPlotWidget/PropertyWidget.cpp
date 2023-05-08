#include "PropertyWidget.h"
#include "ui_PropertyWidget.h"
#include <qwt_plot_item.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <QPalette>
#include <QColorDialog>
#include <QList>
#include <QDebug>

namespace PostPlot {


PropertyWidget::PropertyWidget(PlotWidget* plotwidget,QWidget *parent) :
    QWidget(parent),
    _plotwidget(plotwidget),
    _ui(new Ui::PropertyWidget)
{
    _ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    _curvereader = new PostData::CurveDataReader();
    //_ui->tabWidget->tabBar()->hide();

    //this->read("F:/target.dat");
    //_datapartlist = PostData::PostData::getInstance()->getPostDataPart();
    /*
    for(int i=0;i<_datapartlist.size();i++)
    {
        _ui->datacomboBox->addItem("1");
    }*/
    datainit();
    xyinit();
    initPlotProperty();
    signalConnect();

}


PropertyWidget::~PropertyWidget()
{
    delete _ui;
}

void PropertyWidget::signalConnect()
{
    connect(_ui->datacomboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(readFileData(int)));
    connect(_ui->pushButton,SIGNAL(clicked()),this,SLOT(modifyTitle()));
    connect(_ui->colorbutton,SIGNAL(clicked()),this,SLOT(titleColorButton()));
    connect(_ui->axiscomboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(Axisinit(int)));
    connect(_ui->axiscolor,SIGNAL(clicked()),this,SLOT(AxisColor()));
    connect(_ui->axisOK,SIGNAL(clicked()),this,SLOT(modifyAxis()));
    connect(_ui->BackgrounOK,SIGNAL(clicked()),this,SLOT(modifyBackground()));
    connect(_ui->backcolorButton,SIGNAL(clicked()),this,SLOT(BackColor()));
    connect(_ui->addCurveOK,SIGNAL(clicked()),this,SLOT(addCurveOK()));
    connect(_ui->SelectCurveBox,SIGNAL(currentIndexChanged(int)),this,SLOT(SelectCurve(int)));
    connect(_ui->CurveOK,SIGNAL(clicked()),this,SLOT(modifyCurve()));
    connect(_ui->CurveColor,SIGNAL(clicked()),this,SLOT(CurveColor()));
    connect(_ui->deleteCurve,SIGNAL(clicked()),this,SLOT(deleteCurve()));

}

void PropertyWidget::showSetting(int index)
{
    _ui->tabWidget->setCurrentIndex(index);

}


void PropertyWidget::AxisColor()
{
    QColor color = _ui->axiscolor->palette().color(QPalette::Background);
    QColor c = QColorDialog::getColor(color);
    if(c.isValid())
    {
        _ui->axiscolor->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
    }
}


void PropertyWidget::Axisinit(int axis)
{
    QwtText aTitle = _plotwidget->axisTitle(axis);
    QwtInterval intv = _plotwidget->axisInterval(axis);
    QFont font = aTitle.font();
    int size = font.pointSize();
    QColor color = aTitle.color();
    _ui->axisName->setText(aTitle.text());
    _ui->axisfont->setCurrentFont(font);
    _ui->axissize->setValue(size);
    _ui->axisAutoBox->setChecked(_plotwidget->axisAutoScale(axis));
    _ui->axisStepSpinBox->setValue(_plotwidget->axisStepSize(axis));
    _ui->axisMinSpinBox->setValue(intv.minValue());
    _ui->axisMaxSpinBox->setValue(intv.maxValue());
    _ui->Visible->setChecked(_plotwidget->axisEnabled(axis));
    _ui->axiscolor->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
}


void PostPlot::PropertyWidget::modifyAxis()
{
    _plotwidget->plot_setAxisName(_ui->axiscomboBox->currentIndex(),_ui->axisName->text());
    _plotwidget->plot_setAxisFont(_ui->axiscomboBox->currentIndex(),_ui->axisfont->currentFont());
    _plotwidget->plot_setAxisFontSize(_ui->axiscomboBox->currentIndex(),_ui->axissize->value());
    _plotwidget->plot_setAxisFontColor(_ui->axiscomboBox->currentIndex(),_ui->axiscolor->palette().color(QPalette::Background));

    if(!_ui->axisAutoBox->isChecked())
    {
        //_plotwidget->plot_setAxisRange(_ui->axiscomboBox->currentIndex(),_ui->axisMinSpinBox->value(),_ui->axisMaxSpinBox->value());
        _plotwidget->plot_setAxisRangeSetp(_ui->axiscomboBox->currentIndex(),_ui->axisMinSpinBox->value(),_ui->axisMaxSpinBox->value(),_ui->axisStepSpinBox->value());
    }
    else
    {
        _plotwidget->plot_setAxisScaleAuto(_ui->axiscomboBox->currentIndex(),_ui->axisAutoBox->isChecked());
    }
    _plotwidget->plot_setAxisVisible(_ui->axiscomboBox->currentIndex(),_ui->Visible->isChecked());
}

void PostPlot::PropertyWidget::titleColorButton()
{
    QColor color = _ui->colorbutton->palette().color(QPalette::Background);
    QColor c = QColorDialog::getColor(color);
    if(c.isValid())
    {
        _ui->colorbutton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
    }

}

void PostPlot::PropertyWidget::modifyTitle()
{
    _plotwidget->plot_setTitleName(_ui->titleName->text());
    _plotwidget->plot_setTitleFont(_ui->titlefontCombobox->currentFont());
    _plotwidget->plot_setTitleFontSize(_ui->titlespinBox->value());
    _plotwidget->plot_setTitleFontColor(_ui->colorbutton->palette().color(QPalette::Background));
}





void PropertyWidget::modifyBackground()
{
    _plotwidget->plot_setPlotGrid(_ui->GridCheckBox->isChecked());

    if(_ui->LegendcheckBox->isChecked())
    {
        _plotwidget->plot_setLegendPosition(_ui->legendcomboBox->currentIndex());
    }
    else
    {
        _plotwidget->plot_setLegendVisible(_ui->legendcomboBox->currentIndex(),_ui->LegendcheckBox->isChecked());
    }

    _plotwidget->plot_setBackGround(_ui->backcolorButton->palette().color(QPalette::Background));

}


void PropertyWidget::BackColor()
{
    QColor color = _ui->backcolorButton->palette().color(QPalette::Background);
    QColor c = QColorDialog::getColor(color);
    if(c.isValid())
    {
        _ui->backcolorButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
    }

}


void PropertyWidget::readFileData(int index)
{
    _ui->XcomboBox->clear();
    _ui->YcomboBox->clear();
    if(_ui->datacomboBox->count() != 0)
    {

        _postcurvedata = dynamic_cast<PostData::PostCurveData*>(_datapartlist[index]);
        if(_postcurvedata == nullptr) return;
        QList<QString> a;
        a = _postcurvedata->getDataNames();

        for(int i=0;i<a.size();i++)
        {
            _ui->XcomboBox->addItem(a[i]);
            _ui->YcomboBox->addItem(a[i]);
        }
    }
    /*
    QVector<double> sin_x, sin_y;
    sin_x = _postcurvedata->getDataByName("VV");
    sin_y = _postcurvedata->getDataByName("VV-phase");*/

}


void PropertyWidget::addCurveOK()
{
    if(_postcurvedata == nullptr) return;

    QVector<double> sin_x, sin_y;
    sin_x = _postcurvedata->getDataByName(_ui->XcomboBox->currentText());
    sin_y = _postcurvedata->getDataByName(_ui->YcomboBox->currentText());
    _plotwidget->plot_addCurve(_ui->CurveNamelineEdit->text(),sin_x,sin_y);
    _ui->SelectCurveBox->addItem(_ui->CurveNamelineEdit->text());

    QwtInterval intv = _plotwidget->axisInterval(0);
    _ui->axisStepSpinBox->setValue(_plotwidget->axisStepSize(0));
    _ui->axisMinSpinBox->setValue(intv.minValue());
    _ui->axisMaxSpinBox->setValue(intv.maxValue());
}

void PropertyWidget::addCaseCurve(QString curvename)
{
    _ui->SelectCurveBox->addItem(curvename);

}

void PropertyWidget::delCaseCurve(QString curvename)
{

    for(int i = 0; i<_ui->SelectCurveBox->count(); i++)
    {
        if(_ui->SelectCurveBox->itemText(i) == curvename)
        {
            _ui->SelectCurveBox->removeItem(i);
            modifyBackground();
            return;
        }

    }

}


void PostPlot::PropertyWidget::SelectCurve(int index)
{
    if(index >= 0)
    {
        QwtPlotItemList curves = _plotwidget->itemList(QwtPlotItem::Rtti_PlotCurve);
        if (curves.size() <= index) return;
        QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(curves[index]);
        if (curve == nullptr)return;
        _ui->CurveName->setText(curve->title().text());
        _ui->CurveWidth->setValue(curve->pen().width());
        _ui->CurveStyle->setCurrentIndex(curve->pen().style()-1);
        QColor color = curve->pen().color();
        _ui->CurveColor->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));

    }

}

void PostPlot::PropertyWidget::modifyCurve()
{
    if(_ui->SelectCurveBox->count() == 0) return;

    int index = _ui->SelectCurveBox->currentIndex();
    _plotwidget->plot_setCurveName(index, _ui->CurveName->text());
    _ui->SelectCurveBox->setItemText(index, _ui->CurveName->text());
    _plotwidget->plot_setCurveWidth(index, _ui->CurveWidth->value());
    int style = _ui->CurveStyle->currentIndex();
    _plotwidget->plot_setCurveStyle(index,(Qt::PenStyle)style);
    _plotwidget->plot_setCurveColor(index,_ui->CurveColor->palette().color(QPalette::Background));

}

void PropertyWidget::CurveColor()
{
    QColor color = _ui->CurveColor->palette().color(QPalette::Background);
    QColor c = QColorDialog::getColor(color);
    if(c.isValid())
    {
        _ui->CurveColor->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
    }

}

void PropertyWidget::deleteCurve()
{
    if(_ui->SelectCurveBox->count() == 0) return;

    _plotwidget->plot_removeCurve(_ui->SelectCurveBox->currentIndex());
    _ui->SelectCurveBox->removeItem(_ui->SelectCurveBox->currentIndex());
    modifyBackground();

}


void PropertyWidget::read(QString fileName)
{
    if(_curvereader->read(fileName) == -1) return;
    // if(_curvereader == nullptr) return;


    datainit();

}

void PropertyWidget::datainit()
{
    _datapartlist = PostData::PostData::getInstance()->getPostDataPart();
    _ui->datacomboBox->clear();
    if(_datapartlist.size()!=0)
    {
        for(int i=0;i<_datapartlist.size();i++)
        {
            PostData::PostCurveData* _postcurvedatas = dynamic_cast<PostData::PostCurveData*>(_datapartlist[i]);
            if(_postcurvedatas == nullptr) return;
            QString name=_postcurvedatas->getName();
            QStringList list = name.split("/");
            _ui->datacomboBox->addItem(list[list.size()-1]);
        }
    }
}

void PropertyWidget::xyinit()
{
    _ui->XcomboBox->clear();
    _ui->YcomboBox->clear();
    if(_ui->datacomboBox->count() != 0)
    {
        _postcurvedata = dynamic_cast<PostData::PostCurveData*>(_datapartlist[0]);
        if(_postcurvedata == nullptr) return;
        QList<QString> a;
        a = _postcurvedata->getDataNames();
        for(int i=0;i<a.size();i++)
        {
            _ui->XcomboBox->addItem(a[i]);
            _ui->YcomboBox->addItem(a[i]);
        }
    }
}



void PropertyWidget::initPlotProperty()
{
    QwtText pTitle = _plotwidget->title();
    QFont font = pTitle.font();
    QString title = pTitle.text();
    int size = font.pointSize();
    QColor c = pTitle.color();

    QPalette canvasPalette = _plotwidget->palette();
    QColor backcolor = _plotwidget->canvas()->palette().currentColorGroup();
    _ui->backcolorButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(255).arg(255).arg(255));

    _ui->titleName->setText(title);
    _ui->titlespinBox->setValue(size);
    _ui->titlefontCombobox->setCurrentFont(font);
    _ui->colorbutton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));

    QwtPlotLayout* pLayout = _plotwidget->plotLayout();
    QwtLegend* legend = dynamic_cast<QwtLegend*>(_plotwidget->legend());
    _ui->LegendcheckBox->setChecked(true);
    _ui->GridCheckBox->setChecked(true);
    _ui->CurveStyle->setCurrentIndex(1);
    if (legend != nullptr && pLayout != nullptr)
    {
        _ui->legendcomboBox->setCurrentIndex(pLayout->legendPosition());
        _ui->LegendcheckBox->setChecked(true);
        _ui->GridCheckBox->setChecked(true);
    }

    QwtText aTitle = _plotwidget->axisTitle(0);
    QwtInterval intv = _plotwidget->axisInterval(0);
    //QFont fonts = aTitle.font();
    //int sizes = font.pointSize();
    QColor color = aTitle.color();
    _ui->axisName->setText(aTitle.text());
    _ui->axisfont->setCurrentFont(font);
    _ui->axissize->setValue(size);
    _ui->axisAutoBox->setChecked(true);
    _ui->axisStepSpinBox->setValue(_plotwidget->axisStepSize(0));
    _ui->axisMinSpinBox->setValue(intv.minValue());
    _ui->axisMaxSpinBox->setValue(intv.maxValue());
    _ui->Visible->setChecked(_plotwidget->axisEnabled(0));
    _ui->axiscolor->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
}


}
