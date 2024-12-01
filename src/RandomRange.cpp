#include "RandomRange.h"

RandomRange::RandomRange(){}

// 整数范围构造函数
RandomRange::RandomRange(int low, int high) 
    : generator(std::random_device{}()), 
      int_distribution(std::uniform_int_distribution<int>(low, high)) {}

// 实数范围构造函数
RandomRange::RandomRange(double low, double high) 
    : generator(std::random_device{}()), 
      real_distribution(std::uniform_real_distribution<double>(low, high)) {}

// 获取随机整数
int RandomRange::getRandomInt() {
    return int_distribution(generator);
}

// 获取随机实数
double RandomRange::getRandomReal() {
    return real_distribution(generator);
}
