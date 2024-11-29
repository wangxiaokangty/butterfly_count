#include "MyClass.h"
#include <iostream>

// 构造函数
MyClass::MyClass(const std::string& name) : name(name) {}

// 设置名称
void MyClass::setName(const std::string& name) {
    this->name = name;
}

// 获取名称
std::string MyClass::getName() const {
    return name;
}

// 打印信息
void MyClass::printInfo() const {
    std::cout << "Name: " << name << std::endl;
}
