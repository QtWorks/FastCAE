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
add_library(PostRenderData
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(PostRenderData PRIVATE "POSTRENDERDATA_API")

list(APPEND _runtimes_libraries
	Qt5::Core Qt5::Gui VTK::CommonColor VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::DICOMParser VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersFlowPaths VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersHybrid VTK::FiltersModeling VTK::FiltersParallel VTK::FiltersSources VTK::FiltersStatistics VTK::FiltersTexture VTK::IOCore VTK::IOGeometry VTK::IOImage VTK::IOLegacy VTK::IOParallel VTK::IOXML VTK::IOXMLParser VTK::ImagingColor VTK::ImagingCore VTK::ImagingFourier VTK::ImagingGeneral VTK::ImagingHybrid VTK::ImagingSources VTK::InteractionStyle VTK::InteractionWidgets VTK::ParallelCore VTK::ParallelDIY VTK::RenderingAnnotation VTK::RenderingCore VTK::RenderingFreeType VTK::RenderingVolume VTK::doubleconversion VTK::expat VTK::freetype VTK::jpeg VTK::jsoncpp VTK::lz4 VTK::lzma VTK::metaio VTK::png VTK::pugixml VTK::sys VTK::tiff VTK::zlib
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(PostRenderData PRIVATE
	${_runtimes_libraries}
	PostAlgorithm
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(PostRenderData PostAlgorithm)

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_PostRenderData_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)