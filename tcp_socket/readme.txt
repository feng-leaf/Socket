./thread_server
AT+QIOPEN=1,1,"TCP","8.147.115.176",6000,0,0
C:\Users\Administrator\Desktop>tcping64.exe  -t 8.147.115.176 6000


PS D:\my_prog> .\tcping64.exe -t 8.147.115.176 6000

** Pinging continuously.  Press control-c to stop **

Probing 8.147.115.176:6000/tcp - No response - time=2016.145ms
Probing 8.147.115.176:6000/tcp - No response - time=2015.374ms
Probing 8.147.115.176:6000/tcp - No response - time=2010.917ms
Control-C


gcc -o test thread_server.c -l pthread
