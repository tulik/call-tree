Drzewo wywołań funkcji w programach C
============
1. Opis ogólny
Program ma zbadać proces wywoływania funkcji w zadanym przez użytkownika kodzie źródłowym
napisanym w języku C, oraz na przedstawić tę zależność w postaci drzewa procesów (call tree).
Program powinien ponadto posiadać możliwość:

  • przetwarzania dowolnie wielu plików w jednym przebiegu,

  • ignorowania funkcji znajdujących się na liście wbudowanej domyślnie i liście dostarczonej
przez użytkownika,

  • wypisania linii, w których rozpoczyna się lub kończy funkcja, oraz tych gdzie wywoływane
są poszczególne funkcje,

  • bezbłędnej obsługi komentarzy,

  • ignorowania makrodefinicji.

Ponadto, program powinien we właściwy sposób reagować na niezbilansowanie nawiasów
klamrowych w plikach źródłowych.

2. Format danych
Program powinien przyjmować jako jeden z argumentów co najmniej jedną nazwę pliku z kodem
źródłowym w języku C.
Ponadto program powinien umożliwiać użytkownikowi podanie nazwy do pliku z listą funkcji,
które należy pominąć przy budowaniu drzewa wywołań. Plik z listą funkcji do pominięcia
powinien zawierać nazwy pomijanych funkcji, a nazwa każdej pomijanej funkcji powinna zawierać
się w osobnej linii.

3. Scenariusz działania programu
Program po wywołaniu z listą argumentów zawierającą:

  • nazwę lub nazwy plików źródłowych do analizy,

  • nazwę pliku z listą funkcji do pominięcia,

podejmie następujące działania:

  • wczyta wskazane dane,

  • utworzy drzewo wywołań funkcji,

  • wypisze drzewo na ekranie użytkownika.

Jeśli kod źródłowy podany do analizy zawierać będzie błędy składniowe, program poinformuje o
tym użytkownika i zakończy dalsze badanie kodu w miejscu napotkania błędu.
