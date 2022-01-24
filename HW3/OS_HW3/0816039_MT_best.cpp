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
void *merge_last(void* args);

int main (int argc, const char * argv[]) 
{
    /* Use STDIN (e.g. scanf, cin) to take the input */
    int temp;
    while(cin >> temp){
        numbers.push_back(temp);
    }
    sorted.resize(numbers.size());

    /* Do the sorting */
    int start1 = 0, end1 = numbers.size()/4, start2 = end1+1, end2 = numbers.size()/4*2, start3 = end2+1, end3 = numbers.size()/4*3, start4 = end3+1, end4 = numbers.size()-1;
    
    pthread_t threads[7];
    
    struct insertionSortParams sArgs[4];
    sArgs[0].start = start1;
    sArgs[0].end = end1;
    pthread_create(&threads[0], NULL, insertionSort, &sArgs[0]);    

    sArgs[1].start = start2;
    sArgs[1].end = end2;
    pthread_create(&threads[1], NULL, insertionSort, &sArgs[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    sArgs[2].start = start3;
    sArgs[2].end = end3;
    pthread_create(&threads[2], NULL, insertionSort, &sArgs[2]);    

    sArgs[3].start = start4;
    sArgs[3].end = end4;
    pthread_create(&threads[3], NULL, insertionSort, &sArgs[3]);

    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

    struct mergeParams mArgs[3];
    mArgs[0].begin = start1;
    mArgs[0].mid = start2;
    mArgs[0].end = end2;
    pthread_create(&threads[4], NULL, merge, &mArgs[0]);

    mArgs[1].begin = start3;
    mArgs[1].mid = start4;
    mArgs[1].end = end4;
    pthread_create(&threads[5], NULL, merge, &mArgs[1]);

    pthread_join(threads[4], NULL);
    pthread_join(threads[5], NULL);

    mArgs[2].begin = start1;
    mArgs[2].mid = start3;
    mArgs[2].end = end4;
    pthread_create(&threads[6], NULL, merge_last, &mArgs[2]);

    pthread_join(threads[6], NULL);

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

void *merge_last(void* args){
    struct mergeParams *params = (struct mergeParams*) args;
    int begin = params->begin, mid = params->mid, end = params->end;
    
    int i = begin, j = mid, tpos = begin;

    for(int i = 0 ; i < numbers.size();i++){
        numbers[i] = sorted[i];
    }

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
