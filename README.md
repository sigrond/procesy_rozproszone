# Low Orbit Task Cannon

[TIN] System komunikacji dla zarządzania rozproszonymi procesami.

## Ogloszenia duszpasterskie
Od tego momentu zalecam żeby dla każdego większego fragmentu pracy stworzyć lub znaleźć odpowiednie issue i dodać je do odpowiedniego milestone'a (ewentualnie takiego utworzyć). Pociąga to też za sobą dodawanie w wiadomościach commitów odnośnika do issue czyli #nr_issue lub jeśli commit zawiera rozwiązanie danego issue to close #nr_issue.
https://help.github.com/articles/closing-issues-via-commit-messages/

## Proponowane podterminy -- *brak dobrze uzasadnionych kontrargumentów oznacza zgode*
Przy okazji prezentacji dr J.W. nalegal, żebysmy zrobili wiekszosć aplikacji w najbliższych 3 tygodniach **(28.11.2015-19.12.2015)**, bo w swieta jest mnóstwo innych rzeczy do robienia, a potem nie ma czasy bo jest fala kolokwiów.
Niniejszym proponuje nastepujace kamienie milowe:
- Na **6.12** przynajmniej szkielety wszystkich elementów, czyli deklaracje klas z metodami. Na tym etapie powinny zostać zadane pytania o szczególy projektu i wypracowanie rozwiazania. **Bez tych rzeczy nie damy rady rozpoczać testów integracyjnych.**
  * Serwer -- TJ -- Rozszeżenie szkieletu serwera. Implementacja kolejki blokujacej i **testy jednostkowe** do niej. Zbudowanie mapy strategii i możliwie metody realizujace te strategie.
  * Protokól -- AR -- szkielet "czarnej skrzynki" z protokolem, ze szczególnym naciskiem na szybkie zdefiniowanie interfejsu (deklaracje metod publicznych). Interfejs protokolu powinien być możliwie ladny i przejżysty. Przydala by sie też jakas implementacja najważniejszych elementów i **testy jednostkowe**. AR ma prawo poprosić kogs o pomoc jesli okaże sie, że ogrom prac go przerasta.
  * Konsola administratora -- KS -- Szczególowy szkielet konsoli. Implementacja wszystkich metod które sie już bedzie dalo napisać, a dla tych których jeszcze nie wiadomo funkcje / metody "zaslepki". Do wszystkiego co sie da **testy jednostkowe**.
  * Agent -- ER -- Szczególowy szkielet agenta. Implementacja wszystkich metod które sie już bedzie dalo napisać, a dla tych których jeszcze nie wiadomo funkcje / metody "zaslepki". Do wszystkiego co sie da **testy jednostkowe**.
- Na **13.12** zaimplementowanie elementów niezbednych do testów integracyjnych, oraz **testy jednostkowe** do nich. Oczekuje, że uda sie nam wtedy wydać pierwsza wersje aplikacji, która jako calosć bedzie realizowala czesć funkcjonalnosci. Do tego **skrypty testowe**. Prosze, żeby zglosil sie ktos, kto bedzie nimi zarzadzal zarzadzal (przynajmniej zdefiniowal co i jak ma dany skrypt testować).
- Na **19.12** wersja aplikacji realizujaca możliwie wszystkie zaplanowane funkcjonalnosci. Testy (skrypty) akceptacyjne.
- **6.01** finalna wersja do wyslania. Jesli wczesniej czasu nie starczy to do tego czasu powinien zostać zaimplementowany klient NTP i podwójny stost IPv4 IPv6.

## Inne uwagi dr J.W. podczas prezentacji
- Zostalismy pochwaleni z szczególowosć dokumentacji wstepnej.
- Tylko my mielismy prezentacje multimedialna i chyba wypadlem nieźle. ;)
- Niedopatrzenie redakcyjne w 2.2 punkt 1.
- Koniecznie wprowadzać pod terminy.
- Pdwójny stos IPv4 IPv6.
- Powinna być wyznaczona osoba odpowiedzialna za dokumentacje.
- Powinna być wyznaczona osoba odpowiedzialna za testy.

## Formaty plików

Nie używajcie formatów kompresujących, których GitHub nie ogarnia. Jeśli trzeba coś zapisać tekstem, używajcie zwykłych plików tekstowych lub najlepiej plików markdown, takich jak ten. Raz, że łatwiej i szybciej można się do nich dobrać, a dwa, przy kolejnych commitach łatwo prześledzić zmiany wewnątrz plików. // AR 

## Typy całkowite

Zwracam uwagę na typy całkowite - jeśli dana zmienna musi mieć zagwarantowany rozmiar 32 bitów, należy użyć long zamiast int.
**Nie ma gwarancji, że unsigned int będzie mógł pomieścić liczby większe niż 2^16-1**

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
