BIN=bin
CXFLAGS+= -std=c++11

.PHONY: all mkbin
all: $(BIN)/bitmult
$(BIN)/%: %.cpp | mkbin
	$(CXX) $(CXXFLAGS) $< -o $@

mkbin:
	mkdir -p $(BIN)
