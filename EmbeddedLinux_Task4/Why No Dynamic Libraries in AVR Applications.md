- ## Why No Dynamic Libraries in AVR Applications?

  Using dynamic libraries in AVR applications is not a common practice, and here are the key reasons:

  ### Runtime Overhead

  Dynamic libraries come with runtime overhead, including the need for a dynamic linker/loader. This overhead can affect real-time performance, which is critical in many AVR applications.

  ### Limited Operating System Support

  AVR microcontrollers are often used in bare-metal or minimal operating system environments. Support for dynamic linking and loading is limited in such systems.

  ###  Static Linking for Predictability

  In embedded systems, predictability and determinism are crucial. Static linking at compile-time provides better control over memory layout and behavior, essential for real-time and safety-critical applications.

  ### Flash Memory Constraints

  Flash memory in AVR microcontrollers is limited. Including a dynamic loader and multiple dynamic libraries may significantly increase the size of the final binary.

  ### No Standard ABI

  AVR microcontrollers lack a standardized ABI for dynamic libraries. Different toolchains may have their own formats, leading to compatibility issues.