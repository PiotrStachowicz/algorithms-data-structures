#include <iostream>

template<typename T>
class bst {
private:
    T value;
    bst *left;
    bst *right;
public:
    bst(T element) : value(element), left(nullptr), right(nullptr) {};

    bst(T value, bst *left, bst *right) : value(value), left(left), right(right) {};

    void insert(T element) {
        if (element < value){
            if(left) left->insert(element);
            else left = new bst(element);
        }
        else {
            if (right) right->insert(element);
            else right = new bst(element);
        }
    }

    bst* search(T element) {
        if(value == element) return this;
        if(element < value) return this->left->search(element);
        return this->right->search(element);
    }

    friend std::ostream& operator<<(std::ostream& os, const bst<T>& root) {
        if(root.left) os << *root.left;
        os << root.value;
        if(root.right) os << *root.right;
        return os;
    }
};


int main() {
    using namespace std;
    bst<int> BST(2);

    BST.insert(3);
    BST.insert(8);
    BST.insert(0);

    cout << BST;

    cout << *BST.search(2);


    return 0;
}

