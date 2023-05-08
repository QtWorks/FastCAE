/**
 * @file BDFDataExchange.h
 * @brief BDFDataExchange
 * @author 闫智慧(chanyuantiandao@126.com)
 * @version 1.0.0
 * @date 2022-06-16 09:11:19
 */
#ifndef BDFDataExchange_H
#define BDFDataExchange_H

#include "meshDataExchangePlugin.h"
#include "MeshThreadBase.h"
#include <QTextStream>
#include <vtkUnstructuredGrid.h>
/**
 * @brief 命名空间
 * @since 1.0.0
 */
namespace MeshData {

	class MeshData;
	class MeshKernal;

	/**
	 * @brief BDFDataExchange类
	 * @since 1.0.0
	 */
	class MESHDATAEXCHANGEPLUGINAPI BDFDataExchange : public MeshThreadBase
	{
		Q_OBJECT
	public:
		explicit BDFDataExchange(const QString &filename, MeshOperation operation, GUI::MainWindow *mw, int modelId = -1);
		virtual ~BDFDataExchange() override = default;

		bool read();
		virtual void run() override;

		void readLine(QString &line);
		bool readNodes(vtkUnstructuredGrid* g, QString &line, MeshKernal* k);
		bool readElements(vtkUnstructuredGrid* g, MeshKernal* k);

	private:
		GUI::MainWindow* _mw;
		QTextStream* _stream{};
		QString _fileName{};
		MeshData* _meshData{};
		MeshOperation _operation;
		int _modelId;
		/**
		 * @brief 单元文本行列表
		 * @note 需要保证先读取节点，获得节点索引映射关系之后才能写入单元
		 * @since 1.0.0
		 */
		QStringList _elementList = {};
		/**
		 * @brief 节点索引映射关系：QMap<BDF_Index, VTK_Index>
		 * @since 1.0.0
		 */
		QMap<int, int> _pointIndexMapping = {};

	};

}
#endif // BDFDataExchange_H