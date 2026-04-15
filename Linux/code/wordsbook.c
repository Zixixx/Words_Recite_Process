#include<stdio.h>
#include<string.h>
#include"wordsbook.h"
#include"file.h"
#include"menu.h"
void addwords()
{
	FILE *fp;
	fp=fopen("./system/wordsbook.dat","rb+");
	Wo a,b;
	int i=0,flag=0;
	do
	{
	    switch(flag)
		{
			case 0:
			case 1:
				printf("请输入新单词的英文,输入0返回\n");
				scanf("%s",a.eng);
				flag=0;
				if(a.eng[0]=='0'&&strlen(a.eng)==1)
				{
					return;
				}
				while(!feof(fp))
				{
					fread(&b,sizeof(Wo),1,fp);
					if(strcmp(a.eng,b.eng)==0)
					{
						printf("该单词已存在，请重新输入英文\n");
						flag=1; 
						break;
					}
				}
				rewind(fp);
				break;
			default:
				break;
		}
		switch (flag)
		{
			case 0:
			case 2:
				printf("请输入新单词的中文，输入0返回\n");
				scanf("%s",a.chi);
				flag=0;
				if(a.chi[0]=='0'&&strlen(a.chi)==1)
				{
					flag=1;
					break;
				}
				break;
			default:
				break;
		}
		switch (flag)
		{
			case 0:
				printf("请输入新单词的词性，输入0返回\n");
				scanf("%s",a.lex);
				flag=0;
				if(a.lex[0]=='0'&&strlen(a.lex)==1)
				{
					flag=2;
					break;
				}
				while(fread(&b,sizeof(Wo),1,fp)==1)
				{
					i++;
				}
				a.num=i+1;
				fwrite(&a,sizeof(Wo),1,fp);
				fclose(fp);
				printf("单词添加成功\n");
				return;
			default:
				break;
		}
    }while(1);
}
void modwords()
{
	FILE *fp;
	fp=fopen("./system/wordsbook.dat","rb+");
	Wo a,b;
	char modify[30];
	int variable[2],sum=0,exist,repeat,flag,m,n,i,offset,flag1,flag2;
	while(fread(&a,sizeof(Wo),1,fp)==1)
	{
		sum++;
	}
	if(sum==0)
	{
		printf("单词表中没有单词！\n");
		fclose(fp);
		return;
	}
	do
	{
		menu_modwords();
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
					printf("请输入想要修改的单词的序号(1-%d),输入0返回\n",sum);
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
					fseek(fp,sizeof(Wo)*(variable[1]-1),0);
					fread(&a,sizeof(Wo),1,fp);
					break;
				} while (exist==0);
				break;
			case 2:
				do
				{
					printf("请输入想要修改的英文,输入0返回\n");
					scanf("%s",modify);
					if(modify[0]=='0'&&strlen(modify)==1)
					{
						break;
					}
					rewind(fp);
					while(fread(&a,sizeof(Wo),1,fp)==1)
					{
						if(strcmp(a.eng,modify)==0)
						{
							exist=1;
							break;
						}
					}
					if(exist==0)
					{
						printf("该英文不存在，请输入正确的英文\n");
						continue;
					}
				} while (exist==0);
				break;
			default:
				break;
		}
		if(exist==1)
		{
			do
			{
				flag=0;
				printf("修改单词：\n英文：%-30s\t中文：%-30s\t词性：%-30s\n请做出你的选择:\n",a.eng,a.chi,a.lex);
				menu_modwords_select();
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
							printf("请输入新的英文，输入0返回上一级\n");
							scanf("%s",modify);
							if(modify[0]=='0'&&strlen(modify)==1)
							{
								break;
							}
							repeat=0;
							rewind(fp);
							while(fread(&b,sizeof(Wo),1,fp)==1)
							{
								if(strcmp(b.eng,a.eng)==0)
								{
									printf("该英文已存在，请重新输入\n");
									repeat=1;
									break;
								}
							}
							if(repeat==0)
							{
								strcmp(a.eng,modify);
								fseek(fp,sizeof(Wo)*(a.num-1),0);
								fwrite(&a,sizeof(Wo),1,fp);
								fclose(fp);
								printf("修改成功\n");
								return;
							}
						}while(repeat==1);
						break;
					case 2:
						do
						{
							printf("请输入新的中文，输入0返回上一级\n");
							scanf("%s",a.chi);
							if(modify[0]=='0'&&strlen(modify)==1)
							{
								break;
							}
							strcmp(a.chi,modify);
							fseek(fp,sizeof(Wo)*(a.num-1),0);
							fwrite(&a,sizeof(Wo),1,fp);
							fclose(fp);
							printf("修改成功\n");
							return;
						}while(1);
						break;
					case 3:
						do
						{
							printf("请输入新的词性，输入0返回上一级\n");
							scanf("%s",modify);
							if(modify[0]=='0'&&strlen(modify)==1)
							{
								break;
							}
							strcmp(a.lex,modify);
							fseek(fp,sizeof(Wo)*(a.num-1),0);
							fwrite(&a,sizeof(Wo),1,fp);
							fclose(fp);
							printf("修改成功\n");
							return;
						}while(1);
						break;
					default:
						printf("请做出正确的选择\n");
						break;
				}
			}while(flag==0);
		}
	} while (1);
}
void delwords()
{
	FILE *fp1,*fp2;
	Wo a,b;
	int variable[2],exist,flag,sum=0,x;
	char modify[30];
	fp1=fopen("./system/wordsbook.dat","rb+");
	while(fread(&a,sizeof(Wo),1,fp1)==1)
	{
		sum++;
	}
	if(sum==0)
	{
		printf("单词表中没有单词！\n");
		fclose(fp1);
		return;
	}
	do
	{
	    menu_delwords();
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
					printf("请输入想要删除的单词的序号(1-%d),输入0返回\n",sum);
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
					fseek(fp1,sizeof(Wo)*(variable[1]-1),0);
					fread(&a,sizeof(Wo),1,fp1);
					break;
				} while (exist==0);
				break;
			case 2:
				do
				{
					printf("请输入想要删除的单词的英文,输入0返回\n");
					scanf("%s",modify);
					if(modify[0]=='0'&&strlen(modify)==1)
					{
						break;
					}
					rewind(fp1);
					while(fread(&a,sizeof(Wo),1,fp1)==1)
					{
						if(strcmp(a.eng,modify)==0)
						{
							exist=1;
							break;
						}
					}
					if(exist==0)
					{
						printf("该英文不存在，请输入正确的英文\n");
						continue;
					}
				} while (exist==0);
				break;
			case 3:
				x=reword();
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
				printf("删除单词：\n英文：%-30s\t中文：%-30s\t词性：%-30s\n警告：即将删除单词，输入1继续，输入0返回\n",a.eng,a.chi,a.lex);
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
						fp2=fopen("./system/wordsbook_temp.dat","wb+");	
						rewind(fp1);
						while(fread(&b,sizeof(Wo),1,fp1)==1)
						{
							if(b.num==a.num)
							{
								continue;
							}
							fwrite(&b,sizeof(Wo),1,fp2);
						}
						fclose(fp1);
						fclose(fp2);
						remove("./system/wordsbook.dat");
						rename("./system/wordsbook_temp.dat","./system/wordsbook.dat");
						printf("已删除单词\n"); 
						return;
					default:
						printf("请做出正确的选择\n");
						break;
				}
			}while(flag==0);
		}
    }while(1);
} 
void prewords()
{
	FILE *fp;
	fp=fopen("./system/wordsbook.dat","rb+");
	Wo a;
	int page=0,sum=0,sumpage,variable[4],flag[2],i,exist;
	char english[30];
	while(fread(&a,sizeof(Wo),1,fp)==1)
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
		printf("%-30s\t%-30s\t%-30s\t%-30s\n","序号","英文","中文","词性");
		fseek(fp,sizeof(Wo)*page*10,0);
		for(i=0;i<10;i++)
		{
			if(fread(&a,sizeof(Wo),1,fp)==1)
			{
				printf("%-30d\t%-30s\t%-30s\t%-30s\n",a.num,a.eng,a.chi,a.lex);
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
			menu_prewords();
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
						printf("单词表中没有单词！\n");
						break;
					}
					do
					{
						flag[1]=0;
						menu_selectwords();
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
									printf("请输入想要查询的单词的序号(1-%d)，输入0返回：\n",sum);
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
										continue;
									}
									fseek(fp,sizeof(Wo)*(variable[3]-1),0);
									fread(&a,sizeof(Wo),1,fp);
									printf("%-30s\t%-30s\t%-30s\t%-30s\n","序号","英文","中文","词性");
									printf("%-30d\t%-30s\t%-30s\t%-30s\n",a.num,a.eng,a.chi,a.lex);
								} while (1);
								break;
							case 2:
								do
								{
									printf("请输入想要查询的单词的英文，输入0返回：\n");
									scanf("%s",english);
									if(english[0]=='0'&&strlen(english)==1)
									{
										break;
									}
									rewind(fp);
									exist=0;
									while(fread(&a,sizeof(Wo),1,fp)==1)
									{
										if(strcmp(a.eng,english)==0)
										{
											exist=1;
											break;
										}
									}
									if(exist==0)
									{
										printf("该单词不存在\n");
										continue;
									}
									printf("%-30s\t%-30s\t%-30s\t%-30s\n","序号","英文","中文","词性");
									printf("%-30d\t%-30s\t%-30s\t%-30s\n",a.num,a.eng,a.chi,a.lex);
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