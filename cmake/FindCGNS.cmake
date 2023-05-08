# FindCGNS
# --------
#
# Find the CGNS libraries(Only for CGNS provided by FastCAE)
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``CGNS_FOUND`` True if CGNS found on the local system
#
# ``CGNS_VERSION`` CGNS Version(x.x.x)
#
# ``CGNS_VERSION_MAJOR`` CGNS Major Version
#
# ``CGNS_VERSION_MINOR`` CGNS Minor Version
#
# ``CGNS_VERSION_PATCH`` CGNS Patch Version
#
# ``CGNS_DIRS`` Location of CGNS(root dir)
#
# ``CGNS_INCLUDE_DIRS`` Location of CGNS header files
#
# ``CGNS_LIBRARY_DIRS`` Location of CGNS libraries
#
# ``CGNS_LIBRARIES`` List of the CGNS libraries found
#

# 防止重复引入
if(FASTCAE_CGNS_ALREADY_INCLUDED)
	return()
endif()
set(FASTCAE_CGNS_ALREADY_INCLUDED 1)

# find_path 搜索包含某个文件的路径
# 如果在某个路径下发现了该文件，该结果会被存储到该变量中；如果没有找到，存储的结果将会是<VAR>-NOTFOUND
find_path(CGNS_DIRS 
	NAMES 
		include/cgnslib.h 
	PATHS 
		${CMAKE_SOURCE_DIR}/extlib/CGNS 
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

set(CGNS_VERSION_MAJOR 4)
set(CGNS_VERSION_MINOR 3)
set(CGNS_VERSION_PATCH 0)

set(CGNS_VERSION "${CGNS_VERSION_MAJOR}.${CGNS_VERSION_MINOR}.${CGNS_VERSION_PATCH}")

find_path(CGNS_INCLUDE_DIRS
	NAMES
		cgnslib.h
	HINTS
		${CGNS_DIRS}/include
)

find_path(CGNS_LIBRARY_DIRS
	NAMES
		cgnsdll.lib libcgns.so
	HINTS
		${CGNS_DIRS}/lib
)

set(CGNS_LIBRARIES FASTCAE::CGNS)

add_library(FASTCAE::CGNS SHARED IMPORTED)
set_property(TARGET FASTCAE::CGNS PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CGNS_INCLUDE_DIRS})
set_property(TARGET FASTCAE::CGNS APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_property(TARGET FASTCAE::CGNS PROPERTY INTERFACE_LINK_LIBRARIES FASTCAE::HDF5)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set_target_properties(FASTCAE::CGNS PROPERTIES
		IMPORTED_LOCATION_RELEASE "${CGNS_LIBRARY_DIRS}/libcgns.so.${CGNS_VERSION_MAJOR}.${CGNS_VERSION_MINOR}"
		IMPORTED_SONAME_RELEASE "libcgns.so"
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set_target_properties(FASTCAE::CGNS PROPERTIES
		IMPORTED_IMPLIB_RELEASE "${CGNS_LIBRARY_DIRS}/cgnsdll.lib"
		IMPORTED_LOCATION_RELEASE "${CGNS_DIRS}/bin/cgnsdll.dll"
	)
endif()

include(FindPackageHandleStandardArgs)

# 如果找到所有需要的变量，并且版本匹配，则将CGNS_FOUND变量设置为TRUE
find_package_handle_standard_args(CGNS
	FOUND_VAR
		CGNS_FOUND
	REQUIRED_VARS
		CGNS_DIRS
		CGNS_INCLUDE_DIRS
		CGNS_LIBRARY_DIRS
		CGNS_LIBRARIES
	VERSION_VAR
		CGNS_VERSION
)