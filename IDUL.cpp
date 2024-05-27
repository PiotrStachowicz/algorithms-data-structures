#include <iostream>
#include <climits>
#include <cstdint>


class AVL_TREE
{
public:
    static AVL_TREE* root;
    static bool deletion;

    AVL_TREE* left;
    AVL_TREE* right;
    int64_t val;
    int32_t height;


    explicit AVL_TREE(int64_t value) : left(nullptr), right(nullptr), val(value), height(1) {}


    void update()
    {
        int32_t lh = 0;
        int32_t rh = 0;

        if (left) lh = left->height;

        if (right) rh = right->height;

        height = std::max(lh, rh) + 1;
    }


    AVL_TREE* rebalance()
    {
        if ((left && right && right->height - left->height < -1) || (left && !right && left->height > 1))
        {
            return rotate_right(this, left);
        }

        else if ((left && right && right->height - left->height > 1) || (!left && right && right->height > 1))
        {
            return rotate_left(this, right);
        }

        update();

        return this;
    }


    [[nodiscard]] int64_t find_min() const
    {
        if (left) return std::min(val, left->find_min());

        return val;
    }


    [[nodiscard]] int64_t upper(int64_t x) const
    {
        if (val == x) return val;

        if (val > x)
        {
            if (left) return std::min(val, left->upper(x));
            return val;
        }
        else if (right)
        {
           return right->upper(x);
        }

        return LONG_MAX;
    }


    [[nodiscard]] int64_t lower(int64_t x) const
    {
        if (val == x) return val;

        if (val < x)
        {
            if (right) return std::max(val, right->lower(x));
            return val;
        }
        else if (left)
        {
            return left->lower(x);
        }

        return LONG_MIN;
    }


    static AVL_TREE* rotate_left(AVL_TREE* X, AVL_TREE* Z)
    {
        AVL_TREE* Beta = Z->left;

        Z->left = X;
        if (X) X->right = Beta;


        if (X) X->update();
        Z->update();

        return Z;
    }


    static AVL_TREE* rotate_right(AVL_TREE* X, AVL_TREE* Z)
    {
        AVL_TREE* Beta = Z->right;

        Z->right = X;
        if (X) X->left = Beta;

        if (X) X->update();
        Z->update();

        return Z;
    }


    AVL_TREE* insert_(int64_t x)
    {
        if (val == x) return this;

        if (x < val)
        {
            if (left) left = left->insert_(x);

            else left = new AVL_TREE(x);
        }

        else
        {
            if (right) right = right->insert_(x);

            else right = new AVL_TREE(x);
        }

        update();

        return rebalance();
    }


    AVL_TREE* delete_(int64_t x)
    {
        if (x == val)
        {
            AVL_TREE::deletion = true;

            if (left && right)
            {
                int64_t min = right->find_min();

                val = min;

                right = right->delete_(min);
            }
            else if (!left && !right)
            {
                delete this;

                return nullptr;
            }
            else if (left)
            {
                AVL_TREE* l = left;

                delete this;

                return l;
            }
            else
            {
                AVL_TREE* r = right;

                delete this;

                return r;
            }
        }
        else
        {
            if (x < val)
            {
                if (left) left = left->delete_(x);
            }
            else if (right)
            {
                if (right) right = right->delete_(x);
            }
        }

        update();

        return rebalance();
    }
};


void INSERT_TASK(int64_t x)
{

    if (AVL_TREE::root)
    {
        AVL_TREE::root = AVL_TREE::root->insert_(x);
    }

    else AVL_TREE::root = new AVL_TREE(x);
}


void DELETE_TASK(int64_t x)
{
    AVL_TREE::deletion = false;

    if (AVL_TREE::root)
    {
        AVL_TREE::root = AVL_TREE::root->delete_(x);
    }

    if (AVL_TREE::deletion) std::cout << "OK\n";

    else std::cout << "BRAK\n";
}


void UPPER_TASK(int64_t x)
{
    if (!AVL_TREE::root)
    {
        std::cout << "BRAK\n";
        return;
    }

    int64_t result = AVL_TREE::root->upper(x);

    if (result != LONG_MAX) std::cout << result << "\n";

    else std::cout << "BRAK\n";
}


void LOWER_TASK(int64_t x)
{
    if (!AVL_TREE::root)
    {
        std::cout << "BRAK\n";
        return;
    }

    int64_t result = AVL_TREE::root->lower(x);

    if (result != LONG_MIN) std::cout << result << "\n";

    else std::cout << "BRAK\n";
}


bool AVL_TREE::deletion = false;
AVL_TREE* AVL_TREE::root = nullptr;


int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int64_t N;
    std::cin >> N;

    for (int64_t i = 0; i < N; ++i)
    {
        char operation;
        int64_t x;

        std::cin >> operation >> x;

        switch (operation)
        {
            case 'I':
                INSERT_TASK(x);
                break;

            case 'D':
                DELETE_TASK(x);
                break;

            case 'L':
                LOWER_TASK(x);
                break;

            case 'U':
                UPPER_TASK(x);
                break;

            default:
                break;
        }
    }

    return 0;
}