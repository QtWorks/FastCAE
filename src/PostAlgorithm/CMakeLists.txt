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
add_library(PostAlgorithm
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(PostAlgorithm PRIVATE "POSTALGORITHM_API")
#target_compile_definitions(PostAlgorithm PRIVATE "H5_BUILT_AS_DYNAMIC_LIB")

list(APPEND _depend_library Common)

list(APPEND _runtimes_libraries
	FASTCAE::CGNS FASTCAE::HDF5 FASTCAE::HDF5CPP FASTCAE::TECIO Qt5::Core VTK::CommonColor VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::DICOMParser VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersHybrid VTK::FiltersModeling VTK::FiltersParallel VTK::FiltersSources VTK::FiltersStatistics VTK::FiltersTexture VTK::IOCore VTK::IOGeometry VTK::IOImage VTK::IOLegacy VTK::IOParallel VTK::IOXML VTK::IOXMLParser VTK::ImagingCore VTK::ImagingFourier VTK::ImagingSources VTK::ParallelCore VTK::ParallelDIY VTK::RenderingCore VTK::doubleconversion VTK::expat VTK::jpeg VTK::jsoncpp VTK::lz4 VTK::lzma VTK::metaio VTK::png VTK::pugixml VTK::sys VTK::tiff VTK::zlib
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(PostAlgorithm PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(PostAlgorithm ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_PostAlgorithm_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)