set(CTEST_OUTPUT_ON_FAILURE ON)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(TestPythonModule TestPythonModule.cpp)
set_target_properties(TestPythonModule
	PROPERTIES MACOSX_RPATH ON
	SKIP_BUILD_RPATH OFF
	BUILD_WITH_INSTALL_RPATH OFF
	FOLDER TestModules
)

target_link_libraries(TestPythonModule PRIVATE PythonModule Qt5::Widgets ${Python_LIBRARIES})

#-----------------------------------------------------------------------------
# 添加测试：TestPythonModule
#-----------------------------------------------------------------------------
add_test(
	NAME
		TestPythonModule
	COMMAND
		$<TARGET_FILE:TestPythonModule>
)
