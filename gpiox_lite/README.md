# @iiot2k/gpiox_lite

gpio C++ addon example 

## Detail
This example shows the use of Raspberry Pi GPIO in node.js as an addon module.<br>
GPIO access is done using Linux gpio character device interface (V2) implemented in C++.<br>
The node.js addon offers the functions to write and read Raspberry Pi GPIO.<br>

## Build and Execute
Example turns output on and depends of input after 3s or 1s off.<br>

Copy all files to a folder on Raspberry Pi (e.g. /home/pi/gpiox_lite).<br>
Change to this folder:
```
cd  /home/pi/gpiox_lite
```
Build addon:
```
npm install
```
Execute example:
```
node ./
```
