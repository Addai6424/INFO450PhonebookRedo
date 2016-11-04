#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <Windows.h>
using namespace std;

const int maxcontacts = 100;

class entries
{
	char fullname[50];
	char homephone[13];
	char mobilephone[13];
public:
	entries();
	void setentries(char e1[], char hp[], char mp[]);
	int addentries();
	void display();
	friend class entrylist;
};

entries::entries()
{
	strcpy_s(fullname, "");
	strcpy_s(homephone, "");
	strcpy_s(mobilephone, "");
}

void entries::setentries(char e1[], char hp[], char mp[])
{
	strcpy_s(fullname, e1);
	strcpy_s(homephone, hp);
	strcpy_s(mobilephone, mp);
}

int entries::addentries()
{
	static int num = 0;
	char fullname[50];
	char temp[50];
	char homephone[13];
	char mobilephone[13];

	if (num >= maxcontacts)
	{
		cout << "Phone book is full!" << endl;
	}
	cout << " Enter full name:  " << endl;
	gets_s(fullname);

	for (int i = 0; i < num; i++)
	{
		if (strcmp(fullname, temp) == 0)
		{
			cout << endl;
			cout << temp << "  Already exists in the phonebook!" << endl;
			return num;
		}

		cout << "Please enter home phone number:  " << endl;
		gets_s(homephone);

		cout << "Enter mobilephone number:" << endl;
		gets_s(mobilephone);

		num++;
	}
}
void entries::display()
{
	printf("Name: %s  Homephone number: %s  Mobilephone number: %s \n",
		fullname, homephone, mobilephone);
}

class entrylist
{
	char filename[100];
	int entriescount;
	entries **mylist;
public:
	entrylist();
	~entrylist();
	void setFilename(char f[]);
	int getCount();
	void addtolist(entries *b);
	void showlist();
	int savelist();
	void readlist();
};
entrylist::entrylist()
{
	mylist = new entries*[100];
	entriescount = 0;
}
entrylist::~entrylist()
{
	delete mylist;
}
void entrylist::setFilename(char f[])
{
	strcpy_s(filename, f);
}
void entrylist::addtolist(entries *b)
{
	mylist[entriescount] = b;
	entriescount++;
}
int entrylist::getCount()
{
	return entriescount;
}
void entrylist::showlist()
{
	for (int i = 0; i < entriescount; i ++)
	{
		mylist[i]->display();
	}
}

int entrylist::savelist()
{
	ofstream output(filename);
	if (!output)
	{
		cout << " " << endl;
		return -1;
	}
	for (int i = 0; i < entriescount; i++)
	{
		output << mylist[i]->fullname << " | ";
		output << mylist[i]->homephone << " | ";
		output << mylist[i]->mobilephone << endl;
	}
	output.close();
	return 0;
}
void entrylist::readlist()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		entries *ptr;
		char fullname[50];
		char homep[13];
		char mobilep[13];

		infile.getline(fullname, 50, ',');
		if (strlen(fullname))
		{
			infile.getline(homep, 13, ',');
			infile.getline(mobilep, 13);
			ptr = new entries();
			ptr->setentries(fullname, homep, mobilep);
			addtolist(ptr);
		}
	}
	infile.close();
}
int main()
{
	char fullname[50];
	char homephone[13];
	char mobilephone[13];
	char filename[50];
	char response;

	entrylist *blist = new entrylist();

	cout << "Please enter full path filename" << endl;
	gets_s(filename);
	blist->setFilename(filename);

	blist->readlist();
	if (blist->getCount() == 0)
	{
		cout << "your list is empty! Continue" << endl;
	}
	else
	{
		cout << "You have " << blist->getCount() << "entry(ies) in your list." << endl;
	}

	cout << "Add new entry? Enter Y/y for yes; anything else for no" << endl;
	cin >> response;

	while (response == 'Y' || response == 'y')
	{
		cin.ignore();
		cin.clear();
		cout << "Enter full name" << endl;
		gets_s(fullname);
		cout << "Enter homephone number" << endl;
		gets_s(homephone);
		cout << "Enter mobilephone number" << endl;
		gets_s(mobilephone);

		entries *myentry = new entries();
		myentry->setentries(fullname, homephone, mobilephone);
		blist->addtolist(myentry);

		cout << "Another? Enter Y to add" << endl;
		cin >> response;
	}
	system("PAUSE");
	system("CLS");
	blist->showlist();
	blist->savelist();
	return 0;
}

