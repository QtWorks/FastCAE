﻿#-----------------------------------------------------------------------------
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
add_library(PostCurveDataManager
	${_header}
	${_source}
)	

#-----------------------------------------------------------------------------
# 添加接口声明宏
#-----------------------------------------------------------------------------
target_compile_definitions(PostCurveDataManager PRIVATE "POSTCURVEDATAMANAGER_API")

list(APPEND _runtimes_libraries
	Qt5::Core
)

#-----------------------------------------------------------------------------
# 链接依赖库
#-----------------------------------------------------------------------------
target_link_libraries(PostCurveDataManager PRIVATE ${_runtimes_libraries})

#-----------------------------------------------------------------------------
# 添加运行时依赖关系
#-----------------------------------------------------------------------------
set(FastCAE_PostCurveDataManager_Runtimes_Libraries ${_runtimes_libraries} PARENT_SCOPE)