#-----------------------------------------------------------------------------
# 头文件搜索路径
#-----------------------------------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

#-----------------------------------------------------------------------------
# 自动添加include目录
#-----------------------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-----------------------------------------------------------------------------
# 源码扫描
#-----------------------------------------------------------------------------
file(GLOB _header "*.h")
file(GLOB _source "*.cpp")

#-----------------------------------------------------------------------------
# 添加动态库目标
#-----------------------------------------------------------------------------
add_library(GeometryDataExchange
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(GeometryDataExchange PRIVATE "GEOMETRYDATAEXCHANGE_API")

list(APPEND _depend_library Common PythonModule DataProperty Geometry ModuleBase)

list(APPEND _runtimes_libraries
	OpenCASCADE::TKBO OpenCASCADE::TKBRep OpenCASCADE::TKBool OpenCASCADE::TKG2d OpenCASCADE::TKG3d OpenCASCADE::TKGeomAlgo OpenCASCADE::TKGeomBase OpenCASCADE::TKIGES OpenCASCADE::TKMath OpenCASCADE::TKPrim OpenCASCADE::TKSTEP OpenCASCADE::TKSTEP209 OpenCASCADE::TKSTEPAttr OpenCASCADE::TKSTEPBase OpenCASCADE::TKShHealing OpenCASCADE::TKTopAlgo OpenCASCADE::TKXSBase OpenCASCADE::TKernel VTK::CommonColor VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersSources VTK::FiltersStatistics VTK::IOCore VTK::IOLegacy VTK::IOGeometry VTK::IOXML VTK::IOXMLParser VTK::ImagingCore VTK::ImagingFourier VTK::ImagingMath VTK::InteractionStyle VTK::ParallelCore VTK::ParallelDIY VTK::RenderingCore VTK::RenderingFreeType VTK::RenderingOpenGL2 VTK::RenderingUI VTK::RenderingVolume VTK::RenderingVolumeOpenGL2 VTK::doubleconversion VTK::expat VTK::freetype VTK::glew VTK::lz4 VTK::lzma VTK::sys VTK::zlib
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(GeometryDataExchange  PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(GeometryDataExchange ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_GeometryDataExchange_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)