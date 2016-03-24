#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

main(int ac, char *av[]){
	if(ac ==1)
		do_ls(".");
	if(av[1][0] == '-'){
		if(av[1][1] == 'r'){
			do_ls_r(".", 1 );
		}else{
			printf("please input correct option! \n");
		}
	}
	else
		while (--ac){
			printf("%s:\n", *++av);
			do_ls(*av);
		}
}

do_ls(char dirname[]){
	DIR		*dir_ptr;
	struct dirent	*direntp;
	
	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "error");
	else{
		while((direntp = readdir(dir_ptr)) != NULL)
			printf("%s\n", direntp->d_name);
		closedir(dir_ptr);
	}
}

do_ls_r(const char *name, int level){
	DIR *dir;
	struct dirent *entry;

	if (!(dir = opendir(name)))
		return;
	if (!(entry = readdir(dir)))
		return;

	do {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
			path[len] = 0;
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			printf("Directory name : %*s[%s]\n", level*2, "", entry->d_name);
			do_ls_r(path, level + 1);
		}
		else
			printf("%*sContents : %s\n", level*2, "", entry->d_name);
	} while (entry = readdir(dir));
	closedir(dir);
}
