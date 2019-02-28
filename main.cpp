#pragma GCC optimize ("Ofast")

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Ride{
public:
    
    Ride();
    ~Ride();
};

class Vehicle{
public:
    int id;

    Vehicle();
    ~Vehicle();
};
class Position{};

// auto compare = [](const Ride& r1, const Ride& r2) -> bool {
//     if (r1.m_speed != r2.m_speed)
//         return r1.m_speed < r2.m_speed;
//     return r1.x0() <= r2.x0();
// };


void readFile(unsigned int fileIndex, string* inputFilePaths, int size, int& rows, int& columns, int& F, int& N, int& bonus, int& T, vector< vector<int> >& data)
{
	ifstream file(inputFilePaths[fileIndex]);

	string line;
	stringstream buffer;

	while (getline(file, line))
	{
		buffer << line << '\n';
	}

	cout << buffer.str() << endl;
	buffer >> rows >> columns >> F >> N >> bonus >> T;

	data.resize(N);
	for (int i = 0; i < N; i++)
	{
		data[i].resize(6);
		for (int j = 0; j < 6; j++)
		{
			buffer >> data[i][j];
		}
	}
}

void writeFile(unsigned int fileIndex, string* outputFilePaths, int size, const vector<Vehicle>& fleet)
{
	ofstream output;
	output.open(outputFilePaths[fileIndex]);
	for (unsigned int v = 0; v < fleet.size(); v++)
	{
		// vector<int> finalRides = fleet[v].id;
		// output << finalRides.size() << " ";
		// for (auto it : finalRides)
		// {
		// 	output << it << " ";
		// }
		output << '\n';
	}
	output.close();

}

const int NUM_FILES = 5;

int main() {

	unsigned int fileIndex = 0;
	string inputFilePaths[NUM_FILES] = { "Files/a.in", "Files/b.in", "Files/c.in", "Files/d.in", "Files/e.in" };
	
	int rows, columns, F, N, bonus, T;
	vector< vector<int> > data;
	
	readFile(fileIndex, inputFilePaths, NUM_FILES, rows, columns, F, N, bonus, T, data);

	// Rides
	vector<Ride> rides;
	rides.resize(N);
	for (int i = 0; i < N; i++)
		rides[i] = Ride();

	// Vehicles
	vector<Vehicle> fleet;
	fleet.resize(F);
	for (int i = 0; i < F; i++)
		fleet[i] = Vehicle();

	// MAIN LOOP

	// Output
	string outputFilePaths[5] = { "Files/output_a.out" ,"Files/output_b.out" ,"Files/output_c.out" ,"Files/output_d.out", "Files/output_e.out" };
	writeFile(fileIndex, outputFilePaths, outputFilePaths->size(), fleet);
	
	return 0;
}