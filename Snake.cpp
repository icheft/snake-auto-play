#include "Snake.h"

// Add anything else you need

tuple<int, int> Snake::getClosestPoint(vector<tuple<int, int>> points)
{
}

Snake::Snake(queue<tuple<int, int>> startPosition)
{
    // Implement by yourself
    this->position = startPosition;
}

queue<tuple<int, int>> Snake::nextPosition(vector<vector<int>> map)
{
    // Implement by yourself

    // get every point's position in the map
    vector<tuple<int, int>> points;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0 && map[i][j] != -3 && map[i][j] != -1) points.push_back(tuple<int, int>(i, j));
        }
    }

    tuple<int, int> target = getClosestPoint(points);

    /**
     * 4 cases:
     *  target_x - x > 0
     *     move right
     *  target_x - x < 0
     *     move left
     *  t_y - y > 0
     *     move up
     *  t_y - y < 0
     *     move down
     */

    return this->position;
}

// Add anything else you need
void Snake::displayStats() const
{
    queue<tuple<int, int>> posQ = this->position;
    cout << "tail {";
    while (!posQ.empty()) {
        cout << "(" << get<0>(posQ.front()) << ", " << get<1>(posQ.front()) << ")";
        if (posQ.front() != posQ.back()) cout << ", ";
        posQ.pop();
    }
    cout << "} head" << endl;
}

// Testing

void Snake::addLength(tuple<int, int> nextPost)
{
    this->position.push(nextPost);
}

queue<tuple<int, int>> Snake::getStaticPosition()
{
    return this->position;
}