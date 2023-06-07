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
file(GLOB _header "*.h")
file(GLOB _source "*.cpp")

#-----------------------------------------------------------------------------
# 添加动态库目标
#-----------------------------------------------------------------------------
add_executable(FastCAE
	${_header}
	${_source}
	${CMAKE_CURRENT_SOURCE_DIR}/../qrc/qianfan.rc
)	

#-----------------------------------------------------------------------------
# 设置Visual Studio的启动项
#-----------------------------------------------------------------------------
set_property(DIRECTORY ${CMAKE_SOURCE_DIR}
	PROPERTY
		VS_STARTUP_PROJECT FastCAE
)

list(APPEND _depend_library Common PythonModule SARibbonBar Settings DataProperty MeshData Material Geometry ConfigOptions SelfDefObject ModelData ModuleBase PluginManager GmshModule PostInterface PostWidgets ProjectTree GeometryCommand GeometryWidgets IO SolverControl MainWidgets UserGuidence MainWindow)
if(_WIN_)
	#list(APPEND _depend_library XGenerateReport License)
endif()

list(APPEND _runtimes_libraries
	Qt5::Core Qt5::Gui Qt5::Widgets FASTCAE::HDF5 FASTCAE::HDF5CPP
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(FastCAE PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(FastCAE ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_FastCAE_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)

#-----------------------------------------------------------------------------
# 安装Qt的依赖文件
#-----------------------------------------------------------------------------
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)


#-----------------------------------------------------------------------------
# 拷贝依赖文件(非动态库)到构建目录
#-----------------------------------------------------------------------------
if(FASTCAE_ENABLE_DEV)
	include(InitRuntime)
endif()

#-----------------------------------------------------------------------------
# Linux需要单独安装一些文件
#-----------------------------------------------------------------------------
if(FASTCAE_LINUX)
	# 会导致无法输入中文的情况
	install(
		DIRECTORY
			${_qt_bin_dir}/../plugins/platforminputcontexts	  
			${_qt_bin_dir}/../plugins/xcbglintegrations	
		DESTINATION ${INSTALL_BINDIR}
	)

	install(IMPORTED_RUNTIME_ARTIFACTS
		Qt5::XcbQpa
		DESTINATION ${INSTALL_LIBDIR}
	)

	install(
		DIRECTORY
			${_qt_bin_dir}/../lib
		DESTINATION ${INSTALL_LIBDIR}/..
		USE_SOURCE_PERMISSIONS
		FILES_MATCHING
		PATTERN "cmake*" EXCLUDE
		PATTERN "pkgconfig*" EXCLUDE
		PATTERN "libicu*.so*"
	)

	file(WRITE "${CMAKE_BINARY_DIR}/fastcae.desktop"
		"[Desktop Entry]\n"
		"Name=${PROJECT_NAME}\n"
		"Comment=${PROJECT_DESCRIPTION}\n"
		"Exec=/opt/FastCAE/bin/FastCAE\n"
		"Icon=/opt/FastCAE/bin/FastCAE.ico\n"
		"Type=Application\n"
		"StartupNotify=false\n"
		"Categories=Development;\n"
		"Keywords=fast;cae;"
	)
	
	install(
		FILES
			${CMAKE_SOURCE_DIR}/src/qrc/QUI/main.ico
		DESTINATION
			${INSTALL_BINDIR}
		RENAME
			"FastCAE.ico"
	)

	install(
		FILES
			${CMAKE_BINARY_DIR}/fastcae.desktop
		DESTINATION
			${INSTALL_BINDIR}
	)

endif()

#-----------------------------------------------------------------------------
# 安装Qt的imageformats、platforms
#-----------------------------------------------------------------------------
install(
	DIRECTORY
		${_qt_bin_dir}/../plugins/imageformats
		${_qt_bin_dir}/../plugins/platforms
	DESTINATION ${INSTALL_BINDIR}
)