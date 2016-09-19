library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;

entity stage1 is
port(
		clk: in std_logic;
		rst: in std_logic;
		address_output: out std_logic_vector (15 downto 0);
		front_porchx : out std_logic;
		sync_pulsex  : out std_logic;
		back_porchx  : out std_logic;
		front_porchy : out std_logic;
		sync_pulsey  : out std_logic;
		back_porchy  : out std_logic;
		ysync        : out std_logic;
		xsync        : out std_logic
		);
end entity;

architecture behavior of stage1 is

component counter524
port (
		clk          : in std_logic;
		rst			 : in std_logic :='0';
		count_number : out std_logic_vector (9 downto 0)
);
end component;

component counter800
port (
		clk          : in std_logic;
		rst			 : in std_logic :='0';
		count_number : out std_logic_vector (9 downto 0)
);
end component;

component address_cal
port(
		count_inputx : in std_logic_vector(9 downto 0);
		count_inputy : in std_logic_vector(9 downto 0);
		address_output1 : out std_logic_vector(19 downto 0)
);
end component;

component decider_vertical 
port(
	count_input : in std_logic_vector (9 downto 0);
	front_porch : out std_logic;
	sync_pulse  : out std_logic;
	back_porch  : out std_logic
);
end component;

component decider_horizontal
port(
	count_input : in std_logic_vector (9 downto 0);
	front_porch : out std_logic;
	sync_pulse  : out std_logic;
	back_porch  : out std_logic
);
end component;

signal counterx :std_logic_vector (9 downto 0);
signal countery :std_logic_vector (9 downto 0);
signal hsync :std_logic;
signal vsync :std_logic;

begin

	u1: counter524
		port map(clk=>clk,rst=>rst,count_number=>countery);
	
	u2: counter800	
		port map(clk=>clk,rst=>rst,count_number=>counterx);
	
	u3: decider_horizontal
		port map(count_input=>counterx,front_porch=>front_porchx,sync_pulse=>hsync,back_porch=>back_porchx);
		
	u4: decider_vertical
		port map(count_input=>countery,front_porch=>front_porchy,sync_pulse=>vsync,back_porch=>back_porchy);
	
	u5: address_cal
		port map(count_inputx=>counterx,count_inputy=>countery,address_output1(18 downto 3)=>address_output);
	
	xsync<=not(hsync);
	ysync<=not(vsync);
	sync_pulsex<=hsync;
	sync_pulsey<=vsync;
end;

	