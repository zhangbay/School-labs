library verilog;
use verilog.vl_types.all;
entity lab6part3_vlg_check_tst is
    port(
        Addr            : in     vl_logic_vector(15 downto 0);
        BusWires        : in     vl_logic_vector(15 downto 0);
        IR              : in     vl_logic_vector(15 downto 0);
        LEDG            : in     vl_logic_vector(8 downto 0);
        LEDR            : in     vl_logic_vector(17 downto 0);
        R0              : in     vl_logic_vector(15 downto 0);
        R1              : in     vl_logic_vector(15 downto 0);
        R7              : in     vl_logic_vector(15 downto 0);
        RA              : in     vl_logic_vector(15 downto 0);
        RG              : in     vl_logic_vector(15 downto 0);
        sampler_rx      : in     vl_logic
    );
end lab6part3_vlg_check_tst;
