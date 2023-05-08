macro(buildDoxygenDoc)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Documentation/Doxygen/Doxyfile)

    # request to configure the file
    configure_file(
		${DOXYGEN_IN}
		${DOXYGEN_OUT} 
		@ONLY
	)

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(Doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Documentation/Doxygen
        COMMENT "Generating API documentation(html) with Doxygen"
        VERBATIM )
	set_target_properties(Doxygen
		PROPERTIES
		FOLDER Documentation
	)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
endmacro()

buildDoxygenDoc()