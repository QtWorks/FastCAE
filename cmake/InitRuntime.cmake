if(FASTCAE_ENABLE_DEV)
	
	if(FASTCAE_WIN)
		if(NOT EXISTS "$<TARGET_FILE_DIR:${PROJECT_NAME}>/FastCAE.ini")
			get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
			get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

			foreach(_lib ${FastCAE_Runtimes_Libraries})
				add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy 
						$<TARGET_FILE:${_lib}>
					$<TARGET_FILE_DIR:${PROJECT_NAME}>
				)
			endforeach()

			# 在windows环境需要拷贝所有依赖库的dll到构建目录
			add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				#[[COMMAND ${CMAKE_COMMAND} -E copy 
					$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> 
				$<TARGET_FILE_DIR:${PROJECT_NAME}>
  				COMMAND_EXPAND_LISTS]]

				COMMAND ${CMAKE_COMMAND} -E copy
					# 拷贝Gmsh执行程序
					${Gmsh_EXECUTABLE}
				$<TARGET_FILE_DIR:${PROJECT_NAME}>

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					# 拷贝python的Lib文件夹
					${Python_DIRS}/Lib
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/Lib

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					# 拷贝python的DLLs文件夹
					${Python_DIRS}/DLLs
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/DLLs

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					# 拷贝Qt图片格式支持文件
					${_qt_bin_dir}/../plugins/imageformats
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/imageformats

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					# 拷贝Qt平台支持文件
					${_qt_bin_dir}/../plugins/platforms
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms
			)
		endif()
	else()
		if(NOT EXISTS "$<TARGET_FILE_DIR:${PROJECT_NAME}>/FastCAE.ini")
			get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
			get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
			
			foreach(_lib ${FastCAE_Runtimes_Libraries})
				add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy 
						$<TARGET_LINKER_FILE:${_lib}>
						$<TARGET_SONAME_FILE:${_lib}>
					$<TARGET_FILE_DIR:PythonModule>
				)
			endforeach()

			add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

				COMMAND ${CMAKE_COMMAND} -E copy 
					${Gmsh_EXECUTABLE}
				$<TARGET_FILE_DIR:${PROJECT_NAME}>

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					# 拷贝python的python3.7文件夹
					${Python_DIRS}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}
				$<TARGET_FILE_DIR:PythonModule>/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					# 拷贝Qt图片格式支持文件
					${_qt_bin_dir}/../plugins/imageformats
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/imageformats

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					${_qt_bin_dir}/../plugins/platforms
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					${_qt_bin_dir}/../plugins/platforminputcontexts	  
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/platforminputcontexts

				COMMAND ${CMAKE_COMMAND} -E copy_directory 
					${_qt_bin_dir}/../plugins/xcbglintegrations	
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/xcbglintegrations

				COMMAND ${CMAKE_COMMAND} -E copy 
					$<TARGET_LINKER_FILE:Qt5::XcbQpa>
					$<TARGET_SONAME_FILE:Qt5::XcbQpa>
				$<TARGET_FILE_DIR:PythonModule>
			)

			file(
				COPY 
					# 拷贝Qt多国语言支持文件
					${_qt_bin_dir}/../lib
				DESTINATION ${DEVRUNTIME_LIBDIR}/..
				USE_SOURCE_PERMISSIONS
				FILES_MATCHING
				PATTERN "cmake*" EXCLUDE
				PATTERN "pkgconfig*" EXCLUDE
				PATTERN "libicu*.so*"
			)

		endif()
	endif()

	# FastCAE的配置文件，python脚本，有可能会修改，每次构建都会拷贝
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/FastCAE.ini 
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/CAD.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/Case.py 
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/ControlPanel.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/Geometry.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/MainWindow.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/Material.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/Mesh.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/Mesher.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/Post.py
			${CMAKE_SOURCE_DIR}/src/PythonModule/py/PostProcess.py
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)

endif()
