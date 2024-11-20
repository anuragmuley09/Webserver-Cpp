# Webserver in c++
<br>
Simple web server in c++ using "winsock" library.
<br>
web server can be tailored to our own specific requirement.
<br>
<br>First of all, i want to thank "Eric O Meehan". [link](https://www.youtube.com/@eom-dev).<br>
<br>And also this guy [link](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)<br>


## How to run?
<br>
test.cpp (Networking/Server) is our main file.
First we have compile that file first. But We have to comple all the helping file also.
This code is modular, thus we have to compile each cpp file inside 'Sockets' folder.
<br>
use below command:
<br>
g++ Server/test.cpp Server/TestServer.cpp Server/SimpleServer.cpp Sockets/SimpleSocket.cpp Sockets/BindingSocket.cpp Sockets/ListeningSocket.cpp -o test.exe -lws2_32
<br>
now why am i doing '-lws2_32' is an intresting part. 
<br>
Windows uses a special library called ws2_32 to handle networking tasks like creating sockets, sending/receiving data, and working with IP addresses. This library is part of the Windows Sockets API, also known as Winsock.
<br>
When you compile your code, the -lws2_32 flag tells the compiler to include the ws2_32 library so it can "link" your networking-related functions (like socket, bind, recv, etc.) to the actual code in the library.
<br>
Without the -lws2_32 flag:

The compiler will recognize your networking function calls, but it won't know where to find their actual implementation.
This causes a "linker error" because the compiler can’t resolve those functions.
So, in simple terms:
<br>
-lws2_32 is like telling the compiler: "Hey, for all the networking stuff in my code, use this library (Winsock 2) to make it work.
<br>



<br>After compiling, if we hit the 127.0.0.1 it should print all the logs in terminal.<br>