#include <bits/stdc++.h>

using namespace std;

vector<int>numbers;
vector<int>sorted;

struct mergeParams{
    int begin;
    int mid;
    int end;
};

struct insertionSortParams {
    int start;
    int end;
};

/* function definitions */
void* insertionSort(void *args);
void *merge(void* args);

int main (int argc, const char * argv[]) 
{
    /* Use STDIN (e.g. scanf, cin) to take the input */
    int temp;
    while(cin >> temp){
        numbers.push_back(temp);
    }
    sorted.resize(numbers.size());

    /* Do the sorting */
    int start1 = 0, end1 = numbers.size()/2, start2 = end1+1, end2 = numbers.size()-1;
    
    pthread_t threads[3];
    
    struct insertionSortParams sArgs[2];
    sArgs[0].start = start1;
    sArgs[0].end = end1;
    pthread_create(&threads[0], NULL, insertionSort, &sArgs[0]);    

    sArgs[1].start = start2;
    sArgs[1].end = end2;
    pthread_create(&threads[1], NULL, insertionSort, &sArgs[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);   

    struct mergeParams mArgs;
    mArgs.begin = start1;
    mArgs.mid = start2;
    mArgs.end = end2;
    pthread_create(&threads[2], NULL, merge, &mArgs);

    pthread_join(threads[2], NULL);

    /* Use STDOUT (e.g. printf, cout) to output the sorted array */
    for(int i = 0 ; i < numbers.size() ; i++){
	cout << sorted[i] << " ";
    }

    return 0;
}

void* insertionSort(void *args){
    struct insertionSortParams *params = (struct insertionSortParams*)args;
    int start = params->start, end = params->end;

    int i = start, j, itemToInsert;

    //everything to the left of i is sorted
    while (i <= end){
        itemToInsert = numbers[i];

        //since everything in this sequence is sorted,
        //starting from i, going in reverse order, shift the elements to the right until an element less than numbers[i] is found
        j = i-1;
        while (j >= start && itemToInsert < numbers[j])
        {
            numbers[j+1] = numbers[j];
            j--;
        }
        //insert the element into s[j]
        numbers[j+1] = itemToInsert;
        i++;
    }
    return NULL;
}

void *merge(void* args){
    struct mergeParams *params = (struct mergeParams*) args;
    int begin = params->begin, mid = params->mid, end = params->end;
    
    int i = begin, j = mid, tpos = begin;
    while(i < mid && j <= end){
	if(numbers[i]<numbers[j]){
	    sorted[tpos++] = numbers[i++];
	}
	else{
	    sorted[tpos++] = numbers[j++];	
	}
    }

    while(i < mid){
	sorted[tpos++] = numbers[i++];
    }

    while(j <= end){
	sorted[tpos++] = numbers[j++];
    }

    return NULL;


}
