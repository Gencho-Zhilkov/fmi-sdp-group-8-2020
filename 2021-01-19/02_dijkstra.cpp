#include <unordered_set>
#include <unordered_map>
#include <stdexcept>
#include <iostream>


template<typename T, typename W>
class Graph;

template <typename T, typename W>
class Node {
private:
    friend class Graph<T, W>;

    T key;
    std::unordered_map<T, std::pair<T, W>> edges;

    Node(const T& key):
        key(key), edges() {}

    void addEdge(Node<T, W> *node, const W& w) {
        edges[node->key] = { node->key, w };
    }
};

template <typename T, typename W=unsigned>
class Graph {
private:
    std::unordered_map<T, Node<T, W>*> nodes;

public:
    Graph() : nodes() {}

    void addNode(const T& key) {
        if (nodes.find(key) == nodes.end()) {
            nodes[key] = new Node<T, W>(key);
        }
    }

    void addEdge(const T&u, const T&v, const W& w) {
        addNode(u);
        addNode(v);
        nodes[u]->addEdge(nodes[v], w);
        nodes[v]->addEdge(nodes[u], w);
    }

    /*
    Dijkstra's algorithm for shortest path between two nodes in a weighted graph
    with **positive** weights.

    cf. https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    */
    W dijkstraShortestPath(const T& a, const T& b) const {
        std::unordered_map<T, W> shortestFound;
        shortestFound[a] = 0;

        std::unordered_set<T> visited, frontier;
        frontier.insert(a);

        while(!frontier.empty()) {
            // Намираме най-близкия нод от "фронта".
            auto it = frontier.begin();
            auto minDistance = shortestFound[*it];
            auto minIt = it;
            for(;it != frontier.end(); ++it) {
                auto d = shortestFound[*it];
                if (d < minDistance) {
                    minDistance = d;
                    minIt = it;
                }
            }

            // std::cout << "Closest is: " << *minIt << ", distance=" << minDistance << std::endl;

            // ако той сочи към b, значи сме намерили най-краткия път
            if (*minIt == b) {
                return minDistance;
            }

            // премахваме го, отбелязаме като посетен
            auto current = nodes.at(*minIt);
            frontier.erase(minIt);
            visited.insert(*minIt);

            // обхождаме съседите му, и ги добавяме във фронта
            for(auto const& [key, edge]: current->edges) {
                if (visited.find(key) != visited.end()) {
                    continue;
                }

                auto d = minDistance + edge.second;
                auto it = shortestFound.find(key);
                if (it != shortestFound.end()) {
                    it->second = std::min(it->second, d);
                } else {
                    shortestFound[key] = d;
                    frontier.insert(key);
                }
            }
        }

        throw std::domain_error("No path from source to destination!");
    }
};

int main() {
    using namespace std;

    Graph<int> g;
    g.addEdge(1, 2, 7);
    g.addEdge(1, 3, 9);
    g.addEdge(1, 4, 14);
    g.addEdge(2, 3, 10);
    g.addEdge(2, 4, 15);
    g.addEdge(3, 4, 11);
    g.addEdge(3, 6, 2);
    g.addEdge(4, 5, 6);
    g.addEdge(5, 6, 9);

    cout << g.dijkstraShortestPath(1, 5) << endl;
}
