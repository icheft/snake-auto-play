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
    map.updateMap();
    map.showMap();

    // while (map.hasPoint()) {
    for (int i = 0; i < 40; i++) {
        cout << "////////////////////////////////" << endl;
        snake.nextPosition(map.getMap());
        // cout << "﫟" << endl;
        map.showMap();
        snake.displayStats();
        map.updateSnakePos(snake);
        map.updateMap();
        cout << "////////////////////////////////" << endl;
    }
    // }

    // snake.addLength(tuple<int, int>(3, 4));
    // snake.nextPosition(map.getMap());
    // snake.displayStats();
    // map.updateSnakePos(snake);
    // map.showMap();

    // snake.nextPosition(map.getMap());
    // snake.displayStats();
    // map.updateSnakePos(snake);
    // map.showMap();

    return 0;
}