#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
	puts("Insert char: ");
	char aux = getchar();

	pid_t sonA = fork(), sonB;

	if (sonA > 0)
	{ //father
		sonB = fork();
		if (sonB == 0)
		{ //sonB of father prints uppercase letter
			if (aux > 97 || aux < 122)
			{
				printf("%c\n", aux - 32);
			}
		}
	}
	else
	{ //sonA of father prints next char
		if (aux > 121)
		{
			puts("a");
		}
		else
		{
			printf("%c\n", aux + 1);
		}
	}

	return 0;
}
