EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:18f4550
LIBS:l293d
LIBS:ft232_usb-uart_converter
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "9 jul 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PIC18F4550 U***?
U 1 1 53BDB503
P 5550 4250
F 0 "U***?" H 5550 4350 70  0000 C CNN
F 1 "PIC18F4550" H 5550 4150 70  0000 C CNN
F 2 "" H 5550 4250 60  0000 C CNN
F 3 "" H 5550 4250 60  0000 C CNN
	1    5550 4250
	1    0    0    -1  
$EndComp
$Comp
L L293D U?
U 1 1 53BDC0C9
P 2350 1750
F 0 "U?" H 2200 1700 60  0000 C CNN
F 1 "L293D" H 2200 1700 60  0000 C CNN
F 2 "~" H 2200 1700 60  0000 C CNN
F 3 "~" H 2200 1700 60  0000 C CNN
	1    2350 1750
	1    0    0    -1  
$EndComp
$Comp
L L293D U?
U 1 1 53BDC0D8
P 2350 3250
F 0 "U?" H 2200 3200 60  0000 C CNN
F 1 "L293D" H 2200 3200 60  0000 C CNN
F 2 "~" H 2200 3200 60  0000 C CNN
F 3 "~" H 2200 3200 60  0000 C CNN
	1    2350 3250
	1    0    0    -1  
$EndComp
$Comp
L FT232_USB-UART_CONVERTER U?
U 1 1 53BDC38B
P 9500 3350
F 0 "U?" H 9250 3450 0   0000 C CNN
F 1 "FT232_USB-UART_CONVERTER" H 9550 3700 60  0000 C CNN
F 2 "~" H 9350 3350 60  0000 C CNN
F 3 "~" H 9350 3350 60  0000 C CNN
	1    9500 3350
	1    0    0    -1  
$EndComp
$Comp
L USB J?
U 1 1 53BDC3C9
P 9500 1400
F 0 "J?" H 9450 1800 60  0000 C CNN
F 1 "USB" V 9250 1550 60  0000 C CNN
F 2 "~" H 9500 1400 60  0000 C CNN
F 3 "~" H 9500 1400 60  0000 C CNN
	1    9500 1400
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 53BDCD23
P 4250 4100
F 0 "#PWR?" H 4250 4190 20  0001 C CNN
F 1 "+5V" H 4250 4190 30  0000 C CNN
F 2 "" H 4250 4100 60  0000 C CNN
F 3 "" H 4250 4100 60  0000 C CNN
	1    4250 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53BDCD43
P 4250 4250
F 0 "#PWR?" H 4250 4250 30  0001 C CNN
F 1 "GND" H 4250 4180 30  0001 C CNN
F 2 "" H 4250 4250 60  0000 C CNN
F 3 "" H 4250 4250 60  0000 C CNN
	1    4250 4250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 53BDCD65
P 6850 3800
F 0 "#PWR?" H 6850 3890 20  0001 C CNN
F 1 "+5V" H 6850 3890 30  0000 C CNN
F 2 "" H 6850 3800 60  0000 C CNN
F 3 "" H 6850 3800 60  0000 C CNN
	1    6850 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53BDCD74
P 6850 3950
F 0 "#PWR?" H 6850 3950 30  0001 C CNN
F 1 "GND" H 6850 3880 30  0001 C CNN
F 2 "" H 6850 3950 60  0000 C CNN
F 3 "" H 6850 3950 60  0000 C CNN
	1    6850 3950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 53BDD148
P 3100 2250
F 0 "#PWR?" H 3100 2340 20  0001 C CNN
F 1 "+5V" H 3100 2340 30  0000 C CNN
F 2 "" H 3100 2250 60  0000 C CNN
F 3 "" H 3100 2250 60  0000 C CNN
	1    3100 2250
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 53BDD1A4
P 3100 3750
F 0 "#PWR?" H 3100 3840 20  0001 C CNN
F 1 "+5V" H 3100 3840 30  0000 C CNN
F 2 "" H 3100 3750 60  0000 C CNN
F 3 "" H 3100 3750 60  0000 C CNN
	1    3100 3750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 53BDD1F2
P 3050 3300
F 0 "#PWR?" H 3050 3300 30  0001 C CNN
F 1 "GND" H 3050 3230 30  0001 C CNN
F 2 "" H 3050 3300 60  0000 C CNN
F 3 "" H 3050 3300 60  0000 C CNN
	1    3050 3300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 53BDD29C
P 3050 1800
F 0 "#PWR?" H 3050 1800 30  0001 C CNN
F 1 "GND" H 3050 1730 30  0001 C CNN
F 2 "" H 3050 1800 60  0000 C CNN
F 3 "" H 3050 1800 60  0000 C CNN
	1    3050 1800
	0    -1   -1   0   
$EndComp
$Comp
L +12V #PWR?
U 1 1 53BDD370
P 1150 2250
F 0 "#PWR?" H 1150 2200 20  0001 C CNN
F 1 "+12V" H 1150 2350 30  0000 C CNN
F 2 "" H 1150 2250 60  0000 C CNN
F 3 "" H 1150 2250 60  0000 C CNN
	1    1150 2250
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR?
U 1 1 53BDD3B4
P 1200 3750
F 0 "#PWR?" H 1200 3700 20  0001 C CNN
F 1 "+24V" H 1200 3850 30  0000 C CNN
F 2 "" H 1200 3750 60  0000 C CNN
F 3 "" H 1200 3750 60  0000 C CNN
	1    1200 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3000 3450 6600
Wire Wire Line
	2950 3000 3450 3000
Wire Wire Line
	2950 1950 3900 1950
Wire Wire Line
	2950 1500 4100 1500
Wire Wire Line
	1400 2250 1150 2250
Wire Wire Line
	2950 1800 3050 1800
Wire Wire Line
	2950 1650 2950 1800
Wire Wire Line
	2950 3300 2950 3150
Wire Wire Line
	3050 3300 2950 3300
Wire Wire Line
	3100 3750 2950 3750
Wire Wire Line
	2950 2250 3100 2250
Wire Wire Line
	3150 2850 2950 2850
Wire Wire Line
	3150 2450 3150 2850
Wire Wire Line
	3150 2450 7100 2450
Wire Wire Line
	7100 2450 7100 3300
Wire Wire Line
	7100 3300 6600 3300
Wire Wire Line
	3300 3600 2950 3600
Wire Wire Line
	3300 2600 3300 3600
Wire Wire Line
	3300 2600 6950 2600
Wire Wire Line
	6950 2600 6950 3200
Wire Wire Line
	6950 3200 6600 3200
Wire Wire Line
	6850 1350 2950 1350
Wire Wire Line
	6850 3100 6850 1350
Wire Wire Line
	6600 3100 6850 3100
Wire Wire Line
	6750 2100 2950 2100
Wire Wire Line
	6750 3000 6750 2100
Wire Wire Line
	6600 3000 6750 3000
Wire Wire Line
	4500 5700 4500 5400
Wire Wire Line
	9850 5700 4500 5700
Wire Wire Line
	9850 3650 9850 5700
Wire Wire Line
	4200 5300 4500 5300
Wire Wire Line
	4200 5600 4200 5300
Wire Wire Line
	9650 5600 4200 5600
Wire Wire Line
	9650 3650 9650 5600
Connection ~ 6850 3900
Wire Wire Line
	9050 3900 9050 3650
Wire Wire Line
	9150 2100 9150 2200
Wire Wire Line
	10300 2100 9150 2100
Wire Wire Line
	10300 1600 10300 2100
Wire Wire Line
	9900 1600 10300 1600
Wire Wire Line
	6850 3900 6850 3950
Wire Wire Line
	6600 3900 9050 3900
Wire Wire Line
	6850 3800 6600 3800
Wire Wire Line
	4250 4200 4500 4200
Wire Wire Line
	4250 4250 4250 4200
Wire Wire Line
	4500 4100 4250 4100
Wire Wire Line
	9400 2050 9400 2200
Wire Wire Line
	9000 2050 9400 2050
Wire Wire Line
	9000 1600 9000 2050
Wire Wire Line
	9150 1600 9000 1600
Wire Wire Line
	9650 1950 9650 2200
Wire Wire Line
	9100 1950 9650 1950
Wire Wire Line
	9100 1750 9100 1950
Wire Wire Line
	9150 1750 9100 1750
Wire Wire Line
	10050 2200 9900 2200
Wire Wire Line
	10050 1750 10050 2200
Wire Wire Line
	9900 1750 10050 1750
Wire Wire Line
	2950 3450 3650 3450
Wire Wire Line
	3650 3450 3650 6600
Text GLabel 3450 6600 3    60   Input ~ 0
Y axis motor
Text GLabel 3650 6600 3    60   Input ~ 0
Y axis motor
Wire Wire Line
	3900 1950 3900 6600
Wire Wire Line
	4100 1500 4100 6600
Text GLabel 3900 6600 3    60   Input ~ 0
X axis motor
Text GLabel 4100 6600 3    60   Input ~ 0
X axis motor
$EndSCHEMATC
