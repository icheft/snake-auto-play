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
    void showMap() const;
    vector<vector<int>> getMap() const;

    void updateSnakePos(Snake& snake);
};
