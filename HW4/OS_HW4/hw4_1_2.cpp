#include <bits/stdc++.h>
#include <semaphore.h>

using namespace std;

vector<char>numbers;
vector<int>occurence(3, 0); // set vector size to 3 and initlize them as 0

/* function definitions */
void* countOccur(void *args);

pthread_mutex_t guard = PTHREAD_MUTEX_INITIALIZER;
sem_t sem[3];
sem_t locks[3];

struct insertionCountParams {
    int start;
    int end;
    int index;
};


int main (int argc, const char * argv[]) 
{
    int numThreads = 3;
    long seriesLen = 0;

    /* take input */
    cin>> seriesLen;

    char temp;
    while(cin >> temp){
        numbers.push_back(temp);
    }

    /* do counting */
    pthread_t threads[3];
    struct insertionCountParams cArgs[3];

    for(int iter = 0 ; iter < numThreads ; iter++){
	int start = iter * (seriesLen / numThreads);
	int end = start + (seriesLen / numThreads);
        sem_init(&sem[iter], 0, iter ? 0 : 0);
        sem_init(&locks[iter], 0, iter ? 0 : 1);
	


	cArgs[iter].start = start;
	cArgs[iter].end = end;
	cArgs[iter].index = iter;

	pthread_create(&threads[iter], NULL, countOccur, &cArgs[iter]);

    }

    /* wait for all threads */
    for(int i = 0 ; i < numThreads ; i++){
	pthread_join(threads[i], NULL);
    }

    /* output */
    //for(int i = 0 ; i < occurence.size() ; i++){
	//cout << i <<": "<< occurence[i] << endl;
    //}

    return 0;
}

void* countOccur(void *args){

    struct insertionCountParams *params = (struct insertionCountParams*)args;
    int start = params->start, end = params->end, index = params->index;
		// lock count
		sem_wait(&locks[index]);

    for(int i = start ; i < end ; i++){
	if(numbers[i] == '0'){
	    occurence[0] += 1; 
	}
	else if(numbers[i] == '1'){
	    occurence[1] += 1; 
	}
	else if(numbers[i] == '2'){
	    occurence[2] += 1; 
	}
    }    
		// unlock count
		sem_post(&locks[(index+1)%3]);


	if(index == 2){
	    sem_post(&sem[(index+1)%3]);
	}
	
		// lock cout
	sem_wait(&sem[index]);
    	cout << index <<": "<< occurence[index] << endl;

		// unlock count
	sem_post(&sem[(index+1)%3]);

}

