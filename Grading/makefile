run: test

test:
	@echo [ 17%]  Ready to compile.
	@echo [ 23%]  g++ -std=c++11 main.cpp Snake.cpp -o snake.out
	@g++ -std=c++11 main.cpp Snake.cpp -o snake.out
	@echo [ 70%]  Almost done.
	@echo [100%]  Cheers. Success! Built target snake.out.
	@echo
	@echo $(man)
	@echo
	@echo 💬 \(Or type \"make grade\" to see the result for official grade.\)


clean:
	@echo [ 70%]  Cleaning objects.
	@rm -f snake.out
	@echo [100%] Done.