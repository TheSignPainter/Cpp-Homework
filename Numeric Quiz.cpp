// Numeric Quiz

//A small game about guessing numbers. You can choose the size of the number to be guessed
//  and how many chances you have, by simply replacing some constants.

// 3-25-2015

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int chances=10;      // this constant determines your chances of failure

// Search a number from the head of array, the searching scope is 0 to (pos-1).Return true when exists.
bool findterm(int array[], int size, int a, int pos){
	int i; bool flag=false;
	for (i=0;i<pos;++i){
		if (a==array[i]) {flag=true; break;}
	}
	return flag;
}

// Compare the guessed number with the correct one, and print "XAXB". Return true when the 2 numbers are the same.
bool comp(int *rands , int *guesses , int size){
	int a=0,b=0,i,j;
	for (i=0;i<size;++i){
		for (j=0;j<size;++j){
			if (guesses[i]==rands[j]){
				if (i==j) {++a; break;}
				else {++b; break;}
			}
		}
	}
	if (a==3) return true;
	else {
		cout << a << 'A' << b << 'B' <<endl;
		return false;
	}
}

// Execute the game for 1 round.
bool game(int *rands, int size){
	int i,j,*guess;
	guess=new int[size];
	for (i=0;i<chances;++i){                      // Have some chances
		cout << "��������²������"  << endl;
		for (j=0;j<size;++j)  cin >> guess[j];    //Reading guessed numbers
		
		if (comp(rands,guess,size)){
			delete []guess;
			cout << "��ϲ����¶���" << endl; 
			return true;}
	}
	cout << "���ź�����û���ڹ涨�����ڲ¶ԡ����� ";
	for (i=0;i<size;++i){ cout << rands[i];	}
	delete []guess;
	cout << endl;
	return false;
}

int main(){
	srand(time(0));
	int const size=5;          //Detemine the length of number to be guessed
	int *rands, rantemp, rounds=0, rounds_won=0; char ch;
	rands= new int[size];
	while (true) {
		// Initialization & Condition Checking.
		cout << "��Ҫ����Ϸ��(Y/N) �� " ;
		cin >> ch;
		cout << endl; 
		if ( (ch=toupper(ch))=='N') break;
		rands[0]=rand() % 10;
		
		// Generation of random numbers
		for (int i=1;i<size;++i){
			while (findterm(rands,size,rantemp,i)){
				rantemp= rand() % 10;
			}
			rands[i]=rantemp;
		}		                 
		if (game(rands,size)){
			++rounds_won;
		}
		++rounds; 
	}
	delete []rands;
	cout << "��һ������" << rounds <<"�֣�Ӯ��" << rounds_won <<"�֣�����" << (rounds-rounds_won) << "�֡�" << endl; 
}


















