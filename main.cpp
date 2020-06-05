#include "Map.h"
#include "Snake.h"

int main()
{
    Map map(2);
    map.showMap();

    queue<tuple<int, int>> initPos;

    initPos.push(tuple<int, int>(2, 2));
    initPos.push(tuple<int, int>(2, 3));
    initPos.push(tuple<int, int>(2, 4));
    Snake snake(initPos);
    snake.displayStats();

    map.updateSnakePos(snake);
    map.updateMap();
    map.showMap();
    int preLen = snake.getLength();

    // while (map.hasPoint()) {
    while (snake.getLength() <= 40) {
        cout << "////////////////////////////////" << endl;
        snake.displayStats();
        snake.nextPosition(map.getMap());
        // cout << "﫟" << endl;
        map.showMap();
        if (!map.updateSnakePos(snake)) {
            cout << "Y ﮙ U EAT YOURSELF" << endl;
            cout << "////////////////////////////////" << endl;
            break;
        }
        map.updateMap();
        cout << "////////////////////////////////" << endl;

        // for debugging purpose
        // commenting the lines below will give a whole look of the result
        // char continueOpt;
        // cin >> continueOpt;
        // if (continueOpt != EOF) printf("\033c");
        // else
        //     break;
        cin.ignore();
        printf("\033c");
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