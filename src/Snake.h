#pragma once
#include <cmath>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

// Add anything else you need

using namespace std;

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
protected:
    // helpers
    tuple<int, int> getClosestPoint(vector<tuple<int, int>> points);
    void addLength(tuple<int, int> nextPos);
    void moveBody(tuple<int, int> nextPos);
    bool isBodyPart(tuple<int, int> pos);

public:
    // Don't edit interface
    Snake(queue<tuple<int, int>> startPosition);
    queue<tuple<int, int>> nextPosition(vector<vector<int>> map);

    // Add anything else you need
    void displayStats() const;

    // Testing
    queue<tuple<int, int>> getStaticPosition();
};
