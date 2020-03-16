#include "librarii.h"
class Joc;
std::vector<Joc> jocuri_active;
class Joc
{
private:
    std::vector<std::string> tabla;
    std::vector<int> nivel;
    std::string nume_tabla;

public:
    int signal;

    Joc(int sfd) //creez tabla in fisier
    {
        std::string s("X0000000");
        for (int i = 0; i < 7; ++i)
        {
            tabla.push_back(s);
            nivel.push_back(6);
        }
        nivel.push_back(6); //e ultimul nivel
        signal = 1;

        nume_tabla = std::to_string(jocuri_active.size()) + ".txt"; //nr tabla
        scriere_tabla(1);
    }

    ~Joc()
    {
        remove(nume_tabla.c_str());
    }

    void citire_tabla()
    {
        std::ifstream fout(nume_tabla);
        std::string msg;
        fout>>msg;
        fout >> signal; //afla a cui este tura
        for (auto &i : nivel)
            fout >> i;

        for (auto &s : tabla)
            fout >> s;
        fout.close();
    }

    void scriere_tabla(int player)
    {
        std::ofstream fout(nume_tabla);
        //printf ("%s", "Jucatorul ");
        if(player==-1)
        fout<<"Felicitari! Ai castigat!\n\n";
        else
        fout <<"Jucatorul "<< player << "\n\n";
        for (auto i : nivel)
            fout << i << " ";
        fout << "\n";
        for (auto s : tabla)
            fout << s << '\n';
        fout.close();
    }

    void play(int jucator, int adresa)
    {
        char ch = jucator == 1 ? '*' : '&';
        int poz = 4;
        int stop = 0;
        std::string mesaj;
    
        do
        {
            stop = 0;
            citire_tabla();
            if (signal == -1)
                stop = 1;
            else
            {
                if (signal != jucator)
                    continue;

                citeste(adresa, mesaj);
                poz = atoi(mesaj.c_str());
                
                if (inTabla(nivel[poz], poz))
                {

                    tabla[nivel[poz]][poz] = ch;
                    nivel[poz]--;
                    if (am_castigat(poz))
                    {
                        stop = 1;
                        jucator = 4;
                    }
                    scriere_tabla(3 - jucator);
                }
            }
        } while (!stop);
    }

    bool inTabla(int i, int j)
    { //[i] [j]
        return i >= 0 && i < tabla.size() && j > 0 && j < tabla[i].size();
    }

    bool am_castigat(int poz)
    {
        int vectorX[5] = {0, 1, 2, 3, 4};
        int vectorY[5] = {0, 1, 2, 3, 4};

        int x = nivel[poz] + 1;
        int y = poz;

        int nr_col = 0;

        for (int i = x - 3; i <= x + 3; ++i)
            if (inTabla(i, y) && inTabla(i + 3, y))
            {
                int id = 0;
                for (int j = i; j <= i + 3; ++j)
                    id += tabla[i][y] == tabla[j][y];
                nr_col += id == 4;
            }

        for (int i = y - 3; i <= y + 3; ++i)
            if (inTabla(x, i) && inTabla(x, i + 3))
            {
                int id = 0;
                for (int j = i; j <= i + 3; ++j)
                    id += tabla[x][j] == tabla[x][y];
                nr_col += id == 4;
            }
        for (int ii = -3; ii <= 3; ++ii)
        {
            int xi = x + ii;
            int yi = y + ii;
            int id = 0;
            if (inTabla(xi, yi) && inTabla(xi + 3, yi + 3))
                for (int i = 0; i <= 3; ++i)
                {
                    id += tabla[i + xi][i + yi] == tabla[x][y];
                }
            nr_col += id == 4;
        }
        for (int ii = -3; ii <= 3; ++ii)
        {
            int xi = x + ii;
            int yi = y + ii;
            int id = 0;
            if (inTabla(xi, yi) && inTabla(xi + 3, yi - 3))
                for (int i = 0; i <= 3; ++i)
                {
                    id += tabla[i + xi][-i + yi] == tabla[x][y];
                }
            nr_col += id == 4;
        }
        return nr_col;
    }
};

void conectareLaJoc(int adresa) //citeste nr tablei 
{
    std::string mesaj;
    for (int i = 0; i < jocuri_active.size(); ++i)
        std::cout << i << " ";
    fflush(stdout);

    citeste(adresa, mesaj);
    int id_joc = atoi(mesaj.c_str());
    jocuri_active[id_joc].play(2, adresa);
}
