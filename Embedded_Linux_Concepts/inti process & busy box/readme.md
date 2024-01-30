## U_Boot Variables

**bootcmd:**

This variable outlines the boot command executed by U-Boot upon system boot. It typically comprises a sequence of U-Boot commands responsible for loading the kernel and device tree, configuring boot arguments (`bootargs`), and initiating the kernel boot process.

**bootargs:**

This variable specifies the arguments passed to the kernel during boot. It commonly includes parameters like the root filesystem, console settings, kernel options.

The `bootargs` variable plays a crucial role in specifying important kernel boot parameters, including the location of the root filesystem (`root=`) and the location of the init process (`init=`). Without this information, the kernel wouldn't know where to find the root filesystem and how to initialize the system.

1. **Root Filesystem (`root=` parameter):**
   - The `root=` parameter in `bootargs` specifies the device or partition where the root filesystem is located. It informs the kernel about the location of the filesystem it should mount as the root filesystem during the boot process.
   - For example, if the root filesystem is on the second partition of an SD card formatted with the EXT4 filesystem, the `root=` parameter might look like `root=/dev/mmcblk0p2 rootfstype=ext4`.
2. **Init Process (`init=` parameter):**
   - The `init=` parameter specifies the path to the init process that the kernel should execute as the first user-space process after booting. The init process is responsible for initializing the system and starting essential services.
   - Without this parameter, the kernel wouldn't know which process to execute as the init process, leading to a failure to initialize the system properly.
   - Example: `init=/sbin/init` specifies that the kernel should execute the `/sbin/init` binary as the init process.

3.**The `console=`** **parameter** in the `bootargs` variable specifies the console device that the kernel should use for displaying messages during the boot process. It's essential for reading **system logs**, especially during the early stages of booting when the root filesystem may not be fully available.

- **For BeagleBone:** If you're booting on a BeagleBone platform, you might specify `console=ttyS0` in the `bootargs` variable. This typically corresponds to the first serial port (`ttyS0`) on the BeagleBone, allowing you to read console messages over a serial connection.
- **For Windows:** If you're booting on a system running Windows, you might specify `console=tty0` 

**note that**...The kernel will still function without the `console=` parameter in the `bootargs` variable, but you won't be able to see the boot messages and system logs

-----------------------------------------------------------------------------------------------------

The `bootargs` variable can be specified in multiple places, and each location has a different priority in determining the final value of `bootargs`

1. **U-Boot Environment (e.g., `bootcmd` script):**

   - In U-Boot, you can set the `bootargs` variable in the U-Boot environment, typically as part of the boot script (`bootcmd`). This allows you to customize the boot arguments used by U-Boot when booting the kernel.

   - Example:

     ```
     setenv bootargs console=ttyS0,115200 root=/dev/mmcblk0p2 rootfstype=ext4
     ```

2. **Kernel Configuration (`menuconfig`, etc.):**

   - When building the Linux kernel, you can specify default kernel boot arguments in the kernel configuration (`menuconfig`). These settings become part of the kernel image and are used as default values .

3. **Device Tree Source (DTS) File:**

   - The device tree source (DTS) file for your hardware platform can also include `bootargs` settings. These settings are typically specified in the kernel's device tree and are used to customize boot arguments based on hardware-specific requirements.

   - Example (in DTS file):

     ```
     chosen {
         bootargs = "console=ttyS0,115200 root=/dev/mmcblk0p2 rootfstype=ext4";
     };
     ```

**which on has the highest priority  ?**

- The `bootargs` set in the bootloader's environment has the highest priority because it's specified directly in the bootloader's configuration.

- This allows for easy customization and supply of boot arguments by the bootloader, which can vary based on system configuration and requirements.

  -----------------------------------------

  The default kernel command string, specified in the kernel configuration (e.g., `CONFIG_CMDLINE`), serves as a fallback value for `bootargs` if it's not overridden elsewhere.

- If the bootloader's `bootargs` variable is not set or is empty, the kernel will use the default kernel command string as the boot arguments.

  -------------------------------------------------------------

  The Device Tree Source (DTS) file for the hardware platform may include a `bootargs` setting in the chosen node.

- The `bootargs` specified in the Device Tree serves as another fallback option for boot arguments.

- However, if the bootloader has already set its own `bootargs` variable, it takes precedence over the `bootargs` in the Device Tree.

  ----------------------------------

  The `bootargs` variable  typically includes several important parameters that are crucial for the kernel during the boot process. 

  1. **`root=`:**

     - Specifies the root filesystem for the Linux kernel.
     - It indicates the device or partition where the root filesystem is located.
     - Example: `root=/dev/mmcblk0p2` specifies the second partition (`p2`) of the MMC/SD card (`mmcblk0`) as the root filesystem.

  2. **`init=`:**

     - Specifies the path to the initial userspace process (typically `/sbin/init`).
     - It indicates the program that the kernel should execute as the first userspace process after booting.
     - Example: `init=/sbin/init` specifies that the `/sbin/init` binary should be executed as the init process.

  3. **`console=`:**

     - Specifies the console device for kernel messages and debugging output.
     - It determines where kernel messages are sent during the boot process.
     - Example: `console=ttyS0,115200` specifies the serial console (`ttyS0`) with a baud rate of `115200` as the console device.

  4. **`rootfstype=`:**

     - Specifies the filesystem type of the root filesystem.
     - It indicates the filesystem format used on the root filesystem partition.
     - Example: `rootfstype=ext4` specifies that the root filesystem is formatted with the Ext4 filesystem

     ---------------------------------------------

     1. **`rootwait`:**

        - `rootwait` is used in the `bootargs` to make the kernel wait for the root filesystem to become available before attempting to mount it.
        - It's commonly used when the root filesystem is located on removable media (e.g., SD card) or in scenarios where the kernel needs to wait for external devices to initialize.

     2. **`bootdelay`:**

        - `bootdelay` is an environment variable that specifies the delay (in seconds) before automatically proceeding with the default boot command.

        - It provides a time window during which users can interrupt the automatic boot process and enter U-Boot's command-line interface to interact with the bootloader.

          ```
          setenv bootdelay 5
          ```

-------------------------------------------------

## Device Drivers 

**/dev/loop:**

The `/dev/loop` device is utilized for mounting filesystem images or loopback devices.
It enables a file to be mounted as a block device, granting filesystem access to its contents.
Commonly employed for mounting  disk images, or creating virtual filesystems.

**/dev/mmc:**

The `/dev/mmc` device interface is commonly associated with SD (Secure Digital) cards, MMC (MultiMediaCard) cards


**/dev/sdb:**

The `/dev/sdb` device typically denotes a block storage device, such as a hard disk drive (HDD) or a solid-state drive (SSD), connected via the SCSI or SATA interface.
It's commonly utilized for secondary storage devices.

**/dev/sda:**

The `/dev/sda` device usually represents the first block storage device detected by the system, often serving as the primary storage device.
It could refer to a solid-state drive (SSD), a hard disk drive (HDD), or another block storage device.

----------------------------------------------------------------------------

## Root File System 

![img](https://www.devopsschool.com/blog/wp-content/uploads/2022/04/linux-file-system-tutorial-1.png)

![img](https://www.devopsschool.com/blog/wp-content/uploads/2022/04/linux-file-system-tutorial-2-1024x564.png)

1. **`/bin`:**

   - Contains essential executable binaries needed for basic system operation.
   - Binaries may be optimized for the device's architecture and functionality, focusing on lightweight and efficient implementations.

2. **`/boot`:**

   - Contains bootloader configuration files and possibly kernel images and device tree blobs (DTBs) specific to the embedded device.
   - Bootloader configurations may be customized for booting from specific storage media or network interfaces.

3. **`/dev`:**

   - Contains device files representing physical and virtual devices attached to the embedded device.
   - Device files are tailored to the device's hardware peripherals, such as UARTs, GPIO pins, and sensors.

4. **`/etc`:**

   - Contains system configuration files customized for the embedded device.
   - Configuration files may include network settings, startup scripts, and device-specific parameters.

5. **`/home`:**

   - May or may not be present, depending on whether the device supports user accounts and personal data storage.
   - If present, may contain user-specific configuration files or application data.

6. **`/lib` and `/lib64`:**

   - Contains shared libraries needed by executables in `/bin` and `/sbin`.
   - Libraries may be optimized for size and performance to conserve resources on the embedded device.

7. **`/mnt` and `/media`:**

   - May contain mount points for external storage devices or network shares.
   - Mount points are used to access additional storage or data sources beyond the embedded device's internal filesystem.

8. **`/proc` and `/sys`:**

   - Provides interfaces to kernel data and system information, as in a standard Linux system.
   - Information exposed through `/proc` and `/sys` may be specific to the embedded device's hardware and configuration.

9. **`/root`:**

   - Home directory for the root user, containing system configuration files and administrative scripts.
   - May also serve as a staging area for administrative tasks on the embedded device.

10. **`/sbin`:**

    - Contains system administration binaries needed for device configuration and maintenance.
    - Binaries may include utilities for network management, storage management, and system diagnostics.

11. **`/tmp`:**

    - Used for temporary files created by programs and scripts.
    - Temporary files may be stored in RAM or on persistent storage, depending on available resources and performance requirements.

12. **`/usr`:**

    - Contains user-accessible files and programs not essential for system booting and repair.
    - Binaries and libraries in `/usr` may be additional applications or packages installed on the embedded device.

13. **`/var`:**

    - Contains variable data files that may change in size or content during device operation.

    - Files may include log files, spool files, and other runtime data specific to the embedded device's functionality.

      -------------------

    # BusyBox

    BusyBox is often used to generate the necessary commands and utilities needed for an embedded Linux system.

    **Here is the steps that we are going to do** 

    1. **Selection of Utilities:**
       - BusyBox provides a comprehensive set of  utilities and commands.
    2. **Compilation for Target Architecture:**
       - BusyBox can be cross-compiled for the target architecture of the embedded system.
       - This ensures that the BusyBox binary is compatible with the processor architecture and instruction set of the target device.
    3. **Customization and Size Optimization:**
       - BusyBox's modular design allows developers to include only the necessary utilities, reducing the size of the final binary.
       - Developers can tailor BusyBox to include only the commands required for their specific application, conserving storage space and memory.
    4. **Inclusion in Root Filesystem:**
       - Once BusyBox is compiled with the desired configuration, the resulting binary is included in the root filesystem of the embedded device.
       - This involves copying the BusyBox binary to the appropriate location within the filesystem hierarchy.
    5. **Integration with Boot Process:**
       - BusyBox can be integrated into the boot process of the embedded system.
       - For example, BusyBox's `init` command can be used as the initial process launched by the kernel during system boot.
    6. **Execution and Resource Efficiency:**
       - BusyBox provides lightweight and efficient implementations of common commands and utilities.
       - This helps conserve system resources such as CPU time, memory, and storage space, making it well-suited for embedded systems with limited resources.



--------------------------------------------------------------------

### Install BusyBox

**Download Busy Box**

```
git clone https://github.com/mirror/busybox.git
```

![Screenshot from 2024-01-30 15-42-23](/home/mohamed/Pictures/Screenshots/Screenshot from 2024-01-30 15-42-23.png)

![Screenshot from 2024-01-30 15-42-42](/home/mohamed/Pictures/Screenshots/Screenshot from 2024-01-30 15-42-42.png)

**- Navigate busybox**

```
cd busybox
```

**configure your Cross-Compiler and the Target Architecture**

```
export CROSS_COMPILE=path/to/compiler/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm
```

Cross-compilation allows you to build BusyBox binaries that are  compatible with the target architecture, ensuring they can run on the  embedded system.

BusyBox needs to know the target architecture to generate binaries that are optimized for that architecture.

By setting the `ARCH` environment variable, you inform  BusyBox about the target architecture, enabling it to produce binaries  suitable for our device .

- The `CROSS_COMPILE` variable specifies the prefix used by the cross-compiler binaries (e.g., `arm-linux-gnueabihf-`).
- BusyBox uses this prefix to locate the cross-compiler tools (e.g., `gcc`, `ld`, `as`) needed for building the binaries.

**if you have your x-tools directory in the home directory you can write this command**  

```
export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```

![image-20240130155807073](/home/mohamed/.config/Typora/typora-user-images/image-20240130155807073.png)    

**We have to ways of Configuration**  **(Static Build & Dynamic Build )**(we will apply both )

but before we do that let us Know the difference between them 

BusyBox builds lies in how the BusyBox binary is linked with the libraries it depends on:

1. **Static BusyBox Build:**
   - In a static build, BusyBox is linked statically with all the libraries it requires.
   - This means that all the functionality provided by BusyBox is contained within a single binary file (`busybox`).
   - Static linking eliminates dependencies on external libraries, resulting in a larger binary size but greater portability and simplicity.
   - The static BusyBox binary can be executed on any system without worrying about compatibility with specific library versions.
2. **Dynamic BusyBox Build:**
   - In a dynamic build, BusyBox is linked dynamically with shared libraries (e.g., libc).
   - This means that BusyBox relies on external libraries installed on the system to provide certain functionality.
   - Dynamic linking results in a smaller binary size but introduces dependencies on specific library versions.
   - The dynamic BusyBox binary may require the presence of compatible shared libraries on the target system to run successfully.

the main differences between static and dynamic BusyBox builds are:

- **Binary Size:** Static builds result in larger binary sizes due to including all dependencies, while dynamic builds are smaller since they rely on shared libraries.
- **Portability:** Static builds are more portable since they do not depend on external libraries, while dynamic builds may require specific library versions to be present on the target system.
- **Complexity:** Static builds are simpler since they contain all required functionality within a single binary, while dynamic builds introduce dependencies that must be managed.

###  Let's apply the first Configuration 

#### 1-Static Build 

```
make menuconfig
```

![image-20240130161157606](/home/mohamed/.config/Typora/typora-user-images/image-20240130161157606.png)

- [x] Select Settings
- [x] Go to Build option
- [x] Select build static library (no shared libs)

![image-20240130161537875](/home/mohamed/.config/Typora/typora-user-images/image-20240130161537875.png)

- [x] Then Save and exit

**Now we want to Build the commands source files after we made the configurations **

```
make
```

![Screenshot from 2024-01-30 16-20-08](/home/mohamed/Pictures/Screenshots/Screenshot from 2024-01-30 16-20-08.png)

![image-20240130162407564](/home/mohamed/.config/Typora/typora-user-images/image-20240130162407564.png)

After ruining these commands you will find an executable called busybox

![image-20240130162623279](/home/mohamed/.config/Typora/typora-user-images/image-20240130162623279.png)  

how to ensure that this executable is compiled statically ?

![image-20240130163038635](/home/mohamed/.config/Typora/typora-user-images/image-20240130163038635.png) 

```
file busybox
```

The output of the `file` command indicates that the `busybox` file is an ELF (Executable and Linkable Format) 32-bit binary executable. 

- **File Type:** ELF (Executable and Linkable Format)
- **Architecture:** ARM
- **ABI Version:** EABI5 (Embedded Application Binary Interface version 5)
- **Linkage:** Statically linked
- **Stripped:** The binary is stripped of symbol and debugging information, reducing its size.

the fact that it is statically linked means that all necessary libraries are included within the `busybox` binary itself, making it independent of external libraries. 

**let's Generate the Binaries of the rootfs**

```
make install
```

![image-20240130163736788](/home/mohamed/.config/Typora/typora-user-images/image-20240130163736788.png)

![image-20240130163747332](/home/mohamed/.config/Typora/typora-user-images/image-20240130163747332.png)

a directory named `_install` after running the `make install` command suggests that the installation process created this directory to hold the installed files. Typically, the `_install` directory serves as a staging area where the files are temporarily  placed before being moved or copied to their final destinations in the  filesystem.

![image-20240130164242422](/home/mohamed/.config/Typora/typora-user-images/image-20240130164242422.png)

By setting the ownership of the installed files to `root`, you ensure that they can be executed by privileged users on the target machine without encountering permission denied errors. 

