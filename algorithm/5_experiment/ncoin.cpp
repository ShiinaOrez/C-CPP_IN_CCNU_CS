#include <cstdio>
#include <vector>

using namespace std;

int sum(vector<int> array, int left, int right) {
    int res = 0;
    if (left < 0) {
        return -1;
    }
    for(int i=left; i<right; i++) {
        res += array[i];
    }
    return res;
}

int print(vector<int> array) {
    printf("[ ");
    for (int i=0; i<array.size(); i++) {
        printf("%d ", array[i]);
    }
    printf("]\n");
}

vector<int> slice(vector<int> from, int start, int end) {
    vector<int> res;
    for (int i=start; i<end; i++) {
        res.push_back(from[i]);
    }
    return res;
}

void judge(vector<int> array) {
    int co = 0;
    if (array.size() == 1) {
        printf("Bad coin is: %d\n", array[0]);
        return;
    }
    if (array.size() == 2) {
        return;
    }
    vector<int> res = array;
    while(res.size() > 1) {
        print(res);
        int size = res.size();
        if (size % 3 == 0) {
            int sum1 = sum(res, 0, size/3);
            int sum2 = sum(res, size/3, size/3*2);
            if (sum1 == sum2) {
                co = res[0];
                res = slice(res, size/3*2, size);
            } else {
                co = res[size/3*2];
                res = slice(res, 0, size/3*2);
            }
        } else if (size % 3 == 1) {
            int sum1 = sum(res, 0, size/3);
            int sum2 = sum(res, size/3, size/3*2);
            if (sum1 == sum2) {
                int sum3 = sum(res, size/3*2, size-1);
                if (sum1 == sum3) {
                    printf("Bad coin is: %d\n", res[size]);
                    return;
                } else {
                    co = res[0];
                    res = slice(res, size/3*2, size-1);
                }
            } else {
                int sum3 = sum(res, size/3*2, size-1);
                if (sum1 == sum3) {
                    co = res[0];
                    res = slice(res, size/3, size/3*2);
                } else {
                    co = res[size/3];
                    res = slice(res, 0, size/3);
                }
            }
        } else {
            int sum1 = sum(res, 0, size/3);
            int sum2 = sum(res, size/3, size/3*2);
            if (sum1 == sum2) {
                int sum3 = sum(res, size/3*2, size-2);
                if (sum1 == sum3) {
                    if (res[0] == res[size-2]) {
                        printf("Bad coin is: %d\n", res[size-1]);
                        return;
                    } else {
                        printf("Bad coin is: %d\n", res[size-2]);
                        return;
                    }
                } else {
                    co = res[0];
                    res = slice(res, size/3*2, size/3*3);
                }
            } else {
                int sum3 = sum(res, size/3*2, size-2);
                if (sum1 == sum3) {
                    co = res[0];
                    res = slice(res, size/3, size/3*2);
                } else {
                    co = res[size/3];
                    res = slice(res, 0, size/3);
                }
            }
        }
        print(res);
        if (res.size() == 2) {
            if (res[0] == co) {
                printf("Bad coin is: %d\n", res[1]);
                return;
            } else {
                printf("Bad coin is: %d\n", res[0]);
                return;
            }
        }
    }
    printf("Bad coin is: %d\n", res[0]);
    return;
}

int main() {
    vector<int> array = {1, 1, 2, 1, 1, 1,1,1,1,1,1,1,1, 1, 1};
    judge(array);
    return 0;
}
