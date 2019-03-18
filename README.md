# mXtract
## What is mXtract?
An opensource linux based tool that analyses and dumps memory. Its developed as an offensive pentration testing tool which can be used to scan memory for private keys, ips, and passwords.
## Screenshots
![Screenshot](https://github.com/rek7/mXtract/blob/master/img/f8d810903bba3b2f74f0ac8cbef9c2ad.png)

Scan with verbose and with a simple IP regex, scanning every data segment.
![Screenshot](https://github.com/rek7/mXtract/blob/master/img/949227ffe00d6cfb46826c01c9c1c692.png)

Scan with verbose and with a simple IP regex, scanning only heap and stack.
![Screenshot](https://github.com/rek7/mXtract/blob/master/img/ipregex.png)

Scan without verbose, and with a simple IP regex.
## Why dump directly from memory?
In most linux environments users can access the memory of processes, allows attackers to harvest credentials, private keys, or anything that isnt suppose to be seen but is being processed by a program in clear text. Remember your results are only as good as your regexes.
## Features
+ Ability to enter regex lists
+ Clear and Readable Display
+ Ability to Mass Scan Every Proccess or a Specfic PID
+ Able to choose memory sections to scan
+ Memory dumps automatically removes unicode characters which allows for processing with other tools or manually
## Getting started
###### Compiling: ```g++ -std=c++11 -O2 src/main.cpp -o mxtract```
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
