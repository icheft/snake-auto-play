#pragma once
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unistd.h>
#include <vector>

// Add anything else you need
#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m" /* Cyan */
#define WHITE "\033[37m" /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */

using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Snake
{
private:
    enum
    {
        up = -1,
        down = 1,
        right = 1,
        left = -1
    };

    queue<tuple<int, int>> position;

    // Add anything else you need
    int length;
    Direction direction;

protected:
    // helpers
    tuple<int, int> getClosestPoint(vector<tuple<int, int>> points);
    void addLength(tuple<int, int> nextPos);
    void moveBody(tuple<int, int> nextPos);
    bool isBodyPart(tuple<int, int> pos);

    int checkLeft();
    int checkRight();
    int checkUp();
    int checkDown();

    int check(char pos);
    int check(char pos, char secondPos);

    /*
        return n if not
        return l if should go left
        return r if should go right
        return u if should go up
        return d if should go down
    */
    char hasTwoWays(vector<vector<int>>& map);

public:
    // Don't edit interface
    Snake(queue<tuple<int, int>> startPosition);
    queue<tuple<int, int>> nextPosition(vector<vector<int>> map);

    // Add anything else you need
    void displayStats() const;
    void showMap(vector<vector<int>> map);

    // Testing
    queue<tuple<int, int>> getStaticPosition();
    int getLength() const;
};
