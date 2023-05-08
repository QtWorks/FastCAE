
# 说明


## 源码文件夹结构
- cmake： cmake相关的脚本
- doc： 生成文档需要的模板及配置文件
- extlib： 第三方依赖库（见下文extlib获取方式）
- src： FastCAE源码
- test： 包含单元测试代码（待整理）


### extlib目录结构

   ```
   extlib
   ├─CGNS(version:4.3.0)
   │
   ├─Gmsh(version:4.8.0)
   │
   ├─HDF5(version:1.13.1)
   │
   ├─OCC(version:7.6.0)
   │
   ├─Python(version:3.7.0)
   │
   ├─QuaZIP(version:0.7.3)
   │
   ├─Qwt(version: Qwt:6.1.6 QwtPolar:1.1.1)
   │
   ├─TecIO(version:1.4.2)
   │
   └─VTK(version:9.0.1)

   ```


### extlib获取方式

   ### Linux系统

   ```bash
   git clone https://gitee.com/DISOGitee/FastCAELinuxExtlib.git extlib
   ```

   ### windows系统

   ```bash
   git clone https://gitee.com/DISOGitee/FastCAEWinExtlib.git extlib
   ```



## 编译打包

项目采用cmake构建系统组织代码，可以直接使用cmake转换visual studio 2017工程或者生成Makefile文件，或者可以直接使用支持cmake系统的IDE（比如：vscode、clion、visual studio、qtcreator等）打开项目文件夹进行构建、编译。

> 项目依赖文件会在构建阶段根据系统自动克隆对应的依赖库到本地extlib文件夹，如果需要离线部署，可以在“extlib获取方式”中离线下载依赖库。

构建项目:

```
cmake -DCMAKE_INSTALL_PREFIX:PATH=/path_to_install -DQt5_DIR:PATH=/path_of_Qt5Config.cmake  -B build -S . 
```

> 如果在windows环境下使用命令行构建项目需要增加参数`-G "Visual Studio 15 2017 Win64"`，具体参数需要根据自己的Visual Studio的版本确定，

安装:

```
cmake --build build --target install
```

源码（`.tar.gz` and `.zip`）打包:

```
cmake --build build --target package_source
```

制作安装包（`.deb` `.rpm` `.exe`）:

```
cmake --build build --target package
```

**备注：**
> 1、如果构建系统是Makefile、Ninja、Xcode，则生成`package`目标，如果是MVSC构建系统，则生成大写的`PACKAGE`目标。
>
> > `cmake --build . --target package` 或者 `make package` 或者 `ninja package`

> 2、如果构建系统是Makefile、Ninja，还会则生成`package_source`目标用于打包源码。
>
> >  `cmake --build . --target package_source` 或者 `make package_source` 或者 `ninja package_source`



## 特别说明

- 源码绝对路径中不要出现中文字符、空格以及特殊字符:(){}*/?|\等
- 要求cmake的最低版本为3.21
- windows环境制作安装包要求NSIS版本为3.03+
- linux环境制作安装包需要安装`dpkg-deb`或者`rpmbuild`
- linux的其他系统依赖包`OpenGL`、`fontconfig`、`xkbcommon`


## 测试平台
| 序号 | 操作系统 | GLIBC版本 | 编译器 | Qt | 测试结果 | 备注 |
| :--: | :-----------: | :-------: | :---------: | :--: | :--: | :--: |
|  1   |  Ubuntu18.04  | 2.27 |   GNU GCC 7.5.0    |   Qt5.14.2    |   通过   |      |
|  2   |  Ubuntu20.04  | 2.31 | GNU GCC 9.4.0 |   Qt5.14.2    | 通过 |      |
|  3   |  Ubuntu22.04  | 2.35 | GNU GCC 11.2.0 |      Qt5.14.2       | 通过 | deb成功打包 |
|  4   |   CentOS 7.0.1406   | 2.17 |   GNU GCC 8.3.1    |   Qt5.14.2    |   通过   | 借助devtoolset-8升级GCC |
| 5 | CentOS 7.9.2009 | 2.17 | GNU GCC 7.5.0 | Qt5.14.2 | 通过 |  |
|  6   |   CentOS 8.5.2111   | 2.28 | GNU GCC 8.5.0 | Qt5.14.2 | 通过 | rpm成功打包 |
|  7   |  RedHat Server 7.0  |  |           |             |      | 待测试 |
| 8 | RedHat 8.1 | 2.28 | GNU GCC 8.5.0 | Qt5.14.2 | 通过 |  |
| 9 | RedHat 9.0 | | |          | | 待测试 |
|  10  |  Windows7 X64   | 无 | Visual Studio 2017 Community | Qt5.14.2 | 通过 | VS附带安装Windows 8.1SDK |
|  11  |  Windows10 X64   | 无 | Visual Studio 2017 Community | Qt5.14.2 |   通过   | SDK 10.0.17763.0，NSIS成功打包 |
| 12 | deepin 20.7社区版 | |  |          |  | 待测试 |
| 13 | ubuntukylin 22.04 | 2.35 | GNU GCC 11.2.0 | Qt5.14.2 | 通过 | 基于Ubuntu22.04 |


## 相关链接

- 帮助文档：http://www.fastcae.com/index.php?mod=document
- 社区论坛：http://disc.fastcae.com/


## 感谢开源贡献者

- 陈宗衍 czy.t@163.com（Ribbon风格组件）
- 张立春 zhang.lichun@foxmail.com（远程任务提交插件）
- 赵德祥 zhao.dexiang@foxmail.com（远程任务提交插件）
- 万义钊 wanyizhao@mail.cgs.gov.cn （Tecplot后处理文件格式szplt解析）


## 使用交流

技术交流QQ群：671925863

官方微信号：FastCAE-DISO
