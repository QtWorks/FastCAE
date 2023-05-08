# FindTecIO
# --------
#
# Find the TecIO libraries(Only for TecIO provided by FastCAE)
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``TecIO_FOUND`` True if TecIO found on the local system
#
# ``TecIO_VERSION`` TecIO Version(x.x.x)
#
# ``TecIO_VERSION_MAJOR`` TecIO Major Version
#
# ``TecIO_VERSION_MINOR`` TecIO Minor Version
#
# ``TecIO_VERSION_PATCH`` TecIO Patch Version
#
# ``TecIO_DIRS`` Location of TecIO(root dir)
#
# ``TecIO_INCLUDE_DIRS`` Location of TecIO header files
#
# ``TecIO_LIBRARY_DIRS`` Location of TecIO libraries
#
# ``TecIO_LIBRARIES`` List of the TecIO libraries found
#

# 防止重复引入
if(FASTCAE_TecIO_ALREADY_INCLUDED)
	return()
endif()
set(FASTCAE_TecIO_ALREADY_INCLUDED 1)

# find_path 搜索包含某个文件的路径
# 如果在某个路径下发现了该文件，该结果会被存储到该变量中；如果没有找到，存储的结果将会是<VAR>-NOTFOUND
find_path(TecIO_DIRS 
	NAMES 
		include/TECIO.h 
	PATHS 
		${CMAKE_SOURCE_DIR}/extlib/TecIO 
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

set(TecIO_VERSION_MAJOR 1)
set(TecIO_VERSION_MINOR 4)
set(TecIO_VERSION_PATCH 2)

set(TecIO_VERSION "${TecIO_VERSION_MAJOR}.${TecIO_VERSION_MINOR}.${TecIO_VERSION_PATCH}")

find_path(TecIO_INCLUDE_DIRS
	NAMES
		TECIO.h
	HINTS
		${TecIO_DIRS}/include
)

find_path(TecIO_LIBRARY_DIRS
	NAMES
		tecio.lib libtecio.so
	HINTS
		${TecIO_DIRS}/lib
)

set(TecIO_LIBRARIES FASTCAE::TECIO)

add_library(FASTCAE::TECIO SHARED IMPORTED)
set_property(TARGET FASTCAE::TECIO PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${TecIO_INCLUDE_DIRS})
set_property(TARGET FASTCAE::TECIO APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set_target_properties(FASTCAE::TECIO PROPERTIES
		IMPORTED_LOCATION_RELEASE "${TecIO_LIBRARY_DIRS}/libtecio.so"
		#IMPORTED_SONAME_RELEASE "${TecIO_LIBRARY_DIRS}/libtecio.so"
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set_target_properties(FASTCAE::TECIO PROPERTIES
		IMPORTED_IMPLIB_RELEASE "${TecIO_LIBRARY_DIRS}/tecio.lib"
		IMPORTED_LOCATION_RELEASE "${TecIO_DIRS}/bin/tecio.dll"
	)
endif()

include(FindPackageHandleStandardArgs)

# 如果找到所有需要的变量，并且版本匹配，则将TecIO_FOUND变量设置为TRUE
find_package_handle_standard_args(TecIO
	FOUND_VAR
		TecIO_FOUND
	REQUIRED_VARS
		TecIO_DIRS
		TecIO_INCLUDE_DIRS
		TecIO_LIBRARY_DIRS
		TecIO_LIBRARIES
	VERSION_VAR
		TecIO_VERSION
)