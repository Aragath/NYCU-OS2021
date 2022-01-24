#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
#include <vector>
#include <queue>
#include <deque>

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
    fill(is_completed.begin(), is_completed.end(), 0);
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


    // do mfq
    deque<int> q1,q2;
    int current_time = 0;
    q1.push_back(0);
    int completed = 0;
    vector<int> mark(n); // mark whether the process has been in ready queue before
    mark[0] = 1;

    while(completed != n) {
	if(!q1.empty()){
	    // take in the first process in queue & pop it
            int idx = q1.front();
            q1.pop_front();
	
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
	        is_completed[idx] = 1;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
	    }
	
	    // check the arrival time & current time and push new ready processes to queue
	    for(int i =0 ; i < n ;i++){
	        if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0){
		    q1.push_back(i);
		    mark[i] = 1;
	        }
	    }

	    // if the process is not finished, push it to queue 2
	    if(burst_remaining[idx] > 0){
	        q2.push_back(idx);
	    }
	}
	
	
	
	// do srtf
	if(q1.empty()){
	    //find process with minimum remaining burst time in queue 2
	    int idx = -1, loc;
	    int mn = 10000000;
	    for(int i = 0; i < q2.size() ; i++){
		if(p[q2[i]].arrival_time <= current_time && is_completed[q2[i]] == 0){
		    if(burst_remaining[q2[i]] < mn){
			mn = burst_remaining[q2[i]];
			idx = q2[i];
			loc = i;
		    }
		    if(burst_remaining[q2[i]] == mn){
			if(p[q2[i]].arrival_time < p[idx].arrival_time){
			    mn = burst_remaining[q2[i]];
			    idx = q2[i];
			    loc = i;
			}
		    }
		}
	    }
	    // idx is -1 when there's no matching process
	    // idx is the index with the shortest remaining job & ealiest	    
	    if(idx != -1){
		burst_remaining[idx] -= 1;
		current_time++;
		
		// if the process is finished
		if(burst_remaining[idx] == 0){
		    p[idx].completion_time = current_time;
		    p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                    p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

		    total_turnaround_time += p[idx].turnaround_time;
                    total_waiting_time += p[idx].waiting_time;

		    is_completed[idx] =1;
		    completed++;
		    q2.erase(q2.begin() + loc);
		}

		// if the process is not finished, erase from queue and push back to it 
		else{
		    q2.erase(q2.begin() + loc);
		    q2.push_back(idx);
		}
	    }

	    else{
		current_time++;
	    }
	    
	    // check the arrival time & current time and push new ready processes to queue 1
	    for(int i =0 ; i < n ;i++){
	        if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0){
		    q1.push_back(i);
		    mark[i] = 1;
	        }
	    }
	}
        

    }

    // print out the output
    for(int i = 0; i < n; i++) {
	cout << p[i].waiting_time << " " << p[i].turnaround_time << endl;
    }
    cout << total_waiting_time << endl;
    cout << total_turnaround_time << endl;


}
