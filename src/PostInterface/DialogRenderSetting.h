#ifndef DIALOGRENDERSETTING_H
#define DIALOGRENDERSETTING_H

#include "PostRenderData/Macros.hxx"
#include <QDialog>

ForwardDeclar(QSlider)
ForwardDeclar(QSpinBox)
ForwardDeclar(QTreeWidgetItem)
ForwardDeclarNS(Ui, RenderSettingDialog)

namespace Post {
	ForwardDeclar(RenderProperty)
	ForwardDeclar(RenderDataObject)
	ForwardDeclar(GraphWidget)
	ForwardDeclar(PostTreeWidget)

	class RenderSettingDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit RenderSettingDialog(PostTreeWidget* tree, RenderDataObject* obj, QWidget *parent = nullptr);
		~RenderSettingDialog();

	private:
		void init();
		void initVariableTreeWidget(int loc, QStringList arrayList);
		QString getVariableType(int loc,int type);
		void getCurrentVariable(QString& name, int& loc, int& index);
		void getRenderPropertyList();

	private slots:
		void on_variableColorPushButton_clicked();
		void on_variableColorCheckBox_clicked();
		void on_colorBarCheckBox_clicked();
		void setTransparency(const int value);
		void setColorByVariable(QTreeWidgetItem* item);
		

	private:
		Ui::RenderSettingDialog *_ui;
		RenderDataObject* _dataObject{ nullptr };
		QList<RenderProperty*> _propertyList{};
		GraphWidget* _renderWindow{ nullptr };
		PostTreeWidget* _tree{ nullptr };
	};
}
#endif // DIALOGRENDERSETTING_H
