#pragma once

using namespace std;

enum Teststype {closetest = 1, opentest};

enum CloseTests {Naruto = 1, Science, Vutbr};

enum OpenTests {Programator = 1, StarWars, FEKT};

struct login//zapis struktury uduju usera
{
	string jmeno, prijmeni, gender;
	int age;
};

void chooseTest(struct login user, Teststype typ);

void testClose(struct login user, CloseTests type);

void TestProcessClose( int *answersnumber, int *rightanswers, double* percent, CloseTests type);

void CloseTestFilePrint(struct login user, CloseTests type, int answersnumber, int rightanswers, double percent);

void TestStatisticClose(CloseTests type);

void testOpen(struct login user, OpenTests type);

void TestProcessOpen(struct login user, OpenTests type);
