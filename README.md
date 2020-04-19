# Overview
This is an attempt of creating a firware for the Pine64 PineTime. This project is based on [https://github.com/bosmoment/PineTime-apps](https://github.com/bosmoment/PineTime-apps).
I'm working on Ubuntu 18.04 Bionic Beaver. For Flashing I use a RaspberryPi 2.

## Setup

Clone this repo with:
```Shellsession
git clone https://github.com/tht-jxny/PineTime-Firmware-with-RIOT.git PineTime
```
RIOT won't be cloned automatically, but it is needed.  
To initialize the RIOT submodule simply type in:

```Shellsession
git submodule init
git submodule update
```

## Developing apps for PineTime

The OS this project is based on is [RIOT](https://riot-os.org/). It is very helpful to read the  [Quick Start](https://doc.riot-os.org/index.html#the-quickest-start), so you get familiar with the project structure.  
For GUI development, [LittlevGL](https://littlevgl.com/) is used. I tried the simulator for VSCode but failed. Therefore I decided to use EclipseCDT for simulating my GUI-code. An excellent installation guide can be found [here](https://github.com/littlevgl/lv_sim_eclipse_sdl).  
For the communication between the watch and your phone, as well as synchronizing time and date via bluetooth, [nimBLE](https://github.com/apache/mynewt-nimble) will be used.

## Building and Flashing

To build an application enter its directory via `cd apps/...`. In the moment, the `pinetime` application is a good starting point. Now use `make all` to build the firmware. 
If you receive an error about the gcc-arm-none-eabi version, follow [this guide](#make-all-error).

## Notes for developing

#### Battery percentage

**Correspondent Voltages and Percentages**

The following table is a result of [this graph](https://forum.pine64.org/showthread.php?tid=8147).

Voltage | Percentage  
---|---  
>3.9V | 100%  
3.75 V | 75%  
3.7 V  | 60%  
3.665 V | 50%  
3.62 V | 30%  
3.58 V | 15%  
3.55 V | 5%  
<3.55 V | LOW  

## Troubleshooting

#### `make all` error with gcc-arm-none-eabi-9-2019-q4-major <a name="make-all-error"></a>
If you stumble across this error, please first uninstall any version of `gcc-arm-none-eabi`.  
Then type in these commands:  

```Shellsession
    mkdir -p /opt
    curl -L -o /opt/gcc-arm-none-eabi.tar.bz2 https://developer.arm.com/-/media/Files/downloads/gnu-rm${ARM_URL}/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2
    echo "fe0029de4f4ec43cf7008944e34ff8cc /opt/gcc-arm-none-eabi.tar.bz2" | md5sum -c 
    tar -C /opt -jxf /opt/gcc-arm-none-eabi.tar.bz2 
    rm -f /opt/gcc-arm-none-eabi.tar.bz2 
    rm -rf /opt/gcc-arm-none-eabi-*/share/doc
```
Then add `/opt/gcc-arm-none-eabi-9-2019-q4-major/bin` to your PATH.

Now it should work.
