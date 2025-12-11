# Makefile
MODULE=counter
SRC_DIR=src
SIM_DIR=sim

.PHONY: all clean run

all: run

# Run Verilator to compile the Verilog + C++ wrapper
obj_dir/V$(MODULE): $(SRC_DIR)/$(MODULE).sv $(SIM_DIR)/tb_$(MODULE).cpp
	verilator -cc --exe --build -j 0 -Wall --trace \
	-I$(SRC_DIR) \
	$(SRC_DIR)/$(MODULE).sv $(SIM_DIR)/tb_$(MODULE).cpp \
	--top-module $(MODULE)

# Execute the compiled binary
run: obj_dir/V$(MODULE)
	./obj_dir/V$(MODULE)

clean:
	rm -rf obj_dir
	rm -f *.vcd
