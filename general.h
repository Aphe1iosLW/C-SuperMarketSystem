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
void system_menu();//���˵�
void system_customer();//�˿�ϵͳ
void system_manager();//����Աϵͳ
void list_build();//������
void list_display();//������Ŀչʾ
void list_search_manager();//����Ա�汾��Ʒ����  �޹���ѯ��
void list_search_customer();//�˿Ͱ汾��Ʒ����  �й���ѯ��
void list_item_purchase();//�˿͹�����������
void list_item_add();//����µ���Ʒ
void list_item_delete();//ɾ�����е���Ʒ
void list_item_modify();//�޸�ԭ�е���Ʒ
void list_sort();//����ϵͳ  ���ò�������
void purchase_in_display();//��չʾ��Ŀ�й���
void item_purchased();//��ʾ�˿͹���Ķ���
void list_rewrite();//���޸ĺ����������д���ļ�
void volume_check();//��ѯӪҵ��
void volume_rewrite();//��ÿ���Ӫҵ����д���ļ�
void list_delete();//��������
void password_change();//�޸����루����ԱȨ�ޣ�
bool password();//������
#endif