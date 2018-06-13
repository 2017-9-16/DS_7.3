//
//  main.cpp
//  DS_7.3
//
//  Created by Walter Mitty on 2018/6/12.
//  Copyright © 2018年 Walter Mitty. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define max 10
//#define vertexnum 5
typedef struct list{ //结构定义
    int vertex1;
    int vertex2;
    int weight;
    struct list *next;
}Node; //定义邻接边的结点
typedef Node *edge;
int edges[10][3]={    {1,2,7},{1,3,6},{1,4,5},{1,5,12},{2,3,14},
    {2,4,8},{2,5,8},{3,4,3},{3,5,9},{4,5,2}        }; //针对图G3的结点数据以及权值

void kruskal(edge head,int visited[],int c){
    edge pointer;
    int edgenum=0; //已连结边的数目
    int weight=0;
    pointer=head;
    while(edgenum!=(c-1)){//当边的数目为顶点数少1时，结束循环
        if(visited[pointer->vertex1]==0||visited[pointer->vertex2]==0){
            printf(" ==>[%d,%d] ",pointer->vertex1,pointer->vertex2);
            printf("(%d)",pointer->weight);
            weight+=pointer->weight;
            edgenum++;
            visited[pointer->vertex1]=1; //设为已访问
            visited[pointer->vertex2]=1;
        }
        pointer=pointer->next; //下一个结点
        if(pointer==NULL){
            printf("no tree!\n");
            break;
        }
    }
    printf("\n\ntotal weight is: %d",weight);//输出加权值总和
}
void print_edge(edge head){ //输出链表数据
    edge pointer;
    pointer=head;
    while( pointer!=NULL){ //当结点为NULL时结束循环
        printf("[%d,%d] ",pointer->vertex1,pointer->vertex2);
        printf("(%d) \n",pointer->weight);//输出权值
        pointer=pointer->next;
    }
    printf("\n");
}
edge insert_edge(edge head,edge new_p){//插入邻接边到链表内
    edge pointer,pre;
    pointer=head; //pointer设为首结点
    if(new_p->weight<head->weight){//新的加权值比首结点值小
        new_p->next=head; //插入在首结点之前
        head=new_p;
    }
    else{
        while(pointer&&new_p->weight>=pointer->weight){
            pre=pointer;
            pointer=pointer->next;
        }
        new_p->next=pointer;
        pre->next=new_p;
    }
    return head;
}
void free_edge(edge head){
    edge pointer;
    while(head!=NULL){
        pointer=head;
        head=head->next;
        free(pointer);
    }
}
edge create_edge(edge head,int edgess[][3],int c){ //建立链表
    edge new_p;
    int i;
    head=(edge)malloc(sizeof(Node));
    if(head==NULL)
        printf("memory failure! ");
    else{
        head->vertex1=edgess[0][0];
        printf("%d",head->vertex1);
        
        head->vertex2=edgess[0][1];
        head->weight=edgess[0][2];
        head->next=NULL;
        for(i=1;i<((c-1)*c)/2;i++){
            new_p=(edge)malloc(sizeof(Node));
            if (new_p!=NULL){
                new_p->vertex1=edgess[i][0]; //定义结点加权值
                new_p->vertex2=edgess[i][1];
                new_p->weight=edgess[i][2];
                new_p->next=NULL;
                head=insert_edge(head,new_p); //插入新结点
            }
        }
    }
    return head;
}
int main(){
    edge head=NULL;
    int i,j;
    int c,visited[c];
    printf("请输入城市个数\n");
    
    scanf("%d",&c);
    int edgess[(c*(c-1))/2][3];
    int position[c][2];
    printf("please input the position of cities\n");
    for (i=0; i<c; i++) {
        scanf("%d%d",&position[i][0],&position[i][1]);
        getchar();
    }
    /*for (i=0; i<c; i++) {
        printf("%d\t",position[i][0]);
        
    }*/
    for (i=0; i<c; i++) {
        for (j=1; j<c; j++) {
            double x1=position[i][0];
            double y1=position[i][1];
            double x2=position[j][0];
            double y2=position[j][1];
            int  d=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
            if (i==j) {
                break;
            }
            
            edgess[j-1][0]=i+1;
            printf("%d\t",i+1);
            edgess[j-1][1]=j+1;
            printf("%d\t",j+1);
            edgess[j-1][2]=d;
            printf("%d\n",d);
        }
    }
    
    
    for (i=0;i<c;i++) //对所有的访问顶点清0
        visited[i]=0;
    head=create_edge(head,edgess,c); //调用建立链表
    if (head!=NULL){
        printf("\nfirst step: sorting.\n");
        print_edge(head);
        printf("\nsecond step: find the lest tree.\n");
        kruskal(head,visited,c); //调用克鲁期卡尔算法
        free_edge(head);
    }
    printf("\n\n");
    for (i=0; i<c; i++) {
        printf("%d,%d\t",edgess[i][0],edgess[i][1]);
        
    }
    
}

