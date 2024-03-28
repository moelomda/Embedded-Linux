**Dunfell and Kirkstone** 

Dunfell and Kirkstone are code names for specific Long-Term Support (LTS) releases of the Yocto Project.

- **Long-term Support (LTS):** Selected releases are designated as LTS, receiving critical bug fixes and security patches for a longer period of time (often several years). LTS versions provide stability for products that need a reliable, long-term foundation.

**Dunfell**

- **Release Date:** October 2020
- **LTS Status:** Active LTS, supported until at least April 2024.
- **Features:** Notable features included updated toolchain components, a switch to Python 3 as the default, and improvements to cross-compilation workflows.

**Kirkstone**

- **Release Date:** October 2022
- **LTS Status:** Active LTS, supported for a longer duration (the exact end date is sometimes announced later in the cycle).
- **Features:** Key improvements include security enhancements, a focus on containerization technologies, and better integration with modern development practices.
-------------------------------------------------------------------------------------------------------------------------------------------------

**1. The Kitchen: Your Build Environment**

- **Your Kitchen:** Represents your Build Directory. It's the dedicated workspace where all the cooking (building) happens.
- **Setting Up:** Running `oe-init-build-env` is like cleaning your counter and getting out the essential tools (mixer, measuring cups, etc.).

**2. Recipes & Ingredients: Metadata**

- **Recipe Book:** Think of `meta-poky` and other layers as your recipe book. It has recipes for everything from basic dishes (core Linux components) to fancy desserts (specialized applications).
- **Recipe Files (.bb):** Individual recipes with instructions on how to prepare each dish (fetch ingredients, configure, bake, package).
- **Ingredients:** Source code (eggs, flour, etc.) comes from Git repositories, websites, or even your garden (local projects).

**3. The Chef and Kitchen Tools: BitBake and the Build System**

- **BitBake: The Master Chef** Reads recipes, figures out what tasks to do in what order, and directs the kitchen helpers.
- **Oven:** Represents your cross-compiler. It transforms raw ingredients (source code) into delicious baked goods (compiled software).
- **Pots, Pans, Mixer:** These are like helper tools invoked by BitBake – patch tools, configuration scripts, etc.

**4.  Preparing the Meal: Building Your Image**

- **Shopping List (local.conf):** Your customizations! You choose dishes (packages), dietary restrictions (machine type), and adjust serving sizes (build options).
- **Cooking:** BitBake, like a chef, fetches ingredients, preps them, cooks everything in the right order, and assembles the final meal (your image).
- **Dishes (Packages):** Individual components of your image (webserver, text editor, etc.) neatly packaged in take-out containers.

**5. The Completed Meal: Your Output**

- **The Image:** Your full, bootable, custom-made meal (embedded Linux system), ready to put on your plate (device).
- **Take-out Containers (Packages):** Packages stored in a pantry (package feeds), ready to add to another meal (update your device).
- **Recipe Binder (SDK):** Your notes and tools for making similar meals in the future (developing apps *for* your device).

---------------------------------------------

**the `meta-skeleton` layer**

**Purpose of meta-skeleton**

- **Template for New Layers:** The `meta-skeleton` layer provides a basic structure and boilerplate files to help you quickly create your own custom Yocto Project layers.
- **Best Practices:** It incorporates recommended practices and directory conventions for organizing your recipes and configuration files.
- **Starting Point:** Think of it as a blank canvas that speeds up the initial setup of your layer for adding new components to your embedded Linux build.

Typically, a `meta-skeleton` layer includes:

- Recipe Directory:
  - A placeholder `example.bb` file as a starting point for your own recipes.
- Configuration Directory:
  - A `layer.conf` file where you can define basic information about your layer, like its name, dependencies, and priority.

**What is a BSP Layer?**

- **Hardware-Specific Support:** A BSP is a layer within the Yocto Project that provides the essential information and configurations required to make your embedded Linux system work on a specific hardware target (board).
- **The Bridge:** Think of a BSP as the bridge between the generic components of a Linux system and the unique characteristics of your hardware.

**What's Typically in a BSP Layer**

1. Machine Configuration:

   - Defines the hardware architecture (ARM, x86, etc.), CPU type, available memory, and peripherals present on your board.

2. Kernel Configuration:

   - Linux kernel recipe (often with a pre-configured `.config` file) tailored to your hardware.
   - Device drivers needed for interacting with specific components on your board.

3. Bootloader:

   - Recipes and configuration for the bootloader (e.g., U-Boot, GRUB), along with instructions on how to load it onto your device.

4. **Toolchain (Sometimes):** If required, a BSP might include a cross-compilation toolchain specifically built for your target architecture.

5. Additional Support:

    Potentially other things like:

   - Root filesystem customizations
- Hardware-specific utility scripts or tools
   
   ------------------------------------

6. - **Yocto Metadata**
     
     - **The Big Recipe Book:** Metadata in the Yocto Project serves as a comprehensive set of instructions, configuration files, and data guiding the build process. It resembles a vast recipe book dictating what to build, how to build it, and where to locate the necessary ingredients.
     
     - **Types of Metadata**
     
       1. **Recipes (.bb files):**
           - **Core Instructions:**
             Recipes form the core of Metadata, encompassing:
             - Fetching source code (e.g., Git, tarballs)
             - Configuration for target hardware
             - Compilation steps and flags
             - Packaging directives (e.g., creating .deb, .rpm packages)
     
           - **Found in Layers:** Recipes are organized into layers.
     
     2. **Configuration Files (.conf)**
        - **Global Settings:**
          Files like `local.conf` and `bblayers.conf` govern:
          - Target hardware configuration (machine settings)
          - Inclusion of software packages in the image
          - System-wide build configurations and flags
     
     3. **Patches (.patch or .diff)**
        - **Code Fixes and Modifications:**
          Patches alter the original source code of software components for purposes such as:
          - Bug fixes
          - Feature additions
          - Hardware-specific adaptations
     
     4. **Appends (.bbappend)**
        - **Tweaking Existing Recipes:**
          Append files enable modifications to existing recipes *without* altering the originals. Users can introduce tasks, alter variables, etc., within their own layer.
     
     5. **Classes (.bbclass)**
        - **Reusable Logic:**
          Classes offer reusable blocks of build logic, akin to 'mini-recipes' that can be incorporated into other recipes to automate common tasks or establish standard build patterns.
     
     6. **Images:**
        - **Special Recipe Type:**
          While not strictly referred to as 'Metadata', image recipes within the Yocto Project delineate the precise content (package list) composing the Linux image.

------------------------------------------------------------------------------------

**Variables assignation on Yocto**

Assignment Operators

| Operator | Explanation                                                  | Example                       | Notes                                               |
| -------- | ------------------------------------------------------------ | ----------------------------- | --------------------------------------------------- |
| =        | Basic assignment: Sets a value to a variable immediately.    | MY_VAR = "hello world"        | Spaces in values are preserved.                     |
| ?=       | Sets a value if the variable is undefined.                   | EXTRA_OPTION ?= " -DDEBUG"    | Lower priority than other assignments.              |
| ??=      | Sets a weak default, can be overridden later.                | IMAGE_TYPE ??= "basic"        | Useful for setting 'fallbacks'.                     |
| :=       | Immediate expansion; variable values expanded at assignment. | VAR := "${ANOTHER_VAR} stuff" | Can lead to unexpected results if variables change. |
| +=       | Appends with a space.                                        | FILES += "newfile.txt"        |                                                     |
| =+       | Prepends with a space.                                       | OPTIONS =+ " -v"              |                                                     |
| .=       | Appends without a space.                                     | FILES .= "more.c"             |                                                     |
| =.       | Prepends without a space.                                    | OPTIONS =. "-O3 "             |                                                     |
| :append  | Override-style append; adds at time of use.                  | PACKAGES:append = " mypkg"    | No automatic spaces. Can be complex.                |
| :prepend | Override-style prepend; adds at time of use.                 | OPTIONS:prepend = "debug_"    | No automatic spaces. Can be complex.                |
| :remove  | Override-style remove; deletes at time of use.               | PACKAGES:remove = " unwanted" | Order of overrides matters.                         |

| Operator Type        | Operators                  | When is the Primary Effect?                             |
| -------------------- | -------------------------- | ------------------------------------------------------- |
| Immediate Assignment | :=                         | At the time of the assignment itself                    |
| Deferred Assignment  | =, ?=, ??=                 | When the variable is used in a task or another variable |
| Appending/Prepending | +=, =+, .=, =.             | At the time of the assignment itself                    |
| Overrides            | :append, :prepend, :remove | When the variable is used in a task or another variable |

Immediate Operators: These operators have an immediate effect when the line of code is parsed. Their result is 'locked in' even if other variables they depend on change later.

Deferred Operators: These operators are more dynamic. Their effect is determined when the variable itself is actually used later on.

Overrides: These offer the most flexibility but also complexity. They modify a variable only when it's used, allowing for very fine-tuned control.

**Precedence (Highest to Lowest):**

1. := (Override)
2. = (Simple Assignment)
3. ?= (Conditional)
4. ??= (Weak Conditional)
5. +=, =+, .=, :append, :remove (Modifying)

Overriding: Operators higher on the list take priority if a variable is assigned multiple times.

- Layers: Settings in later layers generally override those in earlier layers within your BBLAYERS configuration.
- Expansion: Know the difference between immediate ${} and delayed ${} expansion.

Example 

```bash
# Immediate Assignment (:=)
VAR1 := "initial"            # VAR1 = "initial"
VAR2 := "${VAR1} value"      # VAR2 = "initial value" 

# Deferred Conditional Assignment (?=)
VAR1 ?= "default"            # VAR1 remains "initial" (already set)
VAR2 ?= "overridden"         # VAR2 remains "initial value" (already set) 

# Immediate Appending (+=)
FILES += "file1.txt"         # FILES = "file1.txt"
FILES += "file2.txt"         # FILES = "file1.txt file2.txt"

# Overrides (:append)
SOURCES := "${SOURCES} newfile.c"  # Undefined SOURCES: has no effect

# Mixing Immediate and Deferred Operators
VAR3 = "another"             # VAR3 = "another" 
VAR4 := "${VAR3} value"      # VAR4 = "another value"  

# Deferred Weak Conditional Assignment (??=)
VAR5 ??= "weak"              # VAR5 = "weak"  
VAR6 ??= "strong"            # VAR6 remains "weak" (already set)

# Immediate Prepending (=+)
OPTIONS =+ "-v"              # OPTIONS = "-v"
OPTIONS =+ "-debug"          # OPTIONS = "-debug -v" (prepended)

# Overrides (:remove)
PACKAGES := "${PACKAGES} unwanted"   # Undefined PACKAGES: has no effect
PACKAGES:remove = "unwanted"        # No effect
-------------------------------------------------------------------------------------------------
# Immediate Assignment (:=) with Deferred Assignment (=):
VAR1 := "initial"            # VAR1 = "initial"
VAR2 = "${VAR1} value"       # VAR2 = "initial value" 

# Deferred Conditional Assignment (?=) with Immediate Assignment (:=):
VAR3 ?= "default"            # VAR3 = "default"  (remains unchanged as already set)
VAR4 := "${VAR3} value"      # VAR4 = "default value" 

# Deferred Assignment (=) with Overrides (:append):
VAR5 = "initial"             # VAR5 = "initial"
VAR6 := "${VAR5} value"      # VAR6 = "initial value"
VAR6 :append = " extra"      # VAR6 = "initial value extra"

# Immediate Appending (+=) with Deferred Conditional Assignment (?=):
FILES += "file1.txt"         # FILES = "file1.txt"
FILES ?= "default.txt"       # FILES = "file1.txt" (remains unchanged)

# Deferred Weak Conditional Assignment (??=) with Immediate Prepending (=+):
VAR7 ??= "weak_default"      # VAR7 = "weak_default"
OPTIONS =+ "-v"              # OPTIONS = "-v"

# Immediate Assignment (:=) with Overrides (:remove):
VAR8 := "initial"            # VAR8 = "initial"
PACKAGES := "${VAR8} package" # PACKAGES = "initial package"  
PACKAGES:remove = " package" # PACKAGES = "initial"

# Deferred Conditional Assignment (?=) with Overrides (:prepend):
VAR9 ?= "default"            # VAR9 = "default"
OPTIONS:prepend := "${VAR9}_" # OPTIONS = "default_-v" 

# Final Result: PACKAGES = "" (PACKAGES is emptied by the removal of "package")
Deferred Conditional Assignment (?=) with Overrides (:prepend):
VAR9 ?= "default"
OPTIONS:prepend := "${VAR9}_"
# Final Result: OPTIONS = "default_" (OPTIONS takes "default_" immediately, not affected by c
```

------------------------------------------------------------------

**Types of Variables in Yocto**

- **Configuration Variables:**(global)
  - Defined in configuration files (`.conf` files such as `local.conf`, `machine.conf`, `distro.conf`).
  - Broadly accessible across recipes and classes, providing a way to set project-wide or machine-specific values.
- **Recipe-Specific Variables:**(local)
  - Defined within a recipe file (`.bb`).
  - Scope is limited to that recipe and any recipes that directly include it or inherit it via `inherit`.
- **BitBake Class Variables (`BBCLASS`):**
  - Defined within a BitBake class file (`.bbclass`).
  - Scope is limited to recipes that inherit the class. They provide a way to set defaults and common behaviors across multiple recipes.

**Achieving "Global" Behavior**

- **Configuration Files:** Placing variables in your `local.conf`, machine-specific configuration, or distribution-level configuration files is the closest equivalent to "global" variables. They will be accessible to most recipes and classes within your Yocto build.

**Achieving "Local" Behavior**

- **Recipe Scope:** Variables defined within a recipe itself are essentially "local" to that recipe and any that directly use it. This is good for values specific to that build process.
- **BBCLASS Scope:** Similar to recipe scope, variables within a `.bbclass` are limited to recipes using that class, allowing for more modular configuration.

## `bitbake-getvar` Command-Line Tool

### Purpose

- **Retrieve Variable Values:** The primary function of `bitbake-getvar` is to retrieve the value of a specified variable, both in its unexpanded and expanded form.
- **Debug Recipes and Configuration:** This tool helps you examine how variables are being set and modified within recipe files (.bb) and configuration files (.conf).

### Syntax

```bash
bitbake-getvar <variable_name> [recipe_file]
```

```
# Get the value of IMAGE_INSTALL for the core-image-minimal image
bitbake-getvar IMAGE_INSTALL core-image-minimal

# Get the value of SRC_URI within the example.bb recipe 
bitbake-getvar SRC_URI example.bb
```

### Output

`bitbake-getvar` displays the following:

- **Variable Name:** The name of the variable you requested.
- **Unexpanded Value:** The raw value of the variable, before any expansions take place.
- **Expanded Value:** The value of the variable after all references to other variables have been resolved.
- **Origin:** Information on where the variable's value was defined or modified.

## Inspecting BitBake Recipe Variables

### bitbake -e <recipe> | grep <variable>

- **bitbake -e <recipe>:** This part of the command tells BitBake to process the specified recipe and print all environment variables and their settings as they exist after all configuration files and the recipe itself are parsed.
- **|:** The pipe symbol takes the output produced by `bitbake -e` and feeds it as input to the next command.
- **grep <variable>:** The `grep` command searches and filters the input, displaying only lines that contain the `<variable>` you want to find.

-----------------------------------------

## What is IMAGE_INSTALL?

**Purpose:** This variable acts as a list specifying which packages should be installed into the root filesystem of your target image.

**Scope:** It has a global scope, meaning it influences the content of images built using the Yocto Project system.

## How to Use IMAGE_INSTALL

**Direct Assignment (=)**

- **Example:** `IMAGE_INSTALL = "nano dropbear openssh"`
- **Effect:** Includes the 'nano' text editor, 'dropbear' lightweight SSH server, and 'openssh' secure shell package in your image.

**Appending (+=)**

- **Example:** `IMAGE_INSTALL += "python3"`
- **Effect:** Adds the 'python3' package to the existing packages listed in IMAGE_INSTALL.

## Important Notes

- **Image Features:** The `IMAGE_FEATURES` variable in your configuration can automatically add sets of packages to `IMAGE_INSTALL`. For example, including "ssh-server" in `IMAGE_FEATURES` might add the necessary OpenSSH server package to `IMAGE_INSTALL`.
- **Recipes:** Individual recipes (.bb files) can further modify `IMAGE_INSTALL` to tailor the image for their software component.

## Relationship to Other Variables

- **CORE_IMAGE_EXTRA_INSTALL:** This variable is specifically for adding packages to images based on the "core-image" class. Using `CORE_IMAGE_EXTRA_INSTALL` is a convenient way to add packages if your image inherits from core-image classes.
- **IMAGE_LINGUAS:** Influences the language-related packages included in your image.

## Tips

- Use `bitbake -e <image_name>` to inspect the final value of `IMAGE_INSTALL` and other variables after your configuration and recipes have been processed. This helps in debugging and understanding what will be included in your image.

----------------------------------------------------------------------------------------------------------------------------------------------------------------

## the step-by-step process of creating a new Yocto layer, adding a recipe to it, and including the package produced by that recipe into your final image:

1. **Create a New Layer**

   - Use `bitbake-layers` script:
     ```bash
     bitbake-layers create-layer <path/to/your/newlayer>
     ```
     *Replace `<path/to/your/newlayer>` with the actual desired location.*

   - Manual Creation (if needed):
     - Create a directory for your layer (e.g., meta-mylayer).
     - Inside, create a `conf` subdirectory with a `layer.conf` file.

2. **Add Layer to Your Build**

   ```bash
   bitbake-layers add-layer <path/to/your/newlayer>
   ```

   1. - Replace `<path/to/your/newlayer>` with the actual path to your layer.

   **What This Does**

   - **Modifies bblayers.conf:** The `bitbake-layers add-layer` command automatically adds the specified layer's path to your `bblayers.conf` file.
   - **Benefits:** It saves you the manual step of editing the `bblayers.conf` file, making the process faster and less prone to errors.

3. **Create a Recipe in Your Layer**

   - **Recipe File:**
     
     - Inside your layer's `recipes-example` directory (or a new directory with a descriptive name), create a `.bb` file for your recipe (e.g., `myrecipe.bb`).
     
   - **Basic Recipe Structure:**
     
     ```bash
     SUMMARY = "Short description of your software"
     LICENSE = "LicenseType" 
     LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LicenseType;md5=..."
     
     SRC_URI = "...." 
     
     # Other variables like DEPENDS, inherit, etc. as needed.
     ```
     *Fill in the appropriate values for your software.*

4. **Include the Package in Your Image**

   - **Modify `IMAGE_INSTALL`:**
     - In your image recipe or in your configuration (`local.conf` or similar), append the name of the package produced by your recipe into the `IMAGE_INSTALL` variable. Assuming your recipe produces a package called 'myrecipe':
       ```bash
       IMAGE_INSTALL += "myrecipe"
       ```

5. **Build the Image**

   - Issue the BitBake command:
     ```bash
     bitbake <your_image_name>
     ```

-------------------------------------------------

**Essential Core Variables in recipes**

- **PN:** The package name. This is how your package will generally be referred to.

- **PV:** The package version. Crucial for tracking changes and dependency resolution.

- **PR:** The package revision. This often functions as an extension to the version, used for minor build updates or custom modifications within the same base version.

- **SUMMARY:** A short, one-line description of the software package.

- **LICENSE:** Specifies the license type of the software (e.g., "MIT", "GPLv3").

- **LIC_FILES_CHKSUM:** A checksum to help ensure the license file itself hasn't been modified.

- **SRC_URI:**

   Defines where the source code for the package can be obtained. This includes:

  - URLS for downloading tarballs or other archives
  - Git repositories and their specific commits/branches.
  - References to local files.
  
- **DEPENDS:** Lists the runtime dependencies of the package—other packages that must be present in the image for your software to function.

- **RDEPENDS:** Lists runtime dependencies that should be included in the final image. This is a subset of 'DEPENDS' for finer control

- The `${workdir}` acts as a temporary workspace where source code is unpacked, patches are applied, compilation happens, and other recipe-specific files are generated.

  **Recipe Isolation:** Each recipe has its own unique `${workdir}`, preventing conflicts and keeping build processes for different recipes separate.
