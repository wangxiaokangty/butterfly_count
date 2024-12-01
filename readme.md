makefile 编译器我用的 clang++，你可能想改成 g++


### 修改配置
configs 目录下保存了每个数据集的不同的信息，用来统一读取的konect数据集
注意改 config 文件的两个路径
都封装到类里面了，想怎么搞你直接改 mian 函数


### 运行方式
```shell
make
./program
```

bug 位于 bigraph.cpp 的 100 行