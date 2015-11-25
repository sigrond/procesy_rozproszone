# Low Orbit Task Cannon

[TIN] System komunikacji dla zarządzania rozproszonymi procesami.

## Prezentacja watępna

Prezentacja jest najprawdopodobniej w piątek o 18 (27.11.2015). W związku z tym prezentację, slajdy i konspekt (kartka podpowiadająca co mówić), bendę robił w czwartek. Prosił bym o wprowadzenie poprawek redaktorskich, oraz propozycje co jeszcze powuedzieć o projekcie.

## Formaty plików

Nie używajcie formatów kompresujących, których GitHub nie ogarnia. Jeśli trzeba coś zapisać tekstem, używajcie zwykłych plików tekstowych lub najlepiej plików markdown, takich jak ten. Raz, że łatwiej i szybciej można się do nich dobrać, a dwa, przy kolejnych commitach łatwo prześledzić zmiany wewnątrz plików. // AR 

## Komunikacja

Kanał irc #tin_projekt @ irc.quakenet.org

Jeśli ktoś nie ma klienta IRC, może użyć webchatu:

https://webchat.quakenet.org/

nickname: dowolnie, najlepiej taki jak na GitHubie

channel: #tin_projekt


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
|- documentation
|- organizacja
|- wireshark
````

## Rozszerzenia nagłówków

Nie chcę się z nikim gryźć o to, więc ustalmy czy stosujemy .hpp, by było jednolicie.
Wedle sztuki .hpp to nagłówki C++ only, a .h to C/C++ compatible; nie żeby mi jakoś bardzo zależało, więc proszę o mniej lub bardziej demokratyczne narzucenie konwencji. // AR
