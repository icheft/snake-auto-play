#include <queue>
#include <tuple>
#include <vector>

// Add anything else you need

using namespace std;

class Snake
{
private:
    queue<tuple<int, int>> position;

    // Add anything else you need

public:
    // Don't edit interface
    Snake(queue<tuple<int, int>> startPosition);
    queue<tuple<int, int>> nextPosition(vector<vector<int>> map);

    // Add anything else you need
};
