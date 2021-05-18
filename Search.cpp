#include <bits/stdc++.h>
#include "DataStructure.h"
#define pii pair<int, int>
#define LIMIT_DEPTH  500
#define ll long long

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
Moves moves[] = {Left, Right, Top, Down};

unordered_set<string> visited;


//Report
ll duration_time;
int duplicatedNodes, solutionDepth, maxDepth;
bool solved;

bool isValidPosition(pii position)
{
    return position.first >= 0 and position.first < 3 && position.second >= 0 and position.second < 3; 
}

void move(pii current, int i, State currentState, DataStructure &ds)
{
    pii newZeroPosition = pii(current.first + dx[i], current.second + dy[i]);

    if (!isValidPosition(newZeroPosition))
    {
        return;
    }

    swap(currentState.grid[currentState.zeroPosition.first][currentState.zeroPosition.second], currentState.grid[newZeroPosition.first][newZeroPosition.second]);

    State newState(currentState.grid, currentState.path);
    newState.depth = currentState.depth + 1;
    newState.cost = ds.cost(newState);

    if (visited.count(newState.key) || newState.depth > LIMIT_DEPTH)
    {
        duplicatedNodes++;
        return;
    }

    visited.insert(newState.key);

    newState.path.push_back(moves[i]);

    ds.add(newState);
}

void printPath(vector<Moves> path)
{
    for (auto currentMovement : path)
    {
        cout << (char)currentMovement << endl;
    }
}

void printGrid(int grid[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << (char)(grid[i][j] ? '0' + grid[i][j] : ' ') << " \n"[j == 2];
        }
    }
}

void clearScreen()
{
    system("cls||clear");
}

void sleep()
{
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
}

void solve (State state)
{
    pii zeroPosition = state.zeroPosition;

    clearScreen();

    for (Moves currentMovement : state.path)
    {
        printGrid(state.grid);

        pii newZeroPosition = pii(zeroPosition.first + dx[currentMovement], zeroPosition.second + dy[currentMovement]);
        swap(state.grid[zeroPosition.first][zeroPosition.second], state.grid[newZeroPosition.first][newZeroPosition.second]);
        zeroPosition = newZeroPosition;

        sleep();

        clearScreen();
    }

    printGrid(state.grid);
}

void search(State &initialState, DataStructure &ds)
{
    try
    {
        maxDepth = duplicatedNodes = solutionDepth = solved = 0;
        visited.clear();

        ds.add(initialState);

        auto start = high_resolution_clock::now();

        while (!ds.isEmpty())
        {
            State currentState = ds.extract();
            
            maxDepth = max(maxDepth, currentState.depth);

            if (currentState.isFinalState())
            {
                duration_time = duration_cast<microseconds>(high_resolution_clock::now() - start).count();

                solutionDepth = currentState.depth;

                solved = true;

                initialState.path = currentState.path;

                solve(initialState);
                return;
            }

            for (int i = 0; i < 4; i++)
            {
                move(currentState.zeroPosition, i, currentState, ds);   
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool askInput(int grid[3][3])
{
    cout << "Insert the 8-puzzle:\n" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (cin.eof())
            {
                return false;
            }
            else 
            {
                cin >> grid[i][j];
            }
        }
    }

    return true;
}

void printReport(State initialState, DataStructure &ds)
{
    search(initialState, ds);
    

    cout << "\nSTRUCTURE NAME: " << ds.name() << endl;
    cout << "TIME: " << duration_time << endl;
    cout << "BOUNDARY NODES: " << visited.size() << endl;
    cout << "GENERATED NODES: " << visited.size() + duplicatedNodes << endl;
    cout << "SOLUTION DEPTH: " << solutionDepth << endl;
    cout << "MAXIMUM DEPTH: " << maxDepth << endl;
    cout << "SOLVED: " << (solved ? "TRUE" : "FALSE") << endl << endl;
}

void report()
{
    int grid[3][3] = {  {8, 3, 2},
                        {7, 4, 5},
                        {1, 6, 0}};

    while (askInput(grid))
    {   

        State initialState(grid);
        
        cout << "Choice a option:\n1 - A* Search\n2 - DFS\n3 - BFS\n4 - Greedy Search\n";
        int choice;
        cin >> choice;
    
        ASTAR dsAStar;
        DFS dsDfs;
        BFS dsBfs;
        Greedy dsGreedy;

        switch (choice)
        {
        case 1:
            printReport(initialState, {dsAStar});
            break;
        case 2:
            printReport(initialState, {dsDfs});
            break;
        case 3:
            printReport(initialState, {dsBfs});
            break;
        case 4:
            printReport(initialState, {dsGreedy});
            break;
        default:
            break;
        }

    }
}

int main()
{
    report();

    return 0;
}