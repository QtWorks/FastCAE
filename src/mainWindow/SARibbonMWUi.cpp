#include "SARibbonMWUi.h"
#include "SARibbonBar/SARibbonBar.h"
#include "SARibbonBar/SARibbonCategory.h"
#include "SARibbonBar/SARibbonPannel.h"
#include "SARibbonBar/SARibbonContextCategory.h"
#include "SARibbonBar/SARibbonTabBar.h"
#include "SARibbonBar/SARibbonMainWindow.h"
#include "SARibbonBar/SARibbonMenu.h"
#include "SARibbonBar/SARibbonQuickAccessBar.h"
#include <QLabel>

namespace Ui 
{
	void MainWindowRibbon::setupRibbonUi(QMainWindow *MainWindow)
	{
		SARibbonToolButton *btn;
		SARibbonMainWindow* ribbonwindow = qobject_cast<SARibbonMainWindow*>(MainWindow);
		if (!ribbonwindow)    return;

		//BaseUi::setupUi(), but not initialized menu and toolbar
		//the actions have initialized but not installed anywhere
		{
			if (MainWindow->objectName().isEmpty())
				MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
			MainWindow->setEnabled(true);
			MainWindow->resize(1678, 921);
			actionNew = new QAction(MainWindow);
			actionNew->setObjectName(QString::fromUtf8("actionNew"));
			QIcon icon;
			icon.addFile(QString::fromUtf8(":/QUI/icon/createNew.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionNew->setIcon(icon);
			actionOpen = new QAction(MainWindow);
			actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
			QIcon icon1;
			icon1.addFile(QString::fromUtf8(":/QUI/icon/open.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionOpen->setIcon(icon1);
			actionSave = new QAction(MainWindow);
			actionSave->setObjectName(QString::fromUtf8("actionSave"));
			actionSave->setEnabled(false);
			QIcon icon2;
			icon2.addFile(QString::fromUtf8(":/QUI/icon/save.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSave->setIcon(icon2);
			actionClose = new QAction(MainWindow);
			actionClose->setObjectName(QString::fromUtf8("actionClose"));
			QIcon icon3;
			icon3.addFile(QString::fromUtf8(":/QUI/icon/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionClose->setIcon(icon3);
			actionSaveAs = new QAction(MainWindow);
			actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
			actionSaveAs->setEnabled(false);
			QIcon icon4;
			icon4.addFile(QString::fromUtf8(":/QUI/icon/saveAs.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSaveAs->setIcon(icon4);
			actionChinese = new QAction(MainWindow);
			actionChinese->setObjectName(QString::fromUtf8("actionChinese"));
			actionChinese->setCheckable(true);
			QIcon icon5;
			icon5.addFile(QString::fromUtf8(":/QUI/icon/chinese_language.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionChinese->setIcon(icon5);
			actionEnglish = new QAction(MainWindow);
			actionEnglish->setObjectName(QString::fromUtf8("actionEnglish"));
			actionEnglish->setCheckable(true);
			QIcon icon6;
			icon6.addFile(QString::fromUtf8(":/QUI/icon/english_language.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionEnglish->setIcon(icon6);
			actionImportMesh = new QAction(MainWindow);
			actionImportMesh->setObjectName(QString::fromUtf8("actionImportMesh"));
			QIcon icon7;
			icon7.addFile(QString::fromUtf8(":/QUI/icon/importMesh.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionImportMesh->setIcon(icon7);
			actionImportGeometry = new QAction(MainWindow);
			actionImportGeometry->setObjectName(QString::fromUtf8("actionImportGeometry"));
			QIcon icon8;
			icon8.addFile(QString::fromUtf8(":/QUI/icon/importGeometry.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionImportGeometry->setIcon(icon8);
			actionWorkingDir = new QAction(MainWindow);
			actionWorkingDir->setObjectName(QString::fromUtf8("actionWorkingDir"));
			actionWorkingDir->setIcon(icon1);
			actionSolve = new QAction(MainWindow);
			actionSolve->setObjectName(QString::fromUtf8("actionSolve"));
			actionSolve->setEnabled(false);
			QIcon icon9;
			icon9.addFile(QString::fromUtf8(":/QUI/icon/solve.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSolve->setIcon(icon9);
			actionSolver_Manager = new QAction(MainWindow);
			actionSolver_Manager->setObjectName(QString::fromUtf8("actionSolver_Manager"));
			QIcon icon10;
			icon10.addFile(QString::fromUtf8(":/QUI/icon/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSolver_Manager->setIcon(icon10);
			actionViewXPlus = new QAction(MainWindow);
			actionViewXPlus->setObjectName(QString::fromUtf8("actionViewXPlus"));
			actionViewXPlus->setEnabled(false);
			QIcon icon11;
			icon11.addFile(QString::fromUtf8(":/QUI/icon/xPlus.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionViewXPlus->setIcon(icon11);
			actionViewXMinus = new QAction(MainWindow);
			actionViewXMinus->setObjectName(QString::fromUtf8("actionViewXMinus"));
			actionViewXMinus->setEnabled(false);
			QIcon icon12;
			icon12.addFile(QString::fromUtf8(":/QUI/icon/xMinus.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionViewXMinus->setIcon(icon12);
			actionViewYPlus = new QAction(MainWindow);
			actionViewYPlus->setObjectName(QString::fromUtf8("actionViewYPlus"));
			actionViewYPlus->setEnabled(false);
			QIcon icon13;
			icon13.addFile(QString::fromUtf8(":/QUI/icon/yPlus.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionViewYPlus->setIcon(icon13);
			actionViewYMinus = new QAction(MainWindow);
			actionViewYMinus->setObjectName(QString::fromUtf8("actionViewYMinus"));
			actionViewYMinus->setEnabled(false);
			QIcon icon14;
			icon14.addFile(QString::fromUtf8(":/QUI/icon/yMinus.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionViewYMinus->setIcon(icon14);
			actionViewZPlus = new QAction(MainWindow);
			actionViewZPlus->setObjectName(QString::fromUtf8("actionViewZPlus"));
			actionViewZPlus->setEnabled(false);
			QIcon icon15;
			icon15.addFile(QString::fromUtf8(":/QUI/icon/zPlus.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionViewZPlus->setIcon(icon15);
			actionViewZMinus = new QAction(MainWindow);
			actionViewZMinus->setObjectName(QString::fromUtf8("actionViewZMinus"));
			actionViewZMinus->setEnabled(false);
			QIcon icon16;
			icon16.addFile(QString::fromUtf8(":/QUI/icon/zMinus.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionViewZMinus->setIcon(icon16);
			actionFitView = new QAction(MainWindow);
			actionFitView->setObjectName(QString::fromUtf8("actionFitView"));
			actionFitView->setEnabled(false);
			QIcon icon17;
			icon17.addFile(QString::fromUtf8(":/QUI/icon/fit.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionFitView->setIcon(icon17);
			actionSelectOff = new QAction(MainWindow);
			actionSelectOff->setObjectName(QString::fromUtf8("actionSelectOff"));
			actionSelectOff->setCheckable(true);
			actionSelectOff->setChecked(true);
			actionSelectOff->setEnabled(false);
			QIcon icon18;
			icon18.addFile(QString::fromUtf8(":/QUI/icon/selectOff.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSelectOff->setIcon(icon18);
			actionSelectMeshNode = new QAction(MainWindow);
			actionSelectMeshNode->setObjectName(QString::fromUtf8("actionSelectMeshNode"));
			actionSelectMeshNode->setCheckable(true);
			actionSelectMeshNode->setEnabled(false);
			QIcon icon19;
			icon19.addFile(QString::fromUtf8(":/QUI/icon/selectNode.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSelectMeshNode->setIcon(icon19);
			actionSelectMeshCell = new QAction(MainWindow);
			actionSelectMeshCell->setObjectName(QString::fromUtf8("actionSelectMeshCell"));
			actionSelectMeshCell->setCheckable(true);
			actionSelectMeshCell->setEnabled(false);
			QIcon icon20;
			icon20.addFile(QString::fromUtf8(":/QUI/icon/selectElement.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSelectMeshCell->setIcon(icon20);
			actionSolve_Options = new QAction(MainWindow);
			actionSolve_Options->setObjectName(QString::fromUtf8("actionSolve_Options"));
			actionSolve_Options->setIcon(icon9);
			actionGraph_Options = new QAction(MainWindow);
			actionGraph_Options->setObjectName(QString::fromUtf8("actionGraph_Options"));
			QIcon icon21;
			icon21.addFile(QString::fromUtf8(":/QUI/icon/graphOption.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionGraph_Options->setIcon(icon21);
			actionSurfaceMesh = new QAction(MainWindow);
			actionSurfaceMesh->setObjectName(QString::fromUtf8("actionSurfaceMesh"));
			actionSurfaceMesh->setEnabled(false);
			QIcon icon22;
			icon22.addFile(QString::fromUtf8(":/QUI/icon/surfaceMesh.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSurfaceMesh->setIcon(icon22);
			actionSolidMesh = new QAction(MainWindow);
			actionSolidMesh->setObjectName(QString::fromUtf8("actionSolidMesh"));
			actionSolidMesh->setEnabled(false);
			QIcon icon23;
			icon23.addFile(QString::fromUtf8(":/QUI/icon/solidMesh.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSolidMesh->setIcon(icon23);
			actionExportMesh = new QAction(MainWindow);
			actionExportMesh->setObjectName(QString::fromUtf8("actionExportMesh"));
			actionExportMesh->setEnabled(false);
			QIcon icon24;
			icon24.addFile(QString::fromUtf8(":/QUI/icon/exportMesh.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionExportMesh->setIcon(icon24);
			actionUser_Manual = new QAction(MainWindow);
			actionUser_Manual->setObjectName(QString::fromUtf8("actionUser_Manual"));
			actionUser_Manual->setCheckable(true);
			actionUser_Manual->setChecked(true);
			QIcon icon25;
			icon25.addFile(QString::fromUtf8(":/QUI/icon/help.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionUser_Manual->setIcon(icon25);
			actionAbout = new QAction(MainWindow);
			actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
			QIcon icon26;
			icon26.addFile(QString::fromUtf8(":/QUI/icon/about_us.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionAbout->setIcon(icon26);
			actionDisplayNode = new QAction(MainWindow);
			actionDisplayNode->setObjectName(QString::fromUtf8("actionDisplayNode"));
			actionDisplayNode->setCheckable(true);
			actionDisplayNode->setEnabled(false);
			QIcon icon27;
			icon27.addFile(QString::fromUtf8(":/QUI/icon/node.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplayNode->setIcon(icon27);
			actionDisplayWireFrame = new QAction(MainWindow);
			actionDisplayWireFrame->setObjectName(QString::fromUtf8("actionDisplayWireFrame"));
			actionDisplayWireFrame->setCheckable(true);
			actionDisplayWireFrame->setChecked(false);
			actionDisplayWireFrame->setEnabled(false);
			QIcon icon28;
			icon28.addFile(QString::fromUtf8(":/QUI/icon/wireFrame.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplayWireFrame->setIcon(icon28);
			actionDisplaySurface = new QAction(MainWindow);
			actionDisplaySurface->setObjectName(QString::fromUtf8("actionDisplaySurface"));
			actionDisplaySurface->setCheckable(true);
			actionDisplaySurface->setEnabled(false);
			QIcon icon29;
			icon29.addFile(QString::fromUtf8(":/QUI/icon/face.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplaySurface->setIcon(icon29);
			actionCreate_Set = new QAction(MainWindow);
			actionCreate_Set->setObjectName(QString::fromUtf8("actionCreate_Set"));
			actionCreate_Set->setEnabled(false);
			QIcon icon30;
			icon30.addFile(QString::fromUtf8(":/QUI/icon/meshComponent.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreate_Set->setIcon(icon30);
			action2DPlot = new QAction(MainWindow);
			action2DPlot->setObjectName(QString::fromUtf8("action2DPlot"));
			QIcon icon31;
			icon31.addFile(QString::fromUtf8(":/QUI/window/2dplot.png"), QSize(), QIcon::Normal, QIcon::Off);
			action2DPlot->setIcon(icon31);
			action3DGraph = new QAction(MainWindow);
			action3DGraph->setObjectName(QString::fromUtf8("action3DGraph"));
			QIcon icon32;
			icon32.addFile(QString::fromUtf8(":/QUI/window/3dgraph.png"), QSize(), QIcon::Normal, QIcon::Off);
			action3DGraph->setIcon(icon32);
			actionSave_Script = new QAction(MainWindow);
			actionSave_Script->setObjectName(QString::fromUtf8("actionSave_Script"));
			QIcon icon33;
			icon33.addFile(QString::fromUtf8(":/QUI/icon/saveScript.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSave_Script->setIcon(icon33);
			actionExecute_Script = new QAction(MainWindow);
			actionExecute_Script->setObjectName(QString::fromUtf8("actionExecute_Script"));
			QIcon icon34;
			icon34.addFile(QString::fromUtf8(":/QUI/icon/execScript.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionExecute_Script->setIcon(icon34);
			actionGenMesh = new QAction(MainWindow);
			actionGenMesh->setObjectName(QString::fromUtf8("actionGenMesh"));
			actionGenMesh->setEnabled(false);
			QIcon icon35;
			icon35.addFile(QString::fromUtf8(":/QUI/icon/solumationsetting.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionGenMesh->setIcon(icon35);
			actionSave_Picture = new QAction(MainWindow);
			actionSave_Picture->setObjectName(QString::fromUtf8("actionSave_Picture"));
			QIcon icon36;
			icon36.addFile(QString::fromUtf8(":/QUI/icon/saveImage.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSave_Picture->setIcon(icon36);
			actionBoxMeshNode = new QAction(MainWindow);
			actionBoxMeshNode->setObjectName(QString::fromUtf8("actionBoxMeshNode"));
			actionBoxMeshNode->setCheckable(true);
			actionBoxMeshNode->setEnabled(false);
			QIcon icon37;
			icon37.addFile(QString::fromUtf8(":/QUI/icon/boxNode.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionBoxMeshNode->setIcon(icon37);
			actionBoxMeshCell = new QAction(MainWindow);
			actionBoxMeshCell->setObjectName(QString::fromUtf8("actionBoxMeshCell"));
			actionBoxMeshCell->setCheckable(true);
			actionBoxMeshCell->setEnabled(false);
			QIcon icon38;
			icon38.addFile(QString::fromUtf8(":/QUI/icon/boxCell.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionBoxMeshCell->setIcon(icon38);
			actionStart_Page = new QAction(MainWindow);
			actionStart_Page->setObjectName(QString::fromUtf8("actionStart_Page"));
			QIcon icon39;
			icon39.addFile(QString::fromUtf8(":/QUI/window/startpage.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionStart_Page->setIcon(icon39);
			actionPre_Window = new QAction(MainWindow);
			actionPre_Window->setObjectName(QString::fromUtf8("actionPre_Window"));
			QIcon icon40;
			icon40.addFile(QString::fromUtf8(":/QUI/window/preWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionPre_Window->setIcon(icon40);
			actionChecking = new QAction(MainWindow);
			actionChecking->setObjectName(QString::fromUtf8("actionChecking"));
			actionChecking->setEnabled(false);
			QIcon icon41;
			icon41.addFile(QString::fromUtf8(":/QUI/icon/meshChecking.png"), QSize(), QIcon::Active, QIcon::On);
			actionChecking->setIcon(icon41);
			actionCreateBox = new QAction(MainWindow);
			actionCreateBox->setObjectName(QString::fromUtf8("actionCreateBox"));
			QIcon icon42;
			icon42.addFile(QString::fromUtf8(":/QUI/geometry/box.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateBox->setIcon(icon42);
			actionCreateCylinder = new QAction(MainWindow);
			actionCreateCylinder->setObjectName(QString::fromUtf8("actionCreateCylinder"));
			QIcon icon43;
			icon43.addFile(QString::fromUtf8(":/QUI/geometry/cylinder.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateCylinder->setIcon(icon43);
			actionCreaterSphere = new QAction(MainWindow);
			actionCreaterSphere->setObjectName(QString::fromUtf8("actionCreaterSphere"));
			QIcon icon44;
			icon44.addFile(QString::fromUtf8(":/QUI/geometry/sphere.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreaterSphere->setIcon(icon44);
			actionChamfer = new QAction(MainWindow);
			actionChamfer->setObjectName(QString::fromUtf8("actionChamfer"));
			QIcon icon45;
			icon45.addFile(QString::fromUtf8(":/QUI/geometry/chamfer.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionChamfer->setIcon(icon45);
			actionFillet = new QAction(MainWindow);
			actionFillet->setObjectName(QString::fromUtf8("actionFillet"));
			QIcon icon46;
			icon46.addFile(QString::fromUtf8(":/QUI/geometry/fillet.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionFillet->setIcon(icon46);
			actionBoolCut = new QAction(MainWindow);
			actionBoolCut->setObjectName(QString::fromUtf8("actionBoolCut"));
			QIcon icon47;
			icon47.addFile(QString::fromUtf8(":/QUI/geometry/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionBoolCut->setIcon(icon47);
			actionBoolFause = new QAction(MainWindow);
			actionBoolFause->setObjectName(QString::fromUtf8("actionBoolFause"));
			QIcon icon48;
			icon48.addFile(QString::fromUtf8(":/QUI/geometry/fuse.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionBoolFause->setIcon(icon48);
			actionBoolCommon = new QAction(MainWindow);
			actionBoolCommon->setObjectName(QString::fromUtf8("actionBoolCommon"));
			QIcon icon49;
			icon49.addFile(QString::fromUtf8(":/QUI/geometry/common.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionBoolCommon->setIcon(icon49);
			actionUndo = new QAction(MainWindow);
			actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
			QIcon icon50;
			icon50.addFile(QString::fromUtf8(":/QUI/geometry/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionUndo->setIcon(icon50);
			actionRedo = new QAction(MainWindow);
			actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
			QIcon icon51;
			icon51.addFile(QString::fromUtf8(":/QUI/geometry/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionRedo->setIcon(icon51);
			actionExportGeometry = new QAction(MainWindow);
			actionExportGeometry->setObjectName(QString::fromUtf8("actionExportGeometry"));
			QIcon icon52;
			icon52.addFile(QString::fromUtf8(":/QUI/icon/exportGeometry.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionExportGeometry->setIcon(icon52);
			actionCreaterCone = new QAction(MainWindow);
			actionCreaterCone->setObjectName(QString::fromUtf8("actionCreaterCone"));
			QIcon icon53;
			icon53.addFile(QString::fromUtf8(":/QUI/geometry/cone.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreaterCone->setIcon(icon53);
			actionMirrorFeature = new QAction(MainWindow);
			actionMirrorFeature->setObjectName(QString::fromUtf8("actionMirrorFeature"));
			QIcon icon54;
			icon54.addFile(QString::fromUtf8(":/QUI/geometry/mirror.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionMirrorFeature->setIcon(icon54);
			actionVariable_Fillet = new QAction(MainWindow);
			actionVariable_Fillet->setObjectName(QString::fromUtf8("actionVariable_Fillet"));
			QIcon icon55;
			icon55.addFile(QString::fromUtf8(":/QUI/geometry/variableFillet.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionVariable_Fillet->setIcon(icon55);
			actionExtrude = new QAction(MainWindow);
			actionExtrude->setObjectName(QString::fromUtf8("actionExtrude"));
			QIcon icon56;
			icon56.addFile(QString::fromUtf8(":/QUI/geometry/extrude.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionExtrude->setIcon(icon56);
			actionCreate_Point = new QAction(MainWindow);
			actionCreate_Point->setObjectName(QString::fromUtf8("actionCreate_Point"));
			QIcon icon57;
			icon57.addFile(QString::fromUtf8(":/QUI/geometry/point.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreate_Point->setIcon(icon57);
			actionCreate_Line = new QAction(MainWindow);
			actionCreate_Line->setObjectName(QString::fromUtf8("actionCreate_Line"));
			QIcon icon58;
			icon58.addFile(QString::fromUtf8(":/QUI/geometry/line.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreate_Line->setIcon(icon58);
			actionCreate_Face = new QAction(MainWindow);
			actionCreate_Face->setObjectName(QString::fromUtf8("actionCreate_Face"));
			QIcon icon59;
			icon59.addFile(QString::fromUtf8(":/QUI/geometry/face.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreate_Face->setIcon(icon59);
			actionMoveFeature = new QAction(MainWindow);
			actionMoveFeature->setObjectName(QString::fromUtf8("actionMoveFeature"));
			QIcon icon60;
			icon60.addFile(QString::fromUtf8(":/QUI/geometry/move.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionMoveFeature->setIcon(icon60);
			actionRotateFeature = new QAction(MainWindow);
			actionRotateFeature->setObjectName(QString::fromUtf8("actionRotateFeature"));
			QIcon icon61;
			icon61.addFile(QString::fromUtf8(":/QUI/geometry/Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionRotateFeature->setIcon(icon61);
			actionRevol = new QAction(MainWindow);
			actionRevol->setObjectName(QString::fromUtf8("actionRevol"));
			QIcon icon62;
			icon62.addFile(QString::fromUtf8(":/QUI/geometry/revolve.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionRevol->setIcon(icon62);
			actionLoft = new QAction(MainWindow);
			actionLoft->setObjectName(QString::fromUtf8("actionLoft"));
			QIcon icon63;
			icon63.addFile(QString::fromUtf8(":/QUI/geometry/loft.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionLoft->setIcon(icon63);
			actionCreateDatumPlane = new QAction(MainWindow);
			actionCreateDatumPlane->setObjectName(QString::fromUtf8("actionCreateDatumPlane"));
			QIcon icon64;
			icon64.addFile(QString::fromUtf8(":/QUI/icon/datumPlane.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateDatumPlane->setIcon(icon64);
			actionDrawLine = new QAction(MainWindow);
			actionDrawLine->setObjectName(QString::fromUtf8("actionDrawLine"));
			actionDrawLine->setCheckable(false);
			QIcon icon65;
			icon65.addFile(QString::fromUtf8(":/QUI/icon/sketchLine.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDrawLine->setIcon(icon65);
			actionDrawRectangle = new QAction(MainWindow);
			actionDrawRectangle->setObjectName(QString::fromUtf8("actionDrawRectangle"));
			actionDrawRectangle->setCheckable(false);
			QIcon icon66;
			icon66.addFile(QString::fromUtf8(":/QUI/icon/sketchRectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDrawRectangle->setIcon(icon66);
			actionDrawCircle = new QAction(MainWindow);
			actionDrawCircle->setObjectName(QString::fromUtf8("actionDrawCircle"));
			actionDrawCircle->setCheckable(false);
			QIcon icon67;
			icon67.addFile(QString::fromUtf8(":/QUI/icon/sketchCircle.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDrawCircle->setIcon(icon67);
			actionCreate_Sketch = new QAction(MainWindow);
			actionCreate_Sketch->setObjectName(QString::fromUtf8("actionCreate_Sketch"));
			actionCreate_Sketch->setCheckable(true);
			QIcon icon68;
			icon68.addFile(QString::fromUtf8(":/QUI/icon/createSketch.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreate_Sketch->setIcon(icon68);
			actionDrawArc = new QAction(MainWindow);
			actionDrawArc->setObjectName(QString::fromUtf8("actionDrawArc"));
			actionDrawArc->setCheckable(false);
			actionDrawArc->setEnabled(true);
			QIcon icon69;
			icon69.addFile(QString::fromUtf8(":/QUI/icon/sketchArc.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDrawArc->setIcon(icon69);
			actionDrawPolyline = new QAction(MainWindow);
			actionDrawPolyline->setObjectName(QString::fromUtf8("actionDrawPolyline"));
			QIcon icon70;
			icon70.addFile(QString::fromUtf8(":/QUI/icon/sketchPolyLine.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDrawPolyline->setIcon(icon70);
			actionMakeMatrix = new QAction(MainWindow);
			actionMakeMatrix->setObjectName(QString::fromUtf8("actionMakeMatrix"));
			QIcon icon71;
			icon71.addFile(QString::fromUtf8(":/QUI/geometry/matrix.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionMakeMatrix->setIcon(icon71);
			actionSweep = new QAction(MainWindow);
			actionSweep->setObjectName(QString::fromUtf8("actionSweep"));
			QIcon icon72;
			icon72.addFile(QString::fromUtf8(":/QUI/geometry/sweep.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSweep->setIcon(icon72);
			actionDrawSpline = new QAction(MainWindow);
			actionDrawSpline->setObjectName(QString::fromUtf8("actionDrawSpline"));
			QIcon icon73;
			icon73.addFile(QString::fromUtf8(":/QUI/icon/sketchSpline.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDrawSpline->setIcon(icon73);
			actionDisplayPoint = new QAction(MainWindow);
			actionDisplayPoint->setObjectName(QString::fromUtf8("actionDisplayPoint"));
			actionDisplayPoint->setCheckable(true);
			actionDisplayPoint->setChecked(false);
			QIcon icon74;
			icon74.addFile(QString::fromUtf8(":/QUI/geometry/pointDisplay.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplayPoint->setIcon(icon74);
			actionDisplayCurve = new QAction(MainWindow);
			actionDisplayCurve->setObjectName(QString::fromUtf8("actionDisplayCurve"));
			actionDisplayCurve->setCheckable(true);
			actionDisplayCurve->setChecked(false);
			QIcon icon75;
			icon75.addFile(QString::fromUtf8(":/QUI/geometry/edgeDisplay.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplayCurve->setIcon(icon75);
			actionDisplayFace = new QAction(MainWindow);
			actionDisplayFace->setObjectName(QString::fromUtf8("actionDisplayFace"));
			actionDisplayFace->setCheckable(true);
			actionDisplayFace->setChecked(true);
			QIcon icon76;
			icon76.addFile(QString::fromUtf8(":/QUI/geometry/facedisplay.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplayFace->setIcon(icon76);
			actionSelectPoint = new QAction(MainWindow);
			actionSelectPoint->setObjectName(QString::fromUtf8("actionSelectPoint"));
			actionSelectPoint->setCheckable(true);
			QIcon icon77;
			icon77.addFile(QString::fromUtf8(":/QUI/geometry/selectpoint.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSelectPoint->setIcon(icon77);
			actionSelectCurve = new QAction(MainWindow);
			actionSelectCurve->setObjectName(QString::fromUtf8("actionSelectCurve"));
			actionSelectCurve->setCheckable(true);
			QIcon icon78;
			icon78.addFile(QString::fromUtf8(":/QUI/geometry/selectwire.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSelectCurve->setIcon(icon78);
			actionSelectFace = new QAction(MainWindow);
			actionSelectFace->setObjectName(QString::fromUtf8("actionSelectFace"));
			actionSelectFace->setCheckable(true);
			QIcon icon79;
			icon79.addFile(QString::fromUtf8(":/QUI/geometry/selectface.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSelectFace->setIcon(icon79);
			actionSelectGeometryBody = new QAction(MainWindow);
			actionSelectGeometryBody->setObjectName(QString::fromUtf8("actionSelectGeometryBody"));
			actionSelectGeometryBody->setCheckable(true);
			QIcon icon80;
			icon80.addFile(QString::fromUtf8(":/QUI/geometry/selectbody.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSelectGeometryBody->setIcon(icon80);
			actionPluginManager = new QAction(MainWindow);
			actionPluginManager->setObjectName(QString::fromUtf8("actionPluginManager"));
			QIcon icon81;
			icon81.addFile(QString::fromUtf8(":/QUI/icon/pluginManager.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionPluginManager->setIcon(icon81);
			actionUser_Guidance = new QAction(MainWindow);
			actionUser_Guidance->setObjectName(QString::fromUtf8("actionUser_Guidance"));
			actionUser_Guidance->setCheckable(true);
			actionUser_Guidance->setChecked(true);
			QIcon icon82;
			icon82.addFile(QString::fromUtf8(":/QUI/icon/userguidance.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionUser_Guidance->setIcon(icon82);
			actionMeasure_Distance = new QAction(MainWindow);
			actionMeasure_Distance->setObjectName(QString::fromUtf8("actionMeasure_Distance"));
			QIcon icon83;
			icon83.addFile(QString::fromUtf8(":/QUI/geometry/geoMeasure.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionMeasure_Distance->setIcon(icon83);
			actionMeasure = new QAction(MainWindow);
			actionMeasure->setObjectName(QString::fromUtf8("actionMeasure"));
			actionGeoSplitter = new QAction(MainWindow);
			actionGeoSplitter->setObjectName(QString::fromUtf8("actionGeoSplitter"));
			QIcon icon84;
			icon84.addFile(QString::fromUtf8(":/QUI/geometry/geoSSplit.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionGeoSplitter->setIcon(icon84);
			actionCreateGeoComponent = new QAction(MainWindow);
			actionCreateGeoComponent->setObjectName(QString::fromUtf8("actionCreateGeoComponent"));
			actionCreateGeoComponent->setEnabled(false);
			QIcon icon85;
			icon85.addFile(QString::fromUtf8(":/QUI/geometry/geoComponent.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateGeoComponent->setIcon(icon85);
			actionFluidMesh = new QAction(MainWindow);
			actionFluidMesh->setObjectName(QString::fromUtf8("actionFluidMesh"));
			actionFluidMesh->setEnabled(false);
			QIcon icon86;
			icon86.addFile(QString::fromUtf8(":/QUI/icon/meshFluid.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionFluidMesh->setIcon(icon86);
			actionFilterMesh = new QAction(MainWindow);
			actionFilterMesh->setObjectName(QString::fromUtf8("actionFilterMesh"));
			actionFilterMesh->setEnabled(false);
			QIcon icon87;
			icon87.addFile(QString::fromUtf8(":/QUI/icon/meshFilter.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionFilterMesh->setIcon(icon87);
			actionFillHole = new QAction(MainWindow);
			actionFillHole->setObjectName(QString::fromUtf8("actionFillHole"));
			QIcon icon88;
			icon88.addFile(QString::fromUtf8(":/QUI/geometry/geoFillHole.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionFillHole->setIcon(icon88);
			actionRemoveSurface = new QAction(MainWindow);
			actionRemoveSurface->setObjectName(QString::fromUtf8("actionRemoveSurface"));
			QIcon icon89;
			icon89.addFile(QString::fromUtf8(":/QUI/geometry/geoRemoveFace.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionRemoveSurface->setIcon(icon89);
			actionFillGap = new QAction(MainWindow);
			actionFillGap->setObjectName(QString::fromUtf8("actionFillGap"));
			QIcon icon90;
			icon90.addFile(QString::fromUtf8(":/QUI/geometry/geoFixSurface.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionFillGap->setIcon(icon90);
			actionVTKTranslation = new QAction(MainWindow);
			actionVTKTranslation->setObjectName(QString::fromUtf8("actionVTKTranslation"));
			actionVTKTranslation->setCheckable(false);
			actionVTKTranslation->setEnabled(false);
			QIcon icon91;
			icon91.addFile(QString::fromUtf8(":/QUI/icon/meshmodeling.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionVTKTranslation->setIcon(icon91);
			actionNormal = new QAction(MainWindow);
			actionNormal->setObjectName(QString::fromUtf8("actionNormal"));
			actionNormal->setCheckable(false);
			actionRibbon = new QAction(MainWindow);
			actionRibbon->setObjectName(QString::fromUtf8("actionRibbon"));
			actionRibbon->setCheckable(false);
			actionOpenPostFile = new QAction(MainWindow);
			actionOpenPostFile->setObjectName(QString::fromUtf8("actionOpenPostFile"));
            QIcon iconOpenPostFile;
            iconOpenPostFile.addFile(QString::fromUtf8(":/QUI/post/open.png"), QSize(), QIcon::Normal, QIcon::Off);
            actionOpenPostFile->setIcon(iconOpenPostFile);
			actionDisplayPoints = new QAction(MainWindow);
			actionDisplayPoints->setObjectName(QString::fromUtf8("actionDisplayPoints"));
			QIcon icon92;
			icon92.addFile(QString::fromUtf8(":/QUI/post/rep_point.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplayPoints->setIcon(icon92);
			actionDisplayWireframe = new QAction(MainWindow);
			actionDisplayWireframe->setObjectName(QString::fromUtf8("actionDisplayWireframe"));
			QIcon icon93;
			icon93.addFile(QString::fromUtf8(":/QUI/post/rep_wireFrame.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplayWireframe->setIcon(icon93);
			actionDisplaySurfaceWithoutEdge = new QAction(MainWindow);
			actionDisplaySurfaceWithoutEdge->setObjectName(QString::fromUtf8("actionDisplaySurfaceWithoutEdge"));
			QIcon icon94;
			icon94.addFile(QString::fromUtf8(":/QUI/post/rep_surface.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplaySurfaceWithoutEdge->setIcon(icon94);
			actionDisplaySurfaceWithEdge = new QAction(MainWindow);
			actionDisplaySurfaceWithEdge->setObjectName(QString::fromUtf8("actionDisplaySurfaceWithEdge"));
			QIcon icon95;
			icon95.addFile(QString::fromUtf8(":/QUI/post/rep_surfaceWithEdge.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionDisplaySurfaceWithEdge->setIcon(icon95);
			actionCreateVector = new QAction(MainWindow);
			actionCreateVector->setObjectName(QString::fromUtf8("actionCreateVector"));
			QIcon icon96;
			icon96.addFile(QString::fromUtf8(":/QUI/post/vector.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateVector->setIcon(icon96);
			actionCreateClip = new QAction(MainWindow);
			actionCreateClip->setObjectName(QString::fromUtf8("actionCreateClip"));
			QIcon icon97;
			icon97.addFile(QString::fromUtf8(":/QUI/post/clip.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateClip->setIcon(icon97);
			actionCreateSlice = new QAction(MainWindow);
			actionCreateSlice->setObjectName(QString::fromUtf8("actionCreateSlice"));
			QIcon icon98;
			icon98.addFile(QString::fromUtf8(":/QUI/post/slice.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateSlice->setIcon(icon98);
			actionCreateStreamLine = new QAction(MainWindow);
			actionCreateStreamLine->setObjectName(QString::fromUtf8("actionCreateStreamLine"));
			QIcon icon99;
			icon99.addFile(QString::fromUtf8(":/QUI/post/streamline.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateStreamLine->setIcon(icon99);
			actionCreateISOCurve = new QAction(MainWindow);
			actionCreateISOCurve->setObjectName(QString::fromUtf8("actionCreateISOCurve"));
            QIcon iconISOCurve;
            iconISOCurve.addFile(QString::fromUtf8(":/QUI/post/isocurve.png"), QSize(), QIcon::Normal, QIcon::Off);
            actionCreateISOCurve->setIcon(iconISOCurve);
			actionCreateISOSurface = new QAction(MainWindow);
			actionCreateISOSurface->setObjectName(QString::fromUtf8("actionCreateISOSurface"));
			QIcon icon100;
			icon100.addFile(QString::fromUtf8(":/QUI/post/isosurf.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateISOSurface->setIcon(icon100);
			actionCreateCalculator = new QAction(MainWindow);
			actionCreateCalculator->setObjectName(QString::fromUtf8("actionCreateCalculator"));
			QIcon icon101;
			icon101.addFile(QString::fromUtf8(":/QUI/post/calculator.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateCalculator->setIcon(icon101);
			actionCreateReflection = new QAction(MainWindow);
			actionCreateReflection->setObjectName(QString::fromUtf8("actionCreateReflection"));
			QIcon icon102;
			icon102.addFile(QString::fromUtf8(":/QUI/post/Reflection.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionCreateReflection->setIcon(icon102);
			actionSaveImage = new QAction(MainWindow);
			actionSaveImage->setObjectName(QString::fromUtf8("actionSaveImage"));
			QIcon icon103;
			icon103.addFile(QString::fromUtf8(":/QUI/post/saveImage.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSaveImage->setIcon(icon103);
			actionSaveVideo = new QAction(MainWindow);
			actionSaveVideo->setObjectName(QString::fromUtf8("actionSaveVideo"));
			QIcon icon104;
			icon104.addFile(QString::fromUtf8(":/QUI/post/video.png"), QSize(), QIcon::Normal, QIcon::Off);
			actionSaveVideo->setIcon(icon104);

			actionGeoMeshRotate = new QAction(MainWindow);
			actionGeoMeshRotate->setObjectName(QString::fromUtf8("actionGeoMeshRotate"));
			QIcon icon105;
			icon105.addFile(QString::fromUtf8(":/QUI/icon/vector.png"), QSize(), QIcon::Normal, QIcon::Off);
            actionGeoMeshRotate->setIcon(icon105);

			centralwidget = new QWidget(MainWindow);
			centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
			gridLayout = new QGridLayout(centralwidget);
			gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
			mdiArea = new QMdiArea(centralwidget);
			mdiArea->setObjectName(QString::fromUtf8("mdiArea"));

			gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

			MainWindow->setCentralWidget(centralwidget);
			statusbar = new QStatusBar(MainWindow);
			statusbar->setObjectName(QString::fromUtf8("statusbar"));
			MainWindow->setStatusBar(statusbar);
		}

		// toolbar to ribbon
		SARibbonBar* ribbon = ribbonwindow->ribbonBar();
		ribbon->setRibbonStyle(SARibbonBar::WpsLiteStyleTwoRow);
		ribbon->quickAccessBar()->addAction(actionNew);
		ribbon->quickAccessBar()->addAction(actionOpen);
		ribbon->quickAccessBar()->addAction(actionSave);
		{
			QPushButton* filebutton = dynamic_cast<QPushButton*>(ribbon->applicationButton());
			menuFile = new QMenu(ribbonwindow);
			{
				filebutton->setText(QObject::tr("File"));
				menuFile->addAction(actionNew);
				menuFile->addAction(actionOpen);
				menuFile->addAction(actionClose);
				menuFile->addSeparator();
				menuFile->addAction(actionImportMesh);
				menuFile->addAction(actionExportMesh);
				menuFile->addAction(actionImportGeometry);
				menuFile->addAction(actionExportGeometry);
				menuFile->addSeparator();
				menuFile->addAction(actionSave);
				menuFile->addAction(actionSaveAs);
				menuFile->addSeparator();
				menuFile->addAction(actionSave_Script);
				menuFile->addAction(actionExecute_Script);
				menuFile->addSeparator();
				menuFile->addAction(actionSave_Picture);
				menuFile->addAction(actionWorkingDir);
				menuFile->addSeparator();
				filebutton->setMenu(menuFile);
			}

			//home
			home_page = ribbon->addCategoryPage(QObject::tr("Home"));
			new_pannel = home_page->addPannel(QObject::tr("File"));
			solve_pannel = home_page->addPannel(QObject::tr("Case"));
			import_mesh_pannel = home_page->addPannel(QObject::tr("Import Mesh"));
			import_geometry_pannel = home_page->addPannel(QObject::tr("Import Geometry"));
			exec_script_pannel = home_page->addPannel(QObject::tr("Script"));
			adapt_window_pannel_home = home_page->addPannel(QObject::tr("View"));
			save_picture_pannel = home_page->addPannel(QObject::tr("Save Picture"));
			plugin_manager_pannel = home_page->addPannel(QObject::tr("Plugin Manager"));
			drawing_option_pannel_home = home_page->addPannel(QObject::tr("Other"));
			{
				new_pannel->addLargeAction(actionNew);
				new_pannel->addMediumAction(actionOpen);
				new_pannel->addMediumAction(actionSave);
				solve_pannel->addLargeAction(actionSolve);
				import_mesh_pannel->addLargeAction(actionImportMesh);
				import_geometry_pannel->addLargeAction(actionImportGeometry);
				exec_script_pannel->addMediumAction(actionExecute_Script);
				exec_script_pannel->addMediumAction(actionSave_Script);
				adapt_window_pannel_home->addLargeAction(actionFitView);
				adapt_window_pannel_home->addSmallAction(actionViewXPlus);
				adapt_window_pannel_home->addSmallAction(actionViewXMinus);
				adapt_window_pannel_home->addSmallAction(actionViewYPlus);
				adapt_window_pannel_home->addSmallAction(actionViewYMinus);
				adapt_window_pannel_home->addSmallAction(actionViewZPlus);
				adapt_window_pannel_home->addSmallAction(actionViewZMinus);
				save_picture_pannel->addLargeAction(actionSave_Picture);
				plugin_manager_pannel->addLargeAction(actionPluginManager);
				drawing_option_pannel_home->addLargeAction(actionGraph_Options);
				QMenu* languageMenu = new QMenu(MainWindow);
				languageMenu->addAction(actionChinese);
				languageMenu->addAction(actionEnglish);
				QAction* languageAction = new QAction(MainWindow);
				QIcon language_Icon;
				language_Icon.addFile(QString::fromUtf8(":/QUI/icon/language.png"), QSize(), QIcon::Normal, QIcon::Off);
				languageAction->setIcon(language_Icon);
				languageAction->setText(QCoreApplication::translate("MainWindow", "Language", nullptr));
				languageAction->setMenu(languageMenu);
				btn = drawing_option_pannel_home->addLargeAction(languageAction);
				btn->setPopupMode(QToolButton::InstantPopup);

				QMenu* styleMenu = new QMenu(MainWindow);
				styleMenu->addAction(actionNormal);
				styleMenu->addAction(actionRibbon);
				QAction* styleAction = new QAction(MainWindow);
				QIcon style_Icon;
				style_Icon.addFile(QString::fromUtf8(":/QUI/icon/graphOption.png"), QSize(), QIcon::Normal, QIcon::Off);
				styleAction->setIcon(style_Icon);
				styleAction->setText(QCoreApplication::translate("MainWindow", "Style", nullptr));
				styleAction->setMenu(styleMenu);
				btn = drawing_option_pannel_home->addLargeAction(styleAction);
				btn->setPopupMode(QToolButton::InstantPopup);
			}

			//geometry
			geometry_page = ribbon->addCategoryPage(QObject::tr("Geometry"));
			sketch_pannel_geometry = geometry_page->addPannel(QObject::tr("Geometry Sketch"));
			cube_pannel = geometry_page->addPannel(QObject::tr("Create Solid Geometry"));
			create_point_pannel = geometry_page->addPannel(QObject::tr("Create Plane Geometry"));
			base_plate_pannel = geometry_page->addPannel(QObject::tr("Create Datum Plane"));
			sum_pannel = geometry_page->addPannel(QObject::tr("Calculate"));
			stretch_pannel = geometry_page->addPannel(QObject::tr("Operation"));
			display_surface_pannel = geometry_page->addPannel(QObject::tr("Display"));
			clear_choice_pannel_geometry = geometry_page->addPannel(QObject::tr("Select"));
			segmentation_pannel = geometry_page->addPannel(QObject::tr("Modify"));
			chamfer_pannel = geometry_page->addPannel(QObject::tr("Chamfer"));
			measure_pannel = geometry_page->addPannel(QObject::tr("Measure and Create"));
			undo_redo_pannel_geometry = geometry_page->addPannel(QObject::tr("Edit"));
			{
				sketch_pannel_geometry->addLargeAction(actionCreate_Sketch);
				cube_pannel->addSmallAction(actionCreateBox);
				cube_pannel->addSmallAction(actionCreateCylinder);
				cube_pannel->addSmallAction(actionCreaterCone);
				cube_pannel->addSmallAction(actionCreaterSphere);
				create_point_pannel->addLargeAction(actionCreate_Point);
				create_point_pannel->addMediumAction(actionCreate_Line);
				create_point_pannel->addMediumAction(actionCreate_Face);
//				base_plate_pannel->addLargeAction(actionCreateDatumPlane);
				base_plate_pannel->addLargeAction(actionGeoMeshRotate);
				sum_pannel->addLargeAction(actionBoolFause);
				sum_pannel->addMediumAction(actionBoolCut);
				sum_pannel->addMediumAction(actionBoolCommon);
				stretch_pannel->addSmallAction(actionExtrude);
				stretch_pannel->addSmallAction(actionRevol);
				stretch_pannel->addSmallAction(actionMoveFeature);
				stretch_pannel->addSmallAction(actionMirrorFeature);
				stretch_pannel->addSmallAction(actionRotateFeature);
				stretch_pannel->addSmallAction(actionMakeMatrix);
				stretch_pannel->addSmallAction(actionLoft);
				stretch_pannel->addSmallAction(actionSweep);
				display_surface_pannel->addLargeAction(actionDisplayFace);
				display_surface_pannel->addSmallAction(actionDisplayCurve);
				display_surface_pannel->addSmallAction(actionDisplayPoint);
				clear_choice_pannel_geometry->addLargeAction(actionSelectOff);
				clear_choice_pannel_geometry->addSmallAction(actionSelectPoint);
				clear_choice_pannel_geometry->addSmallAction(actionSelectCurve);
				clear_choice_pannel_geometry->addSmallAction(actionSelectFace);
				clear_choice_pannel_geometry->addSmallAction(actionSelectGeometryBody);
				segmentation_pannel->addSmallAction(actionGeoSplitter);
				segmentation_pannel->addSmallAction(actionFillHole);
				segmentation_pannel->addSmallAction(actionRemoveSurface);
				segmentation_pannel->addSmallAction(actionFillGap);
				chamfer_pannel->addLargeAction(actionChamfer);
				chamfer_pannel->addMediumAction(actionFillet);
				chamfer_pannel->addMediumAction(actionVariable_Fillet);
				measure_pannel->addMediumAction(actionMeasure_Distance);
				measure_pannel->addMediumAction(actionCreateGeoComponent);		
				undo_redo_pannel_geometry->addLargeAction(actionUndo);
				undo_redo_pannel_geometry->addLargeAction(actionRedo);
			}

			//mesh
			mesh_page = ribbon->addCategoryPage(QObject::tr("Mesh"));
			surface_mesh_subdivision_pannel = mesh_page->addPannel(QObject::tr("Mesh Subdivision"));
			mesh_quailty_examine_pannel = mesh_page->addPannel(QObject::tr("Mesh Operation"));
			clear_choice_pannel_mesh = mesh_page->addPannel(QObject::tr("Mesh Selection"));
			display_node_pannel = mesh_page->addPannel(QObject::tr("Mesh Display"));
			create_set_pannel = mesh_page->addPannel(QObject::tr("Mesh Creation"));
			{
				surface_mesh_subdivision_pannel->addLargeAction(actionSurfaceMesh);
				surface_mesh_subdivision_pannel->addMediumAction(actionSolidMesh);
				surface_mesh_subdivision_pannel->addMediumAction(actionFluidMesh);
				mesh_quailty_examine_pannel->addLargeAction(actionChecking);
				mesh_quailty_examine_pannel->addMediumAction(actionFilterMesh);
				mesh_quailty_examine_pannel->addMediumAction(actionVTKTranslation);
				clear_choice_pannel_mesh->addLargeAction(actionSelectOff);
				clear_choice_pannel_mesh->addSmallAction(actionSelectMeshNode);
				clear_choice_pannel_mesh->addSmallAction(actionBoxMeshNode);
				clear_choice_pannel_mesh->addSmallAction(actionSelectMeshCell);
				clear_choice_pannel_mesh->addSmallAction(actionBoxMeshCell);
				display_node_pannel->addLargeAction(actionDisplayNode);
				display_node_pannel->addSmallAction(actionDisplaySurface);
				display_node_pannel->addSmallAction(actionDisplayWireFrame);
				create_set_pannel->addLargeAction(actionCreate_Set);
				create_set_pannel->addLargeAction(actionGenMesh);
			}

			//solve
			solve_page = ribbon->addCategoryPage(QObject::tr("Solve"));
			solver_management_pannel = solve_page->addPannel(QObject::tr("Solver Manager"));
			{
				solver_management_pannel->addLargeAction(actionSolver_Manager);
				solver_management_pannel->addLargeAction(actionSolve);
			}

			//window
			window_page = ribbon->addCategoryPage(QObject::tr("Windows"));
			start_page_pannel = window_page->addPannel(QObject::tr("Start Page"));
			adapt_window_pannel_window = window_page->addPannel(QObject::tr("Adapt Page"));
			drawing_option_pannel_window = window_page->addPannel(QObject::tr("Drawing Option"));
			{
				start_page_pannel->addLargeAction(actionStart_Page);
				start_page_pannel->addLargeAction(actionPre_Window);
				start_page_pannel->addLargeAction(action2DPlot);
				start_page_pannel->addLargeAction(action3DGraph);
				adapt_window_pannel_window->addLargeAction(actionFitView);
				adapt_window_pannel_window->addSmallAction(actionViewXPlus);
				adapt_window_pannel_window->addSmallAction(actionViewXMinus);
				adapt_window_pannel_window->addSmallAction(actionViewYPlus);
				adapt_window_pannel_window->addSmallAction(actionViewYMinus);
				adapt_window_pannel_window->addSmallAction(actionViewZPlus);
				adapt_window_pannel_window->addSmallAction(actionViewZMinus);
				drawing_option_pannel_window->addLargeAction(actionGraph_Options);
			}

			//post
			post_page = ribbon->addCategoryPage(QObject::tr("3DRender"));
			post_base_pannel = post_page->addPannel(QString());
			post_viewer_pannel = post_page->addPannel(QString());
			post_editor_pannel = post_page->addPannel(QString());
			{
				post_base_pannel->addLargeAction(actionOpenPostFile);
				post_base_pannel->addLargeAction(actionSaveImage);
				post_base_pannel->addLargeAction(actionSaveVideo);
				post_viewer_pannel->addSmallAction(actionDisplayPoints);
				post_viewer_pannel->addSmallAction(actionDisplayWireFrame);
				post_viewer_pannel->addSmallAction(actionDisplaySurfaceWithoutEdge);
				post_viewer_pannel->addSmallAction(actionDisplaySurfaceWithEdge);
				post_editor_pannel->addSmallAction(actionCreateClip);
				post_editor_pannel->addSmallAction(actionCreateSlice);
				post_editor_pannel->addSmallAction(actionCreateISOSurface);
				post_editor_pannel->addSmallAction(actionCreateISOCurve);
				post_editor_pannel->addSmallAction(actionCreateVector);
				post_editor_pannel->addSmallAction(actionCreateStreamLine);
				post_editor_pannel->addSmallAction(actionCreateCalculator);
				post_editor_pannel->addSmallAction(actionCreateReflection);
			}

			//help
			help_page = ribbon->addCategoryPage(QObject::tr( "Help"));
			user_guide_pannel = help_page->addPannel(QObject::tr("User Guide"));
			{
				user_guide_pannel->addLargeAction(actionUser_Guidance);
				user_guide_pannel->addLargeAction(actionUser_Manual);
				user_guide_pannel->addLargeAction(actionAbout);
			}

			//sketch_tool
			sketch_tool_context = ribbon->addContextCategory(QString(), Qt::red, "sketch tool");
			sketch_tool_page = sketch_tool_context->addCategoryPage(QObject::tr("Sketch Tool"));
			sketch_pannel_sketch_tool = sketch_tool_page->addPannel(QObject::tr("Sketch"));
			draw_line_pannel = sketch_tool_page->addPannel(QObject::tr("Sketch Drawing"));
			undo_redo_pannel_sketch = sketch_tool_page->addPannel(QObject::tr("Sketch Edit"));
			{
				sketch_pannel_sketch_tool->addLargeAction(actionCreate_Sketch);
				draw_line_pannel->addLargeAction(actionDrawLine);
				draw_line_pannel->addLargeAction(actionDrawRectangle);
				draw_line_pannel->addLargeAction(actionDrawCircle);
				draw_line_pannel->addLargeAction(actionDrawArc);
				draw_line_pannel->addLargeAction(actionDrawPolyline);
				draw_line_pannel->addLargeAction(actionDrawSpline);
				undo_redo_pannel_sketch->addLargeAction(actionUndo);
				undo_redo_pannel_sketch->addLargeAction(actionRedo);
			}			
		}
		retranslateRibbonUi(MainWindow);
		QMetaObject::connectSlotsByName(MainWindow);
	}

	void MainWindowRibbon::retranslateRibbonUi(QMainWindow *MainWindow)
	{
		//BaseUi::retranslateUi()
		{
			MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FastCAE", nullptr));
			actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
#if QT_CONFIG(tooltip)
			actionNew->setToolTip(QCoreApplication::translate("MainWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
			actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
			actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(tooltip)
			actionOpen->setToolTip(QCoreApplication::translate("MainWindow", "Open", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
			actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
			actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
			actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
			actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
#if QT_CONFIG(tooltip)
			actionClose->setToolTip(QCoreApplication::translate("MainWindow", "Close", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
			actionClose->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
			actionSaveAs->setText(QCoreApplication::translate("MainWindow", "SaveAs", nullptr));
#if QT_CONFIG(shortcut)
			actionSaveAs->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
			actionChinese->setText(QCoreApplication::translate("MainWindow", "Chinese", nullptr));
#if QT_CONFIG(tooltip)
			actionChinese->setToolTip(QCoreApplication::translate("MainWindow", "Chinese", nullptr));
#endif // QT_CONFIG(tooltip)
			actionEnglish->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
#if QT_CONFIG(tooltip)
			actionEnglish->setToolTip(QCoreApplication::translate("MainWindow", "English", nullptr));
#endif // QT_CONFIG(tooltip)
			actionImportMesh->setText(QCoreApplication::translate("MainWindow", "Import Mesh", nullptr));
#if QT_CONFIG(shortcut)
			actionImportMesh->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
			actionImportGeometry->setText(QCoreApplication::translate("MainWindow", "Import Geometry", nullptr));
#if QT_CONFIG(shortcut)
			actionImportGeometry->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+G", nullptr));
#endif // QT_CONFIG(shortcut)
			actionWorkingDir->setText(QCoreApplication::translate("MainWindow", "WorkingDir", nullptr));
			actionSolve->setText(QCoreApplication::translate("MainWindow", "Solve", nullptr));
#if QT_CONFIG(shortcut)
			actionSolve->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
			actionSolver_Manager->setText(QCoreApplication::translate("MainWindow", "Solver Manager", nullptr));
			actionViewXPlus->setText(QCoreApplication::translate("MainWindow", "ViewXPlus", nullptr));
			actionViewXMinus->setText(QCoreApplication::translate("MainWindow", "ViewXMinus", nullptr));
			actionViewYPlus->setText(QCoreApplication::translate("MainWindow", "ViewYPlus", nullptr));
			actionViewYMinus->setText(QCoreApplication::translate("MainWindow", "ViewYMinus", nullptr));
			actionViewZPlus->setText(QCoreApplication::translate("MainWindow", "ViewZPlus", nullptr));
			actionViewZMinus->setText(QCoreApplication::translate("MainWindow", "ViewZMinus", nullptr));
			actionFitView->setText(QCoreApplication::translate("MainWindow", "FitView", nullptr));
			actionSelectOff->setText(QCoreApplication::translate("MainWindow", "selectOff", nullptr));
			actionSelectMeshNode->setText(QCoreApplication::translate("MainWindow", "selectMeshNode", nullptr));
			actionSelectMeshCell->setText(QCoreApplication::translate("MainWindow", "selectMeshCell", nullptr));
			actionSolve_Options->setText(QCoreApplication::translate("MainWindow", "Solve Options", nullptr));
			actionGraph_Options->setText(QCoreApplication::translate("MainWindow", "Graph Options", nullptr));
			actionSurfaceMesh->setText(QCoreApplication::translate("MainWindow", "SurfaceMesh", nullptr));
			actionSolidMesh->setText(QCoreApplication::translate("MainWindow", "SolidMesh", nullptr));
			actionExportMesh->setText(QCoreApplication::translate("MainWindow", "Export Mesh", nullptr));
#if QT_CONFIG(shortcut)
			actionExportMesh->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
			actionUser_Manual->setText(QCoreApplication::translate("MainWindow", "User Manual", nullptr));
			actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
			actionDisplayNode->setText(QCoreApplication::translate("MainWindow", "DisplayNode", nullptr));
			actionDisplayWireFrame->setText(QCoreApplication::translate("MainWindow", "DisplayWireFrame", nullptr));
			actionDisplaySurface->setText(QCoreApplication::translate("MainWindow", "DisplaySurface", nullptr));
//			actionDisplaySurfaceEdge->setText(QCoreApplication::translate("MainWindow", "DisplaySurfaceEdge", nullptr));
#if QT_CONFIG(tooltip)
//			actionDisplaySurfaceEdge->setToolTip(QCoreApplication::translate("MainWindow", "DisplaySurfaceEdge", nullptr));
#endif // QT_CONFIG(tooltip)
			actionCreate_Set->setText(QCoreApplication::translate("MainWindow", "Create Set", nullptr));
			action2DPlot->setText(QCoreApplication::translate("MainWindow", "2D Plot", nullptr));
			action3DGraph->setText(QCoreApplication::translate("MainWindow", "3D Graph", nullptr));
			actionSave_Script->setText(QCoreApplication::translate("MainWindow", "Save Script", nullptr));
			actionExecute_Script->setText(QCoreApplication::translate("MainWindow", "Execute Script", nullptr));
#if QT_CONFIG(shortcut)
			actionExecute_Script->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
			actionGenMesh->setText(QCoreApplication::translate("MainWindow", "GenMesh", nullptr));
			actionSave_Picture->setText(QCoreApplication::translate("MainWindow", "Save Picture", nullptr));
			actionBoxMeshNode->setText(QCoreApplication::translate("MainWindow", "BoxMeshNode", nullptr));
			actionBoxMeshCell->setText(QCoreApplication::translate("MainWindow", "BoxMeshCell", nullptr));
			actionStart_Page->setText(QCoreApplication::translate("MainWindow", "Start Page", nullptr));
			actionPre_Window->setText(QCoreApplication::translate("MainWindow", "Pre Window", nullptr));
			actionChecking->setText(QCoreApplication::translate("MainWindow", "Checking", nullptr));
			actionCreateBox->setText(QCoreApplication::translate("MainWindow", "CreateBox", nullptr));
			actionCreateCylinder->setText(QCoreApplication::translate("MainWindow", "CreateCylinder", nullptr));
			actionCreaterSphere->setText(QCoreApplication::translate("MainWindow", "CreaterSphere", nullptr));
			actionChamfer->setText(QCoreApplication::translate("MainWindow", "Chamfer", nullptr));
			actionFillet->setText(QCoreApplication::translate("MainWindow", "Fillet", nullptr));
			actionBoolCut->setText(QCoreApplication::translate("MainWindow", "BoolCut", nullptr));
			actionBoolFause->setText(QCoreApplication::translate("MainWindow", "BoolFause", nullptr));
			actionBoolCommon->setText(QCoreApplication::translate("MainWindow", "BoolCommon", nullptr));
			actionUndo->setText(QCoreApplication::translate("MainWindow", "undo", nullptr));
#if QT_CONFIG(shortcut)
			actionUndo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
			actionRedo->setText(QCoreApplication::translate("MainWindow", "redo", nullptr));
#if QT_CONFIG(shortcut)
			actionRedo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
			actionExportGeometry->setText(QCoreApplication::translate("MainWindow", "ExportGeometry", nullptr));
			actionCreaterCone->setText(QCoreApplication::translate("MainWindow", "CreaterCone", nullptr));
			actionMirrorFeature->setText(QCoreApplication::translate("MainWindow", "MirrorFeature", nullptr));
			actionVariable_Fillet->setText(QCoreApplication::translate("MainWindow", "Variable Fillet", nullptr));
			actionExtrude->setText(QCoreApplication::translate("MainWindow", "Extrude", nullptr));
			actionCreate_Point->setText(QCoreApplication::translate("MainWindow", "Create Point", nullptr));
			actionCreate_Line->setText(QCoreApplication::translate("MainWindow", "Create Line", nullptr));
			actionCreate_Face->setText(QCoreApplication::translate("MainWindow", "Create_Surface", nullptr));
			actionMoveFeature->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
			actionRotateFeature->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
			actionRevol->setText(QCoreApplication::translate("MainWindow", "Revol", nullptr));
			actionLoft->setText(QCoreApplication::translate("MainWindow", "loft", nullptr));
			actionCreateDatumPlane->setText(QCoreApplication::translate("MainWindow", "Create Datum Plane", nullptr));
			actionDrawLine->setText(QCoreApplication::translate("MainWindow", "DrawLine", nullptr));
			actionDrawRectangle->setText(QCoreApplication::translate("MainWindow", "DrawRectangle", nullptr));
			actionDrawCircle->setText(QCoreApplication::translate("MainWindow", "DrawCircle", nullptr));
			actionCreate_Sketch->setText(QCoreApplication::translate("MainWindow", "Create Sketch", nullptr));
			actionDrawArc->setText(QCoreApplication::translate("MainWindow", "DrawArc", nullptr));
			actionDrawPolyline->setText(QCoreApplication::translate("MainWindow", "DrawPolyline", nullptr));
			actionMakeMatrix->setText(QCoreApplication::translate("MainWindow", "MakeMatrix", nullptr));
#if QT_CONFIG(tooltip)
			actionMakeMatrix->setToolTip(QCoreApplication::translate("MainWindow", "MakeMatrix", nullptr));
#endif // QT_CONFIG(tooltip)
			actionSweep->setText(QCoreApplication::translate("MainWindow", "Sweep", nullptr));
			actionDrawSpline->setText(QCoreApplication::translate("MainWindow", "DrawSpline", nullptr));
			actionDisplayPoint->setText(QCoreApplication::translate("MainWindow", "DisplayPoint", nullptr));
			actionDisplayCurve->setText(QCoreApplication::translate("MainWindow", "DisplayCurve", nullptr));
			actionDisplayFace->setText(QCoreApplication::translate("MainWindow", "DisplayFace", nullptr));
			actionSelectPoint->setText(QCoreApplication::translate("MainWindow", "SelectPoint", nullptr));
			actionSelectCurve->setText(QCoreApplication::translate("MainWindow", "SelectCurve", nullptr));
			actionSelectFace->setText(QCoreApplication::translate("MainWindow", "SelectFace", nullptr));
			actionSelectGeometryBody->setText(QCoreApplication::translate("MainWindow", "SelectGeometryBody", nullptr));
			actionPluginManager->setText(QCoreApplication::translate("MainWindow", "Plugin Manager", nullptr));
#if QT_CONFIG(tooltip)
			actionPluginManager->setToolTip(QCoreApplication::translate("MainWindow", "Plugin Manager", nullptr));
#endif // QT_CONFIG(tooltip)
			actionUser_Guidance->setText(QCoreApplication::translate("MainWindow", "User Guidance", nullptr));
			actionMeasure_Distance->setText(QCoreApplication::translate("MainWindow", "Measure Distance", nullptr));
			actionMeasure->setText(QCoreApplication::translate("MainWindow", "Measure", nullptr));
			actionGeoSplitter->setText(QCoreApplication::translate("MainWindow", "Split", nullptr));
			actionCreateGeoComponent->setText(QCoreApplication::translate("MainWindow", "CreateGeoComponent", nullptr));
			actionFluidMesh->setText(QCoreApplication::translate("MainWindow", "FluidMesh", nullptr));
			actionFilterMesh->setText(QCoreApplication::translate("MainWindow", "FilterMesh", nullptr));
			actionFillHole->setText(QCoreApplication::translate("MainWindow", "FillHole", nullptr));
			actionRemoveSurface->setText(QCoreApplication::translate("MainWindow", "RemoveSurface", nullptr));
			actionFillGap->setText(QCoreApplication::translate("MainWindow", "FillGap", nullptr));
			actionVTKTranslation->setText(QCoreApplication::translate("MainWindow", "Mesh Modeling", nullptr));
			actionGeoMeshRotate->setText(QCoreApplication::translate("MainWindow", "GeoMeshRotate", nullptr));
			actionNormal->setText(QCoreApplication::translate("MainWindow", "Normal", nullptr));
			actionRibbon->setText(QCoreApplication::translate("MainWindow", "Ribbon", nullptr));
			actionOpenPostFile->setText(QCoreApplication::translate("MainWindow", "OpenPostFile", nullptr));
			actionDisplayPoints->setText(QCoreApplication::translate("MainWindow", "DisplayPoints", nullptr));
			actionDisplayWireframe->setText(QCoreApplication::translate("MainWindow", "DisplayWireframe", nullptr));
			actionDisplaySurfaceWithoutEdge->setText(QCoreApplication::translate("MainWindow", "DisplaySurfaceWithoutEdge", nullptr));
			actionDisplaySurfaceWithEdge->setText(QCoreApplication::translate("MainWindow", "DisplaySurfaceWithEdge", nullptr));
			actionCreateVector->setText(QCoreApplication::translate("MainWindow", "CreateVector", nullptr));
			actionCreateClip->setText(QCoreApplication::translate("MainWindow", "CreateClip", nullptr));
			actionCreateSlice->setText(QCoreApplication::translate("MainWindow", "CreateSlice", nullptr));
			actionCreateStreamLine->setText(QCoreApplication::translate("MainWindow", "CreateStreamLine", nullptr));
			actionCreateISOCurve->setText(QCoreApplication::translate("MainWindow", "CreateISOCurve", nullptr));
			actionCreateISOSurface->setText(QCoreApplication::translate("MainWindow", "CreateISOSurface", nullptr));
			actionCreateCalculator->setText(QCoreApplication::translate("MainWindow", "CreateCalculator", nullptr));
			actionCreateReflection->setText(QCoreApplication::translate("MainWindow", "CreateReflection", nullptr));
			actionSaveImage->setText(QCoreApplication::translate("MainWindow", "SaveImage", nullptr));
			actionSaveVideo->setText(QCoreApplication::translate("MainWindow", "SaveVideo", nullptr));
#if QT_CONFIG(tooltip)
			actionSaveVideo->setToolTip(QCoreApplication::translate("MainWindow", "SaveVideo", nullptr));
#endif // QT_CONFIG(tooltip)
		}

		SARibbonMainWindow* ribbonwindow = qobject_cast<SARibbonMainWindow*>(MainWindow);
		ribbonwindow->ribbonBar()->applicationButton()->setText(QObject::tr("File"));
		home_page->setWindowTitle(QObject::tr("Home"));
		geometry_page->setWindowTitle(QObject::tr("Geometry"));
		mesh_page->setWindowTitle(QObject::tr("Mesh"));
		solve_page->setWindowTitle(QObject::tr("Solve"));
		window_page->setWindowTitle(QObject::tr("Windows"));
		help_page->setWindowTitle(QObject::tr("Help"));
		sketch_tool_page->setWindowTitle(QObject::tr("Sketch"));
		auto actions = drawing_option_pannel_home->actions();
		actions.at(1)->setText(QObject::tr("Language"));
		actions.at(2)->setText(QObject::tr("Style"));
	} // retranslateUi
}
