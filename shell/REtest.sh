#bin/bash

#egrep '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$' testfile

#这些命令没有-i选项  不改变文件内容 
#sed '/111/p' testfile   #显示 过滤到的行和所有的行
#sed -n '/111/p' testfile #只显示过滤到的行
#sed  '/111/d' testfile   #在显示的时候不显示过滤到的行

#sed '/t/s/Z/-k-/g' testfile
#sed '/t/s/Z/-k-/' testfile
#sed '/^[0-9]/s/\([0-9]*\)/~\1~/' testfile #\1表示pattern2中第一个()表示的内容
                                           # () 扩起来表示里面的内容为正则表达式的一个整体单元， 
                                           #前面加 \ 是因为sed 默认支持Basic规范 用 + ？() | {  } 前面要转义
                                           #\(..\) 实际上是把() 中匹配到的内容作为 整体 用 \1 来保存 最多可以保存到\9
#地址定位符  操作从第 某行（这一行可以是数字表示也可以是正则表达式表示）到某行
#sed -n '10, 17p' testfile
#sed -n '/33/, 15p' testfile
#sed '/^4/, /^7/d' testfile #^表示一行中第一个字符 

#sed  -n '/my$/p' testfile  #$表示一行中最后一个字符
#sed -n '/x...y/p' testfile
#sed -n '/xinr*/p' testfile  #* 匹配0 个 或多个前导字符 
#sed -n '/xinr\?/p' testfile  #? 匹配1 个 或 0 个前导字符 
#sed -n '/xiaoguodong\+/p' testfile #+匹配 1 个或多个 前导字符
#sed -n '/x[piq]n/p' testfile   # 匹配[] 中的任意一个字符 
#sed -n '/x[^qwert]n/p' testfile # 匹配不在[] 中的任意一个字符


#sed只有在语法错误的时候推出值才不是0  否则推出值都是0

























