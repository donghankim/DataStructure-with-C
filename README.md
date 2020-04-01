# Data-Structures-with-C
Various data structures implemented in C

## Introduction
Data Strucures are an important part of software development. I have made a similar repository called "Algorithms with Python", but I have decided to use C for this repository, as C has more functionality when it comes to memory address manipulation. I will try to cover all of the basic data structures and implement them in C (with some brief description and analysis of the data structure in this README file).

## C Review
In order to use C to implement data structures, you will need to be familiar with some of the memory manipulation techniques available in the C library. I will go over some of the basic functionalty of pointers, structure/unions, file access methods and dynamic memory manipulation in this section. If you are comfortable with these then I suggest you skip over this part.

### Pointers
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

### Structures and Unions
C is not an object-oriented programming language. Therefore, there are no objects in C. However, structures have similar properties to objects, and I think its easier to think of structures as C's way of expressing objects.
```c
struct car{
    char* name;
    char* engine_type;
    int price;
    double mileage;
} c1;

int main(void){

    c1.name = "car 1";
    c1.engine_type = "V4";
    c1.price = 100;
    c1.mileage = 12.3;
    printf("car1 enginer type is %s\n", c1.engine_type);

    // declaring another variable c2 of type struct car
    struct car c2 = {"car 2", "V6", 150, 10.5};

    return 0;
}
```
As the code above shows, you can access struct members using the dot operator (like attributes of objects in OOP languages). However, you can also access struct members using struct pointers.
```c
    // continuing on from the code above
    struct car* c1_ptr = &c1;
    printf("car1 price is %d\n", c1_ptr->price); // == *(c1_ptr).price

```
Sometimes it can be a little confusing to type "struct car" to refer to the structure we have created. The <strong>typedef</strong> keyword is bascially an alias to our structure.
```c
    // continuing on from the code above
    typedef struct car Car;
    Car c3;
    c3.mileage = 16.5;

    // or you can just create a new struct with typedef at initialization
    typedef struct{
        char* name;
        int age;
        int year;
    } Student;

    Student s1 = {"Sean", 20, 3};
```

Unions are similar to structures with the exception that all members of union share the same storage space (memory). Because union members share the same storage space, you can only access only one member at a time.
```c
union number{
    int x;
    double y;
};

int main(void){

    union number n1;
    n1.x = 10;
    n1.y = 10.5;
    printf("int value %d and double value %f\n", n1.x, n1.y);

    // because you can only access one member at a time, you cant do this
    union number n2 = {10, 10.5} // will casue an error

    return 0;
}
```
Unions are not used that often, and wont be used for remainder of this repository. I included it to show you that unions exist.

### File Access
There are two methods of accessing files in C; Sequential access and random access. However, I will only cover sequential access here.

You can open files, modify files and also create new ones. We can do all three using C as well. There are many file types but I will only focus on text files (.txt extension). When dealing with files, you will always need a file pointer. A file pointer points to the memory address where the start of the file lives. Lets see an example of <strong>writing</strong> files first.
```c
void write_method(FILE* file_ptr, char* textfile){
    // fopen connects our file pointer to the file we want to write in
    file_ptr = fopen(textfile, "w");

    printf("To stop entering file press control+d...\n");
    // checks for the EOF key, on mac thats control+d
    while (!feof(stdin)){
        char* user_input;
        scanf("%s", user_input);

        // prints the user input to our file using our file pointer
        fprintf(file_ptr, "%s\n", user_input);
    }
    fclose(file_ptr);
}

int main(void){
    FILE* file_ptr; // declaring a file pointer
    char write_file[50] = "new_write.txt" // name of our new file to write in

    write_method(file_ptr, write_file);
}
```
Running the code above will create a new file with all the inputs the user enters. Note the fopen "mode", in the code above "w", tells the computer that we want to write code. There are multiple modes you can specify. Also, be aware of <strong>fclose(file_ptr)</strong>. Depending on the gcc complier you are using, some compilers will give you a warning if you forget to close the memory access to the file you are working on. Just make sure to close the file you are working with when you are done. Now lets look at reading a file.
```c
void read_method_one(FILE* file_ptr, char* textfile){
    // this time we set the fopen mode to read
    file_ptr = fopen(textfile, "r");

    if(file_ptr == NULL){
        printf("could not open file\n");
    }else{
        char current_word[50];
        // gets one word at a time until EOF
        while(fscanf(file_ptr, "%s", current_word) == 1){
            printf("%s\n", current_word);
        }
    }
    fclose(file_ptr);
}

void read_method_two(FILE* file_ptr, char* textfile){
    file_ptr = fopen(textfile, "r");

    if(file_ptr == NULL){
        printf("could not open file\n");
    }else{
        char current_line[50];
        // gets entire line at a time until EOF
        while(fgets(current_line, 50, file_ptr)){
            printf("%s", current_line);
        }
    }
    fclose(file_ptr);
}

int main(void){
    FILE* file_ptr; // declaring a file pointer
    char read_file[50] = "some_text.txt" // make sure this file is in the directory you are working on

    // two methods to read files
    read_method_one(file_ptr, read_file);
    read_method_two(file_ptr, read_file);
}
```
Ive included two methods to access file content; fscanf and fgets. Wih fscanf, the code reads one word at a time, whereas fgets reads the entire line. If you want to modify a file, then just set the fopen mode to "a" for append. For practice, try creating a program where you copy the contents of one file and move it to another new file.

### Dynamic Memory Manipulation
This is the last part of the C review section.




