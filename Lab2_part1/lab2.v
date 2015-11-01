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
	/* Your multiplier circuit goes here. */	
	wire [7:0] plus, minus;
	wire [7:0] inf1,inf2,inf3,inf4,inf5,inf6,inf7,inf8;
	wire [7:0] c1,c2,c3,c4,c5,c6,c7,c8;
	wire [7:0] ftof1,ftof2,ftof3,ftof4,ftof5,ftof6,ftof7;
	
	wire [27:0] e;
	wire [35:0] c;
	wire [7:0] pp;
	
	booth b1(0, A[0], plus[0], minus[0]);
	booth b2(A[0],A[1], plus[1], minus[1]);
	booth b3(A[1], A[2], plus[2], minus[2]);
	booth b4(A[2], A[3], plus[3], minus[3]);
	booth b5(A[3], A[4], plus[4], minus[4]);
	booth b6(A[4], A[5], plus[5], minus[5]);
	booth b7(A[5], A[6], plus[6], minus[6]);
	booth b8(A[6], A[7], plus[7], minus[7]);
	
	onescomp oc01(B[0], plus[0], minus[0], inf1[0]);
	onescomp oc02(B[1], plus[0], minus[0], inf1[1]);
	onescomp oc03(B[2], plus[0], minus[0], inf1[2]);
	onescomp oc04(B[3], plus[0], minus[0], inf1[3]);
	onescomp oc05(B[4], plus[0], minus[0], inf1[4]);
	onescomp oc06(B[5], plus[0], minus[0], inf1[5]);
	onescomp oc07(B[6], plus[0], minus[0], inf1[6]);
	onescomp oc08(B[7], plus[0], minus[0], inf1[7]);
	
	fa add01 (0, inf1[0], minus[0],c1[0],result[0]);
	fa add02 (0, inf1[1], c1[0],c1[1],ftof1[0]);
	fa add03 (0, inf1[2], c1[1],c1[2],ftof1[1]);
	fa add04 (0, inf1[3], c1[2],c1[3],ftof1[2]);
	fa add05 (0, inf1[4], c1[3],c1[4],ftof1[3]);
	fa add06 (0, inf1[5], c1[4],c1[5],ftof1[4]);
	fa add07 (0, inf1[6], c1[5],c1[6],ftof1[5]);
	fa add08 (0, inf1[7], c1[6],c1[7],ftof1[6]);
	assign pp[0]=ftof1[6];
	
	onescomp oc11(B[0], plus[1], minus[1], inf2[0]);
	onescomp oc12(B[1], plus[1], minus[1], inf2[1]);
	onescomp oc13(B[2], plus[1], minus[1], inf2[2]);
	onescomp oc14(B[3], plus[1], minus[1], inf2[3]);
	onescomp oc15(B[4], plus[1], minus[1], inf2[4]);
	onescomp oc16(B[5], plus[1], minus[1], inf2[5]);
	onescomp oc17(B[6], plus[1], minus[1], inf2[6]);
	onescomp oc18(B[7], plus[1], minus[1], inf2[7]);
	
	fa add11 (ftof1[0], inf2[0], minus[1],c2[0],result[1]);
	fa add12 (ftof1[1], inf2[1], c2[0],c2[1],ftof2[0]);
	fa add13 (ftof1[2], inf2[2], c2[1],c2[2],ftof2[1]);
	fa add14 (ftof1[3], inf2[3], c2[2],c2[3],ftof2[2]);
	fa add15 (ftof1[4], inf2[4], c2[3],c2[4],ftof2[3]);
	fa add16 (ftof1[5], inf2[5], c2[4],c2[5],ftof2[4]);
	fa add17 (ftof1[6], inf2[6], c2[5],c2[6],ftof2[5]);
	
	//fa se1 (0,minus[0],c1[7],c[0],pp[0]);
	fa add18 (pp[0], inf2[7], c2[6],c2[7],ftof2[6]);
	assign pp[1]=c2[7];
	
	onescomp oc21(B[0], plus[2], minus[2], inf3[0]);
	onescomp oc22(B[1], plus[2], minus[2], inf3[1]);
	onescomp oc23(B[2], plus[2], minus[2], inf3[2]);
	onescomp oc24(B[3], plus[2], minus[2], inf3[3]);
	onescomp oc25(B[4], plus[2], minus[2], inf3[4]);
	onescomp oc26(B[5], plus[2], minus[2], inf3[5]);
	onescomp oc27(B[6], plus[2], minus[2], inf3[6]);
	onescomp oc28(B[7], plus[2], minus[2], inf3[7]);
	
	fa add21 (ftof2[0], inf3[0], minus[2],c3[0],result[2]);
	fa add22 (ftof2[1], inf3[1], c3[0],c3[1],ftof3[0]);
	fa add23 (ftof2[2], inf3[2], c3[1],c3[2],ftof3[1]);
	fa add24 (ftof2[3], inf3[3], c3[2],c3[3],ftof3[2]);
	fa add25 (ftof2[4], inf3[4], c3[3],c3[4],ftof3[3]);
	fa add26 (ftof2[5], inf3[5], c3[4],c3[5],ftof3[4]);
	fa add27 (ftof2[6], inf3[6], c3[5],c3[6],ftof3[5]);
	
	//fa se2(0,minus[0],c[0],c[1],e[0]);
	//fa se3(e[0],minus[1],c2[7],c[2],pp[1]);
	
	fa add28 (pp[1], inf3[7], c3[6],c3[7],ftof3[6]);
	assign pp[2]=c3[7];
	onescomp oc31(B[0], plus[3], minus[3], inf4[0]);
	onescomp oc32(B[1], plus[3], minus[3], inf4[1]);
	onescomp oc33(B[2], plus[3], minus[3], inf4[2]);
	onescomp oc34(B[3], plus[3], minus[3], inf4[3]);
	onescomp oc35(B[4], plus[3], minus[3], inf4[4]);
	onescomp oc36(B[5], plus[3], minus[3], inf4[5]);
	onescomp oc37(B[6], plus[3], minus[3], inf4[6]);
	onescomp oc38(B[7], plus[3], minus[3], inf4[7]);
	
	fa add31 (ftof3[0], inf4[0], minus[3],c4[0],result[3]);
	fa add32 (ftof3[1], inf4[1], c4[0],c4[1],ftof4[0]);
	fa add33 (ftof3[2], inf4[2], c4[1],c4[2],ftof4[1]);
	fa add34 (ftof3[3], inf4[3], c4[2],c4[3],ftof4[2]);
	fa add35 (ftof3[4], inf4[4], c4[3],c4[4],ftof4[3]);
	fa add36 (ftof3[5], inf4[5], c4[4],c4[5],ftof4[4]);
	fa add37 (ftof3[6], inf4[6], c4[5],c4[6],ftof4[5]);
	
	//fa se4 (0,minus[0],c[1],c[3],e[1]);
	//fa se5 (e[1],minus[1],c[2],c[4],e[2]);
	//fa se6 (e[2],minus[2],c3[7],c[5],pp[2]);
	
	fa add38 (pp[2], inf4[7], c4[6],c4[7],ftof4[6]);
	assign pp[3]=c4[7];
	onescomp oc41(B[0], plus[4], minus[4], inf5[0]);
	onescomp oc42(B[1], plus[4], minus[4], inf5[1]);
	onescomp oc43(B[2], plus[4], minus[4], inf5[2]);
	onescomp oc44(B[3], plus[4], minus[4], inf5[3]);
	onescomp oc45(B[4], plus[4], minus[4], inf5[4]);
	onescomp oc46(B[5], plus[4], minus[4], inf5[5]);
	onescomp oc47(B[6], plus[4], minus[4], inf5[6]);
	onescomp oc48(B[7], plus[4], minus[4], inf5[7]);
	
	fa add41 (ftof4[0], inf5[0], minus[4],c5[0],result[4]);
	fa add42 (ftof4[1], inf5[1], c5[0],c5[1],ftof5[0]);
	fa add43 (ftof4[2], inf5[2], c5[1],c5[2],ftof5[1]);
	fa add44 (ftof4[3], inf5[3], c5[2],c5[3],ftof5[2]);
	fa add45 (ftof4[4], inf5[4], c5[3],c5[4],ftof5[3]);
	fa add46 (ftof4[5], inf5[5], c5[4],c5[5],ftof5[4]);
	fa add47 (ftof4[6], inf5[6], c5[5],c5[6],ftof5[5]);
	
	//fa se7(0,minus[0],c[3],c[6],e[3]);
	//fa se8(e[3],minus[1],c[4],c[7],e[4]);
	//fa se9 (e[4],minus[2],c[5],c[8],e[5]);
	//fa se10 (e[5],minus[3],c4[7],c[9],pp[3]);
	
	fa add48 (pp[3], inf5[7], c5[6],c5[7],ftof5[6]);
	assign pp[4]=c5[7];
	onescomp oc51(B[0], plus[5], minus[5], inf6[0]);
	onescomp oc52(B[1], plus[5], minus[5], inf6[1]);
	onescomp oc53(B[2], plus[5], minus[5], inf6[2]);
	onescomp oc54(B[3], plus[5], minus[5], inf6[3]);
	onescomp oc55(B[4], plus[5], minus[5], inf6[4]);
	onescomp oc56(B[5], plus[5], minus[5], inf6[5]);
	onescomp oc57(B[6], plus[5], minus[5], inf6[6]);
	onescomp oc58(B[7], plus[5], minus[5], inf6[7]);
	
	fa add51 (ftof5[0], inf6[0], minus[5],c6[0],result[5]);
	fa add52 (ftof5[1], inf6[1], c6[0],c6[1],ftof6[0]);
	fa add53 (ftof5[2], inf6[2], c6[1],c6[2],ftof6[1]);
	fa add54 (ftof5[3], inf6[3], c6[2],c6[3],ftof6[2]);
	fa add55 (ftof5[4], inf6[4], c6[3],c6[4],ftof6[3]);
	fa add56 (ftof5[5], inf6[5], c6[4],c6[5],ftof6[4]);
	fa add57 (ftof5[6], inf6[6], c6[5],c6[6],ftof6[5]);
	
	//fa se11(0,minus[0],c[6],c[10],e[6]);
	//fa se12(e[6],minus[1],c[7],c[11],e[7]);
	//fa se13(e[7],minus[2],c[8],c[12],e[8]);
	//fa se14 (e[8],minus[3],c[9],c[13],e[9]);
	//fa se15 (e[9],minus[4],c5[7],c[14],pp[4]);
	
	fa add58 (pp[4], inf6[7], c6[6],c6[7],ftof6[6]);
	assign pp[5]=c6[7];
	onescomp oc61(B[0], plus[6], minus[6], inf7[0]);
	onescomp oc62(B[1], plus[6], minus[6], inf7[1]);
	onescomp oc63(B[2], plus[6], minus[6], inf7[2]);
	onescomp oc64(B[3], plus[6], minus[6], inf7[3]);
	onescomp oc65(B[4], plus[6], minus[6], inf7[4]);
	onescomp oc66(B[5], plus[6], minus[6], inf7[5]);
	onescomp oc67(B[6], plus[6], minus[6], inf7[6]);
	onescomp oc68(B[7], plus[6], minus[6], inf7[7]);
	
	fa add61 (ftof6[0], inf7[0], minus[6],c7[0],result[6]);
	fa add62 (ftof6[1], inf7[1], c7[0],c7[1],ftof7[0]);
	fa add63 (ftof6[2], inf7[2], c7[1],c7[2],ftof7[1]);
	fa add64 (ftof6[3], inf7[3], c7[2],c7[3],ftof7[2]);
	fa add65 (ftof6[4], inf7[4], c7[3],c7[4],ftof7[3]);
	fa add66 (ftof6[5], inf7[5], c7[4],c7[5],ftof7[4]);
	fa add67 (ftof6[6], inf7[6], c7[5],c7[6],ftof7[5]);
	
	//fa se16(0,minus[0],c[10],c[15],e[10]);
	//fa se17(e[10],minus[1],c[11],c[16],e[11]);
	//fa se18(e[11],minus[2],c[12],c[17],e[12]);
	//fa se19 (e[12],minus[3],c[13],c[18],e[13]);
	//fa se20 (e[13],minus[4],c[14],c[19],e[14]);
	//fa se21 (e[14],minus[5],c6[7],c[20],pp[5]);
	
	fa add68 (pp[5], inf7[7], c7[6],c7[7],ftof7[6]);
	assign pp[6]=c7[7];
	onescomp oc71(B[0], plus[7], minus[7], inf8[0]);
	onescomp oc72(B[1], plus[7], minus[7], inf8[1]);
	onescomp oc73(B[2], plus[7], minus[7], inf8[2]);
	onescomp oc74(B[3], plus[7], minus[7], inf8[3]);
	onescomp oc75(B[4], plus[7], minus[7], inf8[4]);
	onescomp oc76(B[5], plus[7], minus[7], inf8[5]);
	onescomp oc77(B[6], plus[7], minus[7], inf8[6]);
	onescomp oc78(B[7], plus[7], minus[7], inf8[7]);
	
	fa add71 (ftof7[0], inf8[0], minus[7],c8[0],result[7]);
	fa add72 (ftof7[1], 0, c8[0],c8[1],result[8]);
	fa add73 (ftof7[2], 0, c8[1],c8[2],result[9]);
	fa add74 (ftof7[3], inf8[3], c8[2],c8[3],result[10]);
	fa add75 (ftof7[4], inf8[4], c8[3],c8[4],result[11]);
	fa add76 (ftof7[5], inf8[5], c8[4],c8[5],result[12]);
	fa add77 (ftof7[6], inf8[6], c8[5],c8[6],result[13]);
	
	//fa se22(0,minus[0],c[15],c[21],e[15]);
	//fa se23(e[15],minus[1],c[16],c[22],e[16]);
	//fa se24(e[16],minus[2],c[17],c[23],e[17]);
	//fa se25 (e[17],minus[3],c[18],c[24],e[18]);
	//fa se26 (e[18],minus[4],c[19],c[25],e[19]);	
	//fa se27 (e[19],minus[5],c[20],c[26],e[20]);	
	//fa se28 (e[20],minus[6],c7[7],c[27],pp[6]);	

	fa add78 (pp[6], inf8[7], c8[6],c8[7],result[14]);
	assign pp[7]=c8[7];
//	fa se29(0,minus[0],c[21],c[28],e[21]);
//	fa se30(e[21],minus[1],c[22],c[29],e[22]);
//	fa se31(e[22],minus[2],c[23],c[30],e[23]);
//	fa se32 (e[23],minus[3],c[24],c[31],e[24]);
//	fa se33 (e[24],minus[4],c[25],c[32],e[25]);	
//	fa se34 (e[25],minus[5],c[26],c[33],e[26]);	
//	fa se35 (e[26],minus[6],c[27],c[34],e[27]);	
	fa se36 (e[27],minus[7],c8[7],c[35],result[15]);
	
	/* Multiplication result goes to HEX displays. */
	hex_digits h0(result[3:0], HEX0);
	hex_digits h1(result[7:4], HEX1);
	hex_digits h2(result[11:8], HEX2);
	hex_digits h3(result[15:12], HEX3);
	
endmodule

module booth(qi_i, qi, plus, minus);
  input qi_i, qi;
  output plus, minus;
  assign plus = qi_i&~qi;
  assign minus = ~qi_i&qi;
endmodule
 
 
module onescomp (in, plus, minus, out);
 input in, plus, minus;
 output out;
 assign out = (minus & ~in)|(plus & in);
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
