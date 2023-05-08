#ifndef POSTINFOWIDGET_H
#define POSTINFOWIDGET_H

#include "PostInterfaceAPI.h"
#include <QTreeWidget>
#include "PostRenderData/RenderDataObject.h"

namespace GUI
{
    class MainWindow;
}

namespace Ui
{
    class PostInfoWidget;
}

class QTableWidget;
class QTableWidgetItem;

namespace Post
{

    class RenderDataManager;
    class RenderDataObject;

    class POSTINTERFACEAPI PostInfoWidget : public QWidget
    {
        Q_OBJECT

    public:
        PostInfoWidget(GUI::MainWindow* m, QWidget* parent = 0);
        ~PostInfoWidget();

        /**
         * @brief enum型返回QString型
         * @param ObjType类型
         */
        QString enumToString(Post::ObjType type);
		void reTranslate();

	private:
		QString getRenderDataObjectType(RenderDataObject* obj);

    private slots:
        /**
         * @brief 更新表格
         */
        void updatePostTable(QTreeWidgetItem* item);

    private:
        Ui::PostInfoWidget* _ui{};
        QWidget* _parent{};
        GUI::MainWindow* _mainWindow{ nullptr };
        RenderDataManager* _dataManager{ nullptr };
    };
}
#endif // POSTINFOWIDGET_H
