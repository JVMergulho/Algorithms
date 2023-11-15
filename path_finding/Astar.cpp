#include <bits/stdc++.h> // Inclui STL
using namespace std;

typedef pair<double, int> Pair;

void print_vector(vector<int> V)
{
    for (int i : V)
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
    for (unsigned int i = 0; i < path.size(); i++)
    {
        if (i != path.size() - 1)
            cout << "E" << path[i] + 1 << " -> ";
        else
            cout << "E" << path[i] + 1 << "\n";
    }
}

// Heurística
// H[i][j] = distância em linha reta de i a j
vector<vector<double>> H = {
    {0, 10, 18.5, 24.8, 36.4, 38.8, 35.8, 25.4, 17.6, 9.1, 16.7, 27.3, 27.6, 29.8},
    {10, 0, 8.5, 14.8, 26.6, 29.1, 26.1, 17.3, 10, 3.5, 15.5, 20.9, 19.1, 21.8},
    {18.5, 8.5, 0, 6.3, 18.2, 20.6, 17.6, 13.6, 9.4, 10.3, 19.5, 19.1, 12.1, 16.6},
    {24.8, 14.8, 6.3, 0, 12, 14.4, 11.5, 12.4, 12.6, 16.7, 23.6, 18.6, 10.6, 15.4},
    {36.4, 26.6, 18.2, 12, 0, 3, 2.4, 19.4, 23.3, 28.2, 34.2, 24.8, 14.5, 17.9},
    {38.8, 29.1, 20.6, 14.4, 3, 0, 3.3, 22.3, 25.7, 30.3, 36.7, 27.6, 15.2, 18.2},
    {35.8, 26.1, 17.6, 11.5, 2.4, 3.3, 0, 20, 23, 27.3, 34.2, 25.7, 12.4, 15.6},
    {25.4, 17.3, 13.6, 12.4, 19.4, 22.3, 20, 8.2, 20.3, 16.1, 6.4, 22.7, 27.6, 0},
    {17.6, 10, 9.4, 12.6, 23.3, 25.7, 23, 20.3, 8.2, 13.5, 11.2, 10.9, 21.2, 26.6},
    {9.1, 3.5, 10.3, 16.7, 28.2, 30.3, 27.3, 16.1, 13.5, 0, 17.6, 24.2, 18.7, 21.2},
    {16.7, 15.5, 19.5, 23.6, 34.2, 36.7, 34.2, 6.4, 11.2, 17.6, 0, 28.8, 33.6, 0},
    {27.3, 20.9, 19.1, 18.6, 24.8, 27.6, 25.7, 22.7, 10.9, 24.2, 28.8, 0, 5.1, 0},
    {27.6, 19.1, 12.1, 10.6, 14.5, 15.2, 12.4, 27.6, 21.2, 18.7, 33.6, 5.1, 0, 0},
    {29.8, 21.8, 16.6, 15.4, 17.9, 18.2, 15.6, 0, 26.6, 21.2, 0, 0, 0, 0},
};

class Node
{
public:
    Node(int idx, double value, double cost, Node *parent, bool visited)
    {
        this->idx = idx;
        this->value = value;
        this->cost = cost;
        this->parent = parent;
        this->visited = visited;
    }

    int idx;
    double value, cost;
    Node *parent;
    bool visited;
};

void Astar(vector<vector<Pair>> adj, int S, int T)
{
    int V = adj.size();

    priority_queue<Pair, vector<Pair>, greater<Pair>> frontier;
    vector<int> parent(V, -1);
    vector<double> cost(V, FLT_MAX);  // g
    vector<double> value(V, FLT_MAX); // f
    vector<bool> visited(V, false);
    int currNode, nodeIdx;
    double currCost, nodeCost, newCost, newValue;
    bool found;

    cost[S] = 0;
    value[S] = H[S][T];
    frontier.push({0, S});

    while (!frontier.empty()) // pair {f, idx}
    {
        currNode = frontier.top().second;
        currCost = cost[currNode];
        frontier.pop();

        if (currNode == T)
        {
            found = true;
            break;
        }

        if (!visited[currNode])
        {
            cout << "CurrNode = " << currNode << "\n";
            visited[currNode] = true;

            for (Pair node : adj[currNode])
            {
                nodeCost = node.first;
                nodeIdx = node.second;

                newCost = currCost + nodeCost;
                newValue = newCost + H[nodeIdx][T]; // f = g + h

                if ((value[nodeIdx] > newValue))
                {
                    cost[node.second] = newCost;
                    value[nodeIdx] = newValue;
                    frontier.push({value[nodeIdx], nodeIdx});
                    parent[nodeIdx] = currNode;
                }
            }
        }
    }

    if (found)
    {
        cout << "CurrNode = " << currNode << "\n";
        cout << "Path found! \n";
        cout << "Custo total = " << cost[T] << "\n ";
        // print_vector(parent);
        print_path(parent, T);
    }
    else
        cout << "It was not possible to find a path between " << S << " and " << T;
}

int main()
{
    // pair {custo, nodeIndex}
    vector<vector<Pair>> adj = {{{10, 1}},                                  // 0 -> E1
                                {{10, 0}, {8.5, 2}, {10, 8}, {3.5, 9}},     // 1 -> E2
                                {{8.5, 1}, {6.3, 3}, {9.4, 8}, {18.7, 12}}, // 2 -> E3
                                {{13, 4}, {15.3, 7}, {12.8, 12}, {11, 13}}, // 3 -> E4
                                {{3, 5}, {2.4, 6}, {30, 7}},                // 4 -> E5
                                {{3, 4}},                                   // 5 -> E6
                                {{2.4, 4}},                                 // 6 -> E7
                                {{15.3, 3}, {30, 4}, {9.6, 8}, {6.4, 11}},  // 7 -> E8
                                {{10, 1}, {9.4, 2}, {9.6, 7}, {12.2, 10}},  // 8 -> E9
                                {{3.5, 1}},                                 // 9 -> E10
                                {{12.2, 8}},                                // 10 -> E11
                                {{6.4, 7}},                                 // 11 -> E12
                                {{18.7, 2}, {12.8, 3}, {5.1, 13}},          // 12 -> E13
                                {{5.1, 12}, {11, 3}}};                      // tá estranho       // 13 -> E14

    int S, T;

    cout << "Estacao de partida: ";
    cin >> S;
    cout << "\nEstacao de chegada: ";
    cin >> T;

    Astar(adj, S, T);

    return 0;
}