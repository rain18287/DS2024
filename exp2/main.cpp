#include <iostream>
#include "Stack.cpp"
#include <string>
#include <cmath>
//#include <cstdlib>
#include <ctime>
//#include <algorithm>
//#include <limits>
#include <vector>

using namespace std;

// 优先级定义
enum Operator {
    ADD = '+', SUB = '-', MUL = '*', DIV = '/', POW = '^', FAC = '!', L_P = '(', R_P = ')', EOE = '\0'
};

// 优先级表
const char pri[9][9] = {
    // | + | - | * | / | ^ | ! | ( | ) | \0
    { '>', '>', '<', '<', '<', '<', '<', '>', '>' }, // +
    { '>', '>', '<', '<', '<', '<', '<', '>', '>' }, // -
    { '>', '>', '>', '>', '<', '<', '<', '>', '>' }, // *
    { '>', '>', '>', '>', '<', '<', '<', '>', '>' }, // /
    { '>', '>', '>', '>', '>', '<', '<', '>', '>' }, // ^
    { '>', '>', '>', '>', '>', '>', ' ', '>', '>' }, // !
    { '<', '<', '<', '<', '<', '<', '<', '=', ' ' }, // (
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, // )
    { '<', '<', '<', '<', '<', '<', '<', ' ', '=' }  // \0
};

// 计算器类
class Calculator {
private:
    Stack<double> numStack; // 数字栈
    Stack<char> opStack;    // 运算符栈

    // 计算两个数的结果
    double evaluate(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/':
                if (b == 0) throw runtime_error("Division by zero");
                return a / b;
            case '^': return pow(a, b);
            case '!': return tgamma(a + 1);
            default: throw runtime_error("Invalid operator");
        }
    }

    // 运算符优先级
    int precedence(char op) {
        switch (op) {
            case '+': case '-': return 1;
            case '*': case '/': return 2;
            case '^': return 3;
            case '!': return 4;
            default: return 0;
        }
    }

    // 判断是否为运算符
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '!';
    }

    // 判断是否为数字
    bool isNumber(char c) {
        return isdigit(c) || c == '.';
    }

    // 判断是否为函数
    bool isFunction(const string& func) {
        return func == "sin" || func == "cos" || func == "tan" || func == "log" || func == "exp";
    }

    // 处理函数的计算
    double evaluateFunction(const string& func, double value) {
        if (func == "sin") return sin(value * M_PI / 180.0);
        if (func == "cos") return cos(value * M_PI / 180.0);
        if (func == "tan") return tan(value * M_PI / 180.0);
        if (func == "log") return log(value);
        if (func == "exp") return exp(value);
        throw runtime_error("Invalid function");
    }

public:
    // 计算表达式
    double calculate(const string& expression) {
        numStack = Stack<double>();
        opStack = Stack<char>();
        string numBuffer;
        string funcBuffer;

        for (size_t i = 0; i < expression.size(); ++i) {
            char c = expression[i];

            if (isspace(c)) continue; // 忽略空格
            if (isNumber(c)) {
                numBuffer += c; // 记录数字
            } else {
                if (!numBuffer.empty()) {
                    numStack.push(stod(numBuffer)); // 将数字压入栈
                    numBuffer.clear();
                }

                if (isOperator(c)) {
                    while (!opStack.isEmpty() && precedence(opStack.top()) >= precedence(c)) {
                        double b = numStack.top(); numStack.pop();
                        double a = numStack.top(); numStack.pop();
                        char op = opStack.top(); opStack.pop();
                        numStack.push(evaluate(a, b, op));
                    }
                    opStack.push(c);
                } else if (c == '(') {
                    opStack.push(c);
                } else if (c == ')') {
                    while (!opStack.isEmpty() && opStack.top() != '(') {
                        double b = numStack.top(); numStack.pop();
                        double a = numStack.top(); numStack.pop();
                        char op = opStack.top(); opStack.pop();
                        numStack.push(evaluate(a, b, op));
                    }
                    opStack.pop(); // 弹出 '('
                } else {
                    // 处理函数
                    funcBuffer += c;
                    if (isFunction(funcBuffer)) {
                        // 函数结束，期待一个 '('
                        if (i + 1 < expression.size() && expression[i + 1] == '(') {
                            // 查找对应的 ')'
                            size_t endPos = expression.find(')', i + 2);
                            if (endPos == string::npos) {
                                throw runtime_error("Mismatched parentheses in function call");
                            }
                            double arg = stod(expression.substr(i + 2, endPos - (i + 2)));
                            numStack.push(evaluateFunction(funcBuffer, arg));
                            i = endPos; // 移动到 ')' 之后
                            funcBuffer.clear(); // 清空函数缓存
                        }
                    } else {
                        // 如果不是函数，继续构建字符串
                        if (funcBuffer.length() > 0) {
                            funcBuffer.clear(); // 清空缓存
                        }
                    }
                }
            }
        }

        if (!numBuffer.empty()) {
            numStack.push(stod(numBuffer)); // 处理最后一个数字
        }

        while (!opStack.isEmpty()) {
            double b = numStack.top(); numStack.pop();
            double a = numStack.top(); numStack.pop();
            char op = opStack.top(); opStack.pop();
            numStack.push(evaluate(a, b, op));
        }

        return numStack.top();
    }
        // 扩展：支持三角函数
    double three(const string &expression) {
        size_t start = expression.find('(');
        size_t end = expression.find(')');
        double angle = stod(expression.substr(start + 1, end - start - 1));
        return sin(angle * M_PI / 180.0); // 将角度转换为弧度
    }
};

// 计算柱状图中最大矩形面积（分治法）
int largestAreaUtil(const vector<int>& heights, int left, int right) {
    if (left > right) return 0;
    if (left == right) return heights[left];

    int minIndex = left;
    for (int i = left; i <= right; ++i) {
        if (heights[i] < heights[minIndex]) {
            minIndex = i;
        }
    }

    int areaWithMinHeight = heights[minIndex] * (right - left + 1);
    int areaLeft = largestAreaUtil(heights, left, minIndex - 1);
    int areaRight = largestAreaUtil(heights, minIndex + 1, right);

    return max(areaWithMinHeight, max(areaLeft, areaRight));
}

int largestArea(const vector<int>& heights) {
    return largestAreaUtil(heights, 0, heights.size() - 1);
}

// 随机生成测试数据
void generateTest(int numTests) {
    srand(time(0)); // 初始化随机数种子
    for (int i = 0; i < numTests; ++i) {
        int length = rand() % 20 + 1; // 随机生成柱状图长度 (1 到 20)
        vector<int> heights(length);
        cout << "输入" << i + 1 << ": [ ";
        for (int j = 0; j < length; ++j) {
            heights[j] = rand() % 20; // 随机生成柱子高度 (0 到 20)
            cout << heights[j] << " ";
        }
        cout << "]" << endl;
        int maxArea = largestArea(heights);
        cout << "输出: " << maxArea << endl << endl;
    }
}

// 主函数
int main() {
    // 字符串计算器示例测试
    Calculator calc;
    string A1 = "4 + 3 * 2 - 8 / 2 + 3.2";
    cout << "数字运算: " << A1 << " = " << calc.calculate(A1) << endl << endl;

    string A2 = "( 3 + 4 ) * 5 - 24 / 6";
    cout << "数字运算: " << A2 << " = " << calc.calculate(A2) << endl << endl;

    string A3 = "sin(45)";
    cout << "三角函数: " << A3 << " = " << calc.three(A3) << endl << endl;

    // 测试柱状图最大矩形面积
    vector<int> B1 = {2, 1, 5, 6, 2, 3};
    vector<int> B2 = {2, 4};
    cout << "输入: " << "[2, 1, 5, 6, 2, 3]" << endl;
    cout << "输出: " << largestArea(B1) << endl << endl;

    cout << "输入: " << "[2, 4]" << endl;
    cout << "输出: " << largestArea(B2) << endl << endl;

    // 随机生成 10 组测试数据
    generateTest(10);

    return 0;
}