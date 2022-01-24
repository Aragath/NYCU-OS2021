#include <stdio.h>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

int main(){
	
	// input numbers of process, arrive time, burst time
	int n_process, temp;
	cin >> n_process;

	vector<int>arrival_time(n_process);
	vector<int>burst_time(n_process);;
	vector<int>finishing_time(n_process);;

	for(int i = 0 ; i < n_process ; i++){
		cin >> temp;
		arrival_time[i] = temp;
	}
	for(int i = 0 ; i < n_process ; i++){
		cin >> temp;
		burst_time[i]= temp;
	}	

	// set output container
	vector<int>waiting_time(n_process);;
	vector<int>turnaround_time(n_process);;

	// calculate fcfs finishing time
	finishing_time[0] = arrival_time[0] + burst_time[0]; // the first process's finishing time is always its arrival + burst
	for(int i = 1 ; i < n_process ; i++){
		finishing_time[i] = finishing_time[i-1] + burst_time[i];
	}

	// calculate fcfs turnaround time & waiting time
	for(int i = 0 ; i < n_process ; i++){
		turnaround_time[i] = finishing_time[i] - arrival_time[i];
		waiting_time[i]= turnaround_time[i] - burst_time[i];
	}

	// print out
	for(int i = 0 ; i < n_process; i++){
		cout << waiting_time[i] << " " << turnaround_time[i] << endl;
	}
	cout << accumulate(waiting_time.begin(), waiting_time.end(), 0) << endl;
	cout << accumulate(turnaround_time.begin(), turnaround_time.end(), 0);
	
	return 0;
}
