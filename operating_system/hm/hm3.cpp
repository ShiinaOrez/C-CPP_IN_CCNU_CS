#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Mock Data:

1 0x0000 120
2 0x0120 20
3 0x0140 50
4 0x0190 10
-1

10 20 30 40 50 10 20 -1
*/

struct partition_t {
	int id;
	string start_address;
	int space;
};

struct request {
	int size;
};

struct result {
	int statu;
	vector<string> addresses;
};

bool comp_address(const partition_t &p1, const partition_t &p2) {
    return p1.start_address < p2.start_address;
}

bool comp_space(const partition_t &p1, const partition_t &p2) {
	return p1.space < p2.space;
}

bool comp_space_reverse(const partition_t &p1, const partition_t &p2) {
	return p1.space > p2.space;
}

result first_fit(vector<partition_t> p_list, vector<request> r_list) {
	result res{1};
	sort(p_list.begin(), p_list.end(), comp_address);

	for (auto r=r_list.begin(); r != r_list.end(); r++) {
		bool found = false;
		for (auto p=p_list.begin(); p != p_list.end(); p++) {
			if ((*p).space >= (*r).size) {
				p->space -= r->size;
				res.addresses.push_back(p->start_address);
				found = true;
				break;
			}
		}
		if (!found) {
			res.statu = -1;
			return res;
		}
	}
	return res;
}

result best_fit(vector<partition_t> p_list, vector<request> r_list) {
	result res{1};
	sort(p_list.begin(), p_list.end(), comp_space);

	for (auto r=r_list.begin(); r != r_list.end(); r++) {
		bool found = false;
		for (auto p=p_list.begin(); p != p_list.end(); p++) {
			if ((*p).space >= (*r).size) {
				p->space -= r->size;
				res.addresses.push_back((*p).start_address);
				found = true;
				break;
			}
		}
		if (!found) {
			res.statu = -1;
			return res;
		}
		sort(p_list.begin(), p_list.end(), comp_space);
	}
	return res;
}

result worst_fit(vector<partition_t> p_list, vector<request> r_list) {
	result res{1};
	sort(p_list.begin(), p_list.end(), comp_space_reverse);

	for (auto r=r_list.begin(); r != r_list.end(); r++) {
		bool found = false;
		for (auto p=p_list.begin(); p != p_list.end(); p++) {
			if ((*p).space >= (*r).size) {
				p->space -= r->size;
				res.addresses.push_back((*p).start_address);
				found = true;
				break;
			}
		}
		if (!found) {
			res.statu = -1;
			return res;
		}
		sort(p_list.begin(), p_list.end(), comp_space_reverse);
	}
	return res;
}

void print_result(result res) {
	if (res.statu == 1) {
		cout << "==>  allocation success" << endl;
	} else {
		cout << "==>  allocation failed" << endl;
	}
	cout << "==>  " << endl;
	int length = res.addresses.size();
	for (int i=0; i<length; i++)
		cout << "     " << res.addresses[i] << endl;
	return ;
}

int main() {
 	vector<partition_t> partition_t_list;
 	vector<request> request_list;

 	cout << "Welcome to my operating system homework3" << endl;
 	cout << "==>  please input the data:" << endl;
 	cout << "==>  format: (id, start_address, space)" << endl;
    cout << "==>  if id == -1, stop input" << endl;

    int id_cache=0;
    cin >> id_cache;
    while(id_cache != -1) {
    	string start_address;
    	int space;
    	cin >> start_address >> space;
    	partition_t new_partition_t = partition_t{id_cache, start_address, space};
    	partition_t_list.push_back(new_partition_t);
    	cin >> id_cache;
    }

    int size_cache = 1;
    cout << "==>  please input the request sequence:" << endl;
    cout << "==>  format: (request size)" << endl;
    cout << "==>  if id <= 0, stop input" << endl;

    while(size_cache > 0) {
    	cin >> size_cache;
    	request new_request = request{size_cache};
    	request_list.push_back(new_request);
    }

    cout << "==>  input over." << endl;
    cout << "==>  please select the algorithm:" << endl;
    cout << "==>  1: First Fit" << endl;
    cout << "==>  2: Best  Fit" << endl;
    cout << "==>  3: Worst Fit" << endl;
    cout << "==>  4: All Above" << endl;

    int flag=0;

    cin >> flag;
    switch(flag) {
    	case 1: {
    		result res = first_fit(partition_t_list, request_list);
    		print_result(res);
    		break;
    	}
    	case 2: {
    		result res = best_fit(partition_t_list, request_list);
    		print_result(res);
    		break;
    	}
    	case 3: {
    		result res = worst_fit(partition_t_list, request_list);
    		print_result(res);
    		break;
    	}
    	case 4: {
    		result res = first_fit(partition_t_list, request_list);
    		print_result(res);
    		res = best_fit(partition_t_list, request_list);
    		print_result(res);
    		res = worst_fit(partition_t_list, request_list);
    		print_result(res);
    		break;
    	}
    	default: {
    		cout << "==>  please choose 1~4 !" << endl;
    	}
    }
    cout << "==>  program over~" << endl;
    return 0;
}