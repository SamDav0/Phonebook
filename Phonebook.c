#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 10
#define name_len 100
#define number_len 30
struct mutual
{
    char name[name_len];
    char number[number_len];
    int frequency;
    struct mutual *next;
};
struct contacts
{
    char name[name_len];
    char number[number_len];
    struct contacts *link;
};
struct phonebook
{
    char Phone_name[name_len];
    char Phone_number[number_len];
    struct contacts *next;
};

int top=-1,rear=-1;
struct phonebook *phone[max];
struct mutual *suggest=NULL;
//int key=-1;
int flag=1;
//int used[max];

int isFull()
{
    return (rear==max-1);
}
int check()
{
    char temp[name_len];
    printf("Enter Phone name\n");
    fflush(stdin);
    scanf("%[^\n]s",temp);
    fflush(stdin);
    int i=top,found=0,pos;
    if(i!=-1)
    {
        while(i<=rear)
        {
            if(strcmp(temp,phone[i]->Phone_name)==0)
            {
                found=1;
                pos=i;
            }
        i++;
        }
    }
    if(found==0)
        return -1;
    else
        return pos;
}
struct contacts *create_node(char *copy_name,char *copy_number)
{
    struct contacts *temp=malloc(sizeof(struct contacts));
    strcpy(temp->name,copy_name);
    strcpy(temp->number,copy_number);
    temp->link=NULL;
    return temp;
}
struct phonebook *create_Node_Phone()
{
    struct phonebook *temp=malloc(sizeof(struct phonebook));
    temp->next=NULL;
    return temp;
}
struct mutual *create_node_mutual()
{
    struct mutual *temp=malloc(sizeof(struct mutual));
    temp->next=NULL;
    temp->frequency=1;
    return temp;
}
struct contacts *create_Node_Contacts()
{
    struct contacts *temp=malloc(sizeof(struct contacts));
    temp->link=NULL;
    return temp;
}
void swap(struct contacts *a, struct contacts *b) {
    char tempName[20];
    char tempNumber[20];
    
    strcpy(tempName, a->name);
    strcpy(tempNumber, a->number);
    
    strcpy(a->name, b->name);
    strcpy(a->number, b->number);
    
    strcpy(b->name, tempName);
    strcpy(b->number, tempNumber);
}

void sortContacts(struct contacts *start) 
{
    int swapped;
    struct contacts *ptr1;
    struct contacts *lptr = NULL;
    if (start == NULL)
        return;
    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->link != lptr) {
            if (strcasecmp(ptr1->name, ptr1->link->name) > 0) {
                swap(ptr1, ptr1->link);
                swapped = 1;
            }
            ptr1 = ptr1->link;
        }
        lptr = ptr1;
    } while (swapped);
}
void sortAll()
{
    for(int i=0;i<=rear;i++)
    {
        struct contacts *temp=phone[i]->next;
        sortContacts(temp);
    }
}
void swapf(struct mutual *a, struct mutual *b) 
{
    char tempName[20];
    char tempNumber[20];
    int tempFreq;

    strcpy(tempName, a->name);
    strcpy(tempNumber, a->number);
    tempFreq = a->frequency;

    strcpy(a->name, b->name);
    strcpy(a->number, b->number);
    a->frequency = b->frequency;

    strcpy(b->name, tempName);
    strcpy(b->number, tempNumber);
    b->frequency = tempFreq;
}

void sortMutualByFrequency(struct mutual *start)
{
    int swapped;
    struct mutual *ptr1;
    struct mutual *lptr = NULL;

    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->frequency < ptr1->next->frequency) 
            {
                swapf(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void makeMutual()
{
    while(suggest!=NULL)
    {
        struct mutual *temp=suggest;
        suggest=suggest->next;
        free(temp);
    }
    struct contacts *traverse=phone[rear]->next;
    if(traverse!=NULL)
    {
        flag=0;
        suggest=malloc(sizeof(struct mutual));
        struct mutual *temp2=suggest;
        while(traverse!=NULL)
        {
            struct mutual *temp=create_node_mutual();
            strcpy(temp->name,traverse->name);
            strcpy(temp->number,traverse->number);
            temp2->next=temp;
            traverse=traverse->link;
            temp2=temp2->next;
        }
    }
}
void getMutual2(struct contacts *traverse)
{
    if(suggest!=NULL)
    {
    struct mutual *temp=suggest->next;
    struct mutual *prev;
    int found=0;
    while(temp!=NULL)
    {
        if(strcmp(temp->number,traverse->number)==0)
        {
            temp->frequency=temp->frequency+1;
            found=1;
        }
        prev=temp;
        temp=temp->next;
    }
    if(found==0)
    {
        prev->next=create_node_mutual();
        strcpy(prev->next->name,traverse->name);
        strcpy(prev->next->number,traverse->number);
    }
    }
}
void deleteMutual(int index)
{
    struct contacts *traverse=phone[index]->next;
    struct mutual *temp;
    while(traverse!=NULL)
    {
        temp=suggest->next;
        while(temp!=NULL)
        {
            if(strcmp(temp->number,traverse->number)==0)
                temp->frequency=temp->frequency-1;
            temp=temp->next;
        }
        traverse=traverse->link;
    }
}
void deleteMutual2(struct contacts *traverse)
{
    struct mutual *temp=suggest->next;
    while(temp!=NULL)
    {
        if(strcmp(temp->number,traverse->number)==0)
            temp->frequency=temp->frequency-1;
        temp=temp->next;
    }
}
void suggestContacts()
{
    if(suggest!=NULL)
    {
        printf("\n");
        printf("Suggested Contacts:\n");
        struct mutual *temp=suggest->next;
        int nice=1;
        while(temp!=NULL)
        {
            if(temp->frequency>=2)
            {
                if(nice<=5)
                {
                    printf("%s : %s     ",temp->name,temp->number);
                    nice++;
                }
                else
                {
                    nice=1;
                    printf("\n%s : %s     ",temp->name,temp->number);
                }
            }
            temp=temp->next;
        }
        printf("\n\n");
    }
}
void addNumberP()
{
    int wish=1;
    while(wish)
    {
        struct contacts *temp=create_Node_Contacts();
        fflush(stdin);
        printf("Enter contact's name and number\n");
        scanf("%[^\n]s",temp->name);
        fflush(stdin);
        scanf("%s",temp->number);
        fflush(stdin);
        if(flag==0)
            getMutual2(temp);
        if(phone[rear]->next==NULL)
            phone[rear]->next=temp;
        else
        {
            temp->link=phone[rear]->next;
            phone[rear]->next=temp;
        }
        printf("\n\nPress 1 to continue 0 to exit\n");
        scanf("%d",&wish);
    }
}
void copy(int index)
{
    if(top==rear)
        printf("No reference phone to copy from\n");
    else
    {
        int pos=check();
        if(pos==-1)
            printf("Phone entered is not found\n");
        else
        {
            if(index==pos)
                printf("Cannot copy from same phone\n");
            else
            {
                int input;
                printf("Enter 1 to keep the contacts on the phone or Enter 0 to erase the contacts from the phone, and then add\n");
                scanf("%d",&input);
                struct contacts *traverse=phone[index]->next;
                if(input==0)
                {
                    deleteMutual(index);
                    while(traverse!=NULL)
                    {
                        struct contacts *delete2=traverse;
                        traverse=traverse->link;
                        free(delete2);
                    }
                    struct contacts *copy1=phone[pos]->next;
                    if(copy1==NULL)
                        printf("No contacts to copy from phone\n");
                    else
                    {
                        struct contacts *temp=create_Node_Contacts();
                        strcpy(temp->name,copy1->name);
                        strcpy(temp->number,copy1->number);
                        phone[index]->next=temp;
                        getMutual2(temp);
                        struct contacts *copy2=phone[index]->next;
                        copy1=copy1->link;
                        while(copy1!=NULL)
                        {
                            temp=create_Node_Contacts();
                            strcpy(temp->name,copy1->name);
                            strcpy(temp->number,copy1->number);
                            getMutual2(temp);
                            copy2->link=temp;
                            copy2=copy2->link;
                            copy1=copy1->link;
                        }
                        /*used[index]=0;
                        getMutual();*/
                    }
                    
                }
                else
                {
                    struct contacts *traverse2=NULL;
                    while(traverse!=NULL)
                    {
                        traverse2=traverse;
                        traverse=traverse->link;
                    }
                    struct contacts *copy1=phone[pos]->next;
                    if(copy1==NULL)
                        printf("No Phone numbers to copy\n");
                    else
                    {
                        struct contacts *temp;
                        if(traverse2==NULL)
                        {
                            temp=create_Node_Contacts();
                            strcpy(temp->name,copy1->name);
                            strcpy(temp->number,copy1->number);
                            phone[index]->next=temp;
                            traverse2=phone[index]->next;
                            copy1=copy1->link;
                            getMutual2(temp);
                        }
                        while(copy1!=NULL)
                        {
                            temp=create_Node_Contacts();
                            strcpy(temp->name,copy1->name);
                            strcpy(temp->number,copy1->number);
                            traverse2->link=temp;
                            traverse2=traverse2->link;
                            copy1=copy1->link;
                            getMutual2(temp);
                        }
                    }  
                }
            }
        } 
    }
}
void addPhone()
{
    if(isFull())
        printf("Phonebook is full\n");
    else
    {
        int wish;
        if(top==-1)
            top=rear=0;
        else
            rear++;
        phone[rear]=create_Node_Phone();
        fflush(stdin);
        printf("\n\nEnter name of phone\n");
        fflush(stdin);
        scanf("%[^\n]s",phone[rear]->Phone_name);
        fflush(stdin);
        printf("Enter your phone number\n");
        scanf("%[^\n]s",phone[rear]->Phone_number);
        fflush(stdin);
        if(rear>=2)
            suggestContacts();
        printf("\nPhone added\nPress 1 to add number\nPress 2 to copy another phone's contacts\nPress 3 to exit\n");
        scanf("%d",&wish);
        if(wish==1)
            addNumberP();
        else if(wish==2)
            copy(rear);
        if(flag)
        {
            makeMutual();
        }
    }
}
void addNumber()
{
    int pos=check();
    if(pos==-1)
        printf("Phone not found\n");
    else
    {
        int input;
        printf("Enter 1 to add numbers\t\tEnter 2 to copy from another phone\n");
        scanf("%d",&input);
        if(input==1)
        {
            struct contacts *copy=NULL;
            struct contacts *traverse=phone[pos]->next;
            while(traverse!=NULL)
            {
                copy=traverse;
                traverse=traverse->link;
            }
            int wish=1;
            while(wish)
            {
                struct contacts *temp=create_Node_Contacts();
                printf("Enter contact name and number:\n");
                fflush(stdin);
                scanf("%[^\n]s",temp->name);
                fflush(stdin);
                scanf("%[^\n]s",temp->number);
                fflush(stdin);
                printf("Enter 1 to continue and 0 to exit\n");
                scanf("%d",&wish);
                getMutual2(temp);
                if(copy==NULL)
                {
                    phone[pos]->next=temp;
                    copy=temp;
                }
                else
                {
                    copy->link=temp;
                    copy=copy->link;
                }
            }
        }
        else if(input==2)
            copy(pos);     
    }
}
void deletePhone_move(int pos)
{
        deleteMutual(pos);
        struct contacts *temp=phone[pos]->next;
        while(temp!=NULL)
        {
            struct contacts *traverse=temp;
            temp=temp->link;
            free(traverse);
        }
        free(phone[pos]);
        for(;pos<rear;pos++)
            phone[pos]=phone[pos+1];
        rear--;
}
void deletePhone()
{
    int pos=check();
    if(pos==-1)
        printf("Phone not found");
    else
    {
        if(rear==-1)
            printf("Phonebook is empty\n");
        else
        {
            deleteMutual(pos);
            struct contacts *temp=phone[pos]->next;
            while(temp!=NULL)
            {
                struct contacts *traverse=temp;
                temp=temp->link;
                free(traverse);
            }
            free(phone[pos]);
            for(;pos<rear;pos++)
                phone[pos]=phone[pos+1];
            rear--;
        }
        if(rear==-1)
            flag=1;
    }
}
void deleteNumber()
{
    char str[20];
    int pos=check();
    if(pos==-1)
        printf("Phone not found\n");
    else if(rear==-1)
        printf("Phonebook Empty\n");
    else
    {
        struct contacts *temp=phone[pos]->next;
        int input;
        printf("Enter 1 to delete specific contacts\t\tEnter 2 to erase all contacts\n");
        scanf("%d",&input);
        if(input==1)
        {
            int wish=1;
            struct contacts *traverse=NULL;
            while(wish)
            {
                printf("Enter contact name or number\n");
                fflush(stdin);
                scanf("%[^\n]s",str);
                fflush(stdin);
                if(temp==NULL)
                    printf("Phone has no contacts\n");
                else
                {
                    while(temp!=NULL)
                    {
                        if(strcmp(str,temp->name)==0 || strcmp(str,temp->number)==0)
                        {
                            deleteMutual2(temp);
                            if(phone[pos]->next==temp)
                            {
                                phone[pos]->next=temp->link;
                                free(temp);
                            }
                            else if(temp->link==NULL)
                            {
                                traverse->link=NULL;
                                free(temp);
                            }
                            else
                            {
                                traverse->link=temp->link;
                                free(temp);                            
                            }
                        }
                        traverse=temp;
                        temp=temp->link;
                    }
                }
                printf("Enter 1 to continue and 0 to exit\n");
                scanf("%d",&wish);
            }
        }
        else if(input==2)
        {
            if(temp==NULL)
                printf("Phone has no contacts\n");
            else 
            {
                while(temp!=NULL)
                {
                    struct contacts *traverse=temp;
                    temp=temp->link;
                    free(traverse);
                }
                deleteMutual(pos);
            }
        }
    }
}
void search()
{
    char search_name[20];
    printf("Enter the contact name to be searched\n");
    fflush(stdin);
    scanf("%[^\n]s", search_name);
    fflush(stdin);
    for (int i = 0; i < max; i++)
    {
        struct contacts* traverse = phone[i]->next;
        while(traverse!=NULL)
        {
            if (strcmp(traverse->name,search_name)==0)                                          //check with the name. If name not same then move to next link
            {
                printf("\nContact Name belongs to phone:%s\n",phone[i]->Phone_name);
                printf("Contact number: %s\n", traverse->number);
                return;
            }
            traverse = traverse->link;
        }
    }
    printf("Name not in contacts");
}
void copy_move(int dest,int src)
{
    int input;
    printf("Enter 1 to keep the contacts on the phone or Enter 0 to erase the contacts from the phone, and then add\n");
    scanf("%d",&input);
    struct contacts *traverse=phone[dest]->next; 
    if(input==0)
    {
        deleteMutual(dest);
        while(traverse!=NULL)
        {
            struct contacts *delete2=traverse;
            traverse=traverse->link;
            free(delete2);
        }
            struct contacts *copy1=phone[src]->next;
            if(copy1==NULL)
                printf("No contacts to copy from phone\n");
            else
            {
                struct contacts *temp=create_Node_Contacts();
                strcpy(temp->name,copy1->name);
                strcpy(temp->number,copy1->number);
                phone[dest]->next=temp;
                getMutual2(temp);
                struct contacts *copy2=phone[dest]->next;
                copy1=copy1->link;
                while(copy1!=NULL)
                {
                    temp=create_Node_Contacts();
                    strcpy(temp->name,copy1->name);
                    strcpy(temp->number,copy1->number);
                    getMutual2(temp);
                    copy2->link=temp;
                    copy2=copy2->link;
                    copy1=copy1->link;
                }
            }                  
    }
    else
    {
        struct contacts *traverse2=NULL;
        while(traverse!=NULL)
        {
            traverse2=traverse;
            traverse=traverse->link;
        }
        struct contacts *copy1=phone[src]->next;
        if(copy1==NULL)
            printf("No Phone numbers to copy\n");
        else
        {
            struct contacts *temp;
            if(traverse2==NULL)
            {
                temp=create_Node_Contacts();
                strcpy(temp->name,copy1->name);
                strcpy(temp->number,copy1->number);
                phone[dest]->next=temp;
                traverse2=phone[dest]->next;
                copy1=copy1->link;
                getMutual2(temp);
            }
            while(copy1!=NULL)
            {
                temp=create_Node_Contacts();
                strcpy(temp->name,copy1->name);
                strcpy(temp->number,copy1->number);
                traverse2->link=temp;
                traverse2=traverse2->link;
                copy1=copy1->link;
                getMutual2(temp);
            }
        }     
    }
}
void move()
{
    printf("Enter Phone name to be moved\n");
    char temp[name_len];
    fflush(stdin);
    scanf("%[^\n]s",temp);
    fflush(stdin);
    int i=top,pos,found=0;
    if(i!=-1)
    {
        while(i<=rear)
        {
            if(strcmp(temp,phone[i]->Phone_name)==0)
            {
                pos=i;
                found=1;
                break;
            }
            i++;
        }
    }
    else
        return;
    if(found==0)
        printf("Phone entered is not found\n");
    else
    {
        int move_choice;
        printf("Enter 1 to create a phone and then move to\n");
        printf("Enter 2 to move to existing phone\n");
        scanf("%d",&move_choice);
        if(move_choice==1 || rear==0)
        {
            if(isFull())
                printf("Phonebook is full\n");
            else
            {
                int wish;
                if(top==-1)
                    top=rear=0;
                else
                    rear++;
                phone[rear]=create_Node_Phone();
                fflush(stdin);
                printf("\n\nEnter name of phone\n");
                fflush(stdin);
                scanf("%[^\n]s",phone[rear]->Phone_name);
                fflush(stdin);
                printf("Enter your phone number\n");
                scanf("%[^\n]s",phone[rear]->Phone_number);
                fflush(stdin);
                copy_move(rear,pos);
                deletePhone_move(pos);
            }
        }
        else if(move_choice==2)
        {
            int pos2=check();
            if(pos2==-1)
                printf("Phone not found\n");
            else
            {
                copy_move(pos2,pos);
                deletePhone_move(pos);
            }
        }
    }
}
void display()
{
    int input;
    printf("Enter 1 to display all contacts\t\tEnter 2 to display a phone\t\tEnter 0 for exiting\n");
    scanf("%d",&input);
    printf("**************************************************\n");
    if(input==1)
    {
        int i=top;
        int nice=0;
        while(i<=rear)
        {
            printf("Phone name:%s     Phone number:%s\n",phone[i]->Phone_name,phone[i]->Phone_number);
            printf("Contacts:\n");
            struct contacts *traverse=phone[i]->next;
            while(traverse!=NULL)
            {
                if(nice<5)
                {
                    printf("%s : %s     ",traverse->name,traverse->number);
                    nice++;
                }
                if(nice>=5)
                {
                    nice=0;
                    printf("\n");
                }
                traverse=traverse->link;
            }
            nice=0;
            i++;
            printf("\n------------------------------------\n");
        }
    }
    else if(input==2)
    {
        int nice=0;
        int pos=check();
        if(pos==-1)
            printf("Phone not found\n");
        else
        {
            struct contacts *traverse=phone[pos]->next;
            if(traverse==NULL)
                printf("Phone has no contacts\n");
            else
            {
                 while(traverse!=NULL)
                {
                    if(nice<5)
                    {
                        printf("%s : %s     ",traverse->name,traverse->number);
                        nice++;
                    }
                    if(nice>=5)
                    {
                        nice=0;
                        printf("\n");
                    }
                    traverse=traverse->link;
                }
                printf("\n\n");
            }
        }
    }
}
void readcsv()
{
    FILE *fp=fopen("phonebook.csv","r");
    char temp1[100];
    for(int i=0;fgets(temp1,100,fp)!=NULL;i++)
    {
        if(i==max)
            break;
        else
        {
            if(top==-1)
                top=rear=0;
            else
                rear++;
            phone[i]=malloc(sizeof(struct phonebook));
            phone[i]->next=NULL;
            strcpy(phone[i]->Phone_name,strtok(temp1,","));
            strcpy(phone[i]->Phone_number,strtok(NULL,","));
            char temp2[1024];
            fgets(temp2,1024,fp);
            char *token_name=strtok(temp2,",");
            char *token_number=strtok(NULL,",");
            while(token_name!=NULL)
            {
                int len=strlen(token_number);
                if (len > 0 && token_number[len - 1] == '\n') 
                    token_number[len - 1] = '\0';
                if(phone[i]->next==NULL)
                    phone[i]->next=create_node(token_name,token_number);
                else
                {
                    struct contacts *k=create_node(token_name,token_number);
                    k->link=phone[i]->next;
                    phone[i]->next=k;
                }
                token_name=strtok(NULL,",");
                token_number=strtok(NULL,",");
                if(rear>0)
                    getMutual2(phone[i]->next);
            }
            if(rear==0)
                makeMutual();
        }
    }
}
void k()
{
    struct mutual *temp=suggest->next;
    while(temp!=NULL)
    {
        printf("%s : %s     %d\n",temp->name,temp->number,temp->frequency);
        temp=temp->next;
    }
}
int main()
{
    readcsv();
    int wish=1;
    while(wish)
    {
        printf("Press 1 for adding phone\n");
        printf("Press 2 for adding number\n");
        printf("Press 3 for deleting Phone\n");
        printf("Press 4 for deleting number\n");
        printf("Press 5 to display\n");
        printf("Press 6 to move contacts\n");
        printf("Press 7 to search for a contact\n");
        printf("Press 0 for exiting\n");
        scanf("%d",&wish);
        if(wish==1)
            addPhone();
        else if(wish==2)
            addNumber();
        else if(wish==3)
            deletePhone();
        else if(wish==4)
            deleteNumber();
        else if(wish==5)
            display();
        else if(wish==6)
            move();
        else if(wish==7)
            search();
        else if(wish==8)
            k();
        sortAll();
        sortMutualByFrequency(suggest->next);
    }
}