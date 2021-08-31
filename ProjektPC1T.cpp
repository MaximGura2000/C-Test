#include <iostream>
#include <ctype.h>
#include <fstream>
#include "ProjektHeader1.h"

using namespace std;



int main()
{
	struct login user;//zapis uduju do struktury
	cout << "Enter your name, surname, age and gender" << endl<<"Name: ";
	cin >> user.jmeno;//jmeno
	cout << endl << "Surname: ";
	cin >> user.prijmeni;//prijmeni 
	cout << endl << "Age: ";
	cin >> user.age;//vek
	cout << endl << "Gender: ";
	cin >> user.gender;//gender

	int choise;
	cout << endl << "Press 1 if you want close tests or 2 if you want open tests" << endl << "You choise is: ";
	cin >> choise;
	chooseTest(user, Teststype(choise));

	system("pause");
	return 0;

}
