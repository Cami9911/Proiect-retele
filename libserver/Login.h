#include "librarii.h"

class Login
{
private:
    int adresa;
    std::string nume;
    std::string parola;
public:

    Login(int sockfd) : adresa(sockfd) {};
    void start()
    {
        citeste(adresa,nume);
        citeste(adresa,parola);

        std::string mesaj="0";

        if(nume==parola)
            mesaj="1";
        scrie(adresa,mesaj);  
    }

    void ContNou()
    {
        citeste(adresa,nume);
        citeste(adresa,parola);
    }

};