#include <iostream>
#include <deque>
#include <stack>
using namespace std;

//done
template <typename T>
struct Leaf
{
    T info;
    Leaf<T> * left, * right;
    Leaf(const T & value);
    Leaf();
    ~Leaf();
};

//done
template <typename T>
Leaf <T>::Leaf ()
{
    this->info = NULL;
    this->left = nullptr;
    this->right = nullptr;
}

//done
template <typename T>
Leaf <T>::Leaf (const T & value)
{
    this->info = value;
    this->left = nullptr;
    this->right = nullptr;
}

//done
template <typename T>
Leaf <T>::~Leaf ()
{
    if(left) delete left;
    if(right) delete right;
}

//done?
template <typename T>
class Heap
{
private:
    Leaf <T> * top;
    void resort ( Leaf <T> * root );
    void swap ( T & value, T & other_value );
public:
    Heap ();
    ~Heap();
    void push ( const T & value );
    bool find_value ( const T & value );
    T max () const;
};

//done?
template <typename T>
Heap <T>::~Heap()
{
    delete top;
}

//done?
template <class C>
class smart_pointer
{
    C *m_obj;
public:
    smart_pointer(C *obj) : m_obj(obj) { }
    ~smart_pointer() 
    {
        delete m_obj;
    }
    C* operator->() 
    {
        return m_obj; 
    }
    C& operator* () 
    {
        return *m_obj; 
    }
};

//done?
int main()
{
    deque <int> q;
    deque <int> ::iterator it;
    smart_pointer <Heap <int>> pHeap(new Heap <int>());
    int T, key1;
    cin >> T;
    while ( T-- )
    {
        int key;
        cin >> key;
        switch (key)
        {
        case 1:
            cin >> key;
            key1=0;
            pHeap->push(key);
            while (!q.empty() && q.back() > key)
            {
                key1 = q.back();
                q.pop_back();
            }
            q.push_back (key);
            if (key1!=0)
            {
                q.push_back (key1);
            }
            break;
        case 2:
            cin >> key;
            if (!pHeap->find_value (key))
            {
                cout << "-1" << endl;
            }
            else
            {
                for (it = q.begin(); it < q.end(); it++)
                {
                    if ( *it >= key )
                    {
                        if (*it == key)
                        {
                            q.erase(it);
                        }
                        break;
                    }
                }
            }
            break;
        case 3:
            cout << pHeap->max() << endl;
            break;
        case 4:
            if (!q.empty())
            {
                cout << q.front() << endl;
            }
            else
            {
                cout << "-1";
            }
            break;
        }
    }
    system("pause");
    return 0;
}

//done
template <typename T>
Heap <T> :: Heap()
{
    top = NULL;
}

//done
template <typename T>
void Heap <T> ::push( const T & value)
{
    if ( top == NULL )
    {
        this->top = new Leaf <T> (value);
    }
    else
    {
        int temp = value;
        Leaf <T> *el = top;
        while ( el->left && el->right )
        {
            if ( temp > el->info )
            {
                swap(temp, el->info);
            }
            if (rand()&1)
            {
                el = el->left;
            }
            else
            {
                el = el->right;
            }
        }
        if ( temp > el->info )
        {
            swap(temp, el->info);
        }
        if ( !(el->left) )
        {
            el->left = new Leaf <T> (temp);
        }
        else
        {
            el->right = new Leaf <T> (temp);
        }
    }
}

//done
template <typename T>
bool Heap <T> ::find_value( const T & value )
{
    stack <Leaf<T>*> st;
    Leaf <T> *el;
    if ( top )
    {
        el = top;
    }
    else
    {
        return false;
    }
    while (true)
    {
        while ( el->info >= value )
        {
            if ( el->info == value )
            {
                if ( !el->left && !el->right )
                {
                    if ( el == top )
                    {
                        delete top;
                        top = nullptr;
                        //top = NULL;
                        return true;
                    }
                    el = st.top();
                    st.pop();
                    if ( st.empty() || el->right == st.top() )
                    {
                        delete el->left;
                        el->left = nullptr;
                    }
                    else
                    {
                        delete el->right;
                        el->right = nullptr;
                    }
                }
                else
                {
                    Leaf <T> *eltop = el;
                    while(el->left||el->right)
                    {
                        if( el->left && el->right )
                        {
                            if( rand() & 1 )
                            {
                                st.push (el->right);
                                st.push (el);
                                el = el->left;
                            }
                            else
                            {
                                st.push (el->left);
                                st.push (el);
                                el = el->right;
                            }
                        }
                        else
                        {
                            st.push(el);
                            if (el->left)
                            {
                                el = el->left;
                            }
                            else
                            {
                                el = el->right;
                            }
                        }
                    }
                    swap(el->info, eltop->info);
                    //eltop = nullptr;//????
                    //delete el;
                    el = st.top();
                    st.pop();
                    if ( el->left && el->right )
                    {
                        if ( st.top() == el->left )
                        {
                            delete el->right;
                            el->right = nullptr;
                        }
                        else
                        {
                            delete el->left;
                            el->left = nullptr;
                        }
                    }
                    else
                    {
                        if (el->left)
                        {
                            delete el->left;
                            el->left = nullptr;
                        }
                        else
                        {
                            delete el->right;
                            el->right = nullptr;
                        }
                    }
                    resort(eltop);
                }
                return true;
            }
            else
            {
                if ( el->left )
                {
                    if ( el->right )
                    {
                        st.push( el->right );
                    }
                    st.push(el);
                    el = el->left;
                }
                else if ( el->right )
                {
                    st.push(el);
                    el = el->right;
                }
                else
                {
                    break;
                }
            }
        }
        if (!st.empty())
        {
            el = st.top();
            st.pop();
        }
        else
        {
            return false;
        }
    }
}

//done
template <typename T>
void Heap <T> ::swap ( T & value, T & other_value )
{
    int temp = value;
    value = other_value;
    other_value = temp;
}

//done
template <typename T>
T Heap<T>::max() const
{
    if ( top ==  NULL )
    {
        return -1;
    }
    else
    {
        return top->info;
    }
}

//done
template <typename T>
void Heap <T>::resort(Leaf <T> * root)
{
    if ( root->left != NULL )
    {
        if ( root->info < root->left->info)
        {
            if ( root->right != NULL && root->right->info > root->left->info )
            {
                swap(root->info, root->right->info);
                resort (root->right);
                return ;
            }
            else
            {
                swap (root->info, root->left->info);
                resort ( root->left );
                return ;
            }
        }
    }
    if ( root->right != NULL )
    {
        if ( root->info < root->right->info)
        {
            swap (root->info, root->right->info);
            resort ( root->right );
        }
    }
}