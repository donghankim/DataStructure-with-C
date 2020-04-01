# Data Structures with C
Various data structures implemented in C

## Introduction
Data Strucures are an important part of software development. I have made a similar repository called "Algorithms with Python", but I have decided to use C for this repository, as C has more functionality when it comes to memory address manipulation. I will try to cover all of the basic data structures and implement them in C (with some brief description and analysis of the data structure in this README file).

## C Review
In order to use C to implement data structures, you will need to be familiar with some of the memory manipulation techniques available in the C library. I will go over some of the basic functionalty of pointers, structure/unions and file access methods in this section. If you are comfortable with these then I suggest you skip over this part.

### Pointers and Memory Manipulation
A pointer is basically a "data type" that is used to store address locations. Like int is used to store integer values, a pointer is simply a way of telling the compiler that this variable is going to contain an address.

```c
int A = 10;
int* Aptr = &A;

printf("The value of var A is %d and the address it is in %p\n", A, Aptr);
```

The star(*) is a key character that tells the compiler that it is a pointer. The ampersand (&) tells the compiler that we want the address of the following variable. One key point to note here is that not all pointers are the same. For example, if you want the address of an int variable, then you have to define the variable as int*, or if you want the address of a char variable, then you need to use char*.

If you use the * key in front of an already defined pointer, then you are <strong>dereferencing</strong> that pointer. In other words, you are accessing the pointers actual content.

```c
int A = 10;
int* Aptr = &A;

printf("dereferencing A: %d\n", *Aptr); // prints --> 10
```

#### Call-by-reference
We can send the address of a variable to a function instead of sending the actual value of the variable. The following is a simple function that adds two numbers and saves it in the third variable by using the address of all three variables.

```c
void add_by_ref(int* a, int* b, int* result){
    *result = *a + *b; // dereferencing all three variables
}

int main(void){
    int a = 10;
    int b = 100;
    int result;

    add_by_ref(&a, &b, &result); // we are not sending the value of a,b and result but their respective address

    return 0;
}
```

#### Arrays
In c you can access arrays using pointers. In fact it can be easier to use pointers than the square bracket notation we are all too familiar with.
```c
int arr[3] = {1,2,3};

// the following prints the address of the first element of the array
printf("%d\n", arr) ;
printf("%d\n", &arr[0]);

// the following prints the value of the first element of the array
printf("%d\n", *arr);
printf("%d\n", arr[0]);
```

We can also perform pointer arthmetic to find the next address.
```c
printf("%d\n", *(arr+1)); // prints the next element of the array
printf("%d\n", *(arr++));
printf("%d\n", *(arr--)); // prints the previous element of the array (if there is one)
```
There are a lot more features regarding pointers and arrays, especially for strings, but I wont cover that here. Make sure you known how to manipulate and use strings using pointers before moving on to the next part.

#### Pointers to Functions
A pointer to function contains the address of the function in memory. Here is an example of using a function pointer.
```c
int add(int a, int b){
    return a+b;
}

int main(void){

    int (*add_ptr)(int, int) = add; // == int (*add_ptr)(int, int) = &add;
    printf("location of function add in memory: %d\n", add_ptr);

    // using function pointer to call a function, both methods can be used.
    int ret = add_ptr(1, 5);
    printf("return value: %d\n", ret);

    int ret2 = (*add_ptr)(1, 5);
    printf("return value: %d\n", ret);

    return 0;
}
```
You might be wondering why we would use function pointers to begin with, since we can just call a function without using any pointers. However, there are cases where we need to send a function pointer as a parameter to another function. This is called <strong>call-back function</strong>. When you start coding more complicated functions, there will be scenarios where you end up having duplicate code. Call-back functions helps us avoid duplicate code. The example below shows us how we can use quicksort algorithm that is provided by the C library.
```c
#include <stdio.h>
#include <stdlib.h>

int compare(const void* elem1, const void* elem2){
    if((*(int*)elem1) == (*(int*)elem2))
        return 0;
    else if ((*(int*)elem1) < (*(int*)elem2))
        return -1;
    else
        return 1;
}


void print_arr(int arr[], int len){
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void){

    int arr[5] = {10, 2, 8, 7, 3};
    int len = sizeof(arr)/sizeof(arr[0]);
    qsort((void*)arr, len, sizeof(int), compare);
    print_arr(arr, len);

    return 0;
}
```
To use the qsort function, you have to import the stdlib.h library. In addition, you have to define he compare function that <strong>must</strong> recieve two const pointers of void type. The const keyword basically tells us that we cant change the address of the two paraemters (elem1, elem2) that the compare function is recieving. Because we are recieving a void pointer, we need to cast in into an int pointer by using (int*). The neat thing about this compare function is that, if we want to change the criteria of the sort (for example, sort by descending order) then we only need to modify the compare function. This idea may seem a little abstract at first but when you start writing more complicated code, you will start to see the benefit of using call-back functions.






