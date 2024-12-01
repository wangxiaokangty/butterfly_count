#include "BiGraph.h"
#include "RandomRange.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <filesystem>




double BiGraph::estimate_random_te(){
    tls_setup();
    int random_edge =  edge_sampler.getRandomInt();
    // int random_edge = edge;
    int left_node=from_vertexes[random_edge],right_node=to_vertexes[random_edge];
    int left_node_deg = vertex_degs[left_node],right_node_deg = vertex_degs[right_node];
    if (left_node_deg<2||right_node_deg<2){
        return 0;
    }
    RandomRange wedge_sapler{0,left_node_deg+right_node_deg-1};
    int wedge_random = wedge_sapler.getRandomInt();
    if(wedge_random<left_node_deg){
        // left_node in a side , the others in another side
        int new_node = adj[left_node][wedge_random];
        if(new_node==right_node) return 0;
        double bias = static_cast<double>(left_node_deg+right_node_deg) / (left_node_deg+right_node_deg - 2);
        if(right_node_deg<vertex_degs[new_node]){
            int tmp = new_node;
            new_node = right_node;
            right_node = tmp;
        }
        // new_node is the node with lower degree than right node
        int iterate_num;
        if(vertex_degs[new_node]<sqrt_m){
            RandomRange real_sampler{0.0,1.0};
            if(real_sampler.getRandomReal() > static_cast<double>(vertex_degs[new_node])/sqrt_m){
                iterate_num = 1;
            }else {
                return 0;
            }
        }else {
            iterate_num = static_cast<int>(vertex_degs[new_node]/sqrt_m)+1;
        }
        // iterate_num != 1,loop will run
        std::vector<double> results;
        RandomRange neighbor_sampler{0,vertex_degs[new_node]-1};
        int number = neighbor_sampler.getRandomInt();
        int fourth_node = adj[new_node][number];
        for(int i=0;i<iterate_num;i++){
            double result = 0;
            if ( (fourth_node<new_node) && (fourth_node!=left_node) && (is_edge.find({fourth_node,right_node})!=is_edge.end())){
                result = std::max(static_cast<double>(vertex_degs[new_node]),sqrt_m);
            }
            results.push_back(result);
        } 
        double sum = static_cast<double>(std::accumulate(results.begin(), results.end(), 0.0));
        return sum*bias/iterate_num;
    }else {
        // right_node in a side , the others in another side
        int new_node = adj[right_node][wedge_random-left_node_deg];
        if(new_node==left_node) return 0;
        double bias = static_cast<double>(left_node_deg+right_node_deg) / (left_node_deg+right_node_deg - 2);
        if(left_node_deg<vertex_degs[new_node]){
            int tmp = new_node;
            new_node = left_node;
            left_node = tmp;
        }
        // new_node is the node with lower degree than left node
        int iterate_num;
        if(vertex_degs[new_node]<sqrt_m){
            RandomRange real_sampler{0.0,1.0};
            if(real_sampler.getRandomReal() > static_cast<double>(vertex_degs[new_node])/sqrt_m){
                iterate_num = 1;
            }else {
                return 0;
            }
        }else {
            iterate_num = static_cast<int>(vertex_degs[new_node]/sqrt_m)+1;
        }
        // iterate_num != 1,loop will run
        std::vector<double> results;
        RandomRange neighbor_sampler{0,vertex_degs[new_node]-1};
        int number = neighbor_sampler.getRandomInt();
        int fourth_node = adj[new_node][number];
        for(int i=0;i<iterate_num;i++){
            double result = 0;
            if ( (fourth_node<new_node) && (fourth_node!=right_node) && (is_edge.find({fourth_node,left_node})!=is_edge.end())){
                result = std::max(static_cast<double>(vertex_degs[new_node]),sqrt_m);
            }
            results.push_back(result);
        } 
        double sum = static_cast<double>(std::accumulate(results.begin(), results.end(), 0.0));
        return sum*bias/iterate_num;
    }
}


double BiGraph::tls_estimate(int time_limit_seconds){
    auto start_time = std::chrono::high_resolution_clock::now();
    auto time_limit = std::chrono::seconds(time_limit_seconds);
    std::vector<double> results;
    while (1) {
        auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time;
        if (elapsed_time >= time_limit) {
            break; // 如果已经超过时间上限，退出循环
        }
        results.push_back(estimate_random_te());
    }

    return std::accumulate(results.begin(), results.end(), 0.0)*m/results.size();
}

void BiGraph::tls_setup(){
    sqrt_m = sqrt(static_cast<double>(m));
}


void BiGraph::read_raw(std::unordered_map<std::string, std::string> config){
    std::filesystem::path serialize_path = config["serialize_path"];
    DataStream ds;
    if (!std::filesystem::exists(serialize_path)){
        std::ifstream ifs(config["data_path"]);
        std::string line;
        // ignore the first line
        std::getline(ifs,line);
        std::getline(ifs,line);
        std::istringstream iss(line);
        char tmp;
        iss>>tmp>>m>>n_left>>n_right; n=n_left+n_right;
        from_vertexes.resize(2*m+2);
        to_vertexes.resize(2*m+2);
        adj.resize(n+2);

        int edge_count=0;
        while (std::getline(ifs,line)) {
            std::istringstream iss(line);
            int a,b;
            iss>>a>>b; b+=n_left;
            from_vertexes[edge_count]=a;to_vertexes[edge_count++]=b;
            from_vertexes[edge_count]=b;to_vertexes[edge_count++]=a;
            adj[a].push_back(b);
            adj[b].push_back(a);       
        }

        // compute degs of all vertex
        vertex_degs.push_back(0);
        for(int vertex=1;vertex<=n;vertex++){
            vertex_degs.push_back(adj[vertex].size());
        }

        // compute degs of all edges
        for(int edge=0;edge<2*m;edge++){
            int edge_deg = vertex_degs[to_vertexes[edge]] + vertex_degs[from_vertexes[edge]];
            edge_degs.push_back(edge_deg);
        }

        ds << *this;
        ds.save(config["serialize_path"]);
    }else {
        ds.load(config["serialize_path"]);
        ds >> *this;
    }
}


// read graph from raw_data
BiGraph::BiGraph(std::unordered_map<std::string, std::string> config)
{
    read_raw(config);
    edge_sampler = RandomRange(0,m-1);
    for(int vertex=1;vertex<=n;vertex++){
        for (auto neighbor : adj[vertex]){
            is_edge.insert({vertex,neighbor});
        }
    }
    
}

BiGraph::BiGraph(){}

void BiGraph::displayAdjMatrix() const {
    std::cout << "adjcent matrix:" << std::endl;
    for (const auto& row : adj) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    int sum=0;
    for(int vertex=0;vertex<=n;vertex++){
        sum += vertex_degs[vertex];
    }
    std::cout<<"sum"<<sum;
}
