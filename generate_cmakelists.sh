#!/bin/sh

#工程路径
app_path=`pwd`

# 工程头文件路径
project_include_path=\
( \
	s1 \
	s2 \
	s3 \
)

# 工程源代码路径
project_src_path=\
( \
	s1 \
	s2 \
	s3 \
)

# 外部库头文件路径
include_paths=\
( \
	/usr/local/include\
)

# 链接的库路径
libs_path=\
( \
	/usr/local/lib\
)

# 需要连接的库名称,动态库可以这样使用，例如“ACE-5.7.1”实际的动态库名为libACE-5.7.1.so,静态库请使用全称
libs=\
( \
	libjsoncpp.a\
	libboost_system.a\
)

# 预编译宏配置
define_set=\
( \
)

# 动态库或静态库版本号配置
version=1.0.0

#=================以下内容不需要进行修改============================================================
# 输入参数校验
if [ $# != 2 ] ; then
	printf "\t[common error]\n\tplease input \"sh $0 app_name app_type\"\n\tapp_type is {app, shared, static}\n"
	exit 1
fi

if [ "$1" == "" ] || [ "$2" == "" ] ; then
	printf "\t[common error]\n\tplease input \"sh $0 app_name app_type\"\n\tapp_type is {app, shared, static}\n"
	exit 2
fi

if [ "$2" != "app" ] && [ "$2" != "shared" ] && [ "$2" != "static" ] ; then
	printf "\t[2th argumenterror]\n\tplease input \"sh $0 app_name app_type\"\n\tapp_type is {app, shared, static}\n"
	exit 3
fi

# 输出的应用程序名称
app_name=$1
# 输出的应用程序类型
app_type=$2

# 清除上一次的缓存文件和文件夹
echo "delete template files: [CMakeFiles, cmake_install.cmake, CMakeCache.txt, Makefile]..."
rm -rf CMakeFiles 2>/dev/null
rm -rf cmake_install.cmake 2>/dev/null
rm -rf CMakeCache.txt 2>/dev/null
rm -rf Makefile 2>/dev/null
rm -rf CMakeLists.txt 2>/dev/null
rm -rf config.log 2>/dev/null

echo "creat CMakeLists.txt"
touch CMakeLists.txt
touch config.log

echo "generate cmakelists.txt"

# 设置cmake的最低本版要求
echo "cmake_minimum_required(VERSION 2.8)" >> CMakeLists.txt

echo >> CMakeLists.txt
# 设置工程名称
echo "project(${app_name})" >> CMakeLists.txt

# 设置源文件类型编码类型和生成后的编码集合
#echo "set(CMAKE_CXX_FLAGS \"-finput-charset=GB18030 -fexec-charset=UTF8")" >> CMakeLists.txt

# 设置编译标记，debug模式支持的编译参数和relese模式的编译参数
echo "set(CMAKE_CXX_FLAGS_DEBUG \"-g3 -Wall -g -ggdb\")" >> CMakeLists.txt
printf "set(CMAKE_CXX_FLAGS_DEBUG \"-g3 -Wall -g -ggdb\")\n" >> config.log

echo "set(CMAKE_CXX_FLAGS_RELEASE \"-O2 -Wall\")" >> CMakeLists.txt
printf "set(CMAKE_CXX_FLAGS_RELEASE \"-O2 -Wall\")\n" >> config.log

echo "set(CMAKE_CXX_STANDARD 11)" >> CMakeLists.txt
printf "set(CMAKE_CXX_STANDARD 11)\n" >> config.log

# 如果生成的目标是动态库类型则设置动态库版本号
if [ "$2" == "shared" ] || [ "$2" == "static" ]; then
    echo "set(LIB_VERSION ${version})" >> CMakeLists.txt
fi

echo >> CMakeLists.txt

# 添加外部库的头文件路径
echo "append lib include path ..."
for x in ${include_paths[*]}; do
	echo "include_directories(${x})" >> CMakeLists.txt
	printf "include dir ${x}\n" >> config.log
	done
echo "append lib include path ok"
echo >> CMakeLists.txt

# 添加工程的头文件路径
echo "append include path ..."
echo "include_directories(.)" >> CMakeLists.txt
for subdir in ${project_include_path[*]}; do
	#获取目录树结构
	include_tree=`find ${subdir} -type d`
	for x in ${include_tree[*]}; do
		echo "include_directories(${x})" >> CMakeLists.txt
		printf "include dir ${x}\n" >> config.log
		done
	done
echo "append include path ok"
echo >> CMakeLists.txt

# 添加工程的源文件路径
echo "append src path ..."
echo "aux_source_directory(. SRC_LIST)" >> CMakeLists.txt
for subdir in ${project_src_path[*]}; do
	#获取目录树结构
	str_tree=`find ${subdir} -type d`
	for x in ${str_tree[*]}; do
		echo "aux_source_directory(${x} SRC_LIST)" >> CMakeLists.txt
		printf "src dir ${x}\n" >> config.log
		done
	done
echo "append src path ok"
echo >> CMakeLists.txt

# 添加依赖的库路径
echo "append lib path ..."
for x in ${libs_path[*]}; do
	echo "link_directories(${x})" >> CMakeLists.txt
	printf "lib dir ${x}\n" >> config.log;
	done
echo "append lib path ok"
echo >> CMakeLists.txt

#添加预定义的宏定义
echo "append define ..."
for x in ${define_set[*]}; do
	echo "add_definitions(-D${x})" >> CMakeLists.txt
	printf "define ${x}\n" >> config.log
	done
echo "append define ok"
echo >> CMakeLists.txt

#根据输出的配置类型生成动态库或可执行程序
if [ "$2" == "app" ] ; then
	echo "add_executable(\${PROJECT_NAME} \${SRC_LIST})" >> CMakeLists.txt
    echo "SET(EXECUTABLE_OUTPUT_PATH bin)" >> CMakeLists.txt
elif [ "$2" == "shared" ] ; then
	echo "add_library(\${PROJECT_NAME} SHARED \${SRC_LIST})" >> CMakeLists.txt
	echo "SET(LIBRARY_OUTPUT_PATH lib)" >> CMakeLists.txt
	echo "SET_TARGET_PROPERTIES(\${PROJECT_NAME} PROPERTIES VERSION \${LIB_VERSION})" >> CMakeLists.txt
else
	echo "add_library(\${PROJECT_NAME} STATIC \${SRC_LIST})" >> CMakeLists.txt
	echo "SET(LIBRARY_OUTPUT_PATH lib)" >> CMakeLists.txt
	echo "SET_TARGET_PROPERTIES(\${PROJECT_NAME} PROPERTIES VERSION \${LIB_VERSION})" >> CMakeLists.txt
fi

# 添加库依赖
echo "append lib ..."
for x in ${libs[*]}; do
	echo "target_link_libraries(${app_name} ${x})" >> CMakeLists.txt
	printf "link lib ${x}\n" >> config.log
	done
echo "append lib ok"
echo >> CMakeLists.txt
#====================================================================================================

# 输出的提示信息
echo "auto cmake complate"
echo "[debug] cmake -DCMAKE_BUILD_TYPE=Debug -> make -j4"
echo "[release] cmake -DCMAKE_BUILD_TYPE=Release -> make -j4"

exit 0