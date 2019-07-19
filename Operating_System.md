[Goback to Readme](./readme.md)

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Operating System](#operating-system)
  - [Scheduling](#scheduling)
  - [Deadlock](#deadlock)
  - [Process Control Block](#process-control-block)
  - [Thread Control Block](#thread-control-block)
  - [Process vs Thread](#process-vs-thread)
  - [Thread Synchronization](#thread-synchronization)
    - [Race condition](#race-condition)
    - [Synchronization Primitive](#synchronization-primitive)
  - [Producer and Consumer](#producer-and-consumer)
  - [Paging](#paging)
    - [Virtual Memory](#virtual-memory)
      - [Pros](#pros)
      - [Cons](#cons)
  - [Dual Mode: Kernel and User](#dual-mode-kernel-and-user)
    - [Mode bit register](#mode-bit-register)
    - [Hardware timer](#hardware-timer)
    - [Mode transfer](#mode-transfer)
      - [User to kernel](#user-to-kernel)
        - [Interrupt](#interrupt)
        - [Processor execptions](#processor-execptions)
        - [System call](#system-call)
        - [Mode transfer process](#mode-transfer-process)
      - [Kernel to user](#kernel-to-user)
      - [Implement safe system call](#implement-safe-system-call)
  - [Inter Process Communication](#inter-process-communication)

<!-- /code_chunk_output -->

## Operating System

### Scheduling
In order to maximize the reponse time of each thread and the system throughput. We need scheduler to schedule the thread with different algorithm.

We want to avoid the starvation happens
- 


### Deadlock
- Mutual Exclusion: One or more than one resource are non-sharable (Only one process can use at a time)
- Hold and Wait: A process is holding at least one resource and waiting for resources.
- No Preemption: A resource cannot be taken from a process unless the process releases the resource.
- Circular Wait: A set of processes are waiting for each other in circular form.


### Process Control Block
Process control information is used by the OS to manage the process itself. This includes:

- The process scheduling state: The state of the process in terms of "ready", "suspended", etc., and other scheduling information as well, like priority value, the amount of time elapsed since the process gained control of the CPU or since it was suspended. Also, in case of a suspended process, event identification data must be recorded for the event the process is waiting for.
- Process structuring information: process's children id's, or the id's of other processes related to the current one in some functional way, which may be represented as a queue, a ring or other data structures.
- Interprocess communication information: various flags, signals and messages associated with the communication among independent processes may be stored in the PCB.
- Process Privileges in terms of allowed/disallowed access to system resources.
- Process State: State may enter into new, ready, running, waiting, dead depending on CPU scheduling.
- Process Number (PID): A unique identification number for each process in the operating system (also known as Process ID).
- Program Counter (PC): A pointer to the address of the next instruction to be executed for this process.
- CPU Registers: Indicates various register set of CPU where process need to be stored for execution for running state.
- CPU Scheduling Information: indicates the information of a process with which it uses the CPU time through scheduling.
- Memory Management Information: includes the information of **page table**, memory limits, Segment table depending on memory used by the operating system.
- Accounting Information: Includes the amount of CPU used for process execution, time limits, execution ID etc.
- I/O Status Information: Includes a list of I/O devices allocated to the process.

### Thread Control Block
- Thread Identifier: Unique id (tid) is assigned to every new thread
- Stack pointer: Points to thread's stack in the process
- Program counter: Points to the current program instruction of the thread
- State of the thread (running, ready, waiting, start, done)
- Thread's CPU register values
- Pointer to the Process control block (PCB) of the process that the thread lives on

The blow shoe the different states of thread
![](./IMG/Thread_States.png)
### Process vs Thread
- Threads are not independent of one other like processes as a result threads shares with other threads their code section, data section and OS resources like open files and signals. But, like process, a thread has its own program counter (PC), a register set, and a stack space.
- Processes start out with a single main thread. The main thread can create new threads using a thread fork system call. The new threads can also use this system call to create more threads. Consequently, a thread not only belongs to a process; it also has a parent thread - the thread that created it.
![](./IMG/Process_vs_Thread.png)

### Thread Synchronization


#### Race condition
A race condition occurs when two or more threads can access shared data and they try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. Therefore, the result of the change in data is dependent on the thread scheduling algorithm, i.e. both threads are "racing" to access/change the data.

#### Synchronization Primitive
[Semphor vs Mutex vs Spinlock](https://anandabhisheksingh.me/mutex-vs-semaphore-vs-spinlock/)
Semaphore vs Mutex:
Semaphore is used to limit the execution order of thread. It can be released by different thread.

Mutext provide the mutual exclution of some shared resources. It can only be released by the same process.

Locks:
- spin lock
  - With a spinlock, the thread simply waits ("spins") until the lock becomes available. This is efficient if threads are blocked for a short time, because it avoids the overhead of operating system process re-scheduling. 
  - It is inefficient if the lock is held for a long time, or if the progress of the thread that is holding the lock depends on preemption of the locked thread.
- mutex
  - provide mutual exclusion for the resources, and it will block the thread if the resrouce is no availble. CPU would reschedule the thread when the lock is available.

Semaphores:
- counting semaphore
  - Every time you wait on a semaphore, you decrease the current count. 
  - If the count was greater than zero then the decrement just happens, and the wait call returns. 
  - If the count was already zero then it cannot be decremented, so the wait call will block until another thread increases the count by signalling the semaphore.
  - Every time you release a semaphore, you increase the current count.
  - If the count was zero before you called signal, and there was a thread blocked in wait then that thread will be woken. If multiple threads were waiting, only one will be woken
  - If the count was already at its maximum value then the signal is typically ignored, although some semaphores may report an error.

- binary semaphore
  - it is pretty much similar to the mutex

### Producer and Consumer

This is the template for the producer and consumer models in Operating System, it uses the semaphore and mutext to protect resources like ring buffer
![](./IMG/Producer_and_Consumer.png)

### Paging

Paging is a memory management scheme that eliminates the need for contiguous allocation of physical memory. This scheme permits the physical address space of a process to be non–contiguous.

Pages has two states: **valid** and **resident**.

**Valid** means the page are allocated to the program, and it is legal for the process to access.

**Redident** means the page are already in the physical memory.

Page size usually 4KB or 8KB

Page Faults: when a process tries to reference a page not currently present in RAM, the processor treats this invalid memory reference as a page fault and transfers control from the program to the operating system.

Page table will store the mapping from virtual page number to physical page number.

OS Hanlding Page Faults:

- Determine the location of the data on disk.
- Obtain an empty page frame in RAM to use as a container for the data.
- Load the requested data into the available page frame.
- Update the page table to refer to the new page frame.
- Return control to the program, transparently retrying the instruction that caused the page fault.

Thrashing:

- thrashing occurs when a computer's virtual memory resources are overused, leading to a constant state of paging and page faults, inhibiting most application-level processing. A lots of code are using their address space actively
- Solution:
  - Increase the DRAM
  - Run fewer processes
    - reduce the page faults

#### Virtual Memory

##### Pros

- Virtual memory provide processes indepdent address space, and the address space can easily grow according to the requirement of applications
- Through the address translation and divide the memory into pages, it avoid the fragmentation of memory
- The mechanism of VM also enable the processes to flexible share data, and two virtual page can be mapped to the same physical memory location
- When too many process is running, if they can't fit in memory in all, the VM mechanism will page some idle process out of physical memory and make room for active processes.

##### Cons

- the translation process may affect the system performance

**TLB** was used for caching recent translation history, if the virtual address hit in **TLB**, there is no need to look the page table stored in the cache and memory.

In this image, the TLB was in MMU.

![](./IMG/Virtual_mem.png)

### Dual Mode: Kernel and User

In user mode, the process can't run privileged instruction (change the privilege level, adjust memory access permission, enable interrupt). In kernel mode, process can do whatever they want

In modern operating system, a process will has two stacks, one for executing user code, one for executing kernel code.

Four states of process's user and kernel stack

1. process running in user mode, its kernel stack is empty
2. process is running on the processor in kernel mode due to interrupt, processor exceptions, system calls. Its kernal stack is used to contain the CPU state of user level process and the current CPU state kernel handler
3. process in ready state. Its kernel stack contains the register and state to be stored when the process is resumed
4. process waiting for the I/O completion.  

#### Mode bit register

The mode bit in processor stores the mode information for the operating system. In user mode, processor check the each instruction before executing, and in kernal mode, the operating system runs with the protection check turned off.

#### Hardware timer

All computer systems include a hardware timer, when the timer expires, hardware will transfer control from user process to the kerne running in kernel mode.

#### Mode transfer

##### User to kernel

- Interrupt
- Processor execptions
- System call

###### Interrupt

The interrupt is asynchronous and signal the processor external event occured. Each interrupt must associate with a interrupt handler

Procedure:

1. Interrupt fires
2. The processor stop executing the current instruction
3. Processor save the current CPU state (PC, stack pointer, general purpose register, CPU status register), push them into stack
4. Through the interrupt vector table, the processor jump to runing instructions in associated handler
5. When the handler return, CPU recover its original state jsut before the interrupt occured by pop old register value out of stack
6. Running instructions in PC + 4

###### Processor execptions

The processor exception is a hardware event caused by user program which causes a transfer of control to the kernel. It can also caused by benign program by setting the breakpoint in it.

For example:

1. perform priviledge instructions
2. divides a interger by zero
3. access the memory outside of its address space
4. setting break point

###### System call

The user program request kernel perform a operation on user's behalf. It is a procedure provide by the kernel that can be called from user level

For example:

1. create or delete a file
2. malloc spaces for program

###### Mode transfer process

1. Mask the interrupt: hardware disable interrupt in the middle of switch from user mode to kernel mode
2. Save **three key values** into register: program counter, execution flags, stack pointer to internal temporary hardware register
3. Hardware switch the **stack pointer** to the base of kernel interrupt stack which is specified in special register
4. Hardware store **Three key value** into the interrupt stack in the kernel (because the user level can't save the three key value, so they can only be saved by the hardware to temporary registers)
5. Hardware change the program counter pointing the instructions in handler, and handler is invoked.
6. The handler will first save the rest of interrupted process's register and current stack pointer. (once handler save the CPU state of interrupted process, it can do whatever it please)
7. When return from the interrupt handler, it restore all the registers of interrupted program.
8. The user level process continue to run just like nothing happened

The process need cooperation between hardware and software.

##### Kernel to user

- Create new process
- resume after an interrupt, process exceptions, system calls
- switch to different process: scheduler in kernel determ which process to run

##### Implement safe system call


### Inter Process Communication

Inter process communication (IPC) is a mechanism which allows processes to communicate each other and synchronize their actions. 
The communication between these processes can be seen as a method of co-operation between them. Processes can communicate with each other using these two ways:
1. Shared Memory
2. Message passing
![](./IMG/InterProcessCom.png)