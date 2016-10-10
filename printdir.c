#include <stdio.h>   //표준 입, 출력을 위한 라이브러리입니다.
#include <dirent.h>  //디렉터리와 관련된 함수들을 보관한 라이브러리입니다.
#include <string.h>  //문자열을 처리하기 위한 라이브러리 입니다.
#include <sys/stat.h> //파일 정보, 시스템 호출을 위한 라이브러리입니다.
#include <stdlib.h>   //posix라이브러리입니다.

void printdir(char *dir, int depth)
{
   DIR *dp;
   //디렉토리에 저장된 개별 항목의 구조체로 dirent에 해당됩니다.

   struct dirent *entry;
   struct stat statbuf;
   //파일의 상태와 정보를 저장하는 구조체입니다.

   if((dp = opendir(dir)) == NULL) 
   //opendir()은 해당 디렉토리를 열때 사용합니다.  

   {
      fprintf(stderr,"cannot open directory: %s\n", dir);
      return;
   }

   //해당 디렉토리를 열수 없을 때 널포인트를 돌려주고 다음과 같은 출력을 합니다.
   chdir(dir);

   //현재 디렉토리를 dir로 변경합니다.
   
   while((entry = readdir(dp)) != NULL) 

   //readdir()은 매개변수로 들어온 디렉토리 스트림 안에 다음 디렉토리 항목에 대한 구조체의 포인터를 돌려줍니다.
   //오류가 있거나 디렉토리가 끝나면 NULL값을 반환합니다.   
{
      lstat(entry->d_name,&statbuf);
      //해당 파일에 연관된 파일의 상태 정보를 statbuf에 돌려줍니다.

      if(S_ISDIR(statbuf.st_mode))   {
         if(strcmp(".",entry->d_name) == 0||strcmp("..",entry->d_name) == 0)           
		 continue;     
         //entry_name이 '.'이거나 '..'이면 continue를 실행합니다.
         if(entry->d_name[0] == ".")   
           	 continue;
         //entry->d_name의 첫 글자가 '.'일 경우, continue를 실행합니다.
         printf("%*s%s/\n",depth,"",entry->d_name);  

         printdir(entry->d_name,depth+4);        
         //결과를 출력하고 들어쓰기가 적용된 상태로 재귀 호출합니다.                      
      }
      else   
      {
         if(entry->d_name[0] == ".")      
            continue;
                                     
         printf("%*s%s\n",depth,"",entry->d_name);  
      }
   }
   //디렉토리가 아니면 위에서와 같이 entry->d_name의 첫 글자가 '.'일 경우, continue합니다.
   chdir("..");
   closedir(dp);
}
int main()
{
   printf("result\n");
   printdir(".",0);
   printf("done.\n");
   exit(0);
}