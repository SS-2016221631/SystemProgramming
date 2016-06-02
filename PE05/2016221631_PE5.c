#include <stdio.h>
#include <signal.h>

int i;

main(){	
	
	for (i=0;i<5;i++){
		void f(int);
		signal(SIGINT, f);
		printf("hello\n");
		printf("hello <press the ctrl + c>\n");
		
		sleep(3);
	}
}
void f(int signum){
	printf("Interrupted! OK to quit (y/n)? ");
	char input[20];
	scanf("%s",input);
	
	if(!strcmp(input,"y")){
		exit(0);
	}else if(!strcmp(input,"n")){
		return;
	}else{
		printf("wrong input!!\n");
	}
	
}

