#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

int state_position_at(int state, vector< vector<int> > states)
{
    for(int i = 0; i < states.size(); ++i)
        if(states[i][0] == state)
            return i;

    return -1;
}

void update_open_state(vector< vector<int> > &open_state,
                                        vector< vector<int> > closed_state,
                                        vector< vector<int> > matrix_data)
{
    int current_state = closed_state[closed_state.size() - 1][0];
    int current_length = closed_state[closed_state.size() - 1][1];

    for(int i = 0; i < matrix_data[current_state].size(); ++i)
    {
        int state_position_index = state_position_at(i, closed_state);
        if(state_position_index != -1 || matrix_data[current_state][i] < 1)
            continue;

        state_position_index = state_position_at(i, open_state);

        if(state_position_index != -1)
        {
            if(open_state[state_position_index][2] > current_length + matrix_data[current_state][i])
            {
                if(open_state[state_position_index][3] == 1)
                {
                    open_state[state_position_index][0] = i;
                    open_state[state_position_index][1] = current_state;
                    open_state[state_position_index][2] = current_length + matrix_data[current_state][i];
                }
            }
        }
        else
        {
            vector<int> temp;
            temp.push_back(i);
            temp.push_back(current_state);
            temp.push_back(current_length + matrix_data[current_state][i]);
            temp.push_back(1);
            open_state.push_back(temp);
        }
    }
}

vector<int> pick_least(vector< vector<int> > &open_state)
{
    vector<int> next_state;
    int least_index = -1, least_value;

    for(int i = 0; i < open_state.size(); ++i)
        if(least_index == -1 && open_state[i][3] == 1)
        {
            least_index = i;
            least_value = open_state[i][2];
        }
        else if(least_value > open_state[i][2] && open_state[i][3] == 1)
        {
            least_index = i;
            least_value = open_state[i][2];
        }

    if(least_index != -1)
    {
        next_state = open_state[least_index];
        open_state[least_index][3] = 0;
    }

    return next_state;
}

vector<int> construct_shortest_path(int src, int dest, vector< vector<int> > open_state)
{
    vector<int> shortest_path;

    while(dest != src)
    {
        int index = state_position_at(dest, open_state);

        shortest_path.insert(shortest_path.begin(), dest);
        dest = open_state[index][1];
    }

    shortest_path.insert(shortest_path.begin(), dest);

    return shortest_path;
}
// open set is what is reachable from the current node
// closed set is nodes which has been selected
vector<int> dijkstra_shortest_path(int src, int dest, vector< vector <int> > matrix_data)
{
    vector<int> shortest_path, next_state;
    // closed state store the shortest path from source to any state with the distance info
    vector< vector<int> > closed_state, open_state;

    vector<int> temp;
    temp.push_back(src);
    temp.push_back(0);
    closed_state.push_back(temp);

    while(closed_state[closed_state.size() - 1][0] != dest)
    {
        // updating the open state
        update_open_state(open_state, closed_state, matrix_data);

        // picking the least cost state
        if(open_state.empty())
            break;

        next_state = pick_least(open_state);
        temp[0] = next_state[0];
        temp[1] = next_state[2];
        closed_state.push_back(temp);
    }

    if(!next_state.empty() && next_state[0] == dest)
        shortest_path = construct_shortest_path(src, dest, open_state);

    return shortest_path;
}

bool is_connected(int src, int dest, vector< vector<int> > matrix_data)
{
    bool is_it_really_connected = false;
    vector<int> shortest_path = dijkstra_shortest_path(src, dest, matrix_data);

    if(!shortest_path.empty())
        is_it_really_connected = true;

    return is_it_really_connected;
}

vector< vector<int> > generate_graph(int size)
{
    vector<int> row_data(size,0);
    vector< vector <int> > undirected_graph(size, row_data);

    for(int i = 0; i < size; i++)
        for(int j = 0; j < i; j++)
            // you can call rand  after that
            undirected_graph[i][j] = undirected_graph[j][i] = (rand()%100) / 10;

    return undirected_graph;
}

int main(int argc, char** argv)
{
    int src, dest, size;

    srand(time(0)); // call srand once and only once when your program starts
    // to avoid getting the same value

    if(argc == 3)
    {
        stringstream(argv[1]) >> src;
        stringstream(argv[2]) >> dest;
        stringstream(argv[3]) >> size;
        vector< vector<int> > undirected_graph = generate_graph(size);

        vector<int> shortest_path;

        cout << "Matrix of undirected graph" << endl;
        for(int i = 0; i < undirected_graph.size(); ++i)
        {
            for(int j = 0; j < undirected_graph[i].size(); ++j)
                cout << undirected_graph[i][j] << " ";
            cout << "\n";
        }

        shortest_path = dijkstra_shortest_path(src, dest, undirected_graph);

        cout << "The shortest path from " << src << " to " << dest << " is " << endl;

        if(!shortest_path.empty())
            for(int i = 0; i < shortest_path.size(); ++i)
                if(i == shortest_path.size() - 1)
                    cout << shortest_path[i];
                else
                    cout << shortest_path[i] << " -> ";
        else
            cout << "not possible to be found.";
        cout << endl;

        if(is_connected(src, dest, undirected_graph))
            cout << "It is really true that " << src << " and " << dest << " is really connected";
    }
    else
        cout << "Please give the source and the destination state and the size of the graph" << endl;

    return 0;
}

// Primal MST algorithm select the least cost in the open sets based on nodes
// Kruskal MST algorithm select the next the least edges (based on nodes)
// in Kruskal, you sort the edges before you select, whereas in Primal you select the node
// with least cost.
