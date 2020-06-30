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

// private functions
// helpers
void Snake::cleanPath()
{
    while (!take_moves.empty()) {
        take_moves.pop();
    }
}

void Snake::addLength(tuple<int, int> nextPos)
{
    if (get<0>(nextPos) - get<0>(this->position.back()) == 1) this->direction = Direction::DOWN;
    else if (get<0>(nextPos) - get<0>(this->position.back()) == -1)
        this->direction = Direction::UP;
    else if (get<1>(nextPos) - get<1>(this->position.back()) == -1)
        this->direction = Direction::LEFT;
    else if (get<1>(nextPos) - get<1>(this->position.back()) == 1)
        this->direction = Direction::RIGHT;

    this->position.push(nextPos);
}

void Snake::moveBody(tuple<int, int> nextPos)
{
    if (get<0>(nextPos) - get<0>(this->position.back()) == 1) this->direction = Direction::DOWN;
    else if (get<0>(nextPos) - get<0>(this->position.back()) == -1)
        this->direction = Direction::UP;
    else if (get<1>(nextPos) - get<1>(this->position.back()) == -1)
        this->direction = Direction::LEFT;
    else if (get<1>(nextPos) - get<1>(this->position.back()) == 1)
        this->direction = Direction::RIGHT;

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

    queue<tuple<int, int>> tmpPos = this->position;
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

queue<tuple<int, int>> Snake::nextPositionWhenPathNotFound(vector<vector<int>> map)
{
    // Implement by yourself

    // get every point's position in the map
    vector<tuple<int, int, int>> points;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0 && map[i][j] != -3 && map[i][j] != -1) points.push_back(tuple<int, int, int>(i, j, map[i][j]));
        }
    }

    tuple<int, int> target = getClosestPoint(points).front();

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
    queue<tuple<int, int>> tmpPos = this->position;
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
        if (get<0>(target) - get<0>(head) > 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->down, get<1>(nextPos))) && map[get<0>(nextPos) + this->down][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->down, get<1>(nextPos));
                this->direction = Direction::DOWN;
            } else
                tmpDir = Direction::DOWN;
        } else if (get<0>(target) - get<0>(head) < 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos) + this->up, get<1>(nextPos))) && map[get<0>(nextPos) + this->up][get<1>(nextPos)] != -1) {
                nextPos = make_tuple(get<0>(nextPos) + this->up, get<1>(nextPos));
                this->direction = Direction::UP;
            } else {
                tmpDir = Direction::UP;
            }
        } else if (get<1>(target) - get<1>(head) > 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->right)) && map[get<0>(nextPos)][get<1>(nextPos) + this->right] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->right);
                this->direction = Direction::RIGHT;
            } else {
                tmpDir = Direction::RIGHT;
            }
        } else if (get<1>(target) - get<1>(head) < 0) {
            if (!this->isBodyPart(tuple<int, int>(get<0>(nextPos), get<1>(nextPos) + this->left)) && map[get<0>(nextPos)][get<1>(nextPos) + this->left] != -1) {
                nextPos = make_tuple(get<0>(nextPos), get<1>(nextPos) + this->left);
                this->direction = Direction::LEFT;
            } else {
                tmpDir = Direction::LEFT;
            }
        }

        if (nextPos == head) {
            if (tmpDir == Direction::DOWN || tmpDir == Direction::UP) {
                if (get<1>(target) - get<1>(head) > 0) {
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
                } else if (get<1>(target) - get<1>(head) < 0) {
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
                if (get<0>(target) - get<0>(head) > 0) {
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
                } else if (get<0>(target) - get<0>(head) < 0) {
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

    if (nextPos == target) {
        this->addLength(target);
        this->point += map[get<0>(target)][get<1>(target)];
    } else
        this->moveBody(nextPos);

    return this->position;
}
// a star
queue<tuple<int, int>> Snake::getClosestPoint(vector<tuple<int, int, int>> points)
{

    queue<tuple<int, int>> minDisList;

    // dis / value
    tuple<int, int> head = this->position.back(); // get the head

    for (int round = 0; round < points.size(); round++) {
        double minDis = pow((get<0>(points[round]) - get<0>(head)), 2) + pow((get<1>(points[round]) - get<1>(head)), 2) / get<2>(points[round]);
        // double minDis = (pow((get<0>(points[round]) - get<0>(head)), 2) + pow((get<1>(points[round]) - get<1>(head)), 2)) / get<2>(points[round]);
        // double minDis = (abs(get<0>(points[round]) - get<0>(head)) + abs((get<1>(points[round]) - get<1>(head)))) / get<2>(points[round]);
        // double minDis = max(abs(get<0>(points[round]) - get<0>(head)), abs((get<1>(points[round]) - get<1>(head)))) / get<2>(points[round]);

        tuple<int, int> minDisIndex = make_tuple(get<0>(points[round]), get<1>(points[round]));
        int minIndex = round;
        for (int i = round + 1; i < points.size(); i++) {
            if (pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2) / get<2>(points[i]) < minDis) {
                // if ((pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2)) / get<2>(points[i]) < minDis) {
                // if ((abs(get<0>(points[i]) - get<0>(head)) + abs((get<1>(points[i]) - get<1>(head)))) / get<2>(points[i]) < minDis) {
                // if (max(abs(get<0>(points[i]) - get<0>(head)), abs((get<1>(points[i]) - get<1>(head)))) / get<2>(points[i]) < minDis) {

                minDis = pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2) / get<2>(points[i]);
                // minDis = (pow((get<0>(points[i]) - get<0>(head)), 2) + pow((get<1>(points[i]) - get<1>(head)), 2)) / get<2>(points[i]);
                // minDis = (abs(get<0>(points[i]) - get<0>(head)) + abs((get<1>(points[i]) - get<1>(head)))) / get<2>(points[i]);
                // minDis = max(abs(get<0>(points[i]) - get<0>(head)), abs((get<1>(points[i]) - get<1>(head)))) / get<2>(points[i]);

                minDisIndex = make_tuple(get<0>(points[i]), get<1>(points[i]));
                minIndex = i;
            }
        }
        minDisList.push(minDisIndex);
        if (minIndex != round) {
            tuple<int, int, int> tmp = points[round];
            points[round] = points[minIndex];
            points[minIndex] = tmp;
        }
    }

    // value
    /*
    for (int round = 0; round < points.size(); round++) {
        int maxPoint = get<2>(points[round]);
        tuple<int, int> maxPointIndex = make_tuple(get<0>(points[round]), get<1>(points[round]));
        int maxIndex = round;
        for (int i = round + 1; i < points.size(); i++) {
            if (get<2>(points[i]) > maxPoint) {
                maxPoint = get<2>(points[i]);
                maxPointIndex = make_tuple(get<0>(points[i]), get<1>(points[i]));
                maxIndex = i;
            }
        }
        minDisList.push(maxPointIndex);
        if (maxIndex != round) {
            tuple<int, int, int> tmp = points[round];
            points[round] = points[maxIndex];
            points[maxIndex] = tmp;
        }
    }
    */
    return minDisList;
}

Snake::Snake(queue<tuple<int, int>> startPosition)
{
    this->point = 0;
    this->position = startPosition;
}

queue<tuple<int, int>> Snake::nextPosition(vector<vector<int>> map)
{
    // Implement by yourself
    if (this->point < 185) {
        return this->nextPositionWhenPathNotFound(map);
    }
    if (!take_moves.empty()) {
        // stick to the path
        tuple<int, int> nextHead = take_moves.top();
        int x, y;
        tie(x, y) = take_moves.top();
        take_moves.pop();
        if (map[x][y] == 0) {
            this->moveBody(nextHead);
        } else {
            this->addLength(nextHead);
            this->point += map[get<0>(nextHead)][get<1>(nextHead)];
            this->cleanPath();
        }
        return this->position;
    } else {
        // record Snake's position on map, making them obstacles / blocks
        // FIXME
        // vector<vector<int>> tmpMap = map;
        queue<tuple<int, int>> tmpPos = this->position;
        while (!tmpPos.empty()) {
            map[get<0>(tmpPos.front())][get<1>(tmpPos.front())] = -3; //REF: [map change]
            tmpPos.pop();
        }

        // get point
        vector<tuple<int, int, int>> points;
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[0].size(); j++) {
                if (map[i][j] != 0 && map[i][j] != -3 && map[i][j] != -1) points.push_back(tuple<int, int, int>(i, j, map[i][j]));
            }
        }

        queue<tuple<int, int>> pointsList = getClosestPoint(points);

        // find path
        bool success = false;
        while (success == false && !pointsList.empty()) {
            tuple<int, int> head = position.back();
            tie(take_moves, success) = aStarSearch(make_pair(get<0>(head), get<1>(head)), make_pair(get<0>(pointsList.front()), get<1>(pointsList.front())), map);
            pointsList.pop();
            if (!success) this->cleanPath();
        }

        if (success) {
            tuple<int, int> nextHead = take_moves.top();
            int x, y;
            tie(x, y) = take_moves.top();
            take_moves.pop();
            if (map[x][y] == 0) {
                this->moveBody(nextHead);
            } else {
                this->addLength(nextHead);
                this->point += map[get<0>(nextHead)][get<1>(nextHead)];
                this->cleanPath();
            }
            return this->position;
        } else {
            // clean
            this->cleanPath();

            // use the old way
            return this->nextPositionWhenPathNotFound(map);
        }
    }
}

bool Snake::isValid(pair<int, int> pos, const vector<vector<int>>& map)
{
    return (map[pos.first][pos.second] != -1 && map[pos.first][pos.second] != -3);
}

int Snake::calculateHValue(pair<int, int> pos, const pair<int, int>& des)
{
    double x = des.first - pos.first;
    double y = des.second - pos.second;

    return abs(x) + abs(y); // Manhattan
    // return max(x, y); // Diagonal
    // return pow(x, 2) + pow(y, 2); // Euclidean
}

// A Utility Function to trace the path from the source
// to destination
stack<pair<int, int>> tracePath(const vector<vector<cell>>& cellDetails, const pair<int, int>& dest)
{
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    // Path.push (make_pair (row, col));
    return Path;
}

pair<stack<pair<int, int>>, bool> Snake::aStarSearch(pair<int, int> src, pair<int, int> des, vector<vector<int>> map)
{
    // Create a closed list and initialise it to false which means
    // that no cell has been included yet
    // This closed list is implemented as a boolean 2D array in vector form
    vector<bool> tmpClosedList(50, false);
    vector<vector<bool>> closedList(map.size(), tmpClosedList);

    // Declare a 2D array of structure to hold the details
    // of that cell
    cell aCell(-1, -1, INT_MAX, INT_MAX, INT_MAX);
    vector<cell> tmpCellDetails(map[0].size(), aCell);
    vector<vector<cell>> cellDetails(map.size(), tmpCellDetails);

    // Initialising the parameters of the starting node
    // = src
    int i = src.first;
    int j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /* 
	Create an open list having information as- 
	<f, <i, j>> 
	where f = g + h, 
	and i, j are the row and column index of that cell 
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	This open list is implemented as a set of pair of pair.
    */
    set<pPair> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // We set this boolean value as false as initially
    // the destination is not reached.
    // bool foundDest = false; // not used

    while (!openList.empty()) {
        pPair p = *(openList.begin());

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // To store the 'g', 'h' and 'f' of the 4 successors
        double gNew, hNew, fNew;

        Pair grid;

        //----------- 1st Successor (DOWN) ------------

        // Only process this cell if this is a valid one
        grid = Pair(i + 1, j);
        if (isValid(grid, map)) {
            if (grid == des) {
                // Set the Parent of the destination cell
                cellDetails[grid.first][grid.second].parent_i = i;
                cellDetails[grid.first][grid.second].parent_j = j;

                return make_pair(tracePath(cellDetails, des), true);
            }
            // If the successor is already on the closed then ignore it.
            // Else do the following
            else if (closedList[grid.first][grid.second] == false) {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(grid, des);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[grid.first][grid.second].f == INT_MAX || cellDetails[grid.first][grid.second].f > fNew) {
                    openList.insert(make_pair(fNew, grid));
                    // Update the details of this cell
                    cellDetails[grid.first][grid.second].f = fNew;
                    cellDetails[grid.first][grid.second].g = gNew;
                    cellDetails[grid.first][grid.second].h = hNew;
                    cellDetails[grid.first][grid.second].parent_i = i;
                    cellDetails[grid.first][grid.second].parent_j = j;
                }
            }
        }
        //----------- 2nd Successor (UP) ------------

        // Only process this cell if this is a valid one
        grid = Pair(i - 1, j);
        if (isValid(grid, map)) {
            if (grid == des) {
                // Set the Parent of the destination cell
                cellDetails[grid.first][grid.second].parent_i = i;
                cellDetails[grid.first][grid.second].parent_j = j;

                return make_pair(tracePath(cellDetails, des), true);
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[grid.first][grid.second] == false) {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(grid, des);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[grid.first][grid.second].f == INT_MAX || cellDetails[grid.first][grid.second].f > fNew) {
                    openList.insert(make_pair(fNew, grid));
                    // Update the details of this cell
                    cellDetails[grid.first][grid.second].f = fNew;
                    cellDetails[grid.first][grid.second].g = gNew;
                    cellDetails[grid.first][grid.second].h = hNew;
                    cellDetails[grid.first][grid.second].parent_i = i;
                    cellDetails[grid.first][grid.second].parent_j = j;
                }
            }
        }
        //----------- 3rd Successor (RIGHT) ------------

        // Only process this cell if this is a valid one
        grid = Pair(i, j + 1);
        if (isValid(grid, map)) {
            if (grid == des) {
                // Set the Parent of the destination cell
                cellDetails[grid.first][grid.second].parent_i = i;
                cellDetails[grid.first][grid.second].parent_j = j;
                return make_pair(tracePath(cellDetails, des), true);
            }
            // If the successor is already on the closed then ignore it.
            // Else do the following
            else if (closedList[grid.first][grid.second] == false) {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(grid, des);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[grid.first][grid.second].f == INT_MAX || cellDetails[grid.first][grid.second].f > fNew) {
                    openList.insert(make_pair(fNew, grid));
                    // Update the details of this cell
                    cellDetails[grid.first][grid.second].f = fNew;
                    cellDetails[grid.first][grid.second].g = gNew;
                    cellDetails[grid.first][grid.second].h = hNew;
                    cellDetails[grid.first][grid.second].parent_i = i;
                    cellDetails[grid.first][grid.second].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (LEFT) ------------

        // Only process this cell if this is a valid one
        grid = Pair(i, j - 1);
        if (isValid(grid, map)) {
            if (grid == des) {
                // Set the Parent of the destination cell
                cellDetails[grid.first][grid.second].parent_i = i;
                cellDetails[grid.first][grid.second].parent_j = j;

                return make_pair(tracePath(cellDetails, des), true);
            }
            // If the successor is already on the closed then ignore it.
            // Else do the following
            else if (closedList[grid.first][grid.second] == false) {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(grid, des);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[grid.first][grid.second].f == INT_MAX || cellDetails[grid.first][grid.second].f > fNew) {
                    openList.insert(make_pair(fNew, grid));
                    // Update the details of this cell
                    cellDetails[grid.first][grid.second].f = fNew;
                    cellDetails[grid.first][grid.second].g = gNew;
                    cellDetails[grid.first][grid.second].h = hNew;
                    cellDetails[grid.first][grid.second].parent_i = i;
                    cellDetails[grid.first][grid.second].parent_j = j;
                }
            }
        }
    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destination cell. This may happen when the
    // there is no way to destination cell (due to blockages)
    return make_pair(stack<pair<int, int>>(), false);
}
