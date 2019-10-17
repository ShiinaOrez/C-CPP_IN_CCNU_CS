// copyright: 2019-09-23 ShiinaOrez
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

#define max_works 1005

using namespace std;

struct MyTime {
    int hour;
    int mins;

    bool operator < (const MyTime &right_time) const {
        return hour < right_time.hour ? true : hour > right_time.hour ? false : mins < right_time.mins ? true : false;
    }
    bool operator == (const MyTime &right_time) const {
        return hour == right_time.hour && mins == right_time.mins;
    }

    void operator - (const MyTime &right_time) {
        int sub_hour = hour - right_time.hour;
        int sub_mins = mins - right_time.mins;
        if (sub_mins < 0) {
            sub_mins += 60;
            sub_hour -= 1;
        } else if (sub_mins >= 60) {
            sub_hour += (sub_mins/60);
            sub_mins %= 60;
        }
        hour = sub_hour;
        mins = sub_mins;
        return;
    }
};

struct Work {
	int  id;
	MyTime entry_time;
    int cost;

    bool operator < (const Work &right_work) const {
        return cost < right_work.cost;
    }
};

struct WorkWithRatio {
    Work work;
    double ratio;
};

struct Info {
    Work work;
    MyTime start_time;
    MyTime end_time;
};

struct MyTime resolve_string_to_time(char* from) {
	int length = strlen(from);
	int hour=0, mins=0, re=1;
	mins += ((from[length-1]-'0') + (from[length-2]-'0')*10);
	for (int i=0; i<=length-3; i++) {
		hour += re * (from[i]-'0');
		re *= 10;
	}
	return MyTime{
		hour,
		mins
	};
}

void pre_print() {
    cout << "[info]|Now please choose the type you want:" << endl;
    cout << "      |1. First Come First Serve."           << endl;
    cout << "      |2. Shortest Job First."               << endl;
    cout << "      |3. Highest Response Ratio Next."      << endl;
    cout << "      |4. All Above."                        << endl;
    return;
}

void print_excel(vector<Info> infos) {
    cout << "      ╭─────┬───────────┬──────┬───────────┬─────────┬─────────┬────────────────────────╮" << endl;
    cout << "      │ JOB │ EntryTime │ Cost │ StartTime │ EndTime │ RunTime │ TakesPowerTurnoverTime │" << endl;
//  cout << "      ╰─────┴───────────┴──────┴───────────┴─────────┴─────────┴────────────────────────╯" << endl;

    float tot_runtime = 0, tot_wi_time = 0;

    for (auto iter=infos.begin(); iter!=infos.end(); iter++) {
    	Info info = (*iter);
    	MyTime sub_time = info.end_time;
    	sub_time - info.work.entry_time;
        tot_runtime += (sub_time.hour*60+sub_time.mins);
        tot_wi_time += (float(sub_time.hour*60+sub_time.mins) / float(info.work.cost));

    	printf("      ├─────┼───────────┼──────┼───────────┼─────────┼─────────┼────────────────────────┤\n");
    	printf("      │ %3d │  [%02d:%02d]  │ %4d │  [%02d:%02d]  │ [%02d:%02d] │  %5d  │        %8.4f        │\n", \
    		info.work.id, \
    		info.work.entry_time.hour, info.work.entry_time.mins, \
    		info.work.cost, \
    		info.start_time.hour, info.start_time.mins, \
    		info.end_time.hour, info.end_time.mins, \
    		sub_time.hour*60+sub_time.mins, \
    		float(sub_time.hour*60+sub_time.mins) / float(info.work.cost));
    }
    printf("      ├─────┴───────────┴──────┴───────────┴─────────┼─────────┼────────────────────────┤\n");
    printf("      │ T = %8.4f mins                            │         │                        │\n", tot_runtime/infos.size());
    printf("      │ W = %8.4f                                 │  %5d  │        %8.4f        │\n", tot_wi_time/infos.size(), int(tot_runtime), tot_wi_time);
    printf("      ╰──────────────────────────────────────────────┴─────────┴────────────────────────╯\n");
}

bool comp(const Work &w1, const Work &w2) {
    return w1.cost < w2.cost;
}

bool compRatio(const WorkWithRatio &w1, const WorkWithRatio &w2) {
    return w1.ratio > w2.ratio;
}

vector<Info> fcfs(queue<Work> works, MyTime start_time) {
	MyTime mytime=start_time;
	int run_time=0;
	vector<Info> infos;

    while(!works.empty()) {
    	Work work_now = works.front();
    	if (mytime < work_now.entry_time) {
    	    mytime = work_now.entry_time;
    	}
        printf("[time]| [%02d:%02d] Start new work: %d.\n", mytime.hour, mytime.mins, work_now.id);
    	
    	Info info;
    	info.work = work_now;
    	info.start_time = mytime;

    	mytime.mins += work_now.cost;
    	mytime.hour += (mytime.mins/60);
    	mytime.mins %= 60;

    	info.end_time = mytime;
    	infos.push_back(info);

    	MyTime sub_time=mytime;
    	sub_time - work_now.entry_time;
    	run_time += (sub_time.hour*60 + sub_time.mins);

    	works.pop();
    	cout << "[log] | ..Done. Start next work." << endl;
    }

    cout << "[log] | ...Finished! ";
    mytime - start_time;
    printf("Running Cost: [%02d:%02d].\n", run_time/60, run_time%60);
    return infos;
}

vector<Info> sjf(queue<Work> works, MyTime start_time) {
    MyTime mytime=start_time;
    vector<Work> work_cache;
    int length = works.size(), run_time=0;
    vector<Info> infos;

    for (int i=0; i<length; i++) {
        // load works
        while(!works.empty() && (works.front().entry_time < mytime || works.front().entry_time == mytime)) {
            work_cache.push_back(works.front());
            works.pop();
        }
        if (work_cache.size() == 0 && !works.empty()) {
            mytime = works.front().entry_time;
            work_cache.push_back(works.front());
            works.pop();
        }
        sort(work_cache.begin(), work_cache.end(), comp);
        Work work_now = work_cache[0];
        
        Info info;
        info.work = work_now;
        info.start_time = mytime;

        printf("[time]| [%02d:%02d] Start new work: %d.\n", mytime.hour, mytime.mins, work_now.id);
        mytime.mins += work_now.cost;
        mytime.hour += (mytime.mins/60);
        mytime.mins %= 60;

        info.end_time = mytime;
        infos.push_back(info);

        MyTime sub_time=mytime;
        sub_time - work_now.entry_time;
        run_time += (sub_time.hour*60 + sub_time.mins);

        work_cache.erase(work_cache.begin());
        cout << "[log] | ..Done. Start next work." << endl;
    }

    cout << "[log] | ...Finished! ";
    mytime - start_time;
    printf("Running Cost: [%02d:%02d].\n", run_time/60, run_time%60);
    return infos;
}

vector<Info> hrrn(queue<Work> works, MyTime start_time) {
    MyTime mytime=start_time;
    vector<Info> infos;
    vector<WorkWithRatio> work_cache;
    while(!works.empty()) {
        work_cache.push_back(WorkWithRatio{works.front(), 1.0});
        works.pop();
    }
    int length = work_cache.size(), run_time=0;

    for (int i=0; i<length; i++) {
        // fixed time
        if (work_cache.size() == 0) {
            mytime = works.front().entry_time;
        }
        // load works
        while(!works.empty() && (works.front().entry_time < mytime || works.front().entry_time == mytime)) {
            work_cache.push_back(WorkWithRatio{works.front(), 1.0});
            works.pop();
        }
        for (auto iter=work_cache.begin(); iter!=work_cache.end(); iter++) {
            MyTime copy_time=mytime;
            copy_time - (*iter).work.entry_time;
            (*iter).ratio = 1 + ((copy_time.hour*60 + copy_time.mins) / (*iter).work.cost);
        }
        sort(work_cache.begin(), work_cache.end(), compRatio);
        Work work_now = work_cache[0].work;

        Info info;
        info.work = work_now;
        info.start_time = mytime;

        printf("[time]| [%02d:%02d] Start new work: %d.\n", mytime.hour, mytime.mins, work_now.id);
        mytime.mins += work_now.cost;
        mytime.hour += (mytime.mins/60);
        mytime.mins %= 60;

        info.end_time = mytime;
        infos.push_back(info);

        MyTime sub_time=mytime;
        sub_time - work_now.entry_time;
        run_time += (sub_time.hour*60 + sub_time.mins);

        work_cache.erase(work_cache.begin());
        cout << "[log] | ..Done. Start next work." << endl;
    }

    cout << "[log] | ...Finished! ";
    mytime - start_time;
    printf("Running Cost: [%02d:%02d].\n", run_time/60, run_time%60);
    return infos;
}

int main() {
	queue<Work> works;
	int id_cache, cost_cache;
	char entry_time_cache[5];

	cout << "[****]|Welcome to my OS homework-1!" << endl;
	cout << "[info]|Please input the meta data:" << endl;
	cout << "      |[work-id] [entry-time] [cost-time]" << endl;

	// input the meta data to `works` as vector's element
    while(1) {
        cin >> id_cache;
        if (id_cache == -1) {
        	cout << "[log] |Input Over." << endl;
        	break;
        } else {
        	cin >> entry_time_cache >> cost_cache;
            works.push(Work{
                id_cache,
                resolve_string_to_time(entry_time_cache),
                cost_cache
            });
        }
    }

    pre_print();
    int choice=0;

    while(choice <= 0 || choice >= 5) {
    	cout << "[info]|Please Input: ";
    	cin >> choice;
    }

    cout << "[log] | ...OK, your choice is " << choice << endl;

    vector<Info> result;

    switch(choice) {
    	case 1: {
            cout << "[log] |Frist Come First Serve Algorithm: Start." << endl;
            result = fcfs(works, works.front().entry_time);
            print_excel(result);
            break;
    	}
    	case 2: {
    	    cout << "[log] |Shortest Job First Algorithm: Start." << endl;
            result = sjf(works, works.front().entry_time);
            print_excel(result);
            break;
    	}
    	case 3: {
            cout << "[log] |Highest Response Ratio Next Algorithm: Start." << endl;
            result = hrrn(works, works.front().entry_time);
            print_excel(result);
            break;
    	}
    	case 4:  {
            cout << "[log] |Frist Come First Serve Algorithm: Start." << endl;
            result = fcfs(works, works.front().entry_time);
            print_excel(result);
            cout << "[log] |Shortest Job First Algorithm: Start." << endl;
            result = sjf(works, works.front().entry_time);
            print_excel(result);
            cout << "[log] |Highest Response Ratio Next Algorithm: Start." << endl;
            result = hrrn(works, works.front().entry_time);
            print_excel(result);
    	}
    }

    cout << "[log] | ...Over, bye~" << endl;
    return 0;
}