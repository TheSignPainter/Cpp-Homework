/*
 * 实现一个list类命名为MyList，其功能与python数组类似。可以用数组实现，也可以用链表实现。
 * 必须使用template <class T>，不允许使用<iostream>以外的库。
 * 需要实现的功能与测试代码见下。请务必搞清楚每一项的意义，比如什么时候需要用友元函数什么时候需要const什么时候需要&。
 * 当某些由用户正常操作可能产生的run time error（如pop一个空数组，或访问一个超出下标的元素），
 * 请使用try-catch-throw处理错误。
 * 以下类定义不保证完全正确，请根据实际需求修改，以实现样例功能为主。
 */

/* 
 * 本练习不涉及到虚类和类继承，但是期末考试我就不知道了。如果有时间可以用书上的shape类来练习。
 */

#include<iostream>
using namespace std;

class SizeException{};


template<class T>
class MyList{

private:
	T *a;
	int size,size_in_mem;
	void double_space(){
		if (size_in_mem!=0){
		T *tmp;
		tmp=a;
		a=new T[size_in_mem*2];
		size_in_mem*=2;
		for (int i=0;i<size;++i)
			a[i]=tmp[i];
		delete []tmp;
		}
		
		else {
			size_in_mem=10;a=new T[10];}
	};// Double the size of the List.
	

	
public:
	MyList(int sz){
		size=sz;
		size_in_mem=sz;
		a = new T [size];
	}
	MyList(){
		size=0;
		size_in_mem=10;
		a = new T [size_in_mem];
	}
	MyList(int num, const T &item) {
		if (num==0){
			a=new T[10];
			size=0;
			;
		}
		else{
			size=num;
			size_in_mem=num;
			a=new T [size];
			for (int i=0;i<num;++i)
				a[i]=item;
		}
		
	};//将item重复num次填入数组中。
	MyList(const MyList &l){
		size=l.size;
		size_in_mem=l.size_in_mem;
		a=new T [size];
		for (int i=0;i<size;++i)
			a[i]=l.a[i];
	};// Deep copy
    MyList(T* arr, int len){
		size=len;
		size_in_mem=len;
		a=new T [size];
		for (int i=0;i<size;++i)
			a[i]=arr[i];
	};//Construct Mylist according to the first len terms of arr(array).

	void push(const T &item){
		++size;
		if (size>size_in_mem)
			this->double_space();
		a[size-1]=item;
	};//将item添加在MyList最后。
	T pop(){
		try{
			if (size==0) throw(SizeException());
			else {
			T tmp,tmp1=a[size-1];
			a[size--] = tmp;
			return tmp1;}
		}
		catch(SizeException)
			{cout<<"Error: Pop from an empty list"<<endl;}
		
	};//将MyList中最后一个元素删除，并返回这个删除的元素。
	void insert(int index, const T &item){
		++size;
		if (size>size_in_mem)
			this->double_space();
		for (int i = size - 1; i > index; --i) a[i] = a[i - 1];
		a[index] = item;
	};//将item插入到place处。
	void clean(){
		delete[]a;
		size=0;
		size_in_mem=0;
	};//清空数组。
	int get_size(){
		return size;
	}
	;//返回MyList中元素的数量。
	void erase(int start, int end){
		for (int i=end+1;i<size;++i)
			a[i-end-1+start]=a[i];
		size=size-(end-start+1);
	
	}; //删除MyList中第start到第end位的元素，包括两边。
	T get_item(int index){
		return a[index];
	};//返回第index个元素。
	MyList get_item(int start, int end){
		int head,tail;
		head=(size+(start%size))%size;
		tail=(size+(end%size))%size;
		if (head>tail)
			{	MyList<T> b;
				return b;}
		else {
			MyList<T> b(tail-head+1);
			for (int i=head;i<=tail;++i){
				b.a[i-head]=a[i];
				}
			cout <<endl<<b;
			return b;
			
		} 
		
	};//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
	int count(const T &item){
		int c=0;
		for (int i=0;i<size;++i)
			if (a[i]==item)++c;
		return c;
	};//返回MyList中和item相等的元素的个数。
	void remove(const T &item){
		int i;bool flag(false);
		for (i=0;i<size;++i)
			if (a[i]==item) {flag=true;break;};
		if (flag){
			int ind=i+1;
			for (i=ind;i<size;++i)
				a[i-1]=a[i];
			--size;
		}
	
	};//删除MyList中第一个和item相等的元素。

	friend MyList operator + (const MyList &l1, const MyList &l2){
		MyList res(l1.size + l2.size);
		for (int i = 0; i < l1.size; ++i){
			res.a[i] = l1.a[i];
		}
		for (int i = l1.size ; i < res.size; ++i){
			res.a[i] = l2.a[i-l1.size];
		}
	return res;
	}; //合并两个MyList
    friend MyList operator + (const MyList<T> &l1, const T &item){
		MyList<T> res(1+l1.size);
		res.a[l1.size] = item;
		return res;
	}; //同push(T item)，但不修改l1，返回一个新数组

	MyList &operator = (const MyList &l){
		this->size=l.size;
		this->a=new T[size];
		for (int i=0;i<size;++i)
			this->a[i]=l.a[i];
		this->size_in_mem=l.size;
	};//赋值
	MyList &operator += (const T &item){
		T *tmp;
		//while (size_in_mem<size+1) double_space();
		tmp=this->a;
		a=new T[size+1];
		for (int i=0;i<size;++i)
			a[i]=tmp[i];
		a[size]=item;
		++size;
		size_in_mem=size;
	};//同push(T item)
	MyList &operator += (const MyList &l){
		T *tmp;
		while (size_in_mem<size+l.size) double_space();
		tmp=this->a;
		int tmp_size=size;
		this->size+=l.size;
		a=new T [size];
		size_in_mem=size;
		for (int i=0;i<tmp_size;++i)
			a[i]=tmp[i];
		for (int i=tmp_size;i<size;++i)
			a[i]=l.a[i-tmp_size];
		delete []tmp;
	};//将一个MyList加入到本个MyList之后。
	T &operator [](int index){
		try{
			if (0<=index&&index<size)
			{return a[index];}
			else throw(SizeException());}
		catch(SizeException)
			{cout<<"Error: Index out of range"<<endl;}
	};//返回第index个元素。
	friend ostream & operator<<(ostream &os, const MyList &obj){
		os << '[';
		for (int i=0;i<obj.size-1;++i){
			os<<obj.a[i]<<", ";
		}
		os<<obj.a[obj.size-1];
		os<< ']'<<endl;
		return os;
	};//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如：
    // [1, 2, 5, 4, 1]

	void sort(bool less=true){
		if (less) this->qsort(0,size-1);
		else this->r_qsort(0,size-1);
		
	
	};//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。
    // 若less=true，按照从小到大排列，否则按从大到小排列
    
    void qsort(int l, int r)  
	{  
	    if (l < r)  
	    {  
	        //Swap(s[l], s[(l + r) / 2]); //���м��������͵�һ�������� �μ�ע1  
	        int i = l, j = r, x = a[l];  
	        while (i < j)  
	        {  
	            while(i < j && a[j] >= x) // ���������ҵ�һ��С��x����  
	                j--;    
	            if(i < j)   
	                a[i++] = a[j];  
	              
	            while(i < j && a[i] < x) // ���������ҵ�һ�����ڵ���x����  
	                i++;    
	            if(i < j)   
	                a[j--] = a[i];  
	        }  
	        a[i] = x;  
	        this->qsort(l, i - 1); // �ݹ����   
	        this->qsort(i + 1, r);  
	    }  
	}

void r_qsort(int l, int r)  
	{  
	    if (l < r)  
	    {  
	        //Swap(s[l], s[(l + r) / 2]); //���м��������͵�һ�������� �μ�ע1  
	        int i = l, j = r, x = a[l];  
	        while (i < j)  
	        {  
	            while(i < j && a[j] <= x) // ���������ҵ�һ��С��x����  
	                j--;    
	            if(i < j)   
	                a[i++] = a[j];  
	              
	            while(i < j && a[i] > x) // ���������ҵ�һ�����ڵ���x����  
	                i++;    
	            if(i < j)   
	                a[j--] = a[i];  
	        }  
	        a[i] = x;  
	        this->r_qsort(l, i - 1); // �ݹ����   
	        this->r_qsort(i + 1, r);  
	    }  
	}	
    
    
    
	void reverse(){
		T *tmp;
		tmp=new T[size];
		for (int i=0;i<size;++i){
			tmp[i]=a[size-1-i];
		}
		delete []a;
		a=tmp;
		size_in_mem=size;
	};//将MyList的元素倒过来。

	~MyList(){delete [] a;
	}
};


int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *若start > end，返回空数组
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	cout<<a;
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	cout<<b;
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}



