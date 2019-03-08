[Goback to Readme](./readme.md)

- [Embedded C](#embedded-c)
  - [Endianess](#endianess)
  - [Bit-field](#bit-field)
  - [Volatile](#volatile)
  - [Macro vs Inline func](#macro-vs-inline-func)
  - [Unsigned vs Signed](#unsigned-vs-signed)
  - [Floating](#floating)
  - [Struct](#struct)
    - [Data alignment](#data-alignment)
  - [Function pointer](#function-pointer)
  - [Dynamic allocate memory](#dynamic-allocate-memory)
  - [Static qulifier](#static-qulifier)
  - [Const qulifier](#const-qulifier)
  - [Diference between Macro and Inline](#diference-between-macro-and-inline)

## Embedded C

### Endianess 
- Big endian: MSB placed at the lowest addr 
- Little endian: LSB placed at the lowest addr 
```c++
int main() 
{ 
    int x = 1; 
    char *y = (char*)&x; 
    printf("%c\n",*y+48); 
} 
```
### Bit-field


### Volatile

- Non-automatic variables referenced within an interrupt service routine
A global or static variable used in an interrupt will appear to change unexpectedly at the task level, so the volatile keyword is needed to inform the compiler that this will happen.

- Variables shared by multiple tasks in a multi-threaded application 
- Hardware registers in peripherals (for example, status registers)

```c++

uint8_t volatile * p_ledreg = 0x10000000;

//The valatile should be placed before the *
// In the above code, the variable p_legreg is a pointer to a volatile 8-bit unsigned register located at address 0x10000000.

typedef volatile struct
{
uint8_t reg1;
uint8_t reg2;
uint8_t _reserved;
uint8_t reg3;

} mydevice_t;

mydevice_t * p_mydevice = 0x10000000;

// or
typedef struct
{
uint8_t reg1;
uint8_t reg2;
uint8_t _reserved;
uint8_t reg3;

} mydevice_t;

mydevice_t volatile * p_mydevice = 0x10000000;
```

### Macro vs Inline func

Macro:
- expanded by the preprocessor, directly replace the code section
- just do the replacement according to the define
```c++
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
```
Inline func
- only parsed by the compiler
- it is actually programs which can access the member variables

### Unsigned vs Signed
![](./IMG/补码到无符号.png)
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

![](./IMG/floating_point.png)
![](./IMG/IEEE_float.png)

### Struct

#### Data alignment

Many computer system has restrictions on data alignment, they only allow the program to access address which is multiple of some value K (typically 2, 4, or 8), and this restriction is called memory alignment.
![](./IMG/Memory_alignment.png)
![](./IMG/Memory_align2.png)

### Function pointer
![](./IMG/Function_pointer.png)
![](./IMG/Function_pointer2.png)
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

### Const qulifier

- define a const pointer, so you cannot modify the pointer itself, but the program modifer the memory pointed by this ptr
```c++
char* const ptr;
```
- define a pointer, pointer to constant. Here, the value of pointer can be changed, but the value stored in the memory address pointed by the ptr can't be changed.
```c++
const char* ptr;
char const* ptr;
```
```c++
const char* const ptr;
```


### Diference between Macro and Inline