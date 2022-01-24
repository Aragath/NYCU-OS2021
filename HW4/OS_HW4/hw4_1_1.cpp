#include <bits/stdc++.h>

using namespace std;

vector<char>numbers;
vector<int>occurence(3, 0); // set vector size to 3 and initlize them as 0

/* function definitions */
void* countOccur(void *args);

pthread_mutex_t guard = PTHREAD_MUTEX_INITIALIZER;

struct insertionCountParams {
    int start;
    int end;
};


int main (int argc, const char * argv[]) 
{
    int numThreads = 0;
    long seriesLen = 0;

    /* take input */
    cin >> numThreads;
    cin>> seriesLen;

    char temp;
    while(cin >> temp){
        numbers.push_back(temp);
    }

    /* do counting */
    pthread_t threads[4];
    struct insertionCountParams cArgs[4];

    for(int iter = 0 ; iter < numThreads ; iter++){
	int start = iter * (seriesLen / numThreads);
	int end = start + (seriesLen / numThreads);

	cArgs[iter].start = start;
	cArgs[iter].end = end;

	pthread_create(&threads[iter], NULL, countOccur, &cArgs[iter]);

    }

    /* wait for all threads */
    for(int i = 0 ; i < numThreads ; i++){
	pthread_join(threads[i], NULL);
    }

    /* output */
    for(int i = 0 ; i < occurence.size() ; i++){
	cout << i <<": "<< occurence[i] << endl;
    }

    return 0;
}

void* countOccur(void *args){

	// lock
    pthread_mutex_lock(&guard);

    struct insertionCountParams *params = (struct insertionCountParams*)args;
    int start = params->start, end = params->end;

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
	// unlock
    pthread_mutex_unlock(&guard);
}

