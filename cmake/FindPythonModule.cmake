# Find a Python module
# Found at http://www.cmake.org/pipermail/cmake/2011-January/041666.html
# To use do: find_python_module(NumPy REQUIRED)
# Reports also version of package, but you can't currently enforce a specific version to be
# searched for...

macro(find_python_module module)
	# Fail if Python interpreter not known
	if(NOT PYTHON_EXECUTABLE)
	message(FATAL_ERROR "Use find_package(PythonInterp) first!")
	endif()
	string(TOLOWER ${module} _module_lower)
	
	if(NOT ${_module_lower})
		if(ARGC GREATER 1 AND ARGV1 STREQUAL "REQUIRED")
			set(${module}_FIND_REQUIRED TRUE)
		endif()
		# Find module location
		execute_process(
			COMMAND
			${PYTHON_EXECUTABLE} "-c" "import re, ${_module_lower}; print(re.compile('/__init__.py.*').sub('',${_module_lower}.__file__))"
			RESULT_VARIABLE ${module}_STATUS
			OUTPUT_VARIABLE ${module}_LOCATION
			ERROR_QUIET
			OUTPUT_STRIP_TRAILING_WHITESPACE
		)
		if(NOT ${module}_STATUS)
			set(${module} ${${module}_LOCATION} CACHE STRING "Location of Python module ${module}")
		endif()
		# Find module version
		execute_process(
			COMMAND
			${PYTHON_EXECUTABLE} "-c" "import re, ${_module_lower}; print(re.compile('/__init__.py.*').sub('',${_module_lower}.__version__))"
			OUTPUT_VARIABLE ${module}_VERSION
			ERROR_QUIET
			OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	endif()

	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(${module}
		FOUND_VAR
			${module}_FOUND
		REQUIRED_VARS
			${module}_LOCATION
		VERSION_VAR
			${module}_VERSION
	)
endmacro()