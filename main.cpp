#include "Map.h"
#include "Snake.h"

int main()
{
    Map map;
    map.showMap();

    queue<tuple<int, int>> initPos;
    tuple<int, int> pos;
    pos = make_tuple(2, 2);
    initPos.push(pos);
    initPos.push(tuple<int, int>(2, 3));
    initPos.push(tuple<int, int>(2, 4));
    Snake snake(initPos);
    snake.displayStats();

    map.updateSnakePos(snake);
    map.showMap();

    // snake.addLength(tuple<int, int>(3, 4));
    // snake.displayStats();
    // map.updateSnakePos(snake);
    // map.showMap();

    return 0;
}