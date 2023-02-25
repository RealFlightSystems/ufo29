![image (22)](https://user-images.githubusercontent.com/11479564/221340612-1e6882e6-8dd1-47a8-8b7d-bca8b48e16e8.PNG)
![Basic Demo](https://user-images.githubusercontent.com/11479564/221340814-89bd20d3-72c9-4726-b827-45449d3af305.gif)

# ufo29
Programmable 210 NEOPIXEL LED HPR saucer/spool

## Features
- 4.54 in Diameter
- 29mm motor mount
- 105 NEOPIXEL per side, dedicated MCU per side (2 CPU's for A/B sides)
- Multiprocessor design - A/B Sides completely independent strobe/pattern
- 3.7-5V input power
- [2-Pin JST-PH](https://www.amazon.com/dp/B097BVPB38) for 1S LIPO battery (400mA and more recommended)
- 3A Buck/Boost onboard for 1S Lipo
- Button for top/bottom selected (opposite side of button affected)
- Arduino compatible ATTINY85 @16Mhz
- 105 LED's per side
- Modified Adafruit Neopixel library to fit maximum number of full programmable neopixels on Attiny85
- Programmable sequences

## Setup

- Download and install the [Arduino IDE](https://www.arduino.cc/en/software) (time of this writing it is Arduino IDE 2.0.3)
- Connect the [AVR-ISP-MK2 Olimex](https://www.mouser.com/ProductDetail/Olimex-Ltd/AVR-ISP-MK2?qs=C3feHhap9Pq3CI42wNu37Q%3D%3D)  device programmer to the target and connect USB cable to your system.
- Start the Arduino IDE
- Install Arduino AVR Boards
- Install [AttinyCore](https://github.com/SpenceKonde/ATTinyCore/) to enable ATTINY85 Board support
  - AttinyCore can be installed using the boards manager. The boards manager URL is:
     - http://drazzy.com/package_drazzy.com_index.json

   - File->Preferences on a PC, or Arduino->Preferences on a Mac, enter the above URL in "Additional Boards Manager URLs
   - Tools -> Boards -> Boards Manager... 
    - Select "ATTinyCore by Spence Konde" and click "Install".

## Dev Tooling and Setup

- [5V 4A Power Supply](https://www.adafruit.com/product/1466)
- [JST-PH 2 Pin Adapter](https://www.adafruit.com/product/261)
- [2.1mm DC Barrel Jack Adapter](https://www.adafruit.com/product/1328) for Power Supply
- [AVR-ISP-MK2 Olimex](https://www.mouser.com/ProductDetail/Olimex-Ltd/AVR-ISP-MK2?qs=C3feHhap9Pq3CI42wNu37Q%3D%3D)
- Tagconnect [TC2030-IDC-NL](https://www.tag-connect.com/product/tc2030-idc-nl) AVR ICSP adapter

## Develop
- Load the Arduino sketch in sw folder
- Build/upload sketch



## Vehicle Build
- Order a 12in piece of thin-wall 29 mm fiberglass tube from [Mach-1 Rocketry](https://www.mach1rocketry.com/product-page/fiberglass-motor-mount-tubes) for the motor mount (you need 7")
- You also need a carbon fiber launch lug adapter, you can order a unidirectional carbon fiber rod for a 1/8" Estes rod here from [Rockwest Composites](https://www.rockwestcomposites.com/uni-c1-l30)
- For length, order 7" to 12" quantities
- The optimal length for a saucer or spool is L =1.5 D Where D is the diameter of the spool
- The Saucer Plate is - 4.54" diameter so you need a 6.8" long 29mm tube for optimal stability.
- See also [Spool Rocket Center of Pressure](https://aerorocket.com/FinSim/Spool-Rocket.pdf)

## Flight Setup
- Use a small battery and tape to the side of the airframe section used as motor mount
- The [400ma Adafruit](https://www.adafruit.com/product/3898) LIPO is perfect to tape to the side of the motor tube and gets about 15 minutes with Pikachu strobe sequence activated
- Use the [ASP-Rocketry Hang-time](https://www.asp-rocketry.com/ecommerce/Hang-Time-Competition-Parachutes.cfm?cat_id=41) Mylar parachute and "dog barf" for protection. Spectacular night flying is possible with the 36" Mylar chute.



