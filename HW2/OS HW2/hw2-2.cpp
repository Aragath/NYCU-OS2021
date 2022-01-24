#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
#include <vector>

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
    }


    // do sjf
    int current_time = 0;
    int completed = 0;

    while(completed != n) {
	//find process with minimum burst time among process that are in ready queue at current_time
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
	    // check i'th process is within the current_time & is it completed
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
		// look for the shortest job
                if(p[i].burst_time < mn) {
                    mn = p[i].burst_time;
                    idx = i;
                }
		// look for the earliest arrived process with the shortest job
                if(p[i].burst_time == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                }
            }
        }
	// idx is -1 when there's no matching process
	// idx is the index with the shortest job & ealiest
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
        }
        else {
            current_time++;
        }
        
    }

    // print out the output
    for(int i = 0; i < n; i++) {
	cout << p[i].waiting_time << " " << p[i].turnaround_time << endl;
    }
    cout << total_waiting_time << endl;
    cout << total_turnaround_time << endl;


}
