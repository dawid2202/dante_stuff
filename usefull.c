//WIP

/*get help any% sprrdrun*/
robił ktoś 10.15?
    3/4 osób które się pofatygują, żeby sprawdzić, nie robiło - Sagde
czemu to nie działa? no_further_context.jpg
    idk, mi działało

>jakie zadanie
>co nie działa, a ma działać
>screen w raporcie, co się wysypało (chyba, że jest referat w punkcie 2)
>(maybe) fragment kodu, który nawalił
>enjoy better help :D

FAQ:
> program przerwany - SIGSEGV
    wyjście poza zadeklarowany obszar w pamięci (null maybe?)
    program nie skończył się error handlem i dante robi kwiatki
    (czasami/rzadko) niepoprawne wczytywanie danych
> program przerwany - SIGKILL
    program działa zbyt długo
    nieskończona pętla
    planowany input dante < wczytywany przez program
    zbyt głęboko w rekurencje
> program przerwany - SIGBUS
    "z pamięcią coś zdrowo odjebałeś" - @Bedi, dsc roku 2021-22
>ja: działa jak powinien
    dante patrząc na output: NOPE
        szukaj niepotrzebnych białych znaków
        spójrz jeszcze raz na polecenie
        cry_in_the_corner.gif


/*dante error*/
int handle_dante_error(int err_code) {
    switch (err_code) {
        case 0:
            return 0;
        case 1:
            printf("Incorrect input"); return 1;
        case 2:
            printf("Incorrect input data"); return 2;
        case 3:
            return 3;
        case 4:
            printf("Couldn't open file"); return 4;
        case 5:
            printf("Couldn't create file"); return 5;
        case 6:
            printf("File corrupted"); return 6;
        case 7:
            printf("Unsupported file format"); return 7;
        case 8:
            printf("Failed to allocate memory"); return 8;
        case 9:
            printf("Not enough arguments"); return 9;
        default:
            return 0;
    }
}    //podjebane od @Bedi :)

'W ogóle przed wieloma z was pewnie jeszcze jest zadanie 3.12,
'gdzie treść zadania jest zakodowana w pliku i najpierw trzeba
'sobie odkodować, to pewnie wam się przyda od razu znać treść, będzie szybciej

Przygotuj funkcje do kodowania i odkodowywania wiadomosci w obrazach.
    Obraz bedzie zapisany w postaci tekstowej, kazdy wiersz w pliku to jeden wiersz obrazu.
    Obrazy beda w odcieniach szarosci, wartosci pikseli beda w zakresie 0-255.

    Wiadomosc ma byc zakodowana na ostatnim bicie kazdego piksela.
    Oznacza to, ze aby odczytac jeden znak wiadomosci konieczne bedzie przeanalizowanie 8 kolejnych pikseli (tutaj bajto
w) obrazu wejsciowego.

    Funkcje powinny miec nastepujace prototypy:

    int encode(const char *input, char *txt, const char *output)

    Funkcja ma za zadanie zakodowac wiadomosc przekazana w parametrze txt w obrazie,
    ktorego nazwa zostanie przekazana w parametrze input.
    Obraz z ukryta wiadomoscia ma zostac zapisany do pliku o nazwie przekazanej parametrem output.

    Jezeli tresc wiadomosci bedzie krotsza niz maksymalna dopuszczalna dla danego obrazy to najmlodsze bity w pozostalyc
h pikselach powinna zostac wyzerowane.

    Funkcja encode powinna zwrocic wartosc:
     3 - jezeli niemozliwe bedzie zakodowania calej wiadomosci w pliku,
     4 - jezeli nie uda sie utworzyc pliku wyjsciowego,
     2 - jezeli plik wejsciowy nie bedzie istanial,
     1 - w przypadku blednych danych przekazanych podczas wywolywania funkcji encode,
     0 - w przypadku sukcesu.


    int decode(const char * filename, char *txt, int size)

    Funkcja ma odczytac wiadomosc ukryta w pliku o nazwie przekazanej w parametrze filename i zapisac ja do zmiennej txt
.
    Parametr size oznacza pojemnosc tablicy txt w bajtach.

    Funkcja ma zwrocic:
     3 - jezeli dane w pliku wejsciowym beda uszkodzone,
     1 - w przypadku blednych danych wejsciowych,
     2 - kiedy nie uda sie otworzyc pliku wejsciowego,
     0 - w przypadku sukcesu.

    Napisz program, ktory pozwoli uzytkownikowi ukrywac wiadomosc w obrazie i odczytywac wiadomosc z obrazu.

    Wpisanie litery e/E bedzie oznaczalo, ze uzytkownik chce ukryc tekst w obrazie, wtedy program ma pobrac tekst
    do ukrycia (nie wiecej niz 1000 znakow) oraz nazwe pliku z obrazem i nazwe pliku wyjsciowego (nie przekrocza 29 znak
ow).

    Program powinien wyswietlic komunikat:
    - File saved w przypadku powodzenia (kod bledu 0),
    - Couldn't open file - jezeli plik wejsciowy nie zostanie odnaleziony (kod bledu 4).
    - Couldn't create file - jezeli nie mozliwe bedzie utworzenie pliku wyjsciowego (kod bledu 5),
    - File corrupted - jezeli nie uda sie zapisac wiadomosci w pliku (kod bledu 6).

    Wpisanie przez uzytkownika litery d/D bedzie oznaczalo, ze chce on odczytac wiadomosc ukryta w pliku.
    Program powinien zapytac sie uzytkownika o nazwe pliku a nastepnie wyswietlic odczytana wiadomosc i zakonczyc sie z

    kodem bledu 0.

    Program powinien wyswietlic komunikat:
    - Couldn't open file - jezeli nie uda sie otworzyc pliku zrodlowego (kod bledu 4)
    - File corrupted - jezeli nie uda sie odczytac wiadomosci z pliku (kod bledu 6).

    W przypadku podania przez uzytkownika blednego znaku program powinien wyswietlic komunikat Incorrect input data i za
kocznyc dzialanie z kodem bledu 1.

by @Bopke


/*wskaźniki na funkcje*/
typedef void (*FUN_WSK)();
FUN_WSK T[5];

/************/
int add(int a, int b){
    return a+b;
}

typedef int (*FUN_WSK)(int, int);
FUN_WSK[5] = {add, sub,...}

int result = FUN_WSK[0](a, b); //result = add(a, b);

/*makra*/
(w CLion):
shift, shift, "clangd: Preprocess current TU" - podgląd przeprocesowanego kodu

#define FUNCTION(TYPE) TYPE return_##TYPE(return TYPE);
FUNCTION(int);
// int return_int(return int);
