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
add_library(GeometryCommand
	${_resource}
	${_interface}
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(GeometryCommand PRIVATE "GEOMETRYCOMMAND_API")

list(APPEND _depend_library DataProperty Geometry ModuleBase GeometryDataExchange)

list(APPEND _runtimes_libraries
	OpenCASCADE::Freetype OpenCASCADE::TKBO OpenCASCADE::TKBRep OpenCASCADE::TKBool OpenCASCADE::TKFillet OpenCASCADE::TKG2d OpenCASCADE::TKG3d OpenCASCADE::TKGeomAlgo OpenCASCADE::TKGeomBase OpenCASCADE::TKHLR OpenCASCADE::TKIVtk OpenCASCADE::TKMath OpenCASCADE::TKMesh OpenCASCADE::TKOffset OpenCASCADE::TKPrim OpenCASCADE::TKService OpenCASCADE::TKShHealing OpenCASCADE::TKTopAlgo OpenCASCADE::TKV3d OpenCASCADE::TKernel Qt5::Core Qt5::Gui Qt5::Widgets VTK::CommonColor VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersSources VTK::FiltersStatistics VTK::IOCore VTK::IOLegacy VTK::IOXML VTK::IOXMLParser VTK::ImagingCore VTK::ImagingFourier VTK::ImagingMath VTK::InteractionStyle VTK::ParallelCore VTK::ParallelDIY VTK::RenderingCore VTK::RenderingFreeType VTK::RenderingGL2PSOpenGL2 VTK::RenderingOpenGL2 VTK::RenderingUI VTK::RenderingVolume VTK::RenderingVolumeOpenGL2 VTK::doubleconversion VTK::expat VTK::freetype VTK::glew VTK::lz4 VTK::lzma VTK::sys VTK::zlib
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(GeometryCommand PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 运行依赖库
#-----------------------------------------------------------------------------
set(FastCAE_GeometryCommand_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(GeometryCommand ${_depend_library})