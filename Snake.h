#pragma once
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
        up,
        down,
        right,
        left
    };

    queue<tuple<int, int>> position;

    // Add anything else you need
protected:
    tuple<int, int> getClosestPoint(vector<tuple<int, int>> points);

public:
    // Don't edit interface
    Snake(queue<tuple<int, int>> startPosition);
    queue<tuple<int, int>> nextPosition(vector<vector<int>> map);

    // Add anything else you need
    void displayStats() const;

    // Testing
    void addLength(tuple<int, int> nextPost);
    queue<tuple<int, int>> getStaticPosition();
};
