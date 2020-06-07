# run: objects

man = " Usage: ./snake.out <LEVEL> <-OPTION>\n"\
			"Options:\n"\
        			"\t-h,--help               Show this help message\n"\
        			"\t-a,--animation          Show animation in terminal\n"\
        			"\t-f,--frames             Show the process in a series of frames, hitting enter to go through\n"\
        			"\t-l,--list               Show the entire process all in one"

run: test

test:
	@echo [ 17%]  Ready to compile.
	@echo [ 23%]  g++ -std=c++11 main.cpp Snake.cpp Map.cpp -o snake.out
	@g++ -std=c++11 main.cpp Snake.cpp Map.cpp -o snake.out
	@echo [ 70%]  Almost done.
	@echo [100%]  Cheers. Success! Built target snake.out.
	@echo
	@echo $(man)
	@echo
	@echo 💬 \(Or type \"make grade\" to see the result for official grade.\)


grade:
	@echo [ 17%] Ready to compile.
	@echo [ 23%] g++ -std=c++11 Grading/Main.cpp Grading/Snake.cpp -o Grading/snake.out
	@g++ -std=c++11 Grading/Main.cpp Grading/Snake.cpp -o Grading/snake.out
	@echo [ 70%]  Almost done.
	@echo [100%]  Cheers. Success! Built target Grading/snake.out.
	@echo
	@echo $(man)
	@echo
	@echo 💬 \(Or type \"make\" to see the my own version of the snake.\)


clean:
	@echo [ 70%]  Cleaning objects.
	@rm -f Grading/snake.out
	@rm -f snake.out
	@echo [100%] Done.