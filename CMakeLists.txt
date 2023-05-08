#-----------------------------------------------------------------------------
# 工程属性设置
#-----------------------------------------------------------------------------
# 指定所需cmake的最低版本
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
# 设置项目名称 语言
project(FastCAE
	VERSION 2.5.0
	LANGUAGES CXX
	DESCRIPTION "FastCAE，一款免费的CAE仿真软件研发支撑平台。"
	HOMEPAGE_URL "http://www.fastcae.com/"
)

#-----------------------------------------------------------------------------
# 编译系统设置
#-----------------------------------------------------------------------------
# c++语言标准
set(CMAKE_CXX_STANDARD 11)
# 指定是否使用编译器特定的扩展
set(CMAKE_CXX_EXTENSIONS OFF)
# 是否强制要求C++标准为${CMAKE_CXX_STANDARD},如果为OFF则可能使用旧的标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 默认编译动态库
set(BUILD_SHARED_LIBS ON)


#-----------------------------------------------------------------------------
# 检测操作系统
#-----------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(FASTCAE_LINUX True)
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX "/opt/${PROJECT_NAME}" CACHE PATH "${PROJECT_NAME}的安装路径" FORCE)
	endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(FASTCAE_WIN True)
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX "c:/Program Files/${PROJECT_NAME}" CACHE PATH "${PROJECT_NAME}的安装路径" FORCE)
	endif()
else()
  message(SEND_ERROR "No Support System!")
endif()

#-----------------------------------------------------------------------------
# 测试环境定义，发布的时候需要删除
#-----------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
message(STATUS "${PROJECT_NAME} will be installed to ${CMAKE_INSTALL_PREFIX}")

if (NOT DEFINED Qt5_DIR)
	if(FASTCAE_LINUX)
	set(Qt5_DIR "/opt/Qt5.14.2/5.14.2/gcc_64/lib/cmake/Qt5" CACHE PATH "Qt5Config.cmake所在目录" FORCE)
	elseif(FASTCAE_WIN)
	set(Qt5_DIR "D:/software/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5" CACHE PATH "Qt5Config.cmake所在目录" FORCE)
	endif()
endif()

#-----------------------------------------------------------------------------
# 编译选项设置
#-----------------------------------------------------------------------------
# 是否需要编译调试程序
option(FASTCAE_ENABLE_DEV "ON:开启代码调试，OFF:仅安装程序" ON)
# 是否自动下载依赖库
option(FASTCAE_AUTO_DOWNLOAD "如果extlib不存在，则自动下载(git)依赖库" ON)
option(FASTCAE_ENABLE_OPENMP "使用OpenMP" OFF)
option(FASTCAE_ENABLE_MPI "使用MPI" OFF)
option(FASTCAE_DOXYGEN_DOC "生成Doxygen文档" OFF)
option(FASTCAE_INSTALLATION_PACKAGE "生成${PROJECT_NAME}安装包" ON)

#-----------------------------------------------------------------------------
# 指定编译选项
#-----------------------------------------------------------------------------
# 仅对单配制编译器(Makefile Generators or Ninja)生效
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()
if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)
if(MSVC)
	add_definitions(-DUNICODE -D_UNICODE)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options(
			$<$<CONFIG:>:/MD>
			$<$<CONFIG:Debug>:/MDd>
			$<$<CONFIG:Release>:/MD>
	)
endif()


#-----------------------------------------------------------------------------
# 从系统查找OpenMP（动态库引入使用：OpenMP::OpenMP_CXX）
#-----------------------------------------------------------------------------
if(FASTCAE_ENABLE_OPENMP)
	find_package(OpenMP)
	if(OpenMP_CXX_FOUND)
		add_definitions(-DFASTCAE_HAS_OPENMP)
	endif()
endif()

#-----------------------------------------------------------------------------
# 从系统查找MPI（头文件路径：${MPI_CXX_INCLUDE_DIRS} 动态库引入使用：MPI::MPI_CXX）
#-----------------------------------------------------------------------------
if(FASTCAE_ENABLE_MPI)
	find_package(MPI)
	if(MPI_CXX_FOUND)
		add_definitions(-DFASTCAE_HAS_MPI)
	endif()
endif()

#-----------------------------------------------------------------------------
# 从系统查找Qt模块,开启Qt中间文件的自动生成
#-----------------------------------------------------------------------------
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

list(APPEND QtNeededModules 
	Core
	Widgets
	Gui
	Xml
	Svg	# Qwt
	OpenGL	# Qwt
	PrintSupport	# QwtPolar
	DBus
)
if(FASTCAE_LINUX)
	list(APPEND QtNeededModules XcbQpa)
endif()

find_package(Qt5 COMPONENTS ${QtNeededModules} REQUIRED)
if(Qt5_FOUND)
  message(STATUS "Found Qt5: ${Qt5_DIR}")
  if(Qt5_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  endif()
else()
  set(Qt5_DIR "Qt5_DIR-NOTFOUND" CACHE PATH "Qt5_DIR")
endif()

#-----------------------------------------------------------------------------
# 从远程检索依赖库
#-----------------------------------------------------------------------------
if(FASTCAE_AUTO_DOWNLOAD AND NOT EXISTS ${CMAKE_SOURCE_DIR}/extlib)
	if(FASTCAE_WIN)
        set(_extlibGitAddr "https://gitee.com/DISOGitee/FastCAEWinExtlib.git")
	elseif(FASTCAE_LINUX)
		set(_extlibGitAddr "https://gitee.com/DISOGitee/FastCAELinuxExtlib.git")
	endif()

	find_package(Git REQUIRED)
	if(Git_FOUND)
		execute_process(
			COMMAND 
				${GIT_EXECUTABLE} clone ${_extlibGitAddr} extlib
			WORKING_DIRECTORY
				${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE _status
		)
	else()
		message(FATAL_ERROR "Not Found Git")
		message(STATUS "Please execute the command[git clone ${_extlibGitAddr} extlib] under the directory ${CMAKE_SOURCE_DIR}")
	endif()
endif()

#-----------------------------------------------------------------------------
# 引入FastCAE的依赖库
#-----------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# VTK
find_package(VTK REQUIRED)

# OpenCASCADE
find_package(OpenCASCADE REQUIRED)

# Qwt
find_package(Qwt REQUIRED)

# HDF5
find_package(HDF5 REQUIRED)

# CGNS
find_package(CGNS REQUIRED)

# TecIO
find_package(TecIO REQUIRED)

# QuaZIP
find_package(QuaZIP REQUIRED)

# Gmsh
find_package(Gmsh REQUIRED)

# Python
find_package(Python REQUIRED)

#-----------------------------------------------------------------------------
# 检索系统python（需要修改cmake搜索路径）
#-----------------------------------------------------------------------------
#find_package(PythonInterp REQUIRED)
#find_package(Python COMPONENTS Interpreter Development REQUIRED)


#-----------------------------------------------------------------------------
# 开启项目分组
#-----------------------------------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# 可以修改cmake预定义的target分组名称
#set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Predefined")

#-----------------------------------------------------------------------------
# 定义GNU标准的安装目录（GNUInstallDirs.cmake）
#-----------------------------------------------------------------------------
include(GNUInstallDirs)
set(CMAKE_INSTALL_LIBDIR "lib")

#-----------------------------------------------------------------------------
# 定义项目构建中间文件的生成目录
#-----------------------------------------------------------------------------
if(FASTCAE_WIN)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
	if(FASTCAE_ENABLE_DEV)
		set(DEVRUNTIME_BINDIR_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
		set(DEVRUNTIME_BINDIR_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
	endif()
elseif(FASTCAE_LINUX)  
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
	if(FASTCAE_ENABLE_DEV)
		set(DEVRUNTIME_BINDIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
		set(DEVRUNTIME_LIBDIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	endif()
endif()

#-----------------------------------------------------------------------------
# 定义变量作为项目的安装路径
#-----------------------------------------------------------------------------
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
if(FASTCAE_WIN)
	set(INSTALL_LIBDIR ${CMAKE_INSTALL_BINDIR})
else()
	set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
endif()
#set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})


#-----------------------------------------------------------------------------
# 编译位置无关的代码
#-----------------------------------------------------------------------------
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 定义源码路径
add_subdirectory(src)

#-----------------------------------------------------------------------------
# 单元测试Ctest
#-----------------------------------------------------------------------------
option(FASTCAE_ENABLE_TEST "开启单元测试（尚未开发完成）" OFF)
if(FASTCAE_ENABLE_TEST)
	# 开启测试 
	enable_testing() 
	#添加测试项目 
	add_subdirectory(test)
endif()

#-----------------------------------------------------------------------------
# 生成文档(Doxygen + Breathe + Sphinx)
#-----------------------------------------------------------------------------
if(FASTCAE_DOXYGEN_DOC)
	find_package(Doxygen REQUIRED)
	if(DOXYGEN_FOUND)
		message(STATUS "Found doc generate Tool: Doxygen")
		include(UseDoxygen)
		# 文档生成依赖Python解释器、Sphinx
		#[[find_package(PythonInterp)
		find_package(Sphinx)
		
		if(PYTHONINTERP_FOUND AND SPHINX_FOUND)
			message(STATUS "Found doc generate Tool: Sphinx")
			include(FindPythonModule)
			# Python的breathe模块负责协调Doxygen和Sphinx
			find_python_module(breathe REQUIRED)
			if(breathe_FOUND)
				message(STATUS "Python module(breathe) version: ${breathe_VERSION}")
				include(UseSphinx)
			else()
				message(STATUS "Generate sphinx documentation need python module: breathe")
			endif()
			
		endif()]]
	endif()

endif()

#-----------------------------------------------------------------------------
# 安装包生成(windows环境光需要NSIS 3.03+)
#-----------------------------------------------------------------------------
if(FASTCAE_INSTALLATION_PACKAGE)
	if (FASTCAE_WIN)
		find_program(NSIS_EXECUTABLE NSIS.exe)
		# WIX尚未调试，暂时取消
		#find_program(WIX_EXECUTABLE candle.exe)
		#if(NSIS_EXECUTABLE OR WIX_EXECUTABLE)
		if(NSIS_EXECUTABLE)
			include(${CMAKE_SOURCE_DIR}/cmake/CMakePack.cmake)
		endif()
	else()
		include(${CMAKE_SOURCE_DIR}/cmake/CMakePack.cmake)
	endif ()
	# 以下include必须放在主CMakeLists.txt文件最后面，否则在Visual Studio中不会生成PACKAGE（打包）目标
	include(CPack)
endif()
