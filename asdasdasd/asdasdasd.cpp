#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	vector<string> filetext;
	vector<string> text;
	string line;

	ifstream file("text.txt");
	file.imbue(locale("ry_RU.UTF-8"));

	
	while (getline(file, line)) {
		cout << line << endl;
		filetext.push_back(line);
		
	}

	for (int i = 0; i < filetext.size() / 2; i++) {
		text.push_back(filetext[i * 2] + ": " + filetext[i * 2 + 1]);
	}

	line = "";
	for (int k = 0; k < text.size(); k++) {
		line += text[k];
		if (k != text.size() - 1) {
			line += "&";
		}
	}
	cout << endl;
	cout << endl;
	cout << endl;

	cout << line;

	cout << endl;
	cout << endl;
	cout << endl;

	file.close();
}