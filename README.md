![MicroShell](https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Banner.png)
## Final project for the course - **Operating Systems** - UAM

> **Completed during the first semester of computer science studies.**

![Bash](https://github.com/Education-IT/MicroShell/blob/main/images/Bash.png){: align=right width="200"}

The task was to use the C/C++ programming language to create a program that emulates partial functionality of the **Bash** shell. This program is designed to run only on **Unix** systems. During development, I personally used the **Ubuntu** operating system.

![C](https://img.shields.io/badge/C-A8B9CC.svg?style=for-the-badge&logo=C&logoColor=black) ![Bash](https://img.shields.io/badge/GNU%20Bash-4EAA25.svg?style=for-the-badge&logo=GNU-Bash&logoColor=white)  ![Linux](https://img.shields.io/badge/Linux-FCC624.svg?style=for-the-badge&logo=Linux&logoColor=black)[![Website](https://img.shields.io/badge/website-000000?style=for-the-badge&logo=About.me&logoColor=white)](https://education-it.pl/)
## 
**MicroShell Program:**
1) It displays the **login** of the currently logged-in user and the **prompt** symbol in the form of `[{path}] $`, where `{path}` is the path to the current working directory.
2) It handles the `cd` command, which works similarly to the `cd` command known from the bash shell.
3) It allows for creating and deleting directories using the `mkdir` / `rmdir` commands.
4) It accepts commands by name that refer to programs located in directories described by the value of the `PATH` environment variable, and allows for calling these scripts and programs with arguments.
5) It handles the `exit` command, which terminates the shell program.
6) It handles the `help` command, which displays information about the program's author and the offered functionalities.
7) It displays an error message when a command cannot be correctly interpreted.

## Example Usage of the Program
> View after using the `help` command

![MicroShell Help](https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Microshell-help.PNG)

<br>

> Creating / deleting / navigating through the directory tree.

![MicroShell Directory](https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Microshell-dir.PNG)

## Installation:
1) **Clone the *MicroShell* repository.**

```bash
git clone https://github.com/Education-IT/MicroShell.git

```

2) **Navigate to the downloaded directory.**

```bash

cd MicroShell/

```
 
 
3) **Compile the program using gcc.**

```bash

gcc -o microshell microshell.c 

```


4) **Run the program.**

```bash

./microshell

```

  

## What have i learned:
- Prior to studying computer science, I had very little programming experience. This project was an excellent challenge that summarized the knowledge I had acquired so far.
- I learned the basics of utilizing child processes properly and familiarized myself with functions such as `fork()`, `wait()`, `waitpid()`, and `exec()`.
- I encountered difficulties when converting user input in C, which consisted of a string containing multiple words/commands, into an array. I managed to solve this problem by researching online and discovered the `strtok()` function.
