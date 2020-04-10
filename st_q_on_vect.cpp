#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class DataStruct {
	vector<T> obj;
public:
	DataStruct(vector<T> val) {
		for (auto it : val) 
			obj.push_back(it);
	}
	virtual void Print() = 0;
	virtual void Pop() = 0;
	virtual void Push(T val) = 0;
	virtual T Get() const = 0;
	virtual size_t Size() const = 0;

};


template<typename T>
class Stack : public DataStruct<T> {
private:
	vector<T> stack;
public:
        Stack(vector<T> val) : DataStruct<T>(val) {
                for (auto it : val)
                        stack.push_back(it);
        }
        void Push(T val) {
                stack.push_back(val);
        }
        void Pop() {
                stack.pop_back();
        }
        T Get() const {
                return stack[stack.size() - 1];
        }
        size_t Size() const {
                return stack.size();
        }
        void Print() {
		cout << "Stack:" << endl;
                for (auto it = stack.end() - 1; it >= stack.begin(); --it) {
                        cout << *it << " ";
                        Pop();
                }
                cout << endl;
        }
};


template<typename T>
class Queue : public DataStruct<T> {
private:
        vector<T> queue;
public:
        Queue(vector<T> val) : DataStruct<T>(val) {
                for (auto it : val)
                        queue.push_back(it);
        }
        void Push(T val) {
                queue.push_back(val);
        }
        void Pop() {
                queue.erase(queue.begin());
        }
        T Get() const {
                return queue.front();
        }
        size_t Size() const {
                return queue.size();
        }
        void Print() {
		cout << "Queue:" << endl;
                for (auto it = queue.begin(); it < queue.end(); ++it) {
                        cout << *it << " ";
                }
		queue.clear();
                cout << endl;
        }
};

DataStruct<int>* generate(char symbol) {
	if (symbol == 's') {
		vector<int> v = {1, 2, 3};
		return new Stack<int>(v);
	}
	else if(symbol == 'q') {
                vector<int> v = {10, 20, 30};
                return new Queue<int>(v); 
	}
} 


int main() {
	char val;
	cout << "Input Stack(s) or Queue(q):" << endl;
	cin >> val;
	generate(val)->Print();
	return 0;
}
