#ifndef _MODULETYPE_H_
#define _MODULETYPE_H_

namespace ModuleBase
{
	/**
	 * @brief 模块类别
	 * @since 2.5.0
	 */
	enum ModuleType
	{
		Undefined = -1,	 ///< 未定义
		ProjectWindows,	 ///< 工程窗口
		PropertyWindows, ///< 属性窗口
		MessageWindows,	 ///< 消息窗口
		ProcessWindows,	 ///< 进程窗口
		DesignWindow,	 ///< 设计窗口
		GraphWindows,	 ///< 绘图窗口
		Menu,			 ///< 菜单
		ToolBar,		 ///< 工具栏
		IO,				 ///< IO

	};
	/**
	 * @brief 绘图窗口类别
	 * @since 2.5.0
	 */
	enum GraphWindowType
	{
		UnDefined = -1, ///< 未定义
		PreWindows = 0, ///< 前处理窗口
		RealTime = 1,	///< 实时曲线窗口
		Post2D = 2,		///< 后处理二维窗口
		Post3D = 3,		///< 后处理三维窗口
	};
	/**
	 * @brief 选择模式
	 * @since 2.5.0
	 */
	enum SelectModel
	{
		None = -1,
		GeometryWinBody,
		GeometryWinSurface,
		GeometryWinCurve,
		GeometryWinPoint,
		GeometryBody,
		GeometrySurface,
		GeometryCurve,
		GeometryPoint,
		MeshNode,
		MeshCell,
		BoxMeshNode,
		BoxMeshCell,
		DrawSketch,
	};

	/**
	 * @brief 草绘类别
	 * @since 2.5.0
	 */
	enum SketchType
	{
		SketchNone,		///< 无
		SketchLine,		///< 线模
		SketchRect,		///< 矩形
		SketchCircle,	///< 圆
		SketchArc,		///< 弧线
		SketchPolyline, ///< 多段线
		SketchSpline,	///< 样条曲线
	};
}

#endif
