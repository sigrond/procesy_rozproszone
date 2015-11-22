# procesy_rozproszone
[TIN] System komunikacji dla zarządzania rozproszonymi procesami.

Wstępny Projekt:

 - Deadline I - poniedziałek 00:00
 - Deadline II - poniedziałek 09:00
 - Deadline III - poniedziałek 23:50

**Każdy, kto się dowali do mojej roboty po godzinie 23 (niedziela), będzie robił przypadki użycia. Nie żartuję.**

Sugestia na przyszłość: nie używajcie formatów kompresujących, których GitHub nie ogarnia. Jeśli trzeba coś zapisać tekstem, używajcie zwykłych plików tekstowych lub najlepiej plików markdown, takich jak ten. Raz, że łatwiej i szybciej można się do nich dobrać, a dwa, przy kolejnych commitach łatwo prześledzić zmiany wewnątrz plików. 

-----------------------------------------------------------------

-Najlepiej, żeby dokumentacja wstępna była już gotowa w niedzielę (22.11.2015), bo w poniedziałek może nie starczyć czasu, a dokumentacje trzeba wysłać mailem. Zalecam, wytwarzanie (i commitowanie) pliku dokumentacji wstępnej itteracyjnie, bo wcześniej będziemy mogli wypatrzyć różne drobne rzeczy do poprawienia.

W protokole zadania zgodnie z propozycją AR. Synchronizacja też zgodnie z propozycją AR przez implementację minimalnego klienta NTP.

Niech tak to narazie wygląda na dokumentacji wstępnej. Jeśli okaże się w trakcie kodzenia, że lepiej zasosować jednak inne rozwiązania, to nie ma problemu, tylko koniecznie w dokumentacji musi się znaleźć wzmianka o tym, wraz z logicznym uzasadnieniem.

## Komunikacja

Jakby co, przez cały weekend będę dostępny na ircu #tin_projekt@irc.quakenet.org

Jeśli ktoś nie ma klienta IRC, może użyć webchatu:

https://webchat.quakenet.org/

nickname: dowolnie, najlepiej taki jak na GitHubie

channel: #tin_projekt

-----------------------------------------------------------------

**Nadal nie mamy nazwy projektu!**

Nikt się nie wypowiadał, więc arbitralnie wybrałem **Low Orbit Task Cannon**.

Jeśli komuś się nie podoba, ma czas oprotestować decyzję do "zanim skończę pisac ten syf".

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


