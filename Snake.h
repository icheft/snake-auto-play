#pragma once
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

// Add anything else you need

using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

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

    // Add anything else you need
    tuple<int, int> target;
    int length;
    Direction direction;

protected:
    // helpers
    tuple<int, int> getClosestPoint(vector<tuple<int, int, int>> points);
    void addLength(tuple<int, int> nextPos);
    void moveBody(tuple<int, int> nextPos);
    bool isBodyPart(tuple<int, int> pos);

    int checkLeft();
    int checkRight();
    int checkUp();
    int checkDown();

    int check(char pos, char secondPos);

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

public:
    // Don't edit interface
    Snake(queue<tuple<int, int>> startPosition);
    queue<tuple<int, int>> nextPosition(vector<vector<int>> map);

    // Add anything else you need
    void displayStats() const;
    // void showMap(vector<vector<int>> map);

    // Testing
    queue<tuple<int, int>> getStaticPosition();
    int getLength() const;
};
