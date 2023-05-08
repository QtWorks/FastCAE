# FindPython
# --------
#
# Find the Python libraries(Only for Python provided by FastCAE)
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``Python_FOUND`` True if Python found on the local system
#
# ``Python_VERSION`` Python Version(x.x.x)
#
# ``Python_VERSION_MAJOR`` Python Major Version
#
# ``Python_VERSION_MINOR`` Python Minor Version
#
# ``Python_VERSION_PATCH`` Python Patch Version
#
# ``Python_DIRS`` Location of Python(root dir)
#
# ``Python_INCLUDE_DIRS`` Location of Python header files
#
# ``Python_LIBRARY_DIRS`` Location of Python libraries
#
# ``Python_LIBRARIES`` List of the Python libraries found
#
# ``Python_EXECUTABLE`` Location of Python program
#

# 防止重复引入
if(FASTCAE_Python_ALREADY_INCLUDED)
	return()
endif()
set(FASTCAE_Python_ALREADY_INCLUDED 1)

set(Python_VERSION_MAJOR 3)
set(Python_VERSION_MINOR 7)
set(Python_VERSION_PATCH 0)
# find_path 搜索包含某个文件的路径
# 如果在某个路径下发现了该文件，该结果会被存储到该变量中；如果没有找到，存储的结果将会是<VAR>-NOTFOUND

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(_python_h_dir "include/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}m")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(_python_h_dir "include")
endif()

find_path(Python_DIRS 
	NAMES 
		"${_python_h_dir}/Python.h"
	PATHS 
		${CMAKE_SOURCE_DIR}/extlib/Python
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

find_path(Python_INCLUDE_DIRS 
	NAMES
		Python.h
	HINTS
		${Python_DIRS}/${_python_h_dir}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(Python_EXECUTABLE "${Python_DIRS}/python.exe")
else()
	set(Python_EXECUTABLE "${Python_DIRS}/bin/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}")
endif()

#[[if(EXISTS ${Python_EXECUTABLE})
	message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
else()
	set(Python_EXECUTABLE "Python_EXECUTABLE-NOTFOUND")
endif()]]

#[[execute_process(
	COMMAND
		${Python_EXECUTABLE} "-c" "import sys\nprint(sys.version_info)"
	RESULT_VARIABLE _status
	OUTPUT_VARIABLE _version
	ERROR_QUIET
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

function(_findPythonVersion _key _output)
	# 初始化
	set(CMAKE_MATCH_1 "0")
	# 定义正则
	set(_version_expr "${_key}=([0-9]+),")
	# 匹配
	string(REGEX MATCH "${_version_expr}" Python_ver "${_version}")
	# PARENT_SCOPE选项，意味着该变量的作用域会传递到上一层（函数的调用者）
	set(${_output} "${CMAKE_MATCH_1}" PARENT_SCOPE)
endfunction(_findPythonVersion)

_findPythonVersion("major" Python_VERSION_MAJOR)
_findPythonVersion("minor" Python_VERSION_MINOR)
_findPythonVersion("micro" Python_VERSION_PATCH)]]

set(Python_VERSION "${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}.${Python_VERSION_PATCH}")

find_path(Python_LIBRARY_DIRS
	NAMES
		python${Python_VERSION_MAJOR}${Python_VERSION_MINOR}.lib libpython${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}m.so
	HINTS
		${Python_DIRS}/libs ${Python_DIRS}/lib
)

set(Python_LIBRARIES FASTCAE::PYTHON)

add_library(FASTCAE::PYTHON SHARED IMPORTED)

set_property(TARGET FASTCAE::PYTHON PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Python_INCLUDE_DIRS})
set_property(TARGET FASTCAE::PYTHON APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)



if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_library(FASTCAE::FFI SHARED IMPORTED)
	set_property(TARGET FASTCAE::FFI APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
	set_target_properties(FASTCAE::FFI PROPERTIES
		IMPORTED_LOCATION_RELEASE "${Python_LIBRARY_DIRS}/libffi.so.8.1.0"
		IMPORTED_SONAME_RELEASE "libffi.so.8"
	)
	set_target_properties(FASTCAE::PYTHON PROPERTIES
		IMPORTED_LOCATION_RELEASE "${Python_LIBRARY_DIRS}/libpython${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}m.so.1.0"
		IMPORTED_SONAME_RELEASE "libpython${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}m.so"
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set_target_properties(FASTCAE::PYTHON PROPERTIES
		IMPORTED_IMPLIB_RELEASE "${Python_LIBRARY_DIRS}/python${Python_VERSION_MAJOR}${Python_VERSION_MINOR}.lib"
		IMPORTED_LOCATION_RELEASE "${Python_DIRS}/python${Python_VERSION_MAJOR}${Python_VERSION_MINOR}.dll"
	)
endif()


include(FindPackageHandleStandardArgs)
# 如果找到所有需要的变量，并且版本匹配，则将Python_FOUND变量设置为TRUE
find_package_handle_standard_args(Python
	FOUND_VAR
		Python_FOUND
	REQUIRED_VARS
		Python_DIRS
		Python_INCLUDE_DIRS
		Python_LIBRARY_DIRS
		Python_LIBRARIES
		Python_EXECUTABLE
	VERSION_VAR
		Python_VERSION
)