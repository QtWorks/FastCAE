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
add_library(PostInterface
	${_resource}
	${_interface}
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(PostInterface PRIVATE "POSTINTERFACE_API")

list(APPEND _depend_library PythonModule PostRenderData)

list(APPEND _runtimes_libraries
	Qt5::Core Qt5::Gui Qt5::Widgets VTK::CommonColor VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::DICOMParser VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersHybrid VTK::FiltersModeling VTK::FiltersSources VTK::FiltersStatistics VTK::GUISupportQt VTK::IOCore VTK::IOImage VTK::IOLegacy VTK::IOMovie VTK::IOXML VTK::IOXMLParser VTK::ImagingColor VTK::ImagingCore VTK::ImagingFourier VTK::ImagingGeneral VTK::ImagingHybrid VTK::ImagingSources VTK::InteractionStyle VTK::InteractionWidgets VTK::ParallelCore VTK::ParallelDIY VTK::RenderingAnnotation VTK::RenderingCore VTK::RenderingFreeType VTK::RenderingOpenGL2 VTK::RenderingUI VTK::RenderingVolume VTK::doubleconversion VTK::expat VTK::freetype VTK::glew VTK::jpeg VTK::lz4 VTK::lzma VTK::metaio VTK::png VTK::pugixml VTK::sys VTK::tiff VTK::zlib
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(PostInterface PRIVATE
	${_runtimes_libraries}
	${_depend_library}
)

#-----------------------------------------------------------------------------
# 添加依赖关系
#-----------------------------------------------------------------------------
add_dependencies(PostInterface ${_depend_library})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_PostInterface_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)
