#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "D:\university\shujujiegou\DS2024\Vector\Vector.h"
#include <algorithm>
#include <chrono>
using namespace std;
// 复数类定义
class Complex
{
public:
double real;
double imag;
// 运算符重载
Complex(double r = 0, double i = 0) : real(r), imag(i) {}
// 重载 <= 操作符
bool operator<=(const Complex &other) const
{return (x <= other.x && y <= other.y);}
// 重载 > 操作符
bool operator>(const Complex &other) const
{return (x > other.x || (x == other.x && y > other.y));}
double modulus() const
{return sqrt(real * real + imag * imag);}
// 定义小于运算符，用于比较复数模（顺序）
bool operator<(const Complex &other) const
{return modulus() < other.modulus() || (modulus() == other.modulus() && real < other.real);}
// 重载 != 运算符
double x;
double y;
bool operator!=(const Complex &other) const
{return (x != other.x || y != other.y);}
// 重载==
bool operator==(const Complex &other) const
{return real == other.real && imag == other.imag;}
friend ostream &operator<<(ostream &os, const Complex &c)
{os << "(" << c.real << ", " << c.imag << ")";return os;}
};
// 复数模顺序排序
void Sort1(Vector<Complex> &array)
{
int n = array.size();
for (int i = 1; i < n; ++i)
{
Complex key = array[i];
int j = i - 1;
// 按复数的模顺序排序，模相等时按实部排序
while (j >= 0 && key < array[j])
{array[j + 1] = array[j];j = j - 1;}
array[j + 1] = key;
}
}
// 区间查找算法
Vector<Complex> find(const Vector<Complex> &array, double m1, double m2)
{
Vector<Complex> result;
for (int i = 0; i < array.size(); ++i)
{
double modulus = array[i].modulus();
if (modulus >= m1 && modulus < m2)
{result.insert(array[i]);}
}
return result;
}
// 输出函数
void print(Complex &output)
{ cout << output.real << "+" << output.imag << "i  ";}

// 随机生成乱序复数向量
Vector<Complex> generateRandomVector(int n)
{
Vector<Complex> vec;
srand(time(0));
for (int i = 0; i < n; ++i)
{
double real = rand() % 10; // 实部在 0 到 9 之间
double imag = rand() % 10; // 虚部在 0 到 9 之间
vec.insert(Complex(real, imag)); // 插入到最终的向量中
}
return vec;
}
//生成顺序复数向量
Vector<Complex> generateOrderedVector(int n)
{
Vector<Complex> vec;
for (int i = 0; i < n; ++i)
{   
    double j = static_cast<double>(i);
    vec.insert(j, j);
    }
return vec;
}
// 生成逆序复数向量
Vector<Complex> generateReverseOrderedVector(int n)
{
Vector<Complex> vec;
for (int i = n; i > 0; --i)
{   double j = static_cast<double>(i);
    vec.insert(j, j);
    }
return vec;
}

// 记录排序时间并输出结果
void measureSortingTime(const string &sortType, Vector<Complex> vec)
{
clock_t start = clock();
if (sortType == "bubble")
{ vec.bubbleSort(0, vec.size()-1);}
else if (sortType == "merge")
{vec.mergeSort(0, vec.size()-1);}
clock_t end = clock();
double duration = (double(end - start) / CLOCKS_PER_SEC) * 1000000; // 转换为微秒
// 输出排序结果和时间
cout << sortType << " 时间: " << duration << " us" << endl;
}



int main()
{

//1.生成一个无序复数向量
int n = 1000;
Vector<Complex> vec = generateRandomVector(n);
cout << "无序复数向量为:\n";
vec.traverse(print);
cout << endl;
//测试置乱:
vec.unsort(0,vec.size() - 1);
cout << "置乱后的复数向量为：\n";
vec.traverse(print);
cout << endl;
//测试查找
Complex search(5,4);
Rank findnumber = vec.find(search);
if(findnumber != -1)
{cout << "找到元素" << search << "在索引" << findnumber << endl;}
else
{cout << "未找到元素" << search << endl;}
//测试插入
vec.insert(2,Complex(5,4));
cout << "插入元素(5,4)后的向量为：\n";
vec.traverse(print);
cout << endl;
//测试删除
vec.remove(2);//删除插入的元素
cout << "删除元素后的向量为：\n";
vec.traverse(print);
cout << endl;
//唯一化向量
vec.deduplicate();
cout << "唯一化后的向量为：\n";
vec.traverse(print);
cout << endl;

//排序向量
Sort1(vec);
cout << "排序后的向量为：\n";
vec.traverse(print);
cout << endl;

//测试区间查找
double m1 = 1.0;
double m2 = 5.0;
Vector<Complex> findarray = find(vec,m1,m2);
cout << "在区间[" << m1 << "," << m2 << ")的元素为\n";
findarray.traverse(print);
cout << endl;

//测试顺序向量
cout << "顺序排序时间为："<< endl;
Vector<Complex> clock_vec = generateOrderedVector(n);
measureSortingTime("bubble",clock_vec);
measureSortingTime("merge",clock_vec);

// 测试无序向量
cout << "乱序排序时间为：\n";
Vector<Complex> randomvec = generateRandomVector(n);
measureSortingTime("bubble",randomvec);
measureSortingTime("merge",randomvec);



return 0;

}