macro(buildSphinxDoc)
if(DOXYGEN_FOUND AND breathe_FOUND)

	set(SPHINX_IN ${CMAKE_SOURCE_DIR}/docs/conf.py.in)
	set(SPHINX_OUT ${CMAKE_BINARY_DIR}/Documentation/Sphinx/_build/conf.py)

	# BREATHE_DOC_CONF_FILE中的Sphinx模板文件，会通过conf.py配置到的BREATHE_DOC_BUILD_DIR目录下
	configure_file(
		${SPHINX_IN}
		${SPHINX_OUT}
		@ONLY
	)

	# note the option ALL which allows to build the docs together with the application
	add_custom_target(Sphinx ALL
		COMMAND
			${SPHINX_EXECUTABLE}
				-q
				-b html
				-c ${CMAKE_BINARY_DIR}/Documentation/Sphinx/_build
				${CMAKE_SOURCE_DIR}/docs
				${CMAKE_BINARY_DIR}/Documentation/Sphinx/html
		COMMENT
			"Building Sphinx documentation with Breathe, Sphinx and Doxygen"
		VERBATIM
	)
	set_target_properties(Sphinx
		PROPERTIES
		FOLDER Documentation
	)
endif()
endmacro()

buildSphinxDoc()
