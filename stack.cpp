#include <iostream>


template<typename T>
class stack {
private:
    size_t stack_size;
    T value;
    stack *next;

public:
    stack() : stack_size(0), value(T(0)), next(nullptr) {};

    stack(size_t size, T value, stack *next) : stack_size(size), value(value), next(next) {};

    void push(T element) {
        auto *new_stack = new stack(++stack_size, value, this->next);
        this->value = element;
        this->next = new_stack;
    }

    void pop() {
        if (next) {
            stack *temp = next;
            value = next->value;
            next = next->next;
            delete temp;
            stack_size--;
        }
    }

    T top() {
        return value;
    }

    size_t size() {
        return stack_size;
    }
};


int main() {
    using namespace std;
    stack<int> stack{};

    stack.push(2);
    stack.push(1);

    cout << stack.top();
    stack.pop();
    cout << stack.top();
    cout << stack.size();

    return 0;
}
