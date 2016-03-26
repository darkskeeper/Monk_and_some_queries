#include <iostream>
#include <deque>
using namespace std;

template <typename T>
struct Leaf
{
    T info;
    Leaf<T> * left, * right;
};

template <typename T>
class Heap
{
private:
    Leaf <T> * top;
public:
    Heap ();
    Heap ( Leaf <T> * root );
    ~Heap(){};
    void push ( T & value );
    Leaf <T> * find_value ( Leaf <T> * root, T & value );
    Leaf <T> * pop ( Leaf <T> * newroot,  Leaf <T> * oldroot );
    void insert ( Leaf <T> * root, T & value);
    void swap ( T & value, T & other_value );
    int max();
    void resort ( Leaf <T> * root );
};

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
            pHeap->push(key);
            while (!q.empty() && q.back() > key)
	            q.pop_back();
            q.push_back (key);
            break;
        case 2:
            cin >> key;
            key1 = key;
            pHeap->find_value ( NULL , key );
            if ( key != 0 )
            {
                cout << "-1" << endl;
            }
            else
            {
                for (it = q.begin(); it < q.end(); it++)
                {
                    if ( *it >= key1 )
                    {
                        if (*it == key1)
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

template <typename T>
Heap <T> :: Heap()
{
    top = NULL;
}

template <typename T>
void Heap <T> ::push( T & value)
{
    if ( top == NULL )
    {
        this->top = new Leaf <T> ();
        top->info = value;
        top->left = NULL;
        top->right = NULL;
    }
    else
    {
        insert ( top , value );
    }
}

template <typename T>
void Heap <T> ::insert(Leaf <T> *el, T & value)
{
    if ( el->info < value )
    {
        int temp = el->info;
        el->info = value;
        value = temp;
    }
    if ( el->left == NULL )
    {
        el->left = new Leaf<T> ();
        el->left->info = value;
        el->left->right = NULL;
        el->left->left = NULL;
    }
    else if ( el->right == NULL )
    {
        el->right = new Leaf<T> ();
        el->right->info = value;
        el->right->right = NULL;
        el->right->left = NULL;
    }
    else
    {
        if (rand() & 1 )
        {
            insert (el->left, value);
        }
        else
        {
            insert (el->right, value);
        }
    }
}

template <typename T>
Leaf <T> * Heap <T> ::find_value( Leaf <T> *el, T & value )
{
    if ( el == NULL && top != NULL )
    {
        el = top;
    }
    if ( el->info == value )
    {
        *el = *pop (el->left, el->right);
        value = 0;
        if ( el->info == 0 )
        {
            return NULL;
        }
        return el;
    }
    else if ( el->left != NULL )
    {
        if ( el->left->info >= value )
        {
            el->left = find_value( el->left, value );
        }
    }
    if ( value != 0 )
    {
        if ( el->right != NULL )
        {
            if ( el->right->info >= value )
            {
                el->right = find_value( el->right, value );
            }
        }
    }
    return el;
}

template <typename T>
void Heap <T> ::swap ( T & value, T & other_value )
{
    int temp = value;
    value = other_value;
    other_value = temp;
}

template <typename T>
Leaf <T> * Heap <T>::pop(Leaf <T> *newroot, Leaf <T> *oldroot)
{
    if ( !newroot || !oldroot )
    {
        if ( !newroot && !oldroot )
        {
            newroot = new Leaf <T>();
            return newroot;
        }
        if ( oldroot )
        {
            resort(oldroot);
            return oldroot;
        }
        else
        {
            return newroot;
        }
        //return newroot ? newroot : oldroot;
    }
    if ( oldroot->info > newroot->info )
    {
        swap(oldroot->info, newroot->info);
    }
    if (rand() & 1)
    {
	    newroot->left = pop (newroot->left, oldroot);
    }
    else
    {
        newroot->right = pop (newroot->right, oldroot);
    }
	return newroot;
}

template <typename T>
int Heap<T>::max()
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

template <typename T>
void Heap <T>::resort(Leaf <T> * root)
{
    if ( root->left != NULL )
    {
        if ( root->info < root->left->info)
        {
            swap (root->info, root->left->info);
            resort ( root->left );
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