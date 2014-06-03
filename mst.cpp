#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

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

int state_position_at(int state, vector< vector<int> > states)
{
    for(int i = 0; i < states.size(); ++i)
        if(states[i][0] == state)
            return i;

    return -1;
}

void update_open_state( vector< vector<int> > &open_state,
                        vector< vector<int> > closed_state,
                        vector< vector<int> > matrix_data)
{
    int current_state = closed_state[closed_state.size() - 1][0];

    for(int i = 0; i < matrix_data[current_state].size(); ++i)
    {
        int state_position_index = state_position_at(i, closed_state);
        if(state_position_index != -1 || matrix_data[current_state][i] < 1)
            continue;

        int data[] = {i,matrix_data[current_state][i]};
        vector<int> temp(data, data + sizeof(data) / sizeof(int));
        open_state.push_back(temp);
    }
}

vector<int> pick_least(vector< vector<int> > open_state, vector< vector<int> > closed)
{
    vector<int> next_state;
    int least_index;

    for(int i = 1; i < open_state.size(); ++i)
    {
        int pos = state_position_at(open_state[i][0], closed);
        if(pos == -1)
            if(next_state.empty() || next_state[1] > open_state[i][1])
            {
                next_state = open_state[i];
                least_index = i;
            }
    }


    if(least_index != -1)
    {
        next_state = open_state[least_index];
        open_state.erase(open_state.begin()+least_index);
    }

    return next_state;
}

vector<int> minimum_spanning_tree(vector< vector<int> > graph, int &length)
{
    vector<int> mst;
    vector< vector<int> > open, closed;

    if(!graph.empty())
    {
        int data[2] = {0,0};
        vector<int> temp(data, data + sizeof(data) / sizeof(int));
        closed.push_back(temp);

        while(closed.size() != graph.size())
        {
            // updating the open state
            update_open_state(open, closed, graph);

            // picking the least cost state
            if(open.empty())
                break;

            temp = pick_least(open, closed);
            length = temp[1] = temp[1] + closed[closed.size() - 1][1];
            closed.push_back(temp);
        }
    }

    for(auto elem: closed)
        mst.push_back(elem[0]);

    return mst;
}

int main()
{
    int length;
    srand(time(0));
    vector< vector<int> > undirected_graph = generate_graph(5);
    vector<int> mst = minimum_spanning_tree(undirected_graph, length);

    cout << "Matrix of undirected graph" << endl;
    for(auto i: undirected_graph)
    {
        for(auto j: i)
            cout << j << " ";
        cout << "\n";
    }

    cout << "MST starting from 0 is ";

    for(auto elem: mst)
        cout << elem << " ";
    cout << " with length " << length;

    return 0;
}
