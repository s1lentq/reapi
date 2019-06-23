# Reapi [![Build Status](http://teamcity.rehlds.org/app/rest/builds/buildType:(id:Reapi_Publish)/statusIcon)](http://teamcity.rehlds.org/viewType.html?buildTypeId=Reapi_Publish&guest=1) [![Download](https://camo.githubusercontent.com/a3ac64aab91dcea4e0f3dfd611808ad61cc05798/687474703a2f2f7265686c64732e6f72672f76657273696f6e2f72656170692e737667)](http://teamcity.rehlds.org/guestAuth/downloadArtifacts.html?buildTypeId=Reapi_Publish&buildId=lastSuccessful)
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
