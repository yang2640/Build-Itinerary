#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
        return x->val <= y->val;
    }
} comp;

bool dfs(vector<string> &res, vector<string> &cur, GraphNode *x,
        unordered_set<string> &visit, int edgeSize) {

    if (x == nullptr) {
        return false;
    }
    // all the edges visited, return true
    if (visit.size() >= edgeSize) {
        cur.push_back(x->val);
        res.assign(cur.begin(), cur.end());
        cur.pop_back();
        return true;
    }

    cur.push_back(x->val);
    // sort the edges by order
    sort(x->neibors.begin(), x->neibors.end(), comp);
    for (auto to: x->neibors) {
        string edgeStr = x->val + to->val;
        // do not search visited edge
        if (visit.find(edgeStr) != visit.end()) {
            continue;
        }

        visit.insert(edgeStr);
        if (dfs(res, cur, to, visit, edgeSize)) {
            return true;
        }
        visit.erase(edgeStr);
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
    }

    // start visit from "JFK"
    vector<string> res;
    vector<string> cur;
    unordered_set<string> visit;

    dfs(res, cur, nodeMap["JFK"], visit, tickets.size());
    return res;
}


int main() {
    vector<pair<string, string>> tickets = {{"MUC", "LHR"}, {"JFK", "MUC"}, 
        {"SFO", "SJC"}, {"LHR", "SFO"}};

    tickets = {{"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"}};
    vector<string> ret = findItinerary(tickets);
    for (auto x: ret) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
