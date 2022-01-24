#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
#include <vector>
#include <queue>

using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    // input num of process
    int n;
    cin >> n;

    // set vectors and variables
    vector<struct process> p(n);
    vector<int> burst_remaining(n);
    vector<int> is_completed(n);
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    // input arrival time, burst time
    for(int i = 0; i < n; i++) {
	p[i].pid = i+1;
        cin>>p[i].arrival_time;
    }

    for(int i = 0 ; i< n;i++){
	cin>>p[i].burst_time;
	burst_remaining[i] = p[i].burst_time;
    }

    // input time quantum
    int tq;
    cin >> tq;


    // do rr
    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    vector<int> mark(n); // mark whether the process has been in ready queue before
    mark[0] = 1;

    while(completed != n) {
	// take in the first process in queue & pop it
        int idx = q.front();
        q.pop();
	
	// check whether the process comes in the first time and set its start time
	if(burst_remaining[idx] == p[idx].burst_time){
	    p[idx].start_time = max(current_time, p[idx].arrival_time);
	    current_time = p[idx].start_time;
	}

	// if the remaining time is larger than tq, use all the tq 
	if(burst_remaining[idx]-tq > 0){
	    burst_remaining[idx] -= tq;
	    current_time += tq;
	}

	// the remaining time is shorter than tq
        else{
	    current_time += burst_remaining[idx];
	    burst_remaining[idx] = 0;
	    completed++;

	    p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
	}
	
	// check the arrival time & current time and push new ready processes to queue
	for(int i =0 ; i < n ;i++){
	    if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0){
		q.push(i);
		mark[i] = 1;
	    }
	}

	// if the process is not finished, push it back to queue
	if(burst_remaining[idx] > 0){
	    q.push(idx);
	}
        

    }

    // print out the output
    for(int i = 0; i < n; i++) {
	cout << p[i].waiting_time << " " << p[i].turnaround_time << endl;
    }
    cout << total_waiting_time << endl;
    cout << total_turnaround_time << endl;


}
