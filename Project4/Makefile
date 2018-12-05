# TODO: change this to be compatible

BIN=bin
SOURCES=decode

.PHONY: all mkbin test $(SOURCES)
all: $(SOURCES)

$(SOURCES): %: $(BIN)/%

$(BIN)/%: %.cpp | $(BIN)
	g++ -Wall -std=c++11 $< -o $@

test: $(SOURCES)
	@./test.sh

$(BIN):
	@mkdir -p $(BIN)
