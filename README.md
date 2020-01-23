[![Build Status](https://travis-ci.org/jrbenito/ABBAurora.svg?branch=master)](https://travis-ci.org/jrbenito/ABBAurora)
# ABBAurora
ABB Aurora protocol (also used by former PowerOne in their Aurora Inverters) for communication with inverters and other devices

## Introduction

Aurora protocol is used by ABB to control/monitor their power devices (inverters, central inverters, etc) over a RS485 bus. Usually
inverters are capable of Aurora Protocol as well as Modbus RTU protocol (ABB sells a converter from Modbus RTU to Modbus TCP/IP). 

This library intends to communicate with ABB Inverters using RS485/Aurora Protocol. Most of commands here were derived from an old
document from Power One (this company was acquired by ABB year ago) and others were derived from projecs like [aurora monitor](http://auroramonitor.sourceforge.net/)
and [Linux Aurora program](http://www.curtronics.com/Solar/AuroraData.html) from Curtis Blank.

A documentation of the Aurora Inverter Communication Protocol can be found [here](https://www.drhack.it/images/PDF/AuroraCommunicationProtocol_4_2.pdf).

## Original work

Original arduino sketches (example provided) were originally wrote by Mr. Davide Rosa who was kind enough to give me permission to
modify as a library and share under LGPL v2.1.

Originals can be found on [Davide's page](http://www.drhack.it/arduino/32-lettura-inverte-power-one-aurora.html).

## New Products

Please notice that newer product report model codes not recognized by this library yet. Please, send pull requests or open a issue
with register values returned by your product and its model and I will be glad to merge/implement it.

## Similar Work

Other Arduino projects that uses Aurora protocol

. [ArdaSol](https://github.com/hpieren/ArdaSol)
. [PVIMon](https://github.com/H4ndl3/pvimon)
