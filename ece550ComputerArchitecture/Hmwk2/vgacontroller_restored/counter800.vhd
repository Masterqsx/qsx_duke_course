library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity counter800 is
port (
		clk          : in std_logic;
		rst			 : in std_logic :='0';
		count_number : out std_logic_vector (9 downto 0)
);
end counter800;

architecture behavior of counter800 is
component dff
port (
	clk : in std_logic;
	d : in std_logic;
	clrn : in std_logic;
	prn : in std_logic;
	q : out std_logic);
end component dff;

signal count_n: std_logic_vector (9 downto 0) :="0000000000";
signal count_a: std_logic_vector (9 downto 0) :="0000000000";
begin
	count_a<= "0000000000" when count_n="1100011111" else	count_n+1;
	G1: for i in 9 downto 0 generate
		dffx: dff port map (
				clk => clk,
				clrn => not(rst),
				prn => '1',
				d => count_a(i),
				q => count_n(i)
				);
	end generate G1;

	count_number<=count_n;	
end;					