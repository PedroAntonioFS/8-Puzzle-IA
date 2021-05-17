#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

enum Moves
{
    Left = 0,
    Right = 1, 
    Top = 2,
    Down = 3
};

pii finalPosition[] = {{2, 2}, {0, 0}, {0, 1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}};

int manhattanDistance(int grid[3][3])
{
    int cost = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cost += abs(i - finalPosition[grid[i][j]].first) + abs(j - finalPosition[grid[i][j]].second);
        }
    }

    return cost;
}

class State
{
public:
    string key;
    int grid[3][3];
    pii zeroPosition;
    vector<Moves> path;
    int cost;
    int depth;

    State(int initialState[3][3], vector<Moves> currentPath)
    {
        path = currentPath;
        init(initialState);
    }

    State(int initialState[3][3])
    {
        init(initialState);
    }

    State ()
    {
        int current[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
        init(current);
    }


    bool isFinalState()
    {
        return key == "123456780";
    }

    bool operator < (const State &another) const
    {
        return cost > another.cost;
    }

private:
    void init(const int initialState[3][3])
    {
        for (int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {
                grid[i][j] = initialState[i][j];

                key += '0' + grid[i][j];

                if (!grid[i][j])
                {
                    zeroPosition = pii(i, j);
                }
            }
    }
};

class DataStructure
{
public:
    virtual void add(State state) {}
    virtual State extract() {}
    virtual int size () {}
    virtual bool isEmpty() {}
    virtual int cost(State state) {}
};

class ASTAR : public DataStructure
{
public:
    priority_queue<State> ds;

    void add(State state) 
    {
        ds.push(state);
    }
    
    State extract()
    {
        auto head = ds.top();
        ds.pop();
        return head;
    }

    int size ()
    {
        return ds.size();
    }

    bool isEmpty()
    {
        return ds.empty();
    }

    int cost(State state)
    {
        return manhattanDistance(state.grid) + state.depth;
    }
};

class Greedy : public DataStructure
{
public:
    priority_queue<State> ds;

    void add(State state) 
    {
        ds.push(state);
    }
    
    State extract()
    {
        auto head = ds.top();
        ds.pop();
        return head;
    }

    int size ()
    {
        return ds.size();
    }

    bool isEmpty()
    {
        return ds.empty();
    }

    int cost(State state)
    {
        return manhattanDistance(state.grid);
    }
};

class BFS : public DataStructure
{
public:
    queue<State> ds;

    void add(State state) 
    {
        ds.push(state);
    }
    
    State extract()
    {
        auto head = ds.front();
        ds.pop();
        return head;
    }

    int size ()
    {
        return ds.size();
    }

    bool isEmpty()
    {
        return ds.empty();
    }

    int cost(State state)
    {
        return state.depth;
    }
};