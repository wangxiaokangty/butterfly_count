#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <iostream>

#include "BiGraph.h"


// use an unorder map to store run time config
// pay attention to that every key & value is a string
std::unordered_map<std::string, std::string> readConfigFile(const std::string& filePath) {
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

std::unordered_map<std::string, std::string> readDataConfigFile(const std::string& filePath) {
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




std::unordered_map<std::string, std::string> config;
std::unordered_map<std::string, std::string> data_config;

int main() {
    std::ios::sync_with_stdio(false);
    const std::string configFilePath = "config.cfg";
    config = readConfigFile(configFilePath);
    data_config = readDataConfigFile(config["data_config_path"]);

    BiGraph g(config);
    

    // BiGraph g(config);
    
    // std::cout<<"read file finsh"<<std::endl;
    // for(int i=0;i<10;i++){
    //     std::cout << g.tls_estimate(2)<<std::endl;
    // }

    return 0;
}
