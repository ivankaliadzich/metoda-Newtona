#include <iostream>
#include <vector>
#include<string>
#include <cmath>
#include <algorithm>

using namespace std;

struct interval{
    double l, r;
};

string eq;
double l, r, eps;
int i=0, iter=0, max_iter, max_eq=-1, power=-1;
vector <double> eqi_l;
vector <double> eqi_r;
vector <double> values_l;
vector <double> values_r;
vector <interval> equation(10);
interval limits;

void transformation(string eq){
    string str="";
    bool inter=false, b=false, Minus = false, min_int=false;
    double number=0;
    int i, j, fraction=1;

    for ( i=0; i<eq.size(); i++){
if (eq[i] == '-' && eq[i+1] == '[' ){
                        Minus = true;
}
        if (eq[i]=='x'){
            for (j=0; j<str.size(); j++){

                if (str[j] == '['){
                    inter=true;
                }else if (str[j] == ']'){
                    limits.r = number/fraction;
                    if (Minus == true){
                        limits.r*=-1;
                    }
                    Minus = false;
                    if (min_int == true){
                    limits.r*=-1;
                }
                min_int = false;
                    number = 0;
                    fraction=1;
                }else if (str[j]>='0' && str[j]<='9'){
                    if (str[j-1] == '-' && (str[j-2]=='[' || str[j-2]==';')){
                        min_int=true;
                    }
                    number*=10;
                    number+=str[j]-'0';
                    if (b==true){
                        fraction*=10;
                    }
                }else if (str[j] == '.'){
                    b=true;
                }else if (str[j] == ';'){
                limits.l = number/fraction;
                if (Minus == true){
                        limits.l*=-1;
                    }

                if (min_int == true){
                    limits.l*=-1;
                }
                min_int = false;
                b=false;
                number = 0;
                fraction=1;
                }
            }
            if (inter == false){
                    for(int j=0; j<str.size(); j++){
                        if (str[j]=='-'){
                            Minus = true; break;
                        }
                    }
                limits.l = number/fraction;
                limits.r = number/fraction;
                if (Minus == true){
                        limits.r*=-1;
                        limits.l*=-1;
                    }
                    Minus = false;
            }
                inter = false;
                b=false;
                number = 0;
                fraction=1;
                if (eq[i+1]=='^' && eq[i+2]>='0' && eq[i+2]<='9'){
                equation[eq[i+2]-'0'] = limits;
                power = max(power, (eq[i+2]-'0'));
                i+=2;
            } else {
                equation[1] = limits;
            }
            str="";
            Minus = false;
        } else if (eq[i] == '!'){
                for (j=0; j<str.size(); j++){
                if (str[j] == '['){
                    inter=true;
                }else if (str[j] == ']'){
                    limits.r = number/fraction;
                    if (Minus == true){
                        limits.r*=-1;
                    }
                    Minus = false;
                    if (min_int == true){
                    limits.r*=-1;
                }
                min_int=false;
                    number = 0;
                    fraction=1;
                }else if (str[j]>='0' && str[j]<='9'){
                    if (str[j-1] == '-'){
                        min_int=true;
                    }
                    number*=10;
                    number+=str[j]-'0';
                    if (b==true){
                        fraction*=10;
                    }
                }else if (str[j] == '.'){
                    b=true;
                }else if (str[j] == ';'){
                limits.l = number/fraction;
                if (Minus == true){
                        limits.l*=-1;
                    }
                    Minus = false;
                    if (min_int == true){
                    limits.l*=-1;
                    limits.r*=-1;
                }
                min_int = false;
                b=false;
                number = 0;
                fraction=1;
                }
            }
            if (inter == false){
                    for(int j=0; j<str.size(); j++){
                        if (str[j]=='-'){
                            Minus = true; break;
                        }
                    }
                limits.l = number/fraction;
                limits.r = number/fraction;
                if (Minus == true){
                        limits.r*=-1;
                        limits.l*=-1;
                    }
                    Minus = false;

            }
                inter = false;
                b=false;
                number = 0;
                fraction=1;
                equation[0] = limits;
            str="";
            Minus = false;
        } else {
            str+=eq[i];
        }
    }
}

double f_l(double x){
    double Left=0;
    for (int i=0; i<=power; i++){
        double xxx=1;
        for (int q=1; q<=i; q++){
            xxx*=x;
        }
        Left+=xxx*eqi_l[i];
    }
    return Left;
}

double f_r(double x){
    double Right=0;
    for (int i=0; i<=power; i++){
        double xxx=1;
        for (int q=1; q<=i; q++){
            xxx*=x;
        }
        Right+=xxx*eqi_r[i];
    }
    return Right;
}

double df_l(double x){
    double f_d;
    f_d = (f_l(x + eps) - f_l(x - eps)) / (2 * eps);
    return f_d;
}

double df_r(double x){
    double f_d;
    f_d = (f_r(x + eps) - f_r(x - eps)) / (2 * eps);
    return f_d;
}

int main()
{
    cout << "Write an equation" << endl;
    getline(cin, eq);
    eq+='!!!';
    transformation(eq);
    for (int i=0; i<equation.size(); i++){
            if (equation[i].l > equation[i].r){
                swap(equation[i].l , equation[i].r);
            }
            eqi_l.push_back(equation[i].l);
            eqi_r.push_back(equation[i].r);
        }

    cout <<endl <<  "Write an interval" << endl ;
    cin >> l >> r;
    values_l.push_back(l);
    values_r.push_back(r);

    cout <<endl <<  "Write an accuracy of calculations" << endl ;
    cin >> eps;

    cout <<endl <<  "Write a maximum number of iterators" << endl;
    cin >> max_iter;

    i=0;
    while (max_iter > iter){
        double a, b;
        a = values_l[i] - f_l(values_l[i])/df_l(values_l[i]);
        b = values_r[i] - f_r(values_r[i])/df_r(values_r[i]);
        values_l.push_back(a); values_r.push_back(b);
        if (abs(values_l[i+1]-values_l[i])<eps || abs(values_r[i+1]-values_r[i])<eps){
            break;
        }
        if (values_l[i+1]>values_r[i+1]){
            swap(values_l[i+1], values_r[i+1]);
        }
        i++;
        iter++;
    }

     cout << endl << "Equations: " <<endl;
    for (int i=0; i<10; i++){
           if (eqi_l[i]!=0 && eqi_r[i]!=0){
            cout << eqi_l[i] << " " << eqi_r[i] << endl << endl;;
           }
        }

    cout << "Answer = [" << values_l[values_l.size()-1] << " ; " << values_r[values_r.size()-1] << "]" << endl;
    cout << "Width of compartment = " << values_r[values_r.size()-1]-values_l[values_l.size()-1] <<  endl;

    return 0;
}
