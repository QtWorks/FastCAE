set(SOVERSION ${PROJECT_VERSION} ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH})

#-----------------------------------------------------------------------------
# 所有项目
#-----------------------------------------------------------------------------
list(APPEND _libraries Common PythonModule SARibbonBar Settings DataProperty MeshData SelfDefObject Material Geometry BCBase ConfigOptions ParaClassFactory ModelData ModuleBase PostAlgorithm PostRenderData PostInterface PostCurveDataManager PostPlotWidget PostWidgets GeometryDataExchange ProjectTree ProjectTreeExtend GeometryCommand GeometryWidgets PluginManager GmshModule IO SolverControl MainWidgets UserGuidence)

#[[if(_WIN_)
list(APPEND _libraries XGenerateReport License)
endif()]]

list(APPEND _libraries MainWindow ${PROJECT_NAME})



#-----------------------------------------------------------------------------
# 处理FastCAE程序的RPATH
#-----------------------------------------------------------------------------
file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR} ${CMAKE_INSTALL_PREFIX})

if(_APPLE_)
	set(_rpath "@loader_path/${_rel}")
else()
	set(_rpath "\$ORIGIN:\$ORIGIN/${_rel}")
endif()

file(TO_NATIVE_PATH "${_rpath}/${INSTALL_LIBDIR}" _lib_rpath)

# 遗漏两个，临时解决方案
list(APPEND FastCAE_Runtimes_Libraries VTK::loguru VTK::gl2ps Qt5::DBus)

foreach(_library ${_libraries})
	
	add_subdirectory(${_library})
	
	set_target_properties(${_library}
		PROPERTIES 
			MACOSX_RPATH ON
			SKIP_BUILD_RPATH OFF
			BUILD_WITH_INSTALL_RPATH ON
			INSTALL_RPATH "${_lib_rpath}"
			INSTALL_RPATH_USE_LINK_PATH ON
			#POSITION_INDEPENDENT_CODE 1
			#OUTPUT_NAME $<LOWER_CASE:${_library}>
			#DEBUG_POSTFIX "_d"
			VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}
			FOLDER Modules
	)

	list(APPEND FastCAE_Runtimes_Libraries ${FastCAE_${_library}_Runtimes_Libraries})

endforeach()


#-----------------------------------------------------------------------------
# 安装FastCAE，定义项目的安装目录
#-----------------------------------------------------------------------------
install(
	TARGETS ${_libraries} ${PROJECT_NAME}
	#ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
	RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
	LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
)

list(APPEND _plugins PluginCustomizer PluginMeshDataExchange)

foreach(_plugin ${_plugins})
	list(APPEND FastCAE_Runtimes_Libraries ${FastCAE_${_plugin}_Runtimes_Libraries})
	add_subdirectory(${_plugin})
	set_target_properties(${_plugin} PROPERTIES
		FOLDER Plugins
	)
endforeach()

#-----------------------------------------------------------------------------
# 安装插件到plugins目录
#-----------------------------------------------------------------------------
install(
	TARGETS ${_plugins}
	RUNTIME DESTINATION ${INSTALL_BINDIR}/plugins
	LIBRARY DESTINATION ${INSTALL_BINDIR}/plugins
)


list(REMOVE_DUPLICATES FastCAE_Runtimes_Libraries)

install(IMPORTED_RUNTIME_ARTIFACTS
	${FastCAE_Runtimes_Libraries}
	DESTINATION ${INSTALL_LIBDIR}
	COMPONENT lib
)