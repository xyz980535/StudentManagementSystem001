/*学生管理系统*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#define StuPW "StuPWInfo.txt"
#define TeaPW "TeaPWInfo.txt"
#define StuInfo "StuAllInfo.txt"

typedef struct Stu
{
	char id[20];		//学号
	char name[20];		//姓名
	char sex[10];		//性别
	int age;			//年龄
	int cp;		        //C语言
	int en;		        //英语
	int math;	        //高数 
	double avg;			//平均分
}Student;

typedef struct node
{
	Student stu;
	struct node *next;//用来保存下一个节点的地址
}Node;

//学生的注册信息
typedef struct User_1
{
	char identity[20];//账号
	char password[20];//密码
	struct User_1 *next;//后面需要用到 
} User_1;

//教师的注册信息
typedef struct User_2
{
	char identity[20];//账号
	char password[20];//密码
	struct User_2 *next;
} User_2;
int  N = 0;//用来统计学生信息文件中共有多少个学生
void stuLookInfo();
void stuModifyInfo();
void stuLookScore();
void stuLoMenu();
void login();
void mainMenu();
void registers();
void teaLoMenu();
void input();
void displayAll();
void displayOne();
void modifyStudent();
void deleteStudent();
void addStudent();
void saveData1();
void saveData2();
Node *read();
void freeMemory();
void sort();
void saveData3();
User_1 *readStuPW(); 
Node *head=NULL;//全局指针变量
User_1 *head1=NULL;//全局指针变量用来指向学生注册信息 
char id[20] = "000";//全局变量用来标记现在是谁在操作
char g_password[20]="0000";//用来保存操作者的登陆密码 

void mainMenu()
{
	int i;				//序号
	while(1)
	{
		printf("\n*****************************************\n");
		printf("\n**       1.注册                        **\n");
		printf("\n**       2.登录                        **\n");
		printf("\n**       0.退出                        **\n");
		printf("\n*****************************************\n");
		printf("\n请选择");
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			system("cls");
			registers();
			break;
		case 2:
			system("cls");
			login();
			break;
		case 0:
			printf("谢谢使用!");
			Sleep(1000);//推迟0.5s
			exit(0);
		default:
			break; 
		}
		system("cls");
	}
}

void login()
{
	User_1 *user1 = (User_1*)malloc(sizeof(User_1));
	User_2 *user2 = (User_2*)malloc(sizeof(User_2));
	char identity[20];
	char password[20];
	int i;
	FILE *fp1 = fopen(StuPW,"rb");
	FILE *fp2 = fopen(TeaPW, "rb");
	if (fp1 == NULL)
	{
		printf("打开文件错误");
		return;
	}
	if (fp2 == NULL)
	{
		printf("打开文件错误");
		return;
	}

	printf("\n*****************************************\n");
	printf("\n**       1.学生登录                     **\n");
	printf("\n**       2.教师登录                     **\n");
	printf("\n**       0.返回上级菜单                 **\n");
	printf("\n*****************************************\n");
	printf("\n请选择");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		printf("------学生登录------\n");
		printf("请输入学生账号：");
		scanf("%s", identity);
		printf("请输入学生密码：");
		scanf("%s", password);
		while (1)
		{ 
			fread(user1, sizeof(User_1), 1, fp1);
			if(feof(fp1))
			{
				break;//fread得这样写 
			}
			if (strcmp(user1->identity, identity) == 0 && strcmp(user1->password, password) == 0)
			{
				printf("登录成功");
				strcpy(id, identity);//保存现在是哪个学生在操作
				strcpy(g_password,password); //保存该学生的密码 
				free(user1);
				fclose(fp1);
				Sleep(1000);
				system("cls");
				stuLoMenu();
			}
		}
		printf("在数据库中未找到该账号或密码\n");
		Sleep(1000);
		break;
	case 2:
		printf("------教师登录------\n");
		printf("请输入教师账号：");
		scanf("%s", identity);
		printf("请输入教师密码：");
		scanf("%s", password);
		while (1)
		{
			fread(user2, sizeof(User_2), 1, fp2);
			if(feof(fp2))
			{
				break;
			}
			if (strcmp(user2->identity, identity) == 0 && strcmp(user2->password, password) == 0)
			{
				printf("登录成功");
				free(user2);
				fclose(fp2);
				Sleep(1000);
				teaLoMenu();
				return;
			}
		}
		printf("在数据库中未找到该账号或密码\n");
		Sleep(1000);
		break;
	case 0:
		system("cls");
		mainMenu();
		break;
	default:
		break;
	}
}

void stuLookInfo()//查看基本信息
{
	printf("------------基本信息----------------\n\n");
	printf("学号\t姓名\t性别\t年龄\t\n");
	Node *p = read();
	printf("-------------------------------------\n");
	while (p != NULL)
	{
		if (strcmp(p->stu.id, id) == 0)
		{
			printf("%s\t%s\t%s\t%d\t\n", p->stu.id, p->stu.name, p->stu.sex, p->stu.age);
			break;//找到该节点
		}

		p = p->next;    //移向下一个节点
	}
	system("pause");
}


void stuModifyInfo()//修改基本信息
{
	char password[20];//输入需要改的登陆密码 
	printf("------------修改基本信息-----------\n");
	printf("\n*****************************************\n");
	printf("\n**       1.修改姓名                     **\n");
	printf("\n**       2.修改年龄                     **\n");
	printf("\n**       3.修改性别                     **\n");
	printf("\n**       4.修改登陆密码                 **\n");
	printf("\n**       0.返回上一级菜单                **\n");
	printf("\n*****************************************\n");
	printf("\n请选择");
	Node *p = read();
	while (p != NULL)
	{
		if (strcmp(p->stu.id, id) == 0)
		{
			break;//找到该节点
		}
		p = p->next;
	}
	int i;
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		printf("请修改你的姓名：");
		scanf("%s", p->stu.name);
		printf("修改成功\n");
		saveData1();
		printf("3s后返回上级菜单"); 
		Sleep(3000);
		system("cls");
		stuModifyInfo();
		break;
	case 2:
		printf("请修改你的年龄：");
		scanf("%d", &(p->stu.age));
		printf("修改成功\n");
		saveData1();//保存数据 
		printf("3s后返回上级菜单");
		Sleep(3000);
		system("cls");
		stuModifyInfo();
		break;
	case 3:
		printf("请修改你的性别：");
		scanf("%s", p->stu.sex);
		printf("修改成功\n");
		saveData1();//保存数据 
		printf("3s后返回上级菜单");
		Sleep(3000);
		system("cls");
		stuModifyInfo();
		break;
	case 4:
		printf("请修改你的登陆密码：");
		scanf("%s",password); 
		User_1 *p = readStuPW();
		while(p!=NULL)
		{
			if(strcmp(p->identity,id)==0)
			{
				strcpy(p->password,password);//先找到 然后改变值 
				break;
			}
			p=p->next;
		}
		printf("修改成功\n");
		saveData3();
		printf("3s后返回上级菜单");
		Sleep(3000);
		system("cls");
		mainMenu();//回到主菜单 
		break;	
	case 0:
		system("cls");
		stuLoMenu();
	default :
		break; 
	}
	
}

void stuLookScore()//查看各科成绩 
{
	Node *p = read();
	printf("-----------查看各科成绩--------------\n");
	printf("学号\tC语言\t英语\t高数\t平均分\t\n");
	printf("-------------------------------------\n");
	while (p != NULL)
	{
		if(strcmp(p->stu.id,id)==0)
		{
			printf("%s\t%d\t%d\t%d\t%.1f\t\n", p->stu.id,p->stu.cp, p->stu.en, p->stu.math, p->stu.avg);
			break;//结束 
		}
		p = p->next;    //移向下一个节点
	}
	system("pause");
	stuLoMenu();
}

 
void stuLoMenu()//学生登录后菜单
{
	printf("\n*****************************************\n");
	printf("\n**       1.查看基本信息                  **\n");
	printf("\n**       2.修改基本信息                  **\n");
	printf("\n**       3.查看各科成绩                  **\n");
	printf("\n**       0.返回上级菜单                  **\n");
	printf("\n*****************************************\n");
	printf("\n请选择");
	int i;//序号
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		stuLookInfo();
		system("cls");
		stuLoMenu();
		break;
	case 2:
		stuModifyInfo();
		system("cls");
		stuLoMenu();
		break;
	case 3:
		stuLookScore();
		system("cls");
		stuLoMenu();
		break;
	case 0:
		system("cls");
		login();
		break;
	default:
		break;
	}
}
void teaLoMenu()//教师登录后的菜单
{
	printf("\n*****************************************\n");
	printf("\n**       1.录入学生数据                  **\n");
	printf("\n**       2.显示所有学生信息               **\n");
	printf("\n**       3.显示/查询单个学生信息          **\n");
	printf("\n**       4.修改学生信息                  **\n");
	printf("\n**       5.删除学生信息                  **\n");
	printf("\n**       6.增加学生信息                  **\n");
	printf("\n**       7.排序                         **\n");
	printf("\n**       0.返回上级菜单                  **\n");
	printf("\n*****************************************\n");
	printf("\n请选择");
	int i;
	scanf("%d", &i);//输入序号
	fflush(stdin);
	switch (i)
	{
	case 1:
		//system("cls");
		input();
		break;
	case 2:
		displayAll();
		system("pause");
		system("cls");
		teaLoMenu();
		break;
	case 3:
		displayOne();
		system("pause");
		system("cls");
		teaLoMenu();
		break;
	case 4:
		modifyStudent();
		system("pause");
		system("cls");
		teaLoMenu();
		break;
	case 5:
		deleteStudent();
		system("pause");
		system("cls");
		teaLoMenu();
		break;
	case 6:
		addStudent();
		system("pause");
		system("cls");
		teaLoMenu();
		break;
	case 7:
		sort();
		system("pause");
		system("cls");
		teaLoMenu();
		break;
	case 0:
		login();
		break;
	default:
		break;

	}
}
void registers()
{
	User_1 *user1 = (User_1*)malloc(sizeof(User_1));
	User_2 *user2 = (User_2*)malloc(sizeof(User_2));
	int flag = 1;//默认为真,继续输入
	char identity[20];//用来输入账号
	char password[20];//用来输入密码
	int i;//序号
	FILE *fp1 = fopen(StuPW, "ab+");
	FILE *fp2 = fopen(TeaPW, "ab+");
	printf("\n*****************************************\n");
	printf("\n**       1.学生注册                     **\n");
	printf("\n**       2.教师注册                     **\n");
	printf("\n**       0.返回上级菜单                 **\n");
	printf("\n*****************************************\n");
	printf("\n请选择");
	scanf("%d", &i);
	fflush(stdin);
	switch (i)
	{
	case 1:
		if (fp1 == NULL)
		{
			printf("无法打开学生账号密码文件");
			return;
		}
		while (flag)
		{
			printf("------学生注册------\n");
			printf("请输入学生账号：");
			scanf("%s", identity);
			printf("请输入学生密码：");
			scanf("%s", password);
			fflush(stdin);//清理缓存
			rewind(fp1);//回到文件开头
			while (1)//遍历下，当数据库中存在该用户时，不允许注册
			{
				fread(user1, sizeof(User_1), 1, fp1);
				if(feof(fp1)) 
				{
					break;
				}
				if (strcmp(user1->identity, identity) == 0)
				{
					printf("该用户已经存在,请重新输入\n");
					Sleep(1000);
					system("cls");
					flag = 1;
					break;
				}
				else
					flag = 0;
			}
			
		}
	
		strcpy(user1->identity, identity);//进行复制
		strcpy(user1->password, password);//进行复制
		fwrite(user1, sizeof(User_1), 1, fp1);
		fclose(fp1);//关闭文件
		printf("注册成功,3秒后回到主界面");
		Sleep(3000);
		break;
	case 2:
		flag = 1;
		if (fp2 == NULL)
		{
			printf("无法打开教师账号密码文件");
			return;
		}
		while (flag)
		{
			printf("------教师注册------\n");
			printf("请输入教师账号：");
			scanf("%s", identity);
			printf("请输入教师密码：");
			scanf("%s", password);
			fflush(stdin);//清理缓存
			while (1)//遍历下，当数据库中存在该用户时，不允许注册
			{
				
				if(feof(fp2))
				{
					break;
				}
				fread(user2, sizeof(User_2), 1, fp2);
				if (strcmp(user2->identity, identity) == 0)
				{
					printf("该用户已经存在\n");
					Sleep(1000);
					system("cls");
					mainMenu();
					//flag = 1;
					break;
				}
					
			}
			flag = 0;
		}
		strcpy(user2->identity, identity);//进行复制
		strcpy(user2->password, password);//进行复制
		fwrite(user2, sizeof(User_1), 1, fp2);
		fclose(fp2);//关闭文件
		printf("注册成功,3秒后回到主界面");
		Sleep(3000);
		break;
	case 0:
		system("cls");
		mainMenu();
		break;
	default:
		break;
	}
	free(user1);//释放这两个结点
	free(user2);//释放这两个结点
}

void input()
{
	int n;
	Node *p1, *p2;
	n = 0;
	p1 = p2 = (Node*)malloc(sizeof(Node));//生成一个结点，生成链表用于保存数据
	system("pause");
	printf("如果想停止输入，则学号处输入#\n");
	printf("增加第%d个学生信息\n", n + 1);
	printf("学生的学号：");
	scanf("%s", p1->stu.id);
	printf("学生的的姓名：");
	scanf("%s", p1->stu.name);
	printf("学生的年龄：");
	scanf("%d", &(p1->stu.age));
	printf("学生的性别：");
	scanf("%s", p1->stu.sex);
	printf("学生的C语言成绩：");
	scanf("%d", &(p1->stu.cp));
	printf("学生的的数学成绩：");
	scanf("%d", &(p1->stu.math));
	printf("学生的英语成绩：");
	scanf("%d", &(p1->stu.en));
	fflush(stdin);
	p1->stu.avg = (p1->stu.en + p1->stu.cp + p1->stu.math) / 3.0;//平均
	head = NULL;
	while (1)
	{
		if (strcmp(p1->stu.id, "#") == 0)
		{
			break;//当输入是#时，终止输入
		}
		n = n + 1;
		if (n == 1)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (Node*)malloc(sizeof(Node));
		system("cls");
		printf("如果想停止输入，则学号处输入#\n");
		printf("增加第%d个学生信息\n", n + 1);
		printf("学生的学号：");
		scanf("%s", p1->stu.id);
		if (strcmp(p1->stu.id, "#") == 0)
		{
			break;//当输入是#时，终止输入
		}
		fflush(stdin);
		printf("学生的的姓名：");
		scanf("%s", p1->stu.name);
		printf("学生的年龄：");
		scanf("%d", &(p1->stu.age));
		printf("学生的的性别：");
		scanf("%s", p1->stu.sex);
		printf("学生的C语言成绩：");
		scanf("%d", &(p1->stu.cp));
		printf("学生的的数学成绩：");
		scanf("%d", &(p1->stu.math));
		printf("学生的英语成绩：");
		scanf("%d", &(p1->stu.en));
		p1->stu.avg = (p1->stu.en + p1->stu.cp + p1->stu.math) / 3.0;//平均
		fflush(stdin);
	}
	p2->next = NULL;
	saveData2();
	system("cls");
	teaLoMenu();
}

void displayOne()
{

	int i;
	int n;//用来遍历到所需的节点之前共遍历了多少个节点 
	char id[20];
	char name[20];
	Node *p = read();
	printf("\n*****************************************\n");
	printf("\n**       1.学号查找                     **\n");
	printf("\n**       2.姓名查找                    **\n");
	printf("\n**       0.返回上级菜单                 **\n");
	printf("\n*****************************************\n");
	printf("\n请选择");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		n=0; 
		printf("请输入学号：");
		scanf("%s", id);
		while (p != NULL)
		{
			if (strcmp(p->stu.id, id) == 0)
			{
				printf("学号           姓名         性别   年龄   C语言   英语   高数   平均分\n");
				printf("----------------------------------------------------------------------\n");
				printf("%-15s%-14s%-7s%-7d", p->stu.id, p->stu.name, p->stu.sex, p->stu.age);
				printf("%-7d%-7d%-7d%4.1f\n", p->stu.cp, p->stu.en, p->stu.math, p->stu.avg);
				printf("----------------------------------------------------------------------\n");
			    break;//找到就停止遍历 
			}
			n++;
			p = p->next;
		}
		if(n==N)
			printf("不好意思没有找到\n");
		system("pause");
		displayOne();
		break;
	case 2:
		n=0;//初始化 
		printf("请输入查找的姓名：");
		scanf("%s", name);
		while (p != NULL)
		{
			if (strcmp(p->stu.name, name) == 0)
			{
				printf("学号           姓名         性别   年龄   C语言   英语   高数   平均分\n");
				printf("----------------------------------------------------------------------\n");
				printf("%-15s%-14s%-7s%-7d", p->stu.id, p->stu.name, p->stu.sex, p->stu.age);
				printf("%-7d%-7d%-7d%4.1f\n", p->stu.cp, p->stu.en, p->stu.math, p->stu.avg);
				printf("----------------------------------------------------------------------\n");
			    break;//找到就停止遍历 
			}
			p = p->next;
		}
		if(n==N)
			printf("不好意思没有找到\n");
		system("pause");
		displayOne();
		break;
	case 0:
		system("cls");
		teaLoMenu();
	default:
		break;
	}
}
void modifyStudent()
{
	printf("正在完善该功能");
	system("pause");
}
void deleteStudent()
{
	printf("正在完善该功能");
	system("pause");
}
void addStudent()
{
	printf("正在完善该功能");
	system("pause");

}
void sort()
{
	printf("该功能正在完善\n");
	system("pause");
}

void saveData2()//不需要清除原始数据
{
	FILE *fp3 = fopen(StuInfo, "ab+");//不需要擦除前面的数据
	Node *p = head;
	if (fp3 == NULL)
	{
		printf("无法打开该文件\n");
		return;
	}
	while (p != NULL)
	{
		fwrite(p, sizeof(Node), 1, fp3);
		p = p->next;
	}
	fclose(fp3);
	printf("写入数据完成\n");
	printf("3秒钟后返回\n");
	freeMemory();//释放内存
	Sleep(3000);
}

void saveData1()//需要清除原始数据
{
	FILE *fp3 = fopen(StuInfo,"wb");//可以擦除之前的数据
	Node *p = head;
	if (fp3 == NULL)
	{
		printf("无法打开该文件\n");
		return;
	}
	while (p != NULL)
	{
		fwrite(p, sizeof(Node), 1, fp3);
		p = p->next;
	}
	fclose(fp3);
	printf("写入数据完成\n");
	printf("3秒钟后返回\n");
	freeMemory();//释放内存
	Sleep(3000);
}


void displayAll()
{
	Node *p = read();//读入数据
	if (p == NULL)
	{
		printf("没有数据");
		return;
	}
	printf("学号           姓名         性别   年龄   C语言   英语   高数   平均分\n");
	printf("----------------------------------------------------------------------\n");
	while (p != NULL)
	{
		printf("%-15s%-14s%-7s%-7d", p->stu.id, p->stu.name, p->stu.sex, p->stu.age);
		printf("%-7d%-7d%-7d%4.1f\n", p->stu.cp, p->stu.en, p->stu.math, p->stu.avg);
		p = p->next;    //移向下一个节点
	}
	printf("----------------------------------------------------------------------\n");
	freeMemory();
}


Node *read()
{
	int i;
	Node *p = (Node *)malloc(sizeof(Node));
	head = p;
	N=0;//初始化为0 
	Node *temp=NULL;//解决多了一个结点的问题 
	FILE *fp1 = fopen(StuInfo, "rb");
	if (fp1 == NULL)
	{
		printf("打开文件失败\n");
		return NULL;
	}
	while(1)
	{
		fread(p, sizeof(Node), 1, fp1);
		if (feof(fp1))//因为fread的原因，必须得这样，先读再判断 
	    {
	        break;
	    }
		Node *q = (Node *)malloc(sizeof(struct node));
		p->next = q;
		temp = p;
		p = q;
		N++;//统计有多少个学生信息
	}
	fclose(fp1);//关闭文件
	if (N == 0)
	{
		printf("文件中没有数据");
		return NULL;//代表着文件没有数据,关闭
	}
	temp->next = NULL;//temp用上场了
	return head;
}
int main()
{
	mainMenu();
	return 0;
}

void freeMemory()
{
	Node *p = head;
	Node *temp;
	while (p != NULL)
	{
		temp = p;
		p = p->next;
		free(temp);
	}
}
User_1 *readStuPW()
{
	int i;
	User_1 *p = (User_1 *)malloc(sizeof(User_1));
	head1 = p;
	N=0;//初始化为0 
	User_1 *temp=NULL;//解决多了一个结点的问题 
	FILE *fp1 = fopen(StuPW, "rb");
	if (fp1 == NULL)
	{
		printf("打开文件失败\n");
		return NULL;
	}
	while(1)
	{
		fread(p, sizeof(User_1), 1, fp1);
		if (feof(fp1))//因为fread的原因，必须得这样，先读再判断 
	    {
	        break;
	    }
		User_1 *q = (User_1 *)malloc(sizeof(User_1));
		p->next = q;
		temp = p;
		p = q;
		N++;//统计有多少个学生信息
	}
	fclose(fp1);//关闭文件
	if (N == 0)
	{
		printf("文件中没有数据");
		return NULL;//代表着文件没有数据,关闭
	}
	temp->next = NULL;//temp用上场了
	return head1;
}
void saveData3()//用来保存需要写入到stuPW的数据 
{
	FILE *fp3 = fopen(StuPW,"wb");//可以擦除之前的数据
	User_1 *p = head1;
	if (fp3 == NULL)
	{
		printf("无法打开该文件\n");
		return;
	}
	while (p != NULL)
	{
		fwrite(p, sizeof(User_1), 1, fp3);
		p = p->next;
	}
	fclose(fp3);
	printf("写入数据完成\n");
	printf("3秒钟后返回\n");
	Sleep(3000);
} 

