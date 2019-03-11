[Goback to Readme](./readme.md)

- [Compiler Construction](#compiler-construction)
  - [Lexical Analysis](#lexical-analysis)
  - [Parsing](#parsing)
  - [Type checking](#type-checking)
  - [THe last step: code generation](#the-last-step-code-generation)
  - [Program organization](#program-organization)
  - [Optmization](#optmization)
  - [Garbage Collection](#garbage-collection)

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

Start function call:
- If caller want to reuse some value stored in RAX RDX, it need push them into stack, and retrive them after function call
- Caller Push the arguments into stack int reverse order ( last parameter first)
- Caller Push the return adress into stack
- Callee Push old base pointer into stack (The base pointer is used to access elements int the stack by adding offset to it). It points the address manipulated by callee.
- Callee push all the local variable into the stacks
- Callee start execution its instructions

After funcion call ends:
- Callee save the return value in to RAX
- Deallocate all local variable by reset the stack pointer to base pointer
- Restore caller's base pointer value by pop it from the stack
- Execute "ret" instruction, it will find the return address from the stack.

(If we have very large argumetns or local variable, the stackoverflow will happens)
![](./IMG/x86_Stack_Frame.png)

Memory Layout for 32-bit machine. The difference between 32-bit and 64-bit machine is how the size of a memeory address.
![](./IMG/Memory_layout.png)

X86 has 8 general purpuse register. 
- EAX usually will be used as accumulator for alrithmetic instructions. Also it will store the return value.
- 
[x86-64 Reference Sheet](./IMG/x86-64.pdf)

Tree types of operand
- Imediate
- Register
- Memory reference (access memeory location according to computed address)
  - Indirect addressing
  - Absolute value addressing
  - Base + displacement addressing 
  - Scaled index addressing
![](./IMG/x86_OperandForms.png)

[X86 Assembly Guide](http://flint.cs.yale.edu/cs421/papers/x86-asm/asm.html)

Assembly Code example for exchange value. Here the machine is 32bit, if for the 64-bit machine, the xp will be movq 2*8(%ebp), %edx
![](IMG/x86_AssemblyCode_Exchange.png)

### Optmization
In order to do optimization, we need convert the code into a intermediate representation which is convenient for us to analysis the patterns in the code.
For the dead code elimination, we only do it for assignment instruction. Through the liveness analysis, where the dead code is, and remove it from my syntax tree.

- Unboxing: 
  - For these objective oriented language, they regard the int variabla a class. But for compiler, it need generate more code for classes comparing with just integer value. Same for the string class.
  - After we finish code generation, the interger value need to be boxed into a class.

- Loop Unrolling
  - Loop unrolling is used for reducing the number of times of executing branches.
  - Branches consume more CPU cycles than normal instructions.

- Loop Invariants
  - Some variable value in the loop never changes. For these variables
  - These variable can be put outside of the loop

- Constant propagation
  - Propage the constant value to rest of the code

- Dead code elimination
  - some assignments are assigning value to dead variables. These assignments can be removed.
  - We use data flow analysis to get the dead variables

- Register allocation
  - Especially for alrithmatic instructions, the naive approach is use the stack the calculate the result. But it is pretty slow.
  - In order to avoid access memory frequently, we need allocate registers to variables as many as possible.
  - Know how long the variable will stay alive is important, and for each alive veriable we need a register to store its value.


### Garbage Collection

Some memory allocated to programs many never be used again, the garbage collection will recollect these spaces and release them to other programs. 

Tow basic garbage collection algorithm: basic idea is to scane the heap find the unreachable object and free them.
- Mark and Sweep
  - Mark Phase: 
    - so for each object we have a mark bit. Once it is created, its mark bit will set to zero. Then we make each node that the user can access.
    - In the process of marking, we regarded these object as tree node, and use the DFS to mark all rechable object. If a node is reachable, any nodes it points to will be reachable.
  - Sweep Pase:
    - The sweep phase will clear all memory with mark bit zero, and release them to other programs.
  - Pros and Cons
    - Pros: 
      1. It handles the case with cyclic references, even in case of a cycle, this algorithm never ends up in an infinite loop. 
      2. There are no additional overheads incurred during the execution of the algorithm.
    - Cons: 
      1. Cause the “Fragmentation” problem

- Stop and Copy

[Copying Garbage Collection](http://www.cs.cornell.edu/courses/cs312/2003fa/lectures/sec24.htm)


- Reference counting