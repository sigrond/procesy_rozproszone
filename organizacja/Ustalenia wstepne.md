# Wstępne ustalenia projektowe

**UWAGA: Ten dokument będzie bazą pod przyszły oficjalny projekt wstępny. Proszę redagować treść w sposób niedodajacy mi zbyt wiele pracy w przyszłym tygodniu**

## Ustalenia ogólne

#### Temat zadania

Zaprojektowanie i implementacja systemu komunikacji dla zarządzania procesami rozproszonymi.

#### Struktura systemu

> W sieci jest zbiór zarządzanych węzłów, serwer zarządzający i stacja konsoli administratora. W węzłach pracują agenty zarządzające. Agent zarządzający może: załadować kod nowego procesu, usunąć kod procesu, uruchomić/zatrzymać/wznowić/zabić dany proces zgodnie z harmonogramem, wznowić proces nie raportujący swej żywotności, podać dane statystyczne serwerowi. System umożliwia administratorowi zarządzanie rozproszonymi procesami. System komunikacji powinien móc pracować w przestrzeni adresów IPv4 i IPv6. Ponadto należy zaprojektować moduł do Wireshark umożliwiający wyświetlanie i analizę zdefiniowanych komunikatów.

Zadanie dzieli się na pięć głównych problemów:
 - serwer zarządzający agentami, przydzielajacy im zadania i przetwarzający uzyskane wyniki,
 - agenci realizujący zadania poprzez wywołanie i zarządzanie procesami,
 - protokół komunikacyjny między serwerem i agentami,
 - konsola administratora (osobny program? telnet/SSH do serwera?)
 - moduł do Wiresharka umożliwiający analizowanie komunikacji między serwerem i agentami

#### Środowisko sprzętowo-programowe

System operacyjny: GNU/Linux
Języki programowania: C++11 (GCC 5.2) + boost 1.59 (serwer i agenci); Lua (moduł wireshark)

## Protokół
**TO DO ASAP**

## Serwer
**TO DO**

## Agenci
**TO DO**

## Konsola
**TO DO**

## Moduł Wireshark
**TO DO** 
