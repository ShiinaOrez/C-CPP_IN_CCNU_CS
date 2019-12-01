#include <iostream>
#include <vector>

using namespace std;

struct Page {
	int times; // 调用次数
	int code;  // 页码
};

struct Storge {
	vector<Page> pages;
	int space;
} storge;

void init_storge(int space) {
	storge = Storge{};
	storge.space = space;
}

void pre_print() {
	cout << "[info]|Welcome To My Homework 4" << endl;
    return;
}

void print_failures(vector<int> f_list) {
	cout << "[out] |Failure List:" << endl << "      |";
	for (auto f=f_list.begin(); f!=f_list.end(); f++) {
		cout << *f << " ";
	}
	cout << endl;
}

void FIFO(vector<int> r_list) {
	cout << "[info]|Using FIFO Algorithm..." << endl;
	int missing = 0;
	vector<int> f_list; // failure list
	for (auto r=r_list.begin(); r!=r_list.end(); r++) {
		bool found = false;
		for (auto p=storge.pages.begin(); p!=storge.pages.end(); p++) {
			if (p->code == *r) {
				found = true;
				p->times += 1;
				// Page page_cache = *p;
				// page_cache.times += 1;
				// storge.pages.erase(p);
				// storge.pages.push_back(page_cache);
				break;
			}
		}
		if (found) {
			continue;
		}
		missing += 1;
		Page new_page = Page{1, *r};
		if (storge.pages.size() < storge.space) {
			storge.pages.push_back(new_page);
		} else {
			f_list.push_back(storge.pages.begin()->code); // record failure
			storge.pages.erase(storge.pages.begin());
			storge.pages.push_back(new_page);
		}
	}
	print_failures(f_list);
	cout << "[miss]|" << missing << endl;
	cout << "[rate]|" << float(missing)/float(r_list.size()) << endl;
	return;
}

void LRU(vector<int> r_list) {
	cout << "[info]|Using LRU Algorithm..." << endl;
	int missing = 0;
	vector<int> f_list; // failure list
	for (auto r=r_list.begin(); r!=r_list.end(); r++) {
		bool found = false;
		for (auto p=storge.pages.begin(); p!=storge.pages.end(); p++) {
			if (p->code == *r) {
				found = true;
				Page page_cache = *p;
				page_cache.times += 1;
				storge.pages.erase(p);
				storge.pages.push_back(page_cache);
				break;
			}
		}
		if (found) {
			continue;
		}
		missing += 1;
		Page new_page = Page{1, *r};
		if (storge.pages.size() < storge.space) {
			storge.pages.insert(storge.pages.begin(), new_page);
		} else {
			auto failure = storge.pages.end();
			for (auto p=storge.pages.end(); p!=storge.pages.begin(); p--) {
				if (p->times <= failure->times) {
					failure = p;
				}
			}
			f_list.push_back(failure->code); // record failure
			storge.pages.erase(failure);
			storge.pages.push_back(new_page);
		}
	}
	print_failures(f_list);
	cout << "[miss]|" << missing << endl;
	cout << "[rate]|" << float(missing)/float(r_list.size()) << endl;
	return;
}

int main() {
	int page = 3, pages = 0;
	vector<int> r_list; // request list
	pre_print();
	cout << "[info]|Now Please Input Storge Space Page Number:" << endl;
	cin >> page;
	init_storge(page);
    cout << "[info]|Now Please Input Pages List Length:" << endl;
    cin >> pages;
    cout << "[info]|Now Please Input Pages List:";
    for (int i=0; i<pages; i++) {
    	int page_now;
    	cin >> page_now;
    	r_list.push_back(page_now);
    }

    cout << "[info]|Input Over~" << endl;
    cout << "[info]|Now Please Choose The Algorithm:" << endl;
    cout << "[info]|1. FIFO" << endl;
    cout << "[info]|2. LRU" << endl;
    cout << "[info]|3. Both FIFO And LRU" << endl;
	int type;
	cin >> type;
	switch(type) {
		case 1: {
			FIFO(r_list);
			break;
		}
		case 2: {
			LRU(r_list);
			break;
		}
		case 3: {
			FIFO(r_list);
			init_storge(page);
			LRU(r_list);
			break;
		}
		default:
			cout << "[warn]|Algorithm Type Must In Range(1, 3)!" << endl;
	}
	return 0;
}