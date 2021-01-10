#include <iostream>
#include <list>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>


template<typename T>
class Graph;

template <typename T>
class Node {
private:
    friend class Graph<T>;

    T key;
    std::unordered_map<T, Node<T>*> edges;

    Node(const T& key):
        key(key), edges() {}

    void addEdge(Node<T> *node) {
        edges[node->key] = node;
    }
};

template <typename T>
class Graph {
private:
    std::unordered_map<T, Node<T>*> nodes;

public:
    Graph() : nodes() {}

    void addNode(const T& key) {
        if(nodes.find(key) == nodes.end()) {
            nodes[key] = new Node(key);
        }
    }

    void addEdge(const T&u, const T&v) {
        addNode(u);
        addNode(v);
        nodes[u]->addEdge(nodes[v]);
        nodes[v]->addEdge(nodes[u]);
    }

    bool isBipartite() const {
        std::unordered_map<T, int> colours;
        for(auto const& [keyNode, node] : nodes) {
            if (colours.find(node->key) == colours.end()) {
                colours[node->key] = 0;
                std::queue<Node<T>*> toVisit;
                toVisit.push(node);
                while(!toVisit.empty()) {
                    auto front = toVisit.front();
                    toVisit.pop();
                    auto colour = colours[front->key];
                    for(auto const& [keyAdj, adj] : front->edges) {
                        if(colours.find(adj->key) != colours.end()) {
                            if(colour == colours[adj->key]) {
                                return false;
                            }
                        } else {
                            colours[adj->key] = !colour;
                            toVisit.push(adj);
                        }
                    }
                }
            }
        }
        return true;
    }

    bool connected() const {
        if(nodes.empty()) {
            return true;
        }

        std::stack<Node<T>*> st;
        std::unordered_set<T> visited;

        auto node = nodes.begin()->second;
        visited.insert(node->key);
        st.push(node);

        while(!st.empty()) {
            Node<T>* current = st.top();
            st.pop();
            for(auto const& [key, adjacent] : current->edges) {
                if(visited.find(key) == visited.end()) {
                    visited.insert(key);
                    st.push(adjacent);
                }
            }
        }
        return visited.size() == nodes.size();
    }

    std::list<T> findShortestPath(const T& u, const T& v) const {
        std::queue<Node<T>*> q;
        std::unordered_map<T,T> parents;

        auto node = nodes.at(u); // bounds checking
        parents[node->key] = node->key;
        q.push(node);

        while(!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            if(current->key == v) {
                // found it: build path by following the parent links from v to u.
                std::list<T> path;
                for(auto key = v; key != u; key = parents[key]) {
                    path.push_front(key);
                }
                path.push_front(u);
                return path;
            }

            for(auto const& [adjKey, adjacent] : current->edges) {
                if(parents.find(adjKey) == parents.end()) {
                    parents[adjKey] = current->key;
                    q.push(adjacent);
                }
            }
        }

        return std::list<T>();
    }
};

/*
We'll use the following graphs

G1 (connected):
    1 - 2 - 3
     \     /
      - 4 -

G2 (not-connected):
    1 - 2 - 3

        4

G3 (shortest-path):
      3 - 4
     /     \
1 - 2       6
     \     /
      --5--

*/
int main() {
    using namespace std;

    Graph<int> g1;
    g1.addEdge(1, 2);
    g1.addEdge(1, 4);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    cout << g1.isBipartite() << endl;

    Graph<int> g2;
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addNode(4);
    cout << g2.isBipartite() << endl;

    Graph<int> g3;
    g3.addEdge(1, 2);
    g3.addEdge(2, 3);
    g3.addEdge(2, 5);
    g3.addEdge(3, 4);
    g3.addEdge(4, 6);
    g3.addEdge(5, 6);
    cout << g3.isBipartite() << endl;
}
