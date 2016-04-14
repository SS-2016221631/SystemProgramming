#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int check(const char *path){
   struct stat stats;
   if (lstat(path, &stats) == 0 && S_ISDIR(stats.st_mode)){
      return 0;
   }
   else
      return 1;
}


int file_del(char *file_name){
   int unlink_retval = unlink(file_name);
   if (unlink_retval != 0){
      return 1;
   }
   return 0;
}


int main(int argc, char *argv[]){
   char buffer[1024];
   FILE* fdin;
   FILE* fdout;
   int nread, i;
   int file_del_retval;
   
   int flag;
   
   flag = check(argv[2]);
   
   if (!strcmp(argv[1],argv[2])){
	   printf("%s and result is same! \n", argv[1]);
	   exit(1);
   }else{
	   fdin = fopen(argv[1], "rb");
	   if (fdin == NULL){
		  printf("open %s failed \n", argv[1]);
		  exit(1);
	   }
   
	   switch (flag){
	   case 0 :
		  chdir(argv[2]);
		  fdout = fopen(argv[1], "wb");
		  if (fdout == NULL){
			 printf("open %s failed \n", argv[1]);
			 exit(1);
		  }
		  while ((nread = fread(buffer, 1, 1, fdin)) > 0){
			 if (fwrite(buffer, nread, 1, fdout) < nread){
				fclose(fdin);
				fclose(fdout);
			 }
		  }

		  fclose(fdin);
		  fclose(fdout);
		  chdir("..");
		  file_del_retval = file_del(argv[1]);
		  if (0 != file_del_retval) {
			 printf("file (%s) delete fail. \n", argv[1]);
		  }
	  
		case 1 :
		  fdout = fopen(argv[2], "wb");
		  if (fdout == NULL){
			 exit(1);
		  }

		  while ((nread = fread(buffer, 1, 1, fdin)) > 0){
			 if (fwrite(buffer, nread, 1, fdout) < nread){
				fclose(fdin);
				fclose(fdout);
			 }
		  }
		  fclose(fdin);
		  fclose(fdout);

		  file_del_retval = file_del(argv[1]);
		  if (0 != file_del_retval) {
			 printf("delete failed \n", argv[1]);
		  }
		}
   }

   
  
   return 0;
}
