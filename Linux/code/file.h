#include"account.h"
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0755)
#endif
#ifndef _FILE
	#define _FILE
	struct Syspassword
	{
		char password[16];
	};
	typedef struct Syspassword Syspass; 
	struct Backupname
	{
		char name[30];
	};
	typedef struct Backupname Bkname; 
	void judge();
	int settingjudge();
	void modpassword();
	void mkuserfile(Stu x);
	int refile();
	int reuser();
	int reword();
	void rescore(Stu x);
	int reoption(Stu x);
	int respell(Stu x);
	void backup();
	void restore();
#endif