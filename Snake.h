#pragma once
#include <climits>
#include <cmath>
#include <deque>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

struct cell
{
    // Row and Column index of its parent
    int parent_i, parent_j;

    // f = g + h
    int f, g, h;

    cell(int i, int j, int f, int g, int h)
        : parent_i(i), parent_j(j), f(f), g(g), h(h) { }
};

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

class Snake
{
private:
    enum
    {
        up = -1,
        down = 1,
        right = 1,
        left = -1
    };
    queue<tuple<int, int>> position;
    int point;

    tuple<int, int> target;
    Direction direction;
    stack<pair<int, int>> pathToFood;
    // queue<tuple<int, int>> path;

private:
    // dumb
    bool isBodyPart(tuple<int, int> pos);

    /*
        return n if not
        return l if should go left
        return r if should go right
        return u if should go up
        return d if should go down
    */
    Direction hasTwoWays(vector<vector<int>>& map);
    Direction getWallJudge(tuple<int, int> headPos, vector<vector<int>>& map);
    Direction getTailDirectionWhenCollision(Direction dir);
    queue<tuple<int, int>> nextPositionWhenPathNotFound(vector<vector<int>> map);

private:
    // a star
    bool isValid(pair<int, int> pos, const vector<vector<int>>& map);
    bool isValidForTail(pair<int, int> pos, const vector<vector<int>>& map);
    int calculateHValue(pair<int, int> pos, const pair<int, int>& des);
    pair<stack<pair<int, int>>, bool> aStarSearch(pair<int, int> src, pair<int, int> des, vector<vector<int>> map, int opt);
    queue<tuple<int, int>> getClosestPoint(vector<tuple<int, int, int>> points, bool found);

private:
    // helpers
    void addLength(tuple<int, int> nextPos);
    void moveBody(tuple<int, int> nextPos);
    void cleanPath();

public:
    // Don't edit interface
    Snake(queue<tuple<int, int>> startPosition);
    queue<tuple<int, int>> nextPosition(vector<vector<int>> map);

    // Add anything else you need
};
