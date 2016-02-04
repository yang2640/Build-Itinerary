#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class GraphNode {
public:
    string val;
    vector<GraphNode *> neibors;
    GraphNode(string x): val(x) {}
};

struct Compare {
    bool operator()(GraphNode *x, GraphNode *y) {
        return x->val < y->val;
    }
} comp;

bool dfs(vector<string> &res, vector<string> &cur, GraphNode *x,
        unordered_map<string, int> &visit, int edgeSize) {

    if (x == nullptr) {
        return false;
    }

    if (edgeSize <= 0) {
        cur.push_back(x->val);
        res.assign(cur.begin(), cur.end());
        cur.pop_back();
        return true;
    }

    cur.push_back(x->val);
    // sort the edges by order
    sort(x->neibors.begin(), x->neibors.end(), comp);
    // avoid duplicates
    vector<GraphNode *> uniqNeibors;
    int nSize = x->neibors.size();
    if (nSize != 0) {
        uniqNeibors.push_back(x->neibors[0]);
        for (int i = 1; i < nSize; ++i) {
            if (x->neibors[i]->val != uniqNeibors.back()->val) {
                uniqNeibors.push_back(x->neibors[i]);
            } 
        }  
    }

    for (auto to: uniqNeibors) {
        string edgeStr = x->val + to->val;
        // stop seach this edge, if all them are visited
        if (visit[edgeStr] == 0) {
            continue;
        }

        --visit[edgeStr];
        if (dfs(res, cur, to, visit, edgeSize - 1)) {
            return true;
        }
        ++visit[edgeStr];
    }
    cur.pop_back();
    return false;
}

/* build a directed graph, visit all edges, for only once, print smaller order itnary if multiple */
vector<string> findItinerary(vector<pair<string, string>> &tickets) {
    if (tickets.empty()) {
        return vector<string> ();
    }

    // use a nodeMap to store the str -> node mapping
    unordered_map<string, GraphNode*> nodeMap;
    unordered_map<string, int> visit;

    for (auto x: tickets) {
        // create two nodes if they do not exist
        GraphNode *from = nullptr;
        GraphNode *to = nullptr;
        if (nodeMap.find(x.first) == nodeMap.end()) {
            from = new GraphNode(x.first);
            nodeMap[x.first] = from;
        }
        else {
            from = nodeMap[x.first];
        }

        if (nodeMap.find(x.second) == nodeMap.end()) {
            to = new GraphNode(x.second);
            nodeMap[x.second] = to;
        }
        else {
            to = nodeMap[x.second];
        }

        // create the edge
        from->neibors.push_back(to);

        // stat the edges
        visit[from->val + to->val] += 1;
    }

    // start visit from "JFK"
    vector<string> res;
    vector<string> cur;

    dfs(res, cur, nodeMap["JFK"], visit, tickets.size());
    return res;
}


int main() {
    vector<pair<string, string>> tickets = {{"MUC", "LHR"}, {"JFK", "MUC"}, 
        {"SFO", "SJC"}, {"LHR", "SFO"}};

    tickets = {{"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"}};

    tickets = {{"AXA","EZE"},{"EZE","AUA"},{"ADL","JFK"},{"ADL","TIA"},{"AUA","AXA"},{"EZE","TIA"},{"EZE","TIA"},{"AXA","EZE"},{"EZE","ADL"},{"ANU","EZE"},{"TIA","EZE"},{"JFK","ADL"},{"AUA","JFK"},{"JFK","EZE"},{"EZE","ANU"},{"ADL","AUA"},{"ANU","AXA"},{"AXA","ADL"},{"AUA","JFK"},{"EZE","ADL"},{"ANU","TIA"},{"AUA","JFK"},{"TIA","JFK"},{"EZE","AUA"},{"AXA","EZE"},{"AUA","ANU"},{"ADL","AXA"},{"EZE","ADL"},{"AUA","ANU"},{"AXA","EZE"},{"TIA","AUA"},{"AXA","EZE"},{"AUA","SYD"},{"ADL","JFK"},{"EZE","AUA"},{"ADL","ANU"},{"AUA","TIA"},{"ADL","EZE"},{"TIA","JFK"},{"AXA","ANU"},{"JFK","AXA"},{"JFK","ADL"},{"ADL","EZE"},{"AXA","TIA"},{"JFK","AUA"},{"ADL","EZE"},{"JFK","ADL"},{"ADL","AXA"},{"TIA","AUA"},{"AXA","JFK"},{"ADL","AUA"},{"TIA","JFK"},{"JFK","ADL"},{"JFK","ADL"},{"ANU","AXA"},{"TIA","AXA"},{"EZE","JFK"},{"EZE","AXA"},{"ADL","TIA"},{"JFK","AUA"},{"TIA","EZE"},{"EZE","ADL"},{"JFK","ANU"},{"TIA","AUA"},{"EZE","ADL"},{"ADL","JFK"},{"ANU","AXA"},{"AUA","AXA"},{"ANU","EZE"},{"ADL","AXA"},{"ANU","AXA"},{"TIA","ADL"},{"JFK","ADL"},{"JFK","TIA"},{"AUA","ADL"},{"AUA","TIA"},{"TIA","JFK"},{"EZE","JFK"},{"AUA","ADL"},{"ADL","AUA"},{"EZE","ANU"},{"ADL","ANU"},{"AUA","AXA"},{"AXA","TIA"},{"AXA","TIA"},{"ADL","AXA"},{"EZE","AXA"},{"AXA","JFK"},{"JFK","AUA"},{"ANU","ADL"},{"AXA","TIA"},{"ANU","AUA"},{"JFK","EZE"},{"AXA","ADL"},{"TIA","EZE"},{"JFK","AXA"},{"AXA","ADL"},{"EZE","AUA"},{"AXA","ANU"},{"ADL","EZE"},{"AUA","EZE"}};

    tickets = {{"AUA","EZE"},{"JFK","AUA"},{"EZE","ANU"},{"AXA","JFK"},{"AUA","JFK"},{"ADL","TIA"},{"AUA","AXA"},{"ADL","AUA"},{"AUA","AXA"},{"AXA","TIA"},{"EZE","AXA"},{"AXA","AUA"},{"ANU","JFK"},{"ADL","EZE"},{"ADL","ANU"},{"EZE","ADL"},{"AXA","AUA"},{"JFK","EZE"},{"AUA","JFK"},{"AUA","JFK"},{"AXA","JFK"},{"ADL","EZE"},{"AUA","EZE"},{"AUA","JFK"},{"AUA","JFK"},{"JFK","AXA"},{"TIA","AXA"},{"JFK","ADL"},{"ADL","AXA"},{"AXA","AUA"},{"AUA","AXA"},{"JFK","AXA"},{"TIA","JFK"},{"ANU","AXA"},{"JFK","AXA"},{"EZE","AXA"},{"AXA","EZE"},{"JFK","ADL"},{"EZE","AXA"},{"ANU","AXA"},{"AXA","JFK"},{"JFK","AUA"},{"AXA","EZE"},{"ADL","AXA"},{"AUA","ADL"},{"AUA","ADL"},{"AXA","AUA"},{"ADL","ANU"},{"ANU","AUA"},{"ADL","ANU"},{"JFK","ADL"},{"TIA","AUA"},{"EZE","AXA"},{"ANU","TIA"},{"AXA","ADL"},{"JFK","ANU"},{"ADL","ANU"},{"TIA","AUA"},{"ADL","ANU"},{"AUA","EZE"},{"JFK","ANU"},{"AUA","ANU"},{"ADL","AUA"},{"JFK","ADL"},{"TIA","JFK"},{"AXA","ANU"},{"AXA","ANU"},{"JFK","AXA"},{"AXA","JFK"},{"ANU","AXA"},{"ADL","EZE"},{"JFK","ANU"},{"JFK","AUA"},{"AXA","ANU"},{"JFK","TIA"},{"ANU","AXA"},{"JFK","AUA"},{"AXA","AUA"},{"ADL","EZE"},{"ADL","AXA"},{"JFK","TIA"},{"EZE","AUA"},{"AUA","ADL"},{"JFK","ADL"},{"EZE","TIA"},{"TIA","AXA"},{"AUA","ADL"},{"JFK","AUA"},{"JFK","AUA"},{"AUA","ANU"},{"JFK","ADL"},{"AXA","AUA"},{"EZE","JFK"},{"ANU","ADL"},{"ADL","EZE"},{"ANU","JFK"},{"EZE","ANU"},{"AUA","ANU"},{"JFK","EZE"},{"EZE","JFK"},{"AXA","AUA"},{"ANU","AUA"},{"TIA","JFK"},{"ANU","AXA"},{"TIA","ANU"},{"AUA","ADL"},{"ANU","AXA"},{"AXA","ADL"},{"AUA","AXA"},{"ADL","ANU"},{"EZE","AXA"},{"EZE","ANU"},{"AXA","EZE"},{"AUA","ADL"},{"AUA","ADL"},{"TIA","JFK"},{"JFK","AUA"},{"ADL","AUA"},{"AXA","TIA"},{"AXA","TIA"},{"AXA","ANU"},{"AUA","ADL"},{"AUA","AXA"},{"ADL","AUA"},{"ANU","TIA"},{"AUA","AXA"},{"ANU","TIA"},{"AXA","AUA"},{"EZE","JFK"},{"ADL","AUA"},{"ADL","EZE"},{"AXA","JFK"},{"JFK","TIA"},{"AUA","AXA"},{"AUA","AXA"},{"JFK","TIA"},{"EZE","ADL"},{"AUA","ADL"},{"ANU","AXA"},{"EZE","ADL"},{"ADL","ANU"},{"TIA","EZE"},{"ANU","AUA"},{"AUA","HBA"},{"JFK","AUA"},{"TIA","AUA"},{"TIA","ADL"},{"AXA","ADL"},{"EZE","AUA"},{"EZE","JFK"},{"ANU","TIA"},{"ANU","JFK"},{"EZE","AUA"},{"EZE","AUA"},{"ADL","JFK"},{"ADL","AUA"},{"ADL","AXA"},{"AXA","JFK"},{"AXA","AUA"},{"ANU","AUA"},{"ANU","JFK"},{"TIA","EZE"},{"ANU","AUA"},{"ADL","JFK"},{"JFK","ANU"},{"ADL","JFK"},{"ANU","AUA"},{"JFK","ADL"},{"AXA","ANU"},{"AXA","JFK"},{"JFK","ADL"},{"EZE","JFK"},{"TIA","AUA"},{"ANU","ADL"},{"AUA","AXA"},{"ADL","AXA"},{"AUA","JFK"},{"ADL","AXA"},{"EZE","ANU"},{"TIA","EZE"},{"EZE","JFK"},{"ADL","EZE"},{"ANU","JFK"},{"AUA","JFK"},{"ANU","JFK"},{"EZE","ADL"},{"AUA","ADL"},{"EZE","ANU"},{"AXA","EZE"},{"AXA","ADL"},{"JFK","TIA"},{"AUA","ADL"},{"EZE","TIA"},{"AXA","EZE"},{"EZE","AUA"},{"JFK","TIA"},{"AUA","AXA"},{"TIA","ANU"},{"AXA","JFK"},{"TIA","EZE"},{"EZE","ANU"},{"ANU","EZE"},{"JFK","TIA"},{"JFK","EZE"},{"TIA","AXA"},{"ANU","EZE"},{"AUA","TIA"},{"AXA","EZE"},{"ANU","AUA"},{"AUA","EZE"},{"AUA","EZE"},{"ADL","ANU"},{"AUA","AXA"},{"AXA","ADL"},{"JFK","EZE"}};

    vector<string> ret = findItinerary(tickets);
    for (auto x: ret) {
        cout << x << " ";
    }
    cout << endl;
    cout << tickets.size() << "," << ret.size() << endl;
    return 0;
}
