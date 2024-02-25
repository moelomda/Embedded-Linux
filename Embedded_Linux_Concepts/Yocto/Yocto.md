**Yocto Project:** This is an open-source **collaborative project** focused on creating tools and processes that enable the development of custom Linux distributions for embedded devices.

**Customization:** The Yocto Project's primary strength lies in its extreme customizability.

![what-is-yocto-poky](F:\study\ITI_9months\matrial\embeded linux\embeded_linux\assets\what-is-yocto-poky.jpg)

-----

**What is Poky?**

- **Reference Distribution:** Poky is a collection of Metadata (recipes, configuration files, etc.) that serves as the starting point for building a custom embedded Linux distribution using the Yocto Project.

**Poky: The Toolkit for Customization**

- **Part of the Yocto Project:** Poky is a key component within the larger Yocto Project ecosystem.
- **Reference Distribution:** It's a starting point, providing example recipes, configurations, and a basic structure for your embedded Linux distribution.
- Includes Essential Tools:

 Here's what you'll find within Poky:

**BitBake:** The build engine that interprets recipes and executes tasks.

**OpenEmbedded-Core (OE-Core):** A set of foundational recipes and Metadata common to many embedded systems.

**meta-poky:** A layer within Poky containing more Poky-specific configuration and recipes.

**meta-skeleton:** A template layer to help you create your own custom layers.

**Scripts:** Various helpful scripts for setting up the build environment and other tasks.

**Support for some development boards:** May include BSP (Board Support Package) layers for boards like Raspberry Pi.

## if you want to create your own software , and add it to the image you have to create a layer first then add this layer to poky.

**Steps to Add Your Software**

1. **Create a New Layer:**  Use scripts provided by Poky (`bitbake-layers create-layer`) to set up a basic layer structure. This will give you a directory with some essential files.
2. **Write a Recipe:** Create a `.bb` recipe file within your layer. This recipe will tell BitBake:
   - Where to download your software's source code (website, Git repository, etc.)
   - Any patches to apply to the source code.
   - How to configure the build (compilation flags, options).
   - How to install the compiled software into your final image.
3. **Include Your Layer:**
   - **Edit `bblayers.conf`:** Add the path to your new layer within the `BBLAYERS` variable in your Build Directory's `conf/bblayers.conf` file.
4. **Include Your Recipe in the Image:**
   - **Edit an Image Recipe:** Modify an existing image recipe (`core-image-minimal.bb` for example) or create a new one.
   - **Add Dependency:** Use `IMAGE_INSTALL += "your-software-package"` to have your software included in the final image.

**Example:**

Let's say you've developed a custom application called "my-app":

1. You create a layer named "meta-my-app".
2. Inside that layer, you write a recipe "my-app_1.0.bb".
3. You add "meta-my-app" to your `bblayers.conf`.
4. You include `IMAGE_INSTALL += "my-app"` in your image recipe.

Now, when you build your image using BitBake, your custom software 'my-app' will be automatically fetched, compiled, and packaged into your embedded Linux system!

......**This will be discussed later in details** 

---

**BitBake is the task execution engine at the heart of the Yocto Project's build system.** 

**What BitBake Does**

- **Recipe Interpreter:** BitBake reads and understands the instructions written in recipes (`.bb` files). These recipes define all the steps needed to build software components for your embedded Linux system.
- **Task Scheduler:** BitBake breaks down each recipe into a series of tasks (e.g., `do_fetch`, `do_compile`, `do_install`). It analyzes dependencies between tasks and schedules them intelligently for efficient execution and parallelization where possible.
- **Executor:** BitBake actually runs the tasks, which could involve downloading code, applying patches, running compilation commands, packaging software, and more.

**How BitBake Works (a simplified view)**

1. You initiate a build with a command like `bitbake my-image`.
2. BitBake parses configuration files and Metadata (recipes, classes) to create a giant network of tasks and their interdependencies.
3. It starts executing tasks, respecting the dependency graph and maximizing parallelization.
4. The output is your custom Linux image

**BitBake has several key tasks that roughly correspond to the actions ( fetch, patch, config,compile)**

**1. Fetch**

- **Task:** `do_fetch`

- Action: 

  BitBake downloads the necessary source code for a component based on the instructions in the recipe. This could involve:

  - Downloading from Git repositories
  - Downloading source tarballs from websites
  - Using source code from a local directory

**2. Patch**

- **Task:** `do_patch`

- Action

  BitBake applies patches to the source code, if specified in the recipe. Patches are often used to:

  - Fix bugs in the upstream code
  - Add new features
  - Adapt the code to your specific hardware or requirements

  **Types of Patches**

  - **Bug Fixes:** Suppose the upstream (original) version of software has a known bug. Your patch might fix the flawed code to get the software working correctly.

    *Example:* A simple one-line change in a C file to correct an incorrect calculation or a conditional statement.

  - **Feature Enhancements:** You want to add functionality not present in the original software version.

    *Example:* A patch could add a whole new source file implementing a custom feature, along with modifications to other files to integrate it.

  - **Hardware Adaptations:** Patches can be used to make the software compatible with your specific hardware or board.

    - Example:* Modifying a device driver's configuration or initialization code to match your device's specifications.

  - **Security Fixes:** This is critical! Your patch might address a security vulnerability  found in the upstream code.

    - Example:* A patch to close a buffer overflow vulnerability that could potentially be exploited by attackers.

  - **Build System Adjustments:**  Sometimes, you need to modify the upstream project's build scripts or makefiles to make them work smoothly within the Yocto Project build system.

    - Example:* Adding flags to a Makefile to match your cross-compilation environment.

  **How Patches are Applied**

  1. **Within Recipes:** Recipes (`.bb` files) have sections for specifying source code locations and applicable patches.
  2. **Patch Files:** Patches themselves are usually `.patch` or `.diff` files.
  3. **`do_patch` Task:** BitBake's `do_patch` task takes care of applying the patches to the source code.

  **Example Structure (Simplified)**

  Recipe snippet:

  ```
  SRC_URI = "git://some_project.git;branch=main" 
  
  SRC_URI[md5sum] = "1234abc"  # Verifies that the downloaded code is what's expected
  SRC_URI[sha256sum] = "xyz.."  
  
  FILES_${PN}-1.0.patch = "http://patches.example.com/fix-important-bug.patch"
  ```

  In this example, a patch file named `fix-important-bug.patch` is fetched and applied to the source code of the project.

**3. Configure**

- **Task:** `do_configure`

- Action:

   BitBake prepares the source code for compilation. This involves:

  - Running the project's configuration script (often using tools like Autotools or CMake)
  - Applying configuration options specified in the recipe or global/machine-specific configuration files.

**4. Compile (not directly a named task)**

- **Task:** `do_compile`
- **Action:** BitBake compiles the source code into object files and then links them into executable binaries, using an appropriate cross-compilation toolchain.

-----

![yocto-environment](F:\study\ITI_9months\matrial\embeded linux\embeded_linux\assets\yocto-environment.png)

**Overall Workflow**

**1. User Configuration**

- This stage involves users creating custom configurations for their Yocto Project builds. This includes:
  - **Defining build options:** Specifying desired features, packages, and settings for the target image.
  - **Creating recipes:** Writing recipe files (`.bb`) that define how individual software components are downloaded, built, and packaged.
  - **Editing configuration files:** Modifying global configuration files (like `local.conf`) that influence various aspects of the build process.

**2. Source Fetching**

- This stage retrieves the source code for the software components you've selected. It can involve:
  - **Downloading source code:** Using BitBake to fetch code from various sources like Git repositories, tarballs, or local directories.
  - **Version control:** Ensuring the correct revision or version of the code is obtained based on your recipe specifications.

**3. Packaging**

- This stage focuses on creating installable software packages for your target system. It includes:
  - **Compiling software:** Using the appropriate cross-compilation toolchain to build the software for your target device's architecture.
  - **Generating packages:** Creating installable packages in formats suitable for your target system (e.g., RPM, DEB, IPK) using BitBake's packaging mechanisms.
  - **Applying metadata:** Adding necessary metadata (e.g., dependencies, descriptions) to the packages.

**4. Output Packages**

- This represents the final deliverables of the packaging stage:
  - **RPM, DEB, IPK packages:** These are the installable software packages that will be included in your final image.
  - **Metadata/Inputs:** This refers to the additional information associated with the packages, such as their dependencies and build-time inputs.
  - **Process steps:** This could indicate the individual tasks involved within the packaging stage, such as compilation, linking, and packaging commands.

**5. Source Mirror(s)**

- This represents a repository or storage location that holds copies of the source code used during the build process. It can be:
  - **Public mirrors:** Standard repositories from the internet that store open-source software releases.
  - **Local mirrors:** Mirrors set up within your own network to improve build performance and reduce download traffic.

**6. Build System**

- This refers to the overall software and tools used to manage and execute the build process. Key components include:
  - **BitBake:** The task execution engine that interprets recipes and executes tasks according to dependencies.
  - **Toolchain:** The cross-compilation toolchain needed to build software for your target architecture.
  - **Build scripts:** Additional scripts or tools used within the build process for specific tasks like configuration or testing.

**7. Output Image Data**

- This represents the final bootable image generated by the build process. It includes:
  - **Root filesystem:** The core filesystem containing the operating system, libraries, and applications needed to run your system.
  - **Kernel:** The core component responsible for hardware interaction and providing basic system services.
  - **Bootloader:** The program responsible for loading the kernel and initiating the boot process.

**8. Upstream Source**

- This refers to the original source code repositories where the software components originate from. These could be:
  - **Open-source projects:** Public repositories hosting the source code of various software components.
  - **Commercial vendors:** Repositories providing access to licensed software or SDKs.

**9. User**

- This represents the user or developer interacting with the Yocto Project tools and workflow. They perform actions like:
  - **Configuring the build:** Setting up the build environment and defining desired image properties.
  - **Executing the build:** Triggering the build process using BitBake commands.
  - **Managing layers:** Adding custom layers to incorporate additional software or configurations.

**10. Machine Configuration**

- This stage tailors the image to your specific target hardware platform. It involves:
  - **Board Support Packages (BSPs):** Layers providing device-specific drivers, configurations, and support for your target hardware.
  - **Kernel configuration:** Customizing the kernel with options and drivers specific to your hardware.
  - **Device tree:** Defining the hardware components and their configuration within the device tree file.

**11. Policy Configuration**

- This stage enforces policies and guidelines for building the image. It can involve:
- **Security policies:** Establishing security best practices and restrictions on package selection and build options

----------------------------------------

**"Meta" in the Yocto Project**

- **Metadata:** Refers to the recipes, configuration files, and other data that drive the Yocto Project's build process. This is the core use of "meta" in this context.

- Metalayers:

   

  Layers that primarily contain other layers or provide additional functionality to the build system. Think of them as 'layers about layers'. Some essential Yocto Project components come in the form of metalayers:

  - **meta-poky:** Contains Poky-specific recipes and configurations.
  - **meta-openembedded:** Includes a subset of the core OpenEmbedded recipes.

**Examples to Illustrate "Meta"**

- **Recipe (Metadata):** A recipe provides instructions (metadata) on how to build a piece of software (data).
- **Configuration File (Metadata):** A configuration file contains settings (metadata) that control how the build system works (data).
- **Image Recipe (Metadata):** An image recipe defines the list of software packages (data) to include in your final embedded Linux image.