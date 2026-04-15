#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"account.h"
#include"file.h"
#include"recite.h"
#include"wordsbook.h"
#include"menu.h"
void opt(Stu x,int num)
{
	FILE *fp1,*fp2;
	Wrop a;
	Wo b;
	Opt c[4];
	char path[256];
	int i,j,variable,sum=0,rightnum=0,wrongsum=0,randomnum,choose[100]={0},repeat,que[4]={0},quetimes,querepeat,ans,location;
	double score;
	snprintf(path,sizeof(path),"./userdata/%s/wrongoption.dat",x.account);
	fp1=fopen("./system/wordsbook.dat","rb+");
	fp2=fopen(path,"rb+");
	while(fread(&b,sizeof(Wo),1,fp1)==1)
	{
		sum++;
	}
	if(sum<4)
	{
		printf("单词本中单词数量少于4,无法生成选择题,请添加单词后重试\n");
		fclose(fp1);
		fclose(fp2);
		return;
	}
	while(fread(&b,sizeof(Wrop),1,fp2)==1)
	{
		wrongsum++;
	}
	if(num>sum)
	{
		printf("单词本中单词数量少于您输入的题目数量,最多生成%d道题目\n",sum);
		num=sum;
	}
	for(i=0;i<num;i++)
	{
		repeat=0;
		srand(time(NULL));
		randomnum=(rand()%sum)+1;
		for(j=0;j<i;j++)
		{
			if(randomnum==choose[j])
			{
				repeat=1;
				break;
			}
		}
		if(repeat==1)
		{
			i--;
			continue;
		}
		printf("系统正在出题中，请稍等...\n");
		choose[i]=randomnum;
		fseek(fp1,sizeof(Wo)*(randomnum-1),0);
		fread(&b,sizeof(Wo),1,fp1);
		ans=(rand()%4);
		que[0]=c[ans].num=b.num;
		strcpy(c[ans].chi,b.chi);
		strcpy(c[ans].eng,b.eng);
		location=0;
		for(quetimes=1;quetimes<4;quetimes++)
		{
			querepeat=0;
			que[quetimes]=(rand()%sum)+1;
			for(j=0;j<quetimes;j++)
			{
				if(que[j]==que[quetimes])
				{
					querepeat=1;
					break;
				}
			}
			if(querepeat==1)
			{
				quetimes--;
				continue;
			}
			fseek(fp1,sizeof(Wo)*(que[quetimes]-1),0);
			fread(&b,sizeof(Wo),1,fp1);
			if(location==ans)
			{
				location++;
			}
			c[location].num=b.num;
			strcpy(c[location].chi,b.chi);
			strcpy(c[location].eng,b.eng);
			location++;
		}
		printf("第%d题/共%d题：\n请选择单词的中文的正确选项，并输入对应编号，输入0退出题目练习。\n%s\n",i+1,num,c[ans].eng);
		for(j=0;j<4;j++)
		{
			printf("%d:%-30s\t",j+1,c[j].chi);
		}
		printf("\n");
		while(scanf("%d",&variable)!=1||variable<1||variable>4)
		{
			if(variable==0)
			{
				fclose(fp1);
				fclose(fp2);
				return;
			}
			printf("格式错误，请重新输入\n");
			getchar();
		}
		if(variable==ans+1) 
		{
			printf("正确\n");
			rightnum++;
		}
		else
		{
			a.num=++wrongsum;
			strcpy(a.chi1,c[0].chi);
			strcpy(a.chi2,c[1].chi);
			strcpy(a.chi3,c[2].chi);
			strcpy(a.chi4,c[3].chi);
			strcpy(a.eng,c[ans].eng);
			strcpy(a.ans,c[ans].chi);
			fwrite(&a,sizeof(Wrop),1,fp2);
			printf("错误\n");
		}
		printf("当前答对%d题，答错%d题\n",rightnum,i-rightnum+1);
	}
	fclose(fp1);
	fclose(fp2);
	score=(double)rightnum/num*100;
	printf("已完成%d道题目，正确率：%.2f%%\n将自动记录此次成绩，错题将记入错题本\n",num,score);
	mark(x,score);
}
void spe(Stu x,int num)
{
	FILE *fp1,*fp2;
	Wrsp a;
	Wo b;
	char path[256],variable[30];
	int i,j,sum=0,rightnum=0,wrongsum=0,randomnum,choose[100]={0},repeat,len;
	double score;
	snprintf(path,sizeof(path),"./userdata/%s/wrongspell.dat",x.account);
	fp1=fopen("./system/wordsbook.dat","rb+");
	fp2=fopen(path,"ab+");
	while(fread(&b,sizeof(Wo),1,fp1)==1)
	{
		sum++;
	}
	if(sum<1)
	{
		printf("单词本中单词数量少于1,无法生成拼写题,请添加单词后重试\n");
		fclose(fp1);
		fclose(fp2);
		return;
	}
	while(fread(&b,sizeof(Wrsp),1,fp2)==1)
	{
		wrongsum++;
	}
	if(num>sum)
	{
		printf("单词本中单词数量少于您输入的题目数量,最多生成%d道题目\n",sum);
		num=sum;
	}
	for(i=0;i<num;i++)
	{
		repeat=0;
		srand(time(NULL));
		randomnum=(rand()%sum)+1;
		for(j=0;j<i;j++)
		{
			if(randomnum==choose[j])
			{
				repeat=1;
				break;
			}
		}
		if(repeat==1)
		{
			i--;
			continue;
		}
		printf("系统正在出题中，请稍等...\n");
		choose[i]=randomnum;
		fseek(fp1,sizeof(Wo)*(randomnum-1),0);
		fread(&b,sizeof(Wo),1,fp1);
		printf("第%d题/共%d题：\n请根据中文拼写英语单词,输入0退出题目练习\n%s\t(%s)\n",i+1,num,b.chi,b.lex);
		scanf("%s",variable);
		if(variable[0]=='0'&&strlen(variable)==1)
		{
			fclose(fp1);
			fclose(fp2);
			return;
		}
		if(strcmp(variable,b.eng)==0)
		{
			printf("正确\n");
			rightnum++;
		}
		else
		{
			a.num=++wrongsum;
			strcpy(a.chi,b.chi);
			strcpy(a.eng,b.eng);
			strcpy(a.lex,b.lex);
			fwrite(&a,sizeof(Wrsp),1,fp2);
			printf("错误\n");
		}
		printf("当前答对%d题，答错%d题\n",rightnum,i-rightnum+1);
	}
	fclose(fp1);
	fclose(fp2);
	score=(double)rightnum/num*100;
	printf("已完成%d道题目，正确率：%.2f%%\n将自动记录此次成绩，错题将记入错题本\n",num,score);
	mark(x,score);
}
void revoption(Stu x)
{
	FILE *fp;
	Wrop a;
	char path[256];
	int sum=0,page=0,sumpage=0,i=0,variable[4],flag[2];
	snprintf(path,sizeof(path),"./userdata/%s/wrongoption.dat",x.account);
	fp=fopen(path,"rb+");
	while(fread(&a,sizeof(Wrop),1,fp)==1)
	{
		sum++;
	}
	if(sum==0)
	{
		printf("没有错题记录！\n");
		fclose(fp);
		return;
	}
	sumpage=sum/5;
	if(sum%5==0)
	{
		sumpage--;
	}
	rewind(fp);
	do
	{
		fseek(fp,sizeof(Wrop)*page*5,0);
		for(i=0;i<5;i++)
		{
			if(fread(&a,sizeof(Wrop),1,fp)==1)
			{
				printf("第%d题：\n%s\n%-30s\t%-30s\t%-30s\t%-30s\n答案：%s\n",a.num,a.eng,a.chi1,a.chi2,a.chi3,a.chi4,a.ans);
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
			menu_prewrongbook();
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
					printf("请输入想要跳转的页数(1-%d),输入0返回：\n",sumpage+1);
					while(scanf("%d",&variable[1])!=1)
					{
						printf("格式错误，请重新输入\n");
						getchar();
					}
					flag[0]=1;
					if(variable[1]==0)
					{
						break;
					}
					if(variable[1]<1||variable[1]>sumpage+1)
					{
						printf("请输入正确的页数\n");
						break;
					}
					page=variable[1]-1;
					break;
				case 4:
					flag[0]=1;
					do
					{
						printf("请输入想要查询的错题的序号(1-%d)，输入0返回：\n",sum);
						while(scanf("%d",&variable[2])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						if(variable[2]<1||variable[2]>sum)
						{
							if(variable[2]==0)
							{
								break;
							}
							printf("请输入正确的序号\n");
							continue;;
						}
						fseek(fp,sizeof(Wrop)*(variable[2]-1),0);
						fread(&a,sizeof(Wrop),1,fp);
						printf("第%d题：\n%s\n%-30s\t%-30s\t%-30s\t%-30s\n答案：%s\n",a.num,a.eng,a.chi1,a.chi2,a.chi3,a.chi4,a.ans);
					} while (1);
					break;
				case 5:
					flag[0]=1;
					if(sum==0)
					do
					{
						flag[1]=0;
						printf("请输入想要删除的错题的序号(1-%d)，输入0返回：\n",sum);
						while(scanf("%d",&variable[2])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						if(variable[2]<1||variable[2]>sum)
						{
							if(variable[2]==0)
							{
								break;
							}
							printf("请输入正确的序号\n");
							continue;;
						}
						fseek(fp,sizeof(Wrop)*(variable[2]-1),0);
						fread(&a,sizeof(Wrop),1,fp);
						printf("删除错题：\n第%d题：\n%s\n%-30s\t%-30s\t%-30s\t%-30s\n答案：%s\n",a.num,a.eng,a.chi1,a.chi2,a.chi3,a.chi4,a.ans);
						printf("警告：即将删除错题，输入1继续，输入0返回\n");
						while(scanf("%d",&variable[3])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						switch (variable[3])
						{
							case 0:
								break;
							case 1:
								fclose(fp);
								deloption(x,variable[2]);
								fp=fopen(path,"rb+");
								sum--;
								if(sum==0)
								{
									printf("没有错题记录！\n");
									fclose(fp);
									return;
								}
								if(sum%5==0)
								{
									page--;
									sumpage--;
								}
								flag[1]=1;
								break;
							default:
								printf("请做出正确的选择\n");
								break;
						}
					} while (flag[1]==0);
					break;
				case 6:
					flag[0]=1;
					if(reoption(x)==1)
					{
						return;
					}
					break;
				default:
					printf("请做出正确的选择\n");
					break;
			}
		} while (flag[0]==0);
	} while (1);
}
void revspell(Stu x)
{
	FILE *fp;
	Wrsp a;
	char path[256];
	int sum=0,page=0,sumpage=0,i=0,variable[4],flag[2];
	snprintf(path,sizeof(path),"./userdata/%s/wrongspell.dat",x.account);
	fp=fopen(path,"rb+");
	while(fread(&a,sizeof(Wrsp),1,fp)==1)
	{
		sum++;
	}
	if(sum==0)
	{
		printf("没有错题记录！\n");
		fclose(fp);
		return;
	}
	sumpage=sum/5;
	if(sum%5==0)
	{
		sumpage--;
	}
	rewind(fp);
	do
	{
		fseek(fp,sizeof(Wrsp)*page*5,0);
		for(i=0;i<5;i++)
		{
			if(fread(&a,sizeof(Wrsp),1,fp)==1)
			{
				printf("第%d题：\n%s\t(%s)\n答案：%s\n",a.num,a.chi,a.lex,a.eng);
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
			menu_prewrongbook();
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
						break;
					}
					page=variable[1]-1;
					break;
				case 4:
					flag[0]=1;
					do
					{
						printf("请输入想要查询的错题的序号(1-%d)，输入0返回：\n",sum);
						while(scanf("%d",&variable[2])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						if(variable[2]<1||variable[2]>sum)
						{
							if(variable[2]==0)
							{
								break;
							}
							printf("请输入正确的序号\n");
							continue;;
						}
						fseek(fp,sizeof(Wrsp)*(variable[2]-1),0);
						fread(&a,sizeof(Wrsp),1,fp);
						printf("第%d题：\n%s\t(%s)\n答案：%s\n",a.num,a.chi,a.lex,a.eng);
					} while (1);
					break;
				case 5:
					flag[0]=1;
					do
					{
						flag[1]=0;
						printf("请输入想要删除的错题的序号(1-%d)，输入0返回：\n",sum);
						while(scanf("%d",&variable[2])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						if(variable[2]<1||variable[2]>sum)
						{
							if(variable[2]==0)
							{
								break;
							}
							printf("请输入正确的序号\n");
							continue;;
						}
						fseek(fp,sizeof(Wrsp)*(variable[2]-1),0);
						fread(&a,sizeof(Wrsp),1,fp);
						printf("删除错题：\n第%d题：\n%s\t(%s)\n答案：%s\n",a.num,a.chi,a.lex,a.eng);
						printf("警告：即将删除错题，输入1继续，输入0返回\n");
						while(scanf("%d",&variable[3])!=1)
						{
							printf("格式错误，请重新输入\n");
							getchar();
						}
						switch (variable[3])
						{
							case 0:
								break;
							case 1:
								fclose(fp);
								delspell(x,variable[2]);
								fp=fopen(path,"rb+");
								sum--;
								if(sum==0)
								{
									printf("没有错题记录！\n");
									fclose(fp);
									return;
								}
								if(sum%5==0)
								{
									page--;
									sumpage--;
								}
								flag[1]=1;
								break;
							default:
								printf("请做出正确的选择\n");
								break;
						}
					} while (flag[1]==0);
					break;
				case 6:
					flag[0]=1;
					if(respell(x)==1)
					{
						return;
					}
					break;
				default:
					printf("请做出正确的选择\n");
					break;
			}
		} while (flag[0]==0);
	} while (1);
		
}
void deloption(Stu x,int num)
{
	FILE *fp1,*fp2;
	Wrop a;
	char oldpath[256],newpath[256];
	int i=1;
	snprintf(oldpath,sizeof(oldpath),"./userdata/%s/wrongoption.dat",x.account);
	snprintf(newpath,sizeof(newpath),"./userdata/%s/wrongoption_temp.dat",x.account);
	fp1=fopen(oldpath,"rb+");
	fp2=fopen(newpath,"wb+");
	while(fread(&a,sizeof(Wrop),1,fp1)==1)
	{
		if(a.num==num)
		{
			continue;
		}
		a.num=i++;
		fwrite(&a,sizeof(Wrop),1,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	remove(oldpath);
	rename(newpath,oldpath);
	printf("已删除错题\n"); 
}
void delspell(Stu x,int num)
{
	FILE *fp1,*fp2;
	Wrsp a;
	char oldpath[256],newpath[256];
	int i=1;
	snprintf(oldpath,sizeof(oldpath),"./userdata/%s/wrongspell.dat",x.account);
	snprintf(newpath,sizeof(newpath),"./userdata/%s/wrongspell_temp.dat",x.account);
	fp1=fopen(oldpath,"rb+");
	fp2=fopen(newpath,"wb+");
	while(fread(&a,sizeof(Wrsp),1,fp1)==1)
	{
		if(a.num==num)
		{
			continue;
		}
		a.num=i++;
		fwrite(&a,sizeof(Wrsp),1,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	remove(oldpath);
	rename(newpath,oldpath);
	printf("已删除错题\n"); 
}