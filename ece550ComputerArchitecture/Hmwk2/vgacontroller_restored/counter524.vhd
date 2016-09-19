library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity counter524 is
port (
		clk          : in std_logic;
		rst			 : in std_logic :='0';
		count_number : out std_logic_vector (9 downto 0)
);
end counter524;

architecture behavior of counter524 is
component dff
port (
	clk : in std_logic;
	d : in std_logic;
	clrn : in std_logic;
	prn : in std_logic;
	q : out std_logic);
end component dff;

component counter800
port (
		clk          : in std_logic;
		rst			 : in std_logic :='0';
		count_number : out std_logic_vector (9 downto 0)
);
end component;

signal count_n: std_logic_vector (9 downto 0) :="0000000000";
signal count_a: std_logic_vector (9 downto 0) :="0000000000";
signal count  : std_logic_vector (9 downto 0) :="0000000000";
begin
	u1: counter800
		port map(clk=>clk, rst=>rst, count_number=>count);
	
	
	count_a<= "0000000000" when count_n="1000001011" and count ="1100011111" else	
				 count_n+1    when count  ="1100011111" else
				 count_n;
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