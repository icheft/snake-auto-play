#include "Map.h"

Map::Map()
{
    this->map = {
        { -1, -1, -1, -1, -1, -1, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 2, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 1, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, -1, -1, -1, -1, -1, -1 }
    };
}

Map::~Map()
{
}

void Map::showMap() const
{
    cout << "Map size: " << this->map.size() << " x " << this->map[0].size() << endl;
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[0].size(); j++) {
            if (this->map[i][j] == -3) cout << right << setw(5) << "x";
            else
                cout << right << setw(5) << this->map[i][j];
        }
        cout << endl;
    }
    return;
}

vector<vector<int>> Map::getMap() const
{
    return this->map;
}

void Map::updateSnakePos(Snake& snake)
{
    queue<tuple<int, int>> tmpPos = snake.getStaticPosition();

    while (!tmpPos.empty()) {
        this->map[get<0>(tmpPos.front())][get<1>(tmpPos.front())] = -3;
        tmpPos.pop();
    }

    return;
}