# coding=utf-8

import os
import sys

# def InstallScript():
#     packages = [
#         "glew",
#         "glfw3",
#         "glm",
#     ]

#     # vcpkg install --triplet=x86-windows:x64-windows <pkg>
#     Platform = os.environ["Platform"]
#     if not Platform in ["x86", "x64"]:
#         raise AssertionError()

#     ERROR_COMMAND = 'IF %ERRORLEVEL% NEQ 0 EXIT /B 1\n'
#     VCPKG_INSTALL = "vcpkg install --triplet {PLATFORM}-windows {PACKAGE}\n"

#     s = ''.join([VCPKG_INSTALL.format(PLATFORM=Platform, PACKAGE=pkg) + ERROR_COMMAND for pkg in packages])

#     with open("install.bat", "w") as f:
#         f.write(s)

def BuildScript():
    print(os.environ["APPVEYOR_BUILD_WORKER_IMAGE"])
    print(os.environ["Configuration"])
    print(os.environ["Platform"])

    VS = os.environ["APPVEYOR_BUILD_WORKER_IMAGE"]
    Config = os.environ["Configuration"]
    Platform = os.environ["Platform"]

    VS_MAP = {
        "Visual Studio 2017" : "Visual Studio 15 2017",
        "Visual Studio 2015" : "Visual Studio 14 2015",
        "Visual Studio 2013" : "Visual Studio 12 2013",
        "Visual Studio 2012" : "Visual Studio 11 2012",
        "Visual Studio 2010" : "Visual Studio 10 2010",
        "Visual Studio 2008" : "Visual Studio 9 2008",
    }

    Generator = VS_MAP[VS]
    if Platform == "x64":
        Generator += " Win64"

    ERROR_COMMAND = 'IF %ERRORLEVEL% NEQ 0 EXIT /B 1\n'
    # CMAKE_COMMAND1 = 'cmake -G"{GENERATOR}" -DCMAKE_TOOLCHAIN_FILE=c:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET={PLATFORM}-windows ..\n'.format(GENERATOR=Generator,PLATFORM=Platform)
    CMAKE_COMMAND1 = 'cmake -G"{GENERATOR}" ..\n'.format(GENERATOR=Generator)
    CMAKE_COMMAND2 = 'cmake --build . --config ' + Config + '\n'

    CMAKE_COMMANDS = ["mkdir build\n",
        "cd build\n",
        CMAKE_COMMAND1,
        ERROR_COMMAND,
        CMAKE_COMMAND2,
        ERROR_COMMAND,
        "cd ..\n",
    ]

    with open("build.bat", "w") as f:
        f.write("".join(CMAKE_COMMANDS))

if __name__ == "__main__":
    if not len(sys.argv) == 2:
        raise AssertionError()

    mode = sys.argv[1]
    # if not mode in ("install", "build"):
    if not mode in ("build"):
        raise AssertionError()

    print(mode)

    # if mode == "install":
    #     InstallScript()
    # elif mode == "build":
    BuildScript()
