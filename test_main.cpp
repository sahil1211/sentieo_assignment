#include<bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
	string input_file = argv[1];
	string output_file = argv[2];
	ifstream i_file(input_file);
	string line;
	vector<string> i_vec, o_vec;
	if(!i_file.is_open()) {
		cout<<"ERROR: Expected Output File not open!!! \n";
	} else {
		ifstream o_file(output_file);
		if(!o_file.is_open()) {
			cout<<"ERROR: Output File not open!! \n";
		} else {
			while(getline(i_file, line)) {
				i_vec.push_back(line);
			}
			while(getline(o_file, line)) {
				o_vec.push_back(line);
			}
		}
		int i_size = i_vec.size();
		int o_size = o_vec.size();
		if(i_size == o_size)  {
			bool flag = false;
			for(int i = 0;i  < i_size; i++) {
				if (i_vec[i] != o_vec[i]) {
					cout<<"Records Differ"<<endl;
					cout<<"Expected Output File: "<<i_vec[i]<<endl;
					cout<<"Output File: "<<o_vec[i]<<endl;
					flag = true;
					break;
				}
			}
			if(!flag) {
				cout<<"Test Cases Passed!!!!"<<endl;
			}
		} else {
			cout<<"Difference in no of records"<<endl;
			cout<<"Expected Output File: "<<i_size<<endl;
			cout<<"Output File: "<<o_size<<endl;
		}
		o_file.close();
	}
	i_file.close();
	return 0;
}

