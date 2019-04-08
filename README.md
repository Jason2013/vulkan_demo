# Introduction to Vulkan Demo

**Vulkan Demo** is simple `MD2` model viewer based on `Vulkan` API.

**Language/Tools:** C/C++, Vulkan, MS Visual C++ 2017, cmake, git

**Download url:** https://github.com/Jason2013/vulkan_demo/releases/latest

**Source Code:** https://github.com/Jason2013/vulkan_demo

**Features:**
+	MD2 model loading and rendering
+	Based on **Vulkan** API

**Screenshots:**

![Screen Shot 1](https://github.com/Jason2013/vulkan_demo/blob/master/docs/screenshot.png)

**Screencast:**

[Watch on Youtube](https://youtu.be/hbSMGDGro1c)

# Build from source code

1. **Clone the source code from github**:

```
git clone https://github.com/Jason2013/vulkan_demo.git
```

2. **Make a directory for build**: 

```
cd <SRC>
mkdir build
```

3. **Generate `Visual Studio 2017` solution and project files by `CMake`**:

```
cd build
cmake -G"Visual Studio 15 2017 Win64" ..
```

4. **Open the generated solution file by `Visual Studio 2017` and build**.
