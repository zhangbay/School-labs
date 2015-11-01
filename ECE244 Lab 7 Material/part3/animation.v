// Animation

module animation
	(
		CLOCK_50,						//	On Board 50 MHz
		KEY,							//	Push Button[3:0]
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
	output			VGA_CLK;   				//	VGA Clock
	output			VGA_HS;					//	VGA H_SYNC
	output			VGA_VS;					//	VGA V_SYNC
	output			VGA_BLANK;				//	VGA BLANK
	output			VGA_SYNC;				//	VGA SYNC
	output	[9:0]	VGA_R;   				//	VGA Red[9:0]
	output	[9:0]	VGA_G;	 				//	VGA Green[9:0]
	output	[9:0]	VGA_B;   				//	VGA Blue[9:0]
	
	wire resetn;
	assign resetn = KEY[0];
	
	// Create the color, x, y and writeEn wires that are inputs to the controller.

	wire [2:0] color;
	wire [7:0] x;
	wire [6:0] y;
	wire writeEn;
	
	reg [7:0] x_location;
	reg [6:0] y_location;
	reg [2:0] color_to_add;
	reg enable_write;
	
	reg [7:0] prev_x;
	reg [6:0] prev_y;
	
	wire [3:0]newx;
	wire [3:0]newy;
	
	reg load;
	reg count;
	reg erase, draw;
	always@(posedge CLOCK_50)
	begin
		if(resetn == 0)
		begin
			load = 0;
			enable_write = 1; 
			color_to_add = 0;
			if(y_location == 120)
			begin
				x_location <= 0;
				y_location <= 0;
			end
			else if(x_location == 160)
			begin
				y_location <= y_location + 1;
				x_location <= 0;
			end
			else 
				x_location <= x_location + 1;
		end
		else 
			begin
			x_location <= x_location + newx;
			y_location <= y_location + newy;
			color_to_add <= color_x;
			end
	end
	
	assign x = x_location;
	assign y = y_location;
	assign color = color_to_add;
	assign writeEn = enable_write;

	// Create an Instance of a VGA controller - there can be only one!
	// Define the number of colours as well as the initial background
	// image file (.MIF) for the controller.
	vga_adapter VGA(
			.resetn(resetn),
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
		defparam VGA.BACKGROUND_IMAGE = "";
			
	// Put your code here. Your code should produce signals x,y,color and writeEn
	// for the VGA controller, in addition to any other functionality your design may require.
counter(KEY[0],KEY[1],CLOCK_50, newx, newy, color_x);
wire [2:0] color_x;	
endmodule

module counter(input erase, input draw, input clock,output reg [3:0]x_z, output reg [3:0]y_z, output reg [2:0] colour);

TRAIN bsthisshit(address_loc,clock,data_loc,rean,q);
reg [7:0] address_loc;
reg [7:0] data_loc;
reg rean;
reg [7:0] q_loc;
reg enable = 1;
wire q;
assign q = q_loc;
always@(posedge clock)
	begin
	rean <= 1;
	if(enable)
	if(erase==0)
		colour=3'b0;
	if(draw==1)
		colour = q_loc;
		
	if(y_z == 16)
	begin
		address_loc <= 0;
		data_loc <= 0;
		q_loc<=0;
		rean <= 0;
		x_z <= x_z;
		y_z <= y_z;
		enable <= 0;
	end
	else if(x_z == 16)
	begin
		x_z<= 0;
		y_z<= y_z + 1;
	end
	else
		x_z<= x_z + 1;
end


endmodule 

