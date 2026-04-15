#include<stdio.h>
#include<string.h>
#include"file.h"
#include"recite.h"
#include"account.h"
#include"menu.h"
void judge()
{
	FILE *fp;
	MKDIR("system");
	MKDIR("userdata");
	MKDIR("backup");
	fp=fopen("./system/user.dat","rb+");
	if(!fp)
	{
		fp=fopen("./system/user.dat","wb+");
	}
	fclose(fp);
	fp=fopen("./system/wordsbook.dat","rb+");
	if(!fp)
	{
		fp=fopen("./system/wordsbook.dat","wb+");
	}
	fclose(fp);
	fp=fopen("./backup/backuplog.dat","rb+");
	if(!fp)
	{
		fp=fopen("./backup/backuplog.dat","wb+");
	}
	fclose(fp);
	fp=fopen("./system/setting_password.dat","rb+");
	if(!fp)
	{
		fp=fopen("./system/setting_password.dat","wb+");
	}
	fclose(fp);
}
int settingjudge()
{
	FILE *fp;
	Syspass a,b;
	int flag;
	fp=fopen("./system/setting_password.dat","rb+");
	if(fread(&a,sizeof(Syspass),1,fp)!=1)
	{
		do
		{
			printf("首次进入，请设置进入“系统高级设置”的密码，输入0返回：\n");
			scanf("%s",a.password);
			if(a.password[0]=='0'&&strlen(a.password)==1)
			{
				fclose(fp);
				return 0;
			}
			printf("请再次输入您的密码,输入0返回上一级\n");
			scanf("%s",b.password);
			if(b.password[0]=='0'&&strlen(b.password)==1)
			{
				continue;;
			}
			if(strcmp(b.password,b.password)==0)
			{
				printf("设置成功，请牢记您的的密码\n");
				fwrite(&b,sizeof(Syspass),1,fp);
				fclose(fp);
				return 1;
			}
			printf("两次输入的密码不一致，请重新输入\n");
		} while (1);
	}
	do
	{
		printf("请输入进入“系统高级设置”的密码，输入0返回：\n");
		scanf("%s",b.password);
		if(b.password[0]=='0'&&strlen(b.password)==1)
		{
			fclose(fp);
			return 0;
		}
		if(strcmp(a.password,b.password)==0)
		{
			fclose(fp);
			return 1;
		}
		printf("密码错误，请重新输入\n");
	} while (1);
}
void modpassword()
{
	FILE *fp;
	Syspass a,b;
	fp=fopen("./system/setting_password.dat","rb+");
	do
	{
		printf("请输入新密码,输入0返回\n");
		scanf("%s",a.password);
		if(a.password[0]=='0'&&strlen(a.password)==1)
		{
			fclose(fp);
			return;
		}
		printf("请再次输入新密码，输入0返回\n");
		scanf("%s",b.password);
		if(b.password[0]=='0'&&strlen(b.password)==1)
		{
			continue;
		}
		if(strcmp(a.password,b.password)==0)
		{
			printf("密码修改成功\n");
			fwrite(&b,sizeof(Syspass),1,fp);
			fclose(fp);
			return;
		}
		printf("两次输入的密码不一致，请重新输入\n");
	} while (1);
}
void mkuserfile(Stu x)
{
	FILE *fp;
	char fullpath[256],wroppath[256],wrsppath[256];
	snprintf(fullpath,sizeof(fullpath),"userdata/%s",x.account);
	MKDIR(fullpath);
	snprintf(wroppath,sizeof(wroppath),"./userdata/%s/wrongoption.dat",x.account);
	fp=fopen(wroppath,"wb+");
	fclose(fp);
	snprintf(wrsppath,sizeof(wrsppath),"./userdata/%s/wrongspell.dat",x.account);
	fp=fopen(wrsppath,"wb+");
	fclose(fp);
}
int refile()
{
	FILE *fp;
	int variable;
	do
	{
	    printf("警告，即将清除数据，输入1继续，输入0返回\n");
	    while(scanf("%d",&variable)!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		switch (variable)
		{
			case 0:
				return 0;
			case 1:
				#ifdef _WIN32
					system("rd /s /q system");
					system("rd /s /q userdata");
					system("rd /s /q backup");
				#else
					system("rm -rf system");
					system("rm -rf userdata");
					system("rm -rf backup");
				#endif
				judge();
				return 1;
			default:
				printf("请做出正确的选择\n");
				break;
		}
    }while(1);
}
int reuser()
{
	FILE *fp;
	int variable;
	do
	{
	    printf("警告，即将清除账户数据，输入1继续，输入0返回\n");
	    while(scanf("%d",&variable)!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		switch(variable)
		{
			case 0:
				return 0;
			case 1:
				fp=fopen("./system/user.dat","wb+");
	      		fclose(fp);
	      		printf("已清除数据\n"); 
				return 1;
			default:
				printf("请做出正确的选择\n");
				break;
		}
    }while(1);
}
int reword()
{
	FILE *fp;
	int variable;
	do
	{
	    printf("警告，即将清除单词数据，输入1继续，输入0返回\n");
	    while(scanf("%d",&variable)!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		switch(variable)
		{
			case 0:
				return 0;
			case 1:
				fp=fopen("./system/wordsbook.dat","wb+");
	      		fclose(fp);
	      		printf("已清除数据\n"); 
				return 1;
			default:
				printf("请做出正确的选择\n");
				break;
		}
    }while(1);
}
void rescore(Stu x)
{
	FILE *fp;
	int variable,i;
	Stu a;
	do
	{
	    printf("警告，即将清除数据，输入1继续，输入0返回\n");
	    while(scanf("%d",&variable)!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		switch(variable)
		{
			case 0:
				return;
			case 1:
				fp=fopen("./system/user.dat","rb+");
				while(fread(&a,sizeof(Stu),1,fp)==1)
	    		{
					if(a.num==x.num)
					{
						break;
					}
			    }
				fseek(fp,-(long)sizeof(Stu),1);
				for(i=0;i<20;i++)
				{
					a.score[i]=0;
				}
				fwrite(&a,sizeof(Stu),1,fp);
	      		fclose(fp);
	      		printf("已清除数据\n"); 
				return;
			default:
				printf("请做出正确的选择\n");
				break;
		}
    }while(1);
}
int reoption(Stu x)
{
	FILE *fp;
	int variable;
	do
	{
		printf("警告，即将清除数据，输入1继续，输入0返回\n");
		while(scanf("%d",&variable)!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		switch (variable)
		{
			case 0:
				return 0;
			case 1:
				char path[256];
				snprintf(path,sizeof(path),"./userdata/%s/wrongoption.dat",x.account);
				fp=fopen(path,"wb+");
	    		fclose(fp);
	    	    printf("已清除数据\n"); 
				return 1;
			default:
	    		printf("请做出正确的选择\n");
				break;
		}
	} while (1);
}
int respell(Stu x)
{
	FILE *fp;
	int variable;
	do
	{
		printf("警告，即将清除数据，输入1继续，输入0返回\n");
		while(scanf("%d",&variable)!=1)
		{
			printf("格式错误，请重新输入\n");
			getchar();
		}
		switch (variable)
		{
			case 0:
				return 0;
			case 1:
				char path[256];
				snprintf(path,sizeof(path),"./userdata/%s/wrongspell.dat",x.account);
				fp=fopen(path,"wb+");
	    		fclose(fp);
	    	    printf("已清除数据\n"); 
				return 1;
			default:
	    		printf("请做出正确的选择\n");
				break;
		}
	} while (1);
}
void backup()
{
	FILE *fp;
	Bkname a;
	char backuppath[256],command[256],name[30];
	int flag;
	fp=fopen("./backup/backuplog.dat","rb+");
	do
	{
		flag=0;
		printf("请输入备份名，输入0返回\n");
		scanf("%s",name);
		if(name[0]=='0'&&strlen(name)==1)
		{
			fclose(fp);
			return;
		}
		rewind(fp);
		while(fread(&a,sizeof(Bkname),1,fp)==1)
		{
			if(strcmp(a.name,name)==0)
			{
				printf("该备份名已存在，请重新输入新备份名\n");
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			continue;
		}
		snprintf(backuppath,sizeof(backuppath),"./backup/%s",name);
		MKDIR(backuppath);
		#ifdef _WIN32
   			snprintf(command, sizeof(command), "xcopy \".\\system\" \".\\backup\\%s\\system\" /E /I /H /Y > nul", name);
			system(command);
			snprintf(command, sizeof(command), "xcopy \".\\userdata\" \".\\backup\\%s\\userdata\" /E /I /H /Y > nul", name);
			system(command);
		#else
			snprintf(command,sizeof(command),"cp -r ./system ./backup/%s",name);
			system(command);
			snprintf(command,sizeof(command),"cp -r ./userdata ./backup/%s",name);
			system(command);
		#endif
		strcpy(a.name,name);
		fwrite(&a,sizeof(Bkname),1,fp);
		printf("数据备份成功\n");
		fclose(fp);
		return;
	} while (1);
}
void restore()
{
	FILE *fp1,*fp2;
	fp1=fopen("./backup/backuplog.dat","rb+");
	Bkname a;
	int page=0,sum=0,sumpage,variable[4],flag[3],i,exist;
	char name[30];
	while(fread(&a,sizeof(Bkname),1,fp1)==1)
	{
		sum++;
	}
	if(sum==0)
	{
		printf("没有备份文件！\n");
		fclose(fp1);
		return;
	}
	sumpage=sum/5;
	if(sum%5==0)
	{
		sumpage--;
	}
	do
	{
		printf("备份名称：\n");
		fseek(fp1,sizeof(Bkname)*page*5,0);
		for(i=0;i<5;i++)
		{
			if(fread(&a,sizeof(Bkname),1,fp1)==1)
			{
				printf("%-30s\t",a.name);
			}
			else
			{
				break;
			}
		}
		printf("\n第%d页，共%d页\n",page+1,sumpage+1);
		do
		{
			flag[0]=0;
			menu_restore();
			printf("请做出你的选择:\n");
			while(scanf("%d",&variable[0])!=1)
			{
				printf("格式错误，请重新输入\n");
				getchar();
			}
			switch (variable[0])
			{
				case 0:
					fclose(fp1);
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
					do
					{
						exist=0;
						printf("请输入备份名，输入0返回\n");
						scanf("%s",name);
						if(name[0]=='0'&&strlen(name)==1)
						{
							break;
						}
						rewind(fp1);
						while(fread(&a,sizeof(Bkname),1,fp1)==1)
						{
							if(strcmp(a.name,name)==0)
							{
								exist=1;
								break;
							}
						}
						if(exist==1)
						{
							break;
						}
						printf("该备份名不存在，请输入正确的备份名\n");
					} while (1);
					if(exist==1)
					{
						do
						{
							flag[1]=0;
							menu_selectrestore();
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
										flag[2]=0;
										printf("警告：即将恢复账户备份并覆盖当前数据，输入1继续，输入0返回\n");
										while(scanf("%d",&variable[3])!=1)
										{
											printf("格式错误，请重新输入\n");
											getchar();
										}
										switch (variable[3])
										{
											case 0:
												flag[2]=1;
												break;
											case 1:
												flag[2]=1;
												char command[256];
												fclose(fp1);
												#ifdef _WIN32
													system("rd /s /q userdata");
													MKDIR("userdata");
													snprintf(command,sizeof(command),"xcopy \".\\backup\\%s\\system\\user.dat\" \".\\system\" /Y > nul",name);
													system(command);
													snprintf(command,sizeof(command),"xcopy \".\\backup\\%s\\userdata\" \".\\userdata\" /E /I /H /Y > nul",name);
													system(command);
												#else
													system("rm -rf ./userdata");
													MKDIR("userdata");
													snprintf(command,sizeof(command),"cp ./backup/%s/system/user.dat ./system",name);
													system(command);
													snprintf(command,sizeof(command),"cp -r ./backup/%s/userdata .",name);
													system(command);
												#endif
												printf("已恢复账户备份\n"); 
												fp1=fopen("./backup/backuplog.dat","rb+");
												break;
											default:
												printf("请做出正确的选择\n");
												break;
										}
									} while (flag[2]==0);
									break;
								case 2:
									do
									{
										flag[2]=0;
										printf("警告：即将恢复单词本备份并覆盖当前数据，输入1继续，输入0返回\n");
										while(scanf("%d",&variable[3])!=1)
										{
											printf("格式错误，请重新输入\n");
											getchar();
										}
										switch (variable[3])
										{
											case 0:
												flag[2]=1;
												break;
											case 1:
												flag[2]=1;
												char command[256];
												fclose(fp1);
												#ifdef _WIN32
													snprintf(command, sizeof(command),"xcopy \".\\backup\\%s\\system\\wordsbook.dat\" \".\\system\" /Y > nul",name);
													system(command);
												#else
													snprintf(command,sizeof(command),"cp ./backup/%s/system/wordsbook.dat ./system",name);
													system(command);
												#endif
												printf("已恢复单词本备份\n"); 
												fp1=fopen("./backup/backuplog.dat","rb+");
												break;
											default:
												printf("请做出正确的选择\n");
												break;
										}
									} while (flag[2]==0);
									break;
								case 3:
									do
									{
										flag[2]=0;
										printf("警告：即将恢复系统密码备份并覆盖当前数据，输入1继续，输入0返回\n");
										while(scanf("%d",&variable[3])!=1)
										{
											printf("格式错误，请重新输入\n");
											getchar();
										}
										switch (variable[3])
										{
											case 0:
												flag[2]=1;
												break;
											case 1:
												flag[2]=1;
												char command[256];
												fclose(fp1);
												#ifdef _WIN32
													snprintf(command,sizeof(command),"xcopy \".\\backup\\%s\\system\\setting_password.dat\" \".\\system\" /Y > nul",name);
													system(command);
												#else
													snprintf(command,sizeof(command),"cp ./backup/%s/system/setting_password.dat ./system",name);
													system(command);
												#endif
												printf("已恢复系统密码备份\n"); 
												fp1=fopen("./backup/backuplog.dat","rb+");
												break;
											default:
												printf("请做出正确的选择\n");
												break;
										}
									} while (flag[2]==0);
									break;
								case 4:
									do
									{
										flag[2]=0;
										printf("警告：即将恢复该备份中的所有数据并覆盖当前数据，输入1继续，输入0返回\n");
										while(scanf("%d",&variable[3])!=1)
										{
											printf("格式错误，请重新输入\n");
											getchar();
										}
										switch (variable[3])
										{
											case 0:
												flag[2]=1;
												break;
											case 1:
												flag[2]=1;
												char command[256];
												fclose(fp1);
												#ifdef _WIN32
													system("rd /s /q userdata");
													MKDIR("userdata");
													snprintf(command,sizeof(command),"xcopy \".\\backup\\%s\\system\" \".\\system\" /E /I /H /Y > nul",name);
													system(command);
													snprintf(command,sizeof(command),"xcopy \".\\backup\\%s\\userdata\" \".\\userdata\" /E /I /H /Y > nul",name);
													system(command);
												#else
													system("rm -rf ./userdata");
													MKDIR("userdata");
													snprintf(command, sizeof(command), "cp -r ./backup/%s/system .", name);
													system(command);
													snprintf(command, sizeof(command), "cp -r ./backup/%s/userdata .", name);
													system(command);
												#endif
												printf("已恢复该备份中的所有数据\n"); 
												fp1=fopen("./backup/backuplog.dat","rb+");
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
						} while (flag[1]==0);
					}
					break;
				case 5:
					flag[0]=1;
					do
					{
						exist=0;
						printf("请输入备份名，输入0返回\n");
						scanf("%s",name);
						if(name[0]=='0'&&strlen(name)==1)
						{
							break;
						}
						rewind(fp1);
						while(fread(&a,sizeof(Bkname),1,fp1)==1)
						{
							if(strcmp(a.name,name)==0)
							{
								exist=1;
								break;
							}
						}
						if(exist==1)
						{
							break;
						}
						printf("该备份名不存在，请输入正确的备份名\n");
					} while (1);
					if(exist==1)
					{
						do
						{
							printf("删除备份：\n%s\n警告：即将删除该备份，输入1继续，输入0返回\n",name);
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
									fp2=fopen("./backup/backuplog_temp.dat","wb+");	
									rewind(fp1);
									while(fread(&a,sizeof(Bkname),1,fp1)==1)
									{
										if(strcmp(a.name,name)==0)
										{
											continue;
										}
										fwrite(&a,sizeof(Bkname),1,fp2);
									}
									fclose(fp1);
									fclose(fp2);
									remove("./backup/backuplog.dat");
									rename("./backup/backuplog_temp.dat","./backup/backuplog.dat");
									char delcommand[200];
									#ifdef _WIN32
										snprintf(delcommand,sizeof(delcommand),"rd /s /q \".\\backup\\%s\"",name);
									#else
										snprintf(delcommand,sizeof(delcommand),"rm -rf ./backup/%s",name);
									#endif
									system(delcommand);
									printf("已删除备份\n"); 
									fp1=fopen("./backup/backuplog.dat","rb+");
									sum--;
									if(sum==0)
									{
										printf("没有备份文件！\n");
										fclose(fp1);
										return;
									}
									if(sum%5==0)
									{
										page--;
										sumpage--;
									}
									break;
								default:
									printf("请做出正确的选择\n");
									break;
							}
						} while (flag[1]==0);
					}
					break;
				default:
					printf("请做出正确的选择\n");
					break;
			}
		} while (flag[0]==0);
	} while (1);
}
