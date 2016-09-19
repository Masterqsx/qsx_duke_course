---You should not need to edit this file!!!---
---Edit myvga.vhdl---

library IEEE;
use IEEE.std_logic_1164.all;

entity vgacontroller is
  port (
    CLOCK_50  : in std_logic;
    KEY       : in std_logic_vector (3 downto 0);
    VGA_R     : out std_logic_vector (7 downto 0);
    VGA_G     : out std_logic_vector (7 downto 0);
    VGA_B     : out std_logic_vector (7 downto 0);
    VGA_CLK   : out std_logic;
    VGA_BLANK : out std_logic;
    VGA_HS    : out std_logic;
    VGA_VS    : out std_logic;
    VGA_SYNC  : out std_logic);
end entity;

architecture basic of vgacontroller is
component myvga is
port (
    clk     : in std_logic;
    rst     : in std_logic;
    red     : out std_logic_vector (7 downto 0);
    green   : out std_logic_vector (7 downto 0);
    blue    : out std_logic_vector (7 downto 0);
    blank   : out std_logic;
    hsync   : out std_logic;
    vsync   : out std_logic);
end component;
component pll is
		port (	inclk0	: in std_logic;
				c0: out std_logic;
				c1 : out std_logic);
end component;

signal vclk : std_logic;
signal hsyncx: std_logic;
signal vsyncx: std_logic;
signal notrst : std_logic; --realy rst since the button is active low
begin
notrst <= not KEY(0);
pll0 : pll port map (
   inclk0 => CLOCK_50,
   c0 => vclk,
   c1 => VGA_CLK);

myvga0: myvga port map (
   clk => vclk,
   rst => notrst,
   red => VGA_R,
   green => VGA_G,
   blue => VGA_B,
   blank => VGA_BLANK,
   hsync => VGA_HS,
   vsync => VGA_VS);

VGA_SYNC <= '0';

end;


