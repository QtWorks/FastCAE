#ifndef _POSTFUNCTION_DIALOG_BASE_H_
#define _POSTFUNCTION_DIALOG_BASE_H_

#include <QDialog>

namespace Py
{
	class PythonAgent;
}

namespace Post
{
	class PostTreeWidget;
	class RenderDataObject;
	class RenderDataManager;
	class RenderWindowManager;

	class PostFunctionDialogBase : public QDialog
	{
		Q_OBJECT

	public:
		PostFunctionDialogBase(PostTreeWidget *tree, QWidget *parent = nullptr);
		virtual ~PostFunctionDialogBase() = 0;

	protected:
		QStringList getSeletedDataCode(QString name);

	protected slots:
		void setParentObject();

	private:
		virtual void updateDisplayInterface();

	protected:
		PostTreeWidget *_tree{nullptr};
		RenderDataManager *_dataManager{nullptr};
		RenderWindowManager *_windowManager{nullptr};
		RenderDataObject *_parentObject{nullptr};
		Py::PythonAgent *_pyAgent{nullptr};
		RenderDataObject *_editObject{nullptr};
	};
}

#endif // !_POST_FUNCTION_DIALOG_BASE_H_
