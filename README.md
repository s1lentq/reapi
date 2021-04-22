# Reapi [![Download](https://camo.githubusercontent.com/131d02663845c3c56678ac169696fa702504c4534453ced50f4935d762a3b814/68747470733a2f2f696d672e736869656c64732e696f2f6769746875622f72656c656173652f73316c656e74712f72656170692e737667)](https://github.com/s1lentq/reapi/releases/latest) [![Downloads](https://camo.githubusercontent.com/1f2c6ef35aa9a7e845ca73cb4bba4b29730e30d1056917758a501d7497739519/68747470733a2f2f696d672e736869656c64732e696f2f6769746875622f646f776e6c6f6164732f73316c656e74712f72656170692f746f74616c3f636f6c6f723d696d706f7274616e74)]() [![Percentage of issues still open](http://isitmaintained.com/badge/open/s1lentq/reapi.svg)](http://isitmaintained.com/project/s1lentq/reapi "Percentage of issues still open") [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

AMX Mod X module, using API regamedll &amp; rehlds

## Build instructions
### Checking requirements
There are several software requirements for building ReAPI:

#### Windows
<pre>
Visual Studio 2015 (C++14 standard) and later
</pre>

#### Linux
<pre>
git >= 1.8.5
cmake >= 3.10
GCC >= 4.9.2 (Optional)
ICC >= 15.0.1 20141023 (Optional)
LLVM (Clang) >= 6.0 (Optional)
</pre>

### Building

#### Windows
Use `Visual Studio` to build, open `msvc/reapi.sln` and just select from the solution configurations list `Release` or `Debug`

#### Linux

* Optional options using `build.sh --compiler=[gcc] --jobs=[N] -D[option]=[ON or OFF]` (without square brackets)

<pre>
-c=|--compiler=[icc|gcc|clang]  - Select preferred C/C++ compiler to build
-j=|--jobs=[N]                  - Specifies the number of jobs (commands) to run simultaneously (For faster building)

<sub>Definitions (-D)</sub>
DEBUG                           - Enables debugging mode
USE_STATIC_LIBSTDC              - Enables static linking library libstdc++
</pre>

* ICC          <pre>./build.sh --compiler=intel</pre>
* LLVM (Clang) <pre>./build.sh --compiler=clang</pre>
* GCC          <pre>./build.sh --compiler=gcc</pre>

##### Checking build environment (Debian / Ubuntu)

<details>
<summary>Click to expand</summary>

<ul>
<li>
Installing required packages
<pre>
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install -y gcc-multilib g++-multilib
sudo apt-get install -y build-essential
sudo apt-get install -y libc6-dev libc6-dev-i386
</pre>
</li>

<li>
Select the preferred C/C++ Compiler installation
<pre>
1) sudo apt-get install -y gcc g++
2) sudo apt-get install -y clang
</pre>
</li>
</ul>

</details>

## How can I help the project?
Just install it on your game server and report problems you faced.<br />
Merge requests are also welcome :shipit:
