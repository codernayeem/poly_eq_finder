#include <iostream>
using namespace std;

float pow(float base, int power){
    float r = base;
    for (; power != 1; power--)
        r *= base;
    return r;
}

void print_as_list(float x_list[], float y_list[], int size){
    cout << "[";
    for (int i=0; i < size; i++){
        cout << "(" << x_list[i] << ", " << y_list[i] << ")";
        if (i+1!=size)
            cout << ", ";
    }
    cout << "]";
}

float solve(float x_list[], float y_list[], int start, int end){
    // actual solve mechanism
    return start == end ? y_list[start] : (solve(x_list, y_list, start, end-1)-solve(x_list, y_list, start+1, end)) / (x_list[start]-x_list[end]);
}

void get_equation(float x_list[], float y_list[], int size){
    // solve mechanism
    float res[size];
    int size_= size-1;
    for(int index = 0; index != size; index++){
        res[index] = solve(x_list, y_list, 0, size_);
        for (int i = 0; i < size_; i++)
            y_list[i] = y_list[i] - res[index] * pow(x_list[i], size-index-1);
        size_--;
    }
    for (int i = 0; i < size; i++){
        x_list[i] = res[i];
        y_list[i] = size-i-1;
    }
}

float want_num(string qs){
    while (true){
        cout << qs;
        float i;
        try{
            cin >> i;
        }catch(...){
            cout << "[!] - Invalid" << endl;
            continue;
        }
        return i;
    }
}

bool find_duplicate_x(float x_list[], int size, float x){
    for (int i=0; i < size; i++){
        if (x_list[i] == x)
            return true;
    }
    return false;
}

void start() {
    cout << endl << "Assume: y = polynomial equation of x." << endl;
    cout << endl << "[+] - Get your inputs(x) and outputs(y) ready!" << endl;
    int size = 0;
    while (size < 1)
        size = want_num("[?] - How much outputs(y) you know? --> ");
    cout << "[+] - Type the value of x and y one by one" << endl << endl;
    float x_list[size], y_list[size];
    float x, y;
    for(int i=0; i < size; i++){
        while (true){
            x = want_num("[?] - value of x --> ");
            if (!find_duplicate_x(x_list, i, x))
                break;
            cout << "[!] - Duplicate value of x" << endl;
        }
        x_list[i] = x;
        y_list[i] = want_num("[?] - value of y --> ");
        cout << endl;
    }

    cout << "[+] - Got it --> ";
    print_as_list(x_list, y_list, size);
    cout << endl << "[+] - Making Function ..." << endl;
    
    get_equation(x_list, y_list, size);

    // printing Result as List
    cout << endl << "[!] - Data table : ";
    print_as_list(x_list, y_list, size);
    
    // printing Result as String
    cout << endl << "[!] - Success   :  ";
    bool started = false;
    for(int i = 0; i != size; i++){
        x = (int)(x_list[i] * 10000 + (x_list[i] > 0 ? .5 : -.5)) / 10000.;
        y = y_list[i];
        if (x != 0){
            if (x > 0  && started)
                cout << "+";
            if (y == 0)
                cout << x;
            else{
                if (x == -1)
                    cout << "-";
                else if (x != 1)
                    cout << x;
                cout << "x";
                if (y != 1)
                    cout << "^" << int(y);
            }
            started = true;
        }
    }
    if (!started)
        cout << "0";
}

int main(){
    cout << endl << "\t++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\t+++  Polynomial Equation Finder  +++" << endl;
    cout << "\t+++    By Nayeem @codernayeem    +++" << endl;
    cout << "\t++++++++++++++++++++++++++++++++++++" << endl;
    while (true){
        start();
        string s;
        cout << endl << endl << "Enter 'r' to restart or anything to exit > ";
        cin >> s;
        if (s != "r")
            break;
    }
    cout << endl << "\t+++       THANKS FOR USING       +++" << endl;
    return 0;
}
