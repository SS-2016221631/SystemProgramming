#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define oops(m,x) { perror(m) ; exit(x);}

main(int ac, char **av)
{
	int thepipe[2], newfd, pid;
	
	if ( ac != 4 ){
	fprintf(stderr, "usage : pipe cmd1 cmd2 cmd3 \n");
	exit(1);
	}	

	if ( pipe( thepipe ) == -1)
	oops("Cannot get a pipe", 1);

	if ( (pid = fork() ) == -1 )
	oops("Cannot fork", 2);


	if ( pid > 0 ) {
		int innerpipe[2], innerpid;
		if (pipe(innerpipe) == -1)
		oops("Cannot get a pipe",3);

		if ( (innerpid = fork() ) == -1 )
		oops("Cannot fork",4);

		if ( innerpid == 0 ) {
			close(thepipe[0]);
			close(thepipe[1]);	
			close(innerpipe[0]);
			if ( dup2(innerpipe[1], 1) == -1 )
				oops("could not redirect stdin", 5);
			close(innerpipe[1]);

			execlp( av[1], av[1], NULL);
			oops(av[1],6);
		}
		if ( innerpid > 0 ) {
		close(thepipe[0]);
		close(thepipe[1]);
		close(innerpipe[1]);
		if ( dup2(innerpipe[0], 0 ) == -1 )
			oops("could not redirect stdout", 6);

		close(innerpipe[0]);
		execlp( av[2], av[2], NULL);
		oops(av[2], 7);
		}
	}
	if ( pid == 0 ) {
	close(thepipe[0]);

	if ( dup2(thepipe[1], 1) == -1 )
		oops("could not redirect stdout", 7);

	close(thepipe[1]);
	execlp( av[3], av[3], NULL);
	oops(av[3], 8);
	}
}

