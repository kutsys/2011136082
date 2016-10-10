#include <stdio.h>   //ǥ�� ��, ����� ���� ���̺귯���Դϴ�.
#include <dirent.h>  //���͸��� ���õ� �Լ����� ������ ���̺귯���Դϴ�.
#include <string.h>  //���ڿ��� ó���ϱ� ���� ���̺귯�� �Դϴ�.
#include <sys/stat.h> //���� ����, �ý��� ȣ���� ���� ���̺귯���Դϴ�.
#include <stdlib.h>   //posix���̺귯���Դϴ�.

void printdir(char *dir, int depth)
{
   DIR *dp;
   //���丮�� ����� ���� �׸��� ����ü�� dirent�� �ش�˴ϴ�.

   struct dirent *entry;
   struct stat statbuf;
   //������ ���¿� ������ �����ϴ� ����ü�Դϴ�.

   if((dp = opendir(dir)) == NULL) 
   //opendir()�� �ش� ���丮�� ���� ����մϴ�.  

   {
      fprintf(stderr,"cannot open directory: %s\n", dir);
      return;
   }

   //�ش� ���丮�� ���� ���� �� ������Ʈ�� �����ְ� ������ ���� ����� �մϴ�.
   chdir(dir);

   //���� ���丮�� dir�� �����մϴ�.
   
   while((entry = readdir(dp)) != NULL) 

   //readdir()�� �Ű������� ���� ���丮 ��Ʈ�� �ȿ� ���� ���丮 �׸� ���� ����ü�� �����͸� �����ݴϴ�.
   //������ �ְų� ���丮�� ������ NULL���� ��ȯ�մϴ�.   
{
      lstat(entry->d_name,&statbuf);
      //�ش� ���Ͽ� ������ ������ ���� ������ statbuf�� �����ݴϴ�.

      if(S_ISDIR(statbuf.st_mode))   {
         if(strcmp(".",entry->d_name) == 0||strcmp("..",entry->d_name) == 0)           
		 continue;     
         //entry_name�� '.'�̰ų� '..'�̸� continue�� �����մϴ�.
         if(entry->d_name[0] == ".")   
           	 continue;
         //entry->d_name�� ù ���ڰ� '.'�� ���, continue�� �����մϴ�.
         printf("%*s%s/\n",depth,"",entry->d_name);  

         printdir(entry->d_name,depth+4);        
         //����� ����ϰ� ���Ⱑ ����� ���·� ��� ȣ���մϴ�.                      
      }
      else   
      {
         if(entry->d_name[0] == ".")      
            continue;
                                     
         printf("%*s%s\n",depth,"",entry->d_name);  
      }
   }
   //���丮�� �ƴϸ� �������� ���� entry->d_name�� ù ���ڰ� '.'�� ���, continue�մϴ�.
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