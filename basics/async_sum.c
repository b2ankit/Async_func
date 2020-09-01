#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


#define SUCCESS 1
#define FAILURE -100
/*******************************************
 * structure definition                    *
 *******************************************/
pthread_t th;
pthread_mutex_t lock;

typedef void result_cb(char *msg,int retcode);

typedef struct{

    int x;
    int y;
    result_cb *resultCallbacks;
    
}operation_values_t;

void resultCallbacks(char *msg,int retcode){
    printf("%s of number is :  %d\n",msg,retcode);
}

void *async_func(void *arg){
    int result;
    pthread_mutex_lock(&lock);
    operation_values_t *opt_struct = (operation_values_t *)arg;
    result = opt_struct->x + opt_struct->y;
    sleep(1);
    opt_struct->resultCallbacks("sum",result);
    pthread_mutex_unlock(&lock);
}


int cal_sum(int a, int b){
    operation_values_t *optValues = NULL;
    optValues = (operation_values_t *)malloc(sizeof(operation_values_t));
    if(!optValues){
        printf("Memory allocation for optValues : Failed\n");
        return FAILURE;
    }
    optValues->x = a;
    optValues->y = b;
    optValues->resultCallbacks = resultCallbacks;
    pthread_create(&th,NULL,async_func,(void *)optValues);
    return SUCCESS;
}


int main(){

   pthread_mutex_init(&lock,NULL);
   printf("start\n");

   printf("cal_sum 1 called\n");
   if(cal_sum(10,10)!=SUCCESS)
        printf("cal_sum :Failed");
    
   printf("cal_sum 2 called\n"); 
   if(cal_sum(20,20)!=SUCCESS)
        printf("cal_sum :Failed");

    printf("cal_sum 3 called\n");
   if(cal_sum(30,30)!=SUCCESS)
        printf("cal_sum :Failed");

    printf("cal_sum End\n");

   sleep(6);
   printf("End\n"); 
   return 0;
}