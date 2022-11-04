![enter image description here](https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Banner.png)
## Projekt zaliczeniowy na przedmiot - ***Systemy Operacyjne*** - **UAM**

> **Zrealizowano w pierwszym semestrze studiów informatycznych.**

<img align="right" src="https://github.com/Education-IT/MicroShell/blob/main/images/Bash.png" width="200"/>

Zadanie polegało na wykorzystaniu języka C/C++ do napisania programu
odzwierciedlającego częściowe działanie powłoki **Bash**. Program ten, z założenia, możliwy jest jedynie do uruchomienia na systemach  **Unix***. W trakcie pracy, osobiście korzystałem z sytemu operacyjnego - **Ubuntu**.

![enter image description here](https://img.shields.io/badge/C-A8B9CC.svg?style=for-the-badge&logo=C&logoColor=black) ![enter image description here](https://img.shields.io/badge/GNU%20Bash-4EAA25.svg?style=for-the-badge&logo=GNU-Bash&logoColor=white)  ![enter image description here](https://img.shields.io/badge/Linux-FCC624.svg?style=for-the-badge&logo=Linux&logoColor=black)[ ![enter image description here](https://img.shields.io/badge/website-000000?style=for-the-badge&logo=About.me&logoColor=white)](https://education-it.pl/)
 ## 
**Program "MircroShell" :**
 1)  Wyświetla **login** aktualnie zalogowanego użytkownika oraz **znak zachęty** w postaci `[{path}] $`, gdzie `{path}` jest ścieżką do bieżącego katalogu roboczego.
 2) Obsługuje polecenie `cd`, działające analogicznie jak [`cd`] znane nam z powłoki bash.
 3) Umożliwia tworzenie i usuwanie katalogów za pomocą polecenia `mkdir` / `rmdir` 
 4) Przyjmuje polecenia odwołujące się przez nazwę do programów znajdujących się w katalogach opisanych wartością zmiennej środowiskowej [`PATH`] oraz umożliwia wywołanie tych skryptów i programów z argumentami.
 5) Obsługuje polecenie `exit`, kończące działanie programu powłoki;
 6) Obsługuje polecenie `help`, wyświetlające na ekranie informacje o autorze programu i oferowanych przez niego funkcjonalnościach;
 7) Wypisuje komunikat błędu, gdy niemożliwe jest poprawne zinterpretowanie polecenia;
  
  ##  Przykładowe działanie programu
 > Widok po skorzystaniu z polecenia `help` 


![enter image description here](https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Microshell-help.PNG)

## 
<br>

> Tworzenie / usuwanie / poruszanie się po drzewie - **katalogów**.
> 
>Wykorzystywanie poleceń wskazywanych przez zmienną środowiskową `PATH`.

![enter image description here](https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Microshell-dir.PNG)

##  Instalacja:
1) **Pobierz repozytorium *MicroShell*.**

```bash

git clone https://github.com/Education-IT/MicroShell.git

```

2) **Przejdź do pobranego katalogu.**

```bash

cd MicroShell/

```
 
 
3) **Skompiluj program za pomocą gcc.**

```bash

gcc -o microshell microshell.c 

```


4) **Uruchom program.**

```bash

./microshell

```

  

## Czego się nauczyłem:
- Przed studiami informatycznymi - miałem bardzo małą styczność z programowaniem. Projekt ten był idealnym wyzwaniem, podsumowywującym dotychczasowo zdobytą wiedzę.
- Nauczyłem się podstaw odpowiedniego wykorzystywania procesów potomnych - poznałem funkcje: `fork()` / `wait()`/ `waitpid()` / `exec()`.
- Napotkałem wiele trudności ze zmianą w języku C, wprowadzonego przez uzytkownika: "stringa" w tablice w której na ideksach znajdowały się kolejne słowa/polecenia - poradziłem sobie z tym problemem szukając informacji w Internecie. Dzięki czemu poznałem funkcję `strtok()`.
