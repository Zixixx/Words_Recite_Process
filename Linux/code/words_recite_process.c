#include"recite.h"
#include"recite.c"
#include"wordsbook.h"
#include"wordsbook.c"
#include"menu.h"
#include"menu.c"
#include"account.h"
#include"account.c"
#include"file.h"
#include"file.c"
int main()
{
	judge();
	Stu x;
	int flag[3],variable[3],i,j,num;
	do
	{
		printf("欢迎使用背单词系统!\n");
		menu_desktop();
		flag[0]=0;
		printf("请做出你的选择:\n");
		while(scanf("%d",&variable[0])!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		switch(variable[0])
		{
			case 0:
			    flag[0]=1;
			    break;
			case 1:
				regist();
				break;
			case 2:
				x=login();
				if(x.num==0)
				{
					break;
				}
				printf("欢迎您，%s\n",x.name);
				do
				{
					menu_logindesktop();
					flag[1]=0;
					printf("请做出你的选择:\n"); 
					while(scanf("%d",&variable[1])!=1)
					{
						printf("格式错误，请重新输入\n");
						getchar();
					}
					switch(variable[1])
					{
						case 0:
							flag[1]=1;
							break;
						case 1:
							record(x);
							break;
						case 2:
							prewords();
							break;
						case 3:
							do
							{
								menu_practice();
								flag[2]=0;
								printf("请做出你的选择:\n"); 
								while(scanf("%d",&variable[2])!=1)
								{
									printf("格式错误，请重新输入\n");
									getchar();
								}
								switch (variable[2])
								{
									case 0:
										flag[2]=1;
										break;
									case 1:
										do
										{
											printf("请输入需要练习的题目数（1-100）,输入0返回：\n");
											while(scanf("%d",&num)!=1)
											{
												printf("格式错误，请重新输入\n");
												getchar();
											}
											if(num==0)
											{
												break;
											}
											if(num<0||num>100)
											{
												printf("请输入正确的题目数\n");
												continue;
											}
											opt(x,num);
											break;
										} while (1);
										break;
									case 2:
										do
										{
											printf("请输入需要练习的题目数（1-100）,输入0返回：\n");
											while(scanf("%d",&num)!=1)
											{
												printf("格式错误，请重新输入\n");
												getchar();
											}
											if(num==0)
											{
												break;
											}
											if(num<1||num>100)
											{
												printf("请输入正确的题目数\n");
												continue;
											}
											spe(x,num);
											break;
										} while (1);
										break;
									default:
										printf("请做出正确的选择\n");
										break;
								}
							}while(flag[2]==0);
							break;
						case 4:
							do
							{
								menu_score();
								flag[2]=0;
								printf("请做出你的选择:\n"); 
								while(scanf("%d",&variable[2])!=1)
								{
									printf("格式错误，请重新输入\n");
									getchar();
								}
								switch (variable[2])
								{
									case 0:
										flag[2]=1;
										break;
									case 1:
										cheek(x);
										break;
									case 2:
										rescore(x);
										break;
									default:
										printf("请做出正确的选择\n");
										break;
								}
							} while (flag[2]==0);
							break;
						case 5:
							do
							{
								menu_wrong();
								flag[2]=0;
								printf("请做出你的选择:\n"); 
								while(scanf("%d",&variable[2])!=1)
								{
									printf("格式错误，请重新输入\n");
									getchar();
								}
								switch (variable[2])
								{
									case 0:
										flag[2]=1;
										break;
									case 1:
										revoption(x);
										break;
									case 2:
										revspell(x);
										break;
									default:
										printf("请做出正确的选择\n");
										break;
								}
							} while (flag[2]==0);
							break;
						default:
							printf("请做出正确的选择\n");
							break;
						}
				}while(flag[1]==0);
				break;
			case 3:
				if(settingjudge()==0)
				{
					break;
				}
				do
				{
					menu_systemsetting();
					flag[1]=0;
					printf("请做出你的选择:\n");
				    while(scanf("%d",&variable[1])!=1)
					{
						printf("格式错误，请重新输入\n");
						getchar();
					}
					switch (variable[1])
					{
						case 0:
							flag[1]=1;
						    break;
						case 1:
							do
							{
								menu_account();
								flag[2]=0;
								printf("请做出你的选择:\n"); 
								while(scanf("%d",&variable[2])!=1)
								{
									printf("格式错误，请重新输入\n");
									getchar();
								}
								switch (variable[2])
								{
									case 0:
										flag[2]=1;
										break;
									case 1:
										modacc();
										break;
									case 2:
										delacc();
										break;
									case 3:
										preacc();
										break;
									default:
										printf("请做出正确的选择\n");
										break;
								}
							}while (flag[2]==0);
							break;
						case 2:
							do
							{
								menu_wordsbook();
								flag[2]=0;
								printf("请做出你的选择:\n");
								while(scanf("%d",&variable[2])!=1)
								{
									printf("格式错误，请重新输入\n");
									getchar();
								}
								switch(variable[2])
								{
									case 0:
										flag[2]=1;
										break;
									case 1:
										addwords();
										break;
									case 2:
										modwords();
										break;
									case 3:
										delwords();
										break;
									case 4:
										prewords();
										break;
									default:
										printf("请做出正确的选择\n");
										break;
								}
							}while(flag[2]==0);
							break;
						case 3:
							backup();
							break;
						case 4:
							restore();
							break;
						case 5:
							if(refile()==1)
							{
								flag[1]=1;
							}
							break;
						case 6:
							modpassword();
							break;
						default:
							printf("请做出正确的选择\n");
							break;
					}
				} while (flag[1]==0);
				break;
			default:
				printf("请做出正确的选择\n");
				break;
		}
	}while(flag[0]==0);
	return 0;
}