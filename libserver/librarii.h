#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 8989
#define BUFFSIZE 4096



void scrie(int adresa, std::string mesaj)
{
    int dimensiune_mesaj = mesaj.size();
    send(adresa, &dimensiune_mesaj, 4, 0);
    send(adresa, mesaj.c_str(), dimensiune_mesaj, 0);
}

int citeste(int adresa, std::string &mesaj)
{
    mesaj.clear();
    int dimensiune_mesaj = 0;
    char buffer[BUFFSIZE];
    read(adresa, &dimensiune_mesaj, 4);
    for (int poz = 0; poz < dimensiune_mesaj; poz += BUFFSIZE)
    {
        bzero(buffer, BUFFSIZE);
        read(adresa, buffer, std::min(BUFFSIZE, dimensiune_mesaj - poz));
        mesaj.append(buffer);
    }
}




