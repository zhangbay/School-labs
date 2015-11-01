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
	input	[1:0]	KEY;		
	input	[15:0]	SW;		//	Button[3:0]
	output			VGA_CLK;   				//	VGA Clock
	output			VGA_HS;					//	VGA H_SYNC
	output			VGA_VS;					//	VGA V_SYNC
	output			VGA_BLANK;				//	VGA BLANK
	output			VGA_SYNC;				//	VGA SYNC
	output	[9:0]	VGA_R;   				//	VGA Red[9:0]
	output	[9:0]	VGA_G;	 				//	VGA Green[9:0]
	output	[9:0]	VGA_B;   				//	VGA Blue[9:0]
	
	wire resetn;
	assign resetn = ~KEY[0];
	
	// Create the color, x, y and writeEn wires that are inputs to the controller.

	wire [2:0] color;
	wire [7:0] x;
	wire [6:0] y;
	wire writeEn;
	
	assign x=SW[7:0];
	assign y=SW[15:8];
	assign writeEn = ~KEY[1];
	
	wire [7:0] Xo;
	wire [6:0] Yo;

	datapath (x,y,resetn, CLOCK_50,writeEn, Xo, Yo, color);
	// Create an Instance of a VGA controller - there can be only one!
	// Define the number of colours as well as the initial background
	// image file (.MIF) for the controller.
	vga_adapter VGA(
			.resetn(resetn),
			.clock(CLOCK_50),
			.colour(color),
			.x(Xo),
			.y(Yo),
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
		defparam VGA.BACKGROUND_IMAGE = "<put your background image here>";
			
	// Put your code here. Your code should produce signals x,y,color and writeEn
	// for the VGA controller, in addition to any other functionality your design may require.
	
	
endmodule 

module datapath (X_i, Y_i, resetn, clock, enable, X_o, Y_o, color);
input [7:0]X_i;
input [6:0]Y_i;
input resetn;
input clock;
input enable;
output reg [2:0] color;
output reg [7:0]X_o;
output reg [7:0]Y_o;

reg [4:0] counterx=0;
reg [4:0] countery=0;
reg [7:0] address=0;





rom(address,clock,colorrr);

always@ (posedge clock)
begin
if(!resetn)
	begin
	X_o=0;
	Y_o=0;
	
	counterx=0;
	countery=0;
	

	end
else 
	begin
		if(counterx<16)
			begin
				X_o = X_i+counterx;
				counterx=counterx+1;
				if(address<255)
					address=address+1;
				address<=counterx;
		
			end	
		if(countery<16)
			begin
				countery=countery+1;
				address<=countery;
				counterx<=0;
			end
		if(countery==16)
			begin
				countery=0;
				address<=0;
			end
		
	end
end

endmodule

