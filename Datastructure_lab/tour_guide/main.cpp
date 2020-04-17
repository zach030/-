
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************�궨��***************************/

#define OK 1
#define MVNum 10             //��󶥵����
#define V 10
#define MaxInt 32767         //���޴�
#define MaxRoad 100
#define Extra 10             //�������Ӿ���

/*******************����ṹ��**************************/


typedef struct {
	char name[30];          //��������
	char number[10];        //�������
	char introduce[200];    //�������
}Info;

typedef struct {
	int num;			//��Ӧ����ı��
	Info data;			//�洢�������Ϣ
}View;

typedef struct {								//ͼ�Ľṹ
	View	   view[MVNum+Extra];						//������������
	int		   length[MVNum+Extra][MVNum+Extra];           //�ö�ά������ÿ���ߵ�Ȩֵ������·�ĳ���
}MGraph;


/***********************����һЩȫ�ֱ���*****************/

MGraph G;							//�洢��Ϣ��ͼ

int shortest[MVNum][MVNum];			//�洢���������·��

int path[MVNum][MVNum];				//�洢������·��

int visited[V]={0};               //��ʼ������,0Ϊδ����,1Ϊ�Ѿ�����

int stacks[120];                    //���·��������

int top=1;                          //ָ������Ķ���

int ends;                           //ȫ�ֱ��� ·���յ�

int ex=0;                           //�������µľ���

/********************���ú���***************************/

void drawMap();         //����ͼ����
void choose();          //��ת����
void init_info();       //��ʼ����Ϣ����
void Exit();            //��������
int shortdistance();    //���·��
void floyd();           //floyd�㷨�����·��
void display(int i,int j);//������·��
void AllPath(MGraph G,int start);//��ȫ��·��
void visitor();         //�οͳ�ʼ����
void PathInfo();        //����·��������ѡ��
void AddView();         //���Ӿ���
void DeleteView();      //ɾ������
void UpdateView();      //���¾���
void UpdateRoad();      //���µ�·
void manager();         //����Ա��������
void FirstPage();       //��ʼ����
void Check();           //��ӡ���Ӿ����ľ���ͼ

/*******************��ӡ��ͼ****************************/

void drawMap()
{
    int i;
        printf("                            ---------------------------*������*---------\n");
        printf("                            --------------------------------------------\n");
        printf("                            -----------*������*-------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            --*��Ӿ��*------------------------*��¥*----\n");
        printf("                            --------------------------------------------\n");
        printf("                            ---------*����¥*-------------*ͼ���*------\n");
        printf("                            --------------------------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            ----------------------------*�ٳ�*----------\n");
        printf("                            ---------*�ݷ�¥*---------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            ---------*����㳡*-------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            ----------------------------------*������*--\n");

    printf("\n\n����ɽ������Ĳ���:  1�������ο͵�½ϵͳ      2���������Ա��½ϵͳ     3���˳�����\n\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1: visitor();break;
        case 2: manager();break;
        case 3: Exit();break;
    }
}

/******************��ת����******************************/
void choose()
{
    int i;
    printf("����ɽ������Ĳ���:  1��������ҳ      2���˳�����\n");
    scanf("%d",&i);
	switch(i)
	{
	    case 1:FirstPage();break;
	    case 2:Exit();break;
	}
}

/*******************��ʼ����Ϣ**************************/
void init_info()
{
	int i, j;

	G.view[1].num = 1;
	strcpy(G.view[1].data.name, "������");
	strcpy(G.view[1].data.number, "001");
	strcpy(G.view[1].data.introduce, "λ��ѧУ���Ÿ�������һ����ƺ������Ϣ���ֵĺ�ȥ��");

	G.view[2].num = 2;
	strcpy(G.view[2].data.name, "������");
	strcpy(G.view[2].data.number, "002");
	strcpy(G.view[2].data.introduce, "һ�������ı���������������");

	G.view[3].num = 3;
	strcpy(G.view[3].data.name, "��Ӿ��");
	strcpy(G.view[3].data.number, "003");
	strcpy(G.view[3].data.introduce, "У԰�ڿ��ŵ�רҵ��Ӿ��");

	G.view[4].num = 4;
	strcpy(G.view[4].data.name, "����¥");
	strcpy(G.view[4].data.number, "004");
	strcpy(G.view[4].data.introduce, "У԰����ʦ�칫�ĳ���");

	G.view[5].num = 5;
	strcpy(G.view[5].data.name, "�ݷ�¥");
	strcpy(G.view[5].data.number, "005");
	strcpy(G.view[5].data.introduce, "�����ݷ�������½�ѧ¥");

	G.view[6].num = 6;
	strcpy(G.view[6].data.name, "����㳡");
	strcpy(G.view[6].data.number, "006");
	strcpy(G.view[6].data.introduce, "λ��ѧУ���ŵ�һ��Ƭ�㳡���ʺ�����");

	G.view[7].num = 7;
	strcpy(G.view[7].data.name, "������");
	strcpy(G.view[7].data.number, "007");
	strcpy(G.view[7].data.introduce, "У԰����ʩ��ȫ�������ݣ����ڽ��и��������");

	G.view[8].num = 8;
	strcpy(G.view[8].data.name, "�ٳ�");
	strcpy(G.view[8].data.number, "008");
	strcpy(G.view[8].data.introduce, "У԰�ڲ�Ψһһ�������С���˶��������˽��������˶�");

	G.view[9].num = 9;
	strcpy(G.view[9].data.name, "ͼ���");
	strcpy(G.view[9].data.number, "009");
	strcpy(G.view[9].data.introduce, "ͼ����ḻ����ѧ����ϰ�ĺ�ȥ��");

	G.view[10].num = 10;
	strcpy(G.view[10].data.name, "��¥");
	strcpy(G.view[10].data.number, "010");
	strcpy(G.view[10].data.introduce, "У԰����ʷ���ƾõĽ�������ѧУ�����ķ羰");

	for (i = 1; i <= V; i++)
		for (j = 1; j <= V; j++)
			G.length[i][j] = 0;       //��·�����ȳ�ʼ��

	G.length[1][2] = G.length[2][1]=3;             //����·������
	G.length[1][9] = G.length[9][1]=9;
	G.length[1][10] = G.length[10][1]=3;
	G.length[2][3] = G.length[3][2]=5;
	G.length[2][10] = G.length[10][2]=5;
	G.length[3][4] = G.length[4][3]=5;
	G.length[3][5] = G.length[5][3]=8;
	G.length[4][5] = G.length[5][4]=6;
	G.length[4][9] = G.length[9][4]=4;
	G.length[4][10] = G.length[10][4]=6;
	G.length[5][6] = G.length[6][5]=3;
	G.length[6][8] = G.length[8][6]=5;
	G.length[7][8] = G.length[8][7]=4;
	G.length[7][9] = G.length[9][7]=11;
	G.length[8][9] = G.length[9][8]=4;
	G.length[9][10] = G.length[10][9]=7;

    G.length[10][10]=G.length[1][1]=0;
    G.length[2][2]=G.length[3][3]=0;
    G.length[4][4]=0;
    G.length[5][5]=G.length[6][6]=0;
    G.length[7][7]=G.length[8][8]=0;
    G.length[9][9]=0;


}

void Exit()
{
    printf("\n              ���˳�����!");
    system("pause>null");
}
/*******************************�µľ���ͼ************************/
void Check()
{
    int i,j;
    printf("\n");
    for(i=1;i<=MVNum+ex;i++)
        for(j=1;j<=MVNum+ex;j++)
        {
            printf("%d\t",G.length[i][j]);
            if(j==MVNum+ex)
                printf("\n");
        }
    choose();
}
/********************************���·��*************************/

int shortdistance()
{                   //Ҫ���ҵ�����������·��
    int i,j;
    printf("������Ҫ��ѯ��������������ֱ���м��ÿո�����:\n");
    scanf("%d %d",&i,&j);
    floyd();
    display(i,j);
    return 0;
    fflush(stdin);
}

void floyd()                        //floyd�㷨
{
    int i,j,k;
    for(i=1;i<=V;i++)
    {
		for(j=1;j<=V;j++)           //����ά�����ʼ�����Ƚ��������ڵ�·����Ϊ���·��
		{
		    if(G.length[i][j]!=0)   //����������·������shorest()����Ϊ·��
			shortest[i][j]=G.length[i][j];
			else
            shortest[i][j]=MaxInt;  //��������û��·������shorest()��ΪMaxlnt
			path[i][j]=0;           //����path�����Ų��ϸ��µ����·�����ȳ�ʼ��Ϊ0
		}
    }                               //��ʼ������
    for(k=1;k<=V;k++)               //iΪ��ʼ�㣬jΪ�յ�,kΪ�м���ȵ�
		for(i=1;i<=V;i++)
			for(j=1;j<=V;j++)       //��������¶���ʹ�ø���
			{
				if(shortest[i][j]>(shortest[i][k]+shortest[k][j]))
				{
					shortest[i][j]=shortest[i][k]+shortest[k][j];
					path[i][j]=k;
					path[j][i]=k;       //kΪ�յ�ǰ���һ���㣬��Ŀǰ�����·����¼����
				}
			}
}


void display(int i,int j)           //��ӡ������������·��
{
    int k,temp=j;
    printf("��Ҫ��ѯ������������·���ǣ� \n\n");
    fflush(stdin);
    printf("%d",j);             //��ӡ�յ�
    while(path[i][j]!=0)        //���������path����
    {                               //i��������k-j,kΪ�յ�ǰ���һ����
        printf("<--%d",path[i][j]); //�ҵ�k�󣬼�����i��k֮������·��
        j=path[i][j];
    }
    printf("<--%d\n\n",i);
    printf("%d-->%d�����·����:%d��\n",i,temp,100*shortest[i][temp]);
	printf("��ѡ��������Ĳ���:      1��������һ����     2��������ҳ      3���˳�����\n\n");
	scanf("%d",&k);
	switch(k)
	{
	    case 1:PathInfo();break;
	    case 2:FirstPage();break;
	    case 3:Exit();break;
	}
}


/********************************����·��******************************/


void AllPath(MGraph G,int start)   //��ѯ����·��
{
    int j;
    visited[start]=1;              //����Ѿ��߹��ĵ�
    stacks[top]=start;             //������
    top++;
    if(start==ends)                //�����ҵ��յ�
    {
        for(j=1;j<top-1;j++)       //����������stacks�е�·����һһ���
           {
                printf("%d-->",stacks[j]);
           }
        printf("%d\n",ends);
    }
    for(j=1;j<=V;j++)              //��δ�ҵ��յ㣬��������
    {
        if(!visited[j]&&G.length[start][j]!=0)  //j��û�б����ʣ�����������·��
            AllPath(G,j);                       //j����Ϊ�µ�start�����еݹ�
    }
    visited[start]=0;              //jΪ�յ㣬ȡ�����ʱ�ǣ�����������һ��
    top--;                         //ջ��Ԫ�ظ�����һ

}



/***********************************�οͲ������򲿷�**********************/
void visitor()
{
	int i=0,j;
	printf("\n��ѡ����Ҫ�˽�ľ���:\n");
	for(i=1;i<=MVNum+ex;i++)
    {
        printf("%d��%s\t\t",i,G.view[i].data.name);
        if(i==(MVNum+ex)/2)
            printf("\n");
    }
	printf("\n\n��������:");
	scanf("%d",&i);
	fflush(stdin);
	printf("\n");
	for(j=1;j<=MVNum+ex;j++)
    {
        if(j==i)
        {
            printf("������:%d\n", G.view[j].num);
	        printf("��������:%s\n",G.view[j].data.name);
	        printf("������Ϣ:%s\n",G.view[j].data.introduce);
        }
    }
	printf("\n\n�������ɲ�����    1��·�����Ҳ���        2��������ҳ      3���˳�����\n");
	scanf("%d",&i);
	switch(i)
	{
	    case 1: PathInfo();break;
	    case 2: FirstPage();break;
	    case 3: Exit();break;
	}
}

void PathInfo()
{
    int i,v;
	printf("\n·�����Ҳ���:1����������������·��    2�����������������·��\n\n��������:");
	scanf("%d",&i);
	fflush(stdin);
	switch(i)
	{
        case(1):
            shortdistance();
            break;
        case(2):
            printf("���������:");
            scanf("%d",&v);
            printf("�������յ�:");
            scanf("%d",&ends);
            AllPath(G,v);
            break;
	}
    choose();
}

/**************************����Ա��������************************/

void AddView()//���Ӿ������
{
    int i,k,j,way;
    char name[20];
    char number[20];
    char introduce[20];
    printf("������Ҫ���ӵľ������:"); //����k������
    scanf("%d",&k);
    ex+=k;
    for(i=1;i<=k;i++)                   //ͨ��k��ѭ�����������ľ���
    {
        printf("������������ӵľ������Ϣ:\n");
        G.view[MVNum+i].num=MVNum+i;

        printf("�����뾰����:");
        scanf("%s",number);
        strcpy(G.view[MVNum+i].data.number, number);
        printf("\n");

        printf("�����뾰������:");
        scanf("%s",name);
        strcpy(G.view[MVNum+i].data.name, name);
        printf("\n");

        printf("�����뾰�����:");
        scanf("%s",introduce);
        strcpy(G.view[MVNum+i].data.introduce,introduce);
        printf("\n");

        while(1)
        {
            printf("������������·�����Ӷ���(�����Ӿ���Ϊ0�����������):");
            scanf("%d",&j);
            if(j!=0)
            {
                printf("\n������·��:(%d,%d)=",MVNum+i,j);
                scanf("%d",&way);
                G.length[MVNum+i][j]=way;
                G.length[j][MVNum+i]=way;
                printf("\n");
            }
            else
                break;
        }
        printf("��%d��������Ϣ�Ѳ���������\n\n",i);
    }
    printf("��ѡ�����:  1���鿴�µľ������ͼ     2������\n");
    scanf("%d",&i);
    switch (i)
    {
        case 1:Check();break;
        case 2:choose();break;
    }
}

void UpdateView()
{
    int i,n;
    char name[20];
    char k[10];
    char introduce[20];
    printf("��������Ҫ���µľ�����:");
    scanf("%d",&i);
    printf("��ѡ����Ҫ���µ�����:1������     2������       3������\n");
    scanf("%d",&n);
    switch(n)
    {
        case(1):
            {
                printf("�������µĴ���:");
                scanf("%s",k);
                strcpy(G.view[i].data.number, k);
                printf("������Ϣ�Ѹ��£�\n");
            }
            break;
        case(2):
            {
                printf("����¾�������:");
                scanf("%s",name);
                strcpy(G.view[i].data.name, name);
                printf("������Ϣ�Ѹ��£�\n");
            }
            break;
        case(3):
            {
                printf("����¾������:");
                scanf("%s",introduce);
                strcpy(G.view[i].data.introduce,introduce);
                printf("\n������Ϣ�Ѹ��£�\n");
            }
            break;
        default:
            printf("����������!\n");
    }
	choose();
}

void UpdateRoad()
{
    int i,j,l;
    printf("��������Ҫ���µ�·�������������ţ�:");
    scanf("%d %d",&i,&j);
    fflush(stdin);
    printf("�������µ���Ϣ:");
    scanf("%d",&l);
    G.length[i][j]=l;
    printf("��·��Ϣ�Ѹ������!");
    choose();
}

void DeleteView()
{
    //ɾ������i
    int n;
    printf("������Ҫɾ���ľ�����:");
    scanf("%d",&n);
    strcpy(G.view[n].data.name,"��ɾ��");
    strcpy(G.view[n].data.number,"��ɾ��");
    strcpy(G.view[n].data.introduce,"��ɾ��");
    printf("\n�þ�����Ϣ��ɾ��!\n");
    choose();
}

void manager()//���ӡ�ɾ�������¾��㼰��·��Ϣ
{
    int i;
    printf("\n��ӭ�������Ա����ϵͳ����ѡ����Ҫ��ɵ�����:\n\n1�����Ӿ���     2��ɾ������      3�����¾�����Ϣ        4�����µ�·��Ϣ\n\n");
    printf("\n��������:");
    scanf("%d",&i);
    switch(i)
    {
        case 1:AddView();break;
        case 2:DeleteView();break;
        case 3:UpdateView();break;
        case 4:UpdateRoad();break;
    }
}



/*******************��������һ����********************/



void FirstPage()
{
	int i;
	printf("                            |********************************************|\n");
	printf("                            |*         ��ӭ������ũУ԰����ϵͳ         *|\n");
	printf("                            |*            1�������ο͵�½ϵͳ           *|\n");
	printf("                            |*            2�����������Աϵͳ           *|\n");
	printf("                            |*            3����ӡ��ͼ                   *|\n");
	printf("                            |*            4���˳�ϵͳ                   *|\n");
	printf("                            |********************************************|\n");
	printf("\n                                   ��������Ҫѡ��Ĳ���:");
	scanf("%d", &i);
	switch (i)
	{
	case 1: visitor(); break;
	case 2: manager(); break;
	case 3: drawMap();break;
	case 4: Exit();
	}
	system("pause>null");
}

/******************************������**************************/
int main()
{
    init_info();
    FirstPage();
	return 0;
}

