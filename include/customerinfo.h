#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H
typedef struct {//stores informations of registered customer
	char userId[10];	//customer user I.D.
	char name[20];		//customer name
	int age;		//customer age
	char address[20];	//customer adderess
	char pass[20];		//customer password
	int idNo;
}customerinfo;
#endif
