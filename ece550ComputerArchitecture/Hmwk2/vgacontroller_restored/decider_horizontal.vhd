library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity decider_horizontal is
port(
	count_input : in std_logic_vector (9 downto 0);
	front_porch : out std_logic;
	sync_pulse  : out std_logic;
	back_porch  : out std_logic);
end entity;

architecture behavior of decider_horizontal is

begin

front_porch <= '1' when ((count_input>="1010000000") and (count_input<="1010001111")) else
					'0';
				
sync_pulse  <= '1' when ((count_input>="1010010000") and (count_input<="1011101111")) else
					'0';
					
back_porch  <= '1' when ((count_input>="1011110000") and (count_input<="1100011111")) else
					'0';

end behavior;