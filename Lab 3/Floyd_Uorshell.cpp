#include<iostream>
#include <fstream>
#include<string>
#include"Used_function.h"
#include"matrix_of_adjacencies.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "RUS");
	ifstream vvod("input.txt");
	List<string>* list_fly = new List<string>();
	string city_Start;
	string city_End;
	InputDataFromFile(list_fly, vvod);
	cout << "Flight schedule: " << endl;
	for (int i = 0; i < list_fly->get_size(); i++)
		cout << list_fly->at(i) << endl;
	cout << "Enter the departure city" << endl;
	getline(cin, city_Start);
	cout << "Enter your arrival city" << endl;
	getline(cin, city_End);
	Matrix* matrix_floid_uorshell = new Matrix(list_fly);
	cout<<matrix_floid_uorshell->Floid_Uorshell(city_Start,city_End)<<endl;
	system("pause");
}


