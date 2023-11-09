#include <bits/stdc++.h>
using namespace std;

struct Solution
{
    Solution(vector<double> dist, vector<int> parent)
    {
        this->dist = dist;
        this->parent = parent;
    }
    vector<double> dist;
    vector<int> parent;
};

void print_vector(vector<double> V)
{
    for (double i : V)
        cout << i << " ";
}

void print_path(vector<int> parent, int target)
{
    int curr = target;
    vector<int> path;

    while (curr != -1)
    {
        path.push_back(curr);
        curr = parent[curr];
    }

    reverse(path.begin(), path.end());

    cout << "\nShortest path: ";
    for (int i = 0; i < path.size(); i++)
    {
        if (i != path.size() - 1)
            cout << path[i] << " -> ";
        else
            cout << path[i] << "\n";
    }
}

void print_adj_list(vector<vector<pair<double, int>>> adj)
{

    for (int i = 0; i < adj.size(); i++)
    {
        cout << "Adjacency list for vertex " << i << ": ";
        for (pair<int, int> v : adj[i])
        {
            cout << "(" << v.first << ", " << v.second << ") ";
        }
        cout << endl;
    }
}

/// @brief dijkstra algorithm calculates the shortest paths in a graph
/// @param adj graph adjency list
/// @param S source node
/// @return solution -> distance vector from S to every other node and parent vector
Solution dijkstra(vector<vector<pair<double, int>>> adj, int S)
{

    int V = adj.size();
    priority_queue<pair<int, int>> pq; // O(log(n))
    vector<double> dist(V, FLT_MAX);   // [INT_MAX, INT_MAX, INT_MAX, ...]
    vector<int> parent(V, -1);         // [-1, -1, -1, ...]
    vector<bool> visited(V, false);    // [f, f, f, ...]
    // if  visited[e] == true it means the shortest path to e was already calculated

    int currNode;
    double currDist;

    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty())
    {
        currDist = pq.top().first;
        currNode = pq.top().second;
        pq.pop();

        if (!visited[currNode])
        {
            visited[currNode] = true;

            for (pair<double, int> node : adj[currNode])
            {
                if ((dist[node.second] > currDist + node.first))
                {
                    dist[node.second] = currDist + node.first;
                    pq.push({dist[node.second], node.second});
                    parent[node.second] = currNode;
                }
            }
        }
    }

    return Solution(dist, parent);
}

int main()
{
    // pair {weight, nodeIndex}
    vector<vector<pair<double, int>>> adj = {{{10, 1}},
                                             {{10, 0}, {8.5, 2}, {10, 8}, {3.5, 9}},
                                             {{8.5, 1}, {6.3, 3}, {9.4, 8}, {18.7, 12}},
                                             {{13, 4}, {15.3, 7}, {12.8, 12}, {11, 13}},
                                             {{3, 5}, {2.4, 6}, {30, 7}},
                                             {{3, 4}},
                                             {{2.4, 4}},
                                             {{15.3, 3}, {30, 4}, {9.6, 8}, {6.4, 12}},
                                             {{10, 1}, {9.4, 2}, {9.6, 7}, {12.2, 10}},
                                             {{3.5, 1}},
                                             {{12.2, 8}},
                                             {{6.4, 7}},
                                             {{18.7, 2}, {12.8, 3}, {5.1, 13}},
                                             {{5.1, 12}, {11, 3}}}; // tá estranho

    print_adj_list(adj);

    Solution solution = dijkstra(adj, 0);

    cout << "\nDistance vector: ";
    print_vector(solution.dist);

    cout << "\nPath from 0 to 4: ";
    print_path(solution.parent, 4);

    return 0;
}