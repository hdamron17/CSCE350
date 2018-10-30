BUILD:=build
SRC:=src
TEST:=test
PLOTS:=build/plotgrowth2.tex build/plotgrowth3.tex

.PHONY: all replot

all: plot
replot:
	@$(MAKE) -W $(BUILD)/cmpsort

plot: $(PLOTS)
$(PLOTS): $(BUILD)/output.csv $(SRC)/plotgrowth.gp
	gnuplot $(SRC)/plotgrowth.gp

$(BUILD)/output.csv: $(BUILD)/cmpsort $(SRC)/countcmp.sh
	$(SRC)/countcmp.sh > $(BUILD)/output.csv

compile: $(BUILD)/cmpsort

$(BUILD)/cmpsort: $(SRC)/cmpsort.cpp | $(BUILD)
	g++ -Wall -std=c++11 $(SRC)/cmpsort.cpp -o $(BUILD)/cmpsort

doc: $(BUILD)/analysis.pdf
$(BUILD)/analysis.pdf: $(SRC)/analysis.tex $(PLOTS)
	latexmk -pdf -silent -synctex=1 -outdir=build $(SRC)/analysis.tex

test: $(SRC)/test.sh $(BUILD)/cmpsort $(wildcard $(TEST)/*.in $(TEST)/*.out)
	$(SRC)/test.sh

$(BUILD):
	mkdir -p $(BUILD)
