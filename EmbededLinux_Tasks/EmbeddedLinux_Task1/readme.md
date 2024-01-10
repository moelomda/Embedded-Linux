### 1. Using `ldd` Command:

![image-20231222011612727](/home/mohamed/.config/Typora/typora-user-images/image-20231222011612727.png)

 ldd is a command-line utility that prints shared library dependencies of executables.

Running `ldd` on the dynamically linked executable (`calculator_dynamic`) will show the shared libraries it depends on.

Running `ldd` on the statically linked executable (`calculator_static`) may show different output or indicate that it's not a dynamic executable.

### 2. Using `file` Command:

![image-20231222013025787](/home/mohamed/.config/Typora/typora-user-images/image-20231222013025787.png)

- `file` is a command-line utility that provides information about file types.

- Running `file` on both executables will display information such as whether they are dynamically linked or statically linked.

  ### 3-Using `objdump` Command:

  - `objdump` is a command-line utility that displays information about object files.

  - Running `objdump` with the `-x` option on both executables will show additional information, including the architecture, sections, and more.

  - You can use `objdump` to disassemble an object file, providing a human-readable representation of the assembly code.

    objdump -d your_object_file

    

    objdump` can display information about different sections in an object file. This includes sections like `.text`, `.data`, `.bss`, and more.

    objdump -h your_object_file

    To view the full symbol table (including global and local symbols), you can use

    objdump -t your_object_file

    

    

  