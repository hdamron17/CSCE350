BIN=bin

.PHONY: all mkbin test
all: $(BIN)/mult
$(BIN)/%: %.cpp | mkbin
	g++ -Wall -std=c++11 $< -o $@

test:
	@./test.sh

mkbin:
	@mkdir -p $(BIN)
