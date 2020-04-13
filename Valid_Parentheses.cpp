#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isValid(string s) {
	vector<char> open_brackets;

	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '(') {
			open_brackets.push_back(s[i]);
		} 
		if (s[i] == ')') {
			if (open_brackets.back() == '(')
				open_brackets.pop_back(); 
			else
				return false;
		}
		if (s[i] == '{') {
			open_brackets.push_back(s[i]);
		}
		if (s[i] == '}') {
			if (open_brackets.back() == '{')
				open_brackets.pop_back();
			else 
				return false;
		}
		if (s[i] == '[') {
			open_brackets.push_back(s[i]);
		}
		if (s[i] == ']') {
			if (open_brackets.back() == '[')
				open_brackets.pop_back();
			else
				return false;
		}

	} 
		if (open_brackets.empty())
			return true;
		return false;
}

int main() {
	string s1 = "()";
	string s2 = "(){}[]";
	string s3 = "(]";
	string s4 = "([)]";
	string s5 = "{[]}";
	cout << isValid(s5) << endl;
	return 0;
}