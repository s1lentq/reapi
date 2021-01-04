# Reapi [![Build Status](http://teamcity.rehlds.org/app/rest/builds/buildType:(id:Reapi_Publish)/statusIcon)](http://teamcity.rehlds.org/viewType.html?buildTypeId=Reapi_Publish&guest=1) [![Download](https://camo.githubusercontent.com/1e445db0afba4545403a7600f1d51624c50cefc9be27417125a4eddfb6099f24/68747470733a2f2f696d672e736869656c64732e696f2f6769746875622f762f72656c656173652f73316c656e74712f72656170692e737667)](https://github.com/s1lentq/reapi/releases/latest) [![Percentage of issues still open](http://isitmaintained.com/badge/open/s1lentq/reapi.svg)](http://isitmaintained.com/project/s1lentq/reapi "Percentage of issues still open") [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

AMX Mod X module, using API regamedll &amp; rehlds

## Build instructions
There are several software requirements for building ReAPI:
<ol>
<li>Java Development Kit (JDK) 7+ (http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)</li>
<li>For Windows: Visual Studio 2015 and later</li>
<li>For Linux: Intel C++ Compiler 15 and later</li>
</ol>

### Checking requirements
#### JDK version
Windows<pre>&gt; %JAVA_HOME%\bin\javac -version
javac 1.8.0_25
</pre>

Linux
<pre>$ javac -version
javac 1.7.0_65
</pre>

#### Visual Studio
Help -> About

#### ICC
<pre>$ icc --version
icc (ICC) 15.0.1 20141023
</pre>

### Building
On Windows:
<pre>gradlew clean buildRelease</pre>

On Linux (ICC):
<pre>./gradlew clean buildRelease</pre>

On Linux (GCC):
<pre>./gradlew clean -PuseGcc buildRelease</pre>

Compiled binaries will be placed in the build/binaries/ directory

## How can I help the project?
Just install it on your game server and report problems you faced.<br />
Merge requests are also welcome :shipit:
