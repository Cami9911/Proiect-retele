#include "librarii.h"
#include "Login.h"
#include "Joc.h"
void *main_thread(void *p_new_socket);
extern std::vector<Joc> jocuri_active;
class ascultator
{
private:
    int server_fd, new_socket, valread;
    struct sockaddr_in address;

    int addrlen = sizeof(address);

public:
    ascultator();
    ~ascultator();
    void start();
};

void ascultator::start()
{
    do
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::cout << "\n [Server] S-a conectat [" << new_socket << "] ";
        fflush(stdout);
        std::thread fir(main_thread, &new_socket);
        fir.detach();
    } while (1);
}

ascultator::ascultator()
{
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("[Server]\tsocket failed");
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("[Server]\tsetsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("[Server]\tbind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 100) < 0)
    {
        perror("[Server]\tlisten");
        exit(EXIT_FAILURE);
    }
}

ascultator::~ascultator()
{
}

void *main_thread(void *p_new_socket)
{
    int adresa = *(int *)p_new_socket;
    std::string mesaj;
    std::string eroare;
    Login l(adresa);
    Joc j(adresa);
    int id_joc;
    do
    {
        if (!citeste(adresa, mesaj))
        {
            close(adresa);
            return nullptr;
        }
        int cod_comanda = atoi(mesaj.c_str());

        switch (cod_comanda)
        {
        case 1:
            l.start();
            break;
        case 3:
        {
            jocuri_active.push_back(j); //pornesc jocul
            id_joc = jocuri_active.size() - 1;
            j.play(1,adresa);
        }
        break;
        case 4:
             conectareLaJoc(adresa);
            break;

        default:
            break;
        }
    } while (1);
    close(adresa);
    return nullptr;
}
