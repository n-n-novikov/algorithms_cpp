#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <cmath>

using namespace std;

int ind = 0;                                                                    // глобальная переменная, для работы со строкой из нескольких функций

float strToFloat(string S) {                                                    // функция для перевода числа из строки во флоат для занесения его в стек
  string sNum = "";

  while (isdigit(S[ind]) || (S[ind] == '.')) {
    sNum += S[ind];
    ind++;
  }

  float iNum = stof(sNum, 0);
  return iNum;
}

float binRes(float num1, float num2, char op) {                                 // вычисление с помощью бинарных операторов
  switch (op) {
    case '+': num1 = num1 + num2; break;
    case '-': num1 = num1 - num2; break;
    case '*': num1 = num1 * num2; break;
    case '/': num1 = num1 / num2; break;
    case '^': num1 = pow(num1, num2); break;
  }
//  cout << "binRes " << num1 << endl;
  return num1;
}


int main() {
  map <char, int> opValues;                                                      // объявление словаря с приоритетами операций
  opValues['_'] = -1;
  opValues['('] = 0;
  opValues['+'] = 1;
  opValues['-'] = 1;
  opValues['*'] = 2;
  opValues['/'] = 2;
  opValues['^'] = 3;
  opValues['~'] = 4;

  stack <float> nums;                                                            // стек для хранения чисел
  stack <char> ops;                                                              // стек для хранения операций
  ops.push('_');
  nums.push(0);

  string S;
  cin >> S;
  int len = S.length();

  for (ind; ind <= len; ind++) {
    if (isdigit(S[ind])) {                                                       // заполнение стэка чисел
      nums.push(strToFloat(S));
      ind--;
//      cout << "pushed digit " << nums.top() << endl;
    } else {        
      char op = S[ind];
      if (op == '(') ops.push(op);                                              // обработка открывающей скобки
      else if (ops.top() == '~') {                                              // обработка унарного минуса, так как он требует только один операнд
        float num = nums.top();                                                 // выполняется, если минус а вершине стека, потому что у него наивысший приоритет
        nums.pop();
        nums.push(0-num);
        ops.pop();
        ind--;
      }
      else if (op == '~') ops.push(op);                                         // занесение унарного минуса в стек
      else if (op == ')') {                                                     // обработка закрывающей скобки, пока не встретится открывающая
        while (ops.top() != '(') {
          float num2 = nums.top();
          nums.pop();
          float num1 = nums.top();
          nums.pop();
          nums.push(binRes(num1, num2, ops.top()));
//          cout << "result of "<< num1 << ops.top() << num2 << " = " << nums.top() << endl;
          ops.pop();
        }
//        cout << "closing brackets " << ops.top() << endl;
//        cout << "not ";
        ops.pop();                                                              // удаление открывающей скобки
      }
      else {
      label1:                                                                   // "цикл" для повторного вычисления, если необходимо, например, в выражении (2+6/(2*3)-1)
        if (opValues.find(op)->second <= opValues.find(ops.top())->second){     // проверка приоритетов текущей и предыдущей операций
          float num2 = nums.top();
          nums.pop();
          float num1 = nums.top();
          nums.pop();
          nums.push(binRes(num1, num2, ops.top()));
//          cout << "result of "<< num1 << ops.top() << num2 << " = " << nums.top() << endl;
          ops.pop();
          goto label1;
        }
        ops.push(op);
      }
//      cout << "pushed op " << ops.top() << endl;
    }
  }

  cout << "= " << nums.top() << endl;

  return 0;
}
