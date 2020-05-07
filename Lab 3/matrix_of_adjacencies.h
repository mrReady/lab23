#pragma once
#include"List.h"
#include"Map.h"
#include<string>
class Matrix {
public:
	Matrix(List<string>* data) {
		    map_City_name_to_index=new Map<string, int>();
		    map_index_to_name_City=new Map<int, string>();
			int N = data->get_size();
			int index_city = 0;
			for (int i = 0; i < N; i++) {
				string str_cur = data->at(i);
				int cur = str_cur.find(';');//the first occurrence
				int cur1 = str_cur.find(';', cur + 1);//the second occurrence
				string str_name_city1 = str_cur.substr(0, cur);//get first city
				string str_name_city2 = str_cur.substr(cur + 1, cur1 - cur - 1);//get second city
				str_name_city2.erase(0, 1);
				if (!map_City_name_to_index->find_is(str_name_city1)) {
					map_City_name_to_index->insert(str_name_city1, index_city);
					map_index_to_name_City->insert(index_city, str_name_city1);
					index_city++;
				}
				if (!map_City_name_to_index->find_is(str_name_city2)) {
					map_City_name_to_index->insert(str_name_city2, index_city);
					map_index_to_name_City->insert(index_city, str_name_city2);
					index_city++;
				}
			}
			/////////////////////////////////////////////////////////////////////////////make matrix path
			size_of_matrix = index_city;
			matrix = new double* [size_of_matrix];
			for (int i = 0; i < size_of_matrix; i++)
				matrix[i] = new double[size_of_matrix];
			for (int i = 0; i < size_of_matrix; i++)
				for (int j = 0; j < size_of_matrix; j++)
					matrix[i][j] = INF;
			/////////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////////////input matrix path
			for (int i = 0; i < N; i++) {
				int price_1_to_2 = INF;
				int price_2_to_1 = INF;
				string str_cur = data->at(i);
				int cur = str_cur.find(';');
				int cur1 = str_cur.find(';', cur + 1);
				int cur2 = str_cur.find(';', cur1 + 1);
				int cur3 = str_cur.find(';', cur2 + 1);
				string str_name_city1 = str_cur.substr(0, cur);
				string str_name_city2 = str_cur.substr(cur + 1, cur1 - cur - 1);
				str_name_city2.erase(0, 1);
				if (str_cur.substr(cur1 + 2, cur2 - 2 - cur1) != "N/A")
					price_1_to_2 = stof(str_cur.substr(cur1 + 2, cur2 - 2 - cur1));
				if (str_cur.substr(cur2 + 2, cur3 - 1) != "N/A")
					price_2_to_1 = stoi(str_cur.substr(cur2 + 2, cur3 - 2 - cur2));

				matrix[map_City_name_to_index->find(str_name_city1)][map_City_name_to_index->find(str_name_city2)] = price_1_to_2;

				matrix[map_City_name_to_index->find(str_name_city2)][map_City_name_to_index->find(str_name_city1)] = price_2_to_1;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	string Floid_Uorshell(string start_City,string end_City) {
		string cur;
		while (!map_City_name_to_index->find_is(start_City)) {
			cout << "The departure city is missing, enter it again" << endl;
			cin >> start_City;
		}
		while (!map_City_name_to_index->find_is(end_City)) {
			cout << "The arrival city is missing, enter it again" << endl;
			cin >> end_City;
		}
		int index_start_vertex = map_City_name_to_index->find(start_City);
		int index_end_vertex = map_City_name_to_index->find(end_City);
		int** pre = new int* [size_of_matrix];
		for (int i = 0; i < size_of_matrix; i++) {
			pre[i] = new int[size_of_matrix];
			for (int j = 0; j < size_of_matrix; j++)
				pre[i][j] = i;
		}
		for (int k = 0; k < size_of_matrix; ++k)
			for (int i = 0; i < size_of_matrix; ++i)
				for (int j = 0; j < size_of_matrix; ++j) {
					if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
						matrix[i][j] = matrix[i][k] + matrix[k][j];
						pre[i][j] = pre[k][j];
					}
				}
		if (matrix[map_City_name_to_index->find(start_City)][map_City_name_to_index->find(end_City)] != INF) {
			cur = "The best route for the price: " + to_string(matrix[map_City_name_to_index->find(start_City)][map_City_name_to_index->find(end_City)]) + '\n' + "Route: ";
			print_path(index_start_vertex, index_end_vertex, pre, map_index_to_name_City, cur);
			cur.erase(cur.size() - 3);
		}
		else {
			cur = "This route can't be built, try waiting for the flight schedule for tomorrow!";
		}
		return cur;
	}
private:
	void print_path(int i, int j, int** p, Map<int, string>* map_index_to_name_City,string&cur) {
		if (i != j)
			print_path(i, p[i][j], p, map_index_to_name_City,cur);
		cur=cur+map_index_to_name_City->find(j)+" -> ";
	}
	double** matrix;
	int size_of_matrix;
	Map<string, int>* map_City_name_to_index;
	Map<int, string>* map_index_to_name_City;
	const int INF = 1000000000;
};