#include<stdio.h>
#include<string.h>

int main()
{
  char line[50],wordsplit[15][15];
  int i=0,j=0,ind=0,len,linect=0;
  FILE * fp;
  fp = fopen("code","r");
  while( fgets(line,50,fp) != NULL){
    linect++;
    len = strlen(line);
    if(line[len-2]!=';'){
      printf("\nSemi-colon missing - Wrong");
        continue;
    }
              if(line[0]=='i'||line[0]=='c'||line[0]=='f')
              {
                j=0,ind=0;
                  for(i=0;i<(len-1);i++)
                  {
                      if(line[i]==' '||line[i]=='\0'){
                        wordsplit[ind++][j] = '\0';
                        j=0;
                      }
                      else if(line[i]==';'){
                        wordsplit[ind][j]='\0';
                        j=0;
                        wordsplit[++ind][j]=line[i];
                        wordsplit[ind][++j]='\0';
                      }
                      else{
                        wordsplit[ind][j++] = line[i];
                      }
                  }
                printf("\nTokens for line %d:\n",linect);
                for(i=0;i <= ind;i++)
                    printf("%s\n",wordsplit[i]);
                if((strcmp(wordsplit[0],"int")==0||strcmp(wordsplit[0],"char")==0||strcmp(wordsplit[0],"float")==0) && strcmp(wordsplit[2],";")==0 && strcmp(wordsplit[1],";")!=0)
                  printf("Correct\n");
                else
                  printf("Wrong\n");
              }

              if(line[0]=='p')
              {
                j=0,ind=0;
                for(i=0;i<(len-1);i++)
                    {
                          if(line[i]=='('||line[i]==')'||line[i]=='"'||line[i]==';'){
                            wordsplit[ind][j]='\0';
                            j=0;
                            wordsplit[++ind][j++]=line[i];
                            if(line[i]==';')
                              wordsplit[ind][j]='\0';
                          }
                          else{
                            wordsplit[ind][j++] = line[i];
                          }
                    }

                  printf("\nTokens for line %d:\n",linect);
                  for(i=0;i <= ind;i++)
                    printf("%s\n",wordsplit[i]);
                  if((strcmp(wordsplit[0],"printf")==0) && (strcmp(wordsplit[1],"(")==0) && (wordsplit[2][0]=='"') && (strcmp(wordsplit[3],"\"")==0) && (strcmp(wordsplit[4],")")==0) && (strcmp(wordsplit[5],";")==0))
                    printf("Correct\n");
                  else
                    printf("Wrong\n");
              }

              if(line[0]=='s')
              {
                j=0,ind=0;
                for(i=0;i<(len-1);i++)
                    {
                          if(line[i]=='('||line[i]==')'||line[i]=='"'||line[i]==';'||line[i]==','){
                            wordsplit[ind][j]='\0';
                            j=0;
                            wordsplit[++ind][j++]=line[i];
                            if(line[i]==';')
                              wordsplit[ind][j]='\0';
                            if(line[i]==',')
                            {
                              if(line[i+1]!='&')
                              {
                                printf("\nline %d:\n",linect);
                                printf("Wrong");
                                goto nextline;
                              }
                            }
                          }
                          else{
                            wordsplit[ind][j++] = line[i];
                          }
                    }
                  printf("\nTokens for line %d:\n",linect);
                  for(i=0;i <= ind;i++)
                      printf("%s\n",wordsplit[i]);
                  if((strcmp(wordsplit[0],"scanf")==0) && (strcmp(wordsplit[1],"(")==0) && (wordsplit[2][0]=='"') && (strcmp(wordsplit[3],"\"")==0) && (wordsplit[4][0]==',') && (strcmp(wordsplit[ind-1],")")==0))
                    printf("Correct\n");
                  else
                    printf("Wrong\n");
              }
              nextline: ;
  }
  fclose(fp);
  return 0;
}
