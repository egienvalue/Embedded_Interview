[Goback to Readme](./readme.md)


Hi I am JUn current  hte secn master studetnsin the unierst of michgan, my major is eledt an conputre engienr,. I have done amany inte pr re to firmw , dur my intersh at aliab i work ed them lots of my work is related buid the dve fiemra for some of them commercial project, such the caismar lockre for packe , ware hos sensot node it can monitronig the hum an tem dat in re time the hae eh build the appli bas on the B soc and also wiring drivers for difere cper devices.

w ha the ms war h  ses nod I ahve done projecg related to wireless sensor network and out of order processro and compilers .
That p wat ohelp peo toeasiy locate the fere spaces in the librar. We use sensors to detect human body at each table, Wa hae  sensorne to collect all dat and tranmit them tot hte cloud. and The occupandy staets will be presented by the web interface. THe senso we us ti ir sesnor, it is used to detect humanb ody heat.

the libra help poel easily loeat in The sn mesnesor nod nearly. 

what sepcifci 

THe reson for the rle., we bsit jobffirmware.

many functoion. 
Local globcar se local varaibl. 

static global variabl.
static befor out function.







- Cainiao Box
  - What specific work you have done in the team
    - Build the application based on TI RTOS and Bluetooth Low Energy protocol stack
    - Design driers for peripheral ICs it used, real time clock, key pad scan IC, LED driver(Programmerbal IC), and motors driver(dual H bridge)
  - How do you estimate the power consumption
    - The Bluetooth SoC we use the power consumpition calculator provided by TI to estimate power consumption in different condition( different connnection interval, different advertise ment interval 300ms is enough)
    - For the motor, because we want to lock be opened in one second. We assume that the motor will work 10 times per days. Each time, it only rotate for one second. Through that, we can easily calculate the power consumption of the motor.
    - the power consumpiton of other IC, I only calculate its power consumption in sleep mode.
    -  

  - Introduce each peripheral IC's functionality
    - Real time clock
    - Key pad scan
    - LED driver
    - Motor driver
  - Micro controller feature you used in this project
    - I2C
    - SPI
    - GPIO Interrupt
    - Timer
  - Testing
    - Test application for testing if the hardware works well
    - In the initialization function, I write the code to operate RTC, LED driver and motor driver. It is fairly easy to see if the hardware works. The log mechanism provided by TI is also helpful. Through that when it detect error code, the corresponding error information will be printed out.
    - Usually using the printf to print necessary informations through the debugger.
    - Using the GPIO to control LED and show if the program runs correctly
    - If the bluetooth communication has problems.  Using the sniffer to grab the bluetooth packet in the air, and parse it using the wireshark.


- Warehouse sensors
Introduce what work you have done in this project

- Smart Lock


- Wireless Sensor Network
Introduce what work you have done in this project
Our solution is actually a kind of compromise.
- Compiler


- MIPS R10K Processor
Introduce this poject?

- HTTP proxy server
Introduce how the server work?

- Distributed Chatting Service
Introduce how you make this project?