Simplified DES
==============

Overview
--------
This is a C++ implementation of Simplified DES. Simplified DES is a reduced version of DES for educational purposes developed by Professor Edward Schaefer of Santa Clara University in 1996. It uses 2 rounds, an 8-bit plaintext or cipher, and a 10-bit key. This particular implementation will only work with binary.

This implementation was done by [Kevin O'Connor](http://kevin.oconnor.mp).

Compiling
---------
A Makefile is boundled included which uses STL strings and vectors. g++ is used to compile the source. To do so simply run 'make'.

Usage
-----
This implementation supports encryption and decryption which can be done via the following commands:
    ./sdes encrypt <plaintext> <key>
    ./sdes encrypt 10101010 1011011011

    ./sdes decrypt <ciphertext> <key>
    ./sdes decrypt 00100100 1011011011

License
-------
Yeah, no. No licencing on this. Do what you please with it.

