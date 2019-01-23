# include <iostream>
# include <stack>

using namespace std;

template<class T>
class StackExt {
	stack<T> valores;
	stack<T> minimos;
public:
	StackExt() {
	}
	;
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template<class T>
bool StackExt<T>::empty() const {

	return valores.empty();
}

template<class T>
T& StackExt<T>::top() {

	return valores.top();
}

template<class T>
void StackExt<T>::pop() {
	T val = valores.top();
	valores.pop();
	if (minimos.top() == val)
		minimos.pop();
}

template<class T>
void StackExt<T>::push(const T& val) {

	valores.push(val);
	if (!minimos.empty()) {
		if (val <= minimos.top())
			minimos.push(val);
	} else
		minimos.push(val);
}

template<class T>
T& StackExt<T>::findMin() {

	return minimos.top();
}
