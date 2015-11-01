module sketch
	(
		CLOCK_50,						//	On Board 50 MHz
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
	
	wire resetn;
	assign resetn = KEY[0];
	
	// Create the color, x, y and writeEn wires that are inputs to the controller.
	wire [2:0] color;
	wire [7:0] x;
	wire [6:0] y;
	wire [2:0] controlX;
	wire [2:0] controlY;
	reg writeEn;
	reg [2:0] tocolor;
	//assign writeEn	= ~KEY[1];
	
	reg[7:0] x_;
	reg[6:0] y_;
	
	assign x=x_;
	assign y=y_;
	
	// Create an Instance of a VGA controller - there can be only one!
	// Define the number of colours as well as the initial background
	// image file (.MIF) for the controller.
	vga_adapter VGA(
			.resetn(resetn),
			.clock(CLOCK_50),
			.colour(tocolor),
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
		defparam VGA.BACKGROUND_IMAGE = "display.mif]";
			
	// Put your code here. Your code should produce signals x,y,color and writeEn
	// for the VGA controller, in addition to any other functionality your design may require.
	FSM1 inst0(KEY[1], CLOCK_50,resetn,tobegin );
	
	
	reg [4:0]count;
  reg [14:0]rescount;
  integer line;
integer resline;  
	always@(posedge CLOCK_50 )
		begin
		if (!tobegin)begin
			tocolor = 3'b0;
			//fakeenable =1;
			if(rescount>0 && rescount<=19200)
			begin
				writeEn=1;
				x_ = rescount-160*resline;
				y_ = resline;				
			end
			rescount <= rescount +1;  
			resline <= rescount/160; 
			
			if(rescount==19201)
				writeEn=0;
			
			end	
		
		else begin
			//fakeenable = ~KEY[1];
			tocolor[2:0] = SW[17:15];
			if(count>0 && count<=25)
			begin
				writeEn=1;
				x_ = SW[7:0]+count-5*line;
				y_ = SW[14:8]+line;				
			end
			count <= count +1;  
			line <= count/5;		
			
			if(count==26)
				writeEn=0;
			
			end
 end   
endmodule
	
module FSM1(input start, input clock,input reset,output reg beginout);
parameter [2:0] A=3'b000, B=3'b001, C=3'b010, D=3'b011, E=3'b110, F=3'b111;
		
	reg [2:0] pstate, state;
	 
	 
always@(*)
		begin				
				case(pstate)
				A: if(!start)				 
						begin								
								beginout=1;
								state=B;
						end
						
					else if(!reset)
						begin
								beginout=0;
								state=A;
						end
						
					else 
						begin
								beginout=0;
								state=A;							
						end
				B: if(reset) 
						begin 
									beginout=1;
									state=B;
						end
					else
						begin
									beginout=0;
									state=A;
						end
				endcase
			end	 
	
always@(posedge clock, negedge reset)
		
		if(!reset)
			pstate=A;
		else
			pstate=state;		
endmodule