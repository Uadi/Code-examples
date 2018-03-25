#include <iostream>
#include <iomanip> //do setprecision()
#include <fstream> //operacje na plikach
#include <sstream> //do obslugi zmienniej z nazwa pliku
#include <cstring> //do obslugi funkcji z polskimi znakami
#include <cstdlib> //do exita
#include <conio.h> //getch();
#include <string> // dodawanie rozszerzenia

#include <limits>

using namespace std;
int ile, elementy;
char wybor, wybor2;
int input = 0;
int input2 = 0;
int input3 = 0;

int precyzja = 4;

int *dane; //alokacja pamieci
float *wyniki; //alokacja pamieci
std::string nazwapliku;
fstream plik;
std::string nazwapliku2;
fstream plik2; //zapis wyikow
std::string rozszerzenie=".txt";

char *tr(char *str) //POLSKIE ZNAKI
{
    static char buff[256];
    char cp[]="\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215¹æê³ñóœ¿Ÿ¥ÆÊ£ÑÓŒ¯";
    if(strlen(str)>=sizeof(buff)) return str;
    char *bf=buff;
    while(*str)
    {
        char *pos=strchr(cp+18,*str);
        *(bf++)=pos?*(pos-18):*str;
        ++str;
    }
    *bf=0;
    return buff;
}

float input_char(char *wiadomosc) {
	input = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if (ss >> input) {
            if (ss.eof()) break; //Sukces
        }
        cout << tr(wiadomosc);
    }
    return (input);
}

float input_char2(char *wiadomosc, int i) {
	input2 = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if (ss >> input2) {
            if (ss.eof()) break; //Sukces
        }
        cout << "Nie wpisano liczby. " << tr(wiadomosc) << i+1 << ": ";
    }
    return (input2);
}

float input_char3(char *wiadomosc) {
	input3 = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if (ss >> input3) {
            if (ss.eof()) break; //Sukces
        }
        cout << tr("B³¹d. Nie wpisano liczby. Podaj delta(t): ");
    }
    return (input3);
}

int getValidInteger(string prompt);

int sprawdzCzyNieujemna1(char *wiadomosc)
{
    int liczba=-1;
    while (liczba <= 0)
    {
        liczba = input_char(wiadomosc);
        if (liczba <= 0) cout << tr(wiadomosc); cin.clear();
    }
    return liczba;
}

int wprowadzDeltat(char *wiadomosc)
{
    int liczba=-1;
    while (liczba < 0)
    {
        liczba = input_char3(wiadomosc);
        if (liczba < 0) cout << tr(wiadomosc); cin.clear();
    }
    return liczba;
}

int sprawdzPomiar(int j)
{
    int liczba=-1;
    while (liczba < 0)
    {
        cout << tr("Podaj liczbê uszkodzonych elementów w chwili t") << j+1 << ": ";
        liczba = input_char2("Podaj liczbê uszkodzonych elementów w chwili t", j);
        if (liczba < 0) cout << tr("Wpisano liczbe ujemn¹. ");
    }
    return liczba;
}

int menuGlowne()
{
    cout << tr("     Bart³omiej Ka³aska, 1ED23A, 2018")<<endl;
    cout << "-------------------------------------------------------" << endl;
    cout << tr("\t\t     MENU G£ÓWNE") << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "1. Obliczanie dystrybuanty F*(t)" << endl;
    cout << tr("2. Obliczanie funkcji niezawodnoœci R*(t)") << endl;
    cout << tr("3. Obliczanie funkcji gêstoœæi prawdopodobieñstwa f*(t)") << endl;
    cout << tr("4. Obliczanie funkcji intensywnoœci uszkodzeñ lambda*(t)") << endl;
    cout << tr("5. Obliczanie ET") << endl;
    cout << "6. Koniec programu" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << tr("Wybierz opcjê: ");
    wybor = getch();
    cout << wybor;
    return wybor;
}

int wyborDanych ()
{
    cout << endl << endl << tr("Wybierz metodê wprowadzania danych: ");
    cout << endl << tr("1. Rêczne wpisywanie danych") << endl;
    cout << tr("2. Wczytanie danych z istniej¹cego pliku") << endl;
    wybor2 = getch();
    return wybor2;
}

void zapisWynikow(string symbol);

void drukujWyniki(float *tablica, string symbol)
{
    for (int i=0; i<ile; i++)
    {
        cout << setprecision(precyzja) << symbol << "t" << i+1 <<")=" << tablica[i] << endl; // setprecision (ile liczb, ucina te dlugie flaoty)
    }
    zapisWynikow(symbol);
}

void odczyt()
{
    cout << tr("Podaj nazwê instniej¹cego pliku tekstowego, z którego chcesz odczytaæ dane (np. dane1): ");
    cin >> nazwapliku;
    nazwapliku.append(rozszerzenie);
    plik.open(nazwapliku.c_str(), ios::in);

    if (plik.good()==false)
    {
        cout << "Plik o podanej nazwie nie istnieje" << endl;
        exit(0);
    }
}

void zapis()
{
    cout << tr("Podaj nazwê pliku tekstowego, do którego chcesz zapisaæ swoje dane (np. dane1): ");
    cin >> nazwapliku;
    nazwapliku.append(rozszerzenie);
    plik.open(nazwapliku.c_str(), ios::out);

    cout << endl;
    ile = sprawdzCzyNieujemna1("Ile wykonano pomiarów? (Podaj liczbê dodatni¹ ca³kowit¹): ");
    cout << endl << tr("Ile zbadano elementów? (Podaj liczbê dodatni¹ ca³kowit¹): ");
    elementy = sprawdzCzyNieujemna1("Ile zbadano elementów? (Podaj liczbê dodatni¹ ca³kowit¹): ");

    plik<<ile<<endl;
    plik<<elementy<<endl;

    cout << endl;
}

void zapisWynikow(string symbol)
{
    cout << endl << tr("Podaj nazwê pliku tekstowego, do którego chcesz zapisaæ swoje wyniki (np. wyniki1): ");
    cin >> nazwapliku2;
    nazwapliku2.append(rozszerzenie);
    plik2.open(nazwapliku2.c_str(), ios::out);

    plik2 << "Liczba zbadanych elementów: " << elementy << endl;

    for (int i=0; i<ile; i++)
    {
        plik2<< "Elementy uszkodzone w chwili t" << i+1 <<": "<< dane[i] << endl;
    }

    plik2 << endl;
    for (int i=0; i<ile; i++)
    {
        plik2<< symbol << "t" << i+1 <<")=" << wyniki[i] << endl;
    }
    cout << tr("Zapis wykonany. Wciœnij dowolny przycisk, aby wróciæ do menu g³ównego.") << endl;
    getch();
    system("cls");
}

void dystrybutantaFt()
{
    float suma = 0.0;
    dane=0;
    wyniki=0;

    wyborDanych();
    cout << endl;

    switch (wybor2)
    {
        case '1':
            {
                zapis();

                dane = new int [ile]; //alokacja pamieci
                wyniki = new float [ile]; //alokacja pamieci

                for (int i=0; i<ile; i++)
                {
                    dane[i] = sprawdzPomiar(i);
                    plik<<dane[i]<<endl;
                    suma += float(dane[i]);
                    wyniki[i] = suma / float(elementy);
                }
                cout << endl << "Empiryczna dystrybuanta F*(t): " << endl;
                drukujWyniki(wyniki, "F*(");
            }
        break;

        case '2':
            {
                int nrkomorki=0;

                odczyt();
                string linia;
                int nr_linii = 1;

                while (getline(plik,linia))
                {
                   switch (nr_linii)
                   {
                       case 1:
                           {
                                ile = atoi(linia.c_str());
                                dane = new int [ile];
                                wyniki = new float [ile];
                           }
                       break;

                       case 2:  elementy = atoi(linia.c_str()); break;

                       case 3:
                           {
                                dane[nrkomorki]=atoi(linia.c_str());
                                suma += dane[nrkomorki];
                                wyniki[nrkomorki] = suma/float(elementy);
                           }
                   }
                    if (nr_linii == 3) {nr_linii = 2; nrkomorki++;}
                    nr_linii++;
                }
                cout << endl << "Empiryczna dystrybuanta F*(t): " << endl;
                drukujWyniki(wyniki, "F*(");
            }
        break;

        default:
            system("cls"); cout << tr("Taka opcja nie istnieje. Wciœnij dowolny klawisz aby wróciæ do menu g³ównego") << endl; getch(); system("cls");
    }
    delete [] dane;
    delete [] wyniki;
    plik.close();
    plik.clear();
    plik2.close();
    plik2.clear();
}

void niezawodnoscRt()
{
    float suma = 0.0;
    dane=0;
    wyniki=0;

    wyborDanych();
    cout << endl;

    switch (wybor2)
    {
        case '1':
            {
                zapis();

                dane = new int [ile]; //alokacja pamieci
                wyniki = new float [ile]; //alokacja pamieci
                suma = float(elementy);

                for (int i=0; i<ile; i++)
                {
                    dane[i] = sprawdzPomiar(i);
                    plik<<dane[i]<<endl;
                    suma -= float(dane[i]);
                    wyniki[i] = suma / float(elementy);
                }
                cout << endl << tr("Empirczyna funkcja niezawodnoœci R*(t): ") << endl;
                drukujWyniki(wyniki, "R*(");
            }
        break;

        case '2':
            {
                int nrkomorki=0;
                odczyt();

                string linia;
                int nr_linii = 1;

                while (getline(plik,linia))
                {
                   switch (nr_linii)
                    {
                        case 1:
                            {
                                ile = atoi(linia.c_str());
                                dane = new int [ile];
                                wyniki = new float [ile];
                            }
                        break;

                        case 2:
                            {
                                elementy = atoi(linia.c_str());
                                suma = float(elementy);
                            }
                        break;

                        case 3:
                            {
                                dane[nrkomorki]=atoi(linia.c_str());
                                suma = suma - dane[nrkomorki];
                                wyniki[nrkomorki] = suma/float(elementy);
                            }
                        break;
                   }
                    if (nr_linii == 3) {nr_linii = 2; nrkomorki++;}
                    nr_linii++;
                }
                cout << endl << tr("Empiryczna funkcja niezawodnoœci R*(t): ") << endl;
                drukujWyniki(wyniki, "R*(");
            }
        break;

        default:
            system("cls"); cout << tr("Taka opcja nie istnieje. Wciœnij dowolny klawisz aby wróciæ do menu g³ównego") << endl; getch(); system("cls");
    }
    delete [] dane; //zwolnienie pamieci
    delete [] wyniki;
    plik.close();
    plik.clear();
    plik2.close();
    plik2.clear();
}

void prawdopodobienstwoft()
{
    dane=0;
    wyniki=0;
    int deltat=1;

    wyborDanych();
    cout << endl;

    switch (wybor2)
    {
        case '1':
            {
                zapis();

                cout << "Podaj delta(t): ";

                deltat = wprowadzDeltat("B³¹d. Wpisano liczbê niedodatni¹. Podaj delta(t): ");
                //cin >> deltat;

                cout << endl;

                dane = new int [ile]; //alokacja pamieci
                wyniki = new float [ile]; //alokacja pamieci

                for (int i=0; i<ile; i++)
                {
                    dane[i] = sprawdzPomiar(i);
                    plik<<dane[i]<<endl;
                    wyniki[i] = dane[i] / (float(elementy)*deltat);
                }
                cout << endl << tr("Empiryczna funkcja gêstoœci prawdopodobieñstwa f*(t): ") << endl;
                drukujWyniki(wyniki, "f*(");
            }
        break;

        case '2':
            {
                int nrkomorki=0;
                odczyt();

                cout << endl << "Podaj delta(t): ";
                cin.ignore();
                deltat = wprowadzDeltat("B³¹d. Wpisano liczbê niedodatni¹. Podaj delta(t): ");
                //cin >> deltat;

                string linia;
                int nr_linii = 1;

                while (getline(plik,linia))
                {
                   switch (nr_linii)
                   {
                       case 1:
                           {
                                ile = atoi(linia.c_str());
                                dane = new int [ile];
                                wyniki = new float [ile];
                           }
                       break;

                       case 2:  elementy = atoi(linia.c_str()); break;

                       case 3:
                           {
                                dane[nrkomorki]=atoi(linia.c_str());
                                wyniki[nrkomorki] = dane[nrkomorki]/(float(elementy)*deltat);
                           }
                   }
                    if (nr_linii == 3) {nr_linii = 2; nrkomorki++;}
                    nr_linii++;
                }
                cout << endl << tr("Empiryczna funkcja gêstoœci prawdopodobieñstwa f*(t): ") << endl;
                drukujWyniki(wyniki, "f*(");
            }
        break;

        default:
            system("cls"); cout << tr("Taka opcja nie istnieje. Wciœnij dowolny klawisz aby wróciæ do menu g³ównego") << endl; getch(); system("cls");
    }
    delete [] dane;
    delete [] wyniki;
    plik.close();
    plik.clear();
    plik2.close();
    plik2.clear();
}

void intensywnoscUszk()
{
    float suma = 0.0;
    dane=0;
    wyniki=0;
    int deltat=1;

    wyborDanych();
    cout << endl;

    switch (wybor2)
    {
        case '1':
            {
                zapis();

                cout << "Podaj delta(t): ";

                cin.clear();
                //cin.ignore();
                deltat = wprowadzDeltat("B³¹d. Wpisano liczbê niedodatni¹. Podaj delta(t): ");

                cout << endl;

                dane = new int [ile]; //alokacja pamieci
                wyniki = new float [ile]; //alokacja pamieci
                suma = float(elementy);

                for (int i=0; i<ile; i++)
                {
                    dane[i] = sprawdzPomiar(i);
                    plik<<dane[i]<<endl;
                    wyniki[i] = dane[i]/(suma*deltat);
                    suma -= float(dane[i]);
                }
                cout << endl << tr("Empiryczna funkcja intensywnoœci uszkodzeñ lambda*(t): ") << endl;
                drukujWyniki(wyniki, "lambda*(");
            }
        break;

        case '2':
            {
                int nrkomorki=0;
                odczyt();

                cout << endl << "Podaj delta(t): ";
                cin.ignore();
                deltat = wprowadzDeltat("B³¹d. Wpisano liczbê niedodatni¹. Podaj delta(t): ");

                //cin >> deltat;

                string linia;
                int nr_linii = 1;

                while (getline(plik,linia))
                {
                   switch (nr_linii)
                    {
                        case 1:
                            {
                                ile = atoi(linia.c_str());
                                dane = new int [ile];
                                wyniki = new float [ile];
                            }
                        break;

                        case 2:
                            {
                                elementy = atoi(linia.c_str());
                                suma = float(elementy);
                            }
                        break;

                        case 3:
                            {
                                dane[nrkomorki]=atoi(linia.c_str());
                                wyniki[nrkomorki] = dane[nrkomorki]/(suma*deltat);
                                suma = suma - dane[nrkomorki];
                            }
                        break;
                   }
                    if (nr_linii == 3) {nr_linii = 2; nrkomorki++;}
                    nr_linii++;
                }
                cout << endl << tr("Empiryczna funkcja intensywnoœci uszkodzeñ lambda*(t): ") << endl;
                drukujWyniki(wyniki, "lambda*(");
            }
        break;

        default:
            system("cls"); cout << tr("Taka opcja nie istnieje. Wciœnij dowolny klawisz aby wróciæ do menu g³ównego") << endl; getch(); system("cls");
    }
    delete [] dane; //zwolnienie pamieci
    delete [] wyniki;
    plik.close();
    plik.clear();
    plik2.close();
    plik2.clear();
}

void funkcjaET()
{
    float suma = 0.0;
    dane=0;
    wyniki=0;
    float wynik=0.0;
    int deltat=1;

    wyborDanych();
    cout << endl;

    switch (wybor2)
    {
        case '1':
            {
                zapis();

                dane = new int [ile]; //alokacja pamieci
                wyniki = new float [ile]; //alokacja pamieci
                suma = float(elementy);

                cout << "Podaj delta(t): ";
                cin.clear();
                //cin.ignore();
                deltat = wprowadzDeltat("B³¹d. Wpisano liczbê niedodatni¹. Podaj delta(t): ");

                //cin >> deltat;
                cout << endl;

                for (int i=0; i<ile; i++)
                {
                    //cout << "Podaj pomiar dla t=" << i+1 << ": ";
                    //cin >> dane[i];
                    dane[i] = sprawdzPomiar(i);
                    plik<<dane[i]<<endl;
                    suma -= float(dane[i]);
                    wyniki[i] = suma / float(elementy);
                }

                for (int i=0; i<ile; i++)
                {
                    wynik += wyniki[i]*deltat;
                }

                cout << endl << setprecision(precyzja) << "ET = " << wynik << endl;

                cout << endl << tr("Podaj nazwê pliku tekstowego, do którego chcesz zapisaæ swoje wyniki (np. wyniki1): ");
                cin >> nazwapliku2;
                nazwapliku2.append(rozszerzenie);
                plik2.open(nazwapliku2.c_str(), ios::out);

                plik2 << "Liczba zbadanych elementów: " << elementy << endl;

                for (int i=0; i<ile; i++)
                {
                    plik2<< "Elementy uszkodzone w chwili t" << i+1 <<": "<< dane[i] << endl;
                }
                plik2 << endl << "ET = " << wynik << endl;
                cout << tr("Zapis wykonany. Wciœnij dowolny przycisk, aby wróciæ do menu g³ównego.") << endl;
                getch();
                system("cls");
            }
        break;

        case '2':
            {
                int nrkomorki=0;
                odczyt();

                cout << endl << "Podaj delta(t): ";
                cin.ignore();
                deltat = wprowadzDeltat("B³¹d. Wpisano liczbê niedodatni¹. Podaj delta(t): ");

                string linia;
                int nr_linii = 1;

                while (getline(plik,linia))
                {
                   switch (nr_linii)
                    {
                        case 1:
                            {
                                ile = atoi(linia.c_str());
                                dane = new int [ile];
                                wyniki = new float [ile];
                            }
                        break;

                        case 2:
                            {
                                elementy = atoi(linia.c_str());
                                suma = float(elementy);
                            }
                        break;

                        case 3:
                            {
                                dane[nrkomorki]=atoi(linia.c_str());
                                suma = suma - dane[nrkomorki];
                                wyniki[nrkomorki] = suma/float(elementy);
                            }
                        break;
                   }

                    if (nr_linii == 3) {nr_linii = 2; nrkomorki++;}
                    nr_linii++;
                }

                for (int i=0; i<ile; i++)
                {
                    wynik += wyniki[i]*deltat;
                }

                cout << endl << setprecision(precyzja) << "ET = " << wynik << endl;

                cout << endl << tr("Podaj nazwê pliku tekstowego, do którego chcesz zapisaæ swoje wyniki (np. wyniki1): ");
                cin >> nazwapliku2;
                nazwapliku2.append(rozszerzenie);
                plik2.open(nazwapliku2.c_str(), ios::out);

                plik2 << "Liczba zbadanych elementów: " << elementy << endl;

                for (int i=0; i<ile; i++)
                {
                    plik2<< "Elementy uszkodzone w chwili t" << i+1 <<": "<< dane[i] << endl;
                }
                plik2 << endl << "ET = " << wynik << endl;

                cout << tr("Zapis wykonany. Wciœnij dowolny przycisk, aby wróciæ do menu g³ównego.") << endl;
                getch();
                system("cls");
            }
        break;

        default:
            system("cls"); cout << tr("Taka opcja nie istnieje. Wciœnij dowolny klawisz aby wróciæ do menu g³ównego") << endl; getch(); system("cls"); break;
    }

    delete [] dane; //zwolnienie pamieci
    delete [] wyniki;
    plik.close();
    plik.clear();
    plik2.close();
    plik2.clear();
}

int main()
{
    while (true)
    {
        menuGlowne();
        switch (wybor)
        {
            case '1': dystrybutantaFt(); break;
            case '2': niezawodnoscRt(); break;
            case '3': prawdopodobienstwoft(); break;
            case '4': intensywnoscUszk(); break;
            case '5': funkcjaET(); break;
            case '6':
                {
                    cout << endl << endl << tr("Dziêkujemy za skorzystanie z programu. Zapraszamy ponownie!") << endl;
                    getch();
                    exit(0);
                }
            break;
            default:
                {
                    system("cls");
                    cout << tr("B³¹d, nie ma takiej opcji w menu. Wciœnij dowolny klawisz aby wróciæ do menu g³ównego.") << endl;
                    getch();
                    system("cls");
                    break;
                }
        }
    }
}

