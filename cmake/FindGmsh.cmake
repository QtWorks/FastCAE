# FindGmsh
# --------
#
# Find the Gmsh exe (Only for Gmsh provided by FastCAE)
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``Gmsh_FOUND`` True if Gmsh found on the local system
#
# ``Gmsh_VERSION`` Gmsh Version(x.x.x)
#
# ``Gmsh_VERSION_MAJOR`` Gmsh Major Version
#
# ``Gmsh_VERSION_MINOR`` Gmsh Minor Version
#
# ``Gmsh_VERSION_PATCH`` Gmsh Patch Version
#
# ``Gmsh_DIRS`` Location of Gmsh(root dir)
#
# ``Gmsh_EXECUTABLE`` Location of Gmsh program
#

# 防止重复引入
if(Gmsh_ALREADY_INCLUDED)
	return()
endif()
set(Gmsh_ALREADY_INCLUDED 1)

# find_path 搜索包含某个文件的路径
# 如果在某个路径下发现了该文件，该结果会被存储到该变量中；如果没有找到，存储的结果将会是<VAR>-NOTFOUND
find_path(Gmsh_DIRS 
	NAMES 
		gmsh.exe gmsh
	PATHS 
		${CMAKE_SOURCE_DIR}/extlib/Gmsh 
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

set(Gmsh_VERSION_MAJOR 4)
set(Gmsh_VERSION_MINOR 8)
set(Gmsh_VERSION_PATCH 0)

set(Gmsh_VERSION "${Gmsh_VERSION_MAJOR}.${Gmsh_VERSION_MINOR}.${Gmsh_VERSION_PATCH}")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(Gmsh_EXECUTABLE "${Gmsh_DIRS}/gmsh.exe")
else()
	set(Gmsh_EXECUTABLE "${Gmsh_DIRS}/gmsh")
endif()

include(FindPackageHandleStandardArgs)

# 如果找到所有需要的变量，并且版本匹配，则将Gmsh_FOUND变量设置为TRUE
find_package_handle_standard_args(Gmsh
	FOUND_VAR
		Gmsh_FOUND
	REQUIRED_VARS
		Gmsh_DIRS
		Gmsh_EXECUTABLE
	VERSION_VAR
		Gmsh_VERSION
)