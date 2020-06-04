#pragma once
#include "Snake.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

class Map
{
private:
    vector<vector<int>> map;

public:
    Map();
    ~Map();
    void showMap();
    vector<vector<int>> getMap() const;
    bool hasPoint();

    void updateSnakePos(Snake& snake);
};
