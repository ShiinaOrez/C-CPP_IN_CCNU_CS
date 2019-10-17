#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct CPU {
    bool running;
};

struct Range {
    int start = 0;
    int finish = 0;
};

struct Clock {
    // The field `Global`'s unit is micro second.
    int global = 0;
    int time_slice_size = 10; // 30ms
} cpu_clock;

struct Process {
    int id;          // process's identifier, should be integer, if you want to change it to string, please change the t-
                     // -ype in the whole source code.
    short int status;// 1 is ready, 2 is wait, 3 is running
    int cost;        // unit is micro second
    int priority;    // less is more priority

    Range time_range;

    bool operator < (const Process &right_p) const {
    	return priority > right_p.priority;
    }
};

CPU new_cpu() {
    return CPU{};
}

Process idle_process{2019, 2, 0, 2019};
// waiting process will join in ready queue when a process finished or be waited.
queue<Process> ready_queue, waiting_queue, running_queue;
int process_count = 0;
int finished_process_count = 0;
int cpu_num = 1;
vector<CPU> cpus;

Process new_process(int id, int status, int cost, int priority) {
    return Process{id, status, cost, priority};
}

vector<Process> fcfs() {
    cout << " info |Calling First Come First Serve Algorithm..." << endl;
    vector<Process> processes;
    Process process_now;
    if (ready_queue.empty() && running_queue.empty()) {
        ready_queue.push(waiting_queue.front());
        waiting_queue.pop();
    }
    while (finished_process_count < process_count) {
        while (!ready_queue.empty() || !running_queue.empty()) {
            if (!running_queue.empty()) {
                process_now = running_queue.front();
                cpus[0].running = true;

                printf(" %4d |Process %3d running...\n", cpu_clock.global, process_now.id);
                cpu_clock.global += process_now.cost;
                running_queue.pop();
                process_now.time_range.finish = cpu_clock.global;
                processes.push_back(process_now);
                finished_process_count += 1;
                cpus[0].running = false;

                printf(" %4d |Process %3d finished.\n", cpu_clock.global, process_now.id);
            } else {
                running_queue.push(ready_queue.front());
                ready_queue.pop();
            }
            if (!waiting_queue.empty()) {
                printf(" %4d |Process %3d ready.\n", cpu_clock.global, waiting_queue.front().id);
                ready_queue.push(waiting_queue.front());
                waiting_queue.pop();
            }
        }
    }

    int waiting_tot = 0;
    for (auto iter=processes.begin(); iter!=processes.end(); iter++) {
        waiting_tot += ((*iter).time_range.finish - (*iter).time_range.start - (*iter).cost);
    }
    cout << "      ╭─────────────┬────────┬──────────╮" << endl;
    cout << "      │ WaitingTime │ Totoal │ Averange │" << endl;
    cout << "      ├─────────────┼────────┼──────────┤" << endl;
    printf ("      │        (ms) │  %4d  │  %6.3f  │\n", waiting_tot, float(waiting_tot)/float(process_count));
    cout << "      ╰─────────────┴────────┴──────────╯" << endl;
    return processes;
}

vector<Process> rr() {
    cout << " info |Calling Round-Robin Algorithm..." << endl;
    vector<Process> processes;
    Process process_now;
    if (ready_queue.empty() && running_queue.empty()) {
    	ready_queue.push(waiting_queue.front());
    	waiting_queue.pop();
    }
    while (finished_process_count < process_count) {
    	while (!ready_queue.empty() || !running_queue.empty()) {
    		if (!running_queue.empty()) {
    			process_now = running_queue.front();
    			cpus[0].running = true;

                printf(" %4d |Process %3d running.\n", cpu_clock.global, process_now.id);
                cpu_clock.global += cpu_clock.time_slice_size;
                running_queue.pop();

    			process_now.cost -= cpu_clock.time_slice_size;
    			if (process_now.cost < 0) { // finished
    				printf(" %4d |Process %3d finished.\n", cpu_clock.global+process_now.cost, process_now.id);
                    process_now.time_range.finish = cpu_clock.global + process_now.cost;
                    processes.push_back(process_now);
    			} else {
                    printf(" %4d |Process %3d paused.\n", cpu_clock.global, process_now.id);
                    process_now.time_range.start += cpu_clock.time_slice_size;
                    ready_queue.push(process_now);
    			}
                
                finished_process_count += 1;
    			cpus[0].running = false;
    		} else {
                running_queue.push(ready_queue.front());
                ready_queue.pop();
    		}
    		if (!waiting_queue.empty()) {
    			printf(" %4d |Process %3d ready.\n", cpu_clock.global, waiting_queue.front().id);
                ready_queue.push(waiting_queue.front());
    		    waiting_queue.pop();
    		}
       	}
    }

    int waiting_tot = 0;
    for (auto iter=processes.begin(); iter!=processes.end(); iter++) {
        waiting_tot += ((*iter).time_range.finish - (*iter).time_range.start - (*iter).cost);
    }
    cout << "      ╭─────────────┬────────┬──────────╮" << endl;
    cout << "      │ WaitingTime │ Totoal │ Averange │" << endl;
    cout << "      ├─────────────┼────────┼──────────┤" << endl;
    printf ("      │        (ms) │  %4d  │  %6.3f  │\n", waiting_tot, float(waiting_tot)/float(process_count));
    cout << "      ╰─────────────┴────────┴──────────╯" << endl;
    return processes;
}

vector<Process> hpf() {
    cout << " info |Calling Highest Priority First Algorithm..." << endl;
    priority_queue<Process> ready_p_queue;
    vector<Process> processes;
    Process process_now;

    while(!ready_queue.empty()) {
    	ready_p_queue.push(ready_queue.front());
    	ready_queue.pop();
    }

    if (ready_p_queue.empty() && running_queue.empty()) {
        ready_p_queue.push(waiting_queue.front());
        waiting_queue.pop();
    }
    while (finished_process_count < process_count) {
    	while (!ready_p_queue.empty() || !running_queue.empty()) {
    		if (!running_queue.empty()) {
    			if (!ready_p_queue.empty()) {
    				Process ready_process, running_process;
    				ready_process = ready_p_queue.top();
    				running_process = running_queue.front();

                    // 抢占!
    				if (ready_process.priority < running_process.priority) {
    					printf(" %4d |Process %3d preempting!\n", cpu_clock.global, ready_process.id);
                        process_now = ready_process;
                        ready_p_queue.pop();
    				} else {
    					process_now = running_process;
    					running_queue.pop();
    				}
    			} else {
    				process_now = running_queue.front();
    				running_queue.pop();
    			}
                
                cpus[0].running = true;

                printf(" %4d |Process %3d running...\n", cpu_clock.global, process_now.id);
                cpu_clock.global += process_now.cost;
                process_now.time_range.finish = cpu_clock.global;
                processes.push_back(process_now);
                finished_process_count += 1;
                cpus[0].running = false;
                printf(" %4d |Process %3d finished.\n", cpu_clock.global, process_now.id);                
    		} else {
    			running_queue.push(ready_p_queue.top());
    			ready_p_queue.pop();
    		}
    		if (!waiting_queue.empty()) {
    			printf(" %4d |Process %3d ready.\n", cpu_clock.global, waiting_queue.front().id);
    			ready_p_queue.push(waiting_queue.front());
    			waiting_queue.pop();
    		}
    	}
    }

    int waiting_tot = 0;
    for (auto iter=processes.begin(); iter!=processes.end(); iter++) {
        waiting_tot += ((*iter).time_range.finish - (*iter).time_range.start - (*iter).cost);
    }
    cout << "      ╭─────────────┬────────┬──────────╮" << endl;
    cout << "      │ WaitingTime │ Totoal │ Averange │" << endl;
    cout << "      ├─────────────┼────────┼──────────┤" << endl;
    printf ("      │        (ms) │  %4d  │  %6.3f  │\n", waiting_tot, float(waiting_tot)/float(process_count));
    cout << "      ╰─────────────┴────────┴──────────╯" << endl;
    return processes;
}

void pre_print() {
    cout << " info |Now please choose the type you want:" << endl;
    cout << "      |1. First Come First Serve."           << endl;
    cout << "      |2. Round-Robin."                      << endl;
    cout << "      |3. Highest Priority First."           << endl;
    return;
}

int main() {
    int id_cache, status_cache, cost_cache, priority_cache;
    vector<Process> result;
    Process process_cache;
    for (int i=0; i<cpu_num; i++) {
        cpus.push_back(new_cpu());
    }
    cout << " info |Welcome to my OS homework-2!" << endl;
    // cout << " info |Do you want to change the number of CPU?(y/n) (default is 1)" << endl;
    cout << " info |Please input the process data:" << endl;
    cout << " info |[p-id] [p-status] [p-cost] [p-priority]" << endl;
    while(1) {
        cout << "      :";
        cin >> id_cache;
        if (id_cache == -1) {
            cout << " ok   |Input over, there're " << process_count << " process(es)." << endl;
            break;
        }
        cin >> status_cache >> cost_cache >> priority_cache;
        process_cache = new_process(id_cache, status_cache, cost_cache, priority_cache);
        process_count += 1;
        switch(status_cache) {
            case 1:
                ready_queue.push(process_cache);
                break;
            case 2:
                waiting_queue.push(process_cache);
                break;
            case 3:
                running_queue.push(process_cache);
                break;
            default:
                process_count -= 1;
                cout << " error|The Process Status MUST be in range 1 to 3! Please input it again!" << endl;
        }
    }

    int choice;
    pre_print();
    cout << "      :";
    cin >> choice;
    cout << " info |...ok, your choice is " << choice << "." << endl;
    switch(choice) {
        case 1:
            result = fcfs();
            break;
        case 2:
            result = rr();
            break;
        case 3:
            result = hpf();
            break;
        default:
            cout << " error|The Choice MUST be in range 1 to 4! Program will be closed." << endl;
    }
    cout << " info |Bye~" << endl;
    return 0;
}