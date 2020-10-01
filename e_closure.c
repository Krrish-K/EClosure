#include<stdio.h>
#include<stdlib.h>

struct node
{
    int st;
    struct node * link;
};

static int set[20],nostate,noalpha,s,notransition,c,r,buffer[20];
char alphabet[20];
static int e_closure[20][20]={0};
struct node *transition[20][20]={NULL};

void findclosure(int x,int sta)
{
    struct node *temp;
    int i;
    if (buffer[x])
    {
        return;
    }
    e_closure[sta][c++]=x;
    buffer[x]=1;
    if (alphabet[noalpha-1]=='E' && transition[x][noalpha-1]!=NULL)
    {
        temp=transition[x][noalpha-1];
        while (temp!=NULL)
        {
            findclosure(temp->st,sta);
            temp=temp->link;
        }
    }
}

int findalpha(char c)
{
    int i;
    for (i = 0; i < noalpha; i++)
    {
        if (alphabet[i]==c)
        {
            return i;
        }
    }
    return(-1);
}

void insert_trantbl(int r,char c,int s)
{
    int j;
    struct node *temp;
    j=findalpha(c);
    if(j==-1)
    {
        printf("\nError!!");
        exit(0);
    }
    temp=(struct node *)malloc(sizeof(struct node));
    temp->st=s;
    temp->link=transition[r][j];
    transition[r][j]=temp;
}

void print_e_closure(int i)
{
    int j;
    printf("{");
    for (j = 0; e_closure[i][j] != 0; j++)
    {
        printf("q%d,",e_closure[i][j]);
    }
    printf("}");
}

void main()
{
    int i,j,k,m,t,n;
    struct node *temp;
    printf("Enter the Number of Alphabets:");
    scanf("%d",&noalpha);
    getchar();
    printf("\nNOTE:- Use letter 'E' as epsilon");
    printf("\nNOTE:- 'E' must be last character, if present");
    printf("\nEnter the Alphabets:\n");
    for (i = 0; i < noalpha; i++)
    {
        alphabet[i]=getchar();
        getchar();
    }
    printf("\nEnter the Number of States:");
    scanf("%d",&nostate);
    printf("\nEnter Number of Transitions:");
    scanf("%d",&notransition);
    printf("\nNOTE:-Input Transitions in the form:State Alphabet State");
    printf("\nNOTE:-State numbers must be greater than Zero");
    printf("\nEnter the Transitions:\n");
    for (i = 0; i < notransition; i++)
    {
        scanf("%d %c %d",&r,&c,&s);
        insert_trantbl(r,c,s);
    }
    printf("\nE-Closure of States");
    printf("\n*******************");
    for (i = 1; i <= nostate; i++)
    {
        c=0;
        for (j = 0; j < 20; j++)
        {
            buffer[j]=0;
            e_closure[i][j]=0;
        }
        findclosure(i,i);
        printf("\nE-Closure(q%d)=",i);
        print_e_closure(i);
    }
}
