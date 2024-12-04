// 3.1列表节点模板类
typedef int Rank;              // 秩
#define ListNodePosi(T) ListNode<T> *    // 列表节点位置
template <typename T>
struct  ListNode   // 列表节点类模板(以双向链表形式表现)
{
    T data;                 // 数值
    ListNodePosi(T) pred;   // 前驱
    ListNodePosi(T) succ;   // 后继
    //构造函数
    ListNode(){}//针对header和trailer的构造
    ListNode(T e, ListNodePosi(T) p = NULL,ListNodePosi(T) s = NULL)
        : data(e),pred(p),succ(s){}//默认构造器
    //操作接口
    ListNodePosi(T) insertAsPred(T const &e);// 紧靠当前节点之前插入新节点
    ListNodePosi(T) insertAsSucc(T const &e); // 紧靠当前节点之后插入新节点
};


//1.类型定义与宏定义
//typedef int Rank;: 这里创建了一个类型别名 Rank，通常用于表示节点的位置、等级或优先级等。
//#define ListNodePosi(T) ListNode<T> *: 定义了一个宏，用于代表指向 ListNode<T> 的指针。这个宏提高了代码的可读性，可以让我们在后面的代码中更方便地使用 ListNode<T>*。

//2. ListNode 结构体模板定义
//template <typename T>: 使用模板来定义 ListNode 结构体，以支持不同类型的数据。这意味着你可以创建存储任何类型的值的节点，比如 int, float, std::string 等。
//struct ListNode: 声明了一个 ListNode 结构体，代表链表中的一个节点。

//3. 节点成员变量
//T data;: 存储节点的数据部分，类型为 T，即根据模板类型决定。
//ListNodePosi(T) pred;: 指向当前节点前驱的指针。使用之前定义的宏，表示这是一个 ListNode<T>* 类型的指针。
//ListNodePosi(T) succ;: 指向当前节点后继的指针，表示这个节点的下一个节点同样是 ListNode<T>* 类型。

//4. 构造函数
//ListNode() {}: 默认构造函数，适用于创建头结点（header）和尾节点（trailer），通常不需要具体的数据和指针。
//ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL): 带参数的构造函数，允许初始化节点的 data、pred 和 succ。其中：
//T e 是节点存储的数据。
//ListNodePosi(T) p = NULL 是前驱节点指针，默认为 NULL（即没有前驱）。
//ListNodePosi(T) s = NULL 是后继节点指针，默认为 NULL（即没有后继）。
//使用初始化列表将这些参数值赋给对应的成员变量。

//5. 操作接口
//ListNodePosi(T) insertAsPred(T const &e);: 方法声明，用于在当前节点之前插入一个新节点，参数为插入节点的数据 e。返回值是新插入节点的指针。
//ListNodePosi(T) insertAsSucc(T const &e);: 方法声明，用于在当前节点之后插入一个新节点，参数为插入节点的数据 e。同样返回新插入节点的指针。