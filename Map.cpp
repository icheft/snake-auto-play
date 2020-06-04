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

void Map::showMap()
{
    cout << " Map size: " << this->map.size() << " x " << this->map[0].size() << endl;
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[0].size(); j++) {
            if (this->map[i][j] == -3) {
                cout << right << setw(5) << "x";

                this->map[i][j] = 0; // FIXME
                // REF: [map change]
            } else
                cout << right << setw(5) << this->map[i][j];
        }
        cout << endl;
    }
    return;
}

bool Map::hasPoint()
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0 && map[i][j] != -3 && map[i][j] != -1) return true;
        }
    }
    return false;
}

vector<vector<int>> Map::getMap() const
{
    return this->map;
}

void Map::updateSnakePos(Snake& snake)
{
    queue<tuple<int, int>> tmpPos = snake.getStaticPosition();

    while (!tmpPos.empty()) {
        this->map[get<0>(tmpPos.front())][get<1>(tmpPos.front())] = -3; //REF: [map change]
        tmpPos.pop();
    }

    return;
}