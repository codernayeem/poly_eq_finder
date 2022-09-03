#include <iostream>
using namespace std;

float pow(float base, int power){
    // power
    float r = base;
    for (; power != 1; power--)
        r *= base;
    return r;
}

float solve(float x_list[], float y_list[], int start, int end){
    // actual solve mechanism
    return start == end ? y_list[start] : (solve(x_list, y_list, start, end-1)-solve(x_list, y_list, start+1, end)) / (x_list[start]-x_list[end]);
}

int main(){
    int size;
    cin >> size;
    float x_list[size], y_list[size], res[size];
    for(int i=0; i < size; i++)
        cin >> x_list[i] >> y_list[i];

    // solve mechanism
    int size_= size-1;
    for(int index = 0; index != size; index++){
        res[index] = solve(x_list, y_list, 0, size_);
        for (int i = 0; i < size_; i++)
            y_list[i] = y_list[i] - res[index] * pow(x_list[i], size-index-1);
        size_--;
    }

    for (int i=0; i < size; i++)
        cout << "(" << (int)(res[i] * 10000 + (res[i] > 0 ? .5 : -.5)) / 10000. << ", " << size-i-1 << ") ";
    return 0;
}
