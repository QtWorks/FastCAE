# Deployqt
# --------
#
# Define a function which can find the Qt dependent library and copy them to the bin directory
#
# Usage
# ^^^^^^^^^^^^^^^^
#
# deployqt(target dir)
#

#-----------------------------------------------------------------------------
# 获取windeployqt程序路径WINDEPLOYQT_EXECUTABLE
#-----------------------------------------------------------------------------
if(NOT WINDEPLOYQT_EXECUTABLE)
	get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
	get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
endif()

#-----------------------------------------------------------------------------
# 函数定义deployqt(target dir)
#-----------------------------------------------------------------------------
function(deployqt target directory)
	# 在构建完执行命令，拷贝文件到构建目录
	add_custom_command(TARGET ${target} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E
			env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
				--verbose 0
				--no-compiler-runtime
				--release
				\"$<TARGET_FILE:${target}>\"
	)

	# 生成路径保存到文件
	file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${target}_$<CONFIG>_path"
		CONTENT "$<TARGET_FILE:${target}>"
	)

	install(CODE
		"
		file(READ \"${CMAKE_CURRENT_BINARY_DIR}/${target}_${CMAKE_BUILD_TYPE}_path\" _file)
		execute_process(
			COMMAND \"${CMAKE_COMMAND}\" -E
				env PATH=\"${_qt_bin_dir}\" \"${WINDEPLOYQT_EXECUTABLE}\"
					--dry-run
					--no-compiler-runtime
					--release
					--list mapping
					\${_file}
			OUTPUT_VARIABLE _output
			OUTPUT_STRIP_TRAILING_WHITESPACE
		)
		separate_arguments(_files WINDOWS_COMMAND \${_output})
		while(_files)
			list(GET _files 0 _src)
			list(GET _files 1 _dest)
			execute_process(
				COMMAND \"${CMAKE_COMMAND}\" -E
					copy \${_src} \"\${CMAKE_INSTALL_PREFIX}/${directory}/\${_dest}\"
			)
			list(REMOVE_AT _files 0 1)
		endwhile()
		"
	)

	# windeployqt doesn't work correctly with the system runtime libraries,
	# so we fall back to one of CMake's own modules for copying them over
	set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
	include(InstallRequiredSystemLibraries)
	foreach(lib ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
		get_filename_component(filename "${lib}" NAME)
		add_custom_command(TARGET ${target} POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E
				copy_if_different "${lib}" \"$<TARGET_FILE_DIR:${target}>\"
		)
	endforeach()

endfunction()

mark_as_advanced(WINDEPLOYQT_EXECUTABLE)