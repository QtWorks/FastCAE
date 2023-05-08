#ifndef GEOMETRYPY_H_
#define GEOMETRYPY_H_

#include "geometryAPI.h"

extern "C"
{
	/**
	 * @brief 获取几何形状数据数量
	 * @return int 返回几何形状数量
	 * @since 2.5.0
	 */
	int GEOMETRYAPI getGeometrySetCount();

	/**
	 * @brief 判断几何是否为空
	 * @return bool 返回判断结果
	 * @since 2.5.0
	 */
	bool GEOMETRYAPI isEmpty();

	/**
	 * @brief 根据索引获取名称
	 * @param index 要获取名称的几何形状索引
	 * @return char* 返回名称
	 * @since 2.5.0
	 */
	GEOMETRYAPI char *getGeometrySetNameByIndex(int index);

	/**
	 * @brief 根据ID获取名称
	 * @param id 要获取名称的几何形状ID值
	 * @return char* 返回名称
	 * @since 2.5.0
	 */
	GEOMETRYAPI char *getGeometrySetNameByID(int id);

	/**
	 * @brief 根据名称获取索引
	 * @param name 名称
	 * @return int 返回索引值
	 * @since 2.5.0
	 */
	int GEOMETRYAPI getIndexOfGeoometrySet(char *name);

	/**
	 * @brief 根据名称获取ID值
	 * @param name 名称
	 * @return int 返回ID值
	 * @since 2.5.0
	 */
	int GEOMETRYAPI getIDOfGeoometrySet(char *name);

	/**
	 * @brief 根据索引获取ID值
	 * @param index 索引
	 * @return int 返回ID值
	 * @since 2.5.0
	 */
	int GEOMETRYAPI getIDByIndex(int index);

	/**
	 * @brief 根据id获取索引值
	 * @param id id值
	 * @return int 返回索引值
	 * @since 2.5.0
	 */
	int GEOMETRYAPI getIndexByID(int id);

	/**
	 * @brief 根据索引移除几何形状
	 * @param index 要移除几何形状的索引值
	 * @since 2.5.0
	 */
	void GEOMETRYAPI removeGeometrySetByIndex(int index);

	/**
	 * @brief 根据ID值移除几何形状
	 * @param id 要移除几何形状的ID值
	 * @since 2.5.0
	 */
	void GEOMETRYAPI removeGeometrySetByID(int id);

	/**
	 * @brief 清空几何形状
	 * @since 2.5.0
	 */
	void GEOMETRYAPI clear();
}

#endif
