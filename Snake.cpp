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
tuple<int, int> Snake::getClosestPoint(vector<tuple<int, int, int>> points)
{
    tuple<int, int> head = this->position.back(); // get the head
    double minDis = pow((get<0>(points[0]) - get<0>(head)), 2) + pow((get<1>(points[0]) - get<1>(head)), 2) / get<2>(points[0]);

    tuple<int, int> minDisIndex = make_tuple(get<0>(points[0]), get<1>(points[0]));
    for (int i = 1; i < points.size(); i++) {
        if (pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2) / get<2>(points[i]) < minDis) {
            minDis = pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2) / get<2>(points[i]);
            minDisIndex = make_tuple(get<0>(points[i]), get<1>(points[i]));
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

Direction Snake::getWallJudge(tuple<int, int> headPos, vector<vector<int>>& map)
{
    int cnt1 = 0;
    int cnt2 = 0;
    int obs = 0;

    if (this->direction == Direction::UP) {
        for (int i = get<1>(headPos) - 1; i > 0; i--) {
            if (map[get<0>(headPos)][i] != -3 && map[get<0>(headPos)][i] != -1) {
                cnt1++;
            } else
                break;
        }
        for (int i = get<1>(headPos) + 1; i < map[0].size(); ++i) {
            if (map[get<0>(headPos)][i] != -3 && map[get<0>(headPos)][i] != -1) {
                cnt2++;
            } else
                break;
        }

    } else if (this->direction == Direction::DOWN) {
        for (int i = get<1>(headPos) - 1; i > 0; i--) {
            if (map[get<0>(headPos)][i] != -3 && map[get<0>(headPos)][i] != -1) {
                cnt1++;
            } else
                break;
        }
        for (int i = get<1>(headPos) + 1; i < map[0].size(); ++i) {
            if (map[get<0>(headPos)][i] != -3 && map[get<0>(headPos)][i] != -1) {
                cnt2++;
            } else
                break;
        }
    } else if (this->direction == Direction::LEFT) {
        for (int i = get<0>(headPos) - 1; i > 0; i--) {
            if (map[i][get<1>(headPos)] != -3 && map[i][get<1>(headPos)] != -1) {
                cnt1++;
            } else
                break;
        }
        for (int i = get<0>(headPos) + 1; i < map.size(); ++i) {
            if (map[i][get<1>(headPos)] != -3 && map[i][get<1>(headPos)] != -1) {
                cnt2++;
            } else
                break;
        }

    } else if (this->direction == Direction::RIGHT) {
        for (int i = get<0>(headPos) - 1; i > 0; i--) {
            if (map[i][get<1>(headPos)] != -3 && map[i][get<1>(headPos)] != -1) {
                cnt1++;
            } else
                break;
        }
        for (int i = get<0>(headPos) + 1; i < map.size(); ++i) {
            if (map[i][get<1>(headPos)] != -3 && map[i][get<1>(headPos)] != -1) {
                cnt2++;
            } else
                break;
        }
    }

    if (this->direction == Direction::DOWN || this->direction == Direction::UP) {
        for (int i = 1; i < map[0].size(); ++i) {
            if (map[get<0>(headPos)][i] == -1) {
                obs++;
            } else
                break;
        }
        if (cnt1 + cnt2 + obs == map[0].size() - 2 - 1) return Direction::NONE;
        else if (cnt1 > cnt2) {
            return Direction::LEFT;
        } else if (cnt1 < cnt2) {
            return Direction::RIGHT;
        } else
            return Direction::NONE;
    } else if (this->direction == Direction::LEFT || this->direction == Direction::RIGHT) {
        for (int i = 1; i < map.size(); ++i) {
            if (map[i][get<1>(headPos)] == -1) {
                obs++;
            }
        }

        if (cnt1 + cnt2 + obs == map.size() - 2 - 1) return Direction::NONE;
        else if (cnt1 > cnt2) {
            return Direction::UP;
        } else if (cnt1 < cnt2) {
            return Direction::DOWN;
        } else
            return Direction::NONE;
    }
    return Direction::NONE;
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
        } else if (map[get<0>(head) + this->up][get<1>(head)] == -1) {
            if ((map[get<0>(head)][get<1>(head) + this->left] != -3 && map[get<0>(head)][get<1>(head) + this->left] != -1) && (map[get<0>(head)][get<1>(head) + this->right] != -3 && map[get<0>(head)][get<1>(head) + this->right] != -1)) {
                result = this->getWallJudge(head, map);
            }
        }
    } else if (this->direction == Direction::DOWN) {
        if (map[get<0>(head) + this->down][get<1>(head)] == -3) {
            if ((map[get<0>(head)][get<1>(head) + this->left] != -3 && map[get<0>(head)][get<1>(head) + this->left] != -1) && (map[get<0>(head)][get<1>(head) + this->right] != -3 && map[get<0>(head)][get<1>(head) + this->right] != -1)) {
                result = this->getTailDirectionWhenCollision(Direction::DOWN);
            }
        } else if (map[get<0>(head) + this->down][get<1>(head)] == -1) {
            if ((map[get<0>(head)][get<1>(head) + this->left] != -3 && map[get<0>(head)][get<1>(head) + this->left] != -1) && (map[get<0>(head)][get<1>(head) + this->right] != -3 && map[get<0>(head)][get<1>(head) + this->right] != -1)) {
                result = this->getWallJudge(head, map);
            }
        }
    } else if (this->direction == Direction::LEFT) {
        if (map[get<0>(head)][get<1>(head) + this->left] == -3) {
            if ((map[get<0>(head) + this->up][get<1>(head)] != -3 && map[get<0>(head) + this->up][get<1>(head)] != -1) && (map[get<0>(head) + this->down][get<1>(head)] != -3 && map[get<0>(head) + this->down][get<1>(head)] != -1)) {
                result = this->getTailDirectionWhenCollision(Direction::LEFT);
            }
        } else if (map[get<0>(head)][get<1>(head) + this->left] == -1) {
            if ((map[get<0>(head) + this->up][get<1>(head)] != -3 && map[get<0>(head) + this->up][get<1>(head)] != -1) && (map[get<0>(head) + this->down][get<1>(head)] != -3 && map[get<0>(head) + this->down][get<1>(head)] != -1)) {
                result = this->getWallJudge(head, map);
            }
        }
    } else if (this->direction == Direction::RIGHT) {
        if (map[get<0>(head)][get<1>(head) + this->right] == -3) {
            if ((map[get<0>(head) + this->up][get<1>(head)] != -3 && map[get<0>(head) + this->up][get<1>(head)] != -1) && (map[get<0>(head) + this->down][get<1>(head)] != -3 && map[get<0>(head) + this->down][get<1>(head)] != -1)) {
                result = this->getTailDirectionWhenCollision(Direction::RIGHT);
            }
        } else if (map[get<0>(head)][get<1>(head) + this->right] == -1) {
            if ((map[get<0>(head) + this->up][get<1>(head)] != -3 && map[get<0>(head) + this->up][get<1>(head)] != -1) && (map[get<0>(head) + this->down][get<1>(head)] != -3 && map[get<0>(head) + this->down][get<1>(head)] != -1)) {
                result = this->getWallJudge(head, map);
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
    vector<tuple<int, int, int>> points;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0 && map[i][j] != -3 && map[i][j] != -1) points.push_back(tuple<int, int, int>(i, j, map[i][j]));
        }
    }

    this->target = getClosestPoint(points);

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
        Direction tmpDir;
        if (get<0>(this->target) - get<0>(head) > 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->down, get<1>(nextPos))) && map[get<0>(nextPos) + this->down][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
                this->direction = Direction::DOWN;
            } else
                tmpDir = Direction::DOWN;
        } else if (get<0>(this->target) - get<0>(head) < 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->up, get<1>(nextPos))) && map[get<0>(nextPos) + this->up][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
                this->direction = Direction::UP;
            } else {
                tmpDir = Direction::UP;
            }
        } else if (get<1>(this->target) - get<1>(head) > 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->right)) && map[get<0>(nextPos)][get<1>(nextPos) + this->right] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
                this->direction = Direction::RIGHT;
            } else {
                tmpDir = Direction::RIGHT;
            }
        } else if (get<1>(this->target) - get<1>(head) < 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left)) && map[get<0>(nextPos)][get<1>(nextPos) + this->left] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
                this->direction = Direction::LEFT;
            } else {
                tmpDir = Direction::LEFT;
            }
        }

        if (nextPos == head) {
            if (tmpDir == Direction::DOWN || tmpDir == Direction::UP) {
                if (get<1>(this->target) - get<1>(head) > 0) {
                    if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->right)) && map[get<0>(nextPos)][get<1>(nextPos) + this->right] != -1) {
                        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
                        this->direction = Direction::RIGHT;
                    } else {
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
                } else if (get<1>(this->target) - get<1>(head) < 0) {
                    if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left)) && map[get<0>(nextPos)][get<1>(nextPos) + this->left] != -1) {
                        nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
                        this->direction = Direction::LEFT;
                    } else {
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
                } else {
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
            } else if (tmpDir == Direction::RIGHT || tmpDir == Direction::LEFT) {
                if (get<0>(this->target) - get<0>(head) > 0) {
                    if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->down, get<1>(nextPos))) && map[get<0>(nextPos) + this->down][get<1>(nextPos)] != -1) {
                        nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
                        this->direction = Direction::DOWN;
                    } else {
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
                } else if (get<0>(this->target) - get<0>(head) < 0) {
                    if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->up, get<1>(nextPos))) && map[get<0>(nextPos) + this->up][get<1>(nextPos)] != -1) {
                        nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
                        this->direction = Direction::UP;
                    } else {
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
                } else {
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
            } else {
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
    }

    // move

    if (nextPos == this->target) {
        this->addLength(this->target);
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