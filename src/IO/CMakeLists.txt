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
add_library(IO
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(IO PRIVATE "IO_API")

list(APPEND _depend_library Settings DataProperty Geometry MeshData Material ModelData ModuleBase PluginManager GmshModule)

list(APPEND _runtimes_libraries
	FASTCAE::QUAZIP OpenCASCADE::TKBRep OpenCASCADE::TKG2d OpenCASCADE::TKG3d OpenCASCADE::TKGeomBase OpenCASCADE::TKMath OpenCASCADE::TKernel Qt5::Core Qt5::Widgets Qt5::Xml VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersStatistics VTK::IOCore VTK::IOLegacy VTK::IOXML VTK::IOXMLParser VTK::ImagingCore VTK::ImagingFourier VTK::ParallelCore VTK::ParallelDIY VTK::doubleconversion VTK::expat VTK::lz4 VTK::lzma VTK::sys VTK::zlib
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(IO PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(IO ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_IO_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)