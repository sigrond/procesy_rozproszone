# Protokół komunikacyjny serwer-agent

To jest wstępny i ogólnikowy projekt protokołu. Feedback bardzo pożądany.

### Przesyłanie plików

**WAŻNE: sugeruję, byśmy nie utrudniali sobie życia i nie zagłębiali się zbytnio w bawienie się plikami zadania.**

 - Pliki dodajemy siłą wyższej konieczności każdy osobno.
 - Konflikt nazw w obrębie zadania = nadpisanie.
 - Próba dodania więcej niż jednego pliku głównego = usunięcie starego pliku głównego.
 - Nie żądamy usuwania pojedynczych plików, tylko całe zadania. Ludobójstwo może nie jest eleganckie, ale za to mniej w nim zastanawiania się.
 - Żadnych edycji plików. Zadanie jest z zalożenia gotowe i ostateczne.

Innymi słowy, po załadowaniu zadania, możemy je co najwyżej usunąć. Teoretycznie możliwe dodanie kolejnych plików nie powinno wystąpić, patrz punkt wyżej.
Tak, jest to prymitywne, ale nie mamy czasu na budowanie pelnoprawnego protokołu transmisji plików.

Jeśli będziemy cierpieć na nadmiary czasu, możemy się tym pobawić.

--------------------
Poniższa specyfikacja zahacza o implementację agenta, proszę to traktować jako wyjaśnienie idei oraz propozycję.

 - Serwer każdemu zadaniu przypisuje unikalny w obrębie całego systemu identyfikator
 - Zadanie składa się z głównego pliku wykonywalnego i ewentualnych plików pomocniczych
 - Pliki pomocnicze mogą być dowolnymi plikami, zawierającymi dane lub inne programy
 - Pliki nie muszą mieć unikalnych nazw w obrębie całego systemu
 - Protokół wykorzystuje flagę binarną do zaznaczenia, czy dany plik jest plikiem głównym czy plikiem pomocniczym
 - Jedno zadanie ma dokładnie jeden plik główny
 - Po otrzymaniu pliku należącego do zadania o identyfikatorze *id*, agent umieszcza go w folderze *id* (jeśli nie ma folderu, tworzy go)
 - Agent zapamiętuje powiązanie *id* -> plik główny zadania *id*
 - W sposób oczywisty istnieje bijekcja zbioru identyfikatorów na zbiór głównych plików wykonywalnych
 - Komunikat "rozpocznij zadanie *id*" jest realizowany poprzez wejście do folderu *id* i uruchomienie powiązanego z zadaniem *id* pliku głównego
 - Program główny zadania dowolnie wykorzystuje inne pliki z folderu tegoż zadania

Taka organizacja ma następujące zalety:
 - pełne i wyraźne rozdzielenie plików zadań eliminujące obostrzenia odnośnie powtarzalności nazw plików między zadaniami
 - łatwe zarządzanie zadaniami (rozumianymi jako zbiór wielu plików)
 - serwer musi przechowywać tylko identyfikator zadania - nędzne 4 bajty (oczywiście może przechowywać więcej informacji, jeśli to uprości nam życie)

Protokół przesyłania plików musi posiadać:
 - kod operacji dodawania [8 bitów]
 - flagę typu pliku: główny/pomocniczy [1 bit]
 - długość pola nazwy pliku (max 128 bajtów) [7 bitów]
 - suma kontrolna nazwy + pliku [8 bitów]
 - identyfikator zadania [32 bity]
 - dlugość pola danych (maksimum wybadam później) [32 bity]
 - nazwę pliku [max 2^7 bajtów]
 - dane (plik) [max 2^32 bajtów]

Protokół poza realizacją powyższych założeń musi realizować raportowanie sukcesów/niepowodzeń w wykonywaniu żądanych operacji.

**Serwer czeka na raport i nie daje innych poleceń danemu agentowi dopóki nie dostanie odpowiedzi**
W wypadku timeoutu serwer wysyła zapytanie "czy żyjesz?". Trzykrotne niepowodzenie oznacza, że agent jest MIA i trzeba przenieśc zadanie gdzie indziej.

Raportowanie:
 - Kod raportu [8 bitów]

### Zadania

Tu sprawa jest prostsza: 
 - serwer wysyła identyfikator zadania i polecenie (+ ewentualny timestamp dla zadań odłożonych w czasie)
 - agent raportuje sukces/błąd
 - po zakończeniu wykonania zadania agent wysyła wynik, serwer odpowiada potwierdzeniem otrzymania

### Responsywność agentów

Trzeba okresowo badać, czy agent żyje. Można to zrealizować poprzez mechanizm zapytania-odpowiedzi, albo po prostu kazać agentom okresowo wysyłać serwerowi komunikat o tym, że żyją.

### Synchronizacja

To jest problem do solidnego przemyślenia. Możemy to ogólnie zrealizować na cztery sposoby:

**1. Pełna implementacja NTP lub własny protokół synchronizujący**

Zalety:
 - brak zależności od zewnętrznych serwerów czasu i obecności klientów NTP na hoście

Wady:
 - konieczność zaimplementowania serwera i klienta synchronizacji czasu, co może być równie dużym zadaniem co nasz serwer/agent/konsola

**2. Implementacja klienta znanego protokołu (np. ntp)**

Zalety:
 - nie potrzebujemy zewnętrznego klienta ntp

Wady:
 - zależność od zewnętrznych serwerów czasu
 - prostsze niż 1. ale wciąż dodatkowa rzecz do napisania

**3. Niech system to zrobi za nas**

Zalety:
 - względnie mało roboty

Wady:
 - grube założenie, że system ma jakiegoś konkretnego klienta synchronizacji, np. sntp

**4. Kij z precyzją, walnijmy po prostu timestamp z serwera XDDD**

Zalety:
 - niemal zero roboty

Wady:
 - obrzydliwa synchronizacja z błędem zależnym od opóźnienia pakietów w sieci (od kilkunastu ms do nawet kilkunastu/kilkudziesięciu sekund)

### Sumy kontrolne

Musimy się zastanowić, czy robimy sumy kontrolne dla nagłówków protokołu i przesyłanych plików.
