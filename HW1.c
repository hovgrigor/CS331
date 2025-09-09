#include <stdio.h>

// The explanations are in comments
int main()
{
    // Ex 1
    printf("Ex 1 -------------- \n");
    int a = 5; // Declare an int type variable and assign it 5
    int *p = &a; // Create a pointer p which point to variable a
    /* 
    Print the address of a which is declared by putting & at the front of the variable
    the %p is a format specifier used to print memory addresses and %d the same for numbers
    */ 
    printf("Number with int %p \n", &a); 
    printf("Number with int pointer %p \n", p);
    // Here by doing *p = 6, we change the value at address p which is <a> and which becames 6
    *p = 6;
    // This will print 6
    printf("Modified using pointer %d \n", a);

    // Ex 2
    printf("Ex 2  -------------- \n");
    int arr[5] = {1,2,3,4,9}; // Declare an array of ints of length 5 with specified elements
    int *p_arr = &arr[0]; // Declare a pointer to the first value of the array
    for(int i = 0; i < 5; i++){
    /* 
    By doing pointer arithmitic we can get the elements of the array
    (p_arr + i) moves the address to the next element each iteration 
    and by puting * at the front we get its value and print it.
    */ 
        printf("Value at %d is %d \n", i, *(p_arr + i));
    }
    
    // In the same way to move the address and change it to some other value
    for(int i = 0; i < 5; i++){
        *(p_arr + i) = i + 20;
    }
    
    /* 
    Same as above but we also have arr[i] to just print the element at i-th position in the array
    */ 
    for(int i = 0; i < 5; i++){
        printf("Value at %d with pointer is %d, with arr name is %d \n", i, *(p_arr + i), arr[i]);
    }
    
    //Ex 3
    printf("Ex 3 -------------- \n");
    /* 
    A swap function which takes two pointers as arguments
    We make a temp integer and assign it the value at pointer 1, then we swap the values which are at the pointers.
    */ 
    void swap(int *p1, int *p2){
        int temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
    
    // Two cool integers
    int a1 = 6;
    int a2 = 7;
    
    // Before spaw 
    printf("a1 -> %d, a2 -> %d \n", a1, a2);
    swap(&a1, &a2); // Calling with addresses of the variables
    // After they are swaped
    printf("a1 -> %d, a2 -> %d \n", a1, a2);
    
    //Ex 4
    printf("Ex 4 -------------- \n");
    int b; // Declaring integer without assigning value
    int *pb = &b; // a pointer whcih points at the integer
    int **ppb = &pb; // a pointer which point at the pointer pointing at the integer
    **ppb = 25; // assigning 25 at the location of the location of the ppb pointer which is in this case b 
    
    printf("Value pointer -> %d, Value double-pointer -> %d \n", *pb, **ppb);
    
    //Ex 5
    printf("Ex 5 -------------- \n");
    char str[] = "Hello"; // array of characters 
    char *p_str = &str[0]; // pointer to the begining of said characters
    for(int i = 0; i < 5; i++){ // loop
        printf("%c", *(p_str + i)); // print char by char the same way as before
    }
    printf("\n");
    int len = 0; // initalize a counting variable at 0
    /* 
    Here we are incrementing the pointier taking it's value and comparing it to '\0' 
    which is a null terminator at the end of the array. So we are just checking if we reached the end.
    */ 
    while(*(p_str + len) != '\0'){ 
        len++;
    }
    printf("Length of the string is -> %d", len);
    
    return 0;
}