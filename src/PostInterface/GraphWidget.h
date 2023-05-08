#ifndef _GRAPHWIDGET_H_
#define _GRAPHWIDGET_H_

#include <QWidget>
#include "PostRenderData/Macros.hxx"
#include "PostInterfaceAPI.h"

ForwardDeclarNS(Ui, GraphWidget)
ForwardDeclar(vtkRenderWindow)
ForwardDeclar(vtkRenderer)
ForwardDeclar(vtkOrientationMarkerWidget)
ForwardDeclar(vtkRenderWindowInteractor)
ForwardDeclar(vtkTextWidget)

namespace Post {
	ForwardDeclar(RenderDataObject)

	class POSTINTERFACEAPI GraphWidget : public QWidget
	{
		Q_OBJECT

			AddPropertyReadOnly(int, ID, -1)
			AddPropertyReadOnly(int, PostType, -1)
			AddPropertySetOverride(int, PostDisplayMode, 2)
			//AddPtrListProperty(RenderDataObject, ObjectList)
	public:
		GraphWidget(int id, int type, QWidget* parent = nullptr);
		~GraphWidget();
		/**
		 * @brief 强制刷新渲染
		 */
		void reRender();

		/**
		 * @brief 渲染对象
		 */
		bool renderObject(RenderDataObject* obj);
		/**
		 * @brief 移除渲染对象
		 */
		void removeObject(RenderDataObject* obj);
		/**
		 * @brief 设置视角
		 */
		void setView(double lookX, double lookY, double lookZ,
			double upX, double upY, double upZ,
			double posX, double posY, double posZ);
		/**
		 * @brief 适应视角
		 */
		void fitView();
		/**
		 * @brief 保存图片
		 * @param file 文件名称
		 * @return 是否保存成功
		 */
		bool saveImage(QString file);
		/**
		 * @brief 是否激活坐标系
		 * @param  enable  是否激活
		 */
		void enabelAxis(bool enable);
		/**
		 * @brief 设置背景颜色
		 * @param  top     顶部颜色
		 * @param  bottom  底部颜色
		 */
		void setBackground(double* top, double* bottom);
		/**
		* @brief 添加灯光
		* @param wid 窗口id
		* @param color 灯光颜色
		* @param position 灯光位置
		* @param focalPoint 焦点位置
		*/
		void addLight(double* color, double* position, double* focalPoint);
		/**
		* @brief 删除灯光
		* @param wid 窗口id
		* @param index 灯光索引
		*/
		void deleteLight(int index);
		/**
		* @brief 刷新灯光
		* @param wid 窗口id
		* @param index 灯光索引
		* @param color 灯光颜色
		* @param position 灯光位置
		* @param focalPoint 焦点位置
		*/
		void refreshLight(int index, double* color, double* position, double* focalPoint);
		/**
		* @brief 获取窗口所有灯光数量
		*/
		const int getNumberOfLights();

		/**
		* @brief 获取交互器
		*/
		vtkRenderWindowInteractor* getInteractor();

		vtkRenderWindow* getRenderWindow();

		/**
		* @brief 设置后处理窗口标题
		* @param wid 窗口id
		* @param text 标题内容
		* @param color 标题颜色
		* @param pos 标题位置:x,y
		* @param size 标题尺寸:width,height
		* @param movable 标题是否可移动：默认可移动
		* @param visible 标题是否可见：默认可见
		*/
		bool setRenderTitle(const char* text, double* color, double* pos, double* size, bool movable = true, bool visible = true);
		/**
		* @brief 设置标题内容
		* @param wid 窗口id
		* @param text 标题内容
		*/
		bool setRenderTitleText(const char* text);
		/**
		* @brief 设置标题颜色
		* @param wid 窗口id
		* @param color 标题颜色
		*/
		bool setRenderTitleColor(double* color);
		/**
		* @brief 设置标题位置(相对)
		* @param wid 窗口id
		* @param xCoor x坐标:范围0-1
		* @param yCoor y坐标:范围0-1
		*/
		bool setRendetTitlePosition(double xCoor, double yCoor);
		/**
		* @brief 设置标题尺寸(相对)
		* @param wid 窗口id
		* @param width 宽度:范围0-1
		* @param height 高度:范围0-1
		*/
		bool setRendetTitleSize(double width, double height);
		/**
		* @brief 设置标题可见性
		* @param wid 窗口id
		* @param visible true-可见，false-不可见
		*/
		bool setRenderTitleVisible(bool visible);
		/**
		* @brief 设置标题可移动性
		* @param wid 窗口id
		* @param move true-可移动，false-不可移动
		*/
		bool setRenderTitleMovale(bool move);

		

	Q_SIGNALS:
		/**
		 * @brief  渲染窗口关闭，在析构函数触发
		 * @param  w  关闭的窗口，析构函数触发为this
		 */
		void widgetClosed(GraphWidget* w);

	private:
		/**
		 * @brief 右键菜单
		 * @param  event   My Param doc
		 */
		void contextMenuEvent(QContextMenuEvent *event) override;

	private:
		Ui::GraphWidget* _ui{};
		/**
		 * @brief 渲染窗口
		 */
		vtkRenderWindow* _renderWindow{};
		/**
		 * @brief 渲染画布
		 */
		vtkRenderer* _renderer{};
		/**
		 * @brief 坐标系窗口
		 */
		vtkOrientationMarkerWidget* _axesWidget{};

		vtkTextWidget* _textWidget{};

		QList<RenderDataObject*> _ObjectList{};
	};

}
#endif
