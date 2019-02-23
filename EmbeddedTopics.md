# General Topics

## Bluetooth Low Energy

### Overview

Bluetooth 4.2 allows two systems of wireless technology, Bluetooth Basic Rate (BR: BR/EDR for Basic Rate/Enhanced Data Rate) and Bluetooth Low Energy.

The base rate was usually applied in applications like wirelss headphones. The low engery system was created to trasmit small package of data.
![Protocol Stack](BLE-Stack.jpg)

The Bluetooth Low Energy protocol stack consists of host and controller.
- the controller, it consists of three parts: Host-cotroller interfaces, Link layer, and Physical layer.
- the Host, it consists fo GAP, GATT, SM, ATT, L2CAP.
- Any application or profile always sit on hte GAP and GATT layer. Usuallly we only need to take care of GAT and GATT layer.

The GAP layer control the RF state of the device, there are five RF states for a device:
- Standby
- Advertising: advertiser transmited data without connecting
- Scanning: scanner scan for the advertiser
- Initiating: innitiator is a device which respond to a advertiser 
- Connected: when connected, the device become either a master for slave. the connection initialtor is the master, the one accept the request is the slave.

The Logical Link Control and Adaptation Layer Protocol (L2CAP) layer provides data encapsulation services to the upper layers, allowing for logical end-to-end communication of data.


### GAT


#### State diagram of a device
![GAT](GAT.jpg)

- Standby: The device is in the initial idle state upon reset.
- Advertiser: The device is advertising with specific data letting any initiating devices know that it is a connectible device (this advertisement contains the device address and can contain some additional data such as the device name).
- Scanner: When receiving the advertisement, the scanning device sends a scan request to the advertiser. The advertiser responds with a scan response. This process is called device discovery. The scanning device is aware of the advertising device and can initiate a connection with it.
- Initiator: When initiating, the initiator must specify a peer device address to which to connect. If an advertisement is received matching that address of the peer device, the initiating device then sends out a request to establish a connection (link) with the advertising device with the connection parameters described in Connection Parameters.

#### Connection Parameter


- Connection interval is the amount of time between two connection events
-  If there is no application data to be sent or received, the two devices exchange link layer data to maintain the connection
- Slave Latency - This parameter gives the slave (peripheral) device the option of skipping a number of connection events. 
- Effective connection intervals is the interval between two successful connection event when the slave latency is specified.

### GATT

the GATT layer of the Bluetooth low energy protocol stack is used by the application for data communication between two connected devices

- The GATT server: the device containing the characteristic database that is being read or written by a GATT client.
- The GATT client: the device that is reading or writing data from or to the GATT server.

#### GATT Characteristics and Attributes

- Characteristics as groups of information called attributes
- Attributes are the information actually transferred between devices
- 
#### GATT Security


## Bluetooth Mesh




## Embedded C

### Unsigned vs Signed
![](补码到无符号.png)
Convert the unsigned int to signed int, minus 2^32 if the unsigned int greater than 2^31;
Covert the signed int to unsigned int, plus 2^32 if the signed int less than 0;

```c++
// Function to determine overflow for add two unsigned number
bool uadd_ok(uint32_t x, uint32_t y){
    if(x + y < x)
        // here means overflow
        return false;
    return true;
}

// Functoin to determin overflow for add two signed number
bool sadd_ok(int x, int y){
    if(x > 0 && y > 0){
        if(x + y  <=0)
        // overflow when add two positive integer
            return true;
    }
    if(x < 0 && y< 0){
        if(x + y >=0)
        // overflow when add two negative integer
            return true;
    }
    return false;
}

```
### Floating
The representation of floating point in register are shown above.

![](floating_point.png)
![](IEEE_float.png)

### Struct

#### Data alignment

Many computer system has restrictions on data alignment, they only allow the program to access address which is multiple of some value K (typically 2, 4, or 8), and this restriction is called memory alignment.
![](Memory_alignment.png)
![](Memory_align2.png)

### Function pointer
![](Function_pointer.png)
![](Function_pointer2.png)
```c++
int (*fp) (int); // here remember to define (*fp), otherwise, it means that the function with pointer return type
```

### Dynamic allocate memory
```c++
ptr = (int*) malloc(100 * sizeof(int));	//allocates the specified number of bytes

ptr = realloc(ptr, new_size);	//increases or decreases the size of the specified block of memory, moving it if necessary

ptr = (float*) calloc(25, sizeof(float));	//allocates the specified number of bytes and initializes them to zero
free(*ptr)	//releases the specified block of memory back to the system
```
### Static qulifier
- Static for global variable: access it limited in this file
- Static function: limited acces in file
- Static local variable in function: the value will be maintained between function calls
- 

### Diference between Macro and Inline

## Micro-controller


### Peripheral Communication

#### SPI

#### I2C


#### UART



## Linux


### Booting







### Kernel








## Computer Architecture


### 





## Operating System

### Deadlock
- Mutual Exclusion: One or more than one resource are non-sharable (Only one process can use at a time)
- Hold and Wait: A process is holding at least one resource and waiting for resources.
- No Preemption: A resource cannot be taken from a process unless the process releases the resource.
- Circular Wait: A set of processes are waiting for each other in circular form.

### Thread Control Block
- Thread Identifier: Unique id (tid) is assigned to every new thread
- Stack pointer: Points to thread's stack in the process
- Program counter: Points to the current program instruction of the thread
- State of the thread (running, ready, waiting, start, done)
- Thread's register values
- Pointer to the Process control block (PCB) of the process that the thread lives on


### Virtual Memory
![](Virtual_mem.png)


## Computer Networks





## Compiler Construction

### Lexical Analysis
It turns a stream of characters into a stream of tokends. Tokens is to define a class of word. Like in engish, we have noun, objective, verb. For programming language we have integer, string, variable and so on.

Typical, in this step, we use regular expression to match these tokens.

### Parsing
Parsing will generate the abstract syntax tree fron the tokens. Parsing using the context free language to describe the grammer.

You can think about the if expression, the root of the syntrax tree will be if_exp, the child will be the condition, codes in the if statement. else 


### Type checking
When we got the syntax tree, then we do type checking of the code. The inference rule will define the type of different expressions. Like for the if statement, the type of its conndition must be bool. For the function call the type checker will check if the type of paramter and the arguments of that function call meet the definition.

### THe last step: code generation


### Program organization

When the program is invoked, the operating system will allocate spaces for this program. The machien code will be loded into the space.

### Optmization
In order to do optimization, we need convert the code into a intermediate representation which is convenient for us to analysis the patterns in the code.
For the dead code elimination, we only do it for assignment instruction. Through the liveness analysis, where the dead code is, and remove it from my syntax tree.



## Advanced Embedded System

### Building Interfaces
Hardware interfaces allow the programmer to not worry about how exactly the hardware works. It creats a level of abstraction. It allows the application to be written independent of platform or target. 

A good hardware interface has three key features:
- easy to use
- efficent 
- portable to other hardware platform

Three competing requirements (triangle):
- usability
- efficiency
- portability

Software or Hardware first?
In terms of interface design, we can start the software design firstly. Give the pre-designed API about how the interface will look like.

### Real-time system
The official definition of a real-time operating system is that: the correctness of system not only rely on the result but also the time of the result was produced.

Why RT system is Hard
- people want a cheap processor as possible
- there are non-cpu resources to worry about
- Validation is hard: it is a simple question of how do people know the system miss the deadline

Validation is catually the process to prove that your solution meet the constriants.

Property of scheduling task:
- Fix/dynamic priority: the prioriity of tasks can be assigned dynamicly or staicly. D: EDF, S: RM
- Preemptive/Non-preemptive tasks: non-preemptive tasks it task that can not be interuptre once it start

Critical instant analysis:
- The worst case for RMS is that all tasks happen to start at the exact same time.


### Kernel

Kernel is a core part of operating system for managing system resources. It more like a bridge between appliation and hardware.
Kernel process and user process has different adress spaces.


# Resume Details



## CC2640 Bluetoot SoC


## TI-RTOS

The TI-RTOS is a RTOS kernel, specially designed for TI's Bluetooth SoC, like CC2640. It is a real-time, pre-emptive, and multi-threaded operating system.

### Threading module
It has four thread modules. Hardware interrupts, software interrupts, task and idle task.
The TI RTOS manages four distince context levels of thread execution
![image info](fig-tirtos-threads.jpg)

#### HWI
- threads are threads with highest priority in TI-RTOS
- used to perform the time critical task which are subject to the hard deadline.
- no blocking API may be called HW ISR



#### SWI
- provide addtional level of priority between HWI and normal tasks. 
- SWI is triggered programmatically by calling certain SWI modules API
- Swi allows the HWI to defer the less time critical and more time consuming works to a lower-priority task
- Swi require only enough space to store the context of each Swi priority level, while task actually use a sperate stack for each thread


#### Task
- task thread has lower priority than the SWI, and higher priotiryt than the IDLE task
- TI-RTOIS actually provided many mechanisim for thread synchronization like Semaphores, Event, Message queues



#### Idel Task




### Thread Synchronization Model

#### Semaphores

- Semaphores can be counting semaphores or binary semaphores
- Counting semaphore will track the number of times the semaphore was post. When one task want to grad the semaphore it will see it the count is greater than 0, then decrement the count
- Binary semaphore can be regraded as mutex

#### Event
- It was implemented through the semaphore
- The task can be pending on several event happen.
- Event can be posted by calling the Event API in TI-RTOS


#### Message Queue

- Message queue provides thead-safe unidirectional message passing module, like a FIFO. 
- It was commonly used to pass messages from high priority task to low priority task.
- For the key pad, once it was pressed, it will triger the HWI to pass the message to the user application task, it will read the key value from the Key Pad scanning IC. The work associated to the inerrupt can defered to tasks for processing.
- The queue is also used to process the message sent from the Blueooth Protocol Stack. 


#### Tasks 
  

Different states of tasks:

- Running: task is currently running
- Ready: task is scheduled for execution
- Blocked: task is suspended from execution
- Terminated: task is terminated from execution
- Inactive: task is on inactive list

