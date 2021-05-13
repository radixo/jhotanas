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
	#define L_STARTS 3
	char *starts[] = {
		"Jhotanas, se ta maluco? o que voce sabe sobre ",
		"Cara, de verdade, mas com sinceridade mesmo ",
		"Me explica uma coisa que ta me deixando atonito, "
	};
	#define L_ENDS 1
	char *ends[] = {
		"Eu não falo com bandeirantes"
	};
	char buff[512];
	char *ans;
	char *start;
	int pos;

	// seed random with clock
	srand(time(0));

	printf("\n* * J H O T A N Á S * *\n");
	while (1) {
		printf("\nVai... pergunta: \n");
		start = starts[rand() % L_STARTS];
		ans = ends[rand() % L_ENDS];
		master = 0;
		pos = 0;
		if ((c = getch()) == KEY) {
			master = 1;
			ans = buff;
			printf("%c", start[pos++]);
		} else if (c == (char)10) {
			printf("\n");
		} else {
			printf("%c", c);
		}
		fflush(stdout);

		while ((c = getch()) != (char)10) {
			if (c == (char)127) {
				printf("\b \b");
				if (master) {
					pos--;
				}
			} else {
				if (master) {
					if (c != KEY) {
						buff[pos - 1] = c;
					} else {
						buff[pos] = '\0';
						master = 0;
					}
					printf("%c", start[pos++]);
				} else {
					printf("%c", c);
				}
			}
			fflush(stdout);
		}
		printf("\n\n%s\n", ans);
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
