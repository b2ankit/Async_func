#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

/*******************************************
 * structure definition                    *
 ******************************************/

typedef struct{

    int x;
    int y;
    int result;
}operation_values_t;

/*******************************************
 * Declararation of mutex                  *
 ******************************************/
pthread_mutex_t lock;

/*******************************************
 * Declararation of thread                 *
 ******************************************/
pthread_t th1;
pthread_t th2;

/*******************************************
 * sum function definition                 *
 ******************************************/
void *my_add_func(void *arg){
    pthread_mutex_lock(&lock);
    operation_values_t *opt_struct = (operation_values_t *)arg;
     opt_struct->result = opt_struct->x + opt_struct->y;
     printf("x : %d\ty : %d\tresult : %d\n",opt_struct->x,opt_struct->y,opt_struct->result);
    pthread_mutex_unlock(&lock);
}


int main(){
    /*******************************************
    * Mutex intialization                      *
    ******************************************/
   pthread_mutex_init(&lock,NULL);

    /*******************************************
    * Allocating memory for struct             *
    ******************************************/
    operation_values_t *optValues1 = NULL;
    optValues1 = (operation_values_t *)malloc(sizeof(operation_values_t));
    if(!optValues1){
        printf("Memory allocation for optValues1 : Failed\n");
        return -100;
    }
    optValues1->x = 10;
    optValues1->y = 10;

    /*******************************************
    * Allocating memory for struct             *
    ******************************************/
    operation_values_t *optValues2 = NULL;
    optValues2 = (operation_values_t *)malloc(sizeof(operation_values_t));
    if(!optValues2){
        printf("Memory allocation for optValues : Failed\n");
        return -100;
    }
    optValues2->x = 20;
    optValues2->y = 20;

    /*******************************************
    * Thread creation                          *
    ******************************************/
    pthread_create(&th1,NULL,my_add_func,(void *)optValues1);
    pthread_create(&th2,NULL,my_add_func,(void *)optValues2);
    
    /*******************************************
    * Join the main Thread                     *
    ******************************************/
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    return 0;
}