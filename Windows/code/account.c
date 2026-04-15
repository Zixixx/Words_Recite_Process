#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"account.h"
#include"file.h"
#include"menu.h"
void regist()
{
	FILE *fp;
	fp=fopen("./system/user.dat","rb+");
	Stu a,b;
	char ensure[16];
	int i=0,j,step=0,flag;
	do{
		switch (step)
			{
				case 0:
				case 1:
					do
					{
						flag=0;
						printf("账户注册：\n请输入您的帐号,输入0返回上一级\n");
						scanf("%s",a.account);
						if(a.account[0]=='0'&&strlen(a.account)==1)
						{
							return;
						}
						while(fread(&b,sizeof(Stu),1,fp)==1)
						{
							if(strcmp(a.account,b.account)==0)
							{
								printf("该账号已被注册，请输入新账号\n");
								flag=1;
								break;
							}
						}
						rewind(fp);
					}while(flag==1);
					step=0;
					break;
				default:
					break;
			}
		switch (step)
		{
			case 0:
			case 2:	
				do
   				{
					flag=0;
					printf("请输入您的姓名,输入0返回上一级\n");
	    			scanf("%s",a.name);
					if(a.name[0]=='0'&&strlen(a.name)==1)
					{
						step=1;
						break;
					}
	    			while(fread(&b,sizeof(Stu),1,fp)==1)
	    			{
					    if(strcmp(a.name,b.name)==0)
					    {
		   					printf("该姓名已被注册，请输入新姓名\n");
							flag=1;
		   					break;
						}
			    	}
					step=0;
	    			rewind(fp);
    			}while(flag==1);
				break;
			default:
				break;
		}
		switch(step)
		{
			case 0:
				do
				{
					printf("请输入您的密码,输入0返回上一级\n");
					scanf("%s",a.password);
					if(a.password[0]=='0'&&strlen(a.password)==1)
					{
						step=2;
						break;
					}
	    			printf("请再次输入您的密码,输入0返回上一级\n");
	    			scanf("%s",ensure);
					if(ensure[0]=='0'&&strlen(ensure)==1)
					{
						continue;
					}
	    			if(strcmp(a.password,ensure)==0)
	    			{
	    				printf("创建成功\n");
	    				while(fread(&b,sizeof(Stu),1,fp)==1)
						{
							i++;
						}
						a.num=i+1;
	    				a.day=0;
	    				a.times=0;
	    				for(j=0;j<20;j++)
        			    {
        				    a.score[j]=0;
	    			    }
						fwrite(&a,sizeof(Stu),1,fp);
						printf("帐号注册成功,请牢记帐号和密码\n");
						fclose(fp);
						mkuserfile(a);
						return;
	    			}
					printf("两次输入的密码不一致，请重新输入\n");
    			}while(1);
				break;
			default:
				break;
		}
	}while(1);
}
Stu login()
{
	FILE *fp;
	fp=fopen("./system/user.dat","rb+");
	Stu a,b;
	int flag;
	do
	{
		do
		{
	    	flag=0;
			printf("账号登录：\n请输入您的帐号,输入0返回上一级\n");
		    scanf("%s",a.account);
			if(a.account[0]=='0'&&strlen(a.account)==1)
			{
				a.num=0;
				fclose(fp);
				return a;
			}
			rewind(fp);
			while(fread(&b,sizeof(Stu),1,fp)==1)
			{
				 if(strcmp(a.account,b.account)==0)
				 {
					flag=1;
					break;
				 }
			}
		    if(flag==0)
		    {
		    	printf("该账号不存在，请输入正确的帐号\n");
				continue;
		    }
			break;
    	}while(1);
		do
		{
		    printf("请输入您的密码,输入0返回上一级\n");
		    scanf("%s",a.password);
			if(a.password[0]=='0'&&strlen(a.password)==1)
			{
				break;
			}
		    if(strcmp(a.password,b.password)!=0)
		    {
		    	printf("密码错误，请重新输入\n");
				continue;
		    }
		    else
		    {
		    	printf("登陆成功\n");
 				fclose(fp);
 				return b;
		    }
    	}while(1);
	}while(1);
} 
void mark(Stu x,double score)
{
	FILE *fp;
	fp=fopen("./system/user.dat","rb+");
	Stu a;
	int i,num=0;
	while(fread(&a,sizeof(Stu),1,fp)==1)
	{
		num++;
	    if(a.num==x.num)
	    {
	    	break;
		}
	}
	for(i=19;i>0;i--)
	{
		a.score[i]=a.score[i-1];
	} 
	a.score[0]=score;
	fseek(fp,-(long)sizeof(Stu),1);
	fwrite(&a,sizeof(Stu),1,fp);
	fclose(fp);
}
void cheek(Stu x)
{
	FILE *fp;
	fp=fopen("./system/user.dat","rb+");
	Stu a;
	int i,j=0;
	while(fread(&a,sizeof(Stu),1,fp)==1)
	{
	    if(a.num==x.num)
	    {
	    	break;
		}
	}
	printf("以下是近二十次成绩记录\n"); 
	for(i=0;i<20;i++)
	{
		printf("%.2f\t",a.score[i]);
		j++;
		if(j%5==0)
		{
			printf("\n");
		}
	}
	fclose(fp);
}
void record(Stu x)
{
	FILE *fp;
	fp=fopen("./system/user.dat","rb+");
	Stu a;
	int i,j;
	time_t t;
	struct tm *p;
	time(&t);
	p=localtime(&t);
	i=p->tm_yday;
	j=p->tm_year;
	fseek(fp,sizeof(Stu)*(x.num-1),0);
	fread(&a,sizeof(Stu),1,fp);
	fseek(fp,-(long)sizeof(Stu),1);
	if(a.times==0||a.day!=i||(a.day==i&a.year!=j))
	{
		a.times++;
		a.day=i;
		a.year=j;
		printf("打卡成功,当前打卡次数%d次\n",a.times);
		fwrite(&a,sizeof(Stu),1,fp);
	}
	else
	{
		printf("今日已打卡，请明日再来\n");
	}
	fclose(fp);
}
void modacc()
{
	FILE *fp;
	fp=fopen("./system/user.dat","rb+");
	Stu a,b;
	char modify[20];
	int variable[2],sum=0,exist,repeat,flag;
	while(fread(&a,sizeof(Stu),1,fp)==1)
	{
		sum++;
	}
	if(sum==0)
	{
		printf("账户表中没有账户！\n");
		fclose(fp);
		return;
	}
	do
	{
		menu_modacc();
		printf("请做出你的选择:\n");
		while(scanf("%d",&variable[0])!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		exist=0;
		switch (variable[0])
		{
			case 0:
				fclose(fp);
				return;
			case 1:
				do
				{
					printf("请输入想要修改的账户的序号(1-%d),输入0返回\n",sum);
					while(scanf("%d",&variable[1])!=1)
					{
						printf("格式错误，请重新输入\n");
						getchar();
					}
					if(variable[1]<1||variable[1]>sum)
					{
						if(variable[1]!=0)
						{
							printf("该序号不存在，请输入正确的序号\n");
							continue;
						}
						break;
					}
					exist=1;
					fseek(fp,sizeof(Stu)*(variable[1]-1),0);
					fread(&a,sizeof(Stu),1,fp);
					break;
				} while (exist==0);
				break;
			case 2:
				do
				{
					printf("请输入想要修改的账户的账号,输入0返回\n");
					scanf("%s",modify);
					if(modify[0]=='0'&&strlen(modify)==1)
					{
						break;
					}
					rewind(fp);
					while(fread(&a,sizeof(Stu),1,fp)==1)
					{
						if(strcmp(a.account,modify)==0)
						{
							exist=1;
							break;
						}
					}
					if(exist==0)
					{
						printf("该账号不存在，请输入正确的账号\n");
						continue;
					}
				} while (exist==0);
				break;
			case 3:
				do
				{
					printf("请输入想要修改的账户的姓名,输入0返回\n");
					scanf("%s",modify);
					if(modify[0]=='0'&&strlen(modify)==1)
					{
						break;
					}
					exist=0;
					rewind(fp);
					while(fread(&a,sizeof(Stu),1,fp)==1)
					{
						if(strcmp(a.name,modify)==0)
						{
							exist=1;
							break;
						}
					}
					if(exist==0)
					{
						printf("该姓名不存在，请输入正确的姓名\n");
						continue;
					}
				} while (exist==0);
				break;
			default:
				printf("请做出正确的选择\n");
				break;
		}
		if(exist==1)
		{
			do
			{
				flag=0;
				printf("修改账户：\n账号：%-20s\t姓名：%-20s\t密码：%-20s\n请做出你的选择:\n",a.account,a.name,a.password);
				menu_modacc_select();
				while(scanf("%d",&variable[1])!=1)
				{
					printf("格式错误，请重新输入\n");
					getchar();
				}
				switch (variable[1])
				{
					case 0:
						flag=1;
						break;
					case 1:
						do
						{
							printf("请输入新的账号，输入0返回上一级\n");
							scanf("%s",modify);
							if(modify[0]=='0'&&strlen(modify)==1)
							{
								break;
							}
							repeat=0;
							rewind(fp);
							while(fread(&b,sizeof(Stu),1,fp)==1)
							{
								if(strcmp(b.account,a.account)==0)
								{
									printf("该账号已被注册，请输入新账号\n");
									repeat=1;
									break;
								}
							}
							if(repeat==0)
							{
								char oldpath[200],newpath[200];
								snprintf(oldpath,sizeof(oldpath),"userdata/%s",a.account);
								snprintf(newpath,sizeof(newpath),"userdata/%s",a.account);
								rename(oldpath,newpath);
								strcmp(a.account,modify);
								fseek(fp,sizeof(Stu)*(a.num-1),0);
								fwrite(&a,sizeof(Stu),1,fp);
								fclose(fp);
								printf("修改成功\n");
								return;
							}
						}while(repeat==1);
						break;
					case 2:
						do
						{
							printf("请输入新的姓名，输入0返回上一级\n");
							scanf("%s",modify);
							if(modify[0]=='0'&&strlen(modify)==1)
							{
								break;
							}
							repeat=0;
							rewind(fp);
							while(fread(&b,sizeof(Stu),1,fp)==1)
							{
								if(strcmp(b.name,a.name)==0)
								{
									printf("该姓名已被注册，请输入新姓名\n");
									repeat=1;
									break;
								}
							}
							if(repeat==0)
							{
								strcmp(a.name,modify);
								fseek(fp,sizeof(Stu)*(a.num-1),0);
								fwrite(&a,sizeof(Stu),1,fp);
								fclose(fp);
								printf("修改成功\n");
								return;
							}
						}while(repeat==1);
						break;
					case 3:
						do
						{
							printf("请输入您的密码(密码不多于16位)，输入0返回上一级\n");
							scanf("%s",modify);
							if(modify[0]=='0'&&strlen(modify)==1)
							{
								break;
							}
							printf("请再次输入您的密码\n");
							scanf("%s",b.password);
							if(strcmp(modify,b.password)==0)
							{
								strcmp(a.password,modify);
								fseek(fp,sizeof(Stu)*(a.num-1),0);
								fwrite(&a,sizeof(Stu),1,fp);
								fclose(fp);
								printf("修改成功\n");
								return;
							}
							printf("两次输入的密码不一致，请重新输入\n");
						}while(1);
						break;
					default:
						printf("请做出正确的选择\n");
						break;
				}
			} while (flag==0);
		}
	} while (1);
}
void delacc()
{
	FILE *fp1,*fp2;
	Stu a,b;
	int variable[2],exist,flag,sum=0,x;
	char modify[20];
	fp1=fopen("./system/user.dat","rb+");
	while(fread(&a,sizeof(Stu),1,fp1)==1)
	{
		sum++;
	}
	if(sum==0)
	{
		printf("账户表中没有账户！\n");
		fclose(fp1);
		return;
	}
	do
	{
	    menu_delacc();
		printf("请做出你的选择:\n");
		while(scanf("%d",&variable[0])!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		exist=0;
		switch(variable[0])
		{
			case 0:
				return;
			case 1:
				do
				{
					printf("请输入想要删除的账户的序号(1-%d),输入0返回\n",sum);
					while(scanf("%d",&variable[1])!=1)
					{
						printf("格式错误，请重新输入\n");
						getchar();
					}
					if(variable[1]<1||variable[1]>sum)
					{
						if(variable[1]!=0)
						{
							printf("该序号不存在，请输入正确的序号\n");
							continue;
						}
						break;
					}
					exist=1;
					fseek(fp1,sizeof(Stu)*(variable[1]-1),0);
					fread(&a,sizeof(Stu),1,fp1);
					break;
				} while (exist==0);
				break;
			case 2:
				do
				{
					printf("请输入想要删除的账户的账号,输入0返回\n");
					scanf("%s",modify);
					if(modify[0]=='0'&&strlen(modify)==1)
					{
						break;
					}
					rewind(fp1);
					while(fread(&a,sizeof(Stu),1,fp1)==1)
					{
						if(strcmp(a.account,modify)==0)
						{
							exist=1;
							break;
						}
					}
					if(exist==0)
					{
						printf("该账号不存在，请输入正确的账号\n");
						continue;
					}
				} while (exist==0);
				break;
			case 3:
				do
				{
					printf("请输入想要删除的账户的姓名,输入0返回\n");
					scanf("%s",modify);
					if(modify[0]=='0'&&strlen(modify)==1)
					{
						break;
					}
					rewind(fp1);
					while(fread(&a,sizeof(Stu),1,fp1)==1)
					{
						if(strcmp(a.name,modify)==0)
						{
							exist=1;
							break;
						}
					}
					if(exist==0)
					{
						printf("该姓名不存在，请输入正确的姓名\n");
						continue;
					}
				} while (exist==0);
				break;
			case 4:
				x=reuser();
				if(x==1)
				{
					return;
				}
				break;
			default:
				printf("请做出正确的选择\n");
				break;
		}
		if(exist==1)
		{
			do
			{
				flag=0;
				printf("删除账户：\n账号：%-20s\t姓名：%-20s\t密码：%-20s\n警告：即将删除账户，输入1继续，输入0返回\n",a.account,a.name,a.password);
				while(scanf("%d",&variable[1])!=1)
				{
					printf("格式错误，请重新输入\n");
					getchar();
				}
				switch (variable[1])
				{
					case 0:
						flag=1;
						break;
					case 1:
						fp2=fopen("./system/user_temp.dat","wb+");	
						rewind(fp1);
						while(fread(&b,sizeof(Stu),1,fp1)==1)
						{
							if(b.num==a.num)
							{
								continue;
							}
							fwrite(&b,sizeof(Stu),1,fp2);
						}
						fclose(fp1);
						fclose(fp2);
						remove("./system/user.dat");
						rename("./system/user_temp.dat","./system/user.dat");
						char delcommand[200];
						#ifdef _WIN32
							snprintf(delcommand,sizeof(delcommand),"rd /s /q \".\\userdata\\%s\"",a.account);
						#else
							snprintf(delcommand,sizeof(delcommand),"rm -rf ./userdata/%s",a.account);
						#endif
						system(delcommand);
						printf("已删除账号\n"); 
						return;\
					default:
						printf("请做出正确的选择\n");
						break;
				}
			}while(flag==0);
		}
    }while(1);
}
void preacc()
{
	FILE *fp;
	fp=fopen("./system/user.dat","rb+");
	Stu a;
	int page=0,sum=0,sumpage,variable[4],flag[2],i,exist;
	char select[20];
	while(fread(&a,sizeof(Stu),1,fp)==1)
	{
		sum++;
	}
	sumpage=sum/10;
	if(sum!=0&&sum%10==0)
	{
		sumpage--;
	}
	rewind(fp);
	do
	{
		printf("%-20s\t%-20s\t%-20s\t%-20s\n","序号","账号","姓名","密码");
		fseek(fp,sizeof(Stu)*page*10,0);
		for(i=0;i<10;i++)
		{
			if(fread(&a,sizeof(Stu),1,fp)==1)
			{
				printf("%-20d\t%-20s\t%-20s\t%-20s\n",a.num,a.account,a.name,a.password);
			}
			else
			{
				break;
			}
		}
		printf("第%d页，共%d页\n",page+1,sumpage+1);
		do
		{
			flag[0]=0;
			menu_preacc();
			printf("请做出你的选择:\n");
			while(scanf("%d",&variable[0])!=1)
			{
				printf("格式错误，请重新输入\n");
				getchar();
			}
			switch (variable[0])
			{
				case 0:
					fclose(fp);
					return;
				case 1:
					if(page==0)
					{
						printf("已经是第一页，请重新选择\n");
						break;
					}
					page--;
					flag[0]=1;
					break;
				case 2:
					if(page==sumpage)
					{
						printf("已经是最后一页，请重新选择\n");
						break;
					}
					page++;
					flag[0]=1;
					break;
				case 3:
					flag[0]=1;
					do
					{
						printf("请输入想要跳转的页数(1-%d),输入0返回：\n",sumpage+1);
						while(scanf("%d",&variable[1])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						if(variable[1]==0)
						{
							break;
						}
						if(variable[1]<1||variable[1]>sumpage+1)
						{
							printf("请输入正确的页数\n");
							continue;
						}
						page=variable[1]-1;
						break;
					} while (1);
					break;
				case 4:
					flag[0]=1;
					if(sum==0)
					{
						printf("账户表中没有账户！\n");
						break;
					}
					do
					{
						flag[1]=0;
						menu_selectacc();
						printf("请做出你的选择:\n");
						while(scanf("%d",&variable[2])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						switch (variable[2])
						{
							case 0:
								flag[1]=1;
								break;
							case 1:
								do
								{
									printf("请输入想要查询的账户的序号(1-%d)，输入0返回：\n",sum);
									while(scanf("%d",&variable[3])!=1)
									{
										printf("格式错误，请重新输入\n");
										getchar();
									}
									if(variable[3]<1||variable[3]>sum)
									{
										if(variable[3]==0)
										{
											break;
										}
										printf("请输入正确的序号\n");
										continue;;
									}
									fseek(fp,sizeof(Stu)*(variable[3]-1),0);
									fread(&a,sizeof(Stu),1,fp);
									printf("%-20s\t%-20s\t%-20s\t%-20s\n","序号","账号","姓名","密码");
									printf("%-20d\t%-20s\t%-20s\t%-20s\n",a.num,a.account,a.name,a.password);
								} while (1);
								break;
							case 2:
								do
								{
									printf("请输入想要查询的账户的账号，输入0返回：\n");
									scanf("%s",select);
									if(select[0]=='0'&&strlen(select)==1)
									{
										break;
									}
									rewind(fp);
									exist=0;
									while(fread(&a,sizeof(Stu),1,fp)==1)
									{
										if(strcmp(a.account,select)==0)
										{
											exist=1;
											break;
										}
									}
									if(exist==0)
									{
										printf("该账号不存在\n");
										continue;
									}
									printf("%-20s\t%-20s\t%-20s\t%-20s\n","序号","账号","姓名","密码");
									printf("%-20d\t%-20s\t%-20s\t%-20s\n",a.num,a.account,a.name,a.password);
								} while (1);
								break;
							case 3:
								do
								{
									printf("请输入想要查询的账户的姓名，输入0返回：\n");
									scanf("%s",select);
									if(select[0]=='0'&&strlen(select)==1)
									{
										break;
									}
									rewind(fp);
									exist=0;
									while(fread(&a,sizeof(Stu),1,fp)==1)
									{
										if(strcmp(a.name,select)==0)
										{
											exist=1;
											break;
										}
									}
									if(exist==0)
									{
										printf("该账号不存在\n");
										continue;
									}
									printf("%-20s\t%-20s\t%-20s\t%-20s\n","序号","账号","姓名","密码");
									printf("%-20d\t%-20s\t%-20s\t%-20s\n",a.num,a.account,a.name,a.password);
								} while (1);
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
		} while (flag[0]==0);
	} while (1);
}