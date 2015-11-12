# Aplikacja testowa dla pluginu

Napisana na szybko testowa aplikacja klient-serwer z przykładowym, prostym protokołem.

**UWAGA: program jest napisany NAPRAWDĘ na szybko. Nie ma komentarzy, jego struktura jest nędzna i zapewne ma błędy. Założenie było takie, że ma to być cokolwiek, co się kompiluje i komunikuje przy wykorzystaniu testowego protokołu. Do projektu tak nie piszemy.**

### Co to robi

Klient łączy się z lokalnie wystawionym serwerem na porcie 5555 i jest obsługiwany w nieskończony pętli. Po podaniu odpowiedniej komendy klient kończy działanie, co również dość brutalnie zabija serwer.

Zapytania są bardzo proste - klient wysyła dwie liczby całkowite i kod operacji. Serwer zgodnie z kodem dodaje, odejmuje, mnoży lub dzieli te liczby i wysyła wynik.

### Protokół

Protokół składa się z trzech pól:
 - 1 bajt: kod działania
 - 4 bajty: pierwsza liczba
 - 4 bajty: druga liczba

Kody działań są następujące:
 - 0 - dodawanie
 - 1 - odejmowanie
 - 2 - mnożenie
 - 3 - dzielenie całkowite z resztą
 - 4 - wynik (używany przez serwer)
 - 5 - błąd (używany przez serwer jeśli otrzymana wiadomość zawiera błędny kod lub każe dzielić przez 0)

Wyniki działań są wysyłane w pierwszej liczbie. Wynik dzielenia jest wysyłany w pierwszej liczbie, a reszta z dzielenia w drugiej.

### Kompilacja

Upewniamy się, że mamy GCC obsługujące C++11 oraz bibliotekę boost.
Wchodzimy do katalogu z plikami źródłowymi i wydajemy polecenie
````
make
````
i jeśli mamy szczęście, wszystko robi się samo.

Jeśli ktoś by chciał kompilować na własną rękę, przypominam o koniczności poinformowania linkera o użytych bibliotekach boost.

### Uruchamianie

Otwieramy dwa terminale. W pierwszym odpalamy serwer:
````
./server
````
w drugim zaś klienta:
````
./client
````
Ważne jest, by zachować kolejność.

W oknie klienta możemy wydawać polecenia w formacie kod liczba_1 liczba_2, na przykład:
````
0 42 7
````
czyli "dodaj 42 i 7"

Powinniśmy w odpowiedzi dostać kod wyniku (4), wynik i 0:
````
4 49 0
````

Aby ubić klienta, wystarczy podać jako kod działania liczbę ujemną.
