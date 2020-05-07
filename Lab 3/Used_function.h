#pragma once
#include<string>
#include <fstream>
#include"List.h"
void InputDataFromFile(List<string>* data, ifstream& file) {//גגמה טח פאיכא
	while (!file.eof()) {
		string s1;
		getline(file, s1);
		data->push_back(s1);
	}
}