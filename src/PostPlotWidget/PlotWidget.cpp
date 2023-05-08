#include "PlotWidget.h"
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_widget.h>
#include <qwt_abstract_legend.h>
#include <qwt_legend_label.h>
#include <qwt_symbol.h>
#include <qwt_point_data.h>
#include <qwt_plot_layout.h>


namespace PostPlot {

    PlotWidget::PlotWidget(QWidget* parent):
        QwtPlot(parent)
    {
        initPlot();
        //plot_addCurve();
        /*
        _postData = new PostData::PostData();
        b->read("F:/target.dat",_postData);
        a = _postData->getPostDataPart();
        _dataPart = dynamic_cast<PostData::PostCurveData*>(a[0]);
        QVector<double> sin_x, sin_y;
        sin_x = _dataPart->getDataByName("VV");
        sin_y = _dataPart->getDataByName("VV-phase");
        plot_addCurve("789",sin_x,sin_y);
        */
        //plot_removeCurve(0);
        //plot_removeCurve(0);
        //plot_setAxisFontSize(2,30);
        //plot_setPlotGrid(true);
        //plot_setLegendPosition(3);
        //plot_setCurveWidth("yLeft", 1, 20);
        //plot_setCurveStyle("yLeft",0,(Qt::DashLine));
        /*
        double range[2];
        range[0]=-200;
        range[1]=700;
        plot_setAxisRange("xBottom",range);*/
        plot_setPlotGrid(true);
        new QwtPlotMagnifier(this->canvas());
        new QwtPlotPanner(this->canvas());

    }

    PlotWidget::~PlotWidget()
    {
        delete _grid;
    }

    /*
    void PlotWidget::plot_addCurve()
    {
        QVector<double> sin_x, sin_y, cos_x, cos_y;
        for (int i = -180; i < 721; i++)
        {
            double v = i * M_PI / 180;
            double sin_v = qSin(v);
            //double sin_v = qFastSin(v);
            double cos_v = qCos(v);
            //double cos_v = qFastCos(v);
            //qDebug() << i << sin_v << cos_v;
            sin_x.append(i);
            sin_y.append(sin_v);
            cos_x.append(i);
            cos_y.append(cos_v);
        }



        QwtPlotCurve *curve = new QwtPlotCurve();
        curve->setTitle(QString("curve_%1").arg(_curveNum + 1));
        QColor color = colorList.at(_curveNum++ % colorList.size());
        curve->setPen(QPen(color, 10));
        curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        curve->setSamples(sin_x, sin_y);
        curve->attach(this);
        curve->setCurveAttribute(QwtPlotCurve::Fitted, true);
        QwtPlotCurve *curve1 = new QwtPlotCurve();
        curve1->setTitle(QString("curve_%1").arg(_curveNum + 1));
        QColor color1 = colorList.at(_curveNum++ % colorList.size());
        curve1->setPen(QPen(color1, 10,(Qt::DashLine)));
        curve1->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        curve1->setSamples(cos_x, cos_y);
        curve1->attach(this);
        curve1->setCurveAttribute(QwtPlotCurve::Fitted, true);
        this->replot();
    }*/

    void PlotWidget::plot_addCurve(QString name, QVector<double> &xData, QVector<double> &yData)
    {
        if (name.isEmpty()) name = QString("curve_%1").arg(_curveNum + 1);
        QwtPlotCurve *curve = new QwtPlotCurve();
        curve->setTitle(name);
        QColor color = colorList.at(_curveNum++ % colorList.size());
        curve->setPen(QPen(color, 1));
        curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        curve->setSamples(xData, yData);
        curve->attach(this);
        QwtSymbol* symbol = new QwtSymbol;
        symbol->setPen(QColor(255, 0, 0), 5);
        symbol->setStyle(QwtSymbol::NoSymbol);
        curve->setSymbol(symbol);
        this->replot();
        this->insertLegend(new QwtLegend, QwtPlot::LeftLegend);
    }

    void PlotWidget::plot_removeCurve(int index)
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        if (curves.size() <= index) return;
        this->removeItem(curves[index]);
        this->replot();

    }

    void PlotWidget::plot_removeCurve(QString curvename)
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        for(int i = 0; i < curves.size(); i++)
        {
            QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(curves[i]);
            if(curve == nullptr) return;
            if(curve->title().text() == curvename)
            {
                this->removeItem(curves[i]);
                this->replot();
                return;
            }

        }
    }

    void PlotWidget::plot_removeAllCurves()
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        int num = curves.size();
        while (num != 0) {
            num--;
            this->removeItem(curves[num]);
        }
        this->replot();
    }

    void PlotWidget::plot_updateCurve(int index, QVector<double> &xData, QVector<double> &yData)
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        if (curves.size() <= index) return;
        QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(curves[index]);
        if (curve == nullptr)return;
        curve->setSamples(xData, yData);
    }

    void PlotWidget::plot_setTitleName(QString titles)
    {
        _title.setText(titles);
        this->setTitle(_title);
    }

    void PlotWidget::plot_setTitleFont(QFont font)
    {
        _titlefont.setFamily(font.family());
        _title.setFont(_titlefont);
        this->setTitle(_title);

    }

    void PlotWidget::plot_setTitleFontSize(int size)
    {
        _titlefont.setPointSize(size);
        _title.setFont(_titlefont);
        this->setTitle(_title);

    }

    void PlotWidget::plot_setTitleFontColor(QColor color)
    {
        _title.setColor(color);
        this->setTitle(_title);

    }

    void PlotWidget::plot_setBackGround(QColor color)
    {
        this->setCanvasBackground(color);
    }

    void PlotWidget::plot_setPlotGrid(bool isgrid)
    {
        if(isgrid)
        {
            _grid = new QwtPlotGrid;
            _grid->enableXMin(true);
            _grid->setMajorPen(Qt::gray, 0, Qt::DotLine);
            _grid->setMinorPen(Qt::darkGray, 0, Qt::DotLine);
            _grid->attach(this);
        }
        else
        {
            _grid = new QwtPlotGrid;
            _grid->enableXMin(true);
            _grid->setMajorPen(Qt::white, 0, Qt::DotLine);
            _grid->setMinorPen(Qt::white, 0, Qt::DotLine);
            _grid->attach(this);
        }

    }

    void PlotWidget::plot_setLegendPosition(int position)
    {
        switch (position) {
        case 0:
            this->insertLegend(new QwtLegend, QwtPlot::LeftLegend);
            break;
        case 1:
            this->insertLegend(new QwtLegend, QwtPlot::RightLegend);
            break;
        case 2:
            this->insertLegend(new QwtLegend, QwtPlot::BottomLegend);
            break;
        case 3:
            this->insertLegend(new QwtLegend, QwtPlot::TopLegend);
            break;
        default:
            break;
        }

    }

    void PlotWidget::plot_setLegendVisible(int legned, bool flag)
    {

        QwtLegend* legend = dynamic_cast<QwtLegend*>(this->legend());
        if (legend == nullptr) return;

        int pos = legned;
        if (pos == 0 || pos == 1)
            legend->setMaxColumns(1);
        else
            legend->setMaxColumns(0);
        legend->contentsWidget()->setVisible(flag);
        this->insertLegend(legend, (QwtPlot::LegendPosition)pos);

    }

    /*
    void PlotWidget::plot_setAxisNum(int num)
    {

    }*/

    void PlotWidget::plot_setAxisName(int axis, QString name)
    {
        switch (axis) {
        case 2:
            _xBottomtitle.setText(name);
            this->setAxisTitle(QwtPlot::xBottom,_xBottomtitle);
            break;
        case 0:
            _yLefttitle.setText(name);
            this->setAxisTitle(QwtPlot::yLeft,_yLefttitle);
            break;
        case 1:
            _yRighttitle.setText(name);
            this->setAxisTitle(QwtPlot::yRight,_yRighttitle);
            break;
         case 3:
            _xToptitle.setText(name);
            this->setAxisTitle(QwtPlot::xTop,_xToptitle);
            break;
        default:
            break;

        }

    }

    void PlotWidget::plot_setAxisFontColor(int axis, QColor color)
    {
        switch (axis) {
        case 2:
            _xBottomtitle.setColor(color);
            this->setAxisTitle(QwtPlot::xBottom,_xBottomtitle);
            break;
        case 0:
            _yLefttitle.setColor(color);
            this->setAxisTitle(QwtPlot::yLeft,_yLefttitle);
            break;
        case 1:
            _yRighttitle.setColor(color);
            this->setAxisTitle(QwtPlot::yRight,_yRighttitle);
            break;
         case 3:
            _xToptitle.setColor(color);
            this->setAxisTitle(QwtPlot::xTop,_xToptitle);
            break;
        default:
            break;

        }

    }

    void PlotWidget::plot_setAxisFontSize(int axis, int size)
    {
        switch (axis) {
        case 2:
            _xBottomfont.setPointSize(size);
            _xBottomtitle.setFont(_xBottomfont);
            this->setAxisTitle(QwtPlot::xBottom,_xBottomtitle);
            break;
        case 0:
            _yLeftfont.setPointSize(size);
            _yLefttitle.setFont(_yLeftfont);
            this->setAxisTitle(QwtPlot::yLeft,_yLefttitle);
            break;
        case 1:
            _yRightfont.setPointSize(size);
            _yRighttitle.setFont(_yRightfont);
            this->setAxisTitle(QwtPlot::yRight,_yRighttitle);
            break;
         case 3:
            _xTopfont.setPointSize(size);
            _xToptitle.setFont(_xTopfont);
            this->setAxisTitle(QwtPlot::xTop,_xToptitle);
            break;
        default:
            break;

        }

        //axis.remove(0,6);
        //int axsid = axis.toInt();

    }

    void PlotWidget::plot_setAxisFont(int axis, QFont font)
    {
        //axis.remove(0,6);
        //int axsid = axis.toInt();

        switch (axis) {
        case 2:
            _xBottomfont.setFamily(font.family());
            _xBottomtitle.setFont(_xBottomfont);
            this->setAxisTitle(QwtPlot::xBottom,_xBottomtitle);
            break;
        case 0:
            _yLeftfont.setFamily(font.family());
            _yLefttitle.setFont(_yLeftfont);
            this->setAxisTitle(QwtPlot::yLeft,_yLefttitle);
            break;
        case 1:
            _yRightfont.setFamily(font.family());
            _yRighttitle.setFont(_yRightfont);
            this->setAxisTitle(QwtPlot::yRight,_yRighttitle);
            break;
         case 3:
            _xTopfont.setFamily(font.family());
            _xToptitle.setFont(_xTopfont);
            this->setAxisTitle(QwtPlot::xTop,_xToptitle);
            break;
        default:
            break;

        }
    }

    void PlotWidget::plot_setAxisVisible(int axis, bool flag)
    {
            switch (axis) {
            case 2:
                this->enableAxis(2,flag);
                this->replot();
                break;
            case 0:
                this->enableAxis(0,flag);
                this->replot();
                break;
            case 1:
                this->enableAxis(1,flag);
                this->replot();
                break;
            case 3:
                this->enableAxis(3,flag);
                this->replot();
                break;
            default:
                break;
            }

    }

    void PlotWidget::plot_setCurveColor(int colIndex, QColor color)
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        if (curves.size() <= colIndex) return;
        QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(curves[colIndex]);
        if (curve == nullptr)return;
        curve->setPen(color,curve->pen().width(),curve->pen().style());

    }

    void PlotWidget::plot_setCurveStyle(int colIndex, Qt::PenStyle style)
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        if (curves.size() <= colIndex) return;
        QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(curves[colIndex]);
        if (curve == nullptr)return;
        curve->setPen(curve->pen().color(),curve->pen().width(),style);

    }

    void PlotWidget::plot_setCurveWidth(int colIndex, int width)
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        if (curves.size() <= colIndex) return;
        QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(curves[colIndex]);
        if (curve == nullptr)return;
        curve->setPen(curve->pen().color(),width,curve->pen().style());
    }

    /*
    void PlotWidget::plot_setCurveShowPoint(QString fileName, int colindex, bool show)
    {

    }*/

    void PlotWidget::plot_setCurveName(int colIndex, QString name)
    {
        QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);
        if (curves.size() <= colIndex) return;
        QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(curves[colIndex]);
        if (curve == nullptr)return;
        curve->setTitle(name);


    }

    /*
    void PlotWidget::plot_setCurveAxisIndex(QString fileName, int colindex, int axisIndex)
    {

    }*/
    /*
    void PlotWidget::plot_setAxisRange(int axis, double min, double max)
    {
        switch (axis) {
        case 2:
            this->setAxisScale(QwtPlot::xBottom, min, max);
            this->replot();
            break;
        case 0:
            this->setAxisScale(QwtPlot::yLeft, min, max);
            this->replot();
            break;
        case 1:
            this->setAxisScale(QwtPlot::yRight, min, max);
            this->replot();
            break;
         case 3:
            this->setAxisScale(QwtPlot::xTop, min, max);
            this->replot();
            break;
        default:
            break;

        }
    }
    */

    void PlotWidget::plot_setAxisRangeSetp(int axis, double min, double max, double step)
    {
        switch (axis) {
        case 2:
            this->setAxisScale(QwtPlot::xBottom, min, max, step);
            this->replot();
            break;
        case 0:
            this->setAxisScale(QwtPlot::yLeft, min, max, step);
            this->replot();
            break;
        case 1:
            this->setAxisScale(QwtPlot::yRight, min, max, step);
            this->replot();
            break;
         case 3:
            this->setAxisScale(QwtPlot::xTop, min, max, step);
            this->replot();
            break;
        default:
            break;

        }
    }

    void PlotWidget::plot_setAxisScaleAuto(int axis, bool flag)
    {
         this->setAxisAutoScale(axis, flag);
    }

    /*
    void PlotWidget::replot()
    {
        this->replot();
    }
    */
    void PlotWidget::initPlot()
    {
        setAutoFillBackground(true);
        setAutoReplot(true);
        _title.setText("Title");
        _titlefont.setFamily(QString::fromLocal8Bit("黑体"));
        _titlefont.setPointSize(15);
        _title.setFont(_titlefont);
        _title.setColor(Qt::black);
        this->setTitle(_title);
        this->setCanvasBackground(Qt::white);
        //this->insertLegend(new QwtLegend, QwtPlot::BottomLegend);

        //this->setAxisTitle(QwtPlot::xBottom,"x");
        //this->setAxisTitle(QwtPlot::yLeft,"y");


        //this->setAxisScale(QwtPlot::yLeft, 0, 2);
        //this->setAxisScale(QwtPlot::xBottom, 0, 100);

        /*
        _grid = new QwtPlotGrid;
        _grid->enableXMin(true);
        _grid->setMajorPen(Qt::gray, 0, Qt::DotLine);
        _grid->setMinorPen(Qt::darkGray, 0, Qt::DotLine);
        _grid->attach(this);
        */

        QwtPlotCanvas *canvas = new QwtPlotCanvas();
        canvas->setLineWidth(1);
        canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
        canvas->setBorderRadius(15);

        QPalette canvasPalette(Qt::white);
        canvasPalette.setColor(QPalette::Foreground, Qt::white);
        canvas->setPalette(canvasPalette);
        this->setCanvas(canvas);

    }



}
