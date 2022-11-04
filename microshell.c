#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h> 
#include <string.h> 
#include <sys/types.h> 
#define ROZMIAR 1000 
#define Red "\033[31m"
#define Reset "\x1b[0m"
#define Blue "\033[36m"  
#define Green "\033[32m" /* https://godoc.org/github.com/whitedevops/colors */
#define Black "\033[30m"
#define BRed "\033[41m"
#define BGreen "\033[42m"
#define Clear "\033[H\033[J" 

void blad_polecenia()
{
	errno = 2; 
	perror(BRed"operacja niedozwolona");
	printf("numer bledu - (%d)"Reset"\n\n", errno); 
	printf("Wpisz "Green"'help'"Reset" aby zobaczyc wszystkie polecenia oferowane przez powloke\n"); 
	return;
}

void RMDIR(char** polecenie)
{
	int pomocnik;
	int indeks;
	char PATH[ROZMIAR];
	char pomocniczyPATH[ROZMIAR]; 
	getcwd(PATH,sizeof(PATH));
	
	if(strcmp(polecenie[1],"--ignore-fail-on-non-empty")==0){
		indeks=2;
		
	    while(polecenie[indeks]!=NULL){
			rmdir(polecenie[indeks]);
	    	indeks=indeks+1;
			}
	    return;
		}
	else{
		indeks=1;
		
	    while(polecenie[indeks]!=NULL){
			pomocnik=0; 
		    pomocnik=rmdir(polecenie[indeks]);
		    
	    	if(pomocnik<0){
				chdir(polecenie[indeks]); /* aby sprawdzić czy plik istnieje postanowilem sprobowac zapamietac aktualna sciezke i sprobowac się przeniec */
	    		getcwd(pomocniczyPATH,sizeof(pomocniczyPATH));
	    		
	    		if( strcmp(PATH,pomocniczyPATH)==0){ /* jeżeli nowa ścieżka będzie taka sama jak stara to oznacza,że katalog nie iestnieje */
					printf(""Red"nie można usunac katalogu „%s”: plik nieistnieje!"Reset"\n",polecenie[indeks]);
					return;
				}
	    		else if(strcmp(PATH,pomocniczyPATH)!=0){
					printf(""Red"nie można usunac katalogu „%s”: katalog nie jest pusty!"Reset"\n",polecenie[indeks]); 
					chdir(PATH);
					return;
				}
				else{ /* jeżeli natomiast przejście się udało, a pomocnik jest <0 to oznacza że katalog nie jest pusty */
					blad_polecenia(); 
					return;
				}
			}
	
			chdir(PATH); /* wrazie gdyby funckja zmieniła w trakcie działania swoją ścieżkę - w tym momencie kodu wracamy do tej należytej */
			indeks=indeks+1;
		}
	return;
	}
}

void MKDIR(char** polecenie)
{
	int indeks=1; 
	char PATH[ROZMIAR];
	getcwd(PATH,sizeof(PATH));
	int pomocnik;
	
	if((strcmp(polecenie[1],"-p")==0)){
		indeks=2;
		while(polecenie[indeks]!=NULL){    /*(szukając informacji o umask napotkałem w internecie inspiracje*/
			pomocnik=mkdir(polecenie[indeks],0777);/*postanowiłem dodać komunikaty błedów wrazie istniejącego już pliku dzięki temu wiem że mkdir i rmdir */
			if (pomocnik<0){
				printf(""Red"nie można utworzyć katalogu „%s”: plik istnieje"Reset"\n",polecenie[2]); 
				return;
			} 	/* zwracają kod 0 lub -1 */
			chdir(polecenie[indeks]); /* https://www.geeksforgeeks.org/create-directoryfolder-cc-program/ */
			indeks=indeks+1;
		}
	}
	else if (polecenie[indeks]!=NULL){
		while(polecenie[indeks]!=NULL){
			pomocnik=mkdir(polecenie[indeks],0777);
			indeks=indeks+1;
		}
	}
	else{
		blad_polecenia();
		return;
	}
	
	if ((pomocnik<0)&&(strcmp(polecenie[1],"-p")==0)){
		printf(""Red"nie można utworzyć katalogu „%s”: plik istnieje"Reset"\n",polecenie[2]);
	}
	else if (pomocnik<0){
		printf(""Red"nie można utworzyć katalogu „%s”: plik istnieje"Reset"\n",polecenie[1]);
	}
	chdir(PATH);
	return;
}


void help()
{
	printf(Clear);
	printf(BGreen); printf(Black);
	printf("\nMicroshell - help"Reset"\n"); 
	printf("Autor programu - "Blue" Krystian Osiński"Reset"");	printf(Reset); printf("  - Grupa3/1rok/Niestacjonarne/s444820");
	printf("\n\nPolecenia wykonywane przez powloke\n");
	printf("----------------------------------------------------------------------------\n");
	printf("1) "Blue"exit"Reset" (zakonczenie dzialania powloki)\n");
	printf("2) "Blue"cd"Reset" ["Green"PATH"Reset"] (zmiana katalogu roboczego na wskazany przez uzytkownika)\n");
	printf("    |- cd ["Green"."Reset"]  (bieżący katalog)\n");
	printf("    |- cd ["Green"~"Reset"]  (katalog domowy)\n");
	printf("    |- cd ["Green".."Reset"] (nadrzędna lokalizacja)\n");
	printf("    |- cd ["Green"-"Reset"]  (poprzedni katalog)\n");
	printf("3) "Blue"help"Reset" (pomoc i informacje o autorze powloki)\n");
	printf("4) "Blue"clear"Reset" (wyczyszczenie okna terminala z widocznych na ekranie polecen)\n");
	printf("5) "Blue"mkdir"Reset" ["Green"NAME"Reset"] (stworzenie katalogu (jednego lub wielu naraz))\n");
	printf("      |- mkdir ["Green"-p"Reset"] ["Green"NAME"Reset"] (tworzenie katalogu i zarazem podkatalogow - "Red"UWAGA!"Reset"\n");
	printf("                                 nazwy musza byc odzielone spacja!)\n");
	printf("5) "Blue"rmdir"Reset" ["Green"NAME"Reset"] (usuniecie pustego katalogu (jednego lub wielu naraz)\n");
	printf("      |- rmdir ["Green"--ignore-fail-on-non-empty"Reset"] (brak zwracanego bledu)\n");
	printf("6) ["Blue"command"Reset"] ["Green"FLAG"Reset"] ["Green"ARGUMENT"Reset"] (skożystanie z polecen programow znajdujacych\n");
	printf("                               sie w katalogach zmiennej srodowiskowej PATH)\n");
	printf("-----------------------------------------------------------------------------\n");
	return;
}


void cd(char** polecenie, char*homePATH,char* lastPATH)  	/* Chciałem odwzorowac w pelni polecenie 'cd' */
{ 

	char upPATH[]=".."; 
	char pomocniczyPATH[ROZMIAR];
	char PATH[ROZMIAR];
	getcwd(PATH,sizeof(PATH));
	
	if(polecenie[2]!=NULL){
		printf(Red"Za duzo argumentow! Bledna skladnia polecenia!\n"Reset);
		printf("\nWpisz '"Green"help"Reset"' aby zobaczyc wszystkie polecenia oferowane przez powloke\n");
		return;
	} 
	else if((strcmp(polecenie[0],"cd")==0)&&(polecenie[1]==NULL)){
		chdir(homePATH);
		return;
	}
	else if((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],"..")==0)){
		chdir(upPATH);
		return;
	}
	else if((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],"~")==0)){
		chdir(homePATH);
		return;
	}
	else if((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],".")==0)){
		chdir(PATH);
		return;
	}
	else if((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],"-")==0)){
		chdir(lastPATH);
		return;
	}
	else if((strcmp(polecenie[0],"cd")==0)&&(polecenie[1]!=NULL)){
		chdir(polecenie[1]); 
		getcwd(pomocniczyPATH,sizeof(pomocniczyPATH));  
		if( strcmp( PATH, pomocniczyPATH ) == 0 ){/*jeżeli katalog się nie zmienil to oznacza że polecenie było błednie napisane */
			blad_polecenia();
			return;
		}
	}
	
	return;
}

void clear()
{
	printf(Clear);
	return;
}

void Zmiana_naargument(char *dane_wejsciowe,char **polecenie) 
{ /* Uczyłem się o tym z tego źródła - https://brennan.io/2015/01/16/write-a-shell-in-c/?fbclid=IwAR3gOKEMmmIrznCI3FUFOIIdN5uGFlegE-QdoUDmmaWzYufaQKVpsrNP66k */
/* a kod z którego skożystałem znajduje się tutaj -https://cpp0x.pl/dokumentacja/standard-C/strtok/442
i tutaj ---> https://brennan.io/2015/01/16/write-a-shell-in-c/?fbclid=IwAR3gOKEMmmIrznCI3FUFOIIdN5uGFlegE-QdoUDmmaWzYufaQKVpsrNP66k */
/* w funckji strtok w drugim argumencie podajemy jakich znaków szukamy. W moim przypadku jest to spacja , \n oraz  \t */

	char * pojedyncze_slowo = strtok (dane_wejsciowe," \n\t"); /* Funkcja strtok() zastępuję pierwszy znaleziony znak z zmiennej korekta na znak teminalny \0 */
	int indeks=0; 
	while(1){ /*Póki w ciagu znaków ,,dane_wejsciowe" są jakieś znaki - pętla się nie konczy */
		if(pojedyncze_slowo==NULL){
			break;
		}
		else{
			polecenie[indeks]=pojedyncze_slowo; 
			indeks=indeks+1; 
			pojedyncze_slowo=strtok(NULL," \n\t"); /* strtok zwraca wskaznik na sam poczatek lancucha od ktorego zaczeto poszukiwanie pojawienia sie jednego ze znakow ze zmiennej korekta za pierwszym razem */
			polecenie[indeks]=NULL; /* aby powolka dobrze kozystala z argumentów - na samym końcu musimy umieścić NULL ponieważ pare funkcji może
	                           tego wymagać. Również funkcje zainicjowane przezemnie. Po skończeniu pętli na sam koniec trafia NULL*/
		}
	}
	return;
}

int main()
{
	printf(Clear);
	int Y=0;
	char PATH[ROZMIAR];
	char homePATH[ROZMIAR];
	char lastPATH[ROZMIAR];
	getcwd(PATH,sizeof(PATH));
	long int a=(strrchr(PATH,'/')-PATH+1); 
	strncpy(homePATH,PATH,a);
	char *dane_wejsciowe;
	char input[ROZMIAR];
	char *polecenie[ROZMIAR];
	char *USER=getlogin();
	
	while(1)
	{ 
	
		getcwd(PATH,sizeof(PATH));
		printf(Blue);printf("[%s",USER); printf(""Reset":"); printf(""Blue"%s]$ ",PATH); printf(Reset);
		
		dane_wejsciowe = fgets(input, ROZMIAR, stdin);
		Zmiana_naargument(dane_wejsciowe,polecenie);
		
		if(polecenie[0]==NULL){
			continue;
		}               /* W Bash'u brak polecenia nie jest bledem - chcialem to tu odwzorowac */
		else if(strcmp(polecenie[0],"cd")==0){
			cd(polecenie,homePATH,lastPATH); 
			strncpy(lastPATH,PATH,sizeof(lastPATH));
			continue;
		}
		else if(strcmp(polecenie[0],"help")==0){ /* w Bashu konieczne jest napisanie samego polecenia 'help' ale dla mojej powloki przyjalem ze mimo argumentow - polecenie zostanie wykonane */
			help();
			continue;
		}
		else if(strcmp(polecenie[0],"exit")==0){ /* w Bashu jesli napiszemy np 'exit kihfw' - powolka nadal wykona tylko polecenie exit */
			return 0;
		}
		else if((strcmp(polecenie[0],"clear")==0)&&(polecenie[1]==NULL)){ /* w Bashu aby funckja clear sie wykonala nalezy ja podac bez argumentow */
			clear();
			continue;
		}
		else if(strcmp(polecenie[0],"mkdir")==0){
			MKDIR(polecenie);
			continue;
		}
		else if(strcmp(polecenie[0],"rmdir")==0){
			RMDIR(polecenie);
			continue;
		}
		else{ 
			int status; pid_t id = fork();
			if (id == 0){
				Y =  execvp(polecenie[0], polecenie); 
		    	if (Y < 0){  /* Wartością zwrotną funkcji typu exec jest -1 wiec jesli Y < 0 to oznacza brak takiego polecenia */
		    		blad_polecenia();
					return 0;
				} /*komunikat bledu i zakonczenie procesu potomnego */
		    	if (Y > 0){
					return 0;
				}
			} /* zakonczenie procesu potomnego jeżeli się wykonal */
		    else{
				waitpid(id, &status, WUNTRACED);
			}
			continue;
		} /* Czekanie na zakonczenie procesu potomnego i powrót do pętli */ 
		
		continue;
	}
	
	return 0;
}


/* Ucząc się i próbując stworzyć tę powłokę - zbierałem wymagane informacje również z poniższych stron. (z nich nic nie jest skopiowane) */

/* materiały udostępnione w ramach kursu "Systemy operacyjne" */
/* https://cpp0x.pl/dokumentacja/standard-C/1 */
/* https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/ */
/* https://www.fuw.edu.pl/~werner/pmn/CPP_HTML/CPP_files/node117.html */
/* https://danishpraka.sh/2018/01/15/write-a-shell.html */
/* http://wazniak.mimuw.edu.pl/images/e/e5/Sop_07_lab.pdf */

