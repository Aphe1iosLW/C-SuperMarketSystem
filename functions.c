#include "general.h"

//���Ȳ鿴ͷ�ļ� �˽�ÿ������������

Node * head=NULL;
Node * purchased=NULL;
double sum_=0;
char message[5][50];
bool flag=false;//����������
void list_build()//������
{
    Node *p, *p0;//pΪ���ڴ����Ľڵ㣬 p0Ϊp��ǰ�ýڵ�
    FILE *fp = fopen("items.txt", "r");//�Ӵ��ļ��е�������
    if(fp==NULL)//����ļ��Ƿ�¹��򿪣�
    {
        printf("Failed to open the file!\n");
        system("pause");
        exit(-1);
    }
    fscanf(fp,"%s%s%s%s%s",message[0],message[1],message[2],message[3],message[4]);
    while(true)//�ظ������������Ҫѭ��
    {
        p = (Node *) malloc(sizeof(Node));//p�������涯̬�����Ľڵ�
        p->next=NULL;//����Ҫ��һ������������һ��ָ��ָ���  ��Ҫ�����ж���������ͳ䵱�ж�����
        if ((fscanf(fp, "%s%s%s%lf%lf", p->name, p->level, p->category,&p->price, &p->amount)) == EOF)
        {
            free(p);//�����ļ���β����û������������ڴ��ͷŵ�
            break;
        }
        else
        {
            if(head==NULL)
            {
                head=p;
                p0=p;
            }
            else
            {
                p0->next=p;
                p0=p;
            }
        }
    }
    fclose(fp);
}

void list_display()//��������չʾ����
{
    Node *p=head;
    printf("*****************************��Ʒ��Ϣ����*****************************\n\n");
    printf("%-15s",message[0]);
    printf("%-17s",message[1]);
    printf("%-15s",message[2]);
    printf("%-16s",message[3]);
    printf("%-15s",message[4]);
    printf("\n");
    while(p!=NULL)
    {
        printf("%-10s\t",p->name);
        printf("%-10s\t",p->level);
        printf("%-10s\t",p->category);
        printf("%-10.1lf\t",p->price);
        printf("%-10.1lf\t",p->amount);
        printf("\n");
        p=p->next;
    }
    printf("\n");
    printf("**********************************************************************\n");
    system("pause");
}

void list_item_purchase()
{
    char ch[100];
    loop2:
    printf("-1-��������Ҫ�������Ʒ:(Key 0 to quit)\n");
    char name[20];
    scanf("%s", name);
    if(strcmp(name,"0")==0)
        return ;
    printf("-2-������ȼ�����  ��  �� \n");
    char level[30];
    scanf("%s", level);
    Node *p = head;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0 && strcmp(p->level,level)==0) {
            loop1:
            printf("-3-������Ҫ���������/��\n");
            double n;
            scanf("%lf", &n);
            if (n > p->amount) {
                printf("����������棡(���ֻ��%.1lf)\n����������:\n", p->amount);
                goto loop1;
            }
            p->amount -= n;
            double sum = n * p->price;
            printf("-4-����ɹ� �ܹ�����%.1lfԪ\n", sum);

            //���´��뱣�汻����Ķ���
            Node* search=purchased;//�������е��������Ƿ񱣴���ͬ����Ʒ
            while(search!=NULL)
            {
                if(strcmp(search->name,p->name)==0&&strcmp(search->level,p->level)==0) {
                    search->amount+=n;
                    goto loop5;
                }
                search=search->next;
            }
            Node *p_node=(Node*)malloc(sizeof(Node));
            p_node->next=NULL;
            strcpy(p_node->name,p->name);
            strcpy(p_node->level,p->level);
            strcpy(p_node->category,p->category);
            p_node->price=p->price;
            p_node->amount=n;
            if(purchased==NULL){
                purchased=p_node;
                goto loop5;
            }
            search=purchased;
            while(search->next!=NULL)
                search=search->next;
            search->next=p_node;
            //���ϴ��뱣�汻����Ķ���
            loop5:
            sum_+=sum;
            printf("�Ƿ�Ҫ����������Ʒ��\n");
            printf("(1:�� 0:��)\n");
            loop3:
            scanf("%s", ch);
            if (strcmp(ch, "0") == 0)
                return;
            else if (strcmp(ch, "1") == 0)
                goto loop2;
            else {
                printf("��Ч���룬����������\n");
                goto loop3;
            }
        } else
            p = p->next;
    }
    printf("û���ҵ���Ӧ����Ʒ(1:��������  0:����ϵͳ)");
    loop4:
    scanf("%s",ch);
    if(strcmp(ch,"1")==0)
        goto loop2;
    else if(strcmp(ch,"0")==0)
        return ;
    else{
        printf("��Ч���룬����������\n");
        goto loop4;
    }
}

void purchase_in_display()//�ڹ˿�ϵͳ����չʾ����֮��  ����ѯ�ʹ˿��Ƿ�Ҫ����
{
    char ch[100];
    printf("�����Ƿ�Ҫ������Ʒ��(1:����  0:���ع˿�ϵͳ)\n");
    loop2:
    scanf("%s",ch);
    if(strcmp(ch,"0")==0) {
        system("pause");
        return;
    }else if(strcmp(ch,"1")==0) {
        loop3:
        printf("-1-��������Ҫ�������Ʒ:(Key 0 to quit)\n");
        char name[20];
        scanf("%s", name);
        if(strcmp(name,"0")==0)
            return ;
        printf("-2-������ȼ�����  ��  ��\n");
        char level[30];
        scanf("%s", level);
        Node *p = head;
        while (p != NULL) {
            if (strcmp(p->name, name) == 0 && strcmp(p->level,level)==0) {
                loop1:
                printf("-3-������Ҫ���������/��\n");
                double n;
                scanf("%lf", &n);
                if (n > p->amount) {
                    printf("����������棡(���ֻ��%.1lf)\n����������:\n", p->amount);
                    goto loop1;
                }
                p->amount -= n;
                double sum = n * p->price;
                printf("-4-����ɹ� �ܹ�����%.1lfԪ\n", sum);


                //���´��뱣�汻����Ķ���
                Node* search=purchased;//�������е��������Ƿ񱣴���ͬ����Ʒ
                while(search!=NULL)
                {
                    if(strcmp(search->name,p->name)==0&&strcmp(search->level,p->level)==0) {
                        search->amount+=n;
                        goto loop5;
                    }
                    search=search->next;
                }
                Node *p_node=(Node*)malloc(sizeof(Node));
                p_node->next=NULL;
                strcpy(p_node->name,p->name);
                strcpy(p_node->level,p->level);
                strcpy(p_node->category,p->category);
                p_node->price=p->price;
                p_node->amount=n;
                if(purchased==NULL){
                    purchased=p_node;
                    goto loop5;
                }
                search=purchased;
                while(search->next!=NULL)
                    search=search->next;
                search->next=p_node;
                //���ϴ��뱣�汻����Ķ���

                loop5:
                sum_+=sum;
                system("pause\n");
                printf("�Ƿ�Ҫ����������Ʒ��\n");
                printf("(1:�� 0:��)\n");
                loop4:
                scanf("%s",ch);
                if(strcmp(ch,"0")==0)
                    return ;
                else if(strcmp(ch,"1")==0)
                    goto loop3;
                else{
                    printf("��Ч���룬����������\n");
                    goto loop4;
                }
            } else
                p = p->next;
        }
        printf("δ�ҵ���Ӧ����Ʒ�����������룺\n");
        goto loop3;
    }
    else
    {
        printf("��Ч���룬����������:\n");
        goto loop2;
    }
}

void list_item_add()
{
    Node *p=head;
    printf("-1-������Ҫ��ӵ���Ʒ���ƣ�\n");
    char name[20];
    scanf("%s",name);
    while(p->next!=NULL)
        p=p->next;
    Node *temp=(Node *)malloc(sizeof(Node));
    temp->next=NULL;
    printf("-2-��������ȼ���\n");
    scanf("%s",temp->level);
    printf("-3-�����������ࣺ\n");
    scanf("%s",temp->category);
    printf("-4-��������۸�\n");
    scanf("%lf",&temp->price);
    printf("-5-��������������\n");
    scanf("%lf",&temp->amount);
    p->next=temp;
    printf("��ӳɹ��� �������ع���ϵͳ\n");
    system("pause");
}

void list_item_delete()
{
    loop1:
    printf("-1-������Ҫɾ������Ʒ���ƣ�\n");
    char name[20];
    scanf("%s",name);
    printf("-2-������Ҫɾ����Ʒ�ĵȼ�����  ��  ��  \n");
    char level[30];
    scanf("%s",level);
    Node *p=head;
    Node *pre;
    while(p!=NULL)
    {
        if(strcmp(name,p->name)==0&&strcmp(level,p->level)==0){
            printf("%-15s",message[0]);
            printf("%-17s",message[1]);
            printf("%-15s",message[2]);
            printf("%-16s",message[3]);
            printf("%-15s",message[4]);
            printf("\n");
            printf("%-15s",p->name);
            printf("%-15s",p->level);
            printf("%-15s",p->category);
            printf("%-15lf",p->price);
            printf("%-15lf",p->amount);
            printf("\n");
            printf("* ȷ��Ҫɾ������Ʒ��*(1:�� 0:��)\n");
            char ch[20];
            loop2:
            scanf("%s",ch);
            if(strcmp(ch,"1")==0){
                if(p==head){
                    head=head->next;
                    free(p);
                }else{
                    pre->next=p->next;
                    free(p);
                }
                printf("��Ʒɾ���ɹ�\n");
                printf("��Ҫ���ع���ϵͳ\n");
                system("pause");
                return ;
            }else if(strcmp(ch,"0")==0){
                printf("��Ҫ���ع���ϵͳ\n");
                system("pause");
            }else{
                printf("��Ч���룬����������\n");
                goto loop2;
            }
        }
        pre=p;
        p=p->next;
    }
    printf("û���ҵ�����Ʒ (1:��������  0:�˳�)\n");
    char ch[20];
    loop3:
    scanf("%s",ch);
    if(strcmp(ch,"1")==0)
        goto loop1;
    else if(strcmp(ch,"0")==0)
        return ;
    else{
        printf("��Ч���룬����������\n");
        goto loop3;
    }
}

void list_item_modify()
{
    Node * p;
    loop1:
    p=head;
    printf("������Ҫ�޸ĵ���Ʒ���ƣ�\n");
    char name[30];
    scanf("%s",name);
    bool ed=false;
    Node *p_node[10];
    for(int i=0;i<10;i++)
        p_node[i]=0;
    int n=0;
    while(p!=NULL)
    {
        if(strcmp(name,p->name)==0){
            if(!ed){
                printf("*****************************��Ʒ��Ϣ����*****************************\n\n");
                printf("%-15s",message[0]);
                printf("%-17s",message[1]);
                printf("%-15s",message[2]);
                printf("%-16s",message[3]);
                printf("%-15s",message[4]);
                printf("\n");
            }
            p_node[n++]=p;
            ed=true;
            printf("%-10s\t",p->name);
            printf("%-10s\t",p->level);
            printf("%-10s\t",p->category);
            printf("%-10.1lf\t",p->price);
            printf("%-10.1lf\t",p->amount);
            printf("\n");
        }
        p=p->next;
    }
    if(ed){
        printf("������Ҫ�޸���Ʒ�ĵȼ���\n");
        char level[30];
        scanf("%s",level);
        n=0;
        while(p_node[n]!=NULL)
        {
            if(strcmp(p_node[n]->level,level)==0){
                printf("�����Ƿ�Ҫ�޸ĸ���Ʒ��(1:��  0:��)\n");
                char ch[20];
                scanf("%s",ch);
                if(strcmp(ch,"1")==0){
                    printf("�������޸ĺ�ļ۸�\n");
                    scanf("%lf",&p_node[n]->price);
                    printf("�������޸ĺ������:\n");
                    scanf("%lf",&p_node[n]->amount);
                    printf("�ɹ��޸ģ� �Ƿ�Ҫ�����޸���Ʒ��(1:��  0:��)\n");
                    loop2:
                    scanf("%s",ch);
                    if(strcmp(ch,"1")==0){
                        goto loop1;
                    }else if(strcmp(ch,"0")==0){
                        printf("��Ҫ����ϵͳ\n");
                        system("pause");
                        return ;
                    }else{
                        printf("��Ч���룬���������룺\n");
                        goto loop2;
                    }
                }else if(strcmp(ch,"0")==0){
                    printf("��������ϵͳ\n");
                    system("pause");
                    return ;
                }
            }
            n++;
        }
    }else{
        printf("û���ҵ�����Ʒ���Ƿ�Ҫ��������(1:��  0:��)\n");
        char ch[20];
        loop3:
        scanf("%s",ch);
        if(strcmp(ch,"1")==0){
            goto loop1;
        }else if(strcmp(ch,"0")==0){
            printf("��������ϵͳ\n");
            system("pause");
            return ;
        }else{
            printf("��Ч���룬���������룺\n");
            goto loop3;
        }
    }

}


void list_sort()
{
    /*int count=0;//ð����������ʾ��  ������ д�˺þý������������
    Node *p=head;
    Node *pre;
    Node *pre_head;
    pre_head=(Node* )malloc(sizeof(Node));
    pre_head->next=head;
    while(p!=NULL)
    {
        count++;
        p=p->next;
    }
    int i,j;
    for(i=0;i<count-1;i++)
    {
        p=pre_head->next;
        pre=pre_head;
        for(j=0;j<count-i-1;j++)
        {
            if(p->amount>p->next->amount){
                pre->next=p->next;
                p->next=p->next->next;
                p->next->next=p;
                p=pre->next;
            }
            pre=p;
            p=p->next;
        }
    }
    head=pre_head->next;
    free(pre_head);*/
    Node *p,*p0,*r,*r0,*q;
    p0=NULL;
    p=head;
    printf("-1-��ѡ������ķ�ʽ��(1:�۸�����  2:��������  3:�۸���  4:��������  5:����������)\n");
    char ways[20];
    loop1:
    scanf("%s",ways);
    if(strcmp(ways,"1")==0){
        while(p!=NULL)
        {
            r=head;
            while((r->price<p->price)&&(r!=p))
            {
                r0=r;
                r=r->next;
            }
            if(r!=p)
            {
                q=p;
                p0->next=p->next;
                p=p0;
                if(r==head){
                    q->next=head;
                    head=q;
                }else{
                    q->next=r;
                    r0->next=q;
                }
            }
            p0=p;
            p=p->next;
        }
    }else if(strcmp(ways,"2")==0){
        while(p!=NULL)
        {
            r=head;
            while((r->amount<p->amount)&&(r!=p))
            {
                r0=r;
                r=r->next;
            }
            if(r!=p)
            {
                q=p;
                p0->next=p->next;
                p=p0;
                if(r==head){
                    q->next=head;
                    head=q;
                }else{
                    q->next=r;
                    r0->next=q;
                }
            }
            p0=p;
            p=p->next;
        }
    }else if(strcmp(ways,"3")==0){
        while(p!=NULL)
        {
            r=head;
            while((r->price>p->price)&&(r!=p))
            {
                r0=r;
                r=r->next;
            }
            if(r!=p)
            {
                q=p;
                p0->next=p->next;
                p=p0;
                if(r==head){
                    q->next=head;
                    head=q;
                }else{
                    q->next=r;
                    r0->next=q;
                }
            }
            p0=p;
            p=p->next;
        }
    }else if(strcmp(ways,"4")==0){
        while(p!=NULL)
        {
            r=head;
            while((r->amount>p->amount)&&(r!=p))
            {
                r0=r;
                r=r->next;
            }
            if(r!=p)
            {
                q=p;
                p0->next=p->next;
                p=p0;
                if(r==head){
                    q->next=head;
                    head=q;
                }else{
                    q->next=r;
                    r0->next=q;
                }
            }
            p0=p;
            p=p->next;
        }
    }else if(strcmp(ways,"5")==0){
        while(p!=NULL)
        {
            r=head;
            while((strcmp(r->name,p->name)>0)&&(r!=p))
            {
                r0=r;
                r=r->next;
            }
            if(r!=p)
            {
                q=p;
                p0->next=p->next;
                p=p0;
                if(r==head){
                    q->next=head;
                    head=q;
                }else{
                    q->next=r;
                    r0->next=q;
                }
            }
            p0=p;
            p=p->next;
        }
    }



    else{
        printf("��Ч���룬����������\n");
        goto loop1;
    }
    printf("��Ʒ�Ѿ�������ɣ�\n");
    printf("-2-�Ƿ�Ҫչʾ��������Ʒ��(1:��  0:��)\n");
    char ch[20];
    loop2:
    scanf("%s",ch);
    if(strcmp(ch,"1")==0){
        list_display();
    }else if(strcmp(ch,"0")==0){
        system("pause");
        return ;
    }else{
        printf("��Ч���룬����������\n");
        goto loop2;
    }
}

bool password()//���ڼ������ĺ���
{
    FILE *fp= fopen("password.txt","r");
    char password[20];//�����û����������
    printf("����������: ");
    scanf("%s",password);
    char copy[20];//�����ļ��еĸ�������
    if(fp!=NULL) {
        fscanf(fp, "%s", copy);
        fclose(fp);
    }
    else {
        printf("Failed to open the file!");
        exit(-1);
    }
    if(strcmp(copy,password)==0)
        return true;
    else
        return false;
}

void password_change()//����ԱȨ��  ��������
{
    system("cls");
    printf("���Ժ�");
    Sleep(200);
    printf(".");
    Sleep(200);
    printf(".");
    Sleep(200);
    printf(".");
    system("cls");
    printf("\n\n****************����������ӭ���������޸�ϵͳ��������****************\n\n");
    FILE *f=fopen("password.txt","r");
    char password[20];
    fscanf(f,"%s",password);
    fclose(f);
    char password1[20];
    char password2[20];
    loop1:
    printf("-1-�����������룺(��֧���������� �������Ը���)\n");
    printf("(�Ƽ�3-16���ַ�)\n");
    scanf("%s",password1);
    printf("-2-��ȷ�ϣ�\n");
    scanf("%s",password2);
    if(strcmp(password1,password2)==0) {
        if(strcmp(password,password1)==0){
            printf("�����벻����ԭ������ͬ��(1:��������  0:�˳�)\n");
            char ch[20];
            loop2:
            scanf("%s",ch);
            if(strcmp(ch,"1")==0)
                goto loop1;
            else if(strcmp(ch,"0")==0)
                return ;
            else{
                printf("��Ч���룬����������\n");
                goto loop2;
            }
        }
        FILE * fp=fopen("password.txt","w");
        fprintf(fp, "%s", password1);
        fclose(fp);
        printf("�����޸ĳɹ��� ��Ҫ���ع���ϵͳ\n");
        system("pause");
        return ;
    }else{
        printf("�������벻һ�£����������룺\n");
        goto loop1;
    }
}

void list_search_manager()//����Ա��ѯ���� �޹���ѯ��
{
    Node *p=head;
    printf("������Ҫ��ѯ����Ʒ���ƣ�\n");
    char ch[20];
    loop1:
    scanf("%s",ch);
    bool ed=false;
    while(p!=NULL){
        if(strcmp(p->name,ch)==0){
            if(!ed) {
                printf("%-15s",message[0]);
                printf("%-17s",message[1]);
                printf("%-15s",message[2]);
                printf("%-16s",message[3]);
                printf("%-15s",message[4]);
                printf("\n");
            }
            ed=true;
            printf("%-15s",p->name);
            printf("%-15s",p->level);
            printf("%-15s",p->category);
            printf("%-15.1lf",p->price);
            printf("%-15.1lf",p->amount);
            printf("\n");
        }
        p=p->next;
    }
    if(ed){
        system("pause");
        return  ;
    }
    else{
        printf("û���ҵ���Ҫ����Ʒ\n");
        printf("1:��������  0:����ϵͳ\n");
        char c[100];
        loop2:
        scanf("%s",c);
        if(strcmp(c,"1")==0)
            goto loop1;
        else if(strcmp(c,"0")==0)
            return ;
        else{
            printf("��Ч���룬���������룺\n");
            goto loop2;
        }
    }
}

void list_search_customer()//�˿Ͳ�ѯ���� �й���ѯ��
{
    Node *p=head;
    Node* p_node[100];//����һ����Ʒ�ж������� ���ڱ���鵽��������Ʒ�Ľڵ�
    for(int i=0;i<100;i++)
        p_node[i]=NULL;//��ֵΪ�գ������ж�����
    int n=0;//���ڱ���p_node���±�
    printf("-1-������Ҫ��ѯ����Ʒ���ƣ�\n");
    char ch[20];
    loop1:
    scanf("%s",ch);
    bool ed=false;
    while(p!=NULL){
        if(strcmp(p->name,ch)==0){
            if(!ed) {
                printf("%-15s",message[0]);
                printf("%-17s",message[1]);
                printf("%-15s",message[2]);
                printf("%-16s",message[3]);
                printf("%-15s",message[4]);
                printf("\n");
            }
            ed=true;
            printf("%-15s",p->name);
            printf("%-15s",p->level);
            printf("%-15s",p->category);
            printf("%-15.1lf",p->price);
            printf("%-15.1lf",p->amount);
            printf("\n");
            p_node[n++]=p;//������Ʒ�Ľڵ�   ���ڼ���ѭ�������Ч��
        }
        p=p->next;
    }
    if(ed){
        system("pause");
        printf("-2-���Ƿ�Ҫ�������Ʒ��\n");
        printf("1:��  0:��\n");
        scanf("%s",ch);
        if(strcmp(ch,"0")==0)
            return ;
        else if(strcmp(ch,"1")==0){
            printf("-3-������Ҫ����ĵȼ���(��  ��  ��   Key 0 to quit)\n");
            char level[30];
            scanf("%s",level);
            n=0;
            while(p_node[n]!=NULL)
            {
                if(strcmp(level,p_node[n]->level)==0){
                    printf("-4-��������Ҫ���������/��\n");
                    double amount;
                    loop3:
                    scanf("%lf",&amount);
                    if(amount>p_node[n]->amount){
                        printf("���������������(���ֻ��%.1lf��)\n",p_node[n]->amount);
                        printf("���������룺\n");
                        goto loop3;
                    }
                    p_node[n]->amount-=amount;
                    double sum=amount*p_node[n]->price;

                    //���´��뱣�湺�����Ʒ
                    Node* search=purchased;
                    while(search!=NULL)
                    {
                        if(strcmp(search->name,p_node[n]->name)==0&&strcmp(search->level,p_node[n]->level)==0) {
                            search->amount+=amount;
                            goto loop4;
                        }
                        search=search->next;
                    }
                    Node *temp=(Node*)malloc(sizeof(Node));
                    temp->next=NULL;
                    strcpy(temp->name,p_node[n]->name);
                    strcpy(temp->level,p_node[n]->level);
                    strcpy(temp->category,p_node[n]->category);
                    temp->price=p_node[n]->price;
                    temp->amount=amount;
                    if(purchased==NULL) {
                        purchased = temp;
                        goto loop4;
                    }
                    search=purchased;
                    while(search->next!=NULL)
                        search=search->next;
                    search->next=temp;
                    //
                    loop4:
                    sum_+=sum;
                    printf("����ɹ��� ������%.1lfԪ\n",sum);
                    system("pause");

                }
                n++;
            }

        }
    }else{
        printf("û���ҵ���Ҫ����Ʒ\n");
        printf("1:��������  0:����ϵͳ\n");
        loop2:
        scanf("%s",ch);
        if(strcmp(ch,"1")==0)
            goto loop1;
        else if(strcmp(ch,"0")==0)
            return ;
        else{
            printf("��Ч���룬���������룺\n");
            goto loop2;
        }
    }
}

void item_purchased()
{
    printf("***************************�ѹ���Ʒ��Ϣ����***************************\n\n");
    printf("%-15s",message[0]);
    printf("%-17s",message[1]);
    printf("%-15s",message[2]);
    printf("%-16s",message[3]);
    printf("%-15s",message[4]);
    printf("\n");
    Node*p=purchased;
    while(p!=NULL)
    {
        printf("%-10s\t",p->name);
        printf("%-10s\t",p->level);
        printf("%-10s\t",p->category);
        printf("%-10.1lf\t",p->price);
        printf("%-10.1lf\t",p->amount);
        printf("\n");
        p=p->next;
    }
    printf("\n");
    printf("**********************************************************************\n");
    printf("\n������:%.1lfԪ\n",sum_);
    system("pause");

}

void system_menu()
{
    while(true)//����ѭ��  �����ظ�����
    {
        for (int i = 0; i < 51; i++) {
            putchar('*');
            Sleep(1);
        }
        printf("\n");
        printf("---------------------------------------------------\n");
        printf("|                 ��ӭ��������ϵͳ                |\n");
        printf("|*********   ��������� 1 �� 2 ѡ��ϵͳ  *********|\n");
        printf("|*********      Number 1 ���˿�ϵͳ      *********|\n");
        printf("|*********      Number 2 ������ϵͳ      *********|\n");
        printf("|*********      Number 0 ���˳�ϵͳ      *********|\n");
        printf("|                                                 |\n");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < 51; i++) {
            putchar('*');
            Sleep(1);
        }
        printf("\n");
        char ch[100];
        loop:
        scanf("%s",ch);
        if(strcmp(ch,"1")==0)
            system_customer();
        else if(strcmp(ch,"2")==0)
            system_manager();
        else if(strcmp(ch,"0")==0)
            return ;
        else
        {
            printf("��Ч���룬���������룡\n");
            goto loop;
        }
    }
}



void system_customer()
{
    while(true)//�����˵�ͬ��
    {
        system("cls");//ÿ�ν���ϵͳ������  ������õ��Ӿ�����
        for (int i = 0; i < 55; i++) {//�����滨��
            putchar('*');
        }
        printf("\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                ___��ӭ�����˿�ϵͳ___               |\n");
        printf("|*********         ���������ѡ��ϵͳ        *********|\n");
        printf("|*********       Number 1:��Ʒչʾϵͳ       *********|\n");
        printf("|*********       Number 2:��Ʒ��ѯϵͳ       *********|\n");
        printf("|*********       Number 3:��Ʒ����ϵͳ       *********|\n");
        printf("|*********       Number 4:�ѹ���Ʒ��ѯ       *********|\n");
        printf("|*********       Number 0:�˳��˿�ϵͳ       *********|\n");
        printf("|-----------------------------------------------------|\n");
        for (int i = 0; i < 55; i++) {
            putchar('*');
        }
        printf("\n");
        char ch[100];
        scanf("%s",ch);
        if(strcmp(ch,"1")==0){
            list_display();
            purchase_in_display();
        }else if(strcmp(ch,"2")==0){
            list_search_customer();
        }else if(strcmp(ch,"3")==0){
            list_item_purchase();
        }else if(strcmp(ch,"4")==0){
            item_purchased();
        }
        else if(strcmp(ch,"0")==0) {
            system("cls");
            return;
        }
    }
}

void system_manager()
{
    if(!flag)//flag �����ж��Ƿ�����������  ����ɹ����뼴ȷ����� �����������ϵͳ�㲻����Ҫ��������
    {
        system("cls");
        printf("\n\n");
        printf("**************** ����������ӭ���볬�й����¼ϵͳ�������� ****************");
        printf("\n\n\n");
        int count = 4;
        while (!password())
        {
            if (--count == 0)
            {
                printf("��ʣ�����!\n");
                exit(0);
            }
            printf("�������!\n�����ԣ�(����%d�λ���)\n", count);
        }
        flag=true;
        printf("������ȷ!\n");
    }
    while(true)
    {
        system("cls");
        for (int i = 0; i < 55; i++) {
            putchar('*');
        }
        printf("\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                   ��ӭ��������ϵͳ                  |\n");
        printf("|*********         ���������ѡ��ϵͳ        *********|\n");
        printf("|*********       Number 1:��Ʒչʾϵͳ       *********|\n");
        printf("|*********       Number 2:��Ʒ��ѯϵͳ       *********|\n");
        printf("|*********       Number 3:��Ʒ�޸�ϵͳ       *********|\n");
        printf("|*********       Number 4:��Ʒ���ϵͳ       *********|\n");
        printf("|*********       Number 5:��Ʒɾ��ϵͳ       *********|\n");
        printf("|*********       Number 6:��Ʒ����ϵͳ       *********|\n");
        printf("|*********       Number 7:Ӫҵ�ܶ��ѯ       *********|\n");
        printf("|*********       Number 8:���������޸�       *********|\n");
        printf("|*********       Number 0:�˳�����ϵͳ       *********|\n");
        printf("|-----------------------------------------------------|\n");
        for (int i = 0; i < 55; i++) {
            putchar('*');
        }
        printf("\n");
        char ch[100];
        loop://������Ч�������  ǿ����ת
        scanf("%s",ch);
        if(strcmp(ch,"1")==0)
        {
            list_display();
        }else if(strcmp(ch,"2")==0){
            list_search_manager();
        }else if(strcmp(ch,"3")==0){
            list_item_modify();
        }else if(strcmp(ch,"4")==0){
            list_item_add();
        }else if(strcmp(ch,"5")==0){
            list_item_delete();
        }else if(strcmp(ch,"6")==0){
            list_sort();
        }else if(strcmp(ch,"7")==0){
            volume_check();
        }
        else if(strcmp(ch,"8")==0)
            password_change();
        else if(strcmp(ch,"0")==0) {
            system("cls");
            return ;
        }
        else
        {
            printf("��Ч���룬����������:\n");
            goto loop;
        }
    }
}

void volume_check()
{
    FILE* fp=fopen("BusinessVolume.txt","r");
    if(fp==NULL){
        printf("Failed to open the file \n");
        system("pause");
        exit(-1);
    }
    double sum;
    fscanf(fp,"%lf",&sum);
    printf("�ܵ�Ӫҵ��Ϊ%.1lf\n",sum);
    system("pause");
}

void volume_rewrite()
{
    FILE *fp=fopen("BusinessVolume.txt","r");
    if(fp==NULL){
        printf("Failed to open the file \n");
        system("pause");
        exit(-1);
    }
    double temp;
    fscanf(fp,"%lf",&temp);
    fclose(fp);
    double sum=sum_+temp;
    fp=fopen("BusinessVolume.txt","w");
    fprintf(fp,"%lf",sum);
    fclose(fp);
}


void list_rewrite()
{
    Node* p=head;
    FILE *fp=fopen("items.txt","w");
    if(fp==NULL)
    {
        printf("Failed to open the file!");
        exit(0);
    }
    fprintf(fp,"%-15s",message[0]);
    fprintf(fp,"%-17s",message[1]);
    fprintf(fp,"%-15s",message[2]);
    fprintf(fp,"%-16s",message[3]);
    fprintf(fp,"%-15s",message[4]);
    fprintf(fp,"\n");
    while(p!=NULL)
    {
        fprintf(fp,"%-10s\t",p->name);
        fprintf(fp,"%-10s\t",p->level);
        fprintf(fp,"%-10s\t",p->category);
        fprintf(fp,"%-10.1lf\t",p->price);
        fprintf(fp,"%-10.1lf\t",p->amount);
        fprintf(fp,"\n");
        p=p->next;
    }
    fclose(fp);
}

void list_delete()
{
    Node *save,*p;
    p=head;
    while(p!=NULL)
    {
        save=p->next;
        free(p);
        p=save;
    }
}