#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    int i;
    int clk;
    int tick= top->count;
    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open ("counter.vcd");

    //initialize simulation inputs
    top->clk =1;
    top->rst =1;
    top->en = 0;

    //run simulation for many clock cycles
    for (i=0; i<300; i++){
        // dump variables in vcd file and toggle clock

        top->en = !(tick == 9); 
        std::cout<<tick<<std::endl;
        for(clk =0; clk<2; clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }
        top->rst = (i<2) | (i==15);
        //top-> count == x09 then top ->en =0 until building up i = old i +3
        
        
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);

}