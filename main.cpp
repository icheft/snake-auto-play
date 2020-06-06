#include "Map.h"
#include "Snake.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    string arg = argv[1];
    if (argc == 2 && ((arg == "-h") || (arg == "--help"))) {
        cerr << "Usage: " << argv[0] << "<LEVEL> <-OPTION>" << endl;
        cout << "Options:\n"
             << "\t-h,--help\t\tShow this help message\n"
             << "\t-a,--animation\t\tShow animation in terminal\n"
             << "\t-f,--frames\t\tShow the process in a series of frames, hitting enter to go through\n"
             << "\t-l,--list\t\tShow the entire process all in one\n"
             << endl;
        return 1;
    } else if (argc < 3) { // We expect 3 arguments: the program name, the source path and the destination path
        cerr << "Usage: " << argv[0] << " <LEVEL> <-OPTION>" << endl;
        cout << "Options:\n"
             << "\t-h,--help\t\tShow this help message\n"
             << "\t-a,--animation\t\tShow animation in terminal\n"
             << "\t-f,--frames\t\tShow the process in a series of frames, hitting enter to go through\n"
             << "\t-l,--list\t\tShow the entire process all in one\n"
             << endl;
        return 1;
    }

    int level = atoi(argv[1]);
    Map map(level);
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
    arg = argv[2];
    if (arg == "-a" || arg == "--animation") {
        while (true) {
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

<<<<<<< HEAD
            // usleep(100000);
=======
>>>>>>> master
            usleep(50000);
            printf("\033c");
        }
    } else if (arg == "-f" || arg == "--frames") {
        while (true) {
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
            // usleep(100000);
            printf("\033c");
        }
    } else if (arg == "-l" || arg == "--list") {
        while (true) {
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
        }
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