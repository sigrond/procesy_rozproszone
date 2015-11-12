# Plugin do Wiresharka

Prosty plugin dokonujący dysekcji testowego protokołu o wdzięcznej nazwie FOO. Rozpoznaje on pola protokołu, opisuje kod operacji, wyświetla stosowny opis pakietu w zależności od kodu i wykrywa błędy (za krótki nagłówek, błędny kod).

Uwaga: plugin był pisany na (bardzo) szybko, proszę nie traktować tego kodu jako wzorcowego.

#### Instalacja

Wrzucamy foo_dissector.lua do $HOME/.wireshark/plugins (*nix) albo %APPDATA%\Wireshark\plugins (Windows).

#### Uruchomienie i testowanie

Wirehark powinien automatycznie załadować plugin. Wybieramy nasłuchiwanie interfejsu loopback, odpalamy serwer, nastepnie klienta. W oknie z listą pakietów powinniśmy zobaczyć Three-Way Handshake TCP sygnalizujący nawiązanie połączenia.
Każde zapytanie z klienta powinno natychmiast skutkować pojawieniem się dwóch pakietów (zapytanie i odpowiedź) z protokołem FOO i informacjami właściwymi dla pakietu. Po kliknięciu na dany pakiet, w oknie ze szczegółami pakietu powinna być pod TCP pozycja z rozwijalną listą pól protokołu FOO.
