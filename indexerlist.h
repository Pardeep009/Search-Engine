
struct page
{
    char page_url[200];
    int page_count;
    struct page * page_next;
    struct page * page_prev;
};

struct word
{
    char word_name[30];
    struct page * head_page;
    struct page * tail_page;
    struct word * word_next;
    struct word * word_prev;
    int word_key;
    int word_count;
};

struct Hash
{
    struct word * first;
    struct word * last;
};

struct Hash hash[30];

struct word *head=NULL,*last=NULL;

void inititliase()
{
    int i;
    for(i=0;i<30;i++)
    {
        hash[i].first=NULL;
        hash[i].last=NULL;
    }
}

struct page *create_a_page_node(char url[])
{
    struct page *pg = (struct page*)calloc(1,sizeof(struct page));
    strcpy(pg->page_url,url);
    pg->page_count = 1;
    pg->page_next = NULL;
    return pg;
}

void first_node(struct word *temp,int key,char url[])
{
    struct page *pg=NULL;
    hash[key].first = temp;
    hash[key].last = temp;
    pg=create_a_page_node(url);
    pg->page_prev = NULL;
    temp->head_page = pg;
    temp->tail_page = pg;
    temp->word_next = NULL;
    temp->word_count = 1;
    last=temp;
}

void put_in_file()
{
    struct word *temp=head;
    struct page *tmp=NULL;
    FILE *file=fopen("/home/pardeep/search_engine/indexerfile.txt","w");
    while(temp)
    {
        fprintf(file,"%s %d\n",temp->word_name,temp->word_count);
        tmp=temp->head_page;
        while(tmp)
        {
            fprintf(file,"%s %d\n",tmp->page_url,tmp->page_count);
            tmp=tmp->page_next;
        }
        fprintf(file,"\n");
        temp=temp->word_next;
    }
}

void put_in_list(char w[],char url[])
{
    struct word *temp=(struct word*)calloc(1,sizeof(struct word));
    struct page *pg=NULL;
    strcpy(temp->word_name,w);
    int key=strlen(w);
    temp->word_key=key;
    if(head==NULL)
    {
        head = temp;
        first_node(temp,key,url);
        temp->word_prev = NULL;
    }
    else
    {
        if(hash[key].first==NULL)
        {
            last->word_next = temp;
            temp->word_prev = last;
            first_node(temp,key,url);
        }
        else
        {
            if(strcmp(hash[key].first->word_name,temp->word_name)==0)
            {
                hash[key].first->word_count+=1;
                if(strcmp(hash[key].first->tail_page->page_url,url)==0)
                    hash[key].first->tail_page->page_count+=1;
                else
                {
                    pg = create_a_page_node(url);
                    pg->page_prev = hash[key].first->tail_page;
                    hash[key].first->tail_page->page_next = pg;
                    hash[key].first->tail_page = pg;
                }

                free(temp);
                return;
            }
            if(strcmp(hash[key].last->word_name,temp->word_name)==0)
            {
                hash[key].last->word_count+=1;
                if(strcmp(hash[key].last->tail_page->page_url,url)==0)
                    hash[key].last->tail_page->page_count+=1;
                else
                {
                    pg=create_a_page_node(url);
                    pg->page_prev = hash[key].last->tail_page;
                    hash[key].last->tail_page->page_next = pg;
                    hash[key].last->tail_page = pg;
                }
                free(temp);
                return;
            }
            struct word *trav = hash[key].first;
            while(trav&&trav->word_key==key)
            {
                if(strcmp(trav->word_name,temp->word_name)==0)
                {
                    trav->word_count+=1;
                    if(strcmp(trav->tail_page->page_url,url)==0)
                        trav->tail_page->page_count+=1;
                    else
                    {
                        pg=create_a_page_node(url);
                        pg->page_prev = hash[key].last->tail_page;
                        trav->tail_page->page_next = pg;
                        trav->tail_page = pg;
                    }
                    free(temp);
                    return;
                }
                trav=trav->word_next;
            }
            if(trav==NULL)
            {
                last=temp;
                temp->word_next = NULL;
                hash[key].last->word_next = temp;
                temp->word_prev = hash[key].last;
            }
            else
            {
                temp->word_next = trav;
                temp->word_prev = trav->word_prev;
                trav->word_prev = temp;
                hash[key].last->word_next = temp;
            }
            hash[key].last=temp;
            temp->word_count = 1;
            temp->head_page = NULL;
            temp->tail_page = NULL;
            pg=create_a_page_node(url);
            pg->page_prev = NULL;
            temp->head_page = pg;
            temp->tail_page = pg;
        }
    }
}

void print_list()
{
    struct word *temp=head;
    struct page *tmp=NULL;
    while(temp)
    {
        printf("%s %d \n",temp->word_name,temp->word_count);
        tmp=temp->head_page;
        while(tmp)
        {
            printf("%s %d \n",tmp->page_url,tmp->page_count);
            tmp=tmp->page_next;
        }
        printf("\n-----------\n");
        temp=temp->word_next;
    }
}

/*              query work now               */

int c=0,m=1;

struct url
{
    char url_url[200];
    int url_rank;
//    int url_flag;
    struct url *url_next;
    struct url *url_prev;
};

struct url *url_head=NULL,*url_last=NULL;

struct page *find_query(char query[])
{
    int key = strlen(query);
    if(hash[key].first==NULL)
    return NULL;
    else
    {
        struct word *temp=hash[key].first;
        while(temp&&temp->word_key == key)
        {
            if(strcmp(temp->word_name,query)==0)
            return temp->head_page;
            temp = temp->word_next;
        }
    }
    return NULL;
}


int url_visited(char page_url[])
{
    if(url_head==NULL)
    return 0;
    struct url *temp=url_head;
    while(temp)
    {
        if(strcmp(temp->url_url,page_url)==0)
        return 1;
        temp = temp->url_next;
    }
    return 0;
}

void find_occurences(char query[][30],char page_url[],int s,int e)
{
    int i=s;
    for(i=s;i<e;i++)
    {
        struct page *temp = find_query(query[i]);
        while(temp)
        {
            if(strcmp(temp->page_url,page_url)==0)
            {
                c = c + temp->page_count;
                m++;
                break;
            }
            temp = temp->page_next;
        }
    }
}

void put_url_in_list(char url[])
{
    int f = c*m;
    struct url *temp=(struct url*)calloc(1,sizeof(struct url));
    strcpy(temp->url_url,url);
    temp->url_rank = f;
    if(url_head==NULL)
    {
        temp->url_prev = NULL;
        temp->url_next = NULL;
        url_head = temp;
        url_last = temp;
    }
    else
    {
        if(url_head->url_rank<=f)
        {
            temp->url_prev = NULL;
            temp->url_next = url_head;
            url_head->url_prev = temp;
            url_head = temp;
            return;
        }
        struct url *trav = url_head,*prev=url_head;
        while(trav)
          {
                if(trav->url_rank<=f)
                {
                    temp->url_next = trav->url_prev->url_next;
                    trav->url_prev->url_next = temp;
                    temp->url_prev = trav->url_prev;
                    trav->url_prev = temp;
                    return;
                }
                prev=trav;
               trav = trav->url_next;
          }
          temp->url_next = NULL;
          temp->url_prev = prev;
          prev->url_next = temp;
    }
}

void print_url_list()
{
    struct url* temp = url_head;
    while(temp)
    {
        printf("%s rank = %d \n",temp->url_url,temp->url_rank);
        temp = temp->url_next;
    }
}

void rank_query(char query[][30],int l)
{
//    printf("In rank_query\n");
    int i;
    for(i=0;i<l;i++)
    {
        struct page *temp = find_query(query[i]);
    //    printf("%s result\n",query[i]);
        while(temp)
        {
        //    printf("url = %s url_count = %d\n",temp->page_url,temp->page_count);
            c=0;
            m=1;
            if(!url_visited(temp->page_url))
            {
                c = c + temp->page_count;
                find_occurences(query,temp->page_url,i+1,l);
                put_url_in_list(temp->page_url);
            }
            temp = temp->page_next;
        }
    }
    print_url_list();
}
