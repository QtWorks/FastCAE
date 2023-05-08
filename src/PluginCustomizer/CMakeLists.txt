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
set(_lang "${CMAKE_CURRENT_SOURCE_DIR}/resource/customizer.qrc")
qt5_add_resources(_resource ${_qrc} ${_lang})

#-----------------------------------------------------------------------------
# 源码扫描
#-----------------------------------------------------------------------------
file(GLOB _ui "*.ui")
file(GLOB _header "*.h")
file(GLOB _source "*.cpp")
qt5_wrap_ui(_interface ${_ui})

#-----------------------------------------------------------------------------
# 添加动态库目标
#-----------------------------------------------------------------------------
add_library(PluginCustomizer
	${_resource}
	${_interface}
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(PluginCustomizer PRIVATE "CUSTOMIZERPLUGIN_API")

list(APPEND _depend_library PythonModule SARibbonBar Settings DataProperty MeshData Material Geometry BCBase ConfigOptions SelfDefObject ModelData ModuleBase PluginManager PostWidgets ProjectTree ProjectTreeExtend GeometryCommand GeometryWidgets IO SolverControl MainWidgets MainWindow)

list(APPEND _runtimes_libraries
	Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(PluginCustomizer  PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(PluginCustomizer ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_PluginCustomizer_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)

#-----------------------------------------------------------------------------
# 设置插件的输出目录
#-----------------------------------------------------------------------------
set_target_properties(PluginCustomizer
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
    LIBRARY_OUTPUT_DIRECTORY_RELEASE $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
    RUNTIME_OUTPUT_DIRECTORY_RELEASE $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
    LIBRARY_OUTPUT_DIRECTORY_DEBUG $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
    RUNTIME_OUTPUT_DIRECTORY_DEBUG $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins
)