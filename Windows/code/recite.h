#include"account.h"
#ifndef _RECITE
	#define _RECITE
	struct Option
	{
		int num;
		char chi[30];
		char eng[30];
	};
	typedef struct Option Opt;
	struct Wroption
	{
		int num;
		char eng[30];
		char chi1[30];
		char chi2[30];
		char chi3[30];
		char chi4[30];
		char ans[30];
	};
	typedef struct Wroption Wrop; 
	struct Wrspell
	{
		int num;
		char eng[30];
		char chi[30];
		char lex[30];
	};
	typedef struct Wrspell Wrsp; 
	void opt(Stu x,int num);
	void spe(Stu x,int num);
	void revoption(Stu x);
	void revspell(Stu x);
	void deloption(Stu x,int num);
	void delspell(Stu x,int num);
#endif
