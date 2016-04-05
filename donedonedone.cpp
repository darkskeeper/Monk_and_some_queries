#include <stack>
#include <iostream>
using namespace std;

template <typename T>
struct Leaf
{
    T info;
    Leaf <T> *left, *right;
    Leaf();
    Leaf(const T & value);
    ~Leaf();
};

template <typename T>
Leaf <T>::Leaf()
{
    this->info = NULL;
    this->right = nullptr;
    this->left = nullptr;
}

template <typename T>
Leaf <T>::Leaf(const T & value)
{
    this->info = value;
    this->right = nullptr;
    this->left = nullptr;
}

template <typename T>
Leaf <T>::~Leaf()
{
    if (left) delete left;
    if (right) delete right;
}

template <typename T>
class Tree
{
private:
    Leaf <T> * top;
    void swap(T & value, T & other_value);
    void pop(Leaf <T> * root);
    void resort(Leaf <T> * root);
public:
    Tree();
    ~Tree();
    void push(const T & value);
    bool find_value(const T & value);
    T max() const;
    T min() const;
};

int main()
{
    Tree <int> ob;
    int T, key;
    cin >> T;
    while (T--)
    {
        cin >> key;
        switch (key)
        {
        case 1:
            cin >> key;
            ob.push(key);
            break;
        case 2:
            cin >> key;
            if (!ob.find_value(key))
            {
                cout << "-1" << endl;
            }
            break;
        case 3:
            cout << ob.max() << endl;
            break;
        case 4:
            cout << ob.min() << endl;
            break;
        }
    }
    return 0;
}

template <typename T>
Tree <T>::Tree()
{
    top = NULL;
}

template <typename T>
Tree <T>::~Tree()
{
    delete top;
}

template <typename T>
void Tree <T>::push(const T & value)
{
    if (top == NULL)
    {
        top = new Leaf<T>(value);
    }
    else
    {
        Leaf <T> * el = top;
        while (true)
        {
            if (value <= el->info)
            {
                if (el->left == NULL)
                {
                    el->left = new Leaf<T>(value);
                    break;
                }
                el = el->left;
            }
            else
            {
                if (el->right == NULL)
                {
                    el->right = new Leaf<T>(value);
                    break;
                }
                el = el->right;
            }
        }
    }
}

template <typename T>
void Tree <T> ::swap(T & value, T & other_value)
{
    int temp = value;
    value = other_value;
    other_value = temp;
}

template <typename T>
T Tree<T>::max() const
{
    if (!top)
    {
        return -1;
    }
    else
    {
        Leaf <T> * el = top;
        while (el->right != NULL)
        {
            el = el->right;
        }
        return el->info;
    }
}

template <typename T>
T Tree<T>::min() const
{
    if (!top)
    {
        return -1;
    }
    else
    {
        Leaf <T> * el = top;
        while (el->left != NULL)
        {
            el = el->left;
        }
        return el->info;
    }
}

template <typename T>
bool Tree<T>::find_value(const T & value)
{
    if (!top)
    {
        return false;
    }
    else
    {
        stack <Leaf<T> *> st;
        Leaf <T> * el = top;
        while (el != NULL)
        {
            if (value == el->info)
            {
                if (!el->left && !el->right)
                {
                    if (el == top)
                    {
                        delete top;
                        top = nullptr;
                    }
                    else
                    {
                        if (st.top()->left == el)
                        {
                            el = st.top();
                            delete el->left;
                            el->left = nullptr;
                        }
                        else
                        {
                            el = st.top();
                            delete el->right;
                            el->right = nullptr;
                        }
                    }
                }
                else
                {
                    pop(el);
                    if ( (el->left && el->info < el->left->info) || (el->right && el->info > el->right->info) )
                    {
                        resort(el);
                    }
                }
                return true;
            }
            else
            {
                st.push(el);
                if (value > el->info)
                {
                    el = el->right;
                }
                else
                {
                    el = el->left;
                }
            }
        }
        return false;
    }
}

template <typename T>
void Tree<T>::pop(Leaf <T> * el)
{
    Leaf <T> *eldel = el, *el_before_del = el, *el_prev_swap = el;
    if (eldel->right)
    {
        while (eldel->right)
        {
            el_before_del = eldel;
            eldel = eldel->right;
            while (eldel->left)
            {
                el_before_del = eldel;
                eldel = eldel->left;
            }
            swap(el_prev_swap->info, eldel->info);
            el_prev_swap = eldel;
        }
        if (eldel == el_before_del->left)
        {
            delete el_before_del->left;
            el_before_del->left = nullptr;
        }
        else
        {
            delete el_before_del->right;
            el_before_del->right = nullptr;
        }
    }
    else
    {
        while (eldel->left)
        {
            el_before_del = eldel;
            eldel = eldel->left;
            while (eldel->right)
            {
                el_before_del = eldel;
                eldel = eldel->right;
            }
            swap(el_prev_swap->info, eldel->info);
            el_prev_swap = eldel;
        }
        if (eldel == el_before_del->left)
        {
            delete el_before_del->left;
            el_before_del->left = nullptr;
        }
        else
        {
            delete el_before_del->right;
            el_before_del->right = nullptr;
        }
    }
}

template <typename T>
void Tree <T>::resort(Leaf <T> * root)
{
    while (root->left)
    {
        if (root->info < root->left->info)
        {
            swap(root->info, root->left->info);
            root = root->left;
        }
        else
        {
            break;
        }
    }
    while (root->right)
    {
        if (root->info > root->right->info)
        {
            swap(root->info, root->right->info);
            root = root->right;
        }
        else
        {
            break;
        }
    }
}