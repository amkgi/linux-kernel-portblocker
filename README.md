## Simple destination TCP port blocker

### Usage:
Build and load the module:

    git clone https://github.com/amkgi/linux-kernel-portblocker
    cd linux-kernel-portblocker
    make
    sudo insmod port_blocker.ko tcp_port=22
    
*The default port is 80.*
    
Testing:

    curl ya.ru
    
Monitoring:

    sudo dmesg -w | grep port_blocker
        
Unload the module:
    
    sudo rmmod port_blocker
    
### Links: 
1. [The Linux Kernel Module Programming Guide](https://infosecwriteups.com/linux-kernel-communication-part-1-netfilter-hooks-15c07a5a5c4e)
2. [Linux Kernel Communication — Netfilter Hooks](https://infosecwriteups.com/linux-kernel-communication-part-1-netfilter-hooks-15c07a5a5c4e)
    
---    
*Tested on kernel 6.1.50-1-generic in Astra Linux 1.7.5.*