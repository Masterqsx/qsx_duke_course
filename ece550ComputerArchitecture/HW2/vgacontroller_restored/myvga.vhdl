library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
library altera;
use altera.altera_primitives_components.all;

entity myvga is
port (
    clk     : in std_logic;
    rst     : in std_logic;
    red     : out std_logic_vector (7 downto 0);
    green   : out std_logic_vector (7 downto 0);
    blue    : out std_logic_vector (7 downto 0);
    blank   : out std_logic;
    hsync   : out std_logic;
    vsync   : out std_logic);
end myvga;


architecture basic of myvga is

component vmem is
	port (
		address		: in std_logic_vector  (15 downto 0);
		clock		: in std_logic;
		q		    : out std_logic_vector (8 downto 0));
end component;

component stage1 
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
end component;

component rgb_transfer
	port(
		color_input : in std_logic_vector (8 downto 0);
		front_porchx : in std_logic;
		sync_pulsex  : in std_logic;
		back_porchx  : in std_logic;
		front_porchy : in std_logic;
		sync_pulsey  : in std_logic;
		back_porchy  : in std_logic;
		red     : out std_logic_vector (7 downto 0);
		green   : out std_logic_vector (7 downto 0);
		blue    : out std_logic_vector (7 downto 0)
		);
end component;

signal addressline: std_logic_vector(15 downto 0);
signal front_porchx :  std_logic;
signal sync_pulsex  :  std_logic;
signal back_porchx  :  std_logic;
signal front_porchy :  std_logic;
signal sync_pulsey  :  std_logic;
signal back_porchy  :  std_logic;
signal rgbline      :  std_logic_vector(8 downto 0);

begin

	s1: stage1
		port map(clk=>clk, rst=>rst, address_output=>addressline, front_porchx=>front_porchx, sync_pulsex=>sync_pulsex, back_porchx=>back_porchx, front_porchy=>front_porchy, sync_pulsey=>sync_pulsey, back_porchy=>back_porchy, xsync=>hsync, ysync=>vsync);
	
	s2: vmem
		port map(clock=>clk, address=>addressline,q=>rgbline);
	
	s3: rgb_transfer
		port map(color_input=>rgbline, red=>red, green=>green, blue=>blue, front_porchx=>front_porchx, sync_pulsex=>sync_pulsex, back_porchx=>back_porchx, front_porchy=>front_porchy, sync_pulsey=>sync_pulsey, back_porchy=>back_porchy);



   blank<='1'; 






end basic;