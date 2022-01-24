#include <bits/stdc++.h>

using namespace std;

#define INTERVAL 10000
long long counts = 0; // count the in-circle points


/* function definitions */
void* countInCircle(void *args);

pthread_mutex_t guard = PTHREAD_MUTEX_INITIALIZER;

struct insertionCountParams {
    long numRandPoints;
};


int main (int argc, const char * argv[]) 
{
    int numThreads = 0;
    long numPoints = 0;

    /* take input */
    cin >> numThreads;
    cin>> numPoints;


    /* do counting */
    pthread_t threads[4];
    struct insertionCountParams cArgs[4];

    for(int iter = 0 ; iter < numThreads ; iter++){

	cArgs[iter].numRandPoints = numPoints / numThreads;
	pthread_create(&threads[iter], NULL, countInCircle, &cArgs[iter]);

    }

    /* wait for all threads */
    for(int i = 0 ; i < numThreads ; i++){
	pthread_join(threads[i], NULL);
    }

    /* output */
    cout << "get: " << counts << endl;
    cout << "Pi: " << double(4 * counts) / numPoints << endl;

    return 0;
}

void* countInCircle(void *args){

	// lock
    pthread_mutex_lock(&guard);

    struct insertionCountParams *params = (struct insertionCountParams*)args;
    long numRandPoints = params->numRandPoints;

    double rand_x, rand_y, origin_dist, pi;

    // Initializing rand()
    srand(time(NULL));

    for(int i = 0 ; i < numRandPoints ; i++){
	rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL;

        origin_dist = rand_x * rand_x + rand_y * rand_y;
        if (origin_dist <= 1)
            counts++;

    }
  
	// unlock
    pthread_mutex_unlock(&guard);
}

