#include <iostream>
#include <random>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <vector>

std::random_device rd;
std::mt19937 gen(rd());


struct my_obj
{
	int key;
	void* data_ptr;
};

struct my_stack
{	
	int top = -1;
	int* stack_array = nullptr;
	int max_size = 0;
	void initialise(int max_stack_size)
	{
		stack_array = new int[max_stack_size];
		max_size = max_stack_size;
	}
	void delete_stack()
	{
		delete[] stack_array;
	}
	void insert(int value)
	{
		if (top >= max_size-1)
			std::cout << "stack overflow" << std::endl;
		else
		{
			top++;
			stack_array[top] = value;
		}
	}
	int pop()
	{
		if (top < 0)
			std::cout << "stack underflow " << std::endl;
		else
		{
			top--;
			return stack_array[top + 1];
		}
	}
};

struct my_queue
{
	int max_size = 0;
	int head = 0, tail = 0;
	bool is_full = false;
	int* queue_array;

	void initialise(int size)
	{
		max_size = size;
		queue_array = new int[max_size];
	}

	void enqueue(int key)
	{
		if (is_full)
		{
			std::cout << "queue overflow" << std::endl;
			return;
		}
		queue_array[tail] = key;
		if (tail == max_size - 1)
			tail = 0;
		else
			tail++;
		if (tail == head)
			is_full = true;
	}

	int dequeue()
	{
		if (tail == head && !is_full)
		{
			std::cout << "queue underflow " << std::endl;
			return -1;
		}
		int value = queue_array[head];
		if (head == max_size - 1)
			head = 0;
		else
			head++;
		is_full = false;
		return value;
	}
	void display()
	{
		std::cout << " queue display " << std::endl;
		int i = head;
		while (i < max_size && i < tail)
		{
			std::cout << queue_array[i] << " ";
			i++;
		}
		if(i == max_size)
		{
			i = 0;
			while (i < tail)
			{
				std::cout << queue_array[i] << " ";
				i++;
			}
		}
		std::cout << std::endl;
	}
};

struct dlnode
{
	my_obj obj;
	dlnode* next;
	dlnode* prev;
};

struct double_linked_list
{
	dlnode* head = NULL;
	void insert(dlnode* new_node)
	{
		new_node->next = head;
		new_node->prev = NULL;
		head = new_node;
		if (head->next != NULL)
			head->next->prev = new_node;
	}

	dlnode* list_search(int key)
	{
		dlnode* list_it = head;
		while (list_it != NULL && list_it->obj.key != key)
			list_it = list_it->next;
		return list_it;

	}

	void list_delete(dlnode* node)
	{
		if (list_search(node->obj.key) == NULL)
			return;
		if (node->prev != NULL)
			node->prev->next = node->next;
		else
			head = node->next;
		if (node->next != NULL)
			node->next->prev = node->prev;
		delete node;
	}

	void display()
	{
		std::cout << " list display " << std::endl;
		dlnode* list_it = head;
		while (list_it != NULL)
		{
			std::cout << list_it->obj.key << " ";
			list_it = list_it->next;
		}
		std::cout<<std::endl;

	}

	void reverse()
	{
		if (head == NULL)
			return;
		if (head->next == NULL)
			return;

		dlnode* list_it = head;
		dlnode* prev_node = NULL;
		dlnode* next_node = head->next;

		while (next_node != NULL)
		{
			list_it->next = prev_node;
			list_it->prev = next_node;
			prev_node = list_it;
			list_it = next_node;
			next_node = next_node->next;
			
		}
		list_it->prev = NULL;
		list_it->next = prev_node;
		head = list_it;
	}

	dlnode* get_element(int index)
	{
		if (index < 0)
			return NULL;
		dlnode* list_it = head;
		int i = 0;
		while (i < index && list_it != NULL)
		{
			list_it = list_it->next;
			i++;
		}
		return list_it;
	}

	void list_delete_all()
	{
		dlnode* list_it = head;
		while (list_it != NULL)
		{
			dlnode* next_node = list_it->next;
			delete list_it;
			list_it = next_node;
		}
		head = NULL;
	}
};

struct slnode
{
	my_obj obj;
	slnode* next;
};

struct single_linked_list
{
	slnode* head = NULL;
	
	slnode* get_element(int index)
	{
		if (index < 0)
			return NULL;
		slnode* list_it = head;
		int i = 0;
		while (i < index && list_it != NULL)
		{
			list_it = list_it->next;
			i++;
		}
		return list_it;
	}

	void insert(slnode* new_node)
	{
		new_node->next = head;
		head = new_node;
	}
	
	slnode* list_search(int key)
	{
		slnode* list_it = head;
		while (list_it != NULL && list_it->obj.key != key)
			list_it = list_it->next;
		return list_it;
	}

	slnode* get_prev_node(slnode* node)
	{	
		if (head == NULL || head == node)
			return NULL;

		slnode* list_it = head;
		
		while (list_it->next != node && list_it->next != NULL)
			list_it = list_it->next;
		
		if (list_it->next == NULL)
			return NULL;
		else
			return list_it;
	}

	void list_delete(slnode* node)
	{
		if (node == head)
		{
			head = head->next;
			delete node;
		}
		else
		{
			slnode* prev_node = get_prev_node(node);
			if (prev_node != NULL)
			{
				prev_node->next = node->next;
				delete node;
			}
		}
	}

	void reverse()
	{
		if (head == NULL)
			return;
		if (head->next == NULL)
			return;

		slnode* prev_node = NULL;
		slnode* current_node = head;
		slnode* temp;
		while (current_node != NULL)
		{
			temp = current_node->next;
			current_node->next = prev_node;
			prev_node = current_node;
			current_node = temp;
		}

		head = prev_node;
	}

	void display()
	{
		std::cout << " list display " << std::endl;
		slnode* list_it = head;
		while (list_it != NULL)
		{
			std::cout << list_it->obj.key << " ";
			list_it = list_it->next;
		}
		std::cout << std::endl;

	}
};

int get_min(int* my_array, int array_size)
{

	int my_min = my_array[0];
	for (int i = 1; i < array_size; i++)
		if (my_array[i] < my_min)
			my_min = my_array[i];
	return my_min;
}
int get_absolute_max(int* my_array, int array_size)
{
	int my_max = abs(my_array[0]);
	for (int i = 1; i < array_size; i++)
		if (abs(my_array[i]) > my_max)
			my_max = abs(my_array[i]);
	return my_max;
}
int get_max(int* my_array, int array_size)
{

	int my_max = my_array[0];
	for (int i = 1; i < array_size; i++)
		if (my_array[i] > my_max)
			my_max = my_array[i];
	return my_max;
}

void exchange(int& v1, int& v2)
{
	int temp = v1;
	v1 = v2;
	v2 = temp;
}

template <class T, class U>
void DisplayArrVerticaly(T* FirstArr, U* SecondArr, int ArrSize, std::ofstream& MyFile)
{
	MyFile << "First Arr           ,Second Arr           " << std::endl;
	for (int i = 0; i < ArrSize; i++)
	{
		int j;
		for (j = 1; j < 11; j++)
		{
			if (int(FirstArr[i] / pow(10, j)) == 0)
				break;
		}
		int EletNumDigits = j;

		MyFile << FirstArr[i];
		for (j = 0; j < 20 - EletNumDigits; j++)
			MyFile << " ";
		MyFile << SecondArr[i] << std::endl;

	}
}

template <class T>
void display_array(T* MyArr, int ArrSize)
{
	for (int i = 0; i < ArrSize - 1; i++)
		std::cout << +MyArr[i] << ", ";
	std::cout << MyArr[ArrSize - 1] << std::endl;
}

struct MaxSubArr {
	int Low;
	int High;
	int Max;
	void operator=(MaxSubArr A) {
		Low = A.Low;
		High = A.High;
		Max = A.Max;
	}
};

MaxSubArr FindCrossMaxSubArr(int* ChangeArr, int Low, int High)
{
	int Mid = (Low + High) / 2;

	int LeftSum = ChangeArr[Mid];
	int RightSum = ChangeArr[Mid + 1];
	int Sum = 0;
	int LeftLow = Mid;
	int RightHigh = Mid + 1;
	Sum = LeftSum;
	for (int i = Mid-1; i >= Low; i--)
	{
		Sum += ChangeArr[i];
		if (Sum > LeftSum)
		{
			LeftSum = Sum;
			LeftLow = i;
		}
		
	}
	Sum = RightSum;
	for (int i = Mid + 2; i <= High ; i++)
	{
		Sum += ChangeArr[i];
		if (Sum > RightSum)
		{
			RightSum = Sum;
			RightHigh = i;
		}
	}
	MaxSubArr Result = { LeftLow, RightHigh, LeftSum + RightSum };
	return Result;
}

MaxSubArr FindMaxSumSubArrDC(int* ChangeArr, int Low, int High)
{
	if (Low == High)
	{
		MaxSubArr Result = { Low, High, ChangeArr[Low] };
		return Result;
	}
	int Mid = (Low + High) / 2;
	MaxSubArr LeftMaxSubArr = FindMaxSumSubArrDC(ChangeArr, Low, Mid);
	MaxSubArr RightMaxSubArr = FindMaxSumSubArrDC(ChangeArr, Mid + 1, High);
	MaxSubArr CrossMaxSubArr = FindCrossMaxSubArr(ChangeArr, Low, High);
	if (LeftMaxSubArr.Max > RightMaxSubArr.Max && LeftMaxSubArr.Max > CrossMaxSubArr.Max)
		return LeftMaxSubArr;
	else if (CrossMaxSubArr.Max > RightMaxSubArr.Max && CrossMaxSubArr.Max > RightMaxSubArr.Max)
		return CrossMaxSubArr;
	else
		return RightMaxSubArr;
}

MaxSubArr FindMaximumSubArray(int* MyArr, int ArrSize)
{
	int* ChangeArr = new int[ArrSize - 1];
	for (int i = 0; i < ArrSize - 1; i++)
	{
		ChangeArr[i] = MyArr[i + 1] - MyArr[i];
	}
	MaxSubArr ChangeMaxSubArr =  FindMaxSumSubArrDC(ChangeArr, 0, ArrSize - 2);
	MaxSubArr Result = { ChangeMaxSubArr.Low, ChangeMaxSubArr.High + 1, ChangeMaxSubArr.Max };
	return Result;
}

template <class T>
void MergeArrays(T *MyArr, int Low, int High)
{
	int Mid = (Low + High) / 2;
	int n = Mid - Low + 1;
	int m = High - Mid;
	T *FirstArr = new T[n];
	T *SecondArr = new T[m];
	for (int i = 0; i < n; i++)
		FirstArr[i] = MyArr[Low + i];
	for (int i = 0; i < m; i++)
		SecondArr[i] = MyArr[Mid + 1 + i];

	int FirstIndex = 0, SecondIndex = 0;
	int i = Low;
	while(FirstIndex < n && SecondIndex < m)
	{
		if (FirstArr[FirstIndex] <= SecondArr[SecondIndex])
		{
			MyArr[i] = FirstArr[FirstIndex];
			FirstIndex++;
		}
		else {
			MyArr[i] = SecondArr[SecondIndex];
			SecondIndex++;
		}
		i++;
	}
	while(FirstIndex < n)
	{
		MyArr[i] = FirstArr[FirstIndex];
		FirstIndex++;
		i++;
	}

	while (SecondIndex< m)
	{
		MyArr[i] = SecondArr[SecondIndex];
		SecondIndex++;
		i++;
	}
	delete[] FirstArr;
	delete[] SecondArr;
}

template <class T>
void MergeSort(T *MyArr, int Low, int High)
{
	if (Low == High)
		return;
	int Mid = (Low + High) / 2;
	MergeSort<T>(MyArr, Low, Mid);
	MergeSort<T>(MyArr, Mid + 1, High);
	MergeArrays<T>(MyArr, Low, High);

}

template<typename T>
void InsertionSort(T MyArr[], int ArrSize)
{
	for (int i = 0; i < ArrSize; i++)
	{
		T Key = MyArr[i];
		int j = i - 1;
		while (j >= 0 && MyArr[j] > Key)
		{
			MyArr[j + 1] = MyArr[j];
			j--;
		}
		MyArr[j+1] = Key;
	}
}

void MergeSortRT()
{
	LARGE_INTEGER BeginTime, EndTime;
	LARGE_INTEGER PerformanceFrequencyL;
	QueryPerformanceFrequency(&PerformanceFrequencyL);
	int64_t PerformanceFrequency = PerformanceFrequencyL.QuadPart;
	unsigned int ArrSizes[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	double RunningTimes[10] = {0};
	for (int i = 0; i < 10; i++)
	{
		unsigned int* MyArr = new unsigned int[ArrSizes[i]];
		std::uniform_int_distribution<unsigned int> distrib(0, 4000000000);

		for (int j = 0; j < ArrSizes[i]; j++)
			MyArr[i] = distrib(gen);
		QueryPerformanceCounter(&BeginTime);
		MergeSort<unsigned int>(MyArr, 0, ArrSizes[i] - 1);
		QueryPerformanceCounter(&EndTime);
		RunningTimes[i] = double(EndTime.QuadPart - BeginTime.QuadPart) / double(PerformanceFrequency);
		delete[] MyArr;
	}
	std::ofstream MyFile;
	MyFile.open("MerSortRunningTimes.txt");
	DisplayArrVerticaly<unsigned int, double>(ArrSizes, RunningTimes, 10, MyFile);
	MyFile.close();
}

int right_child_index(int i)
{
	return 2 * i + 2;
}
int left_child_index(int i)
{
	return 2 * i + 1;
}
int parent(int i)
{
	return int (i-1) / 2;
}
bool is_leaf(int index, int arr_size)
{
	if (index > parent(arr_size - 1))
		return true;
	return false;
}

void max_heapify_recursive(int* my_array, int array_size, int root)
{
	int left_child = left_child_index(root);
	int right_child = right_child_index(root);
	int largest_index = root;
	if (left_child < array_size && my_array[left_child] > my_array[root])
		largest_index = left_child;
	if (right_child < array_size && my_array[right_child] > my_array[largest_index])
		largest_index = right_child;
	if(largest_index != root)
	{
		exchange(my_array[root], my_array[largest_index]);
		max_heapify_recursive(my_array, array_size, largest_index);
	}
}

void max_heapify_iterative(int* my_array, int array_size, int root)
{
	int key = my_array[root];
	int largest_index = root;

	while (true)
	{
		int left_child = left_child_index(root);
		int right_child = right_child_index(root);
		if (left_child < array_size && my_array[left_child] > my_array[root])
			largest_index = left_child;
		if (right_child < array_size && my_array[right_child]> my_array[largest_index])
			largest_index = right_child;
		if (largest_index == root)
			break;
		my_array[root] = my_array[largest_index];
		root = largest_index;
	}
	my_array[largest_index] = key;
}


void build_max_heap(int* my_array, int array_size)
{
	for (int i = parent(array_size - 1); i >= 0; i--)
		max_heapify_recursive(my_array, array_size, i);
}

void display_heap(int* my_array, int array_size)
{
	int heap_depth = int(log2(array_size));
	int max_number_leafs = pow(2, heap_depth);
	int depth = 0;
	int heap_width = 100;
	for (depth = 0; depth <= heap_depth; depth++)
	{
		int num_elements = pow(2, depth);
		int distance = double(heap_width) / (num_elements + 1);
		for (int j = 0; j < num_elements && num_elements - 1 + j < array_size; j++)
		{
			for (int k = 0; k < distance; k++)
				std::cout << " ";
			std::cout << my_array[num_elements - 1 + j];

		}
		std::cout << std::endl << std::endl;
	}
}

template<typename T>
int BinarySearchIterative(T* SortedArr, int p, int q, T Value)
{
	int mid;
	while (p <= q)
	{
		mid = (p + q) / 2;
		if (SortedArr[mid] == Value)
			return mid;
		else if (Value > SortedArr[mid])
			p = mid + 1;
		else
			q = mid - 1;
	}
	return -1;
}

template<typename T>
int BinarySearchRecursive(T* SortedArr, int p, int q, T Value)
{
	if (p >= q)
		if (SortedArr[p] == Value)
			return p;
		else
			return -1;

	int mid = (p+q)/ 2;
	if (Value == SortedArr[mid])
		return mid;
	else if (Value > SortedArr[mid])
		return BinarySearchRecursive(SortedArr, mid + 1, q, Value);
	else
		return BinarySearchRecursive(SortedArr, p, mid-1, Value);
}

int partition(int* my_array, int p, int q, int pivot = -2)
{
	if (pivot == -2)
		pivot = q;
	int i = p - 1;
	for (int j = p; j < q; j++)
		if (my_array[j] < my_array[pivot])
		{
			i++;
			exchange(my_array[i], my_array[j]);
		}
	exchange(my_array[i + 1], my_array[pivot]);
	return i + 1;
}

int randomized_partition(int* my_array, int p, int q)
{
	std::uniform_int_distribution<unsigned int> distrib(p, q);
	int random_index = distrib(gen);
	return partition(my_array, p, q, random_index);
}

void quick_sort(int* my_array, int p, int q)
{
	if (p >= q)
		return;

	int mid = partition(my_array, p, q);
	quick_sort(my_array, p, mid - 1);
	quick_sort(my_array, mid + 1, q);
}

int get_digit(int number, int digit_nbr, int base)
{
	return int(number / pow(base, digit_nbr - 1)) - int(number / pow(base, digit_nbr)) * base;
}

void count_sort(int* my_array, int array_size, int values_min , int values_max, int* sorted_array = NULL,  int digit_number = 0, bool in_place = false)
{
	int possible_values_nbr = values_max - values_min + 1;
	int* values_count_array = new int[possible_values_nbr];
	if (!sorted_array)
		sorted_array = new int[array_size];

	for (int i = 0; i < possible_values_nbr; i++)
		values_count_array[i] = 0;

	for (int i = 0; i < array_size; i++)
	{
		if (digit_number)
		{
			int element_digit = get_digit(my_array[i], digit_number, possible_values_nbr);
			values_count_array[element_digit - values_min]++;

		}
		else
			values_count_array[my_array[i] - values_min]++;
	}
	for (int i = 1; i < possible_values_nbr; i++)
		values_count_array[i] += values_count_array[i - 1];
	for (int i = array_size - 1; i >= 0; i--)
	{
		if (digit_number)
		{
			int element_digit = get_digit(my_array[i], digit_number, possible_values_nbr);

			sorted_array[values_count_array[element_digit - values_min] - 1] = my_array[i];
			values_count_array[element_digit - values_min]--;

		}
		else
		{
			sorted_array[values_count_array[my_array[i] - values_min] - 1] = my_array[i];
			values_count_array[my_array[i] - values_min]--;
		}
	}
	if (in_place)
	{
		for (int i = 0; i < array_size; i++)
			my_array[i] = sorted_array[i];
	}

}

void radix_sort(int* my_array, int array_size, int base)
{
	int num_digits = 1;
	int array_max_abs = get_absolute_max(my_array, array_size);
	while (int(array_max_abs / pow(base, num_digits)) != 0)
		num_digits++;

	for(int j = 1; j <= num_digits; j++)
		count_sort(my_array, array_size, 0, base -1, NULL, j, true);

}

int select(int* my_array, int p, int q, int i)
{
	int k = randomized_partition(my_array, p, q);
	if (i-1 == k)
		return my_array[k];
	if (i-1 > k)
		return select(my_array, k + 1, q, i);
	return select(my_array, p, k - 1, i);
}

int hash_function(int max_size, int key)
{
	return key % max_size;
}

struct chained_hash_table {
	
	double_linked_list* my_hash_table;
	int max_size;
	void initialise(int table_size)
	{
		max_size = table_size;
		my_hash_table = new double_linked_list[table_size];
	}
	void insert_element(my_obj elet)
	{
		int elet_idx = hash_function(max_size, elet.key);
		dlnode* new_node = new dlnode;
		new_node->obj = elet;
		my_hash_table[elet_idx].insert(new_node);
	}
	void display()
	{
		std::cout << " hash table display " << std::endl;
		for (int i = 0; i < max_size; i++)
			my_hash_table[i].display();
	}
	my_obj* get_element(int key)
	{
		int elet_index = hash_function(max_size, key);
		dlnode* element_node = my_hash_table[elet_index].list_search(key);
		return &element_node->obj;
	}

	void table_delete(my_obj*)
	{

	}
};


int main()
{


	/*const int array_size = 10;
	int my_array[array_size] = {2585,34,83,1,1,2,2,29,17,208};*/

	//chained_hash_table<int> my_htable;
	//my_htable.initialise(10);
	//int* my_array = new int[10];
	//for (int i = 0; i < 10; i++)
	//{
	//	my_obj<int> my_obj;
	//	my_obj.key = i+5;
	//	my_array[i] = 20 + i;
	//	my_obj.data_ptr = &my_array[i];
	//	my_htable.insert_element(my_obj);
	//}
	//my_htable.display();
	//my_obj<int>* obj = my_htable.get_element(9);
	//std::cout << " my obj key : " << obj->key << " and data is : " << *obj->data_ptr;

	// Single linked list testing 
	single_linked_list my_dlist;

	for (int i = 0; i < 10; i++)
	{
		slnode* new_node = new slnode;
		new_node->obj.key = i;
		my_dlist.insert(new_node);
	}
	my_dlist.display();
	for (int i = 0; i < 3; i++)
	{
		slnode* list_it = my_dlist.get_element(2);
		my_dlist.list_delete(list_it);
		my_dlist.display();
	}
	std::cout << " reversed " << std::endl;
	my_dlist.reverse();
	my_dlist.display();

	// Double linked list testing 
	
	//double_linked_list<int> my_dlist;

	//for (int i = 0; i < 10; i++)
	//{
	//	dlnode<int>* new_node = new dlnode<int>;
	//	new_node->obj.key = i;
	//	my_dlist.insert(new_node);
	//}
	//my_dlist.display();
	//for (int i = 0; i < 3; i++)
	//{
	//	dlnode<int>* list_it = my_dlist.get_element(2);
	//	my_dlist.list_delete(list_it);
	//	my_dlist.display();
	//}
	//std::cout << " before reverse " << std::endl;
	//my_dlist.reverse();
	//my_dlist.display();
	//my_dlist.list_delete_all();
	//my_dlist.display();


	// Queue testing 
	
	//my_queue q;
	//q.initialise(10);
	//for (int i = 0; i < 12; i++)
	//	q.enqueue(i);
	//q.display();
	//for (int i = 0; i < 7; i++)
	//	q.dequeue();
	//q.display();

	//for (int i = 7; i < 10; i++)
	//	q.enqueue(i);
	//q.display();

	// Stack testing
	
	//my_stack s;
	//s.initialise(4);
	//for (int i = 0; i < 1; i++)
	//{
	//	s.insert(i);
	//	display_array<int>(s.stack_array, s.top + 1);
	//}
	//for (int i = 0; i < 2; i++)
	//{
	//	s.pop();
	//	display_array<int>(s.stack_array, s.top + 1);
	//}
	
	/*int order_i = 3;
	radix_sort(my_array, array_size, 10);
	display_array<int>(my_array, array_size);

	std::cout << " the " << order_i << "th order statistic is : " << select(my_array, 0, array_size - 1, order_i);*/

	//int* sorted_array = new int[array_size];
	//count_sort(my_array, array_size, sorted_array,0, 9, 2);
	//display_array<int>(sorted_array, array_size);
	return 0;
}