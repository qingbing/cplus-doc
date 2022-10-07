#!/bin/bash

# 构建 gcc 命令
CMD="g++ "
while [ $# != 0 ]; do
	if [ ! -f "${1}" ]; then
		echo "文件 \"${1}\" 不存在"
		exit
	fi

	CMD="${CMD} ${1}"
	shift
done

# 执行编译命令
$CMD

# 执行编译二进制文件，输出结果
if [[ -f a.out ]]; then
	# 执行编译生成的可执行文件
	./a.out
	# 将编译文件删除
	rm -f a.out
else
	echo "沒有生成的 a.out 文件"
fi
