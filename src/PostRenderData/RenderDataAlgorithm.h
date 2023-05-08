#ifndef _RENDERDATA_ALGORITHM_H_
#define _RENDERDATA_ALGORITHM_H_

#include "RenderDataObject.h"
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkAppendFilter.h>
#include <QMultiHash>

namespace Post {
	enum AlgorithmType
	{
		AlgNone,
		ISO,  //等值面等值线
		ISOCurve,
		Vector, //矢量图
		Slice, //切片
		Clip,// 切割
		StreamLine, //流线
		Simplify,  //轻量化 
		Calculator,//计算器
		Reflection,//镜像
	};


	class POSTRENDERDATAAPI RenderDataAlgorithm : public RenderDataObject
	{
		//过滤器（绘图）类型标记
		AddProperty(AlgorithmType, AlgoType, AlgorithmType::AlgNone)

	public:
		RenderDataAlgorithm(RenderDataObject* parent);
		virtual ~RenderDataAlgorithm() = default;

		/**
		 * @brief 强制类型转换
		 * @param  obj  基类指针
		 * @return ViewDataAlgorithm*
		 */
		static RenderDataAlgorithm* SafeDownCast(RenderDataObject* obj);

		virtual void setName(QString name);

		virtual void setSelectedObjectHash(QMultiHash<int,int> hash);

		virtual QMultiHash<int, int> getSelectedObjectHash();

	protected:
		//更新参数
		virtual  void updateParam();
		void combineSelectedObjects();
		
	protected:
		bool _isCombination{ false };

	protected:
		DeclarVTKSmartPtr(vtkDataSetMapper, _mapper)
		DeclarVTKSmartPtr(vtkActor, _actor)
		DeclarVTKSmartPtr(vtkAppendFilter, _append)

		RenderProperty* _algorithmProperty{ nullptr };
		QMultiHash<int, int> _selectedObjects{};
	};

}
#endif