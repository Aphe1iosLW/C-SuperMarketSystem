#include "general.h"

//请先查看头文件 了解每个函数的作用

Node * head=NULL;
Node * purchased=NULL;
double sum_=0;
char message[5][50];
bool flag=false;//用于密码检查
void list_build()//链表创建
{
    Node *p, *p0;//p为正在创建的节点， p0为p的前置节点
    FILE *fp = fopen("items.txt", "r");//从此文件中导入内容
    if(fp==NULL)//检查文件是否陈工打开；
    {
        printf("Failed to open the file!\n");
        system("pause");
        exit(-1);
    }
    fscanf(fp,"%s%s%s%s%s",message[0],message[1],message[2],message[3],message[4]);
    while(true)//重复创建链表的主要循环
    {
        p = (Node *) malloc(sizeof(Node));//p用来保存动态创建的节点
        p->next=NULL;//很重要的一步，把它的下一个指针指向空  主要用来判断链表结束和充当判断条件
        if ((fscanf(fp, "%s%s%s%lf%lf", p->name, p->level, p->category,&p->price, &p->amount)) == EOF)
        {
            free(p);//读到文件结尾，把没有链入链表的内存释放掉
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

void list_display()//链表内容展示函数
{
    Node *p=head;
    printf("*****************************商品信息如下*****************************\n\n");
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
    printf("-1-请输入你要购买的物品:(Key 0 to quit)\n");
    char name[20];
    scanf("%s", name);
    if(strcmp(name,"0")==0)
        return ;
    printf("-2-请输入等级：优  良  次 \n");
    char level[30];
    scanf("%s", level);
    Node *p = head;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0 && strcmp(p->level,level)==0) {
            loop1:
            printf("-3-请输入要购买的数量/斤\n");
            double n;
            scanf("%lf", &n);
            if (n > p->amount) {
                printf("数量超出库存！(库存只有%.1lf)\n请重新输入:\n", p->amount);
                goto loop1;
            }
            p->amount -= n;
            double sum = n * p->price;
            printf("-4-购买成功 总共花费%.1lf元\n", sum);

            //以下代码保存被购买的东西
            Node* search=purchased;//搜索旧有的链表中是否保存相同的商品
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
            //以上代码保存被购买的东西
            loop5:
            sum_+=sum;
            printf("是否要继续购买商品？\n");
            printf("(1:是 0:否)\n");
            loop3:
            scanf("%s", ch);
            if (strcmp(ch, "0") == 0)
                return;
            else if (strcmp(ch, "1") == 0)
                goto loop2;
            else {
                printf("无效输入，请重新输入\n");
                goto loop3;
            }
        } else
            p = p->next;
    }
    printf("没有找到对应的商品(1:重新输入  0:返回系统)");
    loop4:
    scanf("%s",ch);
    if(strcmp(ch,"1")==0)
        goto loop2;
    else if(strcmp(ch,"0")==0)
        return ;
    else{
        printf("无效输入，请重新输入\n");
        goto loop4;
    }
}

void purchase_in_display()//在顾客系统调用展示函数之后  用于询问顾客是否要购买
{
    char ch[100];
    printf("请问是否要购买物品？(1:购买  0:返回顾客系统)\n");
    loop2:
    scanf("%s",ch);
    if(strcmp(ch,"0")==0) {
        system("pause");
        return;
    }else if(strcmp(ch,"1")==0) {
        loop3:
        printf("-1-请输入你要购买的物品:(Key 0 to quit)\n");
        char name[20];
        scanf("%s", name);
        if(strcmp(name,"0")==0)
            return ;
        printf("-2-请输入等级：优  良  次\n");
        char level[30];
        scanf("%s", level);
        Node *p = head;
        while (p != NULL) {
            if (strcmp(p->name, name) == 0 && strcmp(p->level,level)==0) {
                loop1:
                printf("-3-请输入要购买的数量/斤\n");
                double n;
                scanf("%lf", &n);
                if (n > p->amount) {
                    printf("数量超出库存！(库存只有%.1lf)\n请重新输入:\n", p->amount);
                    goto loop1;
                }
                p->amount -= n;
                double sum = n * p->price;
                printf("-4-购买成功 总共花费%.1lf元\n", sum);


                //以下代码保存被购买的东西
                Node* search=purchased;//搜索旧有的链表中是否保存相同的商品
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
                //以上代码保存被购买的东西

                loop5:
                sum_+=sum;
                system("pause\n");
                printf("是否要继续购买商品？\n");
                printf("(1:是 0:否)\n");
                loop4:
                scanf("%s",ch);
                if(strcmp(ch,"0")==0)
                    return ;
                else if(strcmp(ch,"1")==0)
                    goto loop3;
                else{
                    printf("无效输入，请重新输入\n");
                    goto loop4;
                }
            } else
                p = p->next;
        }
        printf("未找到对应的商品，请重新输入：\n");
        goto loop3;
    }
    else
    {
        printf("无效输入，请重新输入:\n");
        goto loop2;
    }
}

void list_item_add()
{
    Node *p=head;
    printf("-1-请输入要添加的商品名称：\n");
    char name[20];
    scanf("%s",name);
    while(p->next!=NULL)
        p=p->next;
    Node *temp=(Node *)malloc(sizeof(Node));
    temp->next=NULL;
    printf("-2-请输入其等级：\n");
    scanf("%s",temp->level);
    printf("-3-请输入其种类：\n");
    scanf("%s",temp->category);
    printf("-4-请输入其价格：\n");
    scanf("%lf",&temp->price);
    printf("-5-请输入其数量：\n");
    scanf("%lf",&temp->amount);
    p->next=temp;
    printf("添加成功！ 即将返回管理系统\n");
    system("pause");
}

void list_item_delete()
{
    loop1:
    printf("-1-请输入要删除的商品名称：\n");
    char name[20];
    scanf("%s",name);
    printf("-2-请输入要删除商品的等级：优  良  次  \n");
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
            printf("* 确定要删除改商品吗？*(1:是 0:否)\n");
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
                printf("商品删除成功\n");
                printf("将要返回管理系统\n");
                system("pause");
                return ;
            }else if(strcmp(ch,"0")==0){
                printf("将要返回管理系统\n");
                system("pause");
            }else{
                printf("无效输入，请重新输入\n");
                goto loop2;
            }
        }
        pre=p;
        p=p->next;
    }
    printf("没有找到该商品 (1:重新输入  0:退出)\n");
    char ch[20];
    loop3:
    scanf("%s",ch);
    if(strcmp(ch,"1")==0)
        goto loop1;
    else if(strcmp(ch,"0")==0)
        return ;
    else{
        printf("无效输入，请重新输入\n");
        goto loop3;
    }
}

void list_item_modify()
{
    Node * p;
    loop1:
    p=head;
    printf("请输入要修改的商品名称：\n");
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
                printf("*****************************商品信息如下*****************************\n\n");
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
        printf("请输入要修改商品的等级：\n");
        char level[30];
        scanf("%s",level);
        n=0;
        while(p_node[n]!=NULL)
        {
            if(strcmp(p_node[n]->level,level)==0){
                printf("请问是否要修改该商品：(1:是  0:否)\n");
                char ch[20];
                scanf("%s",ch);
                if(strcmp(ch,"1")==0){
                    printf("请输入修改后的价格：\n");
                    scanf("%lf",&p_node[n]->price);
                    printf("请输入修改后的数量:\n");
                    scanf("%lf",&p_node[n]->amount);
                    printf("成功修改， 是否要继续修改商品：(1:是  0:否)\n");
                    loop2:
                    scanf("%s",ch);
                    if(strcmp(ch,"1")==0){
                        goto loop1;
                    }else if(strcmp(ch,"0")==0){
                        printf("将要返回系统\n");
                        system("pause");
                        return ;
                    }else{
                        printf("无效输入，请重新输入：\n");
                        goto loop2;
                    }
                }else if(strcmp(ch,"0")==0){
                    printf("即将返回系统\n");
                    system("pause");
                    return ;
                }
            }
            n++;
        }
    }else{
        printf("没有找到该商品，是否要重新输入(1:是  0:否)\n");
        char ch[20];
        loop3:
        scanf("%s",ch);
        if(strcmp(ch,"1")==0){
            goto loop1;
        }else if(strcmp(ch,"0")==0){
            printf("即将返回系统\n");
            system("pause");
            return ;
        }else{
            printf("无效输入，请重新输入：\n");
            goto loop3;
        }
    }

}


void list_sort()
{
    /*int count=0;//冒泡排序错误的示范  好难受 写了好久结果不对呜呜呜
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
    printf("-1-请选择排序的方式：(1:价格升序  2:数量升序  3:价格降序  4:数量降序  5:按名称排序)\n");
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
        printf("无效输入，请重新输入\n");
        goto loop1;
    }
    printf("商品已经排序完成！\n");
    printf("-2-是否要展示排序后的商品？(1:是  0:否)\n");
    char ch[20];
    loop2:
    scanf("%s",ch);
    if(strcmp(ch,"1")==0){
        list_display();
    }else if(strcmp(ch,"0")==0){
        system("pause");
        return ;
    }else{
        printf("无效输入，请重新输入\n");
        goto loop2;
    }
}

bool password()//用于检查密码的函数
{
    FILE *fp= fopen("password.txt","r");
    char password[20];//保存用户输入的密码
    printf("请输入密码: ");
    scanf("%s",password);
    char copy[20];//保存文件中的副本密码
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

void password_change()//管理员权限  更改密码
{
    system("cls");
    printf("请稍候");
    Sleep(200);
    printf(".");
    Sleep(200);
    printf(".");
    Sleep(200);
    printf(".");
    system("cls");
    printf("\n\n****************————欢迎进入密码修改系统————****************\n\n");
    FILE *f=fopen("password.txt","r");
    char password[20];
    fscanf(f,"%s",password);
    fclose(f);
    char password1[20];
    char password2[20];
    loop1:
    printf("-1-请输入新密码：(不支持中文密码 否则后果自负！)\n");
    printf("(推荐3-16个字符)\n");
    scanf("%s",password1);
    printf("-2-请确认：\n");
    scanf("%s",password2);
    if(strcmp(password1,password2)==0) {
        if(strcmp(password,password1)==0){
            printf("新密码不能与原密码相同！(1:重新输入  0:退出)\n");
            char ch[20];
            loop2:
            scanf("%s",ch);
            if(strcmp(ch,"1")==0)
                goto loop1;
            else if(strcmp(ch,"0")==0)
                return ;
            else{
                printf("无效输入，请重新输入\n");
                goto loop2;
            }
        }
        FILE * fp=fopen("password.txt","w");
        fprintf(fp, "%s", password1);
        fclose(fp);
        printf("密码修改成功！ 将要返回管理系统\n");
        system("pause");
        return ;
    }else{
        printf("两次密码不一致，请重新输入：\n");
        goto loop1;
    }
}

void list_search_manager()//管理员查询函数 无购买询问
{
    Node *p=head;
    printf("请输入要查询的物品名称：\n");
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
        printf("没有找到您要的商品\n");
        printf("1:重新输入  0:返回系统\n");
        char c[100];
        loop2:
        scanf("%s",c);
        if(strcmp(c,"1")==0)
            goto loop1;
        else if(strcmp(c,"0")==0)
            return ;
        else{
            printf("无效输入，请重新输入：\n");
            goto loop2;
        }
    }
}

void list_search_customer()//顾客查询函数 有购买询问
{
    Node *p=head;
    Node* p_node[100];//由于一个商品有多种种类 用于保存查到的所有商品的节点
    for(int i=0;i<100;i++)
        p_node[i]=NULL;//赋值为空，用于判断条件
    int n=0;//由于保存p_node的下标
    printf("-1-请输入要查询的物品名称：\n");
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
            p_node[n++]=p;//保存商品的节点   用于减少循环，提高效率
        }
        p=p->next;
    }
    if(ed){
        system("pause");
        printf("-2-您是否要购买此商品？\n");
        printf("1:是  0:否\n");
        scanf("%s",ch);
        if(strcmp(ch,"0")==0)
            return ;
        else if(strcmp(ch,"1")==0){
            printf("-3-请输入要购买的等级：(优  良  次   Key 0 to quit)\n");
            char level[30];
            scanf("%s",level);
            n=0;
            while(p_node[n]!=NULL)
            {
                if(strcmp(level,p_node[n]->level)==0){
                    printf("-4-请输入您要购买的数量/斤\n");
                    double amount;
                    loop3:
                    scanf("%lf",&amount);
                    if(amount>p_node[n]->amount){
                        printf("数量超过库存限制(库存只有%.1lf斤)\n",p_node[n]->amount);
                        printf("请重新输入：\n");
                        goto loop3;
                    }
                    p_node[n]->amount-=amount;
                    double sum=amount*p_node[n]->price;

                    //以下代码保存购买的物品
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
                    printf("购买成功！ 共花费%.1lf元\n",sum);
                    system("pause");

                }
                n++;
            }

        }
    }else{
        printf("没有找到您要的商品\n");
        printf("1:重新输入  0:返回系统\n");
        loop2:
        scanf("%s",ch);
        if(strcmp(ch,"1")==0)
            goto loop1;
        else if(strcmp(ch,"0")==0)
            return ;
        else{
            printf("无效输入，请重新输入：\n");
            goto loop2;
        }
    }
}

void item_purchased()
{
    printf("***************************已购商品信息如下***************************\n\n");
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
    printf("\n共消费:%.1lf元\n",sum_);
    system("pause");

}

void system_menu()
{
    while(true)//主体循环  便于重复进入
    {
        for (int i = 0; i < 51; i++) {
            putchar('*');
            Sleep(1);
        }
        printf("\n");
        printf("---------------------------------------------------\n");
        printf("|                 欢迎来到超市系统                |\n");
        printf("|*********   请键入数字 1 或 2 选择系统  *********|\n");
        printf("|*********      Number 1 ：顾客系统      *********|\n");
        printf("|*********      Number 2 ：管理系统      *********|\n");
        printf("|*********      Number 0 ：退出系统      *********|\n");
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
            printf("无效输入，请重新输入！\n");
            goto loop;
        }
    }
}



void system_customer()
{
    while(true)//与主菜单同理
    {
        system("cls");//每次进入系统就清屏  创造更好的视觉享受
        for (int i = 0; i < 55; i++) {//用于玩花的
            putchar('*');
        }
        printf("\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                ___欢迎来到顾客系统___               |\n");
        printf("|*********         请键入数字选择系统        *********|\n");
        printf("|*********       Number 1:商品展示系统       *********|\n");
        printf("|*********       Number 2:商品查询系统       *********|\n");
        printf("|*********       Number 3:商品购买系统       *********|\n");
        printf("|*********       Number 4:已购商品查询       *********|\n");
        printf("|*********       Number 0:退出顾客系统       *********|\n");
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
    if(!flag)//flag 用于判断是否输入了密码  如果成功输入即确认身份 后续进入管理系统便不再需要输入密码
    {
        system("cls");
        printf("\n\n");
        printf("**************** ————欢迎进入超市管理登录系统———— ****************");
        printf("\n\n\n");
        int count = 4;
        while (!password())
        {
            if (--count == 0)
            {
                printf("无剩余机会!\n");
                exit(0);
            }
            printf("密码错误!\n请重试：(还有%d次机会)\n", count);
        }
        flag=true;
        printf("密码正确!\n");
    }
    while(true)
    {
        system("cls");
        for (int i = 0; i < 55; i++) {
            putchar('*');
        }
        printf("\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                   欢迎来到管理系统                  |\n");
        printf("|*********         请键入数字选择系统        *********|\n");
        printf("|*********       Number 1:商品展示系统       *********|\n");
        printf("|*********       Number 2:商品查询系统       *********|\n");
        printf("|*********       Number 3:商品修改系统       *********|\n");
        printf("|*********       Number 4:商品添加系统       *********|\n");
        printf("|*********       Number 5:商品删除系统       *********|\n");
        printf("|*********       Number 6:商品排序系统       *********|\n");
        printf("|*********       Number 7:营业总额查询       *********|\n");
        printf("|*********       Number 8:管理密码修改       *********|\n");
        printf("|*********       Number 0:退出管理系统       *********|\n");
        printf("|-----------------------------------------------------|\n");
        for (int i = 0; i < 55; i++) {
            putchar('*');
        }
        printf("\n");
        char ch[100];
        loop://处理无效输入情况  强制跳转
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
            printf("无效输入，请重新输入:\n");
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
    printf("总的营业额为%.1lf\n",sum);
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