import shelve, sys #shelve - do obslugi baz danych, sys - do wychodzenia z programu

#menu glowne programu
def menu():
    while True:
        print #pusta linia
        print ('-'*70)
        print ('WYPOZYCZALNIA FILMOW'.center(70))
        print ('-'*70)
        print ('Menu glowne'.center(70))
        print
        print ('\t'*3 + '[D] Dodaj uzytkownika\t[U] Usun uzytkownika') #\t - tabulator
        print ('\t'*3 + '[O] Pokaz uzytkownikow\t[W] Wybierz uzytkownika')
        print ('\t'*3 + '[F] Dodaj film do bazy\t[P] Przegladaj baze filmow')
        print ('[K] Koniec programu'.center(70))
        print ('-'*70)
        w = input('Wybierz opcje z menu glownego: ')
        wCzysty = w.strip() #w.strip() zwraca pustego stringa, gdy nic nie wpisano,
                            # w przypadku kiedy uzytkownik cos podal, to zwraca to,
                            # ale usuwa zbedne spacje na poczatku i koncu, o ile takie istnieja
        wCzystyUpper = wCzysty.upper() #zmiana na duze litery
        if not wCzysty:
            print ('Nieznane polecenie :(')
        else:
            if wCzystyUpper[0] in ('DUOWFPK'): #czy pierwszy wpisany znak wystepuje w menu?
                print ('Wybrano opcje: ' + wCzystyUpper[0])
                return wCzystyUpper[0] #zwracamy wybrana opcje menu
            else:
                print ('Nieznane polecenie :(')

#menu uzytkownika
def podMenu():
    global aktualnyUzytkownik
    while True:
        print
        print ('-'*70)
        print ('WYPOZYCZALNIA FILMOW'.center(70))
        print ('-'*70)
        print (('Zalogowany uzytkownik: ' + aktualnyUzytkownik).center(70))
        print
        print ('\t'*2 + '[W] Wypozycz film' + '\t'*3 + '[O] Oddaj film')  # "\t - tabulator
        print ('\t'*2 + '[H] Historia wypozyczania\t[F] Wypozyczone filmy')
        print ('\t'*2 + '[P] Przegladaj baze filmow\t[K] Powrot do menu glownego')
        print ('-'*70)
        w = input('Wybierz opcje z menu uzytkownika: ')
        wCzysty = w.strip() #w.strip() zwraca pustego stringa, gdy nic nie wpisano
                            #w.strip() gdy uzytkownik cos podal, to zwraca to, ale usuwa zbedne spacje na poczatku i koncu
        wCzystyUpper = wCzysty.upper() #zmiana na duze litery
        if not wCzysty:
            print ('Nieznane polecenie :(')
        else:
            if wCzystyUpper[0] in ('WOHFPK'): #czy pierwszy wpisany znak wystepuje w menu?
                print ('Wybrano opcje: ' + wCzystyUpper[0])
                return wCzystyUpper[0] #zwracamy wybrana opcje menu
            else:
                print ('Nieznane polecenie :(')

#inicjalizacja bazy danych
def init():
    global bazaF, bazaU, bazaW #zmienne globalne
    try:
        bazaF = shelve.open ('filmy') #otwarcie bazy filmow
        bazaU = shelve.open ('uzytkownicy') #otwarcie bazy uzytkownikow
        bazaW = shelve.open ('wypozyczenia') #otwarcie bazy historii wypozyczen
    except:
        print ('Blad, baza danych nie zostala otwarta. :(')
        sys.exit(0) #wyjscie z programu w razie bledu
    print ('Inicjalizacja udana. Baza danych otwarta.')

#wybor uzytkownika
def wybor():
    while True:
        w = menu() #podstaw pod "w" to co zwrocila funckja menu(), czyli to co wybral uzytkownik
                    #przy okazji funkcja menu() wyswietla cale menu
        if w=='K':
            break
        elif w=='D':
            dodajUzytkownika()
        elif w=='U':
            usunUzytkownika()
        elif w=='O':
            pokazUzytkownikow()
        elif w=='W':
            wybierzUzytkownika()
        elif w=='F':
            dodajFilm()
        elif w=='P':
            pokazFilmy()

def wybor2():
    while True:
        w = podMenu() #podstaw pod "w" to co zwrocila funckja podMenu(), czyli to co wybral uzytkownik
                        #przy okazji funkcja podMenu() wyswietla menu konkretnego uzytkownika
        if w=='K':
            print ('Wylogowano.')
            break
        elif w=='W':
            wypozycz()
        elif w=='O':
            oddaj()
        elif w=='H':
            historia()
        elif w=='F':
            wypozyczoneFilmy()
        elif w=='P':
            pokazFilmy()

#dodawanie filmu
def dodajFilm():
    global bazaF
    film = input('Podaj tytul filmu, ktory chcesz dodac do bazy: ')
    film = film.strip()
    if not film:
            print ('Tytul filmu nie moze byc pusty.')
    else:
        if film not in bazaF.keys(): #jest juz taki film w bazie?
            #ilosci kopii raczej nie bedzie jednak
            #iloscKopii = input('Podaj ilosc kopii: ') #podaj ilosc kopii filmu
            bazaF[film] = 1
            print ('Wprowadzono nowy film do bazy.')
        else:
            print ('Blad! Taki film jest juz w bazie :(')

#lista filmow
def pokazFilmy():
    global bazaF
    i = 1
    print ('Lista filmow: ')
    print ('-'*70)
    for film in bazaF.keys():
        print ('| ' + str(i) + '. '  + film)
        i=i+1

#dodawanie uzytkownika
def dodajUzytkownika():
    global bazaU, bazaW
    uzytkownik = input('Podaj nazwe nowego uzytkownika: ')
    uzytkownik = uzytkownik.strip()
    if not uzytkownik:
            print ('Nazwa uzytkwnika nie moze byc pusta.')
    else:
        if uzytkownik not in bazaU.keys(): #czy jest juz taki uzytownik w bazie?
            bazaU[uzytkownik]=[] #lista wypozyczen, poczatkowo pusta
            bazaW[uzytkownik]=[] #historia wypozyczen, poczatkowo pusta
            print ('Wprowadzono nowego uzytkownika o nazwie ' + uzytkownik + '.')
        else:
            print ('Blad! Uzytkownik o tej nazwie juz istnieje :(')

#usuwanie uzytkownika
def usunUzytkownika():
    global bazaU, bazaW
    uzytkownik = input('Podaj nazwe uzytkownika do usuniecia: ')
    if uzytkownik in bazaU.keys(): #czy uzytkownik istnieje?
        if ((len(bazaU[uzytkownik])) == 0): #sprawdzenie czy uzytkownik ma wypozyczone jakies filmy
                                            #jesli tak, to nie mozna go usunac, dopoki ich nie odda
            print ('Uzytkownik o nazwie ' + uzytkownik + ' zostal usuniety')
            del bazaU[uzytkownik] #usuniecie uzytkownika
            del bazaW[uzytkownik]
        else:
            print ('Nie mozna usunac uzytkownika, ktory ma wypozyczone filmy.')
    else:
        print ('Taki uzytkownik nie istnieje.')

def wybierzUzytkownika():
    global bazaU, aktualnyUzytkownik
    uzytkownik = input('Podaj nazwe uzytkownika: ')
    aktualnyUzytkownik = uzytkownik
    if uzytkownik in bazaU.keys(): #czy uzytkownik istnieje?
        print ('Wybrano uzytkownika o nazwie ' + aktualnyUzytkownik)
        wybor2()
    else:
        print ('Taki uzytkownik nie instnieje.')

#lista uzytkownikow
def pokazUzytkownikow():
    global bazaU
    haslo = 'admin'
    wpisaneHaslo = input('Podaj haslo dostepu do bazy uzytkownikow: ')
    if(wpisaneHaslo == haslo):
        print ('Lista uzytkownikow: ')
        i=1
        for uzytkownik in bazaU.keys():
            print ('| ' + str(i) + '. '  + uzytkownik)
            i = i + 1
    else:
        print ('Wpisano nieprawidlowe haslo, dostep zabroniony.')

#wypozyczanie
def wypozycz():
    global bazaU, bazaF, aktualnyUzytkownik
    film = input('Podaj tytul filmu, ktory chcesz wypozyczyc: ')
    if film in bazaF.keys(): #jest juz taki film w bazie?

        listawypozyczen = bazaU[aktualnyUzytkownik] #przypisz do listy akutalnie wypozyczone filmy
        listawypozyczen.append(film)    #dodaj do listy wypozyczany wlasnie film
        bazaU[aktualnyUzytkownik]=listawypozyczen  #zastap aktualna liste tego uzytkownika

        print ('Wypozyczono film o tytule: ' + film)
    else:
        print ('Taki film nie istnieje.')

def oddaj():
    global bazaU, bazaF, bazaW, aktualnyUzytkownik
    film = input('Podaj tytul filmu, ktory chcesz oddac: ')
    #if film in bazaF.keys(): #jest w ogole taki film w bazie?
    try:
        listawypozyczen = bazaU[aktualnyUzytkownik] #przypisz do listy akutalnie wypozyczone filmy
        listawypozyczen.remove(film)    #dodaj do listy wypozyczany wlasnie film
                                    #funkcja .remove() zwroci blad, jesli filmu nie ma na liscie i dalej wykona sie to co jest po "except ValueError:"
        bazaU[aktualnyUzytkownik]=listawypozyczen  #zastap aktualna liste tego uzytkownika

        historiawypozyczen = bazaW[aktualnyUzytkownik] #przypisz do listy akutalna historie wypozyczen
        historiawypozyczen.append(film) #dodaj do niej oddawany wlasnie film
        bazaW[aktualnyUzytkownik]=historiawypozyczen #zastap aktualna liste wypozyczen

        print ('Oddano film o tytule: ' + film)

    except ValueError:
        print ('Nie ma takiego filmu na liscie wypozyczonych.')
        pass

#wyswietlanie wypozyczonych filmow
def wypozyczoneFilmy():
    global bazaU, aktualnyUzytkownik
    listawypozyczen = bazaU[aktualnyUzytkownik]
    i=1
    if (len(listawypozyczen)>0): #gdy lista nie jest pusta
        print ('Filmy wypozyczone przez uzytkownika ' + aktualnyUzytkownik + ':')
        for tytul in listawypozyczen:
            print ('| ' + str(i) + '. '  + tytul)
            i = i + 1
    else: #gdy lista jest pusta
        print ('Lista wypozyczonych filmow jest pusta.')

#wyswietlanie hisorii wypozyczen
def historia():
    global bazaW, aktualnyUzytkownik
    historiawypozyczen = bazaW[aktualnyUzytkownik]
    i=1
    if (len(historiawypozyczen)>0): #gdy lista nie jest pusta
        print ('Historia filmow wypozyczonych przez uzytkownika ' + aktualnyUzytkownik + ':')
        for tytul in historiawypozyczen:
            print ('| ' + str(i) + '. '  + tytul)
            i = i + 1
    else: #gdy lista jest pusta
        print ('Historia wypozyczonych filmow jest pusta.')

#program glowny
init()
try:
    wybor()
except:
    print ('Wystapil blad :(')
bazaW.close()   #zamkniecie bazy historii wypozyczen
bazaU.close()   #zamkniecie bazy uzytkownikow
bazaF.close()   #zamkniecie bazy filmow
print ('Program wylaczony, bazy danych zapisane, papa!')



