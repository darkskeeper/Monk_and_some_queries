#include <iostream>
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
    ~Heap();
    void push ( T & value );
    Leaf <T> * pop ( Leaf <T> * root, T & value);
    void insert ( Leaf <T> * root, T & value);
    Leaf <T> * gettop();
    void repush ( Leaf <T> * old_root, Leaf <T> * new_root);
    int min( Leaf <T> * root );
    int max();
    void del_all( Leaf <T> * root );
};

int main()
{
    Heap <int> ob;
    int T;
    cin >> T;
    while ( T-- )
    {
        int key;
        cin >> key;
        switch (key)
        {
        case 1:
            cin >> key;
            ob.push (key);
            break;
        case 2:
            cin >> key;
            ob.pop (ob.gettop() , key);
            break;
        case 3:
            cout << ob.max() << endl;
            break;
        case 4:
            cout << ob.min(ob.gettop()) << endl;
            break;
        }

    }
    system("pause");
    return 0;
}

template <typename T>
Leaf <T> * Heap <T> :: gettop()
{
        return top;
}

template <typename T>
Heap <T> :: Heap()
{
    top = NULL;
}

template <typename T>
Heap <T> :: Heap(Leaf <T> *obj)
{
    this->top = new Leaf <T> ();
    top->info = obj->info;
    top->left = obj->left;
    top->right = obj->right;
}

template <typename T>
Heap <T> :: ~Heap()
{
    del_all(top);
}

template <typename T>
Leaf <T> * Heap <T> :: pop ( Leaf <T> * el , T & a )
{
    if ( el == NULL )
    {
        cout << "-1" << endl;
        return el;
    }
    else if ( el->info == a )
    {
        if ( el->right == NULL && el->left != NULL )
        {
            *el = *el->left;
            return el;
        }
        else if ( el->left == NULL && el->right != NULL )
        {
            *el = *el->right;
            return el;
        }
        else if ( el->left == NULL && el->right == NULL )
        {
            if ( el == top )
            {
                delete top;
                top = NULL;
                return top;
            }
            else
            {
                delete el;
                el = NULL;
                return el;
            }
        }
        else 
        {
            if ( el == top )
            {
                top = top->right;
                repush ( el->left, top );
                delete el;
                return top;
            }
            else
            {
                Heap <T> ob(el);
                Leaf <T> * el_new = ob.gettop();
                *el = *el->right;
                repush ( el_new->left , el );
                el_new = NULL;
                return el;
            }
        }
    }
    else if ( el->left != NULL && a <= el->left->info )
    {
        el->left = pop ( el->left , a );
        if ( el->left == NULL && el->right != NULL)
        {
            int m = min (el->right);
            insert ( el , m );
            el->right = pop ( el->right , m );
        }
        return el;
    }
    else if ( el->right != NULL )
    {
        el->right = pop ( el->right , a );
        return el;
    }
    else
    {
        cout << "-1" << endl;
        return el;
    }
}

template <typename T>
void Heap <T> :: repush ( Leaf <T> * el , Leaf <T> * el_new )
{
    if ( el->left != NULL ) 
    {
        repush ( el->left, el_new );
    }
    if ( el->right != NULL )
    {
        repush (el->right, el_new );
    }
    insert ( el_new, el->info );
    delete el;
}

template <typename T>
void Heap <T> :: push( T & a )
{
    if( top == NULL )
    {
        top = new Leaf <T> ();
        top->info = a;
        top->left = NULL;
        top->right = NULL;
    }
    else
    {
        insert ( top, a );
    }
}

template <typename T>
void Heap <T> :: insert ( Leaf <T> * el, T & a )
{
    int temp;
    if ( el->info < a )
    {
        temp = el->info;
        el->info = a;
    }
    else
    {
        temp = a;
    }
    if ( el->left == NULL )
    {
        el->left = new Leaf <T> ();
        el->left->info = temp;
        el->left->right = NULL;
        el->left->left = NULL;
    }
    else if ( el->left->info >= temp)
    {
        insert ( el->left , temp );
    }
    else if ( el->right == NULL)
    {
        el->right = new Leaf <T> ();
        el->right->info = temp;
        el->right->right = NULL;
        el->right->left = NULL;
    }
    else
    {
        insert (el->right , temp );
    }
}

template <typename T>
int Heap <T> :: min( Leaf <T> * el )
{
    if ( top == NULL )
    {
        return -1;
    }
    if ( el->left != NULL)
    {
        return min(el->left);
    }
    else if ( el->left == NULL && el->right != NULL )
    {
        int b = min ( el->right );
        return ( el->info < b ) ? el->info : b;
    }
    else
    {
        return el->info;
    }
}

template <typename T>
int Heap <T> :: max()
{
    if ( top == NULL )
    {
        return -1;
    }
    else
    {
        return top->info;
    }
}

template <typename T>
void Heap <T> :: del_all( Leaf <T> * el )
{
    if (el->left != NULL)
    {
        del_all (el->left);
    }
    if (el->right != NULL)
    {
        del_all (el->right);
    }
    delete el;
}