#include "Snake.h"

// Add anything else you need

template <typename T>
tuple<T, T> operator+(tuple<T, T> const& t1, tuple<T, T> const& t2)
{
    return make_tuple(get<0>(t1) + get<0>(t2), get<1>(t1) + get<1>(t2));
}

template <typename T>
tuple<T, T> operator-(tuple<T, T> const& t1, tuple<T, T> const& t2)
{
    return make_tuple(get<0>(t1) - get<0>(t2), get<1>(t1) - get<1>(t2));
}

// protected
tuple<int, int> Snake::getClosestPoint(vector<tuple<int, int>> points)
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
int Snake::check(char pos, char secondPos)
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

Direction Snake::getTailDirectionWhenCollision(Direction headDir)
{
    tuple<int, int> head = this->position.back();
    tuple<int, int> pinPoint = head;
    if (headDir == Direction::UP) {
        pinPoint = make_tuple(get<0>(pinPoint) + this->up, get<1>(pinPoint));
    } else if (headDir == Direction::DOWN) {
        pinPoint = make_tuple(get<0>(pinPoint) + this->down, get<1>(pinPoint));
    } else if (headDir == Direction::LEFT) {
        pinPoint = make_tuple(get<0>(pinPoint), get<1>(pinPoint) + this->left);
    } else if (headDir == Direction::RIGHT) {
        pinPoint = make_tuple(get<0>(pinPoint), get<1>(pinPoint) + this->right);
    }

    queue<tuple<int, int>> tmpPos = this->getStaticPosition();
    tuple<int, int> prePos = tmpPos.front();

    while (!tmpPos.empty()) {
        if (tmpPos.front() == pinPoint) {
            tmpPos.pop();
            if (prePos == pinPoint) {
                tuple<int, int> nextPos = tmpPos.front();
                if (headDir == Direction::UP || headDir == Direction::DOWN) {
                    if (nextPos - pinPoint == make_tuple(0, 1)) {
                        return Direction::LEFT;
                    } else if (nextPos - pinPoint == make_tuple(0, -1)) {
                        return Direction::RIGHT;
                    }
                } else {
                    if (nextPos - pinPoint == make_tuple(1, 0)) {
                        return Direction::UP;
                    } else if (nextPos - pinPoint == make_tuple(-1, 0)) {
                        return Direction::DOWN;
                    }
                }
            } else {
                tuple<int, int> nextPos = tmpPos.front();
                if (headDir == Direction::UP || headDir == Direction::DOWN) {
                    if (nextPos - pinPoint == make_tuple(0, 1)) {
                        return Direction::LEFT;
                    } else if (nextPos - pinPoint == make_tuple(0, -1)) {
                        return Direction::RIGHT;
                    } else if (prePos - pinPoint == make_tuple(0, 1)) {
                        return Direction::RIGHT;
                    } else if (prePos - pinPoint == make_tuple(0, -1)) {
                        return Direction::LEFT;
                    }
                } else {
                    if (nextPos - pinPoint == make_tuple(1, 0)) {
                        return Direction::UP;
                    } else if (nextPos - pinPoint == make_tuple(-1, 0)) {
                        return Direction::DOWN;
                    } else if (prePos - pinPoint == make_tuple(-1, 0)) {
                        return Direction::UP;
                    } else if (prePos - pinPoint == make_tuple(1, 0)) {
                        return Direction::DOWN;
                    }
                }
            }

            break;
        } else {
            prePos = tmpPos.front();
            tmpPos.pop();
        }
    }
    return Direction::NONE;
}

Direction Snake::hasTwoWays(vector<vector<int>>& map)
{
    tuple<int, int> head = this->position.back();
    Direction result = Direction::NONE;
    if (this->direction == Direction::UP) {
        if (map[get<0>(head) + this->up][get<1>(head)] == -3) {
            if ((map[get<0>(head)][get<1>(head) + this->left] != -3 && map[get<0>(head)][get<1>(head) + this->left] != -1) && (map[get<0>(head)][get<1>(head) + this->right] != -3 && map[get<0>(head)][get<1>(head) + this->right] != -1)) {
                result = this->getTailDirectionWhenCollision(Direction::UP);
            }
        }
    } else if (this->direction == Direction::DOWN) {
        if (map[get<0>(head) + this->down][get<1>(head)] == -3) {
            if ((map[get<0>(head)][get<1>(head) + this->left] != -3 && map[get<0>(head)][get<1>(head) + this->left] != -1) && (map[get<0>(head)][get<1>(head) + this->right] != -3 && map[get<0>(head)][get<1>(head) + this->right] != -1)) {
                result = this->getTailDirectionWhenCollision(Direction::DOWN);
            }
        }
    } else if (this->direction == Direction::LEFT) {
        if (map[get<0>(head)][get<1>(head) + this->left] == -3) {
            if ((map[get<0>(head) + this->up][get<1>(head)] != -3 && map[get<0>(head) + this->up][get<1>(head)] != -1) && (map[get<0>(head) + this->down][get<1>(head)] != -3 && map[get<0>(head) + this->down][get<1>(head)] != -1)) {
                result = this->getTailDirectionWhenCollision(Direction::LEFT);
            }
        }
    } else if (this->direction == Direction::RIGHT) {
        if (map[get<0>(head)][get<1>(head) + this->right] == -3) {
            if ((map[get<0>(head) + this->up][get<1>(head)] != -3 && map[get<0>(head) + this->up][get<1>(head)] != -1) && (map[get<0>(head) + this->down][get<1>(head)] != -3 && map[get<0>(head) + this->down][get<1>(head)] != -1)) {
                result = this->getTailDirectionWhenCollision(Direction::RIGHT);
            }
        }
    }

    return result;
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
    Direction opt = hasTwoWays(tmpMap);
    if (opt == Direction::LEFT) {
        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
        this->direction = Direction::LEFT;
    } else if (opt == Direction::RIGHT) {
        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
        this->direction = Direction::RIGHT;
    } else if (opt == Direction::UP) {
        nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
        this->direction = Direction::UP;
    } else if (opt == Direction::DOWN) {
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
    cout << "} head" << endl;
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