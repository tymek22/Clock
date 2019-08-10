# Clock

<br>This smart Clock is made to resemble a traditional wall clock. It shows the time using two rings of RGB LEDs. The inner (smaller) ring is for the hours, while the outer circumference displays the minutes together with the seconds.
<br>The clock is a smart clock, it features a microcontroller which has BLE connectivity. By using a mobile application, the clock can be controlled wirelessly. Below is a photo of the clock showing the time 9:41

![front](/pics/front.jpg)

## <b>Components</b><br>
The clock is built from various components and materials. The main ones are:
 - Frame, 3D printed
 - Power supply, 5V adapter with sufficient power
 - RGB LED strips, 1 strip of 60 and 1 strip of 48 LEDs (WS2812b)
 - PIR sensor
 - CR2032 battery
 - Wires
 - PCB
 - Other components for the PCB
 
## <b>Frame</b><br>
 
 The frame has been designed in Autodesk Fusion 360. It looks like this:<br>
 ![frame](/pics/frame.jpg)<br>
 
 The electronics are placed inside, the only components which are outside of the clock body are the LEDs as well as the wires to a power adapter. Below on the left, you can see the inside of the body and on the right, how it looks in reality.<br>

<img align="left" src="/pics/frame_inside.jpg" width="420" />
<img align="right" src="/pics/inside.jpg" width="420" />
<p>&nbsp;</p>
Because of all those wires, it looks very messy, but fortunately, this can not be seen from the outside.
The fact that one meter of such a LED strip contains 60 LEDs makes it easy, because one hour has 60 minutes. So each LED represents a minute or second. The inner circle is smaller, so 60 LEDs can't fit there.
I have chosen the number of LEDs for the hours to be 48, firstly, because it's a multiple of 12 (and there are 12 hours on a clock). And secondly, that makes the inner circle's circumference 80cm, which fits physically well. Below, the alignment
of the LEDs on the clock casing is shown. The first LED does not start at the top and to make things more complicated, the LEDs run counter-clockwise. Of course it would be better to have the LEDs arranged more logically,
but it was not possible to easily mount it in that way. It's not a big problem, because the arrangement of LEDs can be addressed in software.
 <br><img align="left" src="/pics/led_placement.png" width="100%" />
 <p>&nbsp;</p>
 
## <b>Connections</b><br>

![overview](/pics/overview.jpg)<br>
Here is an overview of the connections. These are all the components, which are not directly on the PCB, but are inside the case. These parts can not be put directly on the PCB, because they are mounted too far away from each other.

## <b>Schematic and PCB</b><br>
 
<img align="left" src="/pics/schematic.png" width="420" />
<img align="right" src="/pics/pcb.png" width="420" />
<p>&nbsp;</p> 
Here you can see the schematic and the PCB layout. The brain of the clock is a Cypress CYBLE-224110-00. It is a module which includes everything what is needed. There are many other Bluetooth modules,
like the NRF51822 or ESP32. However, I have chosen this module over the alternatives, because of its clear IDE and good documentation. It is also very flexible regarding the pins and peripherals.
It features runtime reconfigurable serial communication blocks, as well as programmable logic blocks.
The Cypress module is an ARM Cortex M0 microcontroller, with Bluetooth Low Energy (BLE) and all standard peripherals. This module runs at 3.3V, but the power supply is 5V, so obviously, some voltage regulator is needed.
This is handled by the TLV733P, a simple 5V to 3.3V low-dropout regulator. I liked it because it's small and doesn't require a capacitor to function properly. Because of this, its total footprint is very minimal.
There are two more ICs used. One of them is the DS3231, a famous real-time clock. It's precise and doesn't need an external crystal oscillator. Additionally, it can output a 1Hz square wave at a pin, which makes it ideal for a clock application.
The last major component is SN74AHCT125, a quadruple bus buffer gate, which in my case is used as a voltage level shifter. It converts the 3.3V output of the microcontroller to 5V, which goes to the LED strips.
I tried to make the PCB as small as possible, so it could fit easily inside the case, but also to save on costs. Around the edges, there are multiple pins for various reasons. Some are to connect the MCU with other components,
and some are used for debugging only. 

## <b>Power Consumption</b><br>
All values were measured at maximum brightness.

|  Configuration | Current Draw | Voltage | Power |
| ------------- | ------------- | --- | --- |
| No LEDs  | 78 mA  |  5.39 V |  0.42 W |
| Lamp with one color  | 1.58 A  |  5.25 V |  8.30 W |
| Lamp with white color | 4.17 A |  5.02 V |  20.93 W |
| Low-power clock |  120 mA |  5.38 V |  0.65 W |
| High-power clock |  850 mA |  5.30 V |  4.51 W |

## <b>Software</b><br>
#### MCU Firmware<br>
The firmware is created in the PSoC Creator IDE from Cypress. It runs on the CYBLE-224110-00 module. The module can be upgraded wirelessly by a BLE OTA update.
The main files and code reside in the `CYBLE-224110-00 Clock firmware.cydsn` folder and the code itself is explained using comments.<br>
The RTC is communicating with the MCU via I2C and the RTC outputs a 1Hz square wave. This square wave is used as an interrupt, to easily let the microcontroller check the time every second and update the LEDs.<br>
There is also a PIR sensor. The purpose of this sensor is to check whether there is a person nearby. If there is no one, the clock can show the time with less LEDs turned on, to save on electricity. The full array of LEDs is only used when
there is actually someone who can see it.<br>
Additionally, an LDR is used to see how light or dark it is. This information is used to automatically set the brightness of the clock. If it's really dark (at night), the clock displays the time in the power-saving mode too, so it's not emitting
too much light at night.

#### iOS App<br>
The mobile app is developed for iOS only, as at the time of development my main mobile phone was an iPhone. It is created in XCode, Apple's IDE. The app can fully control the clock. It can set the time to either the iPhone's time,
or to a custom value input by the user. The clock can also be put in the Device Firmware Update (DFU) mode, in which the clock can receive an OTA update. The clock has a feature where it can become a lamp and this
can also be controlled from the application. The user can choose a color and a brightness and send it to the clock. This lamp mode can obviously be turned off as well. Lastly, the app displays some information from the clock.
It shows whether the clock is in the lamp mode. Whether the PIR is on or off. And the light intensity is shown as well. It's also possible to see the temperature of the clock, but this is of limited use, because the temperature inside the
case differs from the outside temperature. I included the temperature for debugging and safety purposes only.

## <b>Improvements</b><br>
In retrospect, I see that there are points to improve on.
<br>One of them is the clock frame. For a next version, I would make proper mounting for all parts, so they don't just sit inside the case, but are firmly attached somewhere. A fixed position would also make the wiring easier,
but because I started from scratch without any reference, it was difficult to set fixed positions for everything, I needed this little flexibility.
<br>Initially, I wanted to use a connector for the power input to the clock, but the connector turned out to be too big. I didn't use the connector and just soldered the cable directly inside the casing. It would be better to have a connector,
so the next time, I would look for a nice one and add it.
<br>Another thing is the PCB. I used only the first revision in the final product, so all errors had to be fixed manually. However, if I was to make a new revision, I would change a few things. The main issue was with the breakout pins.
I would change all pins to one sort. It would be nice if the LDR had its own pins as well, instead of the small SMD pads. In reality, the pads were smaller than I thought and it was hard to solder the leads. It worked for some time,
but after a while, the wires broke and one pad came off. I solved this by reusing the UART Tx pin for the LDR. The Tx pin was not needed anyway, because this issue appeared at the later stages of debugging and I used Bluetooth to see
all data.
<br>As for the software, it would be nice to do something with the LED colors. Some kind of animations and/or random color variations. The iOS app could get a better UI as well. I know that I'm not a good designer, so now it's
just functional and not very nice.

<p>&nbsp;</p> 
<img src="/pics/clock.gif" />