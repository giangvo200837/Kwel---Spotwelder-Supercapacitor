# PIC Microcontroller Spotwelder SuperCAP
 
# Supercapacitor Spot Welder – DIY & Fully Adjustable

This spot welder is a small project designed for use with two or three pairs of Nippon Chemi-Con 1400F 2.5V capacitors connected in series. The circuit features a dual-pulse control system with adjustable timing and setting memory, ensuring precise and reliable welds.
# Key Features:
- Using PIC18 Microcontroller.
- Integrated LM2596 CC 2A Charger.
- Cell Balancing Circuit with customizable discharge resistors and mosfet DPAK package.
- Input Voltage Range: DC 10V-15V (max).
- OLED Display (128x64) for monitoring and adjustments.
- Using 10 MOSFETs AUIRF8409, IRL40SC228 or any D2PAK-7Pin.
- Using Mosfet Driver MIC4424 non-inverting with 3A/Port/5MOS total 6A for all Mosfet, reduce rise time and fall time for reduce power lost and dissipation, with 10 IRL40SC228, total time charge is ~400nS.
# Two Operation Mode:
- Auto Mode (duration by +0.5s per set).
- Manual Mode (controlled via foot pedal or switch).

   Everything is done by hand (DIY) without having to spend any processing steps, easy to do at home.
   
![alt text](https://github.com/giangvo200837/Kwel---Spotwelder-Supercapacitor/blob/main/Pictures/3D.png)

I didn't add vias at the main power line and moved the part name on the top overlay because that's not necessary when diy PCB.

![alt text](https://github.com/giangvo200837/Kwel---Spotwelder-Supercapacitor/blob/main/Pictures/IMG_2330.jpg)

# Special Thanks
Simple Circuit SSD1306 Libraly custom for CCS C Compiler.

https://simple-circuit.com/ssd1306-oled-ccs-c-library/



