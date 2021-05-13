#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <time.h>
#include <stdlib.h>

char getch();
void _terminate();

int
main(int argc, char *argv[])
{
	char c, master;
	const char KEY = ';';
	#define L_STARTS 5
	char *starts[] = {
		"Jhotanas, se ta maluco? o que voce sabe sobre ",
		"Cara, de verdade, mas com sinceridade mesmo ",
		"Me explica uma coisa que ta me deixando atonito, ",
		"Seu arrombado, pq colega vc nao e, me fala o ",
		"Tava pensando auqi, acho que tive uma ideia, me fala "
	};
	#define L_ENDS 3
	char *ends[] = {
		"Eu não falo com bandeirantes",
		"Se ta maluco? Que se ta arrumano?",
		"Você não tem critério, cansei"
	};
	char buff[512];
	char *ans;
	char *start;
	int pos, gap;

	// seed random with clock
	srand(time(0));

	printf("\n* * J H O T A N Á S * *\n");
	while (1) {
		printf("\nVai... pergunta: \n");
		start = starts[rand() % L_STARTS];
		ans = ends[rand() % L_ENDS];
		master = 0;
		pos = 0;
		gap = 1;
		if ((c = getch()) == KEY) {
			master = 1;
			ans = buff;
			printf("%c", start[pos++]);
		} else if (c == (char)10) {
			printf("\n");
			continue;
		} else {
			printf("%c", c);
		}
		fflush(stdout);

		while ((c = getch()) != (char)10) {
			if (c == (char)127) {
				printf("\b \b");
				if (master && pos > 0) {
					pos--;
					if (pos == 0) {
						gap = 0;
					}
				}
			} else {
				if (master) {
					if (c == KEY) {
						master = 0;
					} else {
						buff[pos - gap] = c;
					}
					printf("%c", start[pos++]);
				} else {
					printf("%c", c);
				}
			}
			fflush(stdout);
		}
		buff[pos - gap] = '\0';
		printf("\n\n");
		char bars[] = {'/', '-', '\\', '|'};
		for (int i = 0; i < 7; i++) {
			printf("%c Deixa eu pensa :|", bars[i % sizeof(bars)]);
			fflush(stdout);
			usleep(250000);
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			printf("                   ");
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		}
		printf("%s\n", ans);
	}
}

char
getch()
{
        char buf = 0;
        struct termios old = {0};

        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;

        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");

        if (read(0, &buf, 1) < 0)
                perror ("read()");

        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");

        return (buf);
}

void
_terminate()
{
	perror("Erro ao invocar Jhotanás! Faltou fé no capiroto!");
}
