#-----------------------------------------------------------------------------
# 头文件搜索路径
#-----------------------------------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

#-----------------------------------------------------------------------------
# 自动添加include目录
#-----------------------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-----------------------------------------------------------------------------
# 源码扫描
#-----------------------------------------------------------------------------
file(GLOB _headers "*.h")
file(GLOB _source "*.cpp")

#-----------------------------------------------------------------------------
# 添加动态库目标
#-----------------------------------------------------------------------------
add_library(PythonModule
	${_headers}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(PythonModule PRIVATE "PYTHONMODULE_API")

list(APPEND _depend_library Common)

list(APPEND _runtimes_libraries
	Qt5::Widgets FASTCAE::PYTHON
)
if(FASTCAE_LINUX)
	list(APPEND _runtimes_libraries
		FASTCAE::FFI
	)
endif()

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(PythonModule
	${_runtimes_libraries}
	${_depend_library})

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(PythonModule ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_PythonModule_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)


if(FASTCAE_WIN)
	install(DIRECTORY
		${Python_DIRS}/Lib
		DESTINATION ${INSTALL_BINDIR}
		DESTINATION
	)
	install(DIRECTORY
		${Python_DIRS}/DLLs
		DESTINATION ${INSTALL_BINDIR}
	)
else()
	install(DIRECTORY
		${Python_DIRS}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}
		DESTINATION ${INSTALL_LIBDIR}
	)
endif()
#-----------------------------------------------------------------------------
# 安装Python脚本和配置文件
#-----------------------------------------------------------------------------
install(
	FILES
		${CMAKE_CURRENT_SOURCE_DIR}/py/FastCAE.ini 
		${CMAKE_CURRENT_SOURCE_DIR}/py/CAD.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/Case.py 
		${CMAKE_CURRENT_SOURCE_DIR}/py/ControlPanel.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/Geometry.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/MainWindow.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/Material.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/Mesh.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/Mesher.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/Post.py
		${CMAKE_CURRENT_SOURCE_DIR}/py/PostProcess.py
	DESTINATION ${INSTALL_BINDIR}
)