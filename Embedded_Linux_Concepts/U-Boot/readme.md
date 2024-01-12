- # Vexpress Emulation with QEMU and U-Boot


  ## Create Blank SD Card Image

  Content related to creating a blank SD card image goes here.

  ## Downloading and Installing U-Boot Step by Step

  Step-by-step instructions for downloading and installing U-Boot should be placed here.

  ## Boot Configuration and TFTP Setup

  Information about configuring the boot settings and setting up TFTP should be placed here.

- 

  ## Create Blank SD Card Image

  A "blank" SD card image is like an empty disk. It's a file that will represent the storage for your emulated system. In this guide, we'll create an SD card image instead of buying one 😆.

  ### Partition the SD Card Image

  Partitions are logical sections of the storage. You create partitions on the SD card image to organize the space. For example, we'll create two partitions:

  1. **Boot Partition:** This is where the bootloader resides.

  2. **RootFS Partition:** This is for the root filesystem

     

  ### Format Partitions

  Each partition needs a filesystem, a way to organize and store files. We'll format the partitions as follows:

  - **Boot Partition:** Formatted with FAT16, a common filesystem for bootloaders,They have a simpler structure compared to more advanced file systems like EXT4.
  - **RootFS Partition:** Formatted with EXT4, the filesystem for the actual operating system.The choice of using EXT4 for the root file system (rootfs) because EXT4 file system allows for resizing.

  For detailed commands, refer to Anas repository  [commands provided in the repository](https://github.com/anaskhamees/Embedded_Linux/tree/main/EmbeddedLinuxTasks/Virtual_SD_Card).

  - **i will make a quick review about SD card image** commands

    ## `dd if=/dev/zero of=sd.img bs=1M count=1024`

    - **`dd` Command:**
      - `dd` is a command-line utility for copying and converting files.
      
    - **Options:**
      - `if=/dev/zero`: Specifies the input file, `/dev/zero`. It provides an endless stream of null bytes (zeros).
      - `of=sd.img`: Specifies the output file, `sd.img`. This is the file that will be created and filled with zeros.
      - `bs=1M`: Sets the block size to 1 megabyte. It determines the amount of data that `dd` will read and write at a time.
      - `count=1024`: Specifies the number of blocks to copy. With a block size of 1 megabyte and a count of 1024, the total size of the output file will be 1 gigabyte (1024 megabytes).

    ## `cfdisk sd.img`

    - **`cfdisk` Command:**
      - `cfdisk` is a command-line partitioning tool for creating and managing disk partitions.
    - **Command Usage:**
      - `cfdisk sd.img`: Executes `cfdisk` on the specified SD card image, `sd.img`.
    - **Partitioning Steps:**
      - After executing `cfdisk sd.img`, a text-based user interface will open, allowing you to perform partition-related actions.
    - **Choose DOS Partition Table:**
      - Navigate through the options in the `cfdisk` interface.
      - Choose the option to set the partition table type, commonly referred to as "DOS" for a partition table compatible with older systems.
      - Confirm the selection to apply the DOS partition table to the SD card image.

    ```markdown
    1. **Creating a New Partition:**
         **Step 1:** Choose the "New" option to initiate the creation of a new partition.
    
       - **Step 2:** Specify the size for the new partition. In this case, write `200M` to allocate 200 megabytes to the new partition.
    ```

    ```markdown
    **Choosing Filesystem Type and Making It Bootable:**
    
       - **Step 1:** Choose the "Type" option to specify the filesystem type for the partition.
    
       - **Step 2:** From the list of filesystem types, select "fat16" to set the filesystem of the new partition as FAT16.
    
       - **Step 3:** After setting the filesystem type, navigate to the option to toggle the bootable flag for the partition.
    
       - **Step 4:** Choose the "Bootable" option to mark the partition as bootable
    ```

```markdown
# Configuring Second Partition with `cfdisk`

Continuing from the previous steps where you configured the first primary partition with FAT16:

1. **Creating Second Partition:**

   - **Step 1:** Navigate to the option to create a new partition within the `cfdisk` interface.

   - **Step 2:** Choose the "New" option to initiate the creation of a new partition.

   - **Step 3:** Specify the size for the new partition. In this case, write `823M` to allocate the remaining space to the second partition.

   - **Step 4:** Choose the partition type. In this case, the partition will be an extended partition.

   - **Step 5:** Confirm the creation of the new extended partition.

2. **Setting Extended Partition Type and Creating Logical Partition:**

   - **Step 6:** Navigate to the option to set the type of the newly created extended partition.

   - **Step 7:** Choose the "Type" option and select "Linux" to set the type of the extended partition as Linux.

3. **Saving Changes:**

   - **Step 8:** Navigate to the option to write the changes to the partition table.

   - **Step 9:** Choose the "Write" option to save the changes made to the partition table.

   - **Step 10:** Confirm the write operation.

```

The `/dev/loop` devices in Linux are used to set up loopback devices `it allow you to mount regular files as block devices.` This is particularly  `useful for working with disk images`, creating file systems within files, and `testing without the need for physical storage devices`.

To set up a loop device for the SD card image (`sd.img`), the following command is used:

```bash
sudo losetup -f --show --partscan sd.img
```

**`losetup` Command:**

- Manages loop devices in Linux.

**Options:**

- `-f`: Finds the first available loop device. This ensures that the command associates the image with an unused loop device.
- `--show`: Displays the name of the loop device after it's set up. This makes it convenient to identify the associated loop device.
- `--partscan`: Automatically discovers partitions within the specified image file (`sd.img`). This is particularly useful when working with disk images that contain multiple partitions.
- **After Running the Command:**
  - Upon successful execution, you will see the name of the loop device and any discovered partitions within the specified SD card image.

```
# Display Information about Loop Device

To obtain information about a specific block device, such as `/dev/loop25`, you can use the following command:
lsblk /dev/loop25
```

- **`lsblk` Command:**
  - Lists information about block devices.
- **Options:**
  - `/dev/loop25`: Specifies the block device for which information should be displayed.

```
# Create FAT16 Filesystem on Loop Device Partition

To create a FAT16 filesystem on the first partition (`/dev/loop25p1`) of the loop device (`/dev/loop25`), use the following command:
mkfs.vfat -F 16 -n boot /dev/loop25p1
```

- **`mkfs.vfat` Command:**
  - Creates a FAT filesystem on a specified device.
- **Options:**
  - `-F 16`: Specifies the FAT type as FAT16.
  - `-n boot`: Sets the volume label of the filesystem to "boot."
- **Target:**
  - `/dev/loop25p1`: Specifies the first partition of the loop device (`/dev/loop25`) where the FAT16 filesystem will be created.

```
# Create EXT4 Filesystem on Loop Device Partition

To create an EXT4 filesystem labeled "rootfs" on the second partition (`/dev/loop25p2`) of the loop device (`/dev/loop25`), use the following command:
mkfs.ext4 -L rootfs /dev/loop25p2
```

- **`mkfs.ext4` Command:**
  - Creates an EXT4 filesystem on a specified device.
- **Options:**
  - `-L rootfs`: Sets the volume label of the filesystem to "rootfs."
- **Target:**
  - `/dev/loop25p2`: Specifies the second partition of the loop device (`/dev/loop25`) where the EXT4 filesystem will be created.

```
# Mount Partitions to Local Directory

To mount the partitions created on the loop device to a local directory (`/media/mohamed/Local/`), use the following commands:
mount /dev/loop25p1 /media/mohamed/Local/
mount /dev/loop25p2 /media/mohamed/Local/
```

- **`mount` Command:**
  - Mounts a filesystem.
- **Arguments:**
  - `/dev/loop25p1`: Specifies the first partition of the loop device to be mounted.
  - `/dev/loop25p2`: Specifies the second partition of the loop device to be mounted.
  - `/media/mohamed/Local/`: Specifies the local directory where the partitions will be mounted.

```
# Detach Loop Device

To detach the loop device (`/dev/loop25`) from its associated image file, use the following command:
losetup -d /dev/loop25
```

- **`losetup` Command:**
  - Manages loop devices in Linux.
- **Options:**
  - `-d`: Detaches the specified loop device.
- **Target:**
  - `/dev/loop25`: Specifies the loop device to be detached.
- **Command Explanation:**
  - The `losetup -d /dev/loop25` command is used to detach the loop device (`/dev/loop25`) from its associated image file.

This command is essential when you no longer need the loop device and want to release it from its association with the specified image file

----------------------------------------------------------------------------------------------------------------------------------------------------------

**dmesg Command**

- **Display Kernel Messages:**
  - When run without any arguments, `dmesg` prints the kernel messages, showing information about system events, errors, and hardware-related messages.
- **Real-Time Kernel Output:**
  - The `dmesg` command provides real-time output, allowing you to see messages generated by the kernel as they occur.
- **Kernel Boot Messages:**
  - During the boot process, important kernel messages are logged. Using `dmesg` helps review these messages for troubleshooting or information purposes.
- **Filtering Messages:**
  - You can use additional options or pipe the output of `dmesg` to other commands for filtering or formatting purposes.

-----------------------------------------------------------------------------------------------------------------------------------------------------------

# Downloading and Installing U-Boot Step by Step

## Clone the U-Boot Repository

```bash
git clone https://github.com/u-boot/u-boot.git
```

## Navigate to the U-Boot Directory

```bash
cd u-boot
```

```bash
git checkout v2022.07
```

### Configure U-Boot Machine

```
ls configs/ | grep [your machine]
```

- **`ls configs/`**: Lists the contents of the "configs" directory in the U-Boot repository.

- **`grep [your machine]`**: Searches for lines in the output that contain the specified machine identifier.

- Replace `[your machine]` with the actual name or identifier of your target machine.

- in our case we will work with vexpress

  ```bash
  ls configs/ | grep vexpress
  ```

```
# load the default configuration of ARM Vexpress Cortex A9
```

```bash
make vexpress_ca9x4_defconfig
```

`This command essentially loads a default configuration for the specified platform, providing a starting point for building U-Boot for the ARM  Versatile Express Cortex-A9 platform. After running this command, you  can proceed to build U-Boot using the make command.`  

```bash
make menuconfig
```

`When you run this command, you'll see a text-based menu where you can  navigate through different categories and configure various settings.  Use arrow keys to navigate, Enter key to select, and Esc key to exit or  go back.` 

> the default architecture is ARM architecture it is already set (you don't need to change it ).

**we will dive through the config menu** 

**The "autoboot" option**   (inside boot options)

U-Boot typically provides a countdown timer during the boot sequence. If no user input is received within the specified time, U-Boot proceeds  with the autoboot process.

> adjust delay time as you like or make it off

> fady enabled autoboot(asln by default enabled) and adjusted delay for 5 

**Enable a default value for bootcmd** (inside boot options)

 the first script (variable) which run after booting 

> Enabling a default value for `bootcmd` in U-Boot involves setting a predefined sequence of commands that U-Boot will automatically execute during the autoboot process if the user does not interrupt it. The `bootcmd` environment variable holds this sequence.
>
> select bootcmd value  and type echo hello

**(vexpress-v2p-ca9.dtb) Default fdt file**

> The "(vexpress-v2p-ca9.dtb)" in U-Boot  refers to the default device tree file that is used for the Versatile Express Cortex-A9 platform. The Device Tree Blob (DTB) file is a binary file that `describes the hardware configuration and device information of the target platform.`
>
>  a device tree is a data structure that contains information about hardware , these information will be used later  by kernel 

**Support for U-Boot commands**(in Command line interface)

 is referring to whether or not U-Boot should include a set of built-in commands that are available by default when U-Boot starts.

**shell prompt**(in Command line interface)

the "shell prompt" refers to the command-line interface provided by  U-Boot, where you can interact with the bootloader and issue commands.

> prees enter and write ITI INTAKE 44

**boot commands**(in Command line interface)

> select  bootd 
>
> insure that command run is marked 

**environment**  **commands**(in Command line interface)

> select  editenv 
>
> select  saveenv 

**memory commands** (in Command line interface)

> select md5sum
>
> select meminfo

**device access commands** (in Command line interface)

> select lsblk

**when you are in menu config ...to search for a specific item press forward slash /** 

**Environments** (in main menu )

to make my u-boot support FAT 

> select Environment is in a FAT filesystem
>
> unselect Environment in flash memory 

 **Name of the block device for the environment** (in Environments)

*This is a variablle that specifies the storage device from which U-Boot loads and saves its environment.*

> default config 0 : 1
>

**now we have done all the configuration**  👍

`but when we try to compile... it will not compile` 

`because we didn't set the compiler yet`  

```bash
export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```

then 

```bash
make
```

you might face an error :

include/image.h:1471:12: fatal error: openssl/evp.h: No such file or directory
 1471 | #  include <openssl/evp.h>

**to  solve this** 

```bash
sudo apt-get install libssl-dev
```

then 

```bash
make
```

```
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot/u-boot -sd sd.img
```

- `qemu-system-arm`: QEMU command to emulate an ARM system.
- `-M vexpress-a9`: Specifies the machine type as Versatile Express A9.
- `-m 128M`: Allocates 128MB of memory to the virtual machine.
- `-nographic`: Disables graphical output, suitable for a terminal.
- `-nographic`: Disables graphical output, suitable for a terminal.
- `-kernel u-boot/u-boot`: Specifies the path to the U-Boot bootloader binary.
- `-sd sd.img`: Attaches the SD card image (`sd.img`) to the emulated system.

----------------------------------------------------------------------------------------------------------------------------------------------------------------

# Boot Configuration and TFTP Setup

**when you need to make changes to the partitions , we  can remount it with read-write permissions.**

```bash
sudo mount -o remount,rw /dev/loop25p1
```

`mount`: Command to mount file systems.

`-o`: Options flag.

`remount,rw`: Specify the remount option and set it to read-write.

## **so what is the difference between losetup and mount commands ?** 

`losetup` is a command used to associate loop devices with  regular files or block devices. Loop devices allow you to treat a  regular file as if it were a block device. 

`mount` is a command used to attach a filesystem to the system's directory tree.

----------------------------------------------------------------------------------------------------------------------------------------------------------

```bash
make -j
```

The `-j` option in the `make` command is used to specify the number of jobs (parallel tasks) that `make` is allowed to run simultaneously. This can significantly speed up the build process by utilizing multiple processors or cores.

## Using bootcmd to run commands after booting 

```bash
setenv Kernel_address 0x6000000
setenv fdt_address 0x7000000
```

These commands set an environment variable named `Kernel_address` with the value `0x6000000`. The variable is intended to store the memory address where the kernel image will be loaded.

and set the `fdt_address` environment variable to `0x7000000`. This variable typically represents the memory address where the device  tree binary (DTB) will be loaded during the U-Boot boot process.

```bash
setenv bootcmd "echo 3omda ; fatload mmc 0:1 ${Kernel_address} main.c; fatload mmc 0:1 ${fdt_address} beagle.dtb ; bootz ${Kernel_address} - ${fdt_address}"
```

This command sets the `bootcmd` environment variable. The `bootcmd` variable typically contains **the command(s) that U-Boot will execute when the system boots**. In this case, the `bootcmd` is a string that includes two commands:

- `echo 3omda: This is an `echo` command that will print the string "3omda" during the boot process. It's a simple informational message.
- `fatload mmc 0:1 ${Kernel_address} main.c`: This is a U-Boot command to load a file named `main.c` from the FAT filesystem on the first partition of the SD card. The `${Kernel_address}` is a variable substitution, and it will be replaced with the value stored in the `Kernel_address` variable.
- `fatload mmc 0:1 ${fdt_address} beagle.dtb`: Loads the device tree binary (`beagle.dtb`) from the FAT filesystem on the first partition of the  SD card into memory at the address specified by `${fdt_address}`.
- `bootz ${Kernel_address} - ${fdt_address}`: Initiates the kernel boot process using the `bootz` command. It specifies the kernel image address (`${Kernel_address}`) and the device tree address (`${fdt_address}`). The hyphen (`-`) is used to separate the addresses.

#### **important note ** 

**Use of (DTB)**-----> Device Tree Binary 

- **with U-Boot:**

  - During the U-Boot boot process, the U-Boot bootloader may load the DTB file from a storage medium (such as an SD card) into a specific memory address, as specified by the `fdt_address` environment variable.
  - U-Boot then passes the location of the DTB to the Linux kernel when initiating the kernel boot process.

- **with Linux Kernel:**

  - The Linux kernel, when booted, uses the DTB provided by U-Boot to configure and initialize the hardware components.
  - The device tree allows the Linux kernel **to be more adaptable to different hardware configurations without requiring recompilation of the kernel for each specific platform.**

  ------

#### **optimizing commands** 

```bash
setenv bootcmd "echo 3omda ; if fatload mmc 0:1 ${Kernel_address} main.c && fatload mmc 0:1 ${fdt_address} beagle.dtb; then bootz ${Kernel_address} - ${fdt_address}; else echo 'Failed to load kernel or DTB'; fi"
```

now we use  the `if` statement to check the success of loading `main.c` and `beagle.dtb` using `fatload`.

If both `fatload` commands are successful, it executes `bootz ${Kernel_address} - ${fdt_address}`.

If any of the `fatload` commands fails, it prints "Failed to load kernel or DTB".

#### Now we want to make it more abstracted 

```bash
setenv flash_kernel_size 0x400000   # Example size for kernel 
setenv fdt_address 0x83000000       # Example RAM address for loading DTB 
setenv flash_fdt_offset 0x800000    # Example offset in flash memory for DTB
setenv flash_fdt_size 0x20000       # Example size for DTB 
```

**`flash_kernel_size`:**

- Example: `0x400000` (4 megabytes)
- we should replace this with the actual size of our kernel image in bytes.

**`fdt_address`:**

- Example: `0x83000000`
- This is the RAM address where you want to load the DTB. 

**`flash_fdt_offset`:**

- Example: `0x800000` (8 megabytes)
- This is the offset in the flash memory where the DTB is stored. 

**`flash_fdt_size`**

- Example: `0x20000` (128 kilobytes)
- we should Replace this with the actual size of our  DTB file in bytes. 

```bash
setenv kernel_load_cmd "fatload mmc 0:1 ${Kernel_address} Zimage"
setenv fdt_load_cmd "fatload mmc 0:1 ${fdt_address} beagle.dtb"
setenv kernel_load_flash_cmd "nand read ${Kernel_address} flash_kernel_offset flash_kernel_size"
setenv fdt_load_flash_cmd "nand read ${fdt_address} flash_fdt_offset flash_fdt_size"
setenv kernel_load_tftp_cmd "tftp ${Kernel_address} Zimage"
setenv fdt_load_tftp_cmd "tftp ${fdt_address} beagle.dtb"
```

1. **`setenv kernel_load_cmd "fatload mmc 0:1 ${Kernel_address} Zimage"`:**
   - This command sets an environment variable named `kernel_load_cmd`.
   - The value of this variable is a U-Boot command that loads a file named `Zimage` from the FAT filesystem on the first partition of the SD card into memory at the address specified by `${Kernel_address}`.
2. **`setenv fdt_load_cmd "fatload mmc 0:1 ${fdt_address} beagle.dtb"`:**
   - This command sets an environment variable named `fdt_load_cmd`.
   - The value of this variable is a U-Boot command that loads a file named `beagle.dtb` from the FAT filesystem on the first partition of the MMC/SD card into memory at the address specified by `${fdt_address}`.
3. **`setenv kernel_load_flash_cmd "nand read ${Kernel_address} flash_kernel_offset flash_kernel_size"`:**
   - This command sets an environment variable named `kernel_load_flash_cmd`.
   - The value of this variable is a U-Boot command that reads data from NAND flash memory. It specifically reads data from the offset specified by `flash_kernel_offset` and with a size specified by `flash_kernel_size`. The data is read into memory at the address specified by `${Kernel_address}`.
4. **`setenv fdt_load_flash_cmd "nand read ${fdt_address} flash_fdt_offset flash_fdt_size"`:**
   - This command sets an environment variable named `fdt_load_flash_cmd`.
   - The value of this variable is a U-Boot command that reads data from NAND flash memory. It specifically reads data from the offset specified by `flash_fdt_offset` and with a size specified by `flash_fdt_size`. The data is read into memory at the address specified by `${fdt_address}`.
5. **`setenv kernel_load_tftp_cmd "tftp ${Kernel_address} Zimage"`:**
   - This command sets an environment variable named `kernel_load_tftp_cmd`.
   - The value of this variable is a U-Boot command that initiates a TFTP (Trivial File Transfer Protocol) transfer. It downloads a file named `Zimage` from a TFTP server and loads it into memory at the address specified by `${Kernel_address}`.
6. **`setenv fdt_load_tftp_cmd "tftp ${fdt_address} beagle.dtb"`:**
   - This command sets an environment variable named `fdt_load_tftp_cmd`.
   - The value of this variable is a U-Boot command that initiates a TFTP transfer. It downloads a file named `beagle.dtb` from a TFTP server and loads it into memory at the address specified by `${fdt_address}`.

```bash
setenv bootcmd "echo 3omda ; if ${kernel_load_cmd} && ${fdt_load_cmd}; then
  bootz ${Kernel_address} - ${fdt_address};
else
  echo 'Failed to load kernel or DTB';
  if ${kernel_load_flash_cmd} && ${fdt_load_flash_cmd}; then
    bootz ${Kernel_address} - ${fdt_address};
  else
    echo 'Failed to load from flash';
    ${kernel_load_tftp_cmd} && ${fdt_load_tftp_cmd} && bootz ${Kernel_address} - ${fdt_address};
  fi;
fi"
```

1. **`echo 3omda`**: Prints the string "3omda" during the boot process. This is an informational message.
2. **`if ${kernel_load_cmd} && ${fdt_load_cmd}; then ... else ... fi`**: Checks if the kernel and device tree binaries can be loaded from the SD card using the commands specified in `kernel_load_cmd` and `fdt_load_cmd`.
   - If successful, it executes `bootz ${Kernel_address} - ${fdt_address}` to boot the system.
   - If unsuccessful, it moves to the `else` part.
3. **`echo 'Failed to load kernel or DTB'`**: Prints a failure message if the  SD card loading fails.
4. **`if ${kernel_load_flash_cmd} && ${fdt_load_flash_cmd}; then ... else ... fi`**: Checks if the kernel and device tree binaries can be loaded from NAND flash using the commands specified in `kernel_load_flash_cmd` and `fdt_load_flash_cmd`.
   - If successful, it executes `bootz ${Kernel_address} - ${fdt_address}` to boot the system.
   - If unsuccessful, it moves to the `else` part.
5. **`echo 'Failed to load from flash'`**: Prints a failure message if the NAND flash loading fails.
6. **`${kernel_load_tftp_cmd} && ${fdt_load_tftp_cmd} && bootz ${Kernel_address} - ${fdt_address}`**: Attempts to load the kernel and device tree binaries from a TFTP server using the commands specified in `kernel_load_tftp_cmd` and `fdt_load_tftp_cmd`. If successful, it executes `bootz ${Kernel_address} - ${fdt_address}` to boot the system.

------------------------------------------------------------------------------------

## TFTP Protocol

--------------------------------------------------------

TFTP stands for Trivial File Transfer Protocol. It is a simple,  lightweight file transfer protocol that operates over the User Datagram  Protocol (UDP). TFTP is commonly used for transferring files between  devices on a network.

#### **Uses**

One of the primary use cases for TFTP is network booting. During the boot process, an embedded device may use  TFTP to download its bootloader, kernel, or configuration files from a  TFTP server on the network. This is especially common in scenarios where the embedded device may not have local storage or **needs to retrieve the operating system over the network.**

## **configure my pc to be a server** 

**note that you should  configure TFTP in u-boot configuration ------> in menuconfig** 

**and compile again** 

`you can configure your pc as a server (we are able to do that because our pc has a network interface)`

```bash
sudo apt-get update
sudo apt-get install tftpd-hpa
```

```bash
sudo chown tftp:tftp /srv/tftp
```

`to change  the owner and group to tftp`  

`then add yourself to tftp group` 

```bash
sudo usermod -aG tftp mohamed 
```

 `then open u-boot` 

```bash
setenv ipaddr 192.168.2.201
```

this sets the U-Boot environment variable `ipaddr` to the specified IP address.

**(this will be the ip address  of our machine )**

```
setenv serverip 192.168.2.202
```

This sets the U-Boot environment variable `serverip` to the specified IP address. 

**(this will be the ip address  of the server )**

```
tftp $kernel_address zimage
```

- **`tftp`**: Initiates a TFTP transfer.
- **`$kernel_address`**: This variable should be replaced with the actual memory address where you want to load the kernel image.
- **`zimage`**: Specifies the file name of the kernel image to be fetched from the TFTP 

```
tftp $fdt_address dtb
```

- `tftp`: Again initiates a TFTP transfer.
- `$fdt_address`: Represents the memory address where the DTB will be loaded. You should set this environment variable to a specific address before running this command.
- `dtb`: Specifies the filename of the DTB on the TFTP server.

**Boot the System:**

```
bash
bootz $kernel_address - $fdt_address
```

- `bootz`: This U-Boot command is typically used to boot a Linux kernel with an embedded device tree.

- `$kernel_address`: Represents the memory address where the Linux kernel image (`zImage`) was loaded.

- `-`: Separates the kernel image address from the DTB address.

- `$fdt_address`: Represents the memory address where the DTB was loaded.

  

-----------------------------------------------------------------------------------------------

**now our qemu command has a few changes** 

```
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot/u-boot -sd sd.img -net tap,script=./qemu.ifup -net nic
```

- `-net tap,script=./qemu.ifup`: Configures a TAP interface with the specified script (`qemu.ifup`) to set up the networking on the host side.
- `-net nic`: Adds a network interface card (NIC) to the virtual machine.

Make sure to have the `qemu.ifup` script in the current directory or provide the correct path to the script. This script is responsible for setting up the TAP interface on the host side.

```bash
#!/bin/bash

sudo ip addr add 192.168.1.202/24 dev $1
sudo ip link set $1 up

```

`ip addr add 192.168.1.202/24 dev $1`: Assign the IP address `192.168.1.202` with a subnet mask of `/24` to the network interface specified by `$1`. 

- `ip link set $1 up`: Bring up the network interface specified by `$1`. 

Here's an example using `tap' as the network interface:

```
bash
sudo ip addr add 192.168.1.202/24 dev tap
sudo ip link set tap up
```
