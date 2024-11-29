#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cstdlib>


#include "BiGraph.h"

// use an unorder map to store run time config
// pay attention to that every key & value is a string
const std::unordered_map<std::string, std::string> readConfigFile(const std::string& filePath) {
    std::unordered_map<std::string, std::string> config;
    std::ifstream infile(filePath);
    std::string line;
    while (std::getline(infile, line)) {
        // skip empty lines and comment line
        if (line.empty() || line[0] == '#') continue;
        //  "key = value" format
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            // remove space next to keys & values
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            config[key] = value;
        }
    }
    infile.close();
    return config;
}



int main() {
    const std::string configFilePath = "config.cfg";
    const auto config = readConfigFile(configFilePath);


    BiGraph graph(config);
    // graph.displayAdjMatrix();


    for(int i=0;i<10;i++){
        std::cout<<graph.tls_estimate(2)<<std::endl;
    }


    // 生成一些随机整数
    // for (int i = 0; i < 100; ++i) {
    //     std::cout << "Random number: " << range.getRandom() << std::endl;
    // }

    return 0;
}
