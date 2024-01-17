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
    "z pamięcią coś zdrowo odjebałeś" - Bedi, dsc roku 2021-22
>ja: działa jak powinien
    dante patrząc na output: NOPE
        szukaj niepotrzebnych białych znaków
        spójrz jeszcze raz na polecenie
        cry_in_the_corner.gif


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
