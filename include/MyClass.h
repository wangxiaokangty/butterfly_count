#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>

class MyClass {
private:
    std::string name;

public:
    // 构造函数
    MyClass(const std::string& name);

    // 设置名称
    void setName(const std::string& name);

    // 获取名称
    std::string getName() const;

    // 打印信息
    void printInfo() const;
};


struct wedge
{
    long long u,v,w;
    wedge() {}
    wedge(int u,int v,int w):u(u),v(v),w(w) {}
};


#endif // MYCLASS_H
