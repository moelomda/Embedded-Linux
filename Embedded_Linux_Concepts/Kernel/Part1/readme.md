# Linux Kernel 

The Linux kernel is the core component of the Linux operating system, serving as the intermediary between hardware and user-level applications. It manages system resources, provides essential services, and facilitates communication between software and hardware components.

![fundamental-architecture-of-linux (1)](https://github.com/moelomda/Embedded-Linux/assets/88937815/65fed528-ef6b-43ed-9a2d-2a8ec97af80d)

# Components of the Linux Kernel

## System Calls:

System calls are the interface between user-level applications and the kernel. They allow applications to request services from the kernel, such as file operations, process management, and communication.
Examples of system calls include `open()`, `read()`, `write()`, `fork()`, `exec()`, and many others.
System calls are defined in the kernel's source code, providing a way for user space to interact with the kernel's functionality.

## Device Tree Blob (DTB/DTBO):

The Device Tree is a data structure used by the kernel to describe the hardware configuration of the system, offering a platform-independent way to represent hardware.
The Device Tree Blob (DTB) is a compiled version of the Device Tree source file. It is often provided to the kernel during the boot process to configure and initialize hardware devices.

## Kernel Modules:

Kernel modules are pieces of code that can be loaded and unloaded into the running kernel without requiring a reboot. They extend the functionality of the kernel by providing additional drivers, filesystems, or other features.
Modules are separate from the kernel image and are often distributed as `.ko` files.
Examples of kernel modules include device drivers for specific hardware, filesystem modules, and network protocol modules.
Common commands for managing kernel modules include `insmod` (insert module), `rmmod` (remove module), and `modprobe` (a more feature-rich module management tool).

**we will explain every component  in details later in this file** 

-----------------------------------------------------------------------------

## **arm_linux_uclibc_gnueabihf**

This target  typically refers to the **ARM architecture using the Linux kernel,** the GNU C Library (glibc), and the "hard float" (hf) ABI (Application Binary Interface). It is commonly used for cross-compiling applications to run on ARM-based Linux systems.

## arm_none_eabi

This target  indicates the ARM architecture with **no operating system (bare-metal)** and the Embedded ABI (eabi). It is often used for cross-compiling firmware, bootloaders, or **bare-metal applications** that run directly on ARM microcontrollers or other embedded systems without a full operating system.

## arch_vendor_os_lib

### arch
Represents the target architecture for which you are building software. Examples include arm, x86_64, aarch64, etc.

### vendor
Refers to the entity or organization providing the toolchain or compiler for the specified architecture. Examples include gnu, apple, qualcomm, etc.

### os
Stands for the target operating system for which the software is being compiled. Examples include linux, darwin (macOS), windows, etc.

### lib
Indicates the standard library or runtime library associated with the target. Examples include glibc, uclibc, musl, etc.

-----------------------------------------------------------------------------------------------------------------------

## arm_bb_linux_gnueabi app

### ARM Architecture:
- **arm:** Specifies the target architecture as ARM.

### Barebox Bootloader:
- **bb:** Indicates the use of Barebox as the bootloader. Barebox is a lightweight and flexible bootloader 

### Linux Operating System:
- **linux:** Specifies the use of the Linux kernel as the operating system.

### GNU Embedded ABI:
- **gnueabi:** Specifies the use of the GNU Embedded ABI, a set of conventions used for C and C++ function calls in the ARM architecture.

  ---------

  

## when you compile any application in linux  it will be divided into logic and  system call

### Logic Component:

Contains the main application logic, algorithms, and functionalities. This part is typically responsible for the core functionality of the application.

### System Call Component:
Deals with interactions with the operating system. This part might include code for making system calls, handling interrupts, or interacting with Linux-specific features.
## How the Kernel Loads an  Application to RAM 

**what happens when you type ./app in terminal to run an application ?**

## Command Execution:

When you run `./app`, the shell interprets the command and initiates the execution of the specified executable file (`app`).

## System Calls and Kernel Handling:

- The shell uses system calls like `exec()` to replace its own process image with the process image of the new executable (`app`).
- After the execution of the new program (`app`), it takes over the process, inheriting the Process ID (PID) and other attributes from the original shell process.
- The kernel is responsible for loading the program into memory, setting up its initial state, and preparing it for execution.

## File System and Disk I/O:

- If the executable (`app`) is stored on an SSD card, the kernel interacts with the file system to access the executable.
- File system-related system calls ( open()`, `read()`) are used to read the binary code of the executable from the SSD card.

## Loading into RAM:

- The kernel loads the executable into the RAM (Random Access Memory) of the system.

## Process Creation:

- The kernel creates a new process for the executable, and this process becomes the running instance of your application.
- The new process has its own address space, program counter, stack, and data space.

# User Space and kernel Space 
![user-space-vs-kernel-space-simple-user-space](https://github.com/moelomda/Embedded-Linux/assets/88937815/210f7392-18cb-42cc-82a2-841d27ebd2f3)



## User Space:

The user space is the part of the system where user applications and tasks run. If a task or instruction can be executed **without requiring access to hardware resources or privileged operations**, it can remain within the user space.

**Note: Privileged Operations in a Computer System**

Privileged operations refer to operations that require higher levels of privilege within a computer system. These operations often involve critical system resources and functionalities .

> **Manipulating CPU Control Registers:**
> - Operations that involve configuring or altering CPU control registers, which control various aspects of the processor's behavior. 

> **Handling Interrupts and Exceptions:**
> - Management of system interrupts and exceptions, 

> **Configuring System Clock:**
> - Adjusting settings related to the system clock, including timekeeping and synchronization. 

> **Loading and Unloading Device Drivers:**
> - Operations related to the dynamic loading and unloading of device drivers. Device drivers are crucial for communication between the operating system kernel and hardware devices.

> **Accessing Kernel Memory:**
> - Directly accessing and manipulating kernel memory, which contains sensitive data and critical system structures.

```markdown
### Limitation in Accessing Hardware:

In the user space, there is no direct access to hardware, and users do not have the privileges to interact with hardware components. 
```

## Kernel Space:

The kernel space is the part of the operating system that has direct access to hardware and manages system resources. Tasks that require access to hardware or privileged operations, such as system calls or device interactions, typically involve the kernel.

```markdown
### Privilege Mode:

In the kernel space, operations are carried out in a privileged mode. This mode allows the kernel to execute instructions and access hardware resources that are restricted from user space. 

Tasks running in privilege mode have the authority to execute privileged instructions, interact with hardware components, and manage system-level operations. This level of privilege is crucial for tasks that involve low-level system management, including handling interrupts, managing memory, and facilitating system calls.
```

## Can any application perform without using kernel ?

#### yes ...........

## Execution without Kernel Involvement:

If the process can perform its job entirely within the user space, it means that it doesn't need to make system calls or interact with the kernel. This can be the case for purely computational or algorithmic tasks that don't involve accessing external devices, managing system resources, or requiring special privileges.

## Examples:

Examples of tasks that can be executed without involving the kernel include mathematical computations, data processing, and other algorithmic tasks. These activities only involve the manipulation of data in memory and don't require special system privileges.

---------------------------------------------------------------------------------------

**Note(very important ): Processes as Containers and System Calls**

**A process is a container** , it has  the program's code, data, and resources. If an application requires interaction with hardware or needs to access resources outside its own process, **it  has to make a system call.** System calls act as the bridge between user-level applications and the kernel, allowing the application to request services and operations that require privileges or access to system resources.

## Mode Switching:

- **Transitions between Modes:**
  Transitions between privileged and non-privileged modes occur during certain events, such as system calls, interrupts, or exceptions. When a user-level program needs to perform a privileged operation (e.g., I/O operation, memory allocation), it triggers a mode switch, allowing the kernel to execute the necessary operation on its behalf.

- **Ensuring Security:**
  Mode switching helps ensure that critical operations are performed by trusted components (kernel) and prevents unauthorized access to sensitive resources.
  
  ------------------------------------------------------------------------------------------------------
  
  
  
- ```markdown
  ## Interrupt Handling in Different Modes:
  
  ### Privileged Mode:
  
  - **Interrupt Handling:**
    In privileged mode, the kernel is responsible for handling interrupts. Interrupts generated by hardware devices or external events  require attention from the operating system. The kernel has the necessary privileges to manage and respond to these interrupts.
  
  - **Priority Handling:**
    The kernel can prioritize and manage the handling of interrupts based on their urgency and significance. It ensures that critical operations are promptly addressed, contributing to efficient system responsiveness.
  
  ### Non-privileged Mode:
  
  - **Interrupt Handling:**
    In non-privileged mode, user-level processes do not directly handle interrupts. Instead, they rely on the kernel to manage and respond to interrupts on their behalf.
  
  - **Limited Access:**
    User-level processes do not have the necessary privileges to directly interact with hardware or manage interrupt requests.
  
  ### Mode Switching During Interrupts:
  
  - **Transition to Privileged Mode:**
    When an interrupt occurs, there is often a transition from non-privileged mode to privileged mode. This transition allows the kernel to take control and handle the interrupt, ensuring proper management of system resources.
  
  ```

## printf () Function in C (what is happening in the background ? )

**`at first we need to ask , why printf() need to make a system call ?`** 

**`because printf ()  use the console (screen) to display data and as we mentioned before to access hardware from user space you need to make a system call`**. 

## code example 

```
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

The `printf` function is part of the C Standard Library (libc). and `printf` is responsible for formatted output.

### User Space to Kernel Space Transition:

The `printf` function, residing in user space, needs assistance from the kernel to interact with hardware for tasks like writing to the terminal.

### System Call (write):

Inside the implementation of `printf`, there is typically a system call made to the kernel. The relevant system call for console output is usually `write`. The `write` system call allows the user space program to write data to a file descriptor. The file descriptor associated with the standard output (`stdout`) is usually 1.

> (you don't need to understand this implementation all you need to know that `printf ()` has `write()` on it  )

```c
// Simplified printf implementation using the write system call
int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    // Using the write system call to output data to stdout (file descriptor 1)
    write(1, buffer, len);

    va_end(args);

    return len; // Returning the number of characters written for simplicity
}
```



### Kernel Handling (write System Call):

1. The kernel receives the `write` system call and performs necessary actions to write the specified data to the console or terminal.
2. The kernel checks permissions, performs any necessary buffering, and interacts with the appropriate device driver or subsystem to output the data.

### Console Output:

The data ("Hello, World!\n") is ultimately displayed on the console or terminal.

----

## System Call Table in Linux Kernel :

![image00](https://github.com/moelomda/Embedded-Linux/assets/88937815/8520e014-f8e8-497f-abff-dd6f0e264444)


The system call table is a critical data structure used by the operating system kernel to map system call numbers to the corresponding functions that handle those system calls. 

**System Call Number:**
Each system call has a unique number assigned to it. For example, `open` might have a specific number, `read` another, and so on.

**System Call Invocation:**
When a user-level application makes a system call (e.g., through the `syscall` instruction in assembly or a library function like `syscall` or `int 0x80`), it specifies the system call number.

**Indexing the System Call Table:**
The kernel uses the system call number as an index into the system call table to retrieve the corresponding function pointer.

**Function Execution:**
The kernel then executes the function pointed to by the retrieved function pointer, representing the actual implementation of the requested system call.

**Transition to Kernel Space:**
During this process, the CPU transitions from user space to kernel space, granting the kernel the necessary privileges to execute the system call.

**Return to User Space:**
After the system call is executed, control returns to user space, and the result  is provided to the user-level application.

## ARM System Calls:

On ARM architectures, when performing a system call, the register `r7` is often used to pass the system call number. Additionally, ARM architectures may use a "swi" (Software Interrupt) instruction to initiate a system call. 

### Register `r7` in ARM:

- **General-Purpose Register:**
  In ARM architecture, `r7` is one of the general-purpose registers. It is commonly used as a parameter or for various purposes.

### System Call Number in `r7`:

- **Passing System Call Number:**
  When making a system call on ARM, the system call number is typically passed in register `r7`. The kernel uses the value in `r7` to determine which system call the user space application is requesting.

## `syscall` Instruction:

**Usage:**

- The `syscall` instruction is associated with ARM architectures that follow the ARMv7-A and ARMv8-A architectures.

**ARMv7-A and ARMv8-A:**

- On these architectures, the preferred instruction for system calls is often `syscall`.

**assembly Code:**

```markdown
    write (1 , *buffer , size ); 
    is translated in assembly to ......
    mov r7, 4          ; System call number for write
    mov r0, 1          ; File descriptor for stdout(console)
    ldr r1, =buffer    ; Pointer to the buffer
    mov r2, size       ; Size of the buffer
    syscall
```

## note that you have a user stack and kernel stack 

## User Stack:

- **Located in the memory space reserved for user processes (user space).**
- **Used for managing function calls, storing local variables, and handling control flow within user-level code.**
- **Each user process has its own user stack.**

## Kernel Stack:

- **Located in the memory space reserved for the kernel (kernel space).**
- **Used for managing function calls, storing local variables, and handling control flow within the kernel.**
- **Each process that transitions from user space to kernel space (e.g., during a system call) typically uses a separate kernel stack.**

When a user space program makes a system call, it triggers a transition to kernel space. During this transition, the user stack is usually switched to a kernel stack to avoid potential issues with the user stack being manipulated while in kernel mode. 

-----------------------------------------------------------------------

## System Call Handler:

![introduction-to-system-calls-1-1641802026](https://github.com/moelomda/Embedded-Linux/assets/88937815/e7c2baf2-6529-46e8-a85b-f50f1f97ac91)


A **system call handler** is a function within the kernel that handles a specific system call requested by a user space program. Each system call has a unique identifier , and the kernel uses this identifier to determine which handler should be executed. The handler is responsible for performing the operations associated with the system call and returning the results to the user space program.

**-note that it is like (ISR)**

### How a System Call Handler Works:

#### lets back again to user Space .......

**User Space Program:**
- A user space program makes a system call by invoking a system call interface a library function like `write` or `open` in C).

**System Call Number:**

- The system call interface determines the system call number associated with the requested operation. Each system call has a unique number.

**User Space to Kernel Space Transition:**

- The user space program transitions from user mode to kernel mode, typically through a special instruction or interrupt.

**Dispatcher:**

- The kernel dispatcher determines the appropriate system call handler based on the system call number. This involves looking up the system call number in the system call table.

**Argument Validation:**

- The kernel validates the arguments passed by the user space program to ensure they are valid and within acceptable ranges. 

**System Call Handler Execution:**

- The kernel executes the corresponding system call handler. This handler is a function within the kernel that performs the actual work associated with the system call.

**Kernel Space Processing:**

- Inside the system call handler, the kernel has access to privileged operations and system resources. The handler performs the necessary actions, such as interacting with hardware, managing memory, or accessing filesystems.

**Return to User Space:**
- After the system call handler completes its execution, the kernel returns control to user space, and the user space program continues its execution.

### Symbolic Representation:

```c
// User space program invoking system call
int result = syscall_number(arg1, arg2, ...);

// Kernel space (highly simplified)
long syscall_handler(int syscall_number, long arg1, long arg2, ...) {
    switch (syscall_number) {
        case SYS_WRITE:
            // Implementation of write system call
            return write(arg1, arg2, ...);
        case SYS_READ:
            // Implementation of read system call
            return read(arg1, arg2, ...);
        // ... other system calls ...
        default:
            // Handle unsupported system calls
            return -ENOSYS;
    }
}
```

## How we Can implement our own system Call ?

Implementing a system call involves modifying the kernel.

## General Steps:

### 1. Identify System Call Table:

Locate the system call table in the kernel source code. 

### 2. Choose a System Call Number:

Choose a unique system call number for your new system call. Avoid conflicts with existing system call numbers.

### 3.Write the System Call Handler:

Implement the functionality of your system call by writing a system call handler........ writing the actual code that will be executed when the system call is invoked.

### 4. Update System Call Table:

Add an entry to the system call table, associating your chosen system call number with **the address of your system call handler.**

### 5. recompile and Install the Kernel:

Recompile the modified kernel source code to generate a new kernel image. Install the new kernel on the system. 

**symbolic representation of system call implementation** 

**symboliiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiic**

```
// Include the appropriate kernel headers
#include <linux/kernel.h>
#include <linux/errno.h>

// Define a unique system call number
#define SYS_ITI 333

// System call handler for ITI
asmlinkage long sys_iti(void) {
    printk("Hello from ITI\n");
    return 0;
}

// LCD device driver function to print to the LCD
void LCD_Print(const char *message) {
   contribure @address 
}

// Entry point for LCD_Print function
asmlinkage long sys_lcd_print(const char *message) {
    LCD_Print(message);
    return 0;
}

```

**Include Kernel Headers:**

- Use the appropriate kernel headers. I used `<linux/kernel.h>` and `<linux/errno.h>`.

**Define a System Call Number:**

- I defined a symbolic name (`SYS_ITI`) for the system call number (333). This number needs to be unique and not conflict with existing system call numbers.

**System Call Handler:**

- The `asmlinkage` keyword is often used in the kernel to indicate that the function follows the calling convention of the architecture.
- The `sys_iti` function is the system call handler that gets invoked when the user space program calls `sys_iti()`.

**Print to Kernel Log:**

- The `printk` function is used to print messages to the kernel log. The format string is "Hello from ITI\n".

**Error Handling:**

- I included the `perror` function, which is often used in user space programs for printing error messages along with their descriptions. 

**LCD Device Driver Function:**

- The `LCD_Print` function is part of LCD device driver. It is responsible for interacting with the hardware to display a message on the LCD.
- The implementation of `LCD_Print` would involve low-level operations, such as writing to specific hardware registers or using other mechanisms to control the LCD.

**System Call for LCD Printing:**

- I added a system call named `sys_lcd_print` that invokes the `LCD_Print` function. The `sys_lcd_print` system call allows user space programs to request LCD printing through the kernel.

  --------------

## How to make the kernel abstracted from hardware  ? 

as we explained before the device tree .

### Device Tree  Description

Device Tree is a data structure that describes the hardware configuration of a system. 

## Platform-Independent Hardware 

Instead of hardcoding hardware details directly into the source code of the operating system or device drivers, the hardware configuration is described in a separate Device Tree file. This allows for a platform-independent representation that can be used across different architectures and systems.

## Driver  Discovery and Configuration

Device drivers in the operating system can parse the information present in the Device Tree to discover and configure hardware components dynamically. This enables drivers to adapt to different hardware configurations without requiring modifications to the driver code.

## Avoid Hardcoding Hardware Details

By utilizing the Device Tree, developers can avoid hardcoding hardware addresses, interrupt numbers, and other configuration details directly in the driver code. Instead, these details are specified in the Device Tree file, providing a more flexible and adaptable system .

## Example: LCD Driver Using Device Tree

**in the previous code example**

`void LCD_Print(const char *message) {`
   `contribure @address` 
`}`

the address will be then replaced with the appropriate address from the dtb file  

**that is  how we make kernel abstracted from HW**

------------------------------------------

# Kernel Modules

A kernel module is a loadable and unloadable piece of software code that can be inserted into or removed from the Linux kernel dynamically. It extends the kernel's capabilities by providing additional functionalities, such as device drivers, filesystems, or support for specific hardware.

![unnamed](https://github.com/moelomda/Embedded-Linux/assets/88937815/6de2bad5-1e73-40a8-91da-d5ebc5533592)


suppose that we want to make a new module called GPIO

**you are now in kernel Space **

```c
#include <kernel_headers>

// Symbolic GPIO initialization function
void GPIO_Init() {
    contribute @address dtb;
    // The address will be obtained from the Device Tree Blob (dtb)
    // Actual implementation would involve initializing GPIO based on the provided address
}
```

### Building a Kernel Module for ARM Architecture

When building a kernel module for ARM architecture, you need to use a cross-compiler that is specifically designed to generate binaries for the ARM architecture. The appropriate compiler toolchain for ARM is typically prefixed with the target architecture`arm-linux-gnueabi` 

## For ARM (arm-linux-gnueabi):

### Compiler:
```bash
arm-linux-gnueabi-gcc
```

 the `.ko` extension indicates a loadable kernel module. When you build your GPIO module for ARM architecture using a cross-compiler, you obtain a file named `gpio.ko`. This file can then be loaded into the Linux kernel at runtime using tools like `insmod` or `modprobe`.

```bash
# Compile GPIO module for ARM architecture
arm-linux-gnueabi-gcc -o gpio.o -c gpio.c
arm-linux-gnueabi-ld -o gpio.ko -r gpio.o

# Load GPIO module into the kernel
insmod gpio.ko
```

## Dynamic Modules and Static Modules 

### Dynamic Modules (Loadable Kernel Modules):

**Definition:** Dynamic modules are pieces of code that can be loaded into and unloaded from the Linux kernel at **runtime**. 

- **Loading:** Loaded into the kernel using tools like `insmod` or `modprobe` during runtime.
- **Unloading:** Can be removed from the kernel using tools like `rmmod`.
- **Flexibility:** Provides flexibility to add or remove functionalities on-the-fly without rebooting.
- **File Extension:** Dynamic modules typically have a `.ko` (kernel object) file extension.

## Static Modules:

**Definition:** Static modules are integrated directly into the Linux kernel during the kernel's compilation process. They are part of the kernel image (Zimage).

**Characteristics:**

- **Loading:** Inherent in the kernel image and loaded automatically during the kernel boot process.
- **Unloading:** Cannot be unloaded or removed from the kernel at runtime.
- **Incorporation:** Compiled directly into the kernel image during the kernel build process.
- **File Extension:** No specific file extension, as they are part of the kernel image.

### **why we don't use static modules only** ?

### The Impact of Using Many Static Modules

1. **Kernel Image Size:**
   - Static modules increase the size of the kernel image because all functionalities are compiled into it. 

2. **Booting Time:**
   -  loading a larger kernel image with many static modules can contribute to increased boot times.

## Kernel Modules vs. Kernel Drivers 

**Kernel Modules:**

**Characteristics:**

- Modules can provide various functionalities, such as device drivers, filesystems, or other kernel services.
- They are loaded and unloaded dynamically based on system needs.
- Modules are often used to add or remove support for specific hardware devices or features.

**Kernel Drivers:**

**Definition:** A kernel driver (or device driver) is a specific type of kernel module that facilitates communication between the kernel and a hardware device. 

**Characteristics:**

- **Drivers are a subset of kernel modules** and are loaded as modules or built directly into the kernel.

- They manage the communication between the operating system and specific hardware components

- Drivers expose standardized interfaces, allowing user-space programs and the kernel to interact with the associated hardware without needing to know the low-level details.

  -----

## To complete kernel Configuration refer to  [Anas Repository](https://github.com/anaskhamees/Embedded_Linux/tree/main/EmbeddedLinuxTasks/Kernel).
