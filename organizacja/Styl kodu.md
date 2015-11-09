# Styl kodu

Postanowiłem zamieścić tu ogólne wytyczne odnośnie stylu pisanego kodu jak i wskazówki pozwalające uniknąć głupich błędów. Większość (bądź - mam nadzieję - wszystko) to dla was oczywistości, ale wolę dmuchać na zimne.
Dokument prawdopodobnie będzie się przez parę następnych dni rozrastał. 

#### Konsekwentny styl

Ważne - trzymać się raz wybranego stylu pisania. Jeśli komuś wytyczne w tym dokumencie wybitnie nie odpowiadają, bo ma inne nawyki bądź mama mu kazała, niech już pisze po swojemu. Ale niech Bóg będzie miłosierny dla tych, co spróbują mieszać style, bo ja na pewno nie będę.
Zasada ta dotyczy całości wydzielonych części projektu. Jeśli osoba odpowiedzialna za jakąś część pisze w ten, a nie inny sposób, każda linijka kodu ma być napisana w tym samym stylu, nieważne przez kogo.

#### Nazwy

Kod ma być samodokumentujący. Żadnych pajęczyzmów typu klasa A, funkcja f(). Jeśli z nazwy zmiennej/funkcji/klasy nie wynika przeznaczenie, na 99% robisz coś źle. Wyjątek - indeksy w pętlach.
Wykorzystujemy CamelCase dla klas, camelCase dla funkcji i zmiennych, UPPERCASE_UNDERSCORE dla stałych.
````c++
const int MY_CONSTANT

class MyClass
{
    int myField;
    void myMethod();
};
````

#### Deklaracja i definicja

Rozdzielamy deklarację i definicję klas/funkcji. Deklaracje idą do class.hpp, definicje do class.cpp.
(W wypadku napotkania problemów podczas załączania plików nagłówkowych, uprzejmie przypominam o #include guards oraz deklaracjach wyprzedzających w zależnościach cyklicznych.)

#### Komentarze dokumetacyjne

Komentarze dokumentacyjne wstawiamy w miejscu deklaracji (pliki .hpp), zgodnie ze standardem doxygen dla C++. Nie chce mi się w tej chwili na ten temat rozpisywać, więc jak ktoś nie ogarnia, RTFM: http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html

Później dodam więcej szczegółów na ten temat.

#### Komentarze na początku plików

Na razie wkleję po prostu cytat z doktora Wytrębowicza, później wstawię doskładniejszą ściągę:
>Pliki źródłowe powinny mieć w nagłówku metryczkę podającą w jednolity sposób co najmniej: nazwę projektu, autora (autorów), datę utworzenia.

#### Komentarze w .cpp

Wstawiamy je tam, gdzie jest to konieczne z uwagi na nieoczywistość kodu. Zakładamy jednak, że wszyscy jako-tako ogarniają składnię języka wraz z co ciekawszymi smaczkami, więc proszę używać komentarzy tylko tam, gdzie to rzeczywiście potrzebne.

#### Język

Sugeruję angielskie nazwy w kodzie. Brak obsługi polskich znaków później powoduje powstawanie nieczytelnych nazw. Poza tym moim zdaniem to dobry nawyk pisać kod, który przeczyta niemal każdy, nie tylko Polak. 

#### Wydajność a czytelność

Nie poświęcamy czytelności na rzecz wydajności kodu, chyba, że mniej czytelny kod pozwoli nam na uzyskanie złożoności obliczeniowej lub pamięciowej o klasę lepszej. Zejście z 3n do 2n nie jest warte syfu w kodzie. Da się zrobić zajebisty FizzBuzz bez modulo, na przesunięciach cyklicznych i operacjach bitowych, ale konia z rzędem temu, kto to zrozumie w jeden rzut oka.

#### Klamry

Klamry w nowych wierszach:
````c++
if(condition)
{
    ...
    instructions();
    ...
}
````
Jeśli klamry można opuścić, robimy to:
````c++
for(int i = 0; i < MAX; i++)
    if(condition)
        oneInstruction;
````
zamiast
````c++
for(int i = 0; i < MAX; i++)
{
    if(condition)
    {
        oneInstruction;
    }
}
````

#### Wcięcia

Tabulacje na początku linii. Inne zabiegi kosmetyczne - spacje.

#### Operatory

Szanujemy przestrzeń osobistą operatorów dwuargumentowych i oddzielamy je spacjami od argumentów:
````c++
var1 >= var2 + var3 * var4 >> var5;
````
zamiast
````c++
var1>=var2+var3*var4>>var5;
````

#### Stałe

Do stałych gdy to tylko możliwe, używamy const zamiast #define.

#### Magiczne liczby

Żadnych nienazwanych stałych nie wiadomo skąd.
````c++
const int SIZE = 42;
int array[SIZE];
````
zamiast
````c++
int array[42];
````

#### Semantyka

Stosujemy zapis odpowiedni dla kontekstu, dla przykładu:
````c++
char c = 'A';
bool b = true;
int* pi = nullptr;
````
zamiast
````c++
char c = 65;
bool b = 404;
int* pi = NULL;
````
Poza zwiększoną czytelnością, dla nullptr pozwala to uniknąć błędów związanych z przeciążaniem funkcji.

#### Typy liczbowe

Jeśli jakaś zmienna całkowita nie może przyjmować wartości ujemnych, zawsze dodajemy słowo kluczowe unsigned. Dostajemy za darmo zabezpieczenie przed niepożądanymi wartościami i większy zakres zmiennej.

Przypominam, że typy zmiennoprzecinkowe mają ograniczoną precyzję. Używanie == i != do porównywania może nie być najlepszym pomysłem.

#### Użyszkodnicy

Zakładamy, że użytkownik zrobi wszystko, co może, by wprowadzić nieprawidłowe dane i odpowiednio się zabezpieczamy. Dotyczy to zarówno metod publicznych jak i strumieni wejścia. 
