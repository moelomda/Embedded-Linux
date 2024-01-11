- # Vexpress Emulation with QEMU and U-Boot

  ## Create Blank SD Card Image

  A "blank" SD card image is like an empty disk. It's a file that will represent the storage for your emulated system. In this guide, we'll create an SD card image instead of buying one 😆.

  ### Partition the SD Card Image

  Partitions are logical sections of the storage. You create partitions on the SD card image to organize the space. For example, we'll create two partitions:

  1. **Boot Partition:** This is where the bootloader resides.

  2. **RootFS Partition:** This is for the root filesystem

     

  ### Format Partitions

  Each partition needs a filesystem, a way to organize and store files. We'll format the partitions as follows:

  - **Boot Partition:** Formatted with FAT16, a common filesystem for bootloaders.
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
>  فيه معلومات عن الهاردوير 
>
>  هتحتاجها برضو بعدين kernelالمعلومات دي ال 

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
- `-kernel u-boot/u-boot`: Specifies the path to the U-Boot bootloader binary.
- `-sd sd.img`: Attaches the SD card image (`sd.img`) to the emulated system.
