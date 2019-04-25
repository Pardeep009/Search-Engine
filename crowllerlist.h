
struct Link
{
        int Link_key;
        int Link_flag;
        char *Link_url;
//      struct Link *node_prev;
        struct Link *Link_next;
        int Link_depth;
};

struct Hash
{
        struct Link* first;
        struct Link* last;
        int count;
};

struct Hash hash[50];

struct Link *head=NULL,*last=NULL;

void initialise()
{
        int i;
        for(i=0;i<50;i++)
        {
                hash[i].first=NULL;
                hash[i].last=NULL;
                hash[i].count=0;
        }
}

//---------------------//

int generate_key(char *url)
{
        int i,l=strlen(url),key=0;
        //return strlen(url)%50;
        for(i=0;i<l;i++)
        {
            key+=(int)(url[i]);
        }
        return key%50;
}

//----------------------//

void print_list(struct Link *head)
{
    struct Link *temp=head;
    while(temp!=NULL)
    {
        printf("key = %d Link = %s depth = %d flag= %d\n",temp->Link_key,temp->Link_url,temp->Link_depth,temp->Link_flag);
        temp=temp->Link_next;
    }
}

//---------------------//

void save_links_in_file(struct Link* head)
{
        FILE *ptr=fopen("/home/pardeep/search_engine/links.txt","w");
        struct Link *temp=head;
        while(temp!=NULL)
        {
                fprintf(ptr,"%s ",temp->Link_url);
                fprintf(ptr,"%d ",temp->Link_key);
                fprintf(ptr,"%d ",temp->Link_depth);
                fprintf(ptr,"%d\n",temp->Link_flag);
                temp=temp->Link_next;
        }
}

//---------------------//

void retrieve_links_in_list()
{
        initialise();
        head=NULL;
        FILE *ptr=fopen("/home/pardeep/search_engine/links.txt","r");
        char ch;
        char c[150]={0};
        char url[125]={0};
        char *urlss=NULL;
        int i=0,j=0,k=0;
        struct Link *trav;
        while((ch=fgetc(ptr))!=EOF)
        {
                if(ch=='\n')
                {
                        c[i]='\0';
                        i=0;
                        struct Link *temp=(struct Link*)calloc(1,sizeof(struct Link));
                        j=0;
                        k=0;
                        while(c[k]!=' ')
                        {
                                url[j]=c[k];
                                j++;
                                k++;
                        }
                        url[j]='\0';
                        urlss=(char*)calloc(1,100);
                        strcpy(urlss,url);
                 //       printf("\n%s\n",url);
                        temp->Link_key=generate_key(url);         // put key
                        int key=temp->Link_key;
                        temp->Link_url=urlss;
                    //   strcpy(temp->Link_url,url);                       // put url
                        k++;
                        j=0;
                        while(c[k]!=' ')
                        {
                                k++;
                        }
                        k++;
                        while(c[k]!=' ')
                        {
                                url[j]=c[k];
                                j++;
                                k++;
                        }
                        url[j]='\0';
                        temp->Link_depth=atoi(url);                // put depth
                        j=0;
                        k++;
                        while(c[k]!='\0')
                        {
                                url[j]=c[k];
                                j++;
                                k++;
                        }
                        url[j]='\0';
                        temp->Link_flag=atoi(url);                   // put flag
                        if(head==NULL)
                        {       temp->Link_next=NULL;
                                head=temp;                      //   temp->Link_flag=1;
                                last=temp;
                                hash[key].first=temp;
                                hash[key].last=temp;
                                hash[key].count=1;
                                continue;
                        }
                        else
                        {
                                if(hash[key].first==NULL)
                                {
                                        last->Link_next=temp;
                                        temp->Link_next=NULL;
                                        last=temp;
                                        hash[key].first=temp;
                                        hash[key].last=temp;
                                        hash[key].count=1;
                                }
                                else
                                {
                                        trav=hash[key].first;
                                        if((strcmp(hash[key].first->Link_url,temp->Link_url)==0)||(strcmp(hash[key].last->Link_url,temp->Link_url)==0))
                                        {
                                                free(temp);
                                                free(urlss);
                                                continue;
                                        }
                                int f=0;
                                while(trav->Link_next!=NULL&&trav->Link_next->Link_key==key)
                                {
                                        if(strcmp(trav->Link_url,temp->Link_url)==0)
                                        {
                                                free(temp);
                                                f=1;
                                                break;
                                        }
                                        trav=trav->Link_next;
                                }
                                if(f)
                                continue;
                                if(trav->Link_next==NULL)
                                last=temp;
                                temp->Link_next=trav->Link_next;
                                trav->Link_next=temp;
                                hash[key].last=temp;
                                hash[key].count++;
                        }
                        }
                        c[0]='\0';
                }
                else
                {
                        c[i++]=ch;
                }
        }
        print_list(head);
}

//---------------------//

void put_links_in_list(char **result,int l,int depth)
{
        int i;
        struct Link *temp,*trav;
        for(i=0;i<l;i++)
        {
                temp=(struct Link*)calloc(1,sizeof(struct Link));
                temp->Link_key=generate_key(result[i]);
                int key=temp->Link_key;
                temp->Link_url=result[i];
                temp->Link_depth=depth+1;
                if(head==NULL)
                {       temp->Link_next=NULL;
                        temp->Link_flag=1;
                        temp->Link_depth=depth;
                        head=temp;                      //   temp->Link_flag=1;
                        last=temp;
                        hash[key].first=temp;
                        hash[key].last=temp;
                        hash[key].count=1;
                        continue;
                }
                else
                {
                        if(hash[key].first==NULL)
                        {
                               last->Link_next=temp;
                               temp->Link_next=NULL;
                               temp->Link_flag=0;
                               last=temp;
                               hash[key].first=temp;
                               hash[key].last=temp;
                               hash[key].count=1;
                        }
                        else
                        {
                            trav=hash[key].first;
                            if((strcmp(hash[key].first->Link_url,temp->Link_url)==0)||(strcmp(hash[key].last->Link_url,temp->Link_url)==0))
                                {
                                    free(temp);
                                    continue;
                                }
                            int f=0;
                            while(trav->Link_next!=NULL&&trav->Link_next->Link_key==key)
                            {
                                if(strcmp(trav->Link_url,temp->Link_url)==0)
                                {
                                    free(temp);
                                    f=1;
                                    break;
                                }
                                trav=trav->Link_next;
                            }
                            if(f)
                            continue;
                            if(trav->Link_next==NULL)
                            last=temp;
                            temp->Link_flag=0;
                            temp->Link_next=trav->Link_next;
                            trav->Link_next=temp;
                            hash[key].last=temp;
                            hash[key].count++;
                        }
                }
        }
        save_links_in_file(head);
}

//----------------------//

char* get_next_url(int depth)
{
        struct Link *temp=head;
        while(temp!=NULL)
        {
                if(temp->Link_flag==0&&temp->Link_depth==depth)
                {
                        temp->Link_flag=1;
                        return temp->Link_url;
                }
                temp=temp->Link_next;
        }
        return NULL;
}

//----------------------//
