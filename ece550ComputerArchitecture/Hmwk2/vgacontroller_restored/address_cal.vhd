library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity address_cal is
port(
	count_inputx : in std_logic_vector(9 downto 0);
	count_inputy : in std_logic_vector(9 downto 0);
	address_output1 : out std_logic_vector(19 downto 0)
	);
	
end entity;


architecture behavior of address_cal is

signal address: std_logic_vector(19 downto 0);
begin
address <= count_inputx + count_inputy*"1010000000" when (count_inputx>="0000000000") and (count_inputx<="1001111111") and (count_inputy>="0000000000") and (count_inputy<="0111011111") else
						 address;
address_output1<=address;

end architecture;