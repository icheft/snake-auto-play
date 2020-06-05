#include "Map.h"

Map::Map()
{
    this->map = {
        { -1, -1, -1, -1, -1, -1, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, -1 },
        { -1, -1, -1, -1, -1, -1, -1 }
    };
}

Map::~Map()
{
}

void Map::cleanSnake()
{
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[0].size(); j++) {
            if (this->map[i][j] == -3) {
                this->map[i][j] = 0; // FIXME
            }
        }
    }
}

void Map::showMap()
{
    cout << " Map size: " << this->map.size() << " x " << this->map[0].size() << endl;
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[0].size(); j++) {
            if (this->map[i][j] == -3) {
                cout << right << GREEN << "x" << RESET << "\t";
                // REF: [map change]
            } else if (this->map[i][j] == -1) {
                cout << right << BOLDBLACK << this->map[i][j] << RESET << "\t";
            } else if (this->map[i][j] != 0) {
                cout << right << BOLDYELLOW << this->map[i][j] << RESET << "\t";
            } else
                cout << right << this->map[i][j] << "\t";
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

bool Map::updateSnakePos(Snake& snake)
{
    queue<tuple<int, int>> tmpPos = snake.getStaticPosition();
    this->cleanSnake();
    while (!tmpPos.empty()) {
        if (this->map[get<0>(tmpPos.front())][get<1>(tmpPos.front())] == -3) return false;
        else
            this->map[get<0>(tmpPos.front())][get<1>(tmpPos.front())] = -3; //REF: [map change]
        tmpPos.pop();
    }

    return true;
}

void Map::updateMap()
{
    if (!this->hasPoint()) {
        srand(time(NULL));

        int cnt = rand() % 4 + 1;
        for (int i = 0; i < cnt; i++) {
            tuple<int, int> candyPos = make_tuple(rand() % (this->map.size() - 2) + 1, rand() % (this->map[0].size() - 2) + 1);
            cout << "Updating..." << endl;
            while (map[get<0>(candyPos)][get<1>(candyPos)] == -3 || map[get<0>(candyPos)][get<1>(candyPos)] == -1) {
                candyPos = make_tuple(rand() % (this->map.size() - 1) + 1, rand() % (this->map[0].size() - 1) + 1);
            }
            map[get<0>(candyPos)][get<1>(candyPos)] = 1;
        }
        cout << "Map updated! " << endl;
    }
}