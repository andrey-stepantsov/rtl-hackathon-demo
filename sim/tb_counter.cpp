// sim/tb_counter.cpp
#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

// --- FIX: Define simulation time variable ---
vluint64_t main_time = 0;

double sc_time_stamp() {
    return main_time;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vcounter* dut = new Vcounter;
    VerilatedVcdC* m_trace = new VerilatedVcdC;

    // Waveform setup
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    // Simulation loop
    while (main_time < 100) {
        dut->clk ^= 1;       // Toggle clock
        dut->eval();
        m_trace->dump(main_time); // Dump to VCD
        main_time++;
    }

    m_trace->close();
    delete dut;
    return 0;
}