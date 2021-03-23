#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
	puts("Insert char: ");
	char aux = getchar();

	pid_t sonA, sonB;

	sonA = fork();
	if (sonA > 0)
	{ //father create second son
		sonB = fork();
	}

	if (sonA > 0 && sonB > 0) //father
	{
		while (wait(NULL) > 0)
			;
		puts("Sons are dead, father will die");
	}
	else if (sonA == 0 && sonB != 0)
	{ //sonA of father prints next char
		sleep(1);
		printf("%c\n", aux + 1);
		printf("afeg");
	}
	else if (sonB == 0 && sonA != 0)
	{ //sonB of father prints next char
		printf("%c\n", toupper(aux));
	}

	return 0;
}
