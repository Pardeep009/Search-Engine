#include <sys/types.h>
#include <sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"crowller.h"
//#include"list.h"
//#include "html.h"
#define BASE_URL "www.chitkara.edu.in"
#define DEPTH 5


/*
Function to test directory
#include <sys/types.h>
#include <sys/stat.h>

void testDir(char *dir)
{
  struct stat statbuf;
  if ( stat(dir, &statbuf) == -1 )
  {
    fprintf(stderr, "-----------------\n");
    fprintf(stderr, "Invalid directory\n");
    fprintf(stderr, "-----------------\n");
    exit(1);
  }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) )
  {
    fprintf(stderr, "-----------------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
    fprintf(stderr, "-----------------------------------------------------\n");
    exit(1);
  }

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
  {
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. It isn't writable\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
  }
}
Wget command to use with proxy
-------------------------------------------

wget -e
use_proxy=on -e
http_proxy=10.0.0.220:3128
http://www.uietkuk.org/
--proxy-user=user1
--proxy-password=user1
Function to fetch the web page
----------------------------------------
void getpage(char *url)
{
char urlbuffer[Url_Length+300]={0};
strcat(urlbuffer, "wget -e use_proxy=on -e
http_proxy=10.0.0.220:3128 -O ");

strcat(urlbuffer,"~/dirname/subdirectory/temp.txt ");

strcat(urlbuffer, url);

strcat(urlbuffer, " --proxy-user=user1 --proxy-password=user1");

system(urlbuffer);
}
Some Declarations for crawler
----------------------------------------------

#define HASH_SIZE 100

#define URL_LENGTH 1000

#define SEED_URL "http://www.chitkara.edu.in"

#define MAX_URL_PER_PAGE 1000

#define INTERVAL_TIME 10

#define CHECK_MALLOC(s) if ((s) == NULL) { \
printf("memory allocation failed in %s: line%d", _FILE, __LINE_); \
perror(":"); \
exit(-1); \
}

#define SET_MEM(start,size) memset(start,0,size)
//wget() for validating URL --without proxy--

if(!system("wget --spider http://chitkara.edu.in"))
printf("Valid URL");
else
printf("Invalid URL");
File handling functions to use
--------------------------------------

> fopen - for opening file in different modes.

> fgets(p,100,ptr); - Reads 100 characters pointed by ptr and store them in string p.

> fgetc(ptr)!=EOF - Reading the File up to end

> fprintf(ptr2,"%s",p);
Write the contents of p in the file pointed by ptr2.
To calculate file size & creating path of new file
-------------------------------------------------------------
struct stat st; //variable which will count length of file.
stat("temp.txt",&st); // temp.txt is the file where wget fetch the html
int file_size=st.st_size;

sprintf(itostring,"%d",file_no); //converts integer into string
char file[]="/temp"; //name of file.
char f[]=".txt";
strcat(p,path); //creating path using strcat in p.
strcat(p,file);
strcat(p,itostring);
strcat(p,f);
printf("PATH has been created\n");

void testDir(char *dir)
{
  struct stat statbuf;
  if ( stat(dir, &statbuf) == -1 )
  {
    fprintf(stderr, "-----------------\n");
    fprintf(stderr, "Invalid directory\n");
    fprintf(stderr, "-----------------\n");
    exit(1);
  }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) )
  {
    fprintf(stderr, "-----------------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
    fprintf(stderr, "-----------------------------------------------------\n");
    exit(1);
  }

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
  {
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. It isn't writable\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
  }
}

------------------------------------------
// FILE: html.c

// HTML parser utility implementation
// see html.h for detail usage


/*

*GetNextURL*
------------

Description: Given a HTML string buffer, the URL of the HTML,
and a position index, find the closest URL after the position
and copy the URL into the result buffer, which is also an input
argument. This function is the main component of the HTML parser.
This function is designed such that it is meant to be repeatedly
called toextract URLs from the HTML one at a time, starting from the
beginning of the HTML and terminating when the end of the HTML
is reached. The return value of this function is meant for the
repeated calls of this function; the real return value is the
third input argument, which is the result buffer, in which a
new URL will be written if one is found. This function can
handle normal absolute and relative URLs generally  found in
the <a href=""> tags; however, more extreme cases, like this
<a href="../../../a.txt">, are not currently being extracted.

Input: html_buffer, urlofthispage, result_buffer, current_position

Return: Position of the URL found

** Pseudo Code **

(1) IF (first call) THEN
      Remove white space characters from the page
    END
(2) Find the <a> or <A> html tags by scanning through the html text
(3) Keep going until we may have found a URL
(4) IF (It actually is NOT a URL, which has multiple possibilities) THEN
      Recursively call self from the next position
    END
(5) IF (It is an absolute URL) THEN
      Set result buffer to contain this URL
      Return the current position
    ELSE (It is an relative URL) THEN
      Produce the result URL by combining the relative URL with the urlofthispage
      Set result buffer to contain this URL
      Return the current position
    END
(7) Return -1 to signal completion

*****

*/
/*
int GetNextURL(char* html, char* urlofthispage, char* result, int pos)
{
  char c;
  int len, i, j;
  char* p1;  //!< pointer pointed to the start of a new-founded URL.
  char* p2;  //!< pointer pointed to the end of a new-founded URL.

  // NEW
  // Clean up \n chars
  if(pos == 0) {
    removeWhiteSpace(html);
  }
  // /NEW

  // Find the <a> <A> HTML tag.
  while (0 != (c = html[pos]))
  {
    if ((c=='<') &&
        ((html[pos+1] == 'a') || (html[pos+1] == 'A'))) {
      break;
    }
    pos++;
  }
  //! Find the URL it the HTML tag. They usually look like <a href="www.abc.com">
  //! We try to find the quote mark in order to find the URL inside the quote mark.
  if (c)
  {
    // check for equals first... some HTML tags don't have quotes...or use single quotes instead
    p1 = strchr(&(html[pos+1]), '=');

    if ((!p1) || (*(p1-1) == 'e') || ((p1 - html - pos) > 10))
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*(p1+1) == '\"' || *(p1+1) == '\'')
      p1++;

    p1++;

    p2 = strpbrk(p1, "\'\">");
    if (!p2)
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*p1 == '#')
    { // Why bother returning anything here....recursively keep going...

      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (!strncmp(p1, "mailto:",7))
      return GetNextURL(html, urlofthispage, result, pos+1);
    if (!strncmp(p1, "http", 4) || !strncmp(p1, "HTTP", 4))
    {
      //! Nice! The URL we found is in absolute path.
      strncpy(result, p1, (p2-p1));
      return  (int)(p2 - html + 1);
    } else {
      //! We find a URL. HTML is a terrible standard. So there are many ways to present a URL.
      if (p1[0] == '.') {
        //! Some URLs are like <a href="../../../a.txt"> I cannot handle this.
	// again...probably good to recursively keep going..
	// NEW

        return GetNextURL(html,urlofthispage,result,pos+1);
	// /NEW
      }
      if (p1[0] == '/') {
        //! this means the URL is the absolute path
        for (i = 7; i < strlen(urlofthispage); i++)
          if (urlofthispage[i] == '/')
            break;
        strcpy(result, urlofthispage);
        result[i] = 0;
        strncat(result, p1, (p2 - p1));
        return (int)(p2 - html + 1);
      } else {
        //! the URL is a absolute path.
        len = strlen(urlofthispage);
        for (i = (len - 1); i >= 0; i--)
          if (urlofthispage[i] == '/')
            break;
        for (j = (len - 1); j >= 0; j--)
          if (urlofthispage[j] == '.')
              break;
        if (i == (len -1)) {
          //! urlofthis page is like http://www.abc.com/
            strcpy(result, urlofthispage);
            result[i + 1] = 0;
            strncat(result, p1, p2 - p1);
            return (int)(p2 - html + 1);
        }
        if ((i <= 6)||(i > j)) {
          //! urlofthis page is like http://www.abc.com/~xyz
          //! or http://www.abc.com
          strcpy(result, urlofthispage);
          result[len] = '/';
          strncat(result, p1, p2 - p1);
          return (int)(p2 - html + 1);
        }
        strcpy(result, urlofthispage);
        result[i + 1] = 0;
        strncat(result, p1, p2 - p1);
        return (int)(p2 - html + 1);
      }
    }
  }
  return -1;
}

/*

*NormalizeWord*
---------------

Description: Make sure all the Roman letters in the URL are
of lower cases, for ease of carrying out string comparison in
the future when trying to decide if two URL are the same or not.
Basically a linear scan, starting from the beginning of the URL,
is performed. Whenever a capital letter character is encountered
(by checking its ASCII code value), it is replaced by the
corresponding lower case letter.

Input: input_url

** Pseudo Code **

(1) FOR (every character in the input string) DO
      IF (this character is a capital letter) DO
        Change this letter to lower case
      END
    DONE

*****

*/
/*
void NormalizeWord(char* word) {
  int i = 0;
  while (word[i]) {
      // NEW
    if (word[i] < 91 && word[i] > 64) // Bounded below so this funct. can run on all urls
      // /NEW
      word[i] += 32;
    i++;
  }
}

/*

*NormalizeURL*
--------------

Description: Normalize the input URL string and return its validity.
The normalization contains two major components: first, if the
URL ends with a trailing slash '/' character, this trailing slash
will be removed from the URL; and second, if the URL points to
a file (with an extension), then only certain file extensions are
accepted; currently, acceptable normal file extensions start with
.htm, .HTM, .php, or .jsp. A URL is valid if it is long enough and,
if pointing to a file, points to a file of acceptable format;
otherwise the URL is considered invalid and therefore will not
be added to the url_list for future processing.

Input: input_url

Output: validity of the input URL: 0 - invalid
                                   1 - valid

** Pseudo Code **

(1) Return error signal if input url is too short.
(2) IF (input url ends with '/') THEN
      Remove the '/'
    END
(3) Find the positions of the last occurrences of '/' and '.'
(4) IF (the '/' and '.' are positioned s.t. they indicate the url points to a file) THEN
      IF (the file extension starts with .htm or .HTM or .php or .jsp) THEN
        Do nothing...
      ELSE
        Return bad url signal
      END
    END
(5) Return good url signal

*****

*/
/*

int NormalizeURL(char* URL)
{
  int len = strlen(URL);
  if (len <= 1 )
    return 0;
  //! Normalize all URLs.
  if (URL[len - 1] == '/')
  {
    URL[len - 1] = 0;
    len--;
  }
  int i, j;
  len = strlen(URL);
  //! Safe check.
  if (len < 2)
    return 0;
  //! Locate the URL's suffix.
  for (i = len - 1; i >= 0; i--)
    if (URL[i] =='.')
      break;
  for (j = len - 1; j >= 0; j--)
    if (URL[j] =='/')
      break;
  //! We ignore other file types.
  //! So if a URL link is to a file that are not in the file type of the following
  //! one of four, then we will discard this URL, and it will not be in the URL list.
  if ((j >= 7) && (i > j) && ((i + 2) < len))
  {
    if ((!strncmp((URL + i), ".htm", 4))
        ||(!strncmp((URL + i), ".HTM", 4))
        ||(!strncmp((URL + i), ".php", 4))
        ||(!strncmp((URL + i), ".jsp", 4))
        )
    {
      len = len; // do nothing.
    }
    else
    {
      return 0; // bad type
    }
  }
  return 1;
}

/*

*removeWhiteSpace*
------------------

Description: Removes the white space characters from the input
string buffer that contains the html content. This function
basically scans through the entire html buffer content character
by character, and abandons any white space character it encounters.
The ASCII code of the characters are used to determine whether
a character is a white space or not; Characters with ASCII code
values below 32 are considered white space characters, and are
thus removed.

Input: string_buffer

** Pseudo Code **

(1) Create a target buffer one character than the input buffer, and clear it
(2) FOR (Every character in the input buffer) DO
      IF (the current character is not a while space character) THEN
        Append it to the end of the target buffer
      END
    DONE
(3) Overwrite the input buffer with the target buffer
(4) Release targer buffer

*****

*/

//-----------------------//

void shift_page(char *url,int depth)
{
        static int c=1;
        char file_name[20]={0};
        char open[100]={0};
        char ch[15]={0};
   //     itoa(c , ch , 10);
        char ch1;
        sprintf(ch, "%d" , c);
        strcat(file_name,ch);
        strcat(file_name,".txt");
        strcat(open,"/home/pardeep/search_engine/");
        strcat(open,file_name);
        FILE *temp=fopen("/home/pardeep/search_engine/temp.txt","r");
        FILE *new=fopen(open,"w");
        printf("\n----%s----\n",file_name);
        fprintf(new,"%s\n",url);
        fprintf(new,"%d\n",depth);
        while((ch1=fgetc(temp))!=EOF)
        {
                putc(ch1,new);
        }
        copy_content(open,url,depth);               //   after that in crowller1.h file
        fclose(temp);
        c++;
     // fclose(new);
}

//-------------------//

void getpage(char *url,char *dir,int depth)
{
          char urlbuffer[400]={0};
	        strcat(urlbuffer, "wget -O ");
	        strcat(urlbuffer, dir);
	        strcat(urlbuffer, "/temp.txt ");
	        strcat(urlbuffer, url);
	        system(urlbuffer);
	        shift_page(url,depth);
}

//--------------------//

void check_valid(char *argv1)
{
	char url[300]="wget --spider ";
	strcat(url,argv1);
	if(!system(url))
	printf("VALID URL\n");
	else
	{
		printf("INVALID URL\n");
		exit(1);
	}
}

//---------------------//

void check_url(char argv[])
{
	int i=0;
	char seed_url[strlen(argv)+5];
	while(argv[i]!='/'&&argv[i]!='\0')
	{
		seed_url[i]=argv[i];
		i++;
	}
	seed_url[i]='\0';
	if(strcmp(seed_url,BASE_URL)==0)
	{
		printf("CORRECT BASE URL\n");
 	}
	else
	{
		printf("INCORRECT BASE URL");
		exit(0);
	}
}

//---------------------//

void check_depth(char argv[])
{
	int i=atoi(argv);
	if(i<=DEPTH && i>=1)
	{
		printf("CORRECT DEPTH\n");
	}
	else
	{
		printf("INCORRECT DEPTH");
		exit(0);
	}
}

//---------------------//

void check_dir(char *dir)
{
  	struct stat statbuf;
  	if ( stat(dir, &statbuf) == -1 )
  	{
    		printf("-----------------\n");
    		printf("Invalid directory\n");
    		printf("-----------------\n");
    		exit(1);
 	}

  	//Both check if there's a directory and if it's writable
  	if ( !S_ISDIR(statbuf.st_mode) )
  	{
    		printf("-----------------------------------------------------\n");
    		printf("Invalid directory entry. Your input isn't a directory\n");
    		printf("-----------------------------------------------------\n");
    	exit(1);
  	}

  	if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
  	{
    		printf("------------------------------------------\n");
    		printf("Invalid directory entry. It isn't writable\n");
    		printf("------------------------------------------\n");
    		exit(1);
  	}
}

//---------------------//

void check_validity(int argc,char *argv[])
{
        if(argc!=4)
      	{
      		printf("less values");
      	}
      	check_valid(argv[1]);        // for validating URL --without proxy--
      	check_url(argv[1]);          // for checking valid base url
      	check_depth(argv[2]);  	     // for checking depth
      	check_dir(argv[3]);          // for checking directory
}

//----------------------//

int main(int argc,char *argv[])
{
        check_validity(argc,argv);
        char c;
        initialise();
        printf("previous(p) data or new(n) data \n");
        scanf("%c",&c);
        if(c=='p')
        {
              retrieve_links_in_list();
        }
        else
        {
	        getpage(argv[1],argv[3],1);
        }
        int depth=1;
        char *url=NULL;
        while(depth<=atoi(argv[2]))
        {
                while((url=get_next_url(depth))!=NULL)
                {
                        getpage(url,argv[3],depth);
                }
                depth++;
        }
        print_list(head);
	return 1;
}
