#ifndef _WORDSBOOK
	#define _WORDSBOOK
	struct Word
	{
		int num;	
		char eng[30];
		char chi[30];
		char lex[30];  
	};
	typedef struct Word Wo; 
	void addwords();
	void modwords();
	void delwords();
	void prewords();
#endif