#include "DialogCreateCalculate.h"

#include "PostRenderData/CalculateRenderDataAlg.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostTreeWidget.h"
#include "PythonModule/PyAgent.h"
#include "RenderDirector.h"
#include "ui_DialogCreateCalculate.h"

#include <QMenu>
#include <QMessageBox>

namespace Post {
	CreateCalculateDialog::CreateCalculateDialog(PostTreeWidget* tree, QWidget* parent)
		: PostFunctionDialogBase(tree, parent)
		, _ui(new Ui::CreateCalculateDialog)
	{
		_ui->setupUi(this);
		init();
	}

	CreateCalculateDialog::~CreateCalculateDialog()
	{
		delete _ui;
	}

	void CreateCalculateDialog::init()
	{
		_ui->nameLineEdit->setText(tr("CalculateResult"));
		_operationList.clear();
		_scalarMenu = new QMenu(this);
		_vectorMenu = new QMenu(this);

		_ui->scalarPushButton->setMenu(_scalarMenu);
		_ui->vectorPushButton->setMenu(_vectorMenu);

		setParentObject();
	}

	void CreateCalculateDialog::accept()
	{
		if(_parentObject == nullptr) {
			QMessageBox::warning(this, tr("Warning!"), tr("No selected data!"));
			return;
		}

		QString		name = _ui->nameLineEdit->text();
		QString		exp	 = _ui->expressionLineEdit->text().trimmed();

		QStringList codes{};

		codes += QString("calculate = PostProcess.Calculate()");
		codes += QString("calculate.setParentID(%1)").arg(_parentObject->getID());
		codes += QString("calculate.setName('%1')").arg(name);
		codes += QString("calculate.setUsePointData(%1)").arg(_isPoint);
		codes += QString("calculate.setFunction('%1')").arg(exp);

		for(auto v : _scalarList)
			codes += QString("calculate.appendScalar('%1')").arg(v);
		for(auto v : _vectorList)
			codes += QString("calculate.appendVector('%1')").arg(v);

		codes += this->getSeletedDataCode("calculate");
		codes += QString("calculate.create()");

		_pyAgent->submit(codes);

		// 		CalculateRenderDataAlg* alg = new CalculateRenderDataAlg(_parentObject);
		//
		// 		alg->setSelectedObjectHash(_tree->getSelectedData(_parentObject));
		// 		alg->clearInputScalars();
		// 		alg->clearInputVectors();
		// 		alg->setUsePointData(_isPoint);
		// 		alg->setFunction(exp);
		// 		alg->setResultArrayName(name);
		//
		// 		for (auto v : _scalarList)
		// 			alg->appendInputScalars(v);
		// 		for (auto v : _vectorList)
		// 			alg->appendInputVectors(v);
		//
		// 		alg->updateParam();
		// 		alg->updateAlg();
		// 		alg->update();
		//
		// 		_parentObject->appendSubObjects(alg);
		// 		RenderDirector::getInstance()->renderDataObjectToWindow(alg,
		// _parentObject->getRenderWinID());
		//		_tree->updatePostTree();
		QDialog::accept();
		this->close();
	}

	void CreateCalculateDialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void CreateCalculateDialog::updateDisplayInterface()
	{
		if(_parentObject == nullptr)
			return;
		QAction* action = nullptr;

		_scalarMenu->clear();
		_vectorMenu->clear();

		auto createMenu = [=, &action](QStringList arrayList) {
			for(auto array : arrayList) {
				auto type = _parentObject->variableType(1, array);
				if(type == "scalar") {
					action = _scalarMenu->addAction(array);
					connect(action, &QAction::triggered, [=] {
						setExpression(array);
						if(!_scalarList.contains(array))
							_scalarList.append(array);
					});
				} else if(type == "vector") {
					action = _vectorMenu->addAction(array);
					connect(action, &QAction::triggered, [=] {
						setExpression(array);
						if(!_vectorList.contains(array))
							_vectorList.append(array);
					});
				}
			}
		};

		if(_isPoint) {
			QStringList pArray = _parentObject->getPointDataArray();
			createMenu(pArray);
		} else {
			QStringList cArray = _parentObject->getCellDataArray();
			createMenu(cArray);
		}
	}

	void CreateCalculateDialog::setExpression(QString exp)
	{
		// 		QString text = _ui->expressionLineEdit->text();
		// 		text = text + exp;
		// 		_ui->expressionLineEdit->setText(text);
		_ui->expressionLineEdit->blockSignals(true);
		_operationList.append(exp);
		_ui->expressionLineEdit->setText(_operationList.join(""));
		_ui->expressionLineEdit->blockSignals(false);
	}

	void CreateCalculateDialog::on_addPushButton_clicked()
	{
		setExpression("+");
	}

	void CreateCalculateDialog::on_minusPushButton_clicked()
	{
		setExpression("-");
	}

	void CreateCalculateDialog::on_multiplyPushButton_clicked()
	{
		setExpression("*");
	}

	void CreateCalculateDialog::on_dividedPushButton_clicked()
	{
		setExpression("/");
	}

	void CreateCalculateDialog::on_openParenPushButton_clicked()
	{
		setExpression("(");
	}

	void CreateCalculateDialog::on_closeParenPushButton_clicked()
	{
		setExpression(")");
	}

	void CreateCalculateDialog::on_iHatPushButton_clicked()
	{
		setExpression("iHat");
	}

	void CreateCalculateDialog::on_jHatPushButton_clicked()
	{
		setExpression("jHat");
	}

	void CreateCalculateDialog::on_kHatPushButton_clicked()
	{
		setExpression("kHat");
	}

	void CreateCalculateDialog::on_sinPushButton_clicked()
	{
		setExpression("sin(");
	}

	void CreateCalculateDialog::on_cosPushButton_clicked()
	{
		setExpression("cos(");
	}

	void CreateCalculateDialog::on_tanPushButton_clicked()
	{
		setExpression("tan(");
	}

	void CreateCalculateDialog::on_asinPushButton_clicked()
	{
		setExpression("asin(");
	}

	void CreateCalculateDialog::on_acosPushButton_clicked()
	{
		setExpression("acos(");
	}

	void CreateCalculateDialog::on_atanPushButton_clicked()
	{
		setExpression("atan(");
	}

	void CreateCalculateDialog::on_sinhPushButton_clicked()
	{
		setExpression("sinh(");
	}

	void CreateCalculateDialog::on_coshPushButton_clicked()
	{
		setExpression("cosh(");
	}

	void CreateCalculateDialog::on_tanhPushButton_clicked()
	{
		setExpression("tanh(");
	}

	void CreateCalculateDialog::on_absPushButton_clicked()
	{
		setExpression("abs(");
	}

	void CreateCalculateDialog::on_sqrtPushButton_clicked()
	{
		setExpression("sqrt(");
	}

	void CreateCalculateDialog::on_signPushButton_clicked()
	{
		setExpression("sign(");
	}

	void CreateCalculateDialog::on_lnPushButton_clicked()
	{
		setExpression("ln(");
	}

	void CreateCalculateDialog::on_logPushButton_clicked()
	{
		setExpression("log10(");
	}

	void CreateCalculateDialog::on_ceilPushButton_clicked()
	{
		setExpression("ceil(");
	}

	void CreateCalculateDialog::on_floorPushButton_clicked()
	{
		setExpression("floor(");
	}

	void CreateCalculateDialog::on_minPushButton_clicked()
	{
		setExpression("min(");
	}

	void CreateCalculateDialog::on_maxPushButton_clicked()
	{
		setExpression("max(");
	}

	void CreateCalculateDialog::on_superscriptPushButton_clicked()
	{
		setExpression("^");
	}

	void CreateCalculateDialog::on_expPushButton_clicked()
	{
		setExpression("exp(");
	}

	void CreateCalculateDialog::on_dotPushButton_clicked()
	{
		setExpression("dot(");
	}

	void CreateCalculateDialog::on_pointPushButton_clicked()
	{
		setExpression(".");
	}

	void CreateCalculateDialog::on_crossPushButton_clicked()
	{
		setExpression("cross(");
	}

	void CreateCalculateDialog::on_magPushButton_clicked()
	{
		setExpression("mag(");
	}

	void CreateCalculateDialog::on_normPushButton_clicked()
	{
		setExpression("norm(");
	}

	void CreateCalculateDialog::on_backPushButton_clicked()
	{
		_ui->expressionLineEdit->blockSignals(true);
		_operationList.removeLast();
		_ui->expressionLineEdit->setText(_operationList.join(""));
		_ui->expressionLineEdit->blockSignals(false);
	}

	void CreateCalculateDialog::on_clearPushButton_clicked()
	{
		_ui->expressionLineEdit->blockSignals(true);
		_ui->expressionLineEdit->clear();
		_operationList.clear();
		_ui->expressionLineEdit->blockSignals(false);
	}

	void CreateCalculateDialog::on_expressionLineEdit_textChanged(QString text)
	{
		QString exp = _operationList.join("");
		text.remove(exp);
		if(text.isEmpty())
			return;
		_operationList.append(text);
	}

	void CreateCalculateDialog::on_typeComboBox_currentIndexChanged(int index)
	{
		if(index == 0)
			_isPoint = true;
		else
			_isPoint = false;
	}

} // namespace Post