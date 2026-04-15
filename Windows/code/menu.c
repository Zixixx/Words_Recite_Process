#include<stdio.h>
#include"menu.h"
void menu_desktop()
{
	printf("-----0 退出         -----\n");
	printf("-----1 账户注册     -----\n");
	printf("-----2 账户登录     -----\n");
	printf("-----3 高级设置     -----\n");
}
void menu_logindesktop()
{
	printf("-----0 退出登录     -----\n");
	printf("-----1 今日打卡     -----\n");
	printf("-----2 单词学习     -----\n");
	printf("-----3 题目练习     -----\n");
	printf("-----4 成绩记录     -----\n");
	printf("-----5 错题复习     -----\n");
}
void menu_score()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 查看最近成绩 -----\n");
	printf("-----2 清除最近成绩 -----\n");
}
void menu_wrong()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 选择题错题   -----\n");
	printf("-----2 拼写题错题   -----\n");
}
void menu_account()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 修改账户     -----\n");
	printf("-----2 删除账户     -----\n");
	printf("-----3 已注册的账户 -----\n");
}
void menu_wordsbook()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 添加单词     -----\n");
	printf("-----2 修改单词     -----\n");
	printf("-----3 删除单词     -----\n");
	printf("-----4 单词本浏览   -----\n");
}
void menu_modacc()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 通过序号修改 -----\n");
	printf("-----2 通过账号修改 -----\n");
	printf("-----3 通过姓名修改 -----\n");
}
void menu_modacc_select()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 修改账号     -----\n");
	printf("-----2 修改姓名     -----\n");
	printf("-----3 修改密码     -----\n");
}
void menu_modwords()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 通过序号修改 -----\n");
	printf("-----2 通过英文修改 -----\n");
}
void menu_modwords_select()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 修改英文     -----\n");
	printf("-----2 修改中文     -----\n");
	printf("-----3 修改词性     -----\n");
}
void menu_delacc()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 通过序号删除 -----\n");
	printf("-----2 通过账号删除 -----\n");
	printf("-----3 通过姓名删除 -----\n");
	printf("-----4 删除所有账户 -----\n");
}
void menu_delwords()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 通过序号删除 -----\n");
	printf("-----2 通过英文删除 -----\n");
	printf("-----3 删除所有单词 -----\n");
}
void menu_practice()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 选择题练习   -----\n");
	printf("-----2 拼写题练习   -----\n");
}
void menu_preacc()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 上一页       -----\n");
	printf("-----2 下一页       -----\n");
	printf("-----3 查看指定页数 -----\n");
	printf("-----4 搜素指定账户 -----\n");
}
void menu_selectacc()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 通过序号搜素 -----\n");
	printf("-----2 通过账号搜素 -----\n");
	printf("-----3 通过姓名搜素 -----\n");
}
void menu_prewords()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 上一页       -----\n");
	printf("-----2 下一页       -----\n");
	printf("-----3 查看指定页数 -----\n");
	printf("-----4 搜素指定单词 -----\n");
}
void menu_selectwords()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 通过序号搜素 -----\n");
	printf("-----2 通过英文搜素 -----\n");
}
void menu_prewrongbook()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 上一页       -----\n");
	printf("-----2 下一页       -----\n");
	printf("-----3 查看指定页数 -----\n");
	printf("-----4 搜素指定错题 -----\n");
	printf("-----5 删除指定错题 -----\n");
	printf("-----6 删除所有错题 -----\n");
}
void menu_systemsetting()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 账户管理     -----\n");
	printf("-----2 单词本管理   -----\n");
	printf("-----3 备份数据     -----\n");
	printf("-----4 恢复数据     -----\n");
	printf("-----5 重置所有数据 -----\n");
	printf("-----6 更改系统密码 -----\n");
}
void menu_restore()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 上一页       -----\n");
	printf("-----2 下一页       -----\n");
	printf("-----3 查看指定页数 -----\n");
	printf("-----4 恢复备份文件 -----\n");
	printf("-----5 删除备份文件 -----\n");
}
void menu_selectrestore()
{
	printf("-----0 返回上一级   -----\n");
	printf("-----1 恢复账户数据 -----\n");
	printf("-----2 恢复单词数据 -----\n");
	printf("-----3 恢复系统密码 -----\n");
	printf("-----4 恢复全部数据 -----\n");
}
