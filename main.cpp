#include "Map.h"
#include "Snake.h"
#include <unistd.h>

void displayManMsg(char* program_name)
{
    cerr << "Usage: " << program_name << " <LEVEL> <-OPTION>" << endl;
    cout << "Options:\n"
         << "\t-h,--help\t\tShow this help message\n"
         << "\t-a,--animation\t\tShow animation in terminal\n"
         << "\t-f,--frames\t\tShow the process in a series of frames, hitting enter to go through\n"
         << "\t-l,--list\t\tShow the entire process all in one"
         << "\t-s,--simple\t\tShow the entire process all in one, but only stats are shown"
         << endl;
}

queue<tuple<int, int>> stage2_init()
{
    tuple<int, int> list[104] = { tuple<int, int>(42, 26), tuple<int, int>(42, 27), tuple<int, int>(42, 28), tuple<int, int>(42, 29), tuple<int, int>(42, 30), tuple<int, int>(42, 31), tuple<int, int>(42, 32), tuple<int, int>(42, 33), tuple<int, int>(42, 34), tuple<int, int>(42, 35), tuple<int, int>(42, 36), tuple<int, int>(42, 37), tuple<int, int>(42, 38), tuple<int, int>(42, 39), tuple<int, int>(42, 40), tuple<int, int>(42, 41), tuple<int, int>(42, 42), tuple<int, int>(42, 43), tuple<int, int>(42, 44), tuple<int, int>(42, 45), tuple<int, int>(42, 46), tuple<int, int>(42, 47), tuple<int, int>(41, 47), tuple<int, int>(40, 47), tuple<int, int>(39, 47), tuple<int, int>(38, 47), tuple<int, int>(37, 47), tuple<int, int>(36, 47), tuple<int, int>(35, 47), tuple<int, int>(34, 47), tuple<int, int>(33, 47), tuple<int, int>(32, 47), tuple<int, int>(31, 47), tuple<int, int>(30, 47), tuple<int, int>(29, 47), tuple<int, int>(28, 47), tuple<int, int>(27, 47), tuple<int, int>(26, 47), tuple<int, int>(25, 47), tuple<int, int>(24, 47), tuple<int, int>(23, 47), tuple<int, int>(22, 47), tuple<int, int>(21, 47), tuple<int, int>(20, 47), tuple<int, int>(19, 47), tuple<int, int>(18, 47), tuple<int, int>(17, 47), tuple<int, int>(16, 47), tuple<int, int>(15, 47), tuple<int, int>(14, 47), tuple<int, int>(13, 47), tuple<int, int>(12, 47), tuple<int, int>(11, 47), tuple<int, int>(10, 47), tuple<int, int>(9, 47), tuple<int, int>(8, 47), tuple<int, int>(7, 47), tuple<int, int>(6, 47), tuple<int, int>(5, 47), tuple<int, int>(5, 46), tuple<int, int>(5, 45), tuple<int, int>(6, 45), tuple<int, int>(7, 45), tuple<int, int>(8, 45), tuple<int, int>(9, 45), tuple<int, int>(10, 45), tuple<int, int>(11, 45), tuple<int, int>(12, 45), tuple<int, int>(13, 45), tuple<int, int>(14, 45), tuple<int, int>(15, 45), tuple<int, int>(16, 45), tuple<int, int>(16, 44), tuple<int, int>(16, 43), tuple<int, int>(16, 42), tuple<int, int>(16, 41), tuple<int, int>(16, 40), tuple<int, int>(16, 39), tuple<int, int>(16, 38), tuple<int, int>(16, 37), tuple<int, int>(16, 36), tuple<int, int>(16, 35), tuple<int, int>(16, 34), tuple<int, int>(16, 33), tuple<int, int>(16, 32), tuple<int, int>(16, 31), tuple<int, int>(16, 30), tuple<int, int>(16, 29), tuple<int, int>(16, 28), tuple<int, int>(16, 27), tuple<int, int>(16, 26), tuple<int, int>(16, 25), tuple<int, int>(16, 24), tuple<int, int>(16, 23), tuple<int, int>(16, 22), tuple<int, int>(16, 21), tuple<int, int>(16, 20), tuple<int, int>(16, 19), tuple<int, int>(16, 18), tuple<int, int>(16, 17), tuple<int, int>(16, 16), tuple<int, int>(16, 15), tuple<int, int>(16, 14), tuple<int, int>(16, 13) };
    queue<tuple<int, int>> initPos;
    for (int i = 0; i < 104; i++) {
        initPos.push(list[i]);
    }
    return initPos;
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        displayManMsg(argv[0]);
        return 1;
    }
    string arg = argv[1];
    if (argc == 2 && ((arg == "-h") || (arg == "--help"))) {
        displayManMsg(argv[0]);
        return 1;
    } else if (argc < 3) { // We expect 3 arguments: the program name, the source path and the destination path
        displayManMsg(argv[0]);
        return 1;
    }

    int level = atoi(argv[1]);
    Map map(level);
    map.showMap();
    queue<tuple<int, int>> initPos;

    if (level < 9) {
        initPos.push(tuple<int, int>(2, 2));
        initPos.push(tuple<int, int>(2, 3));
        initPos.push(tuple<int, int>(2, 4));
    } else {
        initPos = stage2_init();
    }

    Snake snake(initPos);
    snake.displayStats();
    int preLen = snake.getLength();

    map.updateSnakePos(snake);
    map.updateMap();
    map.showMap();

    int step = 0;

    // while (map.hasPoint()) {
    arg = argv[2];
    if (arg == "-a" || arg == "--animation") {
        while (true) {
            cout << "////////////////////////////////" << endl;
            step++;
            cout << step << " steps" << endl;
            snake.displayStats();
            snake.nextPosition(map.getMap());
            // cout << "﫟" << endl;
            map.showMap();
            if (!map.updateSnakePos(snake)) {
                cout << "Y ﮙ U EAT YOURSELF" << endl;
                cout << "////////////////////////////////" << endl;
                break;
            }
            if (preLen != snake.getLength()) {
                map.updateMap();
                preLen = snake.getLength();
            }
            cout << "////////////////////////////////" << endl;

            usleep(50000);
            printf("\033c");
        }
    } else if (arg == "-f" || arg == "--frames") {
        while (true) {
            cout << "////////////////////////////////" << endl;
            step++;
            cout << step << " steps" << endl;
            snake.displayStats();
            snake.nextPosition(map.getMap());
            // cout << "﫟" << endl;
            map.showMap();
            if (!map.updateSnakePos(snake)) {
                cout << "Y ﮙ U EAT YOURSELF" << endl;
                cout << "////////////////////////////////" << endl;
                break;
            }
            if (preLen != snake.getLength()) {
                map.updateMap();
                preLen = snake.getLength();
            }
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
            step++;
            cout << step << " steps" << endl;
            snake.displayStats();
            snake.nextPosition(map.getMap());
            // cout << "﫟" << endl;
            map.showMap();
            if (!map.updateSnakePos(snake)) {
                cout << "Y ﮙ U EAT YOURSELF" << endl;
                cout << "////////////////////////////////" << endl;
                break;
            }
            if (preLen != snake.getLength()) {
                map.updateMap();
                preLen = snake.getLength();
            }
            cout << "////////////////////////////////" << endl;
        }
    }

    else if (arg == "-s" || arg == "--simple") {
        while (true) {
            cout << "////////////////////////////////" << endl;
            step++;
            cout << step << " steps" << endl;
            snake.displayStats();
            snake.nextPosition(map.getMap());
            // cout << "﫟" << endl;
            if (!map.updateSnakePos(snake)) {
                map.showMap();
                cout << "Y ﮙ U EAT YOURSELF" << endl;
                cout << "////////////////////////////////" << endl;
                break;
            }
            if (preLen != snake.getLength()) {
                map.updateMap();
                preLen = snake.getLength();
            }
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