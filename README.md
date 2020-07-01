# IM 1010 Final Project
Freshman programming project, which requires students to write a program to automate the game-play of the classic snake game.

+ Score board (valid till `6/30`): [Google Spreadsheets (dm me for the password)](https://thinfi.com/r0zn)
+ Submission on COOL:  [Shortcut (Internal Usage Only)](https://cool.ntu.edu.tw/courses/765/assignments/14537)
+ Spec: [Final Project.pdf (dm me for the password)](./Final%20Project.pdf)

## Disclaimer
I do not own any ideas nor the source code of the grading system in this project. Also, unlike others Snake AI, this projects aims at a simpler (the hard way) implementation of the AI.

The repo is open-source, but it is mainly for the students who are taking the course IM 1010 in Spring 2020 at the National Taiwan University. All implementation is located at `Snake.cpp` and `Snake.h`, so if you are not part of the class, you can still get something out of it (this is not ideally implemented though). 

At first, I was trying to use only `if-else` statements to complete the task. It turned out that the snake was able to reach up to `188` points in the end at TA's grading system (points varied as the map generated different foods each time).

Later, taking advice from [GeeksForGeeks](https://www.geeksforgeeks.org/a-search-algorithm/), I've implemented A* Path Finding Algorithm, and reach the final score of `260`, which puts me in the 9th-ish place among up to 90 students taking this class.

Feel free to play around with this project. Further updates are not guaranteed.


## How to Use
The source code for submission is located at the `submission` branch. The `master` branch is for development use and it provides more information about the project. 

Type `make` to see result using the files in the main directory. To see result in `Grading/` directory, type `make grade`.

To clean up the executable files, type `make clean`.


See the main.cpp for yourself. For the official Grading System, please go to the [Grading Directory](./Grading) and mess with it.

## Ideas
For the `Hamiltonian` Cycle and `Graph` Search as seen on [chuyangliu](https://github.com/chuyangliu)'s [snake](https://github.com/chuyangliu/snake).
+ [ ] Hamiltonian Cycle
+ [ ] Graph search 
+ [x] Shortest path (so that the snake will zigzag to the food/point)

Other ideas I've thought of so far are:
+ [ ] Can overwrite that `tmpMap` and show the best route to the food by replacing all the unused elements to `-1` so that the snake won't run into any of them.


+ [ ] If there are blocks above, but the area of `2x2` (still a question) at the bottom remains empty, the snake can go that way
    ![Image](https://i.imgur.com/dP7m2q9.png)
    <p style="font-size: 12px">🔺 If implemented, when the above situation happens, the snake should go right instead of going left (according to the algorithm now, the snake will go `left` since on the right hand side, there are more blocks occupied and on the right hand side, the <code>u</code> and <code>l</code> is empty).</p>

    ![Image](https://i.imgur.com/JCPNxtQ.png)
    <p style="font-size: 12px">🔺 Still, this has to be solved, probably 2x2 isn't a good idea. In the situation above, the snake should go up instead of down. </p>
+ [ ] 算出蛇在哪個部位轉折的 (有兩段轉折才需要坐後面的判斷)。如果由 `UP` to `RIGHT`，則遇到身體時，需要 go `UP`。(Need to check if this logic fits all though)
+ [ ] 算到第二個轉折點的面積。

+ [ ] 上下左右順序調整（？ (現在是下上右左)

+ [x] 往尾巴那邊走
+ [ ] When you hit the wall, always go to where you are from



`Judge By Openness`: 
If at one point, the Snake has only two possible ways to go, it means that the snake should always go for the one with more spaces.

+ [x] 應該要紀錄目前行走記錄方向。(using `enum`)


`one-way-out`:
Try to implement 上述。


`virtual-snake`:
+ [x] 已經有一條 virtual snake，會每個點都跑一遍，看哪個最適合
+ [ ] 要有多條 virtual snake，每個的 if-else 不一樣 (?)

## Records
| MAPs                        | 🥇   | 🥈                                             | 🥉   |
| --------------------------- | --- | --------------------------------------------- | --- |
| 🌍 `map 1` (11x7) (full: 45) | 42  | 32                                            | 28  | 27 (run into 1-col dead-end) | 23          | 20  | 19  | 16  | 15  | 13 (run into 1-col dead-end) |
| 🌍 `map 2`                   | 52  | 46                                            | 42  | 41                           | 37          | 36  | 33  | 31  | 26  | 22                           |
| 🌍 `map 3`                   | 41  | 40                                            | 34  | 34                           | 30          | 23  | 20  | 10  |
| 🌍 `map 4`                   | 52  | 42                                            | 34  | 33                           | 29          | 20  | 15  |
| 🌍 `map 5`                   | 55  | 45                                            | 44  | 33                           | 28          | 25  | 23  | 21  |
| 🌍 `map 6`                   | 50  | 49                                            | 41  | 32                           | 28          | 27  | 23  | 20  | 16  |
| 🌍 `map 7`                   | 151 | 142 ![Image](https://i.imgur.com/J0Db3qH.png) | 122 | 120 (fixed)                  | 120         | 117 | 114 | 113 | 104 | 93                           | 90  | 84  | 74  | 66                            | 63                            |
| 🌍 `map 8`                   | 235 | 231                                           | 215 |                              | 186         | 182 | 216 | 176 | 176 | 163                          | 162 | 161 | 160 | 154 (run into 1-col dead-end) | 151 (run into 1-col dead-end) | 130 | 121 120 | 110 | 105 | 87 |
| 🌍 `map 8`  (start from 104) | 163 | 153                                           | 150 | 149                          | 124   ｜122 | 114 | 112 |


### Heuristics
| MAPs | Manhattan          | 188                      | Diagonal                 | Euclidean                |
| ---- | ------------------ | ------------------------ | ------------------------ | ------------------------ |
| 646  | 426 (Invalid step) | 139 (Invalid eat length) | 130 (Invalid eat length) | 139 (Invalid eat length) |
| 204  | 204 (Invalid step) | 123 (Invalid step)       | 114 (Invalid step)       | 123 (Invalid step)       |
| 322  | 186 (Invalid step) | 121 (Invalid step)       | 177 (Invalid step)       | 121 (Invalid step)       |
| 477  | 374 (Invalid step) | 112 (Invalid step)       | 195 (Invalid step)       | 132 (Invalid step)       |