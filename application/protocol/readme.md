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

Pola:
 - Kod operacji dodawania [8 bitów]
 - Flaga typu pliku: główny/pomocniczy [1 bit]
 - Długość pola nazwy pliku (max 128 bajtów) [7 bitów]
 - Suma kontrolna nazwy + pliku [16 bitów]
 - ID zadania [32 bity]
 - Dlugość pola danych (maksimum wybadam później) [32 bity]
 - Nazwa pliku [max 2^7 bajtów]
 - Dane (plik) [max 2^32 bajtów]

### Zadania

Tu sprawa jest prostsza: 
 - serwer wysyła identyfikator zadania i polecenie (+ ewentualny timestamp dla zadań odłożonych w czasie)
 - agent raportuje sukces/błąd
 - po zakończeniu wykonania zadania agent wysyła wynik, serwer odpowiada potwierdzeniem otrzymania

Ustalenie: timestamp mniejszy niż aktualny czas oznacza wykonanie natychmiast; zatem oczywistym zdaje się polecenia do wykonania natychmiast wysyłać z timestamp = 0. 

Pola:
 - Kod polecenia [8 bitów]
 - Wypełniacz [24 bity] // jeszcze pomyślę, jak to zagospodarować
 - ID zadania [32 bity]
 - Timestamp [32 bity]

### Responsywność agentów

Trzeba okresowo badać, czy agent żyje. Można to zrealizować poprzez mechanizm zapytania-odpowiedzi, albo po prostu kazać agentom okresowo wysyłać serwerowi komunikat o tym, że żyją.

Zapytanie od serwera:
 - kod "czy żyjesz?" [8 bitów]

Odpowiedź/raport okresowy klienta:
 - kod "tak, żyję" [8 bitów]

Kodu "nie, nie zyję" nie przewidujemy.

### Synchronizacja

Synchronizacja będzie realizowana poprzez wewnętrznego klienta NTP.

Serwer może wysłać do agenta żądanie synchronizacji czasu:

Pola:
 - kod SYN [8 bitów]

Istotne sugestie co do implementacji:
 - nie zmieniamy zegara systemowego (co by wymagało uprawnień root), tylko wyliczamy poprawkę na czas systemowy
 - serwer powinien synchronizować czas natychmiast po uruchomieniu oraz wysyłać polecenie SYN do agenta natychmiast po jego rejestracji
 - serwer i agenci powinni okresowo automatycznie się synchronizować

### Raportowanie

**Serwer po wydaniu jakiejkolwiek komendy czeka na raport i nie daje innych poleceń danemu agentowi dopóki nie dostanie odpowiedzi**

W wypadku timeoutu serwer wysyła zapytanie "czy żyjesz?". Trzykrotne niepowodzenie oznacza, że agent jest MIA i trzeba przenieść zadanie gdzie indziej.

Raportowanie:
 - Kod raportu [8 bitów]

### Przesyłanie wyniku zadania

Tu jest mały problem, bo nie wiadomo zbytnio, co te zadania mają robić, jak mają być interpretowane wyniki. Opracowałem taki uniwersalny schemat:

Pola:
 - Kod return [8 bitów]
 - Exit code [8 bitów]
 - Zwracany typ [8 bitów]
 - Wypełniacz [8 bitów]
 - ID zadania [32 bity]
 - Zwracana wartość

Zwracana wartość może mieć następujące postacie:

dla exit code != 0:
 - Nic

przy zwracaniu typu prostego (liczby)
 - Liczba [32-64 bitów]

przy zwracaniu innych danych:
 - Długość pola danych [32 bity]
 - Dane [max 2^32 bajtów]


Serwer odpowiada raportem otrzymania danych:
 - Kod odpowiedzi [8 bit]
