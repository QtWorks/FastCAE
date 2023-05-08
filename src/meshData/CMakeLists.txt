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
add_library(MeshData
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(MeshData PRIVATE "MESHDATA_API")

list(APPEND _runtimes_libraries
	Qt5::Widgets Qt5::Xml VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersStatistics VTK::FiltersVerdict VTK::IOCore VTK::IOLegacy VTK::IOXML VTK::IOXMLParser VTK::ImagingCore VTK::ImagingFourier VTK::ParallelCore VTK::ParallelDIY VTK::doubleconversion VTK::expat VTK::lz4 VTK::lzma VTK::sys VTK::verdict VTK::zlib
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(MeshData PRIVATE
	${_runtimes_libraries}
	DataProperty
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(MeshData DataProperty)

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_MeshData_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)