makefile 编译器我用的 clang++，你可能想改成 g++


### 修改配置
把./konect_datasets/ucidata-zachary/out.ucidata-zacharyd的绝对路径复制到 ./config.cfg 中
注意等号两边要有个空格

### 运行方式
```shell
make
./program
```

bug 位于 bigraph.cpp 的 100 行