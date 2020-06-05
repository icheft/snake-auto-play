#include "Snake.h"

// Add anything else you need

// protected
tuple<int, int> Snake::getClosestPoint(vector<tuple<int, int>> points)
{
    tuple<int, int> head = this->position.back(); // get the head
    double minDis = pow((get<0>(points[0]) - get<0>(head)), 2) + pow((get<1>(points[0]) - get<1>(head)), 2);
    cout << "﫟" << endl;
    tuple<int, int> minDisIndex = points[0];
    for (int i = 1; i < points.size(); i++) {
        if (pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2) < minDis) {
            minDis = pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2);
            minDisIndex = points[i];
        }
    }

    return minDisIndex;
}

void Snake::addLength(tuple<int, int> nextPos)
{
    this->length++;
    this->position.push(nextPos);
}

void Snake::moveBody(tuple<int, int> nextPos)
{
    this->position.pop();
    this->position.push(nextPos);
}

bool Snake::isBodyPart(tuple<int, int> pos)
{
    queue<tuple<int, int>> posQ = this->position;
    while (!posQ.empty()) {
        if (pos == posQ.front()) return true;
        else
            posQ.pop();
    }
    return false;
}

int Snake::checkLeft()
{
    queue<tuple<int, int>> posQ = this->position;
    tuple<int, int> head = this->position.back();
    int cnt = 0;
    while (!posQ.empty()) {
        if ((get<1>(head) - get<1>(posQ.front())) > 0) {
            cnt++;
        }
        posQ.pop();
    }
    return cnt;
}
int Snake::checkRight()
{
    queue<tuple<int, int>> posQ = this->position;
    tuple<int, int> head = this->position.back();
    int cnt = 0;
    while (!posQ.empty()) {
        if ((get<1>(head) - get<1>(posQ.front())) < 0) {
            cnt++;
        }
        posQ.pop();
    }
    return cnt;
}

int Snake::checkUp()
{
    queue<tuple<int, int>> posQ = this->position;
    tuple<int, int> head = this->position.back();
    int cnt = 0;
    while (!posQ.empty()) {
        if ((get<0>(head) - get<0>(posQ.front())) > 0) {
            cnt++;
        }
        posQ.pop();
    }
    return cnt;
}
int Snake::checkDown()
{
    queue<tuple<int, int>> posQ = this->position;
    tuple<int, int> head = this->position.back();
    int cnt = 0;
    while (!posQ.empty()) {
        if ((get<0>(head) - get<0>(posQ.front())) < 0) {
            cnt++;
        }
        posQ.pop();
    }
    return cnt;
}

char Snake::hasTwoWays(vector<vector<int>>& map)
{
    tuple<int, int> head = this->position.back();

    if ((this->isBodyPart(tuple<int, int>(get<0>(head) + this->down, get<1>(head))) && this->isBodyPart(tuple<int, int>(get<0>(head) + this->up, get<1>(head)))) || (map[get<0>(head) + this->down][get<1>(head)] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head) + this->up, get<1>(head))))) {
        if (map[get<0>(head)][get<1>(head) + this->left] != -1 && map[get<0>(head)][get<1>(head) + this->right] != -1) {
            if (checkRight() > checkLeft()) return 'l';
            else
                return 'r';
        } else {
            return 'n';
        }
    } else if ((this->isBodyPart(tuple<int, int>(get<0>(head) + this->up, get<1>(head))) && this->isBodyPart(tuple<int, int>(get<0>(head) + this->down, get<1>(head)))) || (map[get<0>(head) + this->up][get<1>(head)] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head) + this->down, get<1>(head))))) {
        if (map[get<0>(head)][get<1>(head) + this->left] != -1 && map[get<0>(head)][get<1>(head) + this->right] != -1) {
            if (checkRight() > checkLeft()) return 'l';
            else
                return 'r';
        } else {
            return 'n';
        }
    } else if ((this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->right)) && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->left))) || (map[get<0>(head)][get<1>(head) + this->right] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->left)))) {
        if (map[get<0>(head) + this->up][get<1>(head)] != -1 && map[get<0>(head) + this->down][get<1>(head)] != -1) {
            if (checkDown() > checkUp()) return 'u';
            else
                return 'd';
        } else {
            return 'n';
        }
    } else if ((this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->left)) && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->right))) || (map[get<0>(head)][get<1>(head) + this->left] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->right)))) {
        if (map[get<0>(head) + this->up][get<1>(head)] != -1 && map[get<0>(head) + this->down][get<1>(head)] != -1) {
            if (checkDown() > checkUp()) return 'u';
            else
                return 'd';
        } else {
            return 'n';
        }
    } else {
        return 'n';
    }
}

// public
Snake::Snake(queue<tuple<int, int>> startPosition)
{
    // Implement by yourself
    this->position = startPosition;

    // length
    this->length = 0;
    queue<tuple<int, int>> posQ = this->position;
    while (!posQ.empty()) {
        this->length++;
        posQ.pop();
    }
}

queue<tuple<int, int>> Snake::nextPosition(vector<vector<int>> map)
{
    // Implement by yourself

    // get every point's position in the map
    vector<tuple<int, int>> points;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0 && map[i][j] != -3 && map[i][j] != -1) points.push_back(tuple<int, int>(i, j));
        }
    }

    tuple<int, int> target = getClosestPoint(points);

    cout << "什 target: (" << get<0>(target) << ", " << get<1>(target) << ")" << endl;
    /**
     * Movements:
     * 4 cases:
     *  t_row - row > 0
     *     move down
     *  t_row - row < 0
     *     move up
     *  target_col - col > 0
     *     move right
     *  target_col - col < 0
     *     move left
     */

    tuple<int, int> head = this->position.back();
    tuple<int, int> nextPos = head;
    char opt = hasTwoWays(map);
    if (opt == 'l') {
        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
    } else if (opt == 'r') {
        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
    } else if (opt == 'u') {
        nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
    } else if (opt == 'd') {
        nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
    } else {

        if (get<0>(target) - get<0>(head) > 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->down, get<1>(nextPos))) && map[get<0>(nextPos) + this->down][get<1>(nextPos)] != -1) {
            nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
        } else if (get<0>(target) - get<0>(head) < 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->up, get<1>(nextPos))) && map[get<0>(nextPos) + this->up][get<1>(nextPos)] != -1) {
            nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
        } else if (get<1>(target) - get<1>(head) > 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->right)) && map[get<0>(nextPos)][get<1>(nextPos) + this->right] != -1) {
            nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
        } else if (get<1>(target) - get<1>(head) < 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left)) && map[get<0>(nextPos)][get<1>(nextPos) + this->left] != -1) {
            nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
        }

        if (nextPos == head) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->down, get<1>(nextPos))) && map[get<0>(nextPos) + this->down][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
            } else if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->up, get<1>(nextPos))) && map[get<0>(nextPos) + this->up][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
            } else if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->right)) && map[get<0>(nextPos)][get<1>(nextPos) + this->right] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
            } else if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left)) && map[get<0>(nextPos)][get<1>(nextPos) + this->left] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
            }
        }
    }

    // move

    if (nextPos == target) {
        this->addLength(target);
    } else
        this->moveBody(nextPos);

    return this->position;
}

// Add anything else you need
void Snake::displayStats() const
{
    queue<tuple<int, int>> posQ = this->position;
    cout << "[" << this->length << "]-";
    cout << "tail {";
    while (!posQ.empty()) {
        cout << "(" << get<0>(posQ.front()) << ", " << get<1>(posQ.front()) << ")";
        if (posQ.front() != posQ.back()) cout << ", ";
        posQ.pop();
    }
    cout << "} head " << endl;
}

// Testing

queue<tuple<int, int>> Snake::getStaticPosition()
{
    return this->position;
}

int Snake::getLength() const
{
    return this->length;
}