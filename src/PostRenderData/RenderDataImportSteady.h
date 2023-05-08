#ifndef _RENDERDATAIMPORTSTEADY_H_
#define _RENDERDATAIMPORTSTEADY_H_

#include "RenderDataObject.h"
#include <QString>
#include <vtkSmartPointer.h>

namespace Post {
	class POSTRENDERDATAAPI RenderDataImportSteady : public RenderDataObject
	{
		//文件名称
		AddPropertyReadOnly(QString, FileName)
			//是否定常分析结果
		AddProperty(bool, Steady, true)
			//文件后缀
		AddPropertyReadOnly(QString, Suffix)

	public:
		RenderDataImportSteady(const QString& files);
		virtual ~RenderDataImportSteady() = default;

		/**
		 * @brief 强制类型装换
		 * @param  obj  基类指针
		 * @return ViewDataImportSteady*
		 */
		static RenderDataImportSteady* SafeDownCast(RenderDataObject* obj);

		/**
		 * @brief 获取分块数量
		 * @return int 分区数目
		 */
		int getBlockCount();
		/**
		 * @brief 获取分区名称列表
		 * @return QStringList 名称列表
		 */
		QStringList getBlockNames();
		/**
		 * @brief 设置分区显示状态
		 * @param  index   分区索引
		 * @param  vis     是否显示 true为显示 false为不显示
		 */
		void setBlockVisible(int index, bool vis);



	};
}
#endif