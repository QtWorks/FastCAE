# FindQwt
# --------
#
# Find the Qwt libraries(Only for Qwt provided by FastCAE)
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``Qwt_FOUND`` True if Qwt found on the local system
#
# ``Qwt_VERSION`` Qwt Version(x.x.x)
#
# ``Qwt_VERSION_MAJOR`` Qwt Major Version
#
# ``Qwt_VERSION_MINOR`` Qwt Minor Version
#
# ``Qwt_VERSION_PATCH`` Qwt Patch Version
#
# ``QwtPolar_VERSION`` QwtPolar Version(x.x.x)
#
# ``QwtPolar_VERSION_MAJOR`` QwtPolar Major Version
#
# ``QwtPolar_VERSION_MINOR`` QwtPolar Minor Version
#
# ``QwtPolar_VERSION_PATCH`` QwtPolar Patch Version
#
# ``Qwt_DIRS`` Location of Qwt(root dir)
#
# ``Qwt_INCLUDE_DIRS`` Location of Qwt(QwtPolar) header files
#
# ``Qwt_LIBRARY_DIRS`` Location of Qwt(QwtPolar) libraries
#
# ``Qwt_LIBRARIES`` List of the Qwt libraries(with QwtPolar libraries) found
#
# ``Qwt_BINARY_DIRS`` Location of VTK binary
#

# 防止重复引入
if(FASTCAE_Qwt_ALREADY_INCLUDED)
	return()
endif()
set(FASTCAE_Qwt_ALREADY_INCLUDED 1)

# find_path 搜索包含某个文件的路径
# 如果在某个路径下发现了该文件，该结果会被存储到该变量中；如果没有找到，存储的结果将会是<VAR>-NOTFOUND
find_path(Qwt_DIRS 
	NAMES 
		include/qwt.h 
	PATHS 
		${CMAKE_SOURCE_DIR}/extlib/Qwt 
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

set(Qwt_VERSION_MAJOR 6)
set(Qwt_VERSION_MINOR 1)
set(Qwt_VERSION_PATCH 6)
set(QwtPolar_VERSION_MAJOR 1)
set(QwtPolar_VERSION_MINOR 1)
set(QwtPolar_VERSION_PATCH 1)

set(Qwt_VERSION "${Qwt_VERSION_MAJOR}.${Qwt_VERSION_MINOR}.${Qwt_VERSION_PATCH}")
set(QwtPolar_VERSION "${QwtPolar_VERSION_MAJOR}.${QwtPolar_VERSION_MINOR}.${QwtPolar_VERSION_PATCH}")

find_path(Qwt_INCLUDE_DIRS
	NAMES
		qwt.h
	HINTS
		${Qwt_DIRS}/include
)

find_path(Qwt_LIBRARY_DIRS
	NAMES
		qwt.lib libqwt.so
	HINTS
		${Qwt_DIRS}/lib
)

find_path(Qwt_BINARY_DIRS
	NAMES
		qwt.dll libqwt.so
	HINTS
		${Qwt_DIRS}/lib
)

set(Qwt_LIBRARIES FASTCAE::QWT;FASTCAE::QWTPOLAR)

add_library(FASTCAE::QWT SHARED IMPORTED)
add_library(FASTCAE::QWTPOLAR SHARED IMPORTED)
set_property(TARGET FASTCAE::QWT PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Qwt_INCLUDE_DIRS})
set_property(TARGET FASTCAE::QWT APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_property(TARGET FASTCAE::QWT PROPERTY INTERFACE_LINK_LIBRARIES Qt5::Svg Qt5::OpenGL)
set_property(TARGET FASTCAE::QWT PROPERTY INTERFACE_COMPILE_DEFINITIONS "QWT_DLL")

set_property(TARGET FASTCAE::QWTPOLAR PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Qwt_INCLUDE_DIRS})
set_property(TARGET FASTCAE::QWTPOLAR APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_property(TARGET FASTCAE::QWTPOLAR PROPERTY INTERFACE_LINK_LIBRARIES FASTCAE::QWT Qt5::PrintSupport)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set_target_properties(FASTCAE::QWT PROPERTIES
		IMPORTED_LOCATION_RELEASE "${Qwt_LIBRARY_DIRS}/libqwt.so.${Qwt_VERSION_MAJOR}.${Qwt_VERSION_MINOR}.${Qwt_VERSION_PATCH}"
		IMPORTED_SONAME_RELEASE "libqwt.so.${Qwt_VERSION_MAJOR}"
	)
	set_target_properties(FASTCAE::QWTPOLAR PROPERTIES
		IMPORTED_LOCATION_RELEASE "${Qwt_LIBRARY_DIRS}/libqwtpolar.so.${QwtPolar_VERSION_MAJOR}.${QwtPolar_VERSION_MINOR}.${QwtPolar_VERSION_PATCH}"
		IMPORTED_SONAME_RELEASE "libqwtpolar.so.${QwtPolar_VERSION_MAJOR}"
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set_property(TARGET FASTCAE::QWT APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
	set_property(TARGET FASTCAE::QWTPOLAR APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
	set_target_properties(FASTCAE::QWT PROPERTIES
		IMPORTED_IMPLIB_RELEASE "${Qwt_LIBRARY_DIRS}/qwt.lib"
		IMPORTED_LOCATION_RELEASE "${Qwt_BINARY_DIRS}/qwt.dll"
		IMPORTED_IMPLIB_DEBUG "${Qwt_LIBRARY_DIRS}/qwtd.lib"
		IMPORTED_LOCATION_DEBUG "${Qwt_BINARY_DIRS}/qwtd.dll"
	)
	set_target_properties(FASTCAE::QWTPOLAR PROPERTIES
		IMPORTED_IMPLIB_RELEASE "${Qwt_LIBRARY_DIRS}/qwtpolar.lib"
		IMPORTED_LOCATION_RELEASE "${Qwt_BINARY_DIRS}/qwtpolar.dll"
		IMPORTED_IMPLIB_DEBUG "${Qwt_LIBRARY_DIRS}/qwtpolard.lib"
		IMPORTED_LOCATION_DEBUG "${Qwt_BINARY_DIRS}/qwtpolard.dll"
	)
endif()

include(FindPackageHandleStandardArgs)

# 如果找到所有需要的变量，并且版本匹配，则将Qwt_FOUND变量设置为TRUE
find_package_handle_standard_args(Qwt
	FOUND_VAR
		Qwt_FOUND
	REQUIRED_VARS
		Qwt_DIRS
		Qwt_INCLUDE_DIRS
		Qwt_LIBRARY_DIRS
		Qwt_LIBRARIES
		Qwt_BINARY_DIRS
	VERSION_VAR
		Qwt_VERSION
)