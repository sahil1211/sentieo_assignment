#include<bits/stdc++.h>

using namespace std;


#define split(str, delim, type) (split_fn<type<std::string>>(str, delim))

// Returns an vector of the ouptut coming after splitting the string
// Example:
// '1, 2, 3, 4' return [1, 2, 3, 4]
template <typename Container>
Container split_fn(const std::string& str, char delim = ' ') {
    Container cont{};
    std::size_t current, previous = 0;
    current = str.find(delim);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(delim, previous);
    }
    cont.push_back(str.substr(previous, current - previous));

    return cont;
}

// Used to do date related operations
class Date {
	// (day, month, year) - denotes day, month and year
	// weekday - determine the weekday 0 for Sunday and so on
	int day, month, year, weekday;

	// Determine the weekday
	// and store in the weekdy variable
	// also set the is_weekend variable
	void check_day() {
		int y = this->year;
		int d = this->day;
		int m = this->month;
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    	y -= m < 3;
    	this->weekday = ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
    	if(this->weekday == 0 || this->weekday == 6) {
    		this->is_weekend = true;
    	} else {
    		this->is_weekend = false;
    	}
	}
public:
	// Used to determine if it's a weekend (Sat Sun)
	bool is_weekend;
	Date(string date) {
		vector<string> d = split(date, '/', vector);
		this->month = stoi(d[0]);
		this->day = stoi(d[1]);
		this->year = stoi(d[2]);
		this->check_day();
	}
	// returns the date in dd/mm/yyyy format
	string get_date_string() {
		return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
	}

};

class Entry {
	// price in the entry
	double price;
	vector<double> average;
public:
	// Date of entry
	Date *date;
	Entry(string date_str, string price, int avgSize) {
		this->date = new Date(date_str);
		this->price = stod(price);
		for(int i = 0;i < avgSize; i++) {
			this->average.push_back(-1);
		}
	}
	// Set the average value on the entry
	void set_average(double an , int a ) {
		this->average[a] = an ;
	}
	// Return the price on the entry
	double get_price() {
		return this->price;
	}
	// Return the entry row
	string get_row() {
		string row = this->date->get_date_string() + "," + to_string(price) + ",";
		if(!this->date->is_weekend) {
			row += to_string(price);
			for(int i = 0;i < this->average.size();i++) {
                double val = this->average[i];
                if(val == -1 ) {
                    row = row + ",-";
                }
                else {
                    row = row + ',' + to_string(val);
                }
            }
		}
		else{
            for(int i = 0;i < this->average.size();i++) {
                row += "," ;
            }
		}
		return row;
	}

};


class StockSheet{
	string headers;
	vector<int> avg;
	vector<Entry> entries;

	// Fetch the averages required to be calculated
	void get_averages() {
		vector<string> h_items = split(this->headers, ',', vector);
		for(int i = 3; i < h_items.size(); i++) {
			this->avg.push_back(stoi(split(h_items[i], ' ', vector)[0]));
		}
	}
	// Calculate the averages for the prices
	void calulate_averages() {
		vector<double> prefixSum;
		double cumSum = 0, an;
		int n;
		for(int i = 0; i<this->entries.size(); i++) {
			if(!this->entries[i].date->is_weekend) {
				cumSum += this->entries[i].get_price();
				prefixSum.push_back(cumSum);
				int sz = prefixSum.size();
				for(int a = 0; a < this->avg.size(); a++) {
					n = this->avg[a];
					if (n <= sz) {
						an = n == sz ? prefixSum[sz-1] : prefixSum[sz-1] - prefixSum[sz-n-1];
						an /= n;
						this->entries[i].set_average(an , a) ;
					}
				}
			}
		}
	}

	public:
		StockSheet(string input_file) {
			ifstream file(input_file);
			if(!file.is_open()) {
				cout<<"ERROR: File not open!!! \n";
			} else {
				string line;
				getline(file, line);
				this->headers = line;
				this->get_averages();
				while(getline(file, line)) {
					vector<string> v = split(line, ',', vector);
					entries.push_back(Entry(v[0], v[1], this->avg.size()));
				}
			}
			file.close();
			this->calulate_averages();
		}
		// Display the current StockSheet
		void display_rows() {
			cout<<this->headers<<endl;
			for(int i = 0;i < this->entries.size(); i++) {
				cout<<this->entries[i].get_row()<<endl;
			}
		}
		// Used to generate the current StockSheet to CSV
		void write_to_file(string output_file) {
			ofstream file;
			file.open(output_file);
			file << headers <<endl;
			for(int i = 0; i<this->entries.size(); i++) {
				file << this->entries[i].get_row() << endl;
			}
			file.close();
		}

};

// driver function
int main(int argc, char** argv) {
	string input_file = argv[1];
	string output_file = argv[2];
	StockSheet s(input_file);
	//s.display_rows();   // used to display the rows in the StockSheet
	s.write_to_file(output_file);
	return 0;
}

