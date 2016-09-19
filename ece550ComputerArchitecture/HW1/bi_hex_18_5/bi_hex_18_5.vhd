library ieee;
use ieee.std_logic_1164.all;

entity bi_hex_18_5 is
	port(SWITCH0: in std_logic_vector(3 DOWNTO 0);
		  SWITCH1: in std_logic_vector(3 DOWNTO 0);
		  SWITCH2: in std_logic_vector(3 DOWNTO 0);
		  SWITCH3: in std_logic_vector(3 DOWNTO 0);
		  SWITCH4: in std_logic_vector(1 DOWNTO 0);
		  HEX0: out std_logic_vector(6 DOWNTO 0);
		  HEX1: out std_logic_vector(6 DOWNTO 0);
		  HEX2: out std_logic_vector(6 DOWNTO 0);
		  HEX3: out std_logic_vector(6 DOWNTO 0);
		  HEX4: out std_logic_vector(6 DOWNTO 0)
		  );
end bi_hex_18_5;

architecture structure of bi_hex_18_5 is
		
		component decoder4_7
			port(SWITCH: in std_logic_vector(3 DOWNTO 0); 
		        HEX:out std_logic_vector(6 DOWNTO 0) 
			    );
		end component;
		component decoder2_4
			port(SWITCH: in std_logic_vector(1 DOWNTO 0); 
		        HEX:out std_logic_vector(6 DOWNTO 0) 
			    );
		end component;


begin
		U0: decoder4_7
				port map (SWITCH => SWITCH0, HEX => HEX0);
		U1: decoder4_7
				port map (SWITCH => SWITCH1, HEX => HEX1);
		U2: decoder4_7
				port map (SWITCH => SWITCH2, HEX => HEX2);
		U3: decoder4_7
				port map (SWITCH => SWITCH3, HEX => HEX3);
		U4: decoder2_4
				port map (SWITCH => SWITCH4, HEX => HEX4);
end structure;
		