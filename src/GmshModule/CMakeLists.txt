#-----------------------------------------------------------------------------
# 头文件搜索路径
#-----------------------------------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

#-----------------------------------------------------------------------------
# 自动添加include目录
#-----------------------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-----------------------------------------------------------------------------
# 添加资源文件
#-----------------------------------------------------------------------------
set(_qrc "${CMAKE_CURRENT_SOURCE_DIR}/../qrc/qianfan.qrc")
set(_lang "${CMAKE_CURRENT_SOURCE_DIR}/../qrc/translations.qrc")
qt5_add_resources(_resource ${_qrc} ${_lang})

#-----------------------------------------------------------------------------
# 源码扫描
#-----------------------------------------------------------------------------
file(GLOB _ui "*.ui")
file(GLOB _header "*.h")
file(GLOB _source "*.cpp")
qt5_wrap_ui(_interface ${_ui})

#-----------------------------------------------------------------------------
# 添加动态库目标
#-----------------------------------------------------------------------------
add_library(GmshModule
	${_resource}
	${_interface}
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(GmshModule PRIVATE "GMSH_API")

list(APPEND _depend_library Common PythonModule Settings DataProperty Geometry MeshData SelfDefObject ModuleBase GeometryWidgets)

list(APPEND _runtimes_libraries
	OpenCASCADE::TKBO OpenCASCADE::TKBRep OpenCASCADE::TKG2d OpenCASCADE::TKG3d OpenCASCADE::TKGeomAlgo OpenCASCADE::TKGeomBase OpenCASCADE::TKMath OpenCASCADE::TKPrim OpenCASCADE::TKShHealing OpenCASCADE::TKTopAlgo OpenCASCADE::TKernel Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml VTK::CommonColor VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersSources VTK::FiltersStatistics VTK::IOCore VTK::IOLegacy VTK::IOXML VTK::IOXMLParser VTK::ImagingCore VTK::ImagingFourier VTK::ImagingMath VTK::InteractionStyle VTK::ParallelCore VTK::ParallelDIY VTK::RenderingCore VTK::RenderingFreeType VTK::RenderingOpenGL2 VTK::RenderingUI VTK::RenderingVolume VTK::RenderingVolumeOpenGL2 VTK::doubleconversion VTK::expat VTK::freetype VTK::glew VTK::lz4 VTK::lzma VTK::sys VTK::zlib
)
#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(GmshModule PRIVATE 
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(GmshModule ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_GmshModule_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)

#-----------------------------------------------------------------------------
# 安装gmsh可执行程序
#-----------------------------------------------------------------------------
install(PROGRAMS
	${Gmsh_EXECUTABLE}
	DESTINATION ${INSTALL_BINDIR}
)