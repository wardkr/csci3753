/*Kyle Ward
CSCI-3753
PA3*/

/*Multi-lookup.c*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>

//#include "multi-lookup.h"

#define SHARED_SIZE 100
#define MAX_RESOLVER_THREADS 10
#define MAX_REQUESTER_THREADS 5
#define MAX_NAME_LENGTH 1025
#define MAX_IP_LENGTH INET6 ADDRSTRLEN


#define NUM_THREADS 5
#define NUM_FILES 5




/*struct of arguements to pass to the threads*/
struct s_array{
	char array[20][MAX_NAME_LENGTH];
	pthread_mutex_t writemutex;
};


struct t_data{
	int thread_id;
	int file_number;
	FILE** files_array;
	s_array* sharred_array;
	
};





void *request(void *incoming){
	size_t line = MAX_NAME_LENGTH;
	struct t_data *data;
	data = (struct t_data*)incoming;

	char *hostname = NULL;

	printf("Hello World! It's me, thread #%d!\n", data->thread_id);
/*	printf("%lu\n", data->files_array[data->thread_id-1]);
	printf("after filer pointer print\n");*/

	while(getline(&hostname, &line, data->files_array[data->thread_id-1]) != -1){
		//printf("in loop\n");
		printf("Thread%d read: %s\n", data->thread_id, hostname);

	}
	


	/*FILE *ifp;
	ifp = fopen(data->files_array[tid], "r");
	if(!ifp){
		printf("file open error\n");
	}
	else{
		printf("Thread%d beginning to read from file\n", data->thread_id);
		while (fscanf(ifp, "%s", domain) != EOF){
			printf("Thread%d read: %s\n", data->thread_id, domain);
			//sharred_array[i] = domain; 
	*/
	pthread_exit(NULL);
}



int main(){


	
	FILE *files[NUM_FILES];
	char* names[] = {"names1.txt","names2.txt","names3.txt","names4.txt","names5.txt"};

	pthread_t req_threads[5];
	pthread_t res_threads[5];
	int tc;
	int i, t, f;
	typedef struct s_array *msa_array;
	struct t_data t_data_array[5];

	for(f=0; f<NUM_FILES; f++){
		files[f] = fopen(names[f], "r");
		printf("%s\n", names[f]);
	}


	for (i=1; i<(NUM_THREADS+1); i++){
    	t_data_array[i].thread_id = i;
    	t_data_array[i].file_number = i;
    	t_data_array[i].sharred_array = msa_array;
    	t_data_array[i].files_array = files;
    }


	for(t=1; t<6; t++){
		printf("creating thread %d\n", t);
		//t_data_array[i].filename = "z";
		tc = pthread_create(&req_threads[t], NULL, request, (void *) &t_data_array[t]);
		if (tc){
			printf("ERROR; return code from pthread_create() is %d\n", tc);
			exit(-1);
		}
	}

	/* Last thing that main() should do */
	pthread_exit(NULL);



	return 0;
}