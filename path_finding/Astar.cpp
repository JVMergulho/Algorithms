#include <bits/stdc++.h> // Inclui STL
using namespace std;

typedef tuple <double, int, string> Triple;
typedef pair<string, string> Pairss;
typedef pair<double, Pairss> Pairdss;

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
    {25.4, 17.3, 13.6, 12.4, 19.4, 22.3, 20, 0, 8.2, 20.3, 16.1, 6.4, 22.7, 27.6},
    {17.6, 10, 9.4, 12.6, 23.3, 25.7, 23, 8.2, 0, 13.5, 11.2, 10.9, 21.2, 26.6},
    {9.1, 3.5, 10.3, 16.7, 28.2, 30.3, 27.3, 20.3, 13.5, 0, 17.6, 24.2, 18.7, 21.2},
    {16.7, 15.5, 19.5, 23.6, 34.2, 36.7, 34.2, 16.1, 11.2, 17.6, 0, 14.2, 31.5, 35.5},
    {27.3, 20.9, 19.1, 18.6, 24.8, 27.6, 25.7, 6.4, 10.9, 24.2, 14.2, 0, 28.8, 33.6},
    {27.6, 19.1, 12.1, 10.6, 14.5, 15.2, 12.4, 22.7, 21.2, 18.7, 31.5, 28.8, 0, 5.1},
    {29.8, 21.8, 16.6, 15.4, 17.9, 18.2, 15.6, 27.6, 26.6, 21.2, 35.5, 33.6, 5.1, 0}
    };

double calculateH(string sta1, string sta2)
{
    int i = int(sta1[1]) - 1;
    int j = int(sta2[1]) - 1;

    return H[i][j];
}

class Node
{
public:
    Pairss state;
    double value = FLT_MAX, cost = FLT_MAX;
    Node *parent = NULL;
    bool visited = false;
};

void Astar(map<Pairss, vector<pair<double, Pairss>>> adj, Pairss start, string target)
{
    int V = adj.size();

    priority_queue<Pairdss, vector<Pairdss>, greater<Pairdss>> frontier;
    bool found;

    map<Pairss, Node> nodes;
    nodes[start] = Node();
    nodes[start].value = calculateH(start.first);

    frontier.push({0, start});

    while (!frontier.empty()) // pair {f , state}
    {
        CurrState = frontier.top().second; // pair { station, color}
        currCost = nodes[CurrState].cost;
        frontier.pop();

        if (CurrState.first == target)
        {
            found = true;
            break;
        }

        if (!CurrState.visited)
        {
            cout << "CurrState = E" << CurrState << "\n";
            nodes[CurrState].visited = true;

            for (Pairdss node : adj[CurrState])
            {
                nodeCost = node.first;
                state = node.second;

                newCost = currCost + nodeCost;
                newValue = newCost + calculateH(state.first, target); // f = g + h

                if ((nodes[state].value > newValue))
                {
                    nodes[state].cost = newCost;
                    nodes[state].value = newValue;
                    frontier.push({newValue, state});
                    nodes[state].parent = CurrState;
                }
            }
        }
    }

    if (found)
    {
        // cout << "CurrNode = E" << currNode + 1 << "\n";
        cout << "Path found! \n";
        // cout << "Distancia percorrida = " << cost[T] << " km\n";
        // cout << "Tempo do trajeto = " << cost[T] * 2.0 << " min\n "; // 30 km/h = 1/2 km/min
        // print_path(parent, T);
    }
    else
        cout << "It was not possible to find a path between " << S << " and " << T;
}

int main()
{
    // Triple {custo, nodeIndex, line color}
    // vector<vector<Triple>> adj = {{{10, 1, "blue"}},                                                                // 0 -> E1
    //                             {{10, 0, "blue"}, {8.5, 2, "blue"}, {10, 8, "yellow"}, {3.5, 9, "yellow"}},         // 1 -> E2
    //                             {{8.5, 1, "blue"}, {6.3, 3, "blue"}, {9.4, 8, "red"}, {18.7, 12, "red"}},           // 2 -> E3
    //                             {{13, 4, "blue"}, {15.3, 7, "green"}, {12.8, 12, "green"}},                         // 3 -> E4
    //                             {{3, 5, "blue"}, {2.4, 6, "yellow"}, {30, 7, "yellow"}},                            // 4 -> E5
    //                             {{3, 4, "blue"}},                                                                   // 5 -> E6
    //                             {{2.4, 4, "yellow"}},                                                               // 6 -> E7
    //                             {{15.3, 3, "green"}, {30, 4, "yellow"}, {9.6, 8, "yellow"}, {6.4, 11, "green"}},    // 7 -> E8
    //                             {{10, 1, "yellow"}, {9.4, 2, "red"}, {9.6, 7, "yellow"}, {12.2, 10, "red"}},        // 8 -> E9
    //                             {{3.5, 1, "yellow"}},                                                               // 9 -> E10
    //                             {{12.2, 8, "red"}},                                                                 // 10 -> E11
    //                             {{6.4, 7, "green"}},                                                                // 11 -> E12
    //                             {{18.7, 2, "red"}, {12.8, 3, "green"}, {5.1, 13, "green"}},                         // 12 -> E13
    //                             {{5.1, 12, "green"}}};      // 13 -> E14
                                
    map<Pairss, vector<Pairdss>> adj = {{"E1", "blue"}   : { {10, {"E2", "blue"}} },
                                        {"E2","blue"}    : {  {4, {"E2", "yellow"}}, {10, {"E1", "blue"}}, {8.5, {"E3", "blue"}} },
                                        {"E2","yellow"}  : { {4, {"E2", "blue"}}, {10, {"E9", "yellow"}}, {3.5, {"E10", "yellow"}} },
                                        {"E3","blue"}    : { {4, {"E3", "red"}}, {8.5, {"E2", "blue"}},  {6.3, {"E4", "blue"}} },
                                        {"E3","red"}     : { {4, {"E3", "blue"}}, {8.5, {"E9", "red"}},  {18.7, {"E13", "red"}} },
                                        {"E4","blue"}    : { {4, {"E4", "green"}}, {6.3, {"E3", "blue"}},  {13, {"E5", "blue"}} },
                                        {"E4","green"}   : { {4, {"E4", "blue"}}, {15.3,{"E8", "green"}}, {12.8,{"E13", "green"}} },
                                        {"E5","blue"}    : { {4, {"E5", "yellow"}}, {13,{"E4", "blue"}}, {3,{"E6", "blue"}} },
                                        {"E5","yellow"}  : { {4, {"E5", "blue"}}, {2.4,{"E7", "yellow"}}, {30,{"E8", "yellow"}} },
                                        {"E6","blue"}    : { {3,{"E5", "blue"}} },
                                        {"E7", "yellow"} : { {2.4,{"E5", "yellow"}} },
                                        {"E8","yellow"}  : { {4, {"E8", "green"}}, {30,{"E5", "yellow"}}, {9.6,{"E9", "yellow"}} },
                                        {"E8","green"}   : { {4, {"E8", "yellow"}}, {15.3,{"E4", "green"}}, {6.4,{"E12", "green"}} },
                                        {"E9","yellow"}  : { {4, {"E9", "red"}}, {10,{"E2", "yellow"}}, {9.6,{"E8", "yellow"}} },
                                        {"E9","red"}     : { {4, {"E9", "yellow"}}, {9.4,{"E3", "red"}}, {12.2,{"E11", "red"}} },
                                        {"E10","yellow"} : { {3.5,{"E2", "yellow"}} },
                                        {"E11","red"}    : { {12.2,{"E9", "red"}} },
                                        {"E12","green"}  : { {6.4,{"E8", "green"}} },
                                        {"E13","green"}  : { {4, {"E13", "red"}}, {12.8,{"E4", "green"}}, {5.1,{"E14", "green"}} },
                                        {"E13","red"}    : { {4, {"E13", "green"}}, {18.7,{"E3", "red"}} },
                                        {"E14","green"}  : { {5.1,{"E13", "green"}} },};                                                     

    string station, color, target;

    cout << "Estacao de partida: ";
    cin >> station;
    cout << "Cor da linha inicial: ";
    cin >> color;
    cout << "Estacao de chegada: ";
    cin >> target;

    Astar(adj, {station, color} , target);

    return 0;
}
