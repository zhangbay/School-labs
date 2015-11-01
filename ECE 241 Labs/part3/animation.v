// Animation

module animation
	(
		CLOCK_50,						//	On Board 50 MHz
		KEY,							//	Push Button[3:0]
		SW,
		VGA_CLK,   						//	VGA Clock
		VGA_HS,							//	VGA H_SYNC
		VGA_VS,							//	VGA V_SYNC
		VGA_BLANK,						//	VGA BLANK
		VGA_SYNC,						//	VGA SYNC
		VGA_R,   						//	VGA Red[9:0]
		VGA_G,	 						//	VGA Green[9:0]
		VGA_B   						//	VGA Blue[9:0]
	);

	input			CLOCK_50;				//	50 MHz
	input	[3:0]	KEY;					//	Button[3:0]
	input [17:0] SW;
	output			VGA_CLK;   				//	VGA Clock
	output			VGA_HS;					//	VGA H_SYNC
	output			VGA_VS;					//	VGA V_SYNC
	output			VGA_BLANK;				//	VGA BLANK
	output			VGA_SYNC;				//	VGA SYNC
	output	[9:0]	VGA_R;   				//	VGA Red[9:0]
	output	[9:0]	VGA_G;	 				//	VGA Green[9:0]
	output	[9:0]	VGA_B;   				//	VGA Blue[9:0]
	
	
	// Create the color, x, y and writeEn wires that are inputs to the controller.

	wire [2:0] color;
	wire [7:0] x;
	wire [6:0] y;
	wire writeEn;

	wire x_allow;
	wire y_allow;
	wire erase;
	wire Begin;
	
	reg [7:0] x_start = 0;
	reg [6:0] y_start = 0;
	
	wire [7:0] x_pos;
	wire [6:0] y_pos;
	assign Begin = SW[0];
	wire timing;
	
	DataPath m0(CLOCK_50,x_pos,y_pos,x_allow,y_allow,erase,x,y,color);
	FSM m1(Begin,erase,x_allow,y_allow,writeEn);
	TrainMovement m2(timing,Begin,~KEY[3],~KEY[2],~KEY[1],~KEY[0],x_start,y_start,x_pos,y_pos);
	Delay c0(CLOCK_50,timing);
	
	// Create an Instance of a VGA controller - there can be only one!
	// Define the number of colours as well as the initial background
	// image file (.MIF) for the controller.
	vga_adapter VGA(
			.resetn(1'b1),
			.clock(CLOCK_50),
			.colour(color),
			.x(x),
			.y(y),
			.plot(writeEn),
			/* Signals for the DAC to drive the monitor. */
		.VGA_R(VGA_R),
			.VGA_G(VGA_G),
			.VGA_B(VGA_B),
			.VGA_HS(VGA_HS),
			.VGA_VS(VGA_VS),
			.VGA_BLANK(VGA_BLANK),
			.VGA_SYNC(VGA_SYNC),
			.VGA_CLK(VGA_CLK));
		defparam VGA.RESOLUTION = "160x120";
		defparam VGA.MONOCHROME = "FALSE";
		defparam VGA.BITS_PER_COLOUR_CHANNEL = 1;
		defparam VGA.BACKGROUND_IMAGE = "trainbackground.mif";
			
	// Put your code here. Your code should produce signals x,y,color and writeEn
	// for the VGA controller, in addition to any other functionality your design may require.
	
	
endmodule

module DataPath(Clock, X_Loc,Y_Loc,X_Enable,Y_Enable,Erase,X_out,Y_out,C_out);

up(address, Clock, colour);
	wire [2:0] colour;
	input Clock, X_Enable,Y_Enable,Erase;
	input [7:0] X_Loc;
	input [6:0] Y_Loc;
	output reg [7:0] X_out;
	output reg [6:0] Y_out;
	output reg [2:0] C_out;
	reg [7:0]address=0;
	reg [7:0] X_Change=0;
	reg [6:0] Y_Change=0;

	
	always@(posedge Clock)
	begin
		if(X_Enable & Y_Enable)
			begin
			
				
			X_Change = X_Change + 1;
			
			
			if(X_Change == 12)
			begin
				X_Change = 0;
				Y_Change = Y_Change + 1;
				C_out=colour;
			end
	
			if(Y_Change == 12) 
			begin
				Y_Change = 0;
				C_out=colour;
			end		
			
	end
		
		if(X_Enable & Y_Enable & ~Erase)
		begin
			if(address<144) address=address+1;
			else address=0;
			X_out = X_Loc + (address+10)%12;
			Y_out = Y_Loc + (address+11)/12;
			C_out=colour;
		end
		else C_out=3'b000;
		
	end
endmodule

module DataPathLeft(Clock, X_Loc,Y_Loc,X_Enable,Y_Enable,Erase,X_out,Y_out,C_out);

left(address, Clock, colour);
	wire [2:0] colour;
	input Clock, X_Enable,Y_Enable,Erase;
	input [7:0] X_Loc;
	input [6:0] Y_Loc;
	output reg [7:0] X_out;
	output reg [6:0] Y_out;
	output reg [2:0] C_out;
	reg [7:0]address=0;
	reg [7:0] X_Change=0;
	reg [6:0] Y_Change=0;

	
	always@(posedge Clock)
	begin
		if(X_Enable & Y_Enable)
			begin
			
				
			X_Change = X_Change + 1;
			
			
			if(X_Change == 12)
			begin
				X_Change = 0;
				Y_Change = Y_Change + 1;
				C_out=colour;
			end
	
			if(Y_Change == 12) 
			begin
				Y_Change = 0;
				C_out=colour;
			end		
			
	end
		
		if(X_Enable & Y_Enable & ~Erase)
		begin
			if(address<144) address=address+1;
			else address=0;
			X_out = X_Loc + (address+10)%12;
			Y_out = Y_Loc + (address+11)/12;
			C_out=colour;
		end
		else C_out=3'b000;
		
	end
endmodule

module DataPathRight(Clock, X_Loc,Y_Loc,X_Enable,Y_Enable,Erase,X_out,Y_out,C_out);

tright(address, Clock, colour);
	wire [2:0] colour;
	input Clock, X_Enable,Y_Enable,Erase;
	input [7:0] X_Loc;
	input [6:0] Y_Loc;
	output reg [7:0] X_out;
	output reg [6:0] Y_out;
	output reg [2:0] C_out;
	reg [7:0]address=0;
	reg [7:0] X_Change=0;
	reg [6:0] Y_Change=0;

	
	always@(posedge Clock)
	begin
		if(X_Enable & Y_Enable)
			begin
			
				
			X_Change = X_Change + 1;
			
			
			if(X_Change == 12)
			begin
				X_Change = 0;
				Y_Change = Y_Change + 1;
				C_out=colour;
			end
	
			if(Y_Change == 12) 
			begin
				Y_Change = 0;
				C_out=colour;
			end		
			
	end
		
		if(X_Enable & Y_Enable & ~Erase)
		begin
			if(address<144) address=address+1;
			else address=0;
			X_out = X_Loc + (address+10)%12;
			Y_out = Y_Loc + (address+11)/12;
			C_out=colour;
		end
		else C_out=3'b000;
		
	end
endmodule

module DataPathDwn(Clock, X_Loc,Y_Loc,X_Enable,Y_Enable,Erase,X_out,Y_out,C_out);

datrain(address, Clock, colour);
	wire [2:0] colour;
	input Clock, X_Enable,Y_Enable,Erase;
	input [7:0] X_Loc;
	input [6:0] Y_Loc;
	output reg [7:0] X_out;
	output reg [6:0] Y_out;
	output reg [2:0] C_out;
	reg [7:0]address=0;
	reg [7:0] X_Change=0;
	reg [6:0] Y_Change=0;

	
	always@(posedge Clock)
	begin
		if(X_Enable & Y_Enable)
			begin
			
				
			X_Change = X_Change + 1;
			
			
			if(X_Change == 12)
			begin
				X_Change = 0;
				Y_Change = Y_Change + 1;
				C_out=colour;
			end
	
			if(Y_Change == 12) 
			begin
				Y_Change = 0;
				C_out=colour;
			end		
			
	end
		
		if(X_Enable & Y_Enable & ~Erase)
		begin
			if(address<144) address=address+1;
			else address=0;
			X_out = X_Loc + (address+10)%12;
			Y_out = Y_Loc + address/12;
			C_out=colour;
		end
		else C_out=3'b000;
		
	end
endmodule

module FSM(Start,Erase,X_Enable,Y_Enable,Write);
	input Start;
	integer k=0;
	output reg Erase, X_Enable,Y_Enable,Write;
	always@(*)
	begin
		if(Start || k==0)
		begin	
			Erase = 0;
			X_Enable = 1;
			Y_Enable = 1;
			Write = 1;
			k=1;
		end
		else if(k==1) 
		begin
			Erase = 1;
			X_Enable = 1;
			Y_Enable = 1;
			Write = 0;
			k=2;
			end
		else if(k==2)
		begin
			Erase = 1;
			X_Enable = 1;
			Y_Enable = 1;
			Write = 1;
			k=3;
		end
		else if(k==3)
		begin
			Erase = 0;
			X_Enable = 1;
			Y_Enable = 1;
			Write = 0;
			k=0;
		end
		
	end
endmodule

module TrainMovement(delay_clk,ena,up,down,left,right,curr_x,curr_y,location_x,location_y);
	input [7:0] curr_x;
	input [6:0] curr_y;
	input up,down,left,right,delay_clk,ena;
	
	output reg [7:0] location_x;
	output reg [6:0] location_y;
	
	reg [7:0] shift_x;
	reg [6:0] shift_y;
	always@(posedge delay_clk)
	begin
		if(ena)
		begin
			if(left) shift_x = shift_x -1;
			else if(right) shift_x = shift_x + 1;
			else if(up) shift_y = shift_y - 1;
			else if(down) shift_y = shift_y + 1;
		end
			
		location_x = curr_x + shift_x;
		location_y = curr_y + shift_y;
		
	end
endmodule	
module Delay(clk, out_time);
	input clk;
	output reg out_time;
	
	reg[25:0] cycle_count;
	
	always@(posedge clk)
	begin
		if(cycle_count == 833333)
		begin	
			out_time <= out_time +1;
			cycle_count <= 0;
		end
		
		else
		begin 
			cycle_count <= cycle_count +1;
			out_time <= 0;
		end
	end
endmodule 