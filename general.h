#ifndef SUPERMARKET_GENERAL_H
#define SUPERMARKET_GENERAL_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include<windows.h>

struct goods
{
    char name[30];
    char level[30];
    char  category[30];
    double price;
    double amount;
    struct goods * next;
};

typedef struct goods Node;
void system_menu();//主菜单
void system_customer();//顾客系统
void system_manager();//管理员系统
void list_build();//链表创建
void list_display();//链表条目展示
void list_search_manager();//管理员版本商品搜索  无购买询问
void list_search_customer();//顾客版本商品搜索  有购买询问
void list_item_purchase();//顾客购买搜索函数
void list_item_add();//添加新的商品
void list_item_delete();//删除旧有的商品
void list_item_modify();//修改原有的商品
void list_sort();//排序系统  采用插入排序
void purchase_in_display();//在展示条目中购买
void item_purchased();//显示顾客购买的东西
void list_rewrite();//把修改后的链表重新写入文件
void volume_check();//查询营业额
void volume_rewrite();//把每天的营业额重写入文件
void list_delete();//链表销毁
void password_change();//修改密码（管理员权限）
bool password();//密码检查
#endif