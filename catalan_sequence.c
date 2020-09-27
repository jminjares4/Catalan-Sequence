/*
    Author: Jesus Minjares BSEE 
    Problem:
        Write a multi-threaded program that computes the Catalan number sequence
        (http://mathworld.wolfram.com/CatalanNumber.html) and writes thosenumbers in fixed
        point format to a file called “catalan.dat”. Your program should take two command
        line arguments: the first specifies the number of Catalan numbers to generate and 
        the second specifies the number of threads to use to compute the Catalan number 
        sequence; you can assume a maximum of fourthreads.Create a way to balance the
        load among the threads.You mustuse the “long double” type to get the largest range
        possible; the Catalan numbers grow very quickly.Output must be in ascending order
        (fixed point format) in the file “catalan.dat”
        
        -------Catalan Formula-----
        C_n+1 = 2*(2*n + 1)/(n+2) * Cn
        C_n+1 = (4n + 2)/(n+2) *Cn
        ---------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_THREADS 4 //max threads 
#define MIN_THREADS 1 //minimum thread 
void * printCatalanNumbers(void *param); //subroutine for print 
long double catalanNumber(int n); //get the nth catalan number 
pthread_t thread[MAX_THREADS]; //pthread_t array of 4
typedef struct boundary{
    int high;
    int low;
}Boundary; //data structure to hold the bound 
FILE *file; //file object
pthread_attr_t attr;
int main(int argc, char *argv[]){
    if(argc < 3){ 
        printf("./executable nth threads\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]); //convert array to integer 
    int numThreads = atoi(argv[2]); //convert array to integer 
    file  = fopen("catalan.dat", "w"); //create a file, open a file as "write"
    if(file == NULL){
       fprintf(stderr, "Error opening the file\n");
       return EXIT_FAILURE;             
    }
    int load = (int)n/numThreads; //get the increments
    //set the thread at minimum of 1
    if(atoi(argv[2]) < MIN_THREADS) numThreads = MIN_THREADS; 
    //set the threads at max of 4
    if(atoi(argv[2]) > MAX_THREADS) numThreads = MAX_THREADS;
    //create an array of limits 
    Boundary bound[numThreads];
    //distribute the load among the threads 
    for(int i = 0; i < numThreads; i++){
        bound[i].low = i * load;
        bound[i].high = (i + 1) * load;
    }
    //set the last thread.high at the nth number 
    bound[numThreads - 1].high = n;
    //create the threads, and join them
    pthread_attr_init(&attr);
    for(int i = 0; i  < numThreads; i++){
        //create the thread, default attr, printCatalan function, and pass the structure 
        pthread_create(&thread[i],&attr, printCatalanNumbers,(void*)&bound[i]);
        pthread_join(thread[i], NULL); //wait to the thread has ended 
    } 
    fclose(file);
    printf("Catalan sequence stored in catalan.dat\n");
    return EXIT_SUCCESS;
}
void * printCatalanNumbers(void *param){
    Boundary *bound = param;//implicity type cast the param to a struct *
    //iterate from the low and high of the sequence
    for(int i = bound->low; i < bound->high; i++)
        fprintf(file,"%d: %Lf\n",i+1,catalanNumber(i)); //print to the file 
    fprintf(file,"------------------\n");
    pthread_exit(NULL); //exit thread and return nothing 
}
/*
base case: n < 1, set 1
else: call recursive C(n-1)
NOTE: there will be a precision loss due to division
*/
long double catalanNumber(int n){ 
     return n < 1 ? 1 : catalanNumber(n - 1) * (4*n + 2)  / (n + 2);
}
