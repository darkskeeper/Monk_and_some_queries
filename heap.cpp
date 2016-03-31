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
        while ( el && el->info >= value )
        {
            if ( el->info == value )//если мы нашли элемент с текущим значением
            {
                if ( !el->left && !el->right )//если у найденного элемента нету детей
                {
                    if ( el == top )//если это вершина дерева удаляем её
                    {
                        delete top;
                        top = nullptr;
                    }
                    else//иначе проверяем
                    {
                        if(st.top() && st.top()->right == el)//если указатель на правый элемент вершины стека равен текущему, то
                        {
                            el = st.top();//берём вершину стека и удаляем правый
                            delete el->right;
                            el->right = nullptr;
                        }
                        else//иначе
                        {
                            st.pop();//вытаскиваем указатель на правый элемент нужной вершины из стека
                            el = st.top();//текущий элемент становится вершиной, от которой мы удаляем левый элемент
                            delete el->left;
                            el->left = nullptr;
                        }
                    }//заканчивается условие, когда найденный элемент - не вершина дерева
                }//заканчивается условие, когда у найденного элемента нет детей
                else//если у найденного элемента есть дети
                {
                    Leaf <T> *elnew = el;//запоминаем удаляемый элемент
                    while ( el->left || el->right ) //пока у нас есть правый или левый элемент
                    {
                        st.push(el);//запоминаем текущий
                        if (el->left)//если есть левый - идём влево
                        {
                            el = el->left;
                        }
                        else //иначе вправо
                        {
                            el = el->right;
                        }
                    }//заканчивается цикл, пока у элемента есть хоть 1 ребёнок
                    swap(el->info, elnew->info);//меняем значения у удаляемой вершины и найденного крайнего листа
                    el = st.top();//элемент - родитель листа
                    if (el->left)//если у элемента есть левый лист - удаляем его
                    {
                        delete el->left;
                        el->left = nullptr;
                    }
                    else//иначе правый
                    {
                        delete el->right;
                        el->right = nullptr;
                    }
                    resort(elnew);//пересортировываем после удаления нужного листа
                }//заканчивается условие, когда у найденного элемента есть дети
                return true;//в любом случае возвращаем успех, когда нашли элемент
            }//заканчивается условие, когда мы нашли элемент
            else//если значение вершины больше value, запихиваем в стек текущий элемент, а затем указатель на правый
            {
                st.push(el);
                st.push(el->right);
                el = el->left;
            }//
        }//while( el && el->info >= value)
        while (!st.empty())
        {
            while ( !st.top() )
            {
                el = st.top();
                st.pop();
            }
            while ( !st.empty() && st.top() && st.top()->right == el )
            {
                el=st.top();
                st.pop();
            }
            if (st.empty())
            {
                return false;
            }
            if (st.top())
            {
                break;
            }
        }
        if (st.empty())
        {
            return false;
        }
        el = st.top();
        st.pop();
    }//while (true)
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