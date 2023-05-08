# FindVTK
# --------
#
# Find the VTK libraries(Only for VTK provided by FastCAE)
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``VTK_FOUND`` True if VTK found on the local system
#
# ``VTK_VERSION`` VTK Version(x.x.x)
#
# ``VTK_VERSION_MAJOR`` VTK Major Version
#
# ``VTK_VERSION_MINOR`` VTK Minor Version
#
# ``VTK_VERSION_PATCH`` VTK Patch Version
#
# ``VTK_DIRS`` Location of VTK(root dir)
#
# ``VTK_INCLUDE_DIRS`` Location of VTK header files
#
# ``VTK_LIBRARY_DIRS`` Location of VTK libraries
#
# ``VTK_LIBRARIES`` List of the VTK libraries found
#
# ``VTK_BINARY_DIRS`` Location of VTK binary
#

# 防止重复引入
if(FASTCAE_VTK_ALREADY_INCLUDED)
	return()
endif()
set(FASTCAE_VTK_ALREADY_INCLUDED 1)

set(VTK_DIRS "${CMAKE_SOURCE_DIR}/extlib/VTK")

set(VTK_VERSION_MAJOR 9)
set(VTK_VERSION_MINOR 0)
set(VTK_VERSION_PATCH 1)

set(VTK_INCLUDE_DIRS "${VTK_DIRS}/include/vtk-${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}")
set(VTK_LIBRARY_DIRS "${VTK_DIRS}/lib")
set(VTK_BINARY_DIRS "${VTK_DIRS}/bin")

set(VTK_VERSION "${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}.${VTK_VERSION_PATCH}")

macro(_populate_target_properties _target)
	add_library(${_target} SHARED IMPORTED)
	set_property(TARGET ${_target} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${VTK_INCLUDE_DIRS})
	set_property(TARGET ${_target} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
	if(ARGC GREATER 1)
		set_property(TARGET ${_target} PROPERTY INTERFACE_LINK_LIBRARIES ARGN)
	endif()
	string(SUBSTRING ${_target} 5 -1 _target_name)
	if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set_target_properties(${_target} PROPERTIES
			IMPORTED_LOCATION_RELEASE "${VTK_LIBRARY_DIRS}/libvtk${_target_name}-${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}.so.${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}.${VTK_VERSION_PATCH}"
			IMPORTED_SONAME_RELEASE "libvtk${_target_name}-${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}.so.${VTK_VERSION_PATCH}"
		)
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		set_property(TARGET ${_target} APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
		set_target_properties(${_target} PROPERTIES
			IMPORTED_IMPLIB_RELEASE "${VTK_LIBRARY_DIRS}/vtk${_target_name}-${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}.lib"
			IMPORTED_LOCATION_RELEASE "${VTK_BINARY_DIRS}/vtk${_target_name}-${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}.dll"
			IMPORTED_IMPLIB_DEBUG "${VTK_LIBRARY_DIRS}/vtk${_target_name}-${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}d.lib"
			IMPORTED_LOCATION_DEBUG "${VTK_BINARY_DIRS}/vtk${_target_name}-${VTK_VERSION_MAJOR}.${VTK_VERSION_MINOR}d.dll"
		)
	endif()
endmacro()

set(VTK_LIBRARIES VTK::ChartsCore;VTK::CommonColor;VTK::CommonComputationalGeometry;VTK::CommonCore;VTK::CommonDataModel;VTK::CommonExecutionModel;VTK::CommonMath;VTK::CommonMisc;VTK::CommonSystem;VTK::CommonTransforms;VTK::DomainsChemistry;VTK::FiltersAMR;VTK::FiltersCore;VTK::FiltersExtraction;VTK::FiltersFlowPaths;VTK::FiltersGeneral;VTK::FiltersGeneric;VTK::FiltersGeometry;VTK::FiltersHybrid;VTK::FiltersHyperTree;VTK::FiltersImaging;VTK::FiltersModeling;VTK::FiltersParallel;VTK::FiltersParallelImaging;VTK::FiltersPoints;VTK::FiltersProgrammable;VTK::FiltersSelection;VTK::FiltersSMP;VTK::FiltersSources;VTK::FiltersStatistics;VTK::FiltersTexture;VTK::FiltersTopology;VTK::FiltersVerdict;VTK::GeovisCore;VTK::GUISupportQt;VTK::GUISupportQtSQL;VTK::ImagingColor;VTK::ImagingCore;VTK::ImagingFourier;VTK::ImagingGeneral;VTK::ImagingHybrid;VTK::ImagingMath;VTK::ImagingMorphological;VTK::ImagingSources;VTK::ImagingStatistics;VTK::ImagingStencil;VTK::InfovisCore;VTK::InfovisLayout;VTK::InteractionImage;VTK::InteractionStyle;VTK::InteractionWidgets;VTK::IOAsynchronous;VTK::IOCityGML;VTK::IOCore;VTK::IOEnSight;VTK::IOExport;VTK::IOExportGL2PS;VTK::IOExportPDF;VTK::IOGeometry;VTK::IOImage;VTK::IOImport;VTK::IOInfovis;VTK::IOLegacy;VTK::IOLSDyna;VTK::IOMotionFX;VTK::IOMovie;VTK::IOOggTheora;VTK::IOParallel;VTK::IOParallelXML;VTK::IOPLY;VTK::IOSegY;VTK::IOSQL;VTK::IOTecplotTable;VTK::IOVideo;VTK::IOXML;VTK::IOXMLParser;VTK::ParallelCore;VTK::ParallelDIY;VTK::RenderingAnnotation;VTK::RenderingContext2D;VTK::RenderingCore;VTK::RenderingFreeType;VTK::RenderingGL2PSOpenGL2;VTK::RenderingImage;VTK::RenderingLabel;VTK::RenderingLOD;VTK::RenderingOpenGL2;VTK::RenderingQt;VTK::RenderingSceneGraph;VTK::RenderingUI;VTK::RenderingVolume;VTK::RenderingVolumeOpenGL2;VTK::RenderingVtkJS;VTK::TestingRendering;VTK::doubleconversion;VTK::expat;VTK::freetype;VTK::gl2ps;VTK::glew;VTK::jpeg;VTK::jsoncpp;VTK::libharu;VTK::libproj;VTK::libxml2;VTK::loguru;VTK::lz4;VTK::lzma;VTK::ogg;VTK::png;VTK::pugixml;VTK::sqlite;VTK::theora;VTK::tiff;VTK::verdict;VTK::zlib;VTK::DICOMParser;VTK::sys;VTK::metaio;VTK::ViewsContext2D;VTK::ViewsCore;VTK::ViewsInfovis;VTK::ViewsQt;VTK::WrappingTools)

_populate_target_properties(VTK::ChartsCore VTK::CommonCore VTK::CommonDataModel VTK::FiltersGeneral VTK::RenderingContext2D VTK::RenderingCore VTK::sys VTK::CommonColor VTK::CommonExecutionModel VTK::CommonTransforms VTK::InfovisCore)
_populate_target_properties(VTK::CommonColor VTK::CommonCore VTK::CommonDataModel)
_populate_target_properties(VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel)
_populate_target_properties(VTK::CommonCore VTK::sys)
_populate_target_properties(VTK::CommonDataModel VTK::CommonCore VTK::CommonMath VTK::CommonTransforms VTK::CommonMisc VTK::CommonSystem VTK::sys)
_populate_target_properties(VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::CommonMisc VTK::CommonSystem)
_populate_target_properties(VTK::CommonMath VTK::CommonCore)
_populate_target_properties(VTK::CommonMisc VTK::CommonCore VTK::CommonMath VTK::sys)
_populate_target_properties(VTK::CommonSystem VTK::CommonCore VTK::sys)
_populate_target_properties(VTK::CommonTransforms VTK::CommonCore VTK::CommonMath VTK::sys)
_populate_target_properties(VTK::DomainsChemistry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::IOLegacy VTK::IOXMLParser VTK::RenderingCore VTK::CommonTransforms VTK::FiltersCore VTK::FiltersGeneral VTK::FiltersSources VTK::sys)
_populate_target_properties(VTK::FiltersAMR VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonCore VTK::CommonMath VTK::CommonSystem VTK::FiltersCore VTK::IOXML VTK::ParallelCore)
_populate_target_properties(VTK::FiltersCore VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMisc VTK::CommonMath VTK::CommonSystem VTK::CommonTransforms VTK::sys)
_populate_target_properties(VTK::FiltersExtraction VTK::CommonCore VTK::CommonExecutionModel VTK::FiltersGeneral VTK::CommonDataModel VTK::FiltersCore VTK::FiltersStatistics VTK::ParallelDIY)
_populate_target_properties(VTK::FiltersFlowPaths VTK::CommonCore VTK::CommonComputationalGeometry VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::FiltersCore VTK::FiltersGeometry VTK::FiltersSources VTK::IOCore)
_populate_target_properties(VTK::FiltersGeneral VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMisc VTK::FiltersCore VTK::CommonComputationalGeometry VTK::CommonMath VTK::CommonSystem VTK::CommonTransforms)
_populate_target_properties(VTK::FiltersGeneric VTK::CommonExecutionModel VTK::CommonMath VTK::CommonCore VTK::CommonDataModel VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersSources)
_populate_target_properties(VTK::FiltersGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::FiltersCore VTK::sys)
_populate_target_properties(VTK::FiltersHybrid VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonTransforms VTK::FiltersGeometry VTK::CommonMath VTK::CommonMisc VTK::FiltersCore VTK::FiltersGeneral VTK::ImagingCore VTK::ImagingSources VTK::RenderingCore VTK::sys)
_populate_target_properties(VTK::FiltersHyperTree VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMisc VTK::FiltersCore VTK::FiltersGeneral VTK::CommonCore VTK::CommonSystem)
_populate_target_properties(VTK::FiltersImaging VTK::CommonCore VTK::CommonExecutionModel VTK::FiltersStatistics VTK::CommonDataModel VTK::CommonSystem VTK::ImagingGeneral)
_populate_target_properties(VTK::FiltersModeling VTK::CommonExecutionModel VTK::CommonMisc VTK::FiltersGeneral VTK::CommonCore VTK::CommonDataModel VTK::CommonTransforms VTK::FiltersCore VTK::FiltersSources)
_populate_target_properties(VTK::FiltersParallel VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersHybrid VTK::FiltersModeling VTK::FiltersSources VTK::FiltersTexture VTK::CommonSystem VTK::CommonTransforms VTK::IOLegacy VTK::ParallelCore)
_populate_target_properties(VTK::FiltersParallelImaging VTK::CommonExecutionModel VTK::FiltersImaging VTK::FiltersParallel VTK::ImagingCore VTK::CommonCore VTK::CommonDataModel VTK::CommonSystem VTK::FiltersExtraction VTK::FiltersStatistics VTK::ImagingGeneral VTK::ParallelCore)
_populate_target_properties(VTK::FiltersPoints VTK::CommonCore VTK::CommonExecutionModel VTK::CommonMisc VTK::FiltersModeling)
_populate_target_properties(VTK::FiltersProgrammable VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::CommonTransforms)
_populate_target_properties(VTK::FiltersSelection VTK::CommonCore VTK::CommonExecutionModel VTK::CommonDataModel)
_populate_target_properties(VTK::FiltersSMP VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMisc VTK::CommonTransforms VTK::FiltersCore VTK::FiltersGeneral VTK::CommonMath VTK::CommonSystem)
_populate_target_properties(VTK::FiltersSources VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonTransforms VTK::FiltersCore VTK::FiltersGeneral)
_populate_target_properties(VTK::FiltersStatistics VTK::CommonCore VTK::CommonExecutionModel VTK::CommonDataModel VTK::CommonMisc VTK::ImagingFourier)
_populate_target_properties(VTK::FiltersTexture VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::CommonTransforms VTK::FiltersGeneral)
_populate_target_properties(VTK::FiltersTopology VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel)
_populate_target_properties(VTK::FiltersVerdict VTK::CommonExecutionModel VTK::verdict VTK::CommonCore VTK::CommonDataModel)
_populate_target_properties(VTK::GeovisCore VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonTransforms VTK::InfovisCore VTK::InteractionStyle VTK::InteractionWidgets VTK::RenderingCore VTK::ViewsCore VTK::libproj VTK::CommonSystem VTK::FiltersCore VTK::FiltersGeneral VTK::IOImage VTK::IOXML VTK::ImagingCore VTK::ImagingSources VTK::InfovisLayout)
_populate_target_properties(VTK::GUISupportQt VTK::CommonCore VTK::RenderingCore VTK::RenderingOpenGL2 VTK::InteractionWidgets VTK::CommonDataModel VTK::FiltersExtraction VTK::InteractionStyle)
_populate_target_properties(VTK::GUISupportQtSQL VTK::CommonCore VTK::GUISupportQt VTK::IOSQL VTK::sys)
_populate_target_properties(VTK::ImagingColor VTK::CommonExecutionModel VTK::ImagingCore VTK::CommonCore VTK::CommonDataModel VTK::CommonSystem)
_populate_target_properties(VTK::ImagingCore VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonTransforms)
_populate_target_properties(VTK::ImagingFourier VTK::CommonCore VTK::CommonExecutionModel VTK::ImagingCore VTK::CommonDataModel VTK::sys)
_populate_target_properties(VTK::ImagingGeneral VTK::CommonExecutionModel VTK::ImagingCore VTK::CommonCore VTK::CommonDataModel VTK::ImagingSources)
_populate_target_properties(VTK::ImagingHybrid VTK::CommonCore VTK::CommonExecutionModel VTK::CommonDataModel VTK::IOImage VTK::ImagingCore)
_populate_target_properties(VTK::ImagingMath VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel)
_populate_target_properties(VTK::ImagingMorphological VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::ImagingCore VTK::ImagingGeneral VTK::ImagingSources)
_populate_target_properties(VTK::ImagingSources VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::ImagingCore)
_populate_target_properties(VTK::ImagingStatistics VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::ImagingCore)
_populate_target_properties(VTK::ImagingStencil VTK::CommonExecutionModel VTK::ImagingCore VTK::CommonComputationalGeometry VTK::CommonCore VTK::CommonDataModel)
_populate_target_properties(VTK::InfovisCore VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonColor VTK::IOImage VTK::ImagingCore VTK::ImagingSources VTK::RenderingFreeType VTK::FiltersExtraction VTK::FiltersGeneral)
_populate_target_properties(VTK::InfovisLayout VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonComputationalGeometry VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersGeneral VTK::FiltersModeling VTK::FiltersSources VTK::ImagingHybrid VTK::InfovisCore)
_populate_target_properties(VTK::InteractionImage VTK::CommonCore VTK::RenderingCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::ImagingColor VTK::ImagingCore VTK::InteractionStyle VTK::InteractionWidgets)
_populate_target_properties(VTK::InteractionStyle VTK::CommonDataModel VTK::RenderingCore VTK::CommonCore VTK::CommonMath VTK::CommonTransforms VTK::FiltersExtraction VTK::FiltersSources)
_populate_target_properties(VTK::InteractionWidgets VTK::CommonCore VTK::CommonExecutionModel VTK::FiltersGeneral VTK::FiltersSources VTK::RenderingCore VTK::CommonComputationalGeometry VTK::CommonDataModel VTK::CommonMath VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersHybrid VTK::FiltersModeling VTK::ImagingColor VTK::ImagingCore VTK::ImagingGeneral VTK::ImagingHybrid VTK::InteractionStyle VTK::RenderingAnnotation VTK::RenderingFreeType VTK::RenderingVolume)
_populate_target_properties(VTK::IOAsynchronous VTK::CommonCore VTK::CommonExecutionModel VTK::IOCore VTK::IOImage VTK::IOXML VTK::CommonDataModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::ParallelCore)
_populate_target_properties(VTK::IOCityGML VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::FiltersGeneral VTK::FiltersModeling VTK::pugixml VTK::sys)
_populate_target_properties(VTK::IOCore VTK::CommonCore VTK::CommonExecutionModel VTK::CommonDataModel VTK::CommonMisc VTK::doubleconversion VTK::lz4 VTK::lzma VTK::sys VTK::zlib)
_populate_target_properties(VTK::IOEnSight VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel)
_populate_target_properties(VTK::IOExport VTK::CommonCore VTK::IOCore VTK::IOImage VTK::IOXML VTK::RenderingContext2D VTK::RenderingCore VTK::RenderingFreeType VTK::RenderingVtkJS VTK::CommonDataModel VTK::CommonMath VTK::CommonTransforms VTK::FiltersGeometry VTK::IOImage VTK::ImagingCore VTK::jsoncpp VTK::libharu)
_populate_target_properties(VTK::IOExportGL2PS VTK::IOExport VTK::RenderingGL2PSOpenGL2 VTK::CommonCore VTK::CommonDataModel VTK::ImagingCore VTK::RenderingCore VTK::gl2ps)
_populate_target_properties(VTK::IOExportPDF VTK::IOExport VTK::RenderingContext2D VTK::CommonCore VTK::ImagingCore VTK::libharu)
_populate_target_properties(VTK::IOGeometry VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::IOCore VTK::IOLegacy VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::FiltersGeneral VTK::FiltersHybrid VTK::ImagingCore VTK::IOImage VTK::RenderingCore VTK::jsoncpp VTK::sys VTK::zlib)
_populate_target_properties(VTK::IOImage VTK::CommonCore VTK::CommonExecutionModel VTK::ImagingCore VTK::CommonDataModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::DICOMParser VTK::jpeg VTK::metaio VTK::png VTK::pugixml VTK::tiff VTK::sys VTK::zlib)
_populate_target_properties(VTK::IOImport VTK::CommonCore VTK::CommonExecutionModel VTK::CommonMisc VTK::RenderingCore VTK::sys VTK::CommonDataModel VTK::CommonTransforms VTK::FiltersCore VTK::FiltersSources VTK::ImagingCore VTK::IOGeometry VTK::IOImage VTK::jsoncpp)
_populate_target_properties(VTK::IOInfovis VTK::CommonCore VTK::CommonExecutionModel VTK::IOLegacy VTK::IOXML VTK::CommonDataModel VTK::CommonMisc VTK::IOCore VTK::IOXMLParser VTK::InfovisCore VTK::libxml2 VTK::sys)
_populate_target_properties(VTK::IOLegacy VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::IOCore VTK::CommonMisc VTK::sys)
_populate_target_properties(VTK::IOLSDyna VTK::CommonCore VTK::CommonExecutionModel VTK::IOXMLParser VTK::CommonDataModel VTK::sys)
_populate_target_properties(VTK::IOMotionFX VTK::CommonExecutionModel VTK::CommonDataModel VTK::CommonMisc VTK::IOGeometry VTK::sys)
_populate_target_properties(VTK::IOMovie VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::CommonMisc VTK::CommonSystem)
_populate_target_properties(VTK::IOOggTheora VTK::CommonExecutionModel VTK::IOMovie VTK::CommonCore VTK::CommonDataModel VTK::CommonMisc VTK::CommonSystem VTK::theora)
_populate_target_properties(VTK::IOParallel VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::IOCore VTK::IOGeometry VTK::IOImage VTK::IOLegacy VTK::jsoncpp VTK::CommonMisc VTK::CommonSystem VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersParallel VTK::ParallelCore VTK::sys)
_populate_target_properties(VTK::IOParallelXML VTK::IOXML VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMisc VTK::ParallelCore VTK::sys)
_populate_target_properties(VTK::IOPLY VTK::CommonCore VTK::IOCore VTK::CommonDataModel VTK::CommonMisc VTK::sys)
_populate_target_properties(VTK::IOSegY VTK::CommonDataModel VTK::CommonExecutionModel VTK::IOImage VTK::CommonCore)
_populate_target_properties(VTK::IOSQL VTK::CommonCore VTK::CommonExecutionModel VTK::IOCore VTK::sqlite VTK::sys)
_populate_target_properties(VTK::IOTecplotTable VTK::CommonCore VTK::CommonExecutionModel VTK::CommonDataModel VTK::IOCore VTK::sys)
_populate_target_properties(VTK::IOVideo VTK::CommonExecutionModel VTK::CommonCore VTK::CommonDataModel VTK::CommonSystem VTK::sys)
_populate_target_properties(VTK::IOXML VTK::CommonCore VTK::CommonExecutionModel VTK::IOXMLParser VTK::CommonDataModel VTK::CommonMisc VTK::CommonSystem VTK::IOCore VTK::sys)
_populate_target_properties(VTK::IOXMLParser VTK::CommonCore VTK::CommonDataModel VTK::IOCore VTK::expat VTK::sys)
_populate_target_properties(VTK::ParallelCore VTK::CommonCore VTK::CommonDataModel VTK::CommonSystem VTK::IOLegacy VTK::sys)
_populate_target_properties(VTK::ParallelDIY VTK::CommonCore VTK::CommonDataModel VTK::ParallelCore VTK::FiltersGeneral VTK::IOXML)
_populate_target_properties(VTK::RenderingAnnotation VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::RenderingCore VTK::CommonMath VTK::CommonTransforms VTK::FiltersCore VTK::FiltersGeneral VTK::FiltersSources VTK::ImagingColor VTK::RenderingFreeType)
_populate_target_properties(VTK::RenderingContext2D VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::RenderingCore VTK::CommonMath VTK::CommonSystem VTK::CommonTransforms VTK::FiltersGeneral VTK::RenderingFreeType)
_populate_target_properties(VTK::RenderingCore VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::FiltersCore VTK::CommonColor VTK::CommonComputationalGeometry VTK::CommonSystem VTK::CommonTransforms VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersSources VTK::sys)
_populate_target_properties(VTK::RenderingFreeType VTK::CommonCore VTK::CommonExecutionModel VTK::RenderingCore VTK::freetype VTK::CommonDataModel VTK::FiltersGeneral)
_populate_target_properties(VTK::RenderingGL2PSOpenGL2 VTK::RenderingOpenGL2 VTK::CommonCore VTK::CommonDataModel VTK::CommonMath VTK::RenderingCore VTK::RenderingOpenGL2 VTK::gl2ps)
_populate_target_properties(VTK::RenderingImage VTK::CommonExecutionModel VTK::RenderingCore VTK::CommonCore VTK::CommonDataModel VTK::CommonMath VTK::CommonTransforms VTK::ImagingCore)
_populate_target_properties(VTK::RenderingLabel VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::RenderingCore VTK::RenderingFreeType VTK::CommonMath VTK::CommonSystem VTK::CommonTransforms VTK::FiltersGeneral)
_populate_target_properties(VTK::RenderingLOD VTK::RenderingCore VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonMath VTK::CommonSystem VTK::FiltersCore VTK::FiltersModeling)
_populate_target_properties(VTK::RenderingOpenGL2 VTK::CommonCore VTK::CommonDataModel VTK::RenderingCore VTK::RenderingUI VTK::glew VTK::CommonExecutionModel VTK::CommonMath VTK::CommonSystem VTK::CommonTransforms VTK::sys)
_populate_target_properties(VTK::RenderingQt VTK::CommonCore VTK::CommonExecutionModel VTK::RenderingCore VTK::RenderingLabel VTK::CommonDataModel VTK::CommonSystem VTK::FiltersSources VTK::FiltersTexture VTK::GUISupportQt)
_populate_target_properties(VTK::RenderingSceneGraph VTK::CommonCore VTK::CommonDataModel VTK::CommonMath VTK::RenderingCore)
_populate_target_properties(VTK::RenderingUI VTK::RenderingCore)
_populate_target_properties(VTK::RenderingVolume VTK::CommonCore VTK::CommonExecutionModel VTK::RenderingCore VTK::CommonDataModel VTK::CommonMath VTK::CommonMisc VTK::CommonSystem VTK::CommonTransforms VTK::ImagingCore)
_populate_target_properties(VTK::RenderingVolumeOpenGL2 VTK::CommonCore VTK::CommonDataModel VTK::ImagingCore VTK::ImagingMath VTK::RenderingCore VTK::RenderingOpenGL2 VTK::RenderingVolume VTK::CommonMath VTK::CommonSystem VTK::CommonTransforms VTK::FiltersCore VTK::FiltersGeneral VTK::FiltersSources VTK::glew VTK::sys)
_populate_target_properties(VTK::RenderingVtkJS VTK::CommonCore VTK::RenderingSceneGraph VTK::jsoncpp VTK::CommonDataModel VTK::CommonExecutionModel VTK::RenderingCore)
_populate_target_properties(VTK::TestingRendering VTK::CommonCore VTK::RenderingCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::CommonSystem VTK::IOImage VTK::ImagingCore VTK::sys)
_populate_target_properties(VTK::doubleconversion)
_populate_target_properties(VTK::expat)
_populate_target_properties(VTK::freetype VTK::zlib)
_populate_target_properties(VTK::gl2ps VTK::png VTK::zlib)
_populate_target_properties(VTK::glew)
_populate_target_properties(VTK::jpeg)
_populate_target_properties(VTK::jsoncpp)
_populate_target_properties(VTK::libharu VTK::png VTK::zlib)
_populate_target_properties(VTK::libproj)
_populate_target_properties(VTK::libxml2 VTK::zlib)
_populate_target_properties(VTK::loguru)
_populate_target_properties(VTK::lz4)
_populate_target_properties(VTK::lzma)
_populate_target_properties(VTK::ogg)
_populate_target_properties(VTK::png VTK::zlib)
_populate_target_properties(VTK::pugixml)
_populate_target_properties(VTK::sqlite)
_populate_target_properties(VTK::theora VTK::ogg)
_populate_target_properties(VTK::tiff VTK::jpeg VTK::zlib)
_populate_target_properties(VTK::verdict)
_populate_target_properties(VTK::zlib)
_populate_target_properties(VTK::DICOMParser VTK::sys)
_populate_target_properties(VTK::sys)
_populate_target_properties(VTK::metaio VTK::zlib)
_populate_target_properties(VTK::ViewsContext2D VTK::CommonCore VTK::RenderingCore VTK::ViewsCore VTK::RenderingContext2D)
_populate_target_properties(VTK::ViewsCore VTK::CommonCore VTK::CommonExecutionModel VTK::InteractionWidgets VTK::CommonDataModel VTK::FiltersGeneral VTK::RenderingCore VTK::RenderingUI)
_populate_target_properties(VTK::ViewsInfovis VTK::CommonCore VTK::CommonDataModel VTK::CommonExecutionModel VTK::InteractionStyle VTK::RenderingContext2D VTK::ViewsCore VTK::ChartsCore VTK::CommonColor VTK::CommonTransforms VTK::FiltersCore VTK::FiltersExtraction VTK::FiltersGeneral VTK::FiltersGeometry VTK::FiltersImaging VTK::FiltersModeling VTK::FiltersSources VTK::FiltersStatistics VTK::ImagingGeneral VTK::InfovisCore VTK::InfovisLayout VTK::InteractionWidgets VTK::RenderingAnnotation VTK::RenderingCore VTK::RenderingLabel)
_populate_target_properties(VTK::ViewsQt VTK::CommonCore VTK::GUISupportQt VTK::ViewsCore VTK::ViewsInfovis VTK::CommonDataModel VTK::CommonExecutionModel VTK::FiltersExtraction VTK::FiltersGeneral VTK::InfovisCore)
_populate_target_properties(VTK::WrappingTools)


include(FindPackageHandleStandardArgs)

# 如果找到所有需要的变量，并且版本匹配，则将VTK_FOUND变量设置为TRUE
find_package_handle_standard_args(VTK
	FOUND_VAR
		VTK_FOUND
	REQUIRED_VARS
		VTK_DIRS
		VTK_INCLUDE_DIRS
		VTK_LIBRARY_DIRS
		VTK_LIBRARIES
		VTK_BINARY_DIRS
	VERSION_VAR
		VTK_VERSION
)