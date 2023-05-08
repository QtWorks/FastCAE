#-----------------------------------------------------------------------------
# 头文件搜索路径
#-----------------------------------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

#-----------------------------------------------------------------------------
# 自动添加include目录
#-----------------------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-----------------------------------------------------------------------------
# 添加资源文件
#-----------------------------------------------------------------------------
set(_qrc "${CMAKE_CURRENT_SOURCE_DIR}/../qrc/qianfan.qrc")
set(_lang "${CMAKE_CURRENT_SOURCE_DIR}/../qrc/translations.qrc")
qt5_add_resources(_resource ${_qrc} ${_lang})

#-----------------------------------------------------------------------------
# 源码扫描
#-----------------------------------------------------------------------------
file(GLOB _header "*.h")
file(GLOB _source "*.cpp")

#-----------------------------------------------------------------------------
# 添加动态库目标
#-----------------------------------------------------------------------------
add_library(ProjectTreeExtend
	${_resource}
	${_interface}
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(ProjectTreeExtend PRIVATE "PROJECTTREEEXTEND_API")

list(APPEND _depend_library Settings DataProperty BCBase ConfigOptions MeshData SelfDefObject Material ModelData ModuleBase PostWidgets ProjectTree ParaClassFactory)

list(APPEND _runtimes_libraries
	Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml
	FASTCAE::QWTPOLAR
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(ProjectTreeExtend  PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(ProjectTreeExtend ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_ProjectTreeExtend_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)
