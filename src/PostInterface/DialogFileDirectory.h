#ifndef _FILEDIRECTORY_DIALOG_H_
#define _FILEDIRECTORY_DIALOG_H_

#include "PostInterfaceAPI.h"
#include <QDialog>
#include <QFileDialog>
#include <QTreeWidget>
#include <QDirModel>

namespace Ui { class FileDirectoryDialog; }

class POSTINTERFACEAPI FileDirectoryDialog : public QDialog
{
	Q_OBJECT
		
public:

	/**
	 * @brief 构造函数
	 * @param parent-父对象指针,默认为空
	 * @since Version: 1.0.0
	**/
	FileDirectoryDialog(QWidget *parent = nullptr);
	/**
	 * @brief 析构函数
	 * @since Version: 1.0.0
	**/
	~FileDirectoryDialog();
	
	/**
	 * @brief 返回当前全路径(包含文件名/文件组名)
	 * @return 全路径字符串
	 * @since Version: 1.0.0
	**/
	QString getCurrentFullPath();

	/**
	 * @brief 判断当前选中的是不是文件组
	 * @param path-当前钻中的路径
	 * @return true-是,false-否
	 * @since Version: 1.0.0
	**/
	static bool isGourpFiles(const QString path);

	/**
	 * @brief 初始化文件后缀过滤
	 * @param filterString-文件类型
	 * @note  文件类型要求格式为 类型解释 (*.文件后缀)，例如 plot3D文件(*.xyz *.x)。
	 * @since Version: 1.0.0
	**/
	void iniFileFilterType(QString filterString);
	/**
	 * @brief 初始化文件后缀过滤
	 * @param filterString-文件类型
	 * @note  文件类型要求格式为 类型解释 (*.文件后缀)，例如 plot3D文件(*.xyz *.x)。
	 * @since Version: 1.0.0
	**/
	void iniFileFilterType(QStringList filters);

private:
	/**
	 * @brief 初始化对话框打开路径
	 * @param dirStr-默认打开的路径
	 * @since Version: 1.0.0
	**/
	void initWin(QString dirStr);
	/**
	 * @brief 初始化Ui内容
	 * @since Version: 1.0.0
	**/
	void initUi();

	/**
	 * @brief 获取当前电脑磁盘列表目录
	 * @since Version: 1.0.0
	**/
	void SetDirectoryForDrives();

	/**
	 * @brief 打开一个路径
	 * @param record 是否记录历史路径
	 * @since Version: 1.0.0
	**/
	void openFilePath(bool recordHistory);

	/**
	 * @brief 在树型中归类显示
	 * @since Version: 1.0.0
	**/
	void BuildFilePathTree();

	/**
	 * @brief 刷新文件列表
	 * @since Version: 1.0.0
	**/
	void refreshRightView();
	
	/**
	 * @brief 根据目录名获取目录下的文件
	 * @param dirName-目录名
	 * @since Version: 1.0.0
	**/
	void GetFileList(QString dirName);

	/**
	 * @brief 根据文件类型中的字符串获取每一个文件过滤类型
	 * @param filter-过滤描述字符串
	 * @return 文件后缀过滤集合
	 * @since Version: 1.0.0
	**/
	QStringList GetFilterFromString(const QString& filter);

	/**
	 * @brief 路径添加/
	 * @param curPath-需要添加的路径
	 * @return 返回添加之后的路径
	 * @since Version: 1.0.0
	**/
	QString appendSlash(QString curPath);

	/**
	 * @brief 获取文件扩展名
	 * @param fileName-文件名
	 * @return 返回扩展名
	 * @since Version: 1.0.0
	**/
	QString GetFileExt(QString fileName);

	/**
	 * @brief 获取文件名的全路径
	 * @param index-索引
	 * @return 全路径
	 * @since Version: 1.0.0
	**/
	QString FindFullFilename(const QModelIndex& index);

	/**
	 * @brief 按数字前的字符串形成文件分类列表，并在树型中显示
	 * @since Version: 1.0.0
	**/
	void enterDirectory();

	/**
	 * @brief 更新过滤文件列表槽函数
	 * @param filter-过滤描述字符串
	 * @since Version: 1.0.0
	**/
	void filterChange(QString filter);

private slots:
	/**
	 * @brief 取消槽函数
	 * @since Version: 1.0.0
	**/
	void onCancelClicked();
	/**
	 * @brief 确定槽函数
	 * @since Version: 1.0.0
	**/
	void onOkClicked();

	/**
	 * @brief 过滤条件改变槽函数
	 * @since Version: 1.0.0
	**/
	void onFilterChange(QString filter);

	/**
	 * @brief 执行确定按钮槽函数
	 * @since Version: 1.0.0
	**/
	void onDoubleClickedObject(QTreeWidgetItem* pitem, int column);

	/**
	 * @brief 左侧路径区域双击操作(处理路径中的盘符)
	 * @param model index
	 * @since Version: 1.0.0
	**/
	void pathTreeViewDoubleClick(const QModelIndex&);

	/**
	 * @brief 路径树双击操作
	 * @param model index
	 * @since Version: 1.0.0
	**/
	void func_PathTreeViewDoubleClick(const QModelIndex& index);
    void unix_PathTreeViewDoubleClick(QString itemName);

	/**
	 * @brief 选择项发生变化触发这个槽，更新显示选中文件
	 * @since Version: 1.0.0
	**/
	void onItemSelectionChanged();

	/**
	 * @brief 返回上一级目录
	 * @since Version: 1.0.0
	**/
	void onUpPushButtonClicked();

	/**
	 * @brief 后退
	 * @since Version: 1.0.0
	**/
	void onBackClicked();

	/**
	 * @brief 前进
	 * @since Version: 1.0.0
	**/
	void onFrontClicked();

private:
	Ui::FileDirectoryDialog* _ui;

	/**
	 * @brief 路径变化记录实现前进后退功能
	 * @brief 路径变化记录前进、后退路径容器	 
	 * @since Version: 1.0.0
	**/
	QVector<QString> _pathBackVec{};
	QVector<QString> _pathFrontVec{};

	/**
	 * @brief 当前选择路径
	 * @since Version: 1.0.0
	**/
	QString _currentFilePath;

	/**
	 * @brief 目录模型
	 * @since Version: 1.0.0
	**/
	QDirModel* _dirModel;

	/**
	 * @brief 当前电脑"我的文档"的路径
	 * @brief 当前电脑"桌面"的路径
	 * @brief Unix操作系统的相关路径
	 * @since Version: 1.0.0
	**/
	QString _docPath;
	QString _deskTopPath;
	QString userPath,rootPath,userName,rootName;

	/**
	 * @brief 模型数据索引
	 * @since Version: 1.0.0
	**/
	QModelIndex _currentIndex;

	/**
	 * @brief key为12 ...dat，value为分类下对应的文件列表
	 * @since Version: 1.0.0
	**/
	QMap<QString, QVector<QString>> _fileGroup;

	/**
	 * @brief 用于保存一个或多个文件分类，用;分割
	 * @since Version: 1.0.0
	**/
	QString _selectionText;

	/**
	 * @brief 用于保存文件类型列表
	 * @since Version: 1.0.0
	**/
	QStringList _filterList;

	/**
	 * @brief 文件列表
	 * @since Version: 1.0.0
	**/
	QTreeWidget* _fileTree;

	/**
	 * @brief 根节点
	 * @since Version: 1.0.0
	**/
	QTreeWidgetItem* _builtinItem;

	/**
	 * @brief key为12@data,value为扩展名dat,这样用是因为相同文件名，扩展名可能会不同，属于不同的分类
	 * @since Version: 1.0.0
	**/
	QHash<QString, int> _headFile;

	/**
	 * @brief 某个文件夹下的所有文件列表
	 * @since Version: 1.0.0
	**/
	QVector<QString> _fileList;

	/**
	 * @brief 保存左侧路径QTreeView双击后的文件路径
	 * @since Version: 1.0.0
	**/
	QString _treeWidgetFilename;

	/**
	 * @brief 字符串常量
	 * @since Version: 1.0.0
	**/
	const static QString fatherNodeText;
	const static QString splitExt;

};

#endif
