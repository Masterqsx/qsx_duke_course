library ieee;
use ieee.std_logic_1164.all;

entity decoder2_4 is
	port(SWITCH: in std_logic_vector(1 DOWNTO 0); HEX:out std_logic_vector(6 DOWNTO 0));
end decoder2_4;

architecture behavior of decoder2_4 is 
begin	
	process(SWITCH)
	begin	
		case SWITCH is
			when "00" => HEX<="0000001";
			when "01" => HEX<="1001111";
			when "10" => HEX<="0010010";
			when "11" => HEX<="0000110";
		end case;
	end process;
end behavior;
		