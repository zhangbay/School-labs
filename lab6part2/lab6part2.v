module lab6part2(SW,KEY,LEDR,LEDG);
	input [17:0]SW;
	input [2:0]KEY;
	output [17:0] LEDR;
	output [8:0] LEDG;
	wire [4:0]address;
	wire [15:0] din;
	assign resetn=KEY[0];
	assign mclock=KEY[1];
	assign pclock=KEY[2];
	//assign busWires=LEDR[15:0];
	assign done=LEDR[17];
	assign run=SW[17];
	
		wire [15:0] R0;
		wire [15:0] R1;
		wire [15:0] RA;
		wire [15:0] RG;
		wire [15:0] IR;
		wire [1:0] Tstep_Q;
	
	
	counter(mclock,resetn,address);
	inst_mem(address,mclock,din);
	l6(din,resetn,~KEY[2],SW[17],LEDR[17],LEDR[15:0], R0,R1,RA,RG, IR, Tstep_Q);
	
endmodule

module counter(mclock, resetn, address);
	input mclock, resetn;
	output reg [4:0] address;

	always@(negedge mclock or negedge resetn)
		if(~resetn) begin
			address<=5'b0;
		end
		else if (address==5'b01111)begin
			address<=5'b0;
		end
		else
			address<=address+1;
endmodule
		
		
module l6 (DIN, Resetn, Clock, Run, Done, BusWires, R0,R1,RA,RG, IR, Tstep_Q);
input [15:0] DIN;
input Resetn, Clock, Run;
output reg Done=0;
output reg[15:0] BusWires;
output [15:0] IR;
wire Clear=Done||(~Resetn);
output [1:0]  Tstep_Q;
wire [2:0]  I;
wire [7:0]  Xreg;
wire [7:0]  Yreg;
output [15:0]  R0;
output [15:0]  R1;
output [15:0]  RA;
output [15:0]  RG;
reg [2:0]  Rin=3'b000;
reg [2:0]  Rout=3'b000;
reg Dout;
reg Gout;
reg IRin;
reg Ain;
reg Gin;
reg addsub;
upcount Tstep (Clear, Clock, Tstep_Q);
assign I = IR[15:13];
dec3to8 decX(IR[12:10],1'b1,Xreg);
dec3to8 decY(IR[9:7],1'b1,Yreg);
always @(Clock)
 begin
  if(Dout)//loads din to bus
   BusWires=DIN;
  else if(Rout[0]==1)
   begin
	if(Gin==1)// add or sub
 	begin
  	if(addsub==0)//sub
   	BusWires=RA-R0;
  	else //add
   	BusWires=R0+RA;
  	end
	else//loads R0 to bus
	BusWires=R0;
   end
  else if(Rout[1]==1)
   begin
	if(Gin==1)// add or sub
 	begin
  	if(addsub==0)
   	BusWires=RA-R1;
  	else
   	BusWires=R1+RA;
 	end
	else
 	BusWires=R1;
   end
  else if(Gout==1)//loads RG to bus
   BusWires=RG;
  else
   BusWires=DIN;//default
 end
 
always @(Tstep_Q or I or Xreg or Yreg)
 begin
  case (Tstep_Q)
   2'b00://step0
	begin //set all signals to default values except IRin
 	Done= 1'b0;
 	IRin = 1'b1;
 	Rin[0]=0;
 	Rin[1]=0;
 	Ain=0;
 	Gin=0;
 	Rout[0]=0;
 	Rout[1]=0;
 	Dout=0;
 	Gout=0;
 	addsub=1;
	end
  2'b01: //define signals in time step 1
   begin
	IRin = 1'b0;//reset IRin
	case (I)
	3'b000://mv
   begin//set signals to default values
 	Ain=0;
 	Gin=0;
 	Dout=0;
 	Gout=0;
 	addsub=1;
  	if(Yreg==8'b01000000)//y=R1
   	begin
    	Rout[1]=1;
    	Rout[0]=0;
   	end
  	else if(Yreg==8'b10000000)//y=R0
   	begin
    	Rout[0]=1;
    	Rout[1]=0;
   	end
  	if(Xreg==8'b01000000)//x=R1
   	begin
    	Rin[1]=1;
    	Rin[0]=0;
   	end
  	else if(Xreg==8'b10000000)//x=R0
   	begin
    	Rin[0]=1;
    	Rin[1]=0;
   	end
 	Done= 1'b1;//finish mv
	end
   3'b001://mvi
	begin//set signals to default values
 	Ain=0;
 	Gin=0;
 	Gout=0;
 	addsub=1;
 	if(Xreg==8'b01000000)
  	begin
   	Rin[1]=1;
   	Rin[0]=0;
  	end
 	else if(Xreg==8'b10000000)
  	begin
   	Rin[0]=1;
   	Rin[1]=0;
  	end
	Dout=1;
	Done= 1'b1;//finish mvi
 end
  3'b010://add
   begin
	Dout=0;
	Gout=0;
	addsub=1;
	if(Xreg==8'b01000000)
 	begin
  	Rout[1]=1;
  	Rout[0]=0;
 	end
	else if(Xreg==8'b10000000)
 	begin
  	Rout[0]=1;
  	Rout[1]=0;
 	end
	Ain=1;
	Gin=0;
	Done=0;
   end
  3'b011://sub
   begin
	Dout=0;
	Gout=0;
	addsub=1;
	if(Xreg==8'b01000000)
 	begin
  	Rout[1]=1;
  	Rout[0]=0;
 	end
	else if(Xreg==8'b10000000)
 	begin
  	Rout[0]=1;
  	Rout[1]=0;
 	end
	Ain=1;
	Gin=0;
	Done=0;
   end
  endcase
  end
 2'b10: //define signals in time step 2
  begin
   case (I)
	3'b010:
 	begin
  	Dout=0;
  	Ain=0;
  	Gout=0;
  	addsub=1;
  	if(Yreg==8'b01000000)
   	begin
    	Rout[1]=1;
    	Rout[0]=0;
   	end
  	else if(Yreg==8'b10000000)
   	begin
    	Rout[0]=1;
    	Rout[1]=0;
   	end
  	Gin=1;
  	Done=0;
 	end
	3'b011:
 	begin
  	addsub=0;
  	Dout=0;
  	Ain=0;
  	Gout=0;
  	if(Yreg==8'b01000000)
   	begin
    	Rout[1]=1;
    	Rout[0]=0;
   	end
  	else if(Yreg==8'b10000000)
   	begin
    	Rout[0]=1;
    	Rout[1]=0;
   	end
   	Gin=1;
   	Done=0;
  	end
 	endcase
	end
   2'b11: //define signals in time step 3
	begin
 	Rout[0]=0;
 	Rout[1]=0;
 	Dout=0;
 	addsub=1;
 	case (I)
  	3'b010:
   	begin
   	Dout=0;
   	Ain=0;
   	Gin=0;
   	if(Xreg==8'b01000000)
    	begin
     	Rin[1]=1;
     	Rin[0]=0;
    	end
   	else if(Xreg==8'b10000000)
    	begin
     	Rin[0]=1;
     	Rin[1]=0;
    	end
    	Gout=1;
    	Done=1;
   	end
 	3'b011:
  	begin
   	Dout=0;
   	Ain=0;
   	Gin=0;
    	if(Xreg==8'b01000000)
     	begin
      	Rin[1]=1;
      	Rin[0]=0;
     	end
    	else if(Xreg==8'b10000000)
     	begin
      	Rin[0]=1;
      	Rin[1]=0;
     	end
   	Gout=1;
   	Done=1;
  	end
 	endcase
	end
   endcase
  end
regn reg_IR (BusWires, IRin, Clock,IR);
regn reg_A (BusWires, Ain, Clock,RA);
regn reg_G (BusWires, Gin, Clock,RG);
regn reg_0 (BusWires, Rin[0], Clock, R0);
regn reg_1 (BusWires, Rin[1], Clock, R1);
endmodule

module upcount(Clear, Clock, Q);
 input Clear, Clock;
 output [1:0] Q;
 reg [1:0] Q;
 always @(posedge Clock)
 if (Clear)
 Q <= 2'b0;
 else
 Q <= Q + 1'b1;
endmodule
module dec3to8(W, En, Y);
 input [2:0] W;
 input En;
 output [0:7] Y;
 reg [0:7] Y;
 always @(W or En)
 begin
 if (En == 1)
 case (W)
 3'b000: Y = 8'b10000000;
 3'b001: Y = 8'b01000000;
 3'b010: Y = 8'b00100000;
 3'b011: Y = 8'b00010000;
 3'b100: Y = 8'b00001000;
 3'b101: Y = 8'b00000100;
 3'b110: Y = 8'b00000010;
 3'b111: Y = 8'b00000001;
 endcase
 else
 Y = 8'b00000000;
 end
endmodule
module regn(R, Rin, Clock, Q);
 parameter n = 16;
 input [n-1:0] R;
 input Rin, Clock;
 output [n-1:0] Q;
 reg [n-1:0] Q;
 always @(posedge Clock)
 if (Rin)
 Q <= R;
endmodule



		