# 声明包的名称
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
# 声明包的供应商
set(CPACK_PACKAGE_VENDOR "青岛数智船海科技有限公司")
# 打包的源代码将包括一个描述文件。这是带有安装说明的纯文本文件
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")
# 添加包的描述
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJCT_DESCRIPTION}")
# 许可证文件
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
# site
set(CPACK_SITE "${PROJECT_HOMEPAGE_URL}")
# 从发布包中安装时，文件将放在/opt/${PROJECT_NAME}目录下
#[[if(FASTCAE_WIN)
	set(CPACK_PACKAGING_INSTALL_PREFIX "C:\\Program Files\\${PROJECT_NAME}")
else()
	set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${PROJECT_NAME}")
endif()]]
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
# CPack所需的主要、次要和补丁版本:
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
# 设置了在包装的时候需要忽略的文件列表和目录
set(CPACK_SOURCE_IGNORE_FILES "${PROJECT_BINARY_DIR};/install/;/.git/;/.vscode/;.gitignore")
# 列出了源代码归档的打包生成器
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
# 二进制存档生成器
set(CPACK_GENERATOR "ZIP;TGZ")
# 声明平台原生二进制安装程序，从DEB和RPM包生成器开始，不过只适用于GNU/Linux
if(UNIX)
	if(CMAKE_SYSTEM_NAME MATCHES Linux)
		find_program(_deb dpkg-deb)
		string(FIND ${_deb} "dpkg-deb" _result)
		if(NOT _result STREQUAL "-1")
			list(APPEND CPACK_GENERATOR "DEB")
			set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
			set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
			set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_VENDOR})
			set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${CPACK_SITE})
			set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
			set(CPACK_DEBIAN_PACKAGE_RELEASE "1")
			set(CPACK_DEBIAN_PACKAGE_DEPENDS "libfontconfig-dev")
		endif()
		find_program(_rpm rpmbuild)
		string(FIND ${_rpm} "rpmbuild" _result)
		if(NOT _result STREQUAL "-1")
			list(APPEND CPACK_GENERATOR "RPM")
			set(CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
			set(CPACK_RPM_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
			set(CPACK_RPM_PACKAGE_VERSION ${PROJECT_VERSION})
			set(CPACK_RPM_PACKAGE_VENDOR ${CPACK_PACKAGE_VENDOR})
			set(CPACK_RPM_PACKAGE_URL ${CPACK_SITE})
			set(CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
			set(CPACK_RPM_PACKAGE_RELEASE "1")
			set(CPACK_RPM_PACKAGE_LICENSE "BSD 3-Clause")
			set(CPACK_RPM_PACKAGE_REQUIRES "fontconfig-devel")
			set(CPACK_RPM_PACKAGE_AUTOREQ NO)
		endif()
	endif()
endif()
# 在windows上生成一个NSIS安装程序
# NSIS相关的变量https://cmake.org/cmake/help/latest/cpack_gen/nsis.html#cpack_gen:CPack%20NSIS%20Generator
if(WIN32 OR MINGW)
	if (NSIS_EXECUTABLE)
		list(APPEND CPACK_GENERATOR "NSIS")
		#set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}")
		#set(CPACK_NSIS_INSTALL_ROOT "C:\\Program Files")
		set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/src/qrc/QUI/main.ico")
		set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/src/qrc/QUI/uninstall.ico")
		#set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "${CMAKE_SOURCE_DIR}/src/qrc/QUI/WELCOMEFINISHPAGE.bmp")
		#set(CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP "${CMAKE_SOURCE_DIR}/src/qrc/QUI/UNWELCOMEFINISHPAGE.bmp")
		#set(CPACK_NSIS_MUI_HEADERIMAGE "${CMAKE_SOURCE_DIR}/src/qrc/QUI/HEADERIMAGE.bmp")
		set(CPACK_NSIS_MODIFY_PATH ON)
		set(CPACK_NSIS_MUI_FINISHPAGE_RUN ON)
		set(CPACK_NSIS_HELP_LINK "http://www.fastcae.com/index.php?mod=document")
		set(CPACK_NSIS_URL_INFO_ABOUT "http://www.fastcae.com/index.php?mod=product")
		set(CPACK_NSIS_MENU_LINKS "http://www.fastcae.com/" "FastCAE网站")
		set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
	elseif(WIX_EXECUTABLE)
		list(APPEND CPACK_GENERATOR "WIX")
		set(CPACK_WIX_PROPERTY_ARPCOMMENTS ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
    	set(CPACK_WIX_PROPERTY_ARPURLINFOABOUT "http://www.fastcae.com/index.php?mod=product")
    	set(CPACK_WIX_PROPERTY_ARPHELPLINK "http://www.fastcae.com/")
    endif ()
endif()

# 向用户打印一条信息
message(STATUS "CPack generators: ${CPACK_GENERATOR}")