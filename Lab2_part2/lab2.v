/* This is a top level module that connects the switches and the 7-segment hex displays
 * to your multiplier.
 */
 


module lab2(SW, HEX0, HEX1, HEX2, HEX3);
	input [15:0] SW;
	output [6:0] HEX0;
	output [6:0] HEX1;
	output [6:0] HEX2;
	output [6:0] HEX3;	
	
	
	wire [7:0] A;  
	wire [7:0] B;
	wire [15:0] result;
	
	
	
	/* Connect switches to the multiplier. */
	assign A = SW[7:0];
	assign B = SW[15:8];


wire [7:0] pp1,pp2,pp3,pp4,pp5,pp6,pp7,pp8;
wire [56:0] c;
wire [42:0] r;
assign pp1[0]=A[0]&B[0];
assign pp1[1]=A[1]&B[0];
assign pp1[2]=A[2]&B[0];
assign pp1[3]=A[3]&B[0];
assign pp1[4]=A[4]&B[0];
assign pp1[5]=A[5]&B[0];
assign pp1[6]=A[6]&B[0];
assign pp1[7]=A[7]&B[0];

assign pp2[0]=A[0]&B[1];
assign pp2[1]=A[1]&B[1];
assign pp2[2]=A[2]&B[1];
assign pp2[3]=A[3]&B[1];
assign pp2[4]=A[4]&B[1];
assign pp2[5]=A[5]&B[1];
assign pp2[6]=A[6]&B[1];
assign pp2[7]=A[7]&B[1];

assign pp3[0]=A[0]&B[2];
assign pp3[1]=A[1]&B[2];
assign pp3[2]=A[2]&B[2];
assign pp3[3]=A[3]&B[2];
assign pp3[4]=A[4]&B[2];
assign pp3[5]=A[5]&B[2];
assign pp3[6]=A[6]&B[2];
assign pp3[7]=A[7]&B[2];

assign pp4[0]=A[0]&B[3];
assign pp4[1]=A[1]&B[3];
assign pp4[2]=A[2]&B[3];
assign pp4[3]=A[3]&B[3];
assign pp4[4]=A[4]&B[3];
assign pp4[5]=A[5]&B[3];
assign pp4[6]=A[6]&B[3];
assign pp4[7]=A[7]&B[3];

assign pp5[0]=A[0]&B[4];
assign pp5[1]=A[1]&B[4];
assign pp5[2]=A[2]&B[4];
assign pp5[3]=A[3]&B[4];
assign pp5[4]=A[4]&B[4];
assign pp5[5]=A[5]&B[4];
assign pp5[6]=A[6]&B[4];
assign pp5[7]=A[7]&B[4];

assign pp6[0]=A[0]&B[5];
assign pp6[1]=A[1]&B[5];
assign pp6[2]=A[2]&B[5];
assign pp6[3]=A[3]&B[5];
assign pp6[4]=A[4]&B[5];
assign pp6[5]=A[5]&B[5];
assign pp6[6]=A[6]&B[5];
assign pp6[7]=A[7]&B[5];

assign pp7[0]=A[0]&B[6];
assign pp7[1]=A[1]&B[6];
assign pp7[2]=A[2]&B[6];
assign pp7[3]=A[3]&B[6];
assign pp7[4]=A[4]&B[6];
assign pp7[5]=A[5]&B[6];
assign pp7[6]=A[6]&B[6];
assign pp7[7]=A[7]&B[6];

assign pp8[0]=A[0]&B[7];
assign pp8[1]=A[1]&B[7];
assign pp8[2]=A[2]&B[7];
assign pp8[3]=A[3]&B[7];
assign pp8[4]=A[4]&B[7];
assign pp8[5]=A[5]&B[7];
assign pp8[6]=A[6]&B[7];
assign pp8[7]=A[7]&B[7];


ha add0 (.x (pp1[0]),.y (0), .carry(c[0]), .sum(result[0]));

fa add1 (.x (pp1[1]), .y (pp2[0]), .cin (0), .cout (c[1]), .sum (r[0]));
fa add2 (.x (r[0]), .y (c[0]), .cin (0), .cout (c[2]), .sum (result[1]));

fa add3 (.x (pp1[2]), .y (pp2[1]), .cin (pp3[0]), .cout (c[3]), .sum (r[1]));
fa add4 (.x (r[1]), .y (c[1]), .cin (c[2]), .cout (c[4]), .sum (result[2]));

fa add5 (.x (pp1[3]), .y (pp2[2]), .cin (pp3[1]), .cout (c[5]), .sum (r[2]));
fa add6 (.x (r[2]), .y (pp4[0]), .cin (c[3]), .cout (c[6]), .sum (r[3]));
fa add7 (.x (r[3]), .y (c[4]), .cin (0), .cout (c[7]), .sum (result[3]));

fa add8 (.x (pp1[4]), .y (pp2[3]), .cin (pp3[2]), .cout (c[8]), .sum (r[4]));
fa add9 (.x (r[4]), .y (pp4[1]), .cin (c[5]), .cout (c[9]), .sum (r[5]));
fa add10 (.x (r[5]), .y (pp5[0]), .cin (c[6]), .cout (c[10]), .sum (r[6]));
fa add11 (.x (r[6]), .y (c[7]), .cin (0), .cout (c[11]), .sum (result[4]));

fa add12 (.x (pp1[5]), .y (pp2[4]), .cin (pp3[3]), .cout (c[12]), .sum (r[7]));
fa add13 (.x (r[7]), .y (pp4[2]), .cin (c[8]), .cout (c[13]), .sum (r[8]));
fa add14 (.x (r[8]), .y (pp5[1]), .cin (c[9]), .cout (c[14]), .sum (r[9]));
fa add15 (.x (r[9]), .y (pp6[0]), .cin (c[10]), .cout (c[15]), .sum (r[10]));
fa add16 (.x ( r[10] ), .y ( 0 ), .cin ( c[11] ), .cout (c[16]  ), .sum (result[5]));

fa add17 (.x (pp1[6]), .y (pp2[5] ), .cin (pp3[4]  ), .cout (c[17]  ), .sum (r[11]  ));
fa add18 (.x ( r[11] ), .y (pp4[3]  ), .cin ( c[12] ), .cout (c[18]  ), .sum (r[12]  ));
fa add19 (.x ( r[12] ), .y ( pp5[2] ), .cin ( c[13] ), .cout ( c[19] ), .sum ( r[13] ));
fa add20 (.x ( r[13] ), .y ( pp6[1] ), .cin ( c[14] ), .cout ( c[20] ), .sum ( r[14] ));
fa add21 (.x ( r[14] ), .y ( pp7[0] ), .cin ( c[15] ), .cout ( c[21] ), .sum ( r[15] ));
fa add22 (.x ( r[15] ), .y ( 0 ), .cin (c[16]  ), .cout ( c[22] ), .sum (result[6]  ));

fa add23 (.x (pp1[7]  ), .y (pp2[6]  ), .cin (pp3[5]  ), .cout (c[23]  ), .sum ( r[16] ));
fa add24 (.x ( r[16] ), .y ( pp4[4] ), .cin ( c[17] ), .cout ( c[24] ), .sum ( r[17] ));
fa add25 (.x ( r[17] ), .y ( pp5[3] ), .cin ( c[18] ), .cout ( c[25] ), .sum ( r[18] ));
fa add26 (.x ( r[18] ), .y ( pp6[2] ), .cin ( c[19] ), .cout ( c[26] ), .sum ( r[19] ));
fa add27 (.x ( r[19] ), .y ( pp7[1] ), .cin ( c[20] ), .cout ( c[27] ), .sum ( r[20] ));
fa add28 (.x ( r[20] ), .y ( pp8[0] ), .cin ( c[21] ), .cout ( c[28] ), .sum ( r[21] ));
fa add29 (.x ( r[21] ), .y ( 0 ), .cin ( c[22] ), .cout ( c[29] ), .sum ( result[7] ));

fa add30 (.x (pp2[7] ), .y (pp3[6]  ), .cin (c[23] ), .cout (c[30] ), .sum (r[22] ));
fa add31 (.x (r[22] ), .y (pp4[5] ), .cin (c[24] ), .cout (c[31] ), .sum (r[23] ));
fa add32 (.x (r[23] ), .y ( pp5[4] ), .cin (c[25] ), .cout ( c[32]), .sum (r[24] ));
fa add33 (.x (r[24] ), .y (pp6[3]  ), .cin (c[26] ), .cout (c[33] ), .sum (r[25] ));
fa add34 (.x (r[25] ), .y ( pp7[2] ), .cin (c[27] ), .cout (c[34] ), .sum ( r[26]));
fa add35 (.x (r[26] ), .y ( pp8[1] ), .cin (c[28] ), .cout (c[35] ), .sum (r[27] ));
fa add36 (.x (r[27] ), .y (0  ), .cin (c[29] ), .cout (c[36] ), .sum (result[8] ));

fa add37 (.x (pp3[7] ), .y (pp4[6]  ), .cin (c[30] ), .cout (c[37] ), .sum (r[28] ));
fa add38 (.x (r[28] ), .y (pp5[5] ), .cin (c[31] ), .cout (c[38] ), .sum (r[29] ));
fa add39 (.x (r[29] ), .y ( pp6[4] ), .cin (c[32] ), .cout (c[39] ), .sum (r[30] ));
fa add40 (.x (r[30] ), .y (pp7[3]  ), .cin (c[33] ), .cout (c[40] ), .sum (r[31] ));
fa add41 (.x (r[31] ), .y (pp8[2] ), .cin (c[34] ), .cout (c[41] ), .sum (r[32] ));
fa add42	(.x (r[32] ), .y ( c[35] ), .cin ( c[36]), .cout (c[42] ), .sum (result[9] ));

fa add43 (.x (pp4[7] ), .y (pp5[6]  ), .cin (c[37] ), .cout (c[43] ), .sum (r[33] ));
fa add44 (.x (r[33] ), .y (pp6[5]  ), .cin (c[38] ), .cout (c[44] ), .sum (r[34] ));
fa add45 (.x ( r[34]), .y (pp7[4]  ), .cin (c[39] ), .cout (c[45] ), .sum (r[35] ));
fa add46 (.x (r[35] ), .y (pp8[3]  ), .cin (c[40] ), .cout (c[46] ), .sum ( r[36]));
fa add47 (.x (r[36] ), .y (c[41]  ), .cin (c[42] ), .cout (c[47] ), .sum (result[10] ));

fa add48 (.x (pp5[7] ), .y ( pp6[6] ), .cin (c[43] ), .cout (c[48] ), .sum (r[37] ));
fa add49 (.x (r[37] ), .y ( pp7[5] ), .cin (c[44] ), .cout (c[49] ), .sum (r[38] ));
fa add50 (.x (r[38] ), .y (pp8[4]  ), .cin (c[45] ), .cout (c[50] ), .sum (r[39] ));
fa add51 (.x (r[39] ), .y (c[46]  ), .cin (c[47] ), .cout (c[51] ), .sum ( result[11]));

fa add52 (.x (pp6[7] ), .y (pp7[6]  ), .cin (c[48] ), .cout (c[52] ), .sum ( r[40]));
fa add53 (.x (r[40] ), .y ( pp8[5] ), .cin (c[49] ), .cout (c[53] ), .sum (r[41] ));
fa add54 (.x (r[41] ), .y ( c[50] ), .cin ( c[51] ), .cout (c[54] ), .sum (result[12] ));

fa add55 (.x (pp7[7] ), .y ( pp8[6] ), .cin (c[52] ), .cout (c[55] ), .sum (r[42] ));
fa add56 (.x (r[42] ), .y (c[53]  ), .cin (c[54] ), .cout (c[56] ), .sum (result[13] ));

fa add57 (.x (pp8[7] ), .y ( c[55] ), .cin (c[56] ), .cout (result[15] ), .sum (result[14] ));


	/* Multiplication result goes to HEX displays. */
	hex_digits h0(result[3:0], HEX0);
	hex_digits h1(result[7:4], HEX1);
	hex_digits h2(result[11:8], HEX2);
	hex_digits h3(result[15:12], HEX3);
	
endmodule 

module ha (x, y, carry, sum);
	input x;
	input y;
	output carry,sum;
	
	assign carry=x&y;
	assign sum=x^y;
	
endmodule


 module fa (x,y,cin,cout,sum);
	input x,y,cin;
	output cout,sum;
	
	wire a,b,c;
	
	assign a= x^y;
	assign b= x&y;
	assign c= a&cin;
		
	assign cout=c|b;
	
	assign sum= cin^a;
	
endmodule

