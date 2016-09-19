-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 32-bit"
-- VERSION "Version 13.0.0 Build 156 04/24/2013 SJ Full Version"

-- DATE "09/06/2015 22:55:56"

-- 
-- Device: Altera EP4CE115F29C7 Package FBGA780
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	bi_hex_18_5 IS
    PORT (
	SWITCH0 : IN std_logic_vector(3 DOWNTO 0);
	SWITCH1 : IN std_logic_vector(3 DOWNTO 0);
	SWITCH2 : IN std_logic_vector(3 DOWNTO 0);
	SWITCH3 : IN std_logic_vector(3 DOWNTO 0);
	SWITCH4 : IN std_logic_vector(1 DOWNTO 0);
	HEX0 : OUT std_logic_vector(6 DOWNTO 0);
	HEX1 : OUT std_logic_vector(6 DOWNTO 0);
	HEX2 : OUT std_logic_vector(6 DOWNTO 0);
	HEX3 : OUT std_logic_vector(6 DOWNTO 0);
	HEX4 : OUT std_logic_vector(6 DOWNTO 0)
	);
END bi_hex_18_5;

-- Design Ports Information
-- HEX0[0]	=>  Location: PIN_H22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0[1]	=>  Location: PIN_J22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0[2]	=>  Location: PIN_L25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0[3]	=>  Location: PIN_L26,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0[4]	=>  Location: PIN_E17,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0[5]	=>  Location: PIN_F22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0[6]	=>  Location: PIN_G18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX1[0]	=>  Location: PIN_U24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX1[1]	=>  Location: PIN_U23,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX1[2]	=>  Location: PIN_W25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX1[3]	=>  Location: PIN_W22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX1[4]	=>  Location: PIN_W21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX1[5]	=>  Location: PIN_Y22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX1[6]	=>  Location: PIN_M24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX2[0]	=>  Location: PIN_W28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX2[1]	=>  Location: PIN_W27,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX2[2]	=>  Location: PIN_Y26,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX2[3]	=>  Location: PIN_W26,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX2[4]	=>  Location: PIN_Y25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX2[5]	=>  Location: PIN_AA26,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX2[6]	=>  Location: PIN_AA25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX3[0]	=>  Location: PIN_Y19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX3[1]	=>  Location: PIN_AF23,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX3[2]	=>  Location: PIN_AD24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX3[3]	=>  Location: PIN_AA21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX3[4]	=>  Location: PIN_AB20,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX3[5]	=>  Location: PIN_U21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX3[6]	=>  Location: PIN_V21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX4[0]	=>  Location: PIN_AE18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX4[1]	=>  Location: PIN_AF19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX4[2]	=>  Location: PIN_AE19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX4[3]	=>  Location: PIN_AH21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX4[4]	=>  Location: PIN_AG21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX4[5]	=>  Location: PIN_AA19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX4[6]	=>  Location: PIN_AB19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH0[0]	=>  Location: PIN_AB28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH0[1]	=>  Location: PIN_AC28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH0[2]	=>  Location: PIN_AC27,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH0[3]	=>  Location: PIN_AD27,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH1[0]	=>  Location: PIN_AB27,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH1[1]	=>  Location: PIN_AC26,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH1[2]	=>  Location: PIN_AD26,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH1[3]	=>  Location: PIN_AB26,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH2[0]	=>  Location: PIN_AC25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH2[1]	=>  Location: PIN_AB25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH2[2]	=>  Location: PIN_AC24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH2[3]	=>  Location: PIN_AB24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH3[0]	=>  Location: PIN_AB23,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH3[1]	=>  Location: PIN_AA24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH3[2]	=>  Location: PIN_AA23,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH3[3]	=>  Location: PIN_AA22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH4[1]	=>  Location: PIN_Y23,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SWITCH4[0]	=>  Location: PIN_Y24,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF bi_hex_18_5 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_SWITCH0 : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_SWITCH1 : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_SWITCH2 : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_SWITCH3 : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_SWITCH4 : std_logic_vector(1 DOWNTO 0);
SIGNAL ww_HEX0 : std_logic_vector(6 DOWNTO 0);
SIGNAL ww_HEX1 : std_logic_vector(6 DOWNTO 0);
SIGNAL ww_HEX2 : std_logic_vector(6 DOWNTO 0);
SIGNAL ww_HEX3 : std_logic_vector(6 DOWNTO 0);
SIGNAL ww_HEX4 : std_logic_vector(6 DOWNTO 0);
SIGNAL \HEX0[0]~output_o\ : std_logic;
SIGNAL \HEX0[1]~output_o\ : std_logic;
SIGNAL \HEX0[2]~output_o\ : std_logic;
SIGNAL \HEX0[3]~output_o\ : std_logic;
SIGNAL \HEX0[4]~output_o\ : std_logic;
SIGNAL \HEX0[5]~output_o\ : std_logic;
SIGNAL \HEX0[6]~output_o\ : std_logic;
SIGNAL \HEX1[0]~output_o\ : std_logic;
SIGNAL \HEX1[1]~output_o\ : std_logic;
SIGNAL \HEX1[2]~output_o\ : std_logic;
SIGNAL \HEX1[3]~output_o\ : std_logic;
SIGNAL \HEX1[4]~output_o\ : std_logic;
SIGNAL \HEX1[5]~output_o\ : std_logic;
SIGNAL \HEX1[6]~output_o\ : std_logic;
SIGNAL \HEX2[0]~output_o\ : std_logic;
SIGNAL \HEX2[1]~output_o\ : std_logic;
SIGNAL \HEX2[2]~output_o\ : std_logic;
SIGNAL \HEX2[3]~output_o\ : std_logic;
SIGNAL \HEX2[4]~output_o\ : std_logic;
SIGNAL \HEX2[5]~output_o\ : std_logic;
SIGNAL \HEX2[6]~output_o\ : std_logic;
SIGNAL \HEX3[0]~output_o\ : std_logic;
SIGNAL \HEX3[1]~output_o\ : std_logic;
SIGNAL \HEX3[2]~output_o\ : std_logic;
SIGNAL \HEX3[3]~output_o\ : std_logic;
SIGNAL \HEX3[4]~output_o\ : std_logic;
SIGNAL \HEX3[5]~output_o\ : std_logic;
SIGNAL \HEX3[6]~output_o\ : std_logic;
SIGNAL \HEX4[0]~output_o\ : std_logic;
SIGNAL \HEX4[1]~output_o\ : std_logic;
SIGNAL \HEX4[2]~output_o\ : std_logic;
SIGNAL \HEX4[3]~output_o\ : std_logic;
SIGNAL \HEX4[4]~output_o\ : std_logic;
SIGNAL \HEX4[5]~output_o\ : std_logic;
SIGNAL \HEX4[6]~output_o\ : std_logic;
SIGNAL \SWITCH0[3]~input_o\ : std_logic;
SIGNAL \SWITCH0[1]~input_o\ : std_logic;
SIGNAL \SWITCH0[2]~input_o\ : std_logic;
SIGNAL \SWITCH0[0]~input_o\ : std_logic;
SIGNAL \U0|Mux6~0_combout\ : std_logic;
SIGNAL \U0|Mux5~0_combout\ : std_logic;
SIGNAL \U0|Mux4~0_combout\ : std_logic;
SIGNAL \U0|Mux3~0_combout\ : std_logic;
SIGNAL \U0|Mux2~0_combout\ : std_logic;
SIGNAL \U0|Mux1~0_combout\ : std_logic;
SIGNAL \U0|Mux0~0_combout\ : std_logic;
SIGNAL \SWITCH1[3]~input_o\ : std_logic;
SIGNAL \SWITCH1[1]~input_o\ : std_logic;
SIGNAL \SWITCH1[2]~input_o\ : std_logic;
SIGNAL \SWITCH1[0]~input_o\ : std_logic;
SIGNAL \U1|Mux6~0_combout\ : std_logic;
SIGNAL \U1|Mux5~0_combout\ : std_logic;
SIGNAL \U1|Mux4~0_combout\ : std_logic;
SIGNAL \U1|Mux3~0_combout\ : std_logic;
SIGNAL \U1|Mux2~0_combout\ : std_logic;
SIGNAL \U1|Mux1~0_combout\ : std_logic;
SIGNAL \U1|Mux0~0_combout\ : std_logic;
SIGNAL \SWITCH2[0]~input_o\ : std_logic;
SIGNAL \SWITCH2[2]~input_o\ : std_logic;
SIGNAL \SWITCH2[3]~input_o\ : std_logic;
SIGNAL \SWITCH2[1]~input_o\ : std_logic;
SIGNAL \U2|Mux6~0_combout\ : std_logic;
SIGNAL \U2|Mux5~0_combout\ : std_logic;
SIGNAL \U2|Mux4~0_combout\ : std_logic;
SIGNAL \U2|Mux3~0_combout\ : std_logic;
SIGNAL \U2|Mux2~0_combout\ : std_logic;
SIGNAL \U2|Mux1~0_combout\ : std_logic;
SIGNAL \U2|Mux0~0_combout\ : std_logic;
SIGNAL \SWITCH3[1]~input_o\ : std_logic;
SIGNAL \SWITCH3[0]~input_o\ : std_logic;
SIGNAL \SWITCH3[3]~input_o\ : std_logic;
SIGNAL \SWITCH3[2]~input_o\ : std_logic;
SIGNAL \U3|Mux6~0_combout\ : std_logic;
SIGNAL \U3|Mux5~0_combout\ : std_logic;
SIGNAL \U3|Mux4~0_combout\ : std_logic;
SIGNAL \U3|Mux3~0_combout\ : std_logic;
SIGNAL \U3|Mux2~0_combout\ : std_logic;
SIGNAL \U3|Mux1~0_combout\ : std_logic;
SIGNAL \U3|Mux0~0_combout\ : std_logic;
SIGNAL \SWITCH4[1]~input_o\ : std_logic;
SIGNAL \SWITCH4[0]~input_o\ : std_logic;
SIGNAL \U4|Mux3~0_combout\ : std_logic;
SIGNAL \U4|Mux1~0_combout\ : std_logic;
SIGNAL \U4|Mux1~1_combout\ : std_logic;
SIGNAL \ALT_INV_SWITCH4[1]~input_o\ : std_logic;
SIGNAL \U3|ALT_INV_Mux6~0_combout\ : std_logic;
SIGNAL \U2|ALT_INV_Mux6~0_combout\ : std_logic;
SIGNAL \U1|ALT_INV_Mux6~0_combout\ : std_logic;
SIGNAL \U0|ALT_INV_Mux6~0_combout\ : std_logic;

BEGIN

ww_SWITCH0 <= SWITCH0;
ww_SWITCH1 <= SWITCH1;
ww_SWITCH2 <= SWITCH2;
ww_SWITCH3 <= SWITCH3;
ww_SWITCH4 <= SWITCH4;
HEX0 <= ww_HEX0;
HEX1 <= ww_HEX1;
HEX2 <= ww_HEX2;
HEX3 <= ww_HEX3;
HEX4 <= ww_HEX4;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\ALT_INV_SWITCH4[1]~input_o\ <= NOT \SWITCH4[1]~input_o\;
\U3|ALT_INV_Mux6~0_combout\ <= NOT \U3|Mux6~0_combout\;
\U2|ALT_INV_Mux6~0_combout\ <= NOT \U2|Mux6~0_combout\;
\U1|ALT_INV_Mux6~0_combout\ <= NOT \U1|Mux6~0_combout\;
\U0|ALT_INV_Mux6~0_combout\ <= NOT \U0|Mux6~0_combout\;

-- Location: IOOBUF_X115_Y69_N2
\HEX0[0]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U0|ALT_INV_Mux6~0_combout\,
	devoe => ww_devoe,
	o => \HEX0[0]~output_o\);

-- Location: IOOBUF_X115_Y67_N16
\HEX0[1]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U0|Mux5~0_combout\,
	devoe => ww_devoe,
	o => \HEX0[1]~output_o\);

-- Location: IOOBUF_X115_Y54_N16
\HEX0[2]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U0|Mux4~0_combout\,
	devoe => ww_devoe,
	o => \HEX0[2]~output_o\);

-- Location: IOOBUF_X115_Y50_N2
\HEX0[3]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U0|Mux3~0_combout\,
	devoe => ww_devoe,
	o => \HEX0[3]~output_o\);

-- Location: IOOBUF_X67_Y73_N23
\HEX0[4]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U0|Mux2~0_combout\,
	devoe => ww_devoe,
	o => \HEX0[4]~output_o\);

-- Location: IOOBUF_X107_Y73_N23
\HEX0[5]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U0|Mux1~0_combout\,
	devoe => ww_devoe,
	o => \HEX0[5]~output_o\);

-- Location: IOOBUF_X69_Y73_N23
\HEX0[6]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U0|Mux0~0_combout\,
	devoe => ww_devoe,
	o => \HEX0[6]~output_o\);

-- Location: IOOBUF_X115_Y28_N9
\HEX1[0]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U1|ALT_INV_Mux6~0_combout\,
	devoe => ww_devoe,
	o => \HEX1[0]~output_o\);

-- Location: IOOBUF_X115_Y22_N2
\HEX1[1]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U1|Mux5~0_combout\,
	devoe => ww_devoe,
	o => \HEX1[1]~output_o\);

-- Location: IOOBUF_X115_Y20_N9
\HEX1[2]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U1|Mux4~0_combout\,
	devoe => ww_devoe,
	o => \HEX1[2]~output_o\);

-- Location: IOOBUF_X115_Y30_N2
\HEX1[3]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U1|Mux3~0_combout\,
	devoe => ww_devoe,
	o => \HEX1[3]~output_o\);

-- Location: IOOBUF_X115_Y25_N23
\HEX1[4]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U1|Mux2~0_combout\,
	devoe => ww_devoe,
	o => \HEX1[4]~output_o\);

-- Location: IOOBUF_X115_Y30_N9
\HEX1[5]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U1|Mux1~0_combout\,
	devoe => ww_devoe,
	o => \HEX1[5]~output_o\);

-- Location: IOOBUF_X115_Y41_N2
\HEX1[6]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U1|Mux0~0_combout\,
	devoe => ww_devoe,
	o => \HEX1[6]~output_o\);

-- Location: IOOBUF_X115_Y21_N16
\HEX2[0]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U2|ALT_INV_Mux6~0_combout\,
	devoe => ww_devoe,
	o => \HEX2[0]~output_o\);

-- Location: IOOBUF_X115_Y20_N2
\HEX2[1]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U2|Mux5~0_combout\,
	devoe => ww_devoe,
	o => \HEX2[1]~output_o\);

-- Location: IOOBUF_X115_Y18_N2
\HEX2[2]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U2|Mux4~0_combout\,
	devoe => ww_devoe,
	o => \HEX2[2]~output_o\);

-- Location: IOOBUF_X115_Y19_N2
\HEX2[3]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U2|Mux3~0_combout\,
	devoe => ww_devoe,
	o => \HEX2[3]~output_o\);

-- Location: IOOBUF_X115_Y19_N9
\HEX2[4]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U2|Mux2~0_combout\,
	devoe => ww_devoe,
	o => \HEX2[4]~output_o\);

-- Location: IOOBUF_X115_Y16_N2
\HEX2[5]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U2|Mux1~0_combout\,
	devoe => ww_devoe,
	o => \HEX2[5]~output_o\);

-- Location: IOOBUF_X115_Y17_N9
\HEX2[6]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U2|Mux0~0_combout\,
	devoe => ww_devoe,
	o => \HEX2[6]~output_o\);

-- Location: IOOBUF_X105_Y0_N2
\HEX3[0]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U3|ALT_INV_Mux6~0_combout\,
	devoe => ww_devoe,
	o => \HEX3[0]~output_o\);

-- Location: IOOBUF_X105_Y0_N9
\HEX3[1]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U3|Mux5~0_combout\,
	devoe => ww_devoe,
	o => \HEX3[1]~output_o\);

-- Location: IOOBUF_X105_Y0_N23
\HEX3[2]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U3|Mux4~0_combout\,
	devoe => ww_devoe,
	o => \HEX3[2]~output_o\);

-- Location: IOOBUF_X111_Y0_N2
\HEX3[3]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U3|Mux3~0_combout\,
	devoe => ww_devoe,
	o => \HEX3[3]~output_o\);

-- Location: IOOBUF_X100_Y0_N2
\HEX3[4]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U3|Mux2~0_combout\,
	devoe => ww_devoe,
	o => \HEX3[4]~output_o\);

-- Location: IOOBUF_X115_Y29_N2
\HEX3[5]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U3|Mux1~0_combout\,
	devoe => ww_devoe,
	o => \HEX3[5]~output_o\);

-- Location: IOOBUF_X115_Y25_N16
\HEX3[6]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U3|Mux0~0_combout\,
	devoe => ww_devoe,
	o => \HEX3[6]~output_o\);

-- Location: IOOBUF_X79_Y0_N23
\HEX4[0]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \ALT_INV_SWITCH4[1]~input_o\,
	devoe => ww_devoe,
	o => \HEX4[0]~output_o\);

-- Location: IOOBUF_X83_Y0_N16
\HEX4[1]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U4|Mux3~0_combout\,
	devoe => ww_devoe,
	o => \HEX4[1]~output_o\);

-- Location: IOOBUF_X83_Y0_N23
\HEX4[2]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \SWITCH4[0]~input_o\,
	devoe => ww_devoe,
	o => \HEX4[2]~output_o\);

-- Location: IOOBUF_X74_Y0_N2
\HEX4[3]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U4|Mux1~0_combout\,
	devoe => ww_devoe,
	o => \HEX4[3]~output_o\);

-- Location: IOOBUF_X74_Y0_N9
\HEX4[4]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U4|Mux1~1_combout\,
	devoe => ww_devoe,
	o => \HEX4[4]~output_o\);

-- Location: IOOBUF_X107_Y0_N9
\HEX4[5]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \HEX4[5]~output_o\);

-- Location: IOOBUF_X98_Y0_N23
\HEX4[6]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \U4|Mux1~0_combout\,
	devoe => ww_devoe,
	o => \HEX4[6]~output_o\);

-- Location: IOIBUF_X115_Y13_N8
\SWITCH0[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH0(3),
	o => \SWITCH0[3]~input_o\);

-- Location: IOIBUF_X115_Y14_N1
\SWITCH0[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH0(1),
	o => \SWITCH0[1]~input_o\);

-- Location: IOIBUF_X115_Y15_N8
\SWITCH0[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH0(2),
	o => \SWITCH0[2]~input_o\);

-- Location: IOIBUF_X115_Y17_N1
\SWITCH0[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH0(0),
	o => \SWITCH0[0]~input_o\);

-- Location: LCCOMB_X114_Y50_N0
\U0|Mux6~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U0|Mux6~0_combout\ = (\SWITCH0[0]~input_o\ & ((\SWITCH0[3]~input_o\) # (\SWITCH0[1]~input_o\ $ (\SWITCH0[2]~input_o\)))) # (!\SWITCH0[0]~input_o\ & ((\SWITCH0[1]~input_o\) # (\SWITCH0[3]~input_o\ $ (\SWITCH0[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111011011110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH0[3]~input_o\,
	datab => \SWITCH0[1]~input_o\,
	datac => \SWITCH0[2]~input_o\,
	datad => \SWITCH0[0]~input_o\,
	combout => \U0|Mux6~0_combout\);

-- Location: LCCOMB_X114_Y50_N26
\U0|Mux5~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U0|Mux5~0_combout\ = (\SWITCH0[1]~input_o\ & (!\SWITCH0[3]~input_o\ & (!\SWITCH0[2]~input_o\))) # (!\SWITCH0[1]~input_o\ & (\SWITCH0[0]~input_o\ & (\SWITCH0[3]~input_o\ $ (!\SWITCH0[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010010100000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH0[3]~input_o\,
	datab => \SWITCH0[1]~input_o\,
	datac => \SWITCH0[2]~input_o\,
	datad => \SWITCH0[0]~input_o\,
	combout => \U0|Mux5~0_combout\);

-- Location: LCCOMB_X114_Y50_N12
\U0|Mux4~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U0|Mux4~0_combout\ = (\SWITCH0[1]~input_o\ & (!\SWITCH0[3]~input_o\ & ((\SWITCH0[0]~input_o\)))) # (!\SWITCH0[1]~input_o\ & ((\SWITCH0[2]~input_o\ & (!\SWITCH0[3]~input_o\)) # (!\SWITCH0[2]~input_o\ & ((\SWITCH0[0]~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101011100010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH0[3]~input_o\,
	datab => \SWITCH0[1]~input_o\,
	datac => \SWITCH0[2]~input_o\,
	datad => \SWITCH0[0]~input_o\,
	combout => \U0|Mux4~0_combout\);

-- Location: LCCOMB_X114_Y50_N14
\U0|Mux3~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U0|Mux3~0_combout\ = (\SWITCH0[0]~input_o\ & ((\SWITCH0[1]~input_o\ $ (!\SWITCH0[2]~input_o\)))) # (!\SWITCH0[0]~input_o\ & ((\SWITCH0[3]~input_o\ & (\SWITCH0[1]~input_o\ & !\SWITCH0[2]~input_o\)) # (!\SWITCH0[3]~input_o\ & (!\SWITCH0[1]~input_o\ & 
-- \SWITCH0[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH0[3]~input_o\,
	datab => \SWITCH0[1]~input_o\,
	datac => \SWITCH0[2]~input_o\,
	datad => \SWITCH0[0]~input_o\,
	combout => \U0|Mux3~0_combout\);

-- Location: LCCOMB_X114_Y50_N24
\U0|Mux2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U0|Mux2~0_combout\ = (\SWITCH0[3]~input_o\ & (\SWITCH0[2]~input_o\ & ((\SWITCH0[1]~input_o\) # (!\SWITCH0[0]~input_o\)))) # (!\SWITCH0[3]~input_o\ & (\SWITCH0[1]~input_o\ & (!\SWITCH0[2]~input_o\ & !\SWITCH0[0]~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000010100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH0[3]~input_o\,
	datab => \SWITCH0[1]~input_o\,
	datac => \SWITCH0[2]~input_o\,
	datad => \SWITCH0[0]~input_o\,
	combout => \U0|Mux2~0_combout\);

-- Location: LCCOMB_X114_Y50_N2
\U0|Mux1~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U0|Mux1~0_combout\ = (\SWITCH0[3]~input_o\ & ((\SWITCH0[0]~input_o\ & (\SWITCH0[1]~input_o\)) # (!\SWITCH0[0]~input_o\ & ((\SWITCH0[2]~input_o\))))) # (!\SWITCH0[3]~input_o\ & (\SWITCH0[2]~input_o\ & (\SWITCH0[1]~input_o\ $ (\SWITCH0[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001100011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH0[3]~input_o\,
	datab => \SWITCH0[1]~input_o\,
	datac => \SWITCH0[2]~input_o\,
	datad => \SWITCH0[0]~input_o\,
	combout => \U0|Mux1~0_combout\);

-- Location: LCCOMB_X114_Y50_N4
\U0|Mux0~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U0|Mux0~0_combout\ = (\SWITCH0[3]~input_o\ & (\SWITCH0[0]~input_o\ & (\SWITCH0[1]~input_o\ $ (\SWITCH0[2]~input_o\)))) # (!\SWITCH0[3]~input_o\ & (!\SWITCH0[1]~input_o\ & (\SWITCH0[2]~input_o\ $ (\SWITCH0[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010100100010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH0[3]~input_o\,
	datab => \SWITCH0[1]~input_o\,
	datac => \SWITCH0[2]~input_o\,
	datad => \SWITCH0[0]~input_o\,
	combout => \U0|Mux0~0_combout\);

-- Location: IOIBUF_X115_Y15_N1
\SWITCH1[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH1(3),
	o => \SWITCH1[3]~input_o\);

-- Location: IOIBUF_X115_Y11_N8
\SWITCH1[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH1(1),
	o => \SWITCH1[1]~input_o\);

-- Location: IOIBUF_X115_Y10_N1
\SWITCH1[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH1(2),
	o => \SWITCH1[2]~input_o\);

-- Location: IOIBUF_X115_Y18_N8
\SWITCH1[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH1(0),
	o => \SWITCH1[0]~input_o\);

-- Location: LCCOMB_X114_Y22_N0
\U1|Mux6~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U1|Mux6~0_combout\ = (\SWITCH1[0]~input_o\ & ((\SWITCH1[3]~input_o\) # (\SWITCH1[1]~input_o\ $ (\SWITCH1[2]~input_o\)))) # (!\SWITCH1[0]~input_o\ & ((\SWITCH1[1]~input_o\) # (\SWITCH1[3]~input_o\ $ (\SWITCH1[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111011011110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH1[3]~input_o\,
	datab => \SWITCH1[1]~input_o\,
	datac => \SWITCH1[2]~input_o\,
	datad => \SWITCH1[0]~input_o\,
	combout => \U1|Mux6~0_combout\);

-- Location: LCCOMB_X114_Y22_N2
\U1|Mux5~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U1|Mux5~0_combout\ = (\SWITCH1[1]~input_o\ & (!\SWITCH1[3]~input_o\ & (!\SWITCH1[2]~input_o\))) # (!\SWITCH1[1]~input_o\ & (\SWITCH1[0]~input_o\ & (\SWITCH1[3]~input_o\ $ (!\SWITCH1[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010010100000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH1[3]~input_o\,
	datab => \SWITCH1[1]~input_o\,
	datac => \SWITCH1[2]~input_o\,
	datad => \SWITCH1[0]~input_o\,
	combout => \U1|Mux5~0_combout\);

-- Location: LCCOMB_X114_Y22_N28
\U1|Mux4~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U1|Mux4~0_combout\ = (\SWITCH1[1]~input_o\ & (!\SWITCH1[3]~input_o\ & ((\SWITCH1[0]~input_o\)))) # (!\SWITCH1[1]~input_o\ & ((\SWITCH1[2]~input_o\ & (!\SWITCH1[3]~input_o\)) # (!\SWITCH1[2]~input_o\ & ((\SWITCH1[0]~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101011100010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH1[3]~input_o\,
	datab => \SWITCH1[1]~input_o\,
	datac => \SWITCH1[2]~input_o\,
	datad => \SWITCH1[0]~input_o\,
	combout => \U1|Mux4~0_combout\);

-- Location: LCCOMB_X114_Y22_N22
\U1|Mux3~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U1|Mux3~0_combout\ = (\SWITCH1[0]~input_o\ & ((\SWITCH1[1]~input_o\ $ (!\SWITCH1[2]~input_o\)))) # (!\SWITCH1[0]~input_o\ & ((\SWITCH1[3]~input_o\ & (\SWITCH1[1]~input_o\ & !\SWITCH1[2]~input_o\)) # (!\SWITCH1[3]~input_o\ & (!\SWITCH1[1]~input_o\ & 
-- \SWITCH1[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH1[3]~input_o\,
	datab => \SWITCH1[1]~input_o\,
	datac => \SWITCH1[2]~input_o\,
	datad => \SWITCH1[0]~input_o\,
	combout => \U1|Mux3~0_combout\);

-- Location: LCCOMB_X114_Y22_N24
\U1|Mux2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U1|Mux2~0_combout\ = (\SWITCH1[3]~input_o\ & (\SWITCH1[2]~input_o\ & ((\SWITCH1[1]~input_o\) # (!\SWITCH1[0]~input_o\)))) # (!\SWITCH1[3]~input_o\ & (\SWITCH1[1]~input_o\ & (!\SWITCH1[2]~input_o\ & !\SWITCH1[0]~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000010100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH1[3]~input_o\,
	datab => \SWITCH1[1]~input_o\,
	datac => \SWITCH1[2]~input_o\,
	datad => \SWITCH1[0]~input_o\,
	combout => \U1|Mux2~0_combout\);

-- Location: LCCOMB_X114_Y22_N26
\U1|Mux1~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U1|Mux1~0_combout\ = (\SWITCH1[3]~input_o\ & ((\SWITCH1[0]~input_o\ & (\SWITCH1[1]~input_o\)) # (!\SWITCH1[0]~input_o\ & ((\SWITCH1[2]~input_o\))))) # (!\SWITCH1[3]~input_o\ & (\SWITCH1[2]~input_o\ & (\SWITCH1[1]~input_o\ $ (\SWITCH1[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001100011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH1[3]~input_o\,
	datab => \SWITCH1[1]~input_o\,
	datac => \SWITCH1[2]~input_o\,
	datad => \SWITCH1[0]~input_o\,
	combout => \U1|Mux1~0_combout\);

-- Location: LCCOMB_X114_Y22_N12
\U1|Mux0~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U1|Mux0~0_combout\ = (\SWITCH1[3]~input_o\ & (\SWITCH1[0]~input_o\ & (\SWITCH1[1]~input_o\ $ (\SWITCH1[2]~input_o\)))) # (!\SWITCH1[3]~input_o\ & (!\SWITCH1[1]~input_o\ & (\SWITCH1[2]~input_o\ $ (\SWITCH1[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010100100010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH1[3]~input_o\,
	datab => \SWITCH1[1]~input_o\,
	datac => \SWITCH1[2]~input_o\,
	datad => \SWITCH1[0]~input_o\,
	combout => \U1|Mux0~0_combout\);

-- Location: IOIBUF_X115_Y4_N22
\SWITCH2[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH2(0),
	o => \SWITCH2[0]~input_o\);

-- Location: IOIBUF_X115_Y4_N15
\SWITCH2[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH2(2),
	o => \SWITCH2[2]~input_o\);

-- Location: IOIBUF_X115_Y5_N15
\SWITCH2[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH2(3),
	o => \SWITCH2[3]~input_o\);

-- Location: IOIBUF_X115_Y16_N8
\SWITCH2[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH2(1),
	o => \SWITCH2[1]~input_o\);

-- Location: LCCOMB_X114_Y16_N0
\U2|Mux6~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U2|Mux6~0_combout\ = (\SWITCH2[0]~input_o\ & ((\SWITCH2[3]~input_o\) # (\SWITCH2[2]~input_o\ $ (\SWITCH2[1]~input_o\)))) # (!\SWITCH2[0]~input_o\ & ((\SWITCH2[1]~input_o\) # (\SWITCH2[2]~input_o\ $ (\SWITCH2[3]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111011110111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH2[0]~input_o\,
	datab => \SWITCH2[2]~input_o\,
	datac => \SWITCH2[3]~input_o\,
	datad => \SWITCH2[1]~input_o\,
	combout => \U2|Mux6~0_combout\);

-- Location: LCCOMB_X114_Y16_N26
\U2|Mux5~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U2|Mux5~0_combout\ = (\SWITCH2[1]~input_o\ & (((!\SWITCH2[2]~input_o\ & !\SWITCH2[3]~input_o\)))) # (!\SWITCH2[1]~input_o\ & (\SWITCH2[0]~input_o\ & (\SWITCH2[2]~input_o\ $ (!\SWITCH2[3]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001110000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH2[0]~input_o\,
	datab => \SWITCH2[2]~input_o\,
	datac => \SWITCH2[3]~input_o\,
	datad => \SWITCH2[1]~input_o\,
	combout => \U2|Mux5~0_combout\);

-- Location: LCCOMB_X114_Y16_N12
\U2|Mux4~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U2|Mux4~0_combout\ = (\SWITCH2[1]~input_o\ & (\SWITCH2[0]~input_o\ & ((!\SWITCH2[3]~input_o\)))) # (!\SWITCH2[1]~input_o\ & ((\SWITCH2[2]~input_o\ & ((!\SWITCH2[3]~input_o\))) # (!\SWITCH2[2]~input_o\ & (\SWITCH2[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000101000101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH2[0]~input_o\,
	datab => \SWITCH2[2]~input_o\,
	datac => \SWITCH2[3]~input_o\,
	datad => \SWITCH2[1]~input_o\,
	combout => \U2|Mux4~0_combout\);

-- Location: LCCOMB_X114_Y16_N14
\U2|Mux3~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U2|Mux3~0_combout\ = (\SWITCH2[0]~input_o\ & (\SWITCH2[2]~input_o\ $ (((!\SWITCH2[1]~input_o\))))) # (!\SWITCH2[0]~input_o\ & ((\SWITCH2[2]~input_o\ & (!\SWITCH2[3]~input_o\ & !\SWITCH2[1]~input_o\)) # (!\SWITCH2[2]~input_o\ & (\SWITCH2[3]~input_o\ & 
-- \SWITCH2[1]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001100000100110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH2[0]~input_o\,
	datab => \SWITCH2[2]~input_o\,
	datac => \SWITCH2[3]~input_o\,
	datad => \SWITCH2[1]~input_o\,
	combout => \U2|Mux3~0_combout\);

-- Location: LCCOMB_X114_Y16_N16
\U2|Mux2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U2|Mux2~0_combout\ = (\SWITCH2[2]~input_o\ & (\SWITCH2[3]~input_o\ & ((\SWITCH2[1]~input_o\) # (!\SWITCH2[0]~input_o\)))) # (!\SWITCH2[2]~input_o\ & (!\SWITCH2[0]~input_o\ & (!\SWITCH2[3]~input_o\ & \SWITCH2[1]~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000101000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH2[0]~input_o\,
	datab => \SWITCH2[2]~input_o\,
	datac => \SWITCH2[3]~input_o\,
	datad => \SWITCH2[1]~input_o\,
	combout => \U2|Mux2~0_combout\);

-- Location: LCCOMB_X114_Y16_N10
\U2|Mux1~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U2|Mux1~0_combout\ = (\SWITCH2[3]~input_o\ & ((\SWITCH2[0]~input_o\ & ((\SWITCH2[1]~input_o\))) # (!\SWITCH2[0]~input_o\ & (\SWITCH2[2]~input_o\)))) # (!\SWITCH2[3]~input_o\ & (\SWITCH2[2]~input_o\ & (\SWITCH2[0]~input_o\ $ (\SWITCH2[1]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110010001001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH2[0]~input_o\,
	datab => \SWITCH2[2]~input_o\,
	datac => \SWITCH2[3]~input_o\,
	datad => \SWITCH2[1]~input_o\,
	combout => \U2|Mux1~0_combout\);

-- Location: LCCOMB_X114_Y16_N28
\U2|Mux0~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U2|Mux0~0_combout\ = (\SWITCH2[2]~input_o\ & (!\SWITCH2[1]~input_o\ & (\SWITCH2[0]~input_o\ $ (!\SWITCH2[3]~input_o\)))) # (!\SWITCH2[2]~input_o\ & (\SWITCH2[0]~input_o\ & (\SWITCH2[3]~input_o\ $ (!\SWITCH2[1]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000010000110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH2[0]~input_o\,
	datab => \SWITCH2[2]~input_o\,
	datac => \SWITCH2[3]~input_o\,
	datad => \SWITCH2[1]~input_o\,
	combout => \U2|Mux0~0_combout\);

-- Location: IOIBUF_X115_Y9_N22
\SWITCH3[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH3(1),
	o => \SWITCH3[1]~input_o\);

-- Location: IOIBUF_X115_Y7_N15
\SWITCH3[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH3(0),
	o => \SWITCH3[0]~input_o\);

-- Location: IOIBUF_X115_Y6_N15
\SWITCH3[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH3(3),
	o => \SWITCH3[3]~input_o\);

-- Location: IOIBUF_X115_Y10_N8
\SWITCH3[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH3(2),
	o => \SWITCH3[2]~input_o\);

-- Location: LCCOMB_X114_Y7_N16
\U3|Mux6~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U3|Mux6~0_combout\ = (\SWITCH3[0]~input_o\ & ((\SWITCH3[3]~input_o\) # (\SWITCH3[1]~input_o\ $ (\SWITCH3[2]~input_o\)))) # (!\SWITCH3[0]~input_o\ & ((\SWITCH3[1]~input_o\) # (\SWITCH3[3]~input_o\ $ (\SWITCH3[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110011111111010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH3[1]~input_o\,
	datab => \SWITCH3[0]~input_o\,
	datac => \SWITCH3[3]~input_o\,
	datad => \SWITCH3[2]~input_o\,
	combout => \U3|Mux6~0_combout\);

-- Location: LCCOMB_X114_Y7_N26
\U3|Mux5~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U3|Mux5~0_combout\ = (\SWITCH3[1]~input_o\ & (((!\SWITCH3[3]~input_o\ & !\SWITCH3[2]~input_o\)))) # (!\SWITCH3[1]~input_o\ & (\SWITCH3[0]~input_o\ & (\SWITCH3[3]~input_o\ $ (!\SWITCH3[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100000000001110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH3[1]~input_o\,
	datab => \SWITCH3[0]~input_o\,
	datac => \SWITCH3[3]~input_o\,
	datad => \SWITCH3[2]~input_o\,
	combout => \U3|Mux5~0_combout\);

-- Location: LCCOMB_X114_Y7_N28
\U3|Mux4~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U3|Mux4~0_combout\ = (\SWITCH3[1]~input_o\ & (\SWITCH3[0]~input_o\ & (!\SWITCH3[3]~input_o\))) # (!\SWITCH3[1]~input_o\ & ((\SWITCH3[2]~input_o\ & ((!\SWITCH3[3]~input_o\))) # (!\SWITCH3[2]~input_o\ & (\SWITCH3[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110101001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH3[1]~input_o\,
	datab => \SWITCH3[0]~input_o\,
	datac => \SWITCH3[3]~input_o\,
	datad => \SWITCH3[2]~input_o\,
	combout => \U3|Mux4~0_combout\);

-- Location: LCCOMB_X114_Y7_N30
\U3|Mux3~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U3|Mux3~0_combout\ = (\SWITCH3[0]~input_o\ & (\SWITCH3[1]~input_o\ $ (((!\SWITCH3[2]~input_o\))))) # (!\SWITCH3[0]~input_o\ & ((\SWITCH3[1]~input_o\ & (\SWITCH3[3]~input_o\ & !\SWITCH3[2]~input_o\)) # (!\SWITCH3[1]~input_o\ & (!\SWITCH3[3]~input_o\ & 
-- \SWITCH3[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100101100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH3[1]~input_o\,
	datab => \SWITCH3[0]~input_o\,
	datac => \SWITCH3[3]~input_o\,
	datad => \SWITCH3[2]~input_o\,
	combout => \U3|Mux3~0_combout\);

-- Location: LCCOMB_X114_Y7_N8
\U3|Mux2~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U3|Mux2~0_combout\ = (\SWITCH3[3]~input_o\ & (\SWITCH3[2]~input_o\ & ((\SWITCH3[1]~input_o\) # (!\SWITCH3[0]~input_o\)))) # (!\SWITCH3[3]~input_o\ & (\SWITCH3[1]~input_o\ & (!\SWITCH3[0]~input_o\ & !\SWITCH3[2]~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH3[1]~input_o\,
	datab => \SWITCH3[0]~input_o\,
	datac => \SWITCH3[3]~input_o\,
	datad => \SWITCH3[2]~input_o\,
	combout => \U3|Mux2~0_combout\);

-- Location: LCCOMB_X114_Y7_N10
\U3|Mux1~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U3|Mux1~0_combout\ = (\SWITCH3[1]~input_o\ & ((\SWITCH3[0]~input_o\ & (\SWITCH3[3]~input_o\)) # (!\SWITCH3[0]~input_o\ & ((\SWITCH3[2]~input_o\))))) # (!\SWITCH3[1]~input_o\ & (\SWITCH3[2]~input_o\ & (\SWITCH3[0]~input_o\ $ (\SWITCH3[3]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011011010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH3[1]~input_o\,
	datab => \SWITCH3[0]~input_o\,
	datac => \SWITCH3[3]~input_o\,
	datad => \SWITCH3[2]~input_o\,
	combout => \U3|Mux1~0_combout\);

-- Location: LCCOMB_X114_Y7_N4
\U3|Mux0~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U3|Mux0~0_combout\ = (\SWITCH3[3]~input_o\ & (\SWITCH3[0]~input_o\ & (\SWITCH3[1]~input_o\ $ (\SWITCH3[2]~input_o\)))) # (!\SWITCH3[3]~input_o\ & (!\SWITCH3[1]~input_o\ & (\SWITCH3[0]~input_o\ $ (\SWITCH3[2]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100000110000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH3[1]~input_o\,
	datab => \SWITCH3[0]~input_o\,
	datac => \SWITCH3[3]~input_o\,
	datad => \SWITCH3[2]~input_o\,
	combout => \U3|Mux0~0_combout\);

-- Location: IOIBUF_X115_Y14_N8
\SWITCH4[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH4(1),
	o => \SWITCH4[1]~input_o\);

-- Location: IOIBUF_X115_Y13_N1
\SWITCH4[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SWITCH4(0),
	o => \SWITCH4[0]~input_o\);

-- Location: LCCOMB_X83_Y1_N24
\U4|Mux3~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U4|Mux3~0_combout\ = (\SWITCH4[0]~input_o\) # (\SWITCH4[1]~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH4[0]~input_o\,
	datad => \SWITCH4[1]~input_o\,
	combout => \U4|Mux3~0_combout\);

-- Location: LCCOMB_X83_Y1_N26
\U4|Mux1~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \U4|Mux1~0_combout\ = (\SWITCH4[0]~input_o\ & !\SWITCH4[1]~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH4[0]~input_o\,
	datad => \SWITCH4[1]~input_o\,
	combout => \U4|Mux1~0_combout\);

-- Location: LCCOMB_X83_Y1_N4
\U4|Mux1~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \U4|Mux1~1_combout\ = (!\SWITCH4[0]~input_o\ & \SWITCH4[1]~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SWITCH4[0]~input_o\,
	datad => \SWITCH4[1]~input_o\,
	combout => \U4|Mux1~1_combout\);

ww_HEX0(0) <= \HEX0[0]~output_o\;

ww_HEX0(1) <= \HEX0[1]~output_o\;

ww_HEX0(2) <= \HEX0[2]~output_o\;

ww_HEX0(3) <= \HEX0[3]~output_o\;

ww_HEX0(4) <= \HEX0[4]~output_o\;

ww_HEX0(5) <= \HEX0[5]~output_o\;

ww_HEX0(6) <= \HEX0[6]~output_o\;

ww_HEX1(0) <= \HEX1[0]~output_o\;

ww_HEX1(1) <= \HEX1[1]~output_o\;

ww_HEX1(2) <= \HEX1[2]~output_o\;

ww_HEX1(3) <= \HEX1[3]~output_o\;

ww_HEX1(4) <= \HEX1[4]~output_o\;

ww_HEX1(5) <= \HEX1[5]~output_o\;

ww_HEX1(6) <= \HEX1[6]~output_o\;

ww_HEX2(0) <= \HEX2[0]~output_o\;

ww_HEX2(1) <= \HEX2[1]~output_o\;

ww_HEX2(2) <= \HEX2[2]~output_o\;

ww_HEX2(3) <= \HEX2[3]~output_o\;

ww_HEX2(4) <= \HEX2[4]~output_o\;

ww_HEX2(5) <= \HEX2[5]~output_o\;

ww_HEX2(6) <= \HEX2[6]~output_o\;

ww_HEX3(0) <= \HEX3[0]~output_o\;

ww_HEX3(1) <= \HEX3[1]~output_o\;

ww_HEX3(2) <= \HEX3[2]~output_o\;

ww_HEX3(3) <= \HEX3[3]~output_o\;

ww_HEX3(4) <= \HEX3[4]~output_o\;

ww_HEX3(5) <= \HEX3[5]~output_o\;

ww_HEX3(6) <= \HEX3[6]~output_o\;

ww_HEX4(0) <= \HEX4[0]~output_o\;

ww_HEX4(1) <= \HEX4[1]~output_o\;

ww_HEX4(2) <= \HEX4[2]~output_o\;

ww_HEX4(3) <= \HEX4[3]~output_o\;

ww_HEX4(4) <= \HEX4[4]~output_o\;

ww_HEX4(5) <= \HEX4[5]~output_o\;

ww_HEX4(6) <= \HEX4[6]~output_o\;
END structure;


