#ifndef BI_GRAPH
#define BI_GRAPH


#include "RandomRange.h"
#include <unordered_set>
#include <vector>
#include <string>
#include <cstdlib>
#include <utility>
#include <unordered_map>


typedef long long ll;


namespace std{
template<> struct hash<pair<int, int>>{
    size_t operator()(const pair<int, int> &p) const {
        auto res = (static_cast<size_t>(p.first) << (sizeof(int) * 8)) + static_cast<size_t>(p.second);
        return res;
    }
};
template<> struct equal_to<pair<int, int>>{
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};
}

class BiGraph{
private:
    // adj[i] represent ith node' neighbor
    std::vector<std::vector<int>> adj;
    // represents ith vertex's deg & ith edge deg respectively
    // pay attention that vertex index start from 1,but edge's start from 0
    std::vector<int> vertex_degs,edge_degs;
    int m{0},n_left,n_right,n;
    std::unordered_set<std::pair<int, int>> is_edge;
    
public:
    BiGraph(std::unordered_map<std::string, std::string> config);
    void displayAdjMatrix() const;

// for tls
// record ith edge's from node & to node to sample an edge in O(1)
private:
    std::vector<int> from_vertexes,to_vertexes;
    RandomRange edge_sampler;
    double sqrt_m;
public:
    void tls_setup();
    int sample_wedge_based_edge(int edge);
    double tls_estimate(int time_limit_seconds);
    double estimate_random_te();

};


#endif