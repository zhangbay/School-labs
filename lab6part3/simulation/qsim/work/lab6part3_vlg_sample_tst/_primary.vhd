library verilog;
use verilog.vl_types.all;
entity lab6part3_vlg_sample_tst is
    port(
        KEY             : in     vl_logic_vector(3 downto 0);
        SW              : in     vl_logic_vector(17 downto 0);
        sampler_tx      : out    vl_logic
    );
end lab6part3_vlg_sample_tst;
