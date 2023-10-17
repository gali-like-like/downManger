#!/bin/bash
a=123
c=456
d=$0
printf "文件目录:%s 文件名：%s 完整路径:%s\n" `pwd` $0 `pwd`${d:1}
