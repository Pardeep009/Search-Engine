#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include"indexerlist.h"

char* copy_content(FILE *file,int file_size)
{
    char *html_buffer=(char*)calloc(1,file_size);
    int i=0;
    char ch;
    while((ch=fgetc(file))!=EOF)
    {
        html_buffer[i++]=ch;
    }
    html_buffer[i]='\0';
    return html_buffer;
}

void rem1_spa(char s[])
{
	int i=0,j=0,f=0;
  char ch;
	while(s[i]!='\0')
	{
    ch=s[i];
		if(ch==' '||ch==':'||ch=='.'||ch==')'||ch=='!')
		{
			s[i]='\0';
		}
		i++;
	}
}
/*
void rem_spa(char sentence[])
{
  int i=0,j=0,f=1;
  while(sentence[i])
  {
    if(sentence[i]==' ')
    {
      if(f)
      {
        sentence[j++]
      }
    }
    else
    {
      sentence[j++]=sentence[i++];
      f=1;
    }
  }

}
*/
void extract_words(char *start,char *end,char url[])
{
    char word[100]={0};
    int k=0;
    if(start==end)
    {
      printf("\n1\n");
    }
    for(;start!=end;start++)
    {
        if(*start==' '||*start==','||*start=='-'||*start=='.'||*start==':'||*start==';'||*start=='#'||*start=='&')
        {
            if(start+1==end)
            {
                word[k++]=*start;
            }
            word[k]='\0';
            rem1_spa(word);
            if(k>1&&((word[0]>='A'&&word[0]<='Z')||(word[0]>='a'&&word[0]<='z')))
            put_in_list(word,url);
            k=0;
            word[0]='\0';
        }
        else
        {
            word[k++]=*start;
        }
    }
}

void read_file(int file_size,char *html)
{
    char title[]="title";
    int i=0,f=1;
    char url[200]={0};
    while(html[i]!='\n')
    {
        url[i]=html[i];
        i++;
    }
    url[i]='\0';
    if(url[i-1]=='/')
    url[i-1]='\0';
    i++;
    for(;i<file_size;i++)
    {
        if(html[i]=='<')
        {
            if(html[i+1]=='t'&&f)
            {
                char subbuff[6]={0};
                memcpy( subbuff, &html[i+1], 5 );
                subbuff[5] = '\0';
                if(strcmp(subbuff,title)==0)
                {
                    char *start=NULL,*end=NULL;
                    start = &html[i];
                    start = strpbrk(start,">");
                    start++;
                    end = strpbrk(start,"<");
                    extract_words(start,end,url);
                    f=0;
                    continue;
               //     i=i+end-start+2;
                }
            }
            if(html[i+1]=='h'&&html[i+2]>='1'&&html[i+2]<='6')
            {
                char *start=NULL,*end=NULL;
                start = &html[i];
                start = strpbrk(start,">");
                start++;
                while(*start=='<')
                {
                    start = strpbrk(start,">");
                    start++;
                }
                end = strpbrk(start,"<");
                extract_words(start,end,url);
            //    i=i+end-start+2;
            }
        }
    }
}

void rem_spa(char ch[])
{
    int i=0,s=0,f=0,f1=0;
    while(ch[i])
    {
        if(ch[i]==' ')
        {
            f=1;
        }
        else
        {
            if(f&&f1)
            {
                ch[s++]=' ';
                f1=0;
            }
            ch[s++]=ch[i];
            f1=1;
            f=0;
        }
        i++;
    }
    ch[s]='\0';
}

int count_words(char ch[])
{
    int i=0,c=0;
    while(ch[i])
    {
        if(ch[i]==' ')
        c++;
        i++;
    }
    return c+1;
}

void do_next_work()
{
    char ch[100]={0};
    printf("Enter your Query\n");
    scanf("%[^\n]s",ch);
    rem_spa(ch);
    int words = count_words(ch);
    char query[20][30]={0};
    int k=0,i=0,j=0;
    for(int k=0;k<strlen(ch);k++)
    {
        if(ch[k]==' ')
        {
            query[i][j]='\0';
            j=0;
            i++;
        }
        else
        {
            query[i][j++]=ch[k];
        }
    }
    query[i][j]='\0';
    /*
    for(i=0;i<words;i++)
    printf("%s\n",query[i]);
    */
    rank_query(query,words);
}

int main()
{
    inititliase();
    int c=1;
    while(1)
    {
        char file_name[10]={0},path_name[100]={0},*html=NULL;
        sprintf(file_name,"%d",c);
        strcat(file_name,".txt");
        strcat(path_name,"/home/pardeep/search_engine/");
        strcat(path_name,file_name);
        FILE *file = fopen(path_name,"r");
        if(file)
        {
            struct stat st;
            stat(path_name,&st);
            int file_size=st.st_size;
						html=copy_content(file,file_size);
            read_file(file_size,html);
          //  free(html);
						//html=NULL;
        }
        else
        {
            printf("\n---end---\n");
            break;
        }
        c++;
    }
    print_list();
    put_in_file();
    do_next_work();
}
