#include "DialogSaveAnimation.h"
#include "ui_DialogSaveAnimation.h"
#include "AnimationToolBar.h"
#include "PythonModule/PyAgent.h"
#include <QFileDialog>

namespace Post
{
	SaveAnimationDialog::SaveAnimationDialog(AnimationToolBar *toolBar, QWidget *parent) : QDialog(parent),
																						   _ui(new Ui::SaveAnimationDialog),
																						   _animation(toolBar)
	{
		_ui->setupUi(this);
		_fps = -1;
		_id = -1;
	}

	SaveAnimationDialog::~SaveAnimationDialog()
	{
		delete _ui;
	}

	void SaveAnimationDialog::getAnimationInfo(int &id, QString &file, int &fps)
	{
		id = _id;
		file = _file;
		fps = _fps;
	}

	void SaveAnimationDialog::init()
	{
		QString path;
		int fps = 15;
		_animation->getAviSetting(path, fps);
		_ui->rateSpinBox->setValue(fps);
		_ui->pathLineEdit->setText(path);
	}

	void SaveAnimationDialog::accept()
	{
		QString file = _ui->pathLineEdit->text().trimmed();
		int fps = _ui->rateSpinBox->value();
		auto id = _animation->getCurrentObjectID();

		if (file.isEmpty() || (id == -1))
			return;

		// 		_animation->setAviSetting(file, fps);
		// 		_animation->on_RunAnimation();

		// 		QString code = QString("PostProcess.savePostAnimation(%1,'%2',%3)").arg(id).arg(file).arg(fps);
		// 		Py::PythonAgent::getInstance()->submit(code);

		_id = id;
		_fps = fps;
		_file = file;

		QDialog::accept();
		this->close();
	}

	void SaveAnimationDialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void SaveAnimationDialog::on_selectPushButton_clicked()
	{
		QString filePath = _ui->pathLineEdit->text().trimmed();
		if (filePath.isEmpty())
			filePath = qApp->applicationDirPath();

		QString path = QFileDialog::getSaveFileName(this, tr("Select File"), filePath, "AVI files(*.avi)");
		if (path.isEmpty())
			return;
		_ui->pathLineEdit->setText(path);
	}
}