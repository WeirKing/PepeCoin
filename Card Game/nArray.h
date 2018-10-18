#include <stdexcept>
template <typename T>
class array {
private:
	T *head;
public:
	int size;

T& operator[](int n){
	if (n < size and n >= 0){
		return *(head + sizeof(T) * n);
	}
	return *head;
}
array(int size_){
	size = size_;
	head = new T[size];
}

};
/*
#include <iostream>
int main(){
	array<char> a(5);
	a[0] = 'a';
	a[1] = 'b';
	a[2] = 'c';
	a[3] = 'd';
	a[4] = 'e';
	int i;

	for (i = 0; i < 6; i++){
		printf("value: %c\n", a[i]);
	}

}
*/