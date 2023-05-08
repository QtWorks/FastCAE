# FindQuaZIP
# --------
#
# Find the QuaZIP libraries(Only for QuaZIP provided by FastCAE)
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``QuaZIP_FOUND`` True if QuaZIP found on the local system
#
# ``QuaZIP_VERSION`` QuaZIP Version(x.x.x)
#
# ``QuaZIP_VERSION_MAJOR`` QuaZIP Major Version
#
# ``QuaZIP_VERSION_MINOR`` QuaZIP Minor Version
#
# ``QuaZIP_VERSION_PATCH`` QuaZIP Patch Version
#
# ``QuaZIP_DIRS`` Location of QuaZIP(root dir)
#
# ``QuaZIP_INCLUDE_DIRS`` Location of QuaZIP header files
#
# ``QuaZIP_LIBRARY_DIRS`` Location of QuaZIP libraries
#
# ``QuaZIP_LIBRARIES`` List of the QuaZIP libraries found
#
# ``QuaZIP_BINARY_DIRS`` Location of VTK binary
#

# 防止重复引入
if(FASTCAE_QuaZIP_ALREADY_INCLUDED)
	return()
endif()
set(FASTCAE_QuaZIP_ALREADY_INCLUDED 1)

# find_path 搜索包含某个文件的路径
# 如果在某个路径下发现了该文件，该结果会被存储到该变量中；如果没有找到，存储的结果将会是<VAR>-NOTFOUND
find_path(QuaZIP_DIRS 
	NAMES 
		include/quazip5/quazip.h 
	PATHS 
		${CMAKE_SOURCE_DIR}/extlib/QuaZIP 
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

set(QuaZIP_VERSION_MAJOR 0)
set(QuaZIP_VERSION_MINOR 7)
set(QuaZIP_VERSION_PATCH 3)

set(QuaZIP_VERSION "${QuaZIP_VERSION_MAJOR}.${QuaZIP_VERSION_MINOR}.${QuaZIP_VERSION_PATCH}")

find_path(QuaZIP_INCLUDE_DIRS
	NAMES
		quazip.h
	HINTS
		${QuaZIP_DIRS}/include/quazip5
)

find_path(QuaZIP_LIBRARY_DIRS
	NAMES
		quazip5.lib libquazip5.so
	HINTS
		${QuaZIP_DIRS}/lib
)

find_path(QuaZIP_BINARY_DIRS
	NAMES
		quazip5.dll libquazip5.so
	HINTS
		${QuaZIP_DIRS}/lib
)

set(QuaZIP_LIBRARIES FASTCAE::QUAZIP)

add_library(FASTCAE::QUAZIP SHARED IMPORTED)
set_property(TARGET FASTCAE::QUAZIP PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${QuaZIP_INCLUDE_DIRS})
set_property(TARGET FASTCAE::QUAZIP APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set_target_properties(FASTCAE::QUAZIP PROPERTIES
		IMPORTED_LOCATION_RELEASE "${QuaZIP_LIBRARY_DIRS}/libquazip5.so.1.0.0"
		IMPORTED_SONAME_RELEASE "libquazip5.so.1"
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set_property(TARGET FASTCAE::QUAZIP APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
	set_target_properties(FASTCAE::QUAZIP PROPERTIES
		IMPORTED_IMPLIB_RELEASE "${QuaZIP_LIBRARY_DIRS}/quazip5.lib"
		IMPORTED_LOCATION_RELEASE "${QuaZIP_BINARY_DIRS}/quazip5.dll"
		IMPORTED_IMPLIB_DEBUG "${QuaZIP_LIBRARY_DIRS}/quazip5d.lib"
		IMPORTED_LOCATION_DEBUG "${QuaZIP_BINARY_DIRS}/quazip5d.dll"
	)
endif()

include(FindPackageHandleStandardArgs)

# 如果找到所有需要的变量，并且版本匹配，则将QuaZIP_FOUND变量设置为TRUE
find_package_handle_standard_args(QuaZIP
	FOUND_VAR
		QuaZIP_FOUND
	REQUIRED_VARS
		QuaZIP_DIRS
		QuaZIP_INCLUDE_DIRS
		QuaZIP_LIBRARY_DIRS
		QuaZIP_LIBRARIES
		QuaZIP_BINARY_DIRS
	VERSION_VAR
		QuaZIP_VERSION
)