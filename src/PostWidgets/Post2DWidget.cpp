#include "Post2DWidget.h"
#include "ui_Post2DWidget.h"
#include "MainWindow/MainWindow.h"
#include "Settings/BusAPI.h"
#include "PostPlotWidget/PlotWidget.h"
#include "PostCurveDataManager/PostData.h"
#include <QList>

namespace Post
{
	Post2DWindow::Post2DWindow(GUI::MainWindow *mw, int proID)
		: _ui(new Ui::Post2DWidget), ModuleBase::GraphWindowBase(mw, proID, ModuleBase::Post2D)
	{
		_ui->setupUi(this);
		//_mainWindow = mw;
		_plots = new PostPlot::PlotMainWidget(this);
		_ui->layout->addWidget(_plots);

		connect(this, SIGNAL(updatePlotTree()), mw, SIGNAL(updatePlotTreeSig()));
		// 		_curveMainWindow = new curve_MainWindow;
		// 		_ui->layout->addWidget(_curveMainWindow->get_curve_plotWidget());
		//		_curveMainWindow->get_curve_plotWidget()->show();
	}
	Post2DWindow::~Post2DWindow()
	{
		//	if (_curveMainWindow) _curveMainWindow->close();
		if (_plots != nullptr)
			delete _plots;
		if (_ui != nullptr)
			delete _ui;
	}
	void Post2DWindow::replot()
	{
		//	_curveMainWindow->script_update_replot();
	}
	bool Post2DWindow::openFile(QString file)
	{
		_plots->readfile(file);

		emit updatePlotTree();
		//	return _curveMainWindow->script_openFile(file);
		return false;
	}
	void Post2DWindow::addCurve(QString tep_filename, int tep_column_index)
	{
		Q_UNUSED(tep_filename)
		Q_UNUSED(tep_column_index)
		//	_curveMainWindow->script_addCurve(tep_filename, tep_column_index);
	}
	void Post2DWindow::addCurve(QVector<double> data_x, QVector<double> data_y, QString tep_filename, QString curvename)
	{
		/*
			QList<PostData::PostDataPart*> _datapartlist = PostData::PostData::getInstance()->getPostDataPart();
			for(int i = 0; i < _datapartlist.size(); i++)
			{
				PostData::PostCurveData* _postcurvedata = dynamic_cast<PostData::PostCurveData*>(_datapartlist[i]);
				QString name=_postcurvedata->getName();
				QStringList list = name.split("/");
				if(tep_filename == list[list.size()-1])
				{

				}
			}*/

		if (isCaseFileOpen(tep_filename))
		{
			_plots->post2DaddCurve(data_x, data_y, curvename);
		}
		else
		{
			_plots->readfile(tep_filename);
			emit updatePlotTree();
			_plots->post2DaddCurve(data_x, data_y, curvename);
		}
		//    _plot->plot_addCurve(tep_filename,data_x,data_y);
		//	_curveMainWindow->script_addCurve(data_x, data_y, tep_filename);
	}
	void Post2DWindow::addCurve(QVector<double> data_y, QString fileName)
	{
		Q_UNUSED(data_y)
		Q_UNUSED(fileName)
		//	_curveMainWindow->script_addCurve(data_y, fileName);
	}
	void Post2DWindow::delCurve(QString fileName, int colum_index)
	{
		Q_UNUSED(colum_index)
		_plots->post2DdelCurve(fileName);
		//	_curveMainWindow->script_delCurve(fileName, colum_index);
	}
	void Post2DWindow::delAllCurves()
	{
		//   _plot->plot_removeAllCurves();
		//	_curveMainWindow->script_delAllCurves();
	}
	void Post2DWindow::setTitle(QString title)
	{
		Q_UNUSED(title)
		//    _plot->plot_setTitleName(title);
		//	_curveMainWindow->script_Plot_title(title);
	}
	void Post2DWindow::setTitleFont(int font)
	{
		if (font < 0 || font > 2)
			return;
		//   _plot->plot_setTitleFont(font);
		//	_curveMainWindow->script_Plot_titleFontType((plotProp_fontType)font);
	}
	void Post2DWindow::setTitleFontSize(int size)
	{
		Q_UNUSED(size)
		//   _plot->plot_setTitleFontSize(size);
		//	_curveMainWindow->script_Plot_titleFontSize(size);
	}
	void Post2DWindow::setTitleFontColor(QColor color)
	{
		Q_UNUSED(color)
		//   _plot->plot_setTitleFontColor(color);
		//	_curveMainWindow->script_Plot_titleFontColor(color);
	}
	void Post2DWindow::setBackGround(QColor color)
	{
		Q_UNUSED(color)
		//   _plot->plot_setBackGround(color);
		//	_curveMainWindow->script_Plot_backgroundColor(c);
	}
	void Post2DWindow::setPlotGrid(bool isgrid)
	{
		Q_UNUSED(isgrid)
		//   _plot->plot_setPlotGrid(isgrid);
		//	_curveMainWindow->script_Plot_grid(isgrid);
	}
	void Post2DWindow::setLegendPosition(int p)
	{
		if (p < 0 || p > 4)
			return;
		//    _plot->plot_setLegendPosition(p);
		//	_curveMainWindow->script_Plot_legend((plotProp_legendPostion)p);
	}
	void Post2DWindow::setAxisNum(int num)
	{
		Q_UNUSED(num)
		//	_curveMainWindow->script_Plot_numAxis(num);
	}
	void Post2DWindow::setAxisName(QString axis, QString name)
	{
		Q_UNUSED(axis)
		Q_UNUSED(name)
		//    _plot->plot_setAxisName(axis, name);
		//	_curveMainWindow->script_Plot_axisName(axis, name);
	}
	void Post2DWindow::setAxisFontColor(QString axis, QColor color)
	{
		Q_UNUSED(axis)
		Q_UNUSED(color)
		//   _plot->plot_setAxisFontColor(axis, color);
		//	_curveMainWindow->script_Plot_axisFontColor(axis, color);
	}
	void Post2DWindow::setAxisFontSize(QString axis, int size)
	{
		Q_UNUSED(axis)
		Q_UNUSED(size)
		//    _plot->plot_setAxisFontSize(axis, size);
		//	_curveMainWindow->script_Plot_axisFontSize(axis, size);
	}
	void Post2DWindow::setAxisFont(QString axis, int font)
	{
		Q_UNUSED(axis)
		if (font < 0 || font > 2)
			return;
		//    _plot->plot_setAxisFont(axis, font);
		//	_curveMainWindow->script_Plot_axisFontType(axis, (plotProp_fontType)font);
	}
	void Post2DWindow::setCurveColor(QString fileName, int colIndex, QColor color)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(colIndex)
		Q_UNUSED(color)
		//   _plot->plot_setCurveColor(fileName, colIndex, color);
		//	_curveMainWindow->script_Curve_color(fileName, colIndex, color);
	}
	void Post2DWindow::setCurveStyle(QString fileName, int colIndex, Qt::PenStyle style)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(colIndex)
		Q_UNUSED(style)
		//   _plot->plot_setCurveStyle(fileName, colIndex, style);
		//	_curveMainWindow->script_Curve_lineType(fileName, colIndex, style);
	}
	void Post2DWindow::setCurveWidth(QString fileName, int colIndex, int width)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(colIndex)
		Q_UNUSED(width)
		//    _plot->plot_setCurveWidth(fileName, colindex, width);
		//	_curveMainWindow->script_Curve_lineWidth(fileName, colindex, width);
	}
	void Post2DWindow::setCurveShowPoint(QString fileName, int index, bool show)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(index)
		Q_UNUSED(show)
		//	_curveMainWindow->script_Curve_showPoint(fileName, index, show);
	}
	void Post2DWindow::setCurveName(QString fileName, int colIndex, QString name)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(colIndex)
		Q_UNUSED(name)
		//	_curveMainWindow->script_Curve_name(fileName, colindex, name);
	}
	void Post2DWindow::setCurveAxisIndex(QString fileName, int colIndex, int axisIndex)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(colIndex)
		Q_UNUSED(axisIndex)
		//	_curveMainWindow->script_Curve_axisIndex(fileName, colindex, axisIndex);
	}
	// 	QWidget* Post2DWindow::getPropWidget()
	// 	{
	// 		return _curveMainWindow->get_column_dataWidget();
	// 	}
	// 	QWidget* Post2DWindow::getTreeWidget()
	// 	{
	// 		return _curveMainWindow->get_curve_treeWidget();
	// 	}
	void Post2DWindow::updateCurve(QVector<double> data_x, QVector<double> data_y, QString tep_filename)
	{
		Q_UNUSED(data_x)
		Q_UNUSED(data_y)
		Q_UNUSED(tep_filename)
		//	_curveMainWindow->script_updateCurveData(data_x, data_y, tep_filename);
	}
	void Post2DWindow::updateCurve(QVector<double> data_y, QString tep_filename)
	{
		Q_UNUSED(data_y)
		Q_UNUSED(tep_filename)
		//	_curveMainWindow->script_updateCurveData(data_y, tep_filename);
	}
	void Post2DWindow::setBackGround(QColor color1, QColor color2)
	{
		Q_UNUSED(color1)
		Q_UNUSED(color2)
		// TODO
	}
	void Post2DWindow::saveImage(QString fileName, int width, int heigh, bool showDlg)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(width)
		Q_UNUSED(heigh)
		Q_UNUSED(showDlg)
		//	_curveMainWindow->script_saveImage(showDlg, width, heigh, fileName);
	}
	void Post2DWindow::setAxisRange(QString axis, double range[2])
	{
		Q_UNUSED(axis)
		Q_UNUSED(range)
		//    _plot->plot_setAxisRange(axis, range);
		//	_curveMainWindow->script_Plot_axisrange(axis, range);
	}
	QStringList Post2DWindow::getColumnNameList(QString fileName)
	{
		Q_UNUSED(fileName)
		//	return _curveMainWindow->script_getFileColumnNameList(fileName);
		return QStringList();
	}
	void Post2DWindow::reTranslate()
	{
		_ui->retranslateUi(this);
		QString lang = Setting::BusAPI::instance()->getLanguage();
		//	_curveMainWindow->ChangeLanguage(lang);
	}
	QWidget *Post2DWindow::getTreeWidget()
	{
		// 		QDockWidget* dw = _curveMainWindow->get_curve_treeWidget();
		// 		QWidget* old = dw->titleBarWidget();
		// 		QWidget* empty = new QWidget;
		// 		dw->setTitleBarWidget(empty);
		// 		delete old;
		// 		return dw;
		return nullptr;
	}
	QWidget *Post2DWindow::getPropWidget()
	{
		// 		QDockWidget* dw = _curveMainWindow->get_column_dataWidget();
		// 		QWidget* old = dw->titleBarWidget();
		// 		QWidget* empty = new QWidget;
		// 		dw->setTitleBarWidget(empty);
		// 		delete old;
		// 		return dw;
		return nullptr;
	}
	// 	curve_line_data Post2DWindow::getCurveProp(QString tepFileName, int colIndex)
	// 	{
	// 		return _curveMainWindow->script_get_CurveProp(tepFileName, colIndex);
	// 	}

	bool Post2DWindow::startAnimate()
	{
		// return _curveMainWindow->script_start_animate();
		return false;
	}

	bool Post2DWindow::stopAnimate()
	{
		// return _curveMainWindow->script_stop_animate();
		return false;
	}

	void Post2DWindow::setAniPointColor(QString fileName, int colum, QColor color)
	{
		Q_UNUSED(fileName)
		Q_UNUSED(colum)
		Q_UNUSED(color)
		//_curveMainWindow->script_AniPoint_color(fileName, colum, color);
	}

	// 	void Post2DWindow::setAniPointType(QString fileName, int colum, aniPointType type)
	// 	{
	// 		//_curveMainWindow->script_AniPoint_type(fileName, colum, type);
	// 	}

	bool Post2DWindow::isCaseFileOpen(QString filename)
	{
		_datapartlist = PostData::PostData::getInstance()->getPostDataPart();
		for (int i = 0; i < _datapartlist.size(); i++)
		{
			PostData::PostCurveData *_postcurvedata = dynamic_cast<PostData::PostCurveData *>(_datapartlist[i]);
			if (_postcurvedata == nullptr)
				continue;
			QString name = _postcurvedata->getName();
			if (filename == name)
			{
				return true;
			}
		}
		return false;
	}

}
