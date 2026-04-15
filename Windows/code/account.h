#ifndef _ACCOUNT
	#define _ACCOUNT
	struct Student
	{
		char account[20];
		char password[16];
		char name[20]; 
		double score[20];
		int day;
		int year;
		int num;
		int times;
	};
	typedef struct Student Stu; 
	void regist();
	Stu login();
	void mark(Stu x,double score);
	void cheek(Stu x);
	void record(Stu x);
	void delacc();
	void modacc();
	void preacc();
#endif
