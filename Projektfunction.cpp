#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "ProjektHeader1.h"


using namespace std;

void chooseTest(struct login user, Teststype typ)//funkce pro vyber typu testu
{
	if (typ == 1)//close test
	{
		cout << "Choose test you want to have :"<< endl << "Naruto test (press 1)" << endl << "Science test (press 2)" 
		<< endl << "VUT test (press 3)"<<endl;
		int choise;//case for test type
		cin >> choise;
		testClose(user,  CloseTests(choise));
	}
	if (typ == 2)//open test
	{
		cout << "choose test you want to have :" << endl << "Programator test (press 1)" << endl << "Star Wars test (press 2)"
			<< endl << "FEKT test (press 3)" << endl;
		int choise;//case for test type
		cin >> choise;
		testOpen(user, OpenTests(choise));
	}
}

void testClose(struct login user, CloseTests type)
{
	int answersnumber;//number of ansers
	int rightanswers = 0;// number of right answers
	double percent;
	if (type == 1)
	{
		TestProcessClose( &answersnumber, &rightanswers, &percent, CloseTests(type));
		CloseTestFilePrint(user, CloseTests(type), answersnumber, rightanswers, percent);
		TestStatisticClose(CloseTests(type));
	}
	if (type == 2)
	{
		TestProcessClose(&answersnumber, &rightanswers, &percent, CloseTests (type));
		CloseTestFilePrint(user, CloseTests(type), answersnumber, rightanswers, percent);
		TestStatisticClose(CloseTests(type));
	}
	if (type == 3)
	{
		TestProcessClose(&answersnumber, &rightanswers, &percent, CloseTests(type));
		CloseTestFilePrint(user, CloseTests(type), answersnumber, rightanswers, percent);
		TestStatisticClose(CloseTests(type));
	}
}

void TestProcessClose( int *answersnumber, int *rightanswers, double *percent, CloseTests type)
{
	string str; //case for line detection
	ifstream file;// test file
	bool answer=true;// case for cheking if program print answers or questions
	int step = 0;// case for right answers work
	char youranswers[20];// case for users answers
	int i = 0;// integer for control answers
	if (type==1)
		file.open("closetesty\\NarutoTest\\NarutoExpert.txt");

	else if (type==2)
		file.open("closetesty\\Science\\Science.txt");

	else if (type==3)
		file.open("closetesty\\VUTTest\\VUTTest.txt");

	if (file)
	{
		while (!file.eof())
		{
			if (step == 0)
			{
				getline(file, str, '\n');
				step++;
			}
			else if ((isdigit(str[0]) || (str[0] >= 'a' && str[0] <= 'f')) && step <=1)
			{
				answer = false;
				cout << str;
				cout << endl;
				getline(file, str, '\n');
			}
			else if (answer == false)//user give answer
			{
				answer = true;
				cout << str;
				cout << endl;
				getline(file, str, '\n');
				cout << "You answer is: ";
				cin >>youranswers[i];
				i++;//i = number of question answers
			}
			else
			{
				if (step > 1)
				{
					getline(file, str, '\n');
					if (!isdigit(str[1]))
						cout << i + 1 << " Question:" << endl << "Right answer is " << str[2] << endl << "Your answer is " << youranswers[i] << endl;
					if (isdigit(str[1]))
						cout << i + 1 << " Question:" << endl << "Right answer is " << str[3] << endl << "Your answer is " << youranswers[i] << endl;
					if (youranswers[i] == str[2] && !isdigit(str[1]))//for questions below 10
					{
						*rightanswers = *rightanswers + 1;
						for (int j = 3; str[j] != ';' ; j++)
							cout << str[j];
						cout << endl;
					}
					if (youranswers[i] == str[3] && isdigit(str[1]))//for questions below 10
					{
						*rightanswers = *rightanswers + 1;
						for (int j = 4; str[j] != ';' ; j++)
							cout << str[j];
						cout << endl;
					}
					i++;
					cout << endl;
				}
				else
				{
					*answersnumber = i;
					cout << str;
					cout << endl;
					i = 0;
					step++;
				}
			}
			
		}
		file.close();
	}
	else
		cout << "error, cant open file";
	*percent = (*rightanswers * 100) / *answersnumber;
	cout << "You result is " << *rightanswers << " right answers between " << *answersnumber << " question" << endl;
	cout << "Test result is " << *percent << "%"<<endl;
}

void CloseTestFilePrint(struct login user, CloseTests type, int answersnumber, int rightanswers, double percent)
{
	ofstream Filezapisu;//chceme otevrit file pro zapis textu do neho
	if (type == 1)
		Filezapisu.open("closetesty\\NarutoTest\\NarutoExpertTestStats.txt", ios::app);//otevirame fail a zapisujeme v jeho konec

	else if (type ==2)
		Filezapisu.open("closetesty\\Science\\ScienceTestStats.txt", ios::app);//otevirame fail a zapisujeme v jeho konec

	else if (type == 3)
		Filezapisu.open("closetesty\\VUTTest\\VUTTestStats.txt", ios::app);

	Filezapisu << user.jmeno << " " << user.prijmeni << endl << user.age << " ages" << endl << "Gender is " << user.gender << endl;
	Filezapisu << "Test got "<< answersnumber << " questions and user pass test with result of "<< rightanswers << " right answers"
	<<endl<<"Percent is "<<percent<<"%"<<endl<<endl;

	Filezapisu.close();

}

void TestStatisticClose(CloseTests type)
{
	ifstream file;
	string str;
	int sum=0;//sum of percent
	int number=0;//number of all tests
	if (type == 1)
		file.open("closetesty\\NarutoTest\\NarutoExpertTestStats.txt");

	else if (type == 2)
		file.open("closetesty\\Science\\ScienceTestStats.txt");
	else if (type == 3)
		file.open("closetesty\\VUTTest\\VUTTestStats.txt");

	while (!file.eof())
	{
		getline(file, str, '\n');
		if (str[0] == 'P' && str[1] == 'e' && str[2] == 'r' && str[3] == 'c')
		{
			for (int i = 6; i < 20; i++)
			{
				if (isdigit(str[i]))
				{
					if (isdigit(str[i + 2]))
					{
						sum = sum + 100;
						number++;
						getline(file, str, '\n');
						i = 20;
						}
					else  if (isdigit(str[i + 1]) && (!isdigit(str[i + 2])))
					{
						sum = sum + 10*(str[i]-48) + str[i+1]-48;//v ASCII 0='48', 1='49'
						number++;
						getline(file, str, '\n');
						i = 20;
					}
				}
			}
		}
	}

	double allresult;
	allresult = sum / number;
	cout << "All users tests average result is: " << allresult<< "%" << endl;
	
}

void testOpen(struct login user, OpenTests type)
{
	if (type == 1)
		TestProcessOpen(user, OpenTests(type));
	if (type == 2)
		TestProcessOpen(user, OpenTests(type));
	if (type == 3)
		TestProcessOpen(user, OpenTests(type));
}

void TestProcessOpen(struct login user, OpenTests type)
{
	string str; //case for line detection
	ifstream file;// test file
	ofstream File;// answers file
	char answer[20];// case for users answers
	int count = 1;//answer count

	if (type == 1)
	{
		file.open("opentesty\\Programator\\ProgramatorOpenTest.txt");
		File.open("opentesty\\Programator\\ProgramatorOpenTestAnswer.txt", ios::app);
	}
	else if (type == 2)
	{
		file.open("opentesty\\StarWars\\StarWarsOpenTest.txt");
		File.open("opentesty\\StarWars\\StarWarsOpenTestAnswer.txt", ios::app);
	}

	else if (type == 3)
	{
		file.open("opentesty\\FEKT\\FEKTOpenTest.txt");
		File.open("opentesty\\FEKT\\FEKTOpenTestAnswer.txt", ios::app);
	}

	File << user.jmeno << " " << user.prijmeni << endl << "Age is " << user.age << " years" << endl << "Gender is " << user.gender << endl;

	if (file)
	{
		while (!file.eof())
		{
			getline(file, str, '\n');
			cout<<str<<endl<<"Your answer is (if you wants to end you answer wright 'nxt') : ";
			File << count << " question answer: ";
			cin >> answer;
			while (strcmp(answer, "nxt")!=0)
			{
				File << answer << " ";
				cin >> answer;
			}
			File << endl;
			count++;
			getline(file, str, '\n');
		}
		File << endl;
		file.close();
		File.close();
		cout << "Your answers are saved to the text file, wait for checking" <<endl;
	}
	else
		cout << "error, cant open file";
}


