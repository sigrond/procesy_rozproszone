# procesy_rozproszone
[TIN] System komunikacji dla zarządzania rozproszonymi procesami.

 - Do piątku godzin późnonocnych/soboty godzin wczesnorannych - porządna dokumentacja protokołu
 - Do soboty godzin późnonocnych - jak najostateczniejsze dokumentacje pozostałych części
 - Niedziela na ogarnięcie tego do formy reprezentatywnej

Przypominam, by przejrzeć wymagania i nie zapomnieć o różnych duperelach, których sobie prowadzący życzył.

-----------------------------------------------------------------

-Najlepiej, żeby dokumentacja wstępna była już gotowa w niedzielę (22.11.2015), bo w poniedziałek może nie starczyć czasu, a dokumentacje trzeba wysłać mailem. Zalecam, wytwarzanie (i commitowanie) pliku dokumentacji wstępnej itteracyjnie, bo wcześniej będziemy mogli wypatrzyć różne drobne rzeczy do poprawienia.

W protokole zadania zgodnie z propozycją AR. Synchronizacja też zgodnie z propozycją AR przez implementację minimalnego klienta NTP.

Niech tak to narazie wygląda na dokumentacji wstępnej. Jeśli okaże się w trakcie kodzenia, że lepiej zasosować jednak inne rozwiązania, to nie ma problemu, tylko koniecznie w dokumentacji musi się znaleźć wzmianka o tym, wraz z logicznym uzasadnieniem.

-----------------------------------------------------------------
**Nadal nie mamy nazwy projektu!**

Do niedzieli trzeba coś wybrać.

Proponowane nazwy:

1. One to rule them all
2. Rozpraszacz
3. Siewca Procesów
4. PANDA3
5. Low Orbit Process Cannon

Proponowane poważne nazwy:

1. ...

## Struktura drzewa katalogów projektu

````
|- application
|  |- client 
|  |- console
|  |- protocol
|  |- server
|     |- server.cpp
|     |- ...
|
|- organizacja
|- wireshark
````

## Rozszerzenia nagłówków

Nie chcę się z nikim gryźć o to, więc ustalmy czy stosujemy .hpp, by było jednolicie.
Wedle sztuki .hpp to nagłówki C++ only, a .h to C/C++ compatible; nie żeby mi jakoś bardzo zależało, więc proszę o mniej lub bardziej demokratyczne narzucenie konwencji. Im mniej rozbieżności, tym mniej możliwego czepialstwa ze strony prowadzącego. // AR


