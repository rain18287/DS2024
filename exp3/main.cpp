#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

// 位图类 Bitmap
typedef int Rank;
class Bitmap {
private:
    unsigned char* M;  
    Rank N, _sz;  

protected:
    
    void init(Rank n) 
    {
        M = new unsigned char[N = (n + 7) / 8];  
        memset(M, 0, N);  
        _sz = 0;
    }

public:
    Bitmap(Rank n = 8) { init(n); } 
    ~Bitmap() { delete[] M; M = nullptr; _sz = 0; }  
    Rank size() { return _sz; }  

    void set(Rank k) 
    { 
        expand(k);  
        _sz++; 
        M[k >> 3] |= (0x80 >> (k & 0x07));  
    }

    void clear(Rank k) 
    { 
        expand(k); 
        _sz--; 
        M[k >> 3] &= ~(0x80 >> (k & 0x07));  
    }

    bool test(Rank k) 
    { 
        expand(k); 
        return M[k >> 3] & (0x80 >> (k & 0x07)); 
    }

    void expand(Rank k) 
    {
        if (k < 8 * N) return;  
        Rank oldN = N;
        unsigned char* oldM = M;
        init(2 * k);  
        memcpy(M, oldM, oldN);  
        delete[] oldM;  
    }
};

// Huffman树节点类定义
class BinTreeNode {
public:
    char data;  
    int frequency;  
    BinTreeNode* left;  
    BinTreeNode* right;  

    BinTreeNode(char data, int frequency) 
        : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// 比较器用于优先队列，频率小的节点优先
struct Compare {
    bool operator()(BinTreeNode* a, BinTreeNode* b) 
    {
        return a->frequency > b->frequency;
    }
};

// Huffman树类
class HuffTree {
private:
    BinTreeNode* root;  

public:
    // 通过给定文本构造 Huffman 树
    HuffTree(const string& text) 
    {
        priority_queue<BinTreeNode*, vector<BinTreeNode*>, Compare> pq;  
        unordered_map<char, int> freq;  

        for (char currentChar : text) 
        {  
            freq[currentChar]++;
        }

        for (auto it = freq.begin(); it != freq.end(); ++it) 
        {  
            pq.push(new BinTreeNode(it->first, it->second));
        }

        while (pq.size() > 1) 
        {  
            BinTreeNode* left = pq.top(); 
            pq.pop();
            BinTreeNode* right = pq.top(); 
            pq.pop();
            BinTreeNode* node = new BinTreeNode('\0', left->frequency + right->frequency);
            node->left = left;
            node->right = right;
            pq.push(node);
        }
        root = pq.top();  
    }

    // 递归生成Huffman编码
    void generateCodes(unordered_map<char, string>& huffCodes, BinTreeNode* node, string code) 
    {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) 
        {  
            huffCodes[node->data] = code;
            return;
        }
        generateCodes(huffCodes, node->left, code + "0");
        generateCodes(huffCodes, node->right, code + "1");
    }

    // 返回编码表
    unordered_map<char, string> getHuffmanCodes() {
        unordered_map<char, string> huffCodes;
        generateCodes(huffCodes, root, "");
        return huffCodes;
    }
};

// Huffman编码功能类
class HuffmanEncoding 
{
private:
    HuffTree* huffTree;
    unordered_map<char, string> huffCodes;

public:
    HuffmanEncoding(const string& text) 
    {
        huffTree = new HuffTree(text); 
        huffCodes = huffTree->getHuffmanCodes();  
    }

    string encode(const string& text) 
    {  
        string encodedString = "";
        for (char currentChar : text) 
        {
            encodedString += huffCodes[currentChar];
        }
        return encodedString;
    }

    void printHuffmanCodes() 
    {  
        for (const auto& it : huffCodes) 
        {
            cout << it.first << " -> " << it.second << endl;
        }
    }
};

// 从文本中提取单词
void extractWordsFromText(const string& text, set<string>& words) 
{
    stringstream ss(text);
    string word;
    while (ss >> word) 
    {
        words.insert(word);
    }
}

int main() 
{
    string filePath = "I_have_a_dream.txt";  
    ifstream file(filePath);


    stringstream buffer;
    buffer << file.rdbuf();  
    string text = buffer.str();
    file.close();

    set<string> words;
    extractWordsFromText(text, words);  // 提取所有单词并存储在集合中

    // 对单词 "dream" 进行 Huffman 编码
    string predefinedWord = "dream";
    HuffmanEncoding predefinedHuffman(predefinedWord);

    cout << "在'dream'这个单词中每个字母的Huffman编码为:" << endl;
    predefinedHuffman.printHuffmanCodes();

    string encodedPredefinedWord = predefinedHuffman.encode(predefinedWord);
    cout << "编码后 'dream': " << encodedPredefinedWord << endl << endl;

    cout << "请输入你想进行编码的单词: ";
    string selectedWord;
    cin >> selectedWord;

    if (words.find(selectedWord) == words.end()) 
    {  
        cout << "无法再文件中找到此单词!" << endl;
        return 1;
    }

    HuffmanEncoding huffman(selectedWord);  

    cout << "此单词中每个字母的Huffman编码为:" << endl;
    huffman.printHuffmanCodes();  // 打印每个字符的编码

    string encoded = huffman.encode(selectedWord);  // 对单词进行编码
    cout << "编码后的单词为: " << encoded << endl;

    return 0;
}

