library verilog;
use verilog.vl_types.all;
entity lab6part3 is
    port(
        KEY             : in     vl_logic_vector(3 downto 0);
        SW              : in     vl_logic_vector(17 downto 0);
        LEDR            : out    vl_logic_vector(17 downto 0);
        LEDG            : out    vl_logic_vector(8 downto 0);
        BusWires        : out    vl_logic_vector(15 downto 0);
        R0              : out    vl_logic_vector(15 downto 0);
        R1              : out    vl_logic_vector(15 downto 0);
        RA              : out    vl_logic_vector(15 downto 0);
        RG              : out    vl_logic_vector(15 downto 0);
        R7              : out    vl_logic_vector(15 downto 0);
        IR              : out    vl_logic_vector(15 downto 0);
        Addr            : out    vl_logic_vector(15 downto 0)
    );
end lab6part3;
