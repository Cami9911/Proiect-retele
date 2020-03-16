#include "libserver/librarii.h"

int ConectareLaServer(const char *argv)
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form

    if (inet_pton(AF_INET, argv, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    return sock;
}

int main()
{

    int adresa = ConectareLaServer("127.0.0.1");

    std::string mesaj("1");

    std::cout<<"             MENIU\n\n";
    std::cout<<"   Alegeti 3 pentru un joc nou\n";
    std::cout<<"   Alegeti 4 pentru a intra intr-un joc\n";

    
    int poz;
    std::cin >> poz;
    scrie(adresa, std::to_string(poz));

    std::cout<<"Jocul a inceput\n ";
   

    int x=0;
    do
    {
        
        if(x==0)
            std::cout<<"Alege tabla: ";
        else
        std::cout<<"Selectati coloana: ";
        x++;
        int poz;
        std::cin >> poz;
        scrie(adresa, std::to_string(poz));
    } while (1);
    return 0;
}