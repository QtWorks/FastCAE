# 产品更新日志

Version：2.5.x

---
更新时间：2020-05-08

**新增功能**
- 后处理增加tecplot文件（szplt）的读取。
- 加入OpenGL版本检测函数，当环境OPenGL版本低于3.3时，给出错误提示。
- 新增自动打包功能，Windows需要NSIS 3.03+、Linux需要dpkg-deb或者rpmbuild(需要python3）。
- 新增文档自动生成功能，需要安装Doxygen和Graphviz。
- 增加vtu、pvtu格式的后处理文件支持

**功能优化**
- 代码全部采用cmake进行管理，可任意选择vscode、Visual Studio、Clion、Qtcreator等支持cmake系统的IDE。
- 后处理代码重构。
- 删除Qt浏览器组建及相关依赖（Qt安装不再需要QWebEngine组件）。
- 优化Python调用，不再依赖系统配置，简化操作。
- 从依赖库中移除未使用的VTK、OpenCASCADE模块。
- 优化CGNS后处理文件解析，添加MIXED类型单元区域的解析。
- 优化后处理属性面板场变量数据类型的显示方式。
- 优化日志输出方式，便于错误定位

**功能修复**
- 修复linux环境卸载插件时崩溃的问题
- 修复单个窗口下视图控制不正常的问题
- 修复几何绘制线段失败的问题

**其他**
- OpenCASCADE的版本变更(7.5.0->7.6.0)。
- gmsh的版本变更(4.5.4->4.8.0)。
- linux环境下的依赖库基于GLIBC2.17编译，基本满足现有linux操作系统要求。