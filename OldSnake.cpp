#include "OldSnake.h"

// Add anything else you need

// protected
tuple<int, int> OldSnake::getClosestPoint(vector<tuple<int, int>> points)
{
    tuple<int, int> head = this->position.back(); // get the head
    double minDis = pow((get<0>(points[0]) - get<0>(head)), 2) + pow((get<1>(points[0]) - get<1>(head)), 2);

    tuple<int, int> minDisIndex = points[0];
    for (int i = 1; i < points.size(); i++) {
        if (pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2) < minDis) {
            minDis = pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2);
            minDisIndex = points[i];
        }
    }

    return minDisIndex;
}

void OldSnake::addLength(tuple<int, int> nextPos)
{
    this->length++;
    this->position.push(nextPos);
}

void OldSnake::moveBody(tuple<int, int> nextPos)
{
    this->position.pop();
    this->position.push(nextPos);
}

bool OldSnake::isBodyPart(tuple<int, int> pos)
{
    queue<tuple<int, int>> posQ = this->position;
    while (!posQ.empty()) {
        if (pos == posQ.front()) return true;
        else
            posQ.pop();
    }
    return false;
}
int OldSnake::check(char pos, char secondPos)
{
    int cnt = 0;
    if (pos == 'l' && secondPos == 'd') {
        queue<tuple<int, int>> posQ = this->position;
        tuple<int, int> head = this->position.back();
        while (!posQ.empty()) {
            if ((get<1>(head) - get<1>(posQ.front())) > 0 && (get<0>(head) - get<0>(posQ.front())) < 0) {
                cnt++;
            }
            posQ.pop();
        }
    } else if (pos == 'l' && secondPos == 'u') {
        queue<tuple<int, int>> posQ = this->position;
        tuple<int, int> head = this->position.back();
        while (!posQ.empty()) {
            if ((get<1>(head) - get<1>(posQ.front())) > 0 && (get<0>(head) - get<0>(posQ.front())) > 0) {
                cnt++;
            }
            posQ.pop();
        }

    } else if (pos == 'r' && secondPos == 'd') {
        queue<tuple<int, int>> posQ = this->position;
        tuple<int, int> head = this->position.back();
        while (!posQ.empty()) {
            if ((get<1>(head) - get<1>(posQ.front())) < 0 && (get<0>(head) - get<0>(posQ.front())) < 0) {
                cnt++;
            }
            posQ.pop();
        }
    } else if (pos == 'r' && secondPos == 'u') {
        queue<tuple<int, int>> posQ = this->position;
        tuple<int, int> head = this->position.back();
        while (!posQ.empty()) {
            if ((get<1>(head) - get<1>(posQ.front())) < 0 && (get<0>(head) - get<0>(posQ.front())) > 0) {
                cnt++;
            }
            posQ.pop();
        }
    }
    return cnt;
}

int OldSnake::checkLeft()
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
int OldSnake::checkRight()
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

int OldSnake::checkUp()
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
int OldSnake::checkDown()
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

char OldSnake::hasTwoWays(vector<vector<int>>& map)
{
    tuple<int, int> head = this->position.back();

    if (this->direction == Direction::DOWN && ((this->isBodyPart(tuple<int, int>(get<0>(head) + this->down, get<1>(head))) && this->isBodyPart(tuple<int, int>(get<0>(head) + this->up, get<1>(head)))) || (map[get<0>(head) + this->down][get<1>(head)] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head) + this->down, get<1>(head)))))) {
        if (((map[get<0>(head)][get<1>(head) + this->left] != -1 && map[get<0>(head)][get<1>(head) + this->left] != -3) && (map[get<0>(head)][get<1>(head) + this->right] != -1 && map[get<0>(head)][get<1>(head) + this->right] != -3))) {
            if (map[get<0>(head) + this->down][get<1>(head)] != -1) {
                if (checkRight() > checkLeft()) {
                    if (check('r', 'u') == 0 || check('r', 'd') == 0)
                        return 'r';
                    else
                        return 'l';
                } else if (checkRight() < checkLeft()) {
                    if (check('l', 'u') == 0 || check('l', 'd') == 0)
                        return 'l';
                    else
                        return 'r';
                } else
                    return 'n';
            } else
                return 'n';
        } else {
            // 看是不是死巷子
            // BUG
            return 'n';
        }
    } else if (this->direction == Direction::UP && ((this->isBodyPart(tuple<int, int>(get<0>(head) + this->up, get<1>(head))) && this->isBodyPart(tuple<int, int>(get<0>(head) + this->down, get<1>(head)))) || (map[get<0>(head) + this->up][get<1>(head)] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head) + this->down, get<1>(head)))))) {
        if (((map[get<0>(head)][get<1>(head) + this->left] != -1 && map[get<0>(head)][get<1>(head) + this->left] != -3) && (map[get<0>(head)][get<1>(head) + this->right] != -1 && map[get<0>(head)][get<1>(head) + this->right] != -3))) {
            if (map[get<0>(head) + this->up][get<1>(head)] != -1) {
                if (checkRight() > checkLeft()) {
                    if (check('r', 'u') == 0 || check('r', 'd') == 0)
                        return 'r';
                    else
                        return 'l';
                } else if (checkRight() < checkLeft()) {
                    if (check('l', 'u') == 0 || check('l', 'd') == 0)
                        return 'l';
                    else
                        return 'r';
                } else
                    return 'n';
            } else
                return 'n';
        } else {
            return 'n';
        }
    } else if (this->direction == Direction::RIGHT && ((this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->right)) && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->left))) || (map[get<0>(head)][get<1>(head) + this->right] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->left))))) {
        if (((map[get<0>(head) + this->up][get<1>(head)] != -1 && map[get<0>(head) + this->up][get<1>(head)] != -3) && (map[get<0>(head) + this->down][get<1>(head)] != -1 && map[get<0>(head) + this->down][get<1>(head)] != -3))) {
            if (map[get<0>(head)][get<1>(head) + this->right] != -1) {
                if (checkDown() < checkUp()) {
                    if (check('r', 'u') == 0 || check('l', 'u') == 0)
                        return 'u';
                    else
                        return 'd';
                } else if (checkDown() > checkUp()) {
                    if (check('r', 'd') == 0 || check('l', 'd') == 0)
                        return 'd';
                    else
                        return 'u';
                } else
                    return 'n';
            } else
                return 'n';

        } else {
            return 'n';
        }
    } else if (this->direction == Direction::LEFT && ((this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->left)) && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->right))) || (map[get<0>(head)][get<1>(head) + this->left] == -1 && this->isBodyPart(tuple<int, int>(get<0>(head), get<1>(head) + this->right))))) {
        if (((map[get<0>(head) + this->up][get<1>(head)] != -1 && map[get<0>(head) + this->up][get<1>(head)] != -3) && (map[get<0>(head) + this->down][get<1>(head)] != -1 && map[get<0>(head) + this->down][get<1>(head)] != -3))) {
            if (map[get<0>(head)][get<1>(head) + this->left] != -1) {
                if (checkDown() < checkUp()) {
                    if (check('r', 'u') == 0 || check('l', 'u') == 0)
                        return 'u';
                    else
                        return 'd';
                } else if (checkDown() > checkUp()) {
                    if (check('r', 'd') == 0 || check('l', 'd') == 0)
                        return 'd';
                    else
                        return 'u';
                } else
                    return 'n';
            } else
                return 'n';
        } else {
            return 'n';
        }
    } else {
        return 'n';
    }
}

// public
OldSnake::OldSnake(queue<tuple<int, int>> startPosition)
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

queue<tuple<int, int>> OldSnake::nextPosition(vector<vector<int>> map)
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
    vector<vector<int>> tmpMap = map;
    queue<tuple<int, int>> tmpPos = this->getStaticPosition();
    while (!tmpPos.empty()) {
        tmpMap[get<0>(tmpPos.front())][get<1>(tmpPos.front())] = -3; //REF: [map change]
        tmpPos.pop();
    }

    tuple<int, int> head = this->position.back();
    tuple<int, int> nextPos = head;
    char opt = hasTwoWays(tmpMap);
    if (opt == 'l') {
        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
        this->direction = Direction::LEFT;
    } else if (opt == 'r') {
        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
        this->direction = Direction::RIGHT;
    } else if (opt == 'u') {
        nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
        this->direction = Direction::UP;
    } else if (opt == 'd') {
        nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
        this->direction = Direction::DOWN;
    } else {

        if (get<0>(target) - get<0>(head) > 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->down, get<1>(nextPos))) && map[get<0>(nextPos) + this->down][get<1>(nextPos)] != -1) {
            nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
            this->direction = Direction::DOWN;
        } else if (get<0>(target) - get<0>(head) < 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->up, get<1>(nextPos))) && map[get<0>(nextPos) + this->up][get<1>(nextPos)] != -1) {
            nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
            this->direction = Direction::UP;
        } else if (get<1>(target) - get<1>(head) > 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->right)) && map[get<0>(nextPos)][get<1>(nextPos) + this->right] != -1) {
            nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
            this->direction = Direction::RIGHT;
        } else if (get<1>(target) - get<1>(head) < 0 && !this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left)) && map[get<0>(nextPos)][get<1>(nextPos) + this->left] != -1) {
            if (this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left))) {
            }
            nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
            this->direction = Direction::LEFT;
        }

        if (nextPos == head) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->down, get<1>(nextPos))) && map[get<0>(nextPos) + this->down][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
                this->direction = Direction::DOWN;
            } else if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->up, get<1>(nextPos))) && map[get<0>(nextPos) + this->up][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
                this->direction = Direction::UP;
            } else if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->right)) && map[get<0>(nextPos)][get<1>(nextPos) + this->right] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
                this->direction = Direction::RIGHT;
            } else if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left)) && map[get<0>(nextPos)][get<1>(nextPos) + this->left] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
                this->direction = Direction::LEFT;
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
void OldSnake::displayStats() const
{
    queue<tuple<int, int>> posQ = this->position;
    cout << "[" << this->length << "]-";
    cout << "tail {";
    while (!posQ.empty()) {
        cout << "(" << get<0>(posQ.front()) << ", " << get<1>(posQ.front()) << ")";
        if (posQ.front() != posQ.back()) cout << ", ";
        posQ.pop();
    }
    cout << "} head" << endl;
}

// Testing

queue<tuple<int, int>> OldSnake::getStaticPosition()
{
    return this->position;
}

int OldSnake::getLength() const
{
    return this->length;
}