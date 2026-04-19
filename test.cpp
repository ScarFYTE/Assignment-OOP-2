#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;


struct Node{
    int data;
    Node* right;
    Node* left;

    Node(int val){
        data = val;
        right = nullptr;
        left = nullptr;
    }

    Node(int val, Node* right, Node* left){
        data = val;
        this->right = right;
        this->left = left;
    }
};


void SelectionSort(vector <int> & v){
    for (int i = 0; i < v.size() -1;i++){
        int min = i;
        
        for (int j = i + 1; j < v.size(); j++){
            if(v[j]<v[min])
                min = j;
        }
        swap(v[i], v[min]);
    }
}   

void insertionsort(vector<int>& v){
    for (int i = 1; i < v.size();i++){
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j]>key){
            v[j + 1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
}

void binaryInsertionSort(vector<int>& v){
    for (int i = 1; i < v.size(); i++){
        int key = v[i];
        auto it = lower_bound(v.begin(), v.begin() + i, key, [](int a, int b){
            return a < b;
        });
        int pos = distance(v.begin(), it);
        for (int j = i; j > pos; j--){
            v[j] = v[j - 1];
        }
        v[pos] = key;
    }
}

int main(){
    Node* p = new Node (10);
    Node* q = new Node (20);
    Node* r = new Node (30);

    p->right = q;
    q->left = p;
    q->right = r;
    r->left = q;

    Node* temp = p;

    p=q->right;

    q->left = p;
    temp->right->left = r;

    
}