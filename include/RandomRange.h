#ifndef RANDOM_RANGE_H
#define RANDOM_RANGE_H

#include <random>

class RandomRange {
private:
    std::mt19937 generator; // 随机数生成器
    std::uniform_int_distribution<int> int_distribution; // 整数均匀分布
    std::uniform_real_distribution<double> real_distribution; // 实数均匀分布

public:
    RandomRange();
    RandomRange(int low, int high); // 整数构造函数
    RandomRange(double low, double high); // 实数构造函数

    int getRandomInt(); // 获取随机整数
    double getRandomReal(); // 获取随机实数
};

#endif
