# RTRenderLab

  这是一个用OpenGL开发的实时渲染器，拥有基于Qt的GUI界面。程序代码用C++写成，用了部分C++11的特性。代码架构以及基础代码参考了[Joey de Vries]( https://learnopengl.com/ ) 的讲解现代OpenGL开发的教程。

## 配置指南

  在本项目的[Release]( https://github.com/convlCode/RTRenderLab/releases )页面部分版本可以下载可直接执行的程序版本(如v060版本，其中含有“bin”字样的压缩包)，下面给出从源码运行本渲染器的方法。

### 环境需求

1. 支持C++11的C++编译器，本人开发时使用的Visual Studio 2017 。 
2. 安装Qt开发包，本人开发时使用的Qt5.12 
3. 用CMake编译Assimp三维模型加载库，具体配置方式见[Assimp官网]( http://www.assimp.org )的说明

### 运行
  安装好上述环境后，先下载本仓库的源代码。然后打开Qt Creator，并点击软件菜单栏的“文件->打开文件或项目”，找到下载代码的目录，点击RTRRenderLab.pro文件即可打开本项目。接下来只需在Qt Creator中编译代码就可以运行了。渲染器运行界面如下:  
  ![程序界面](https://github.com/convlCode/RTRenderLab/blob/master/images/demo3.png "程序界面")
  ![程序界面2](https://github.com/convlCode/RTRenderLab/blob/master/images/demo4.png "程序界面2")

## 版本控制

本项目所有的历史版本可以在该仓库的“releases”中找到---[releases on this repository](https://github.com/convlCode/RTRenderLab/releases) 。

## 作者

* **ConvlCode**

## License

本项目遵循 GPLv3 License - 点击查看详情 [LICENSE.md](https://github.com/convlCode/RTRenderLab/blob/master/LICENSE) 。
