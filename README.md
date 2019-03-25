# mXtract
[![Build Status](https://travis-ci.org/rek7/mXtract.svg?branch=master)](https://travis-ci.org/rek7/mXtract) [![License](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/rek7/mXtract/blob/master/LICENSE) [![Twitter](https://img.shields.io/badge/Twitter-%400x726B-blue.svg)](https://twitter.com/0x726B)
## What is mXtract?
An opensource linux based tool that analyzes and dumps memory. It is developed as an offensive pentration testing tool, its primary purpose is to scan memory for private keys, ips, and passwords using regexes. Remember, your results are only as good as your regexes.
## Screenshots
![Screenshot](https://github.com/rek7/mXtract/blob/master/img/ss1.png)

Scan with verbose and with a simple IP regex, scanning every data segment.
![Screenshot](https://github.com/rek7/mXtract/blob/master/img/ss2.png)

Scan with verbose and with a simple IP regex, scanning only heap and stack.
![Screenshot](https://github.com/rek7/mXtract/blob/master/img/ss3.png)

Scan without verbose, and with a simple IP regex.
## Why dump directly from memory?
In most linux environments users can access the memory of processes, this allows attackers to harvest credentials, private keys, or anything that isnt suppose to be seen but is being processed by a program in clear text.
## Features
+ Ability to enter regex lists
+ Clear and Readable Display
+ Ability to Mass Scan Every Proccess or a Specific PID
+ Able to choose memory sections to scan
+ Memory dumps automatically removes unicode characters which allows for processing with other tools or manually
## Getting started
###### Compiling: ```sh compile.sh``` 
###### This will create the directory bin/ and compile the binary as mXtract
## Commands 
```
        -v      Enable Verbose Output
        -s      Suppress Banner
        -h      Help
        -c      suppress colored output
        -r=     Regex DB
        -a      Scan all memory ranges not just heap/stack
        -w      Write raw memory to file Default directory is pid/
        -o      Write regex output to file
        -d=     Custom Ouput Directory
        -p=     Specify single pid to scan
        Either -r= or -w needed
```
