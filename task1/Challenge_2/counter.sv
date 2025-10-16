module counter #(
    parameter WIDTH = 8
)(
    input logic clk,
    input logic arst,
    input logic  en,
    output logic [WIDTH-1:0] count
);

    always_ff @( posedge clk, posedge arst ) begin 
        if(arst) count <= {WIDTH{1'b0}};
        else count <= count+ {{WIDTH-1{1'b0}},en};
    end 
        
endmodule

