CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(test) # 项目名称

# 把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST
AUX_SOURCE_DIRECTORY(. SRC_LIST)

# 生成应用程序 test
ADD_EXECUTABLE(test ${SRC_LIST})

# TARGET_LINK_LIBRARIES(test pthread)