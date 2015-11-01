// Etch-and-sketch
module sketch
	(	CLOCK_50,						//	On Board 50 MHz
		KEY,							//	Push Button[3:0]
		SW,								//	DPDT Switch[17:0]
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
	input	[17:0]	SW;						//	Switches[0:0]
	output			VGA_CLK;   				//	VGA Clock
	output			VGA_HS;					//	VGA H_SYNC
	output			VGA_VS;					//	VGA V_SYNC
	output			VGA_BLANK;				//	VGA BLANK
	output			VGA_SYNC;				//	VGA SYNC
	output	[9:0]	VGA_R;   				//	VGA Red[9:0]
	output	[9:0]	VGA_G;	 				//	VGA Green[9:0]
	output	[9:0]	VGA_B;   				//	VGA Blue[9:0]
	
 wire resetn, plot, enable;
 wire [2:0] color;
 wire [7:0] x;
 wire [6:0] y;
 reg [7:0] x_coord;
 reg [6:0] y_coord;
 reg [2:0] clreg;
 reg fakeenable;
 assign resetn = KEY[0];
 //assign enable = ~KEY[1];
 // Further assignments go here...
 //assign x = SW[7:0];
 //assign y = SW[14:8];
 assign color = clreg;
 
 assign x = x_coord;
 assign y = y_coord;
 assign enable = fakeenable;
 	// Create an Instance of a VGA controller - there can be only one!
	// Define the number of colours as well as the initial background
	// image file (.MIF) for the controller.
	vga_adapter VGA(
			.resetn(resetn),
			.clock(CLOCK_50),
			.colour(color),
			.x(x),
			.y(y),
			.plot(enable),
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
		defparam VGA.BACKGROUND_IMAGE = "";			
	// Put your code here. Your code should produce signals x,y,color and writeEn
	// for the VGA controller, in addition to any other functionality your design may require.
	
  reg [4:0]count;
  reg [14:0]rescount;
  integer line;
 integer resline;  
	always@(posedge CLOCK_50 )
		begin
		if (resetn == 0)begin
			clreg = 0;
			fakeenable =1;
			if(rescount>0 && rescount<=19200)
			begin
				x_coord = rescount-160*resline;
				y_coord = resline;				
			end
			rescount <= rescount +1;  
			resline <= rescount/160; 
			
			end	
		
		else begin
			fakeenable = ~KEY[1];
			clreg = SW[17:15];
			if(count>0 && count<=25)
			begin
				x_coord = SW[7:0]+count-5*line;
				y_coord = SW[14:8]+line;				
			end
			count <= count +1;  
			line <= count/5;		end
 end   
endmodule