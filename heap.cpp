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
            if ( el->info == value )//���� �� ����� ������� � ������� ���������
            {
                if ( !el->left && !el->right )//���� � ���������� �������� ���� �����
                {
                    if ( el == top )//���� ��� ������� ������ ������� �
                    {
                        delete top;
                        top = nullptr;
                    }
                    else//����� ���������
                    {
                        if(st.top() && st.top()->right == el)//���� ��������� �� ������ ������� ������� ����� ����� ��������, ��
                        {
                            el = st.top();//���� ������� ����� � ������� ������
                            delete el->right;
                            el->right = nullptr;
                        }
                        else//�����
                        {
                            st.pop();//����������� ��������� �� ������ ������� ������ ������� �� �����
                            el = st.top();//������� ������� ���������� ��������, �� ������� �� ������� ����� �������
                            delete el->left;
                            el->left = nullptr;
                        }
                    }//������������� �������, ����� ��������� ������� - �� ������� ������
                }//������������� �������, ����� � ���������� �������� ��� �����
                else//���� � ���������� �������� ���� ����
                {
                    Leaf <T> *elnew = el;//���������� ��������� �������
                    while ( el->left || el->right ) //���� � ��� ���� ������ ��� ����� �������
                    {
                        st.push(el);//���������� �������
                        if (el->left)//���� ���� ����� - ��� �����
                        {
                            el = el->left;
                        }
                        else //����� ������
                        {
                            el = el->right;
                        }
                    }//������������� ����, ���� � �������� ���� ���� 1 ������
                    swap(el->info, elnew->info);//������ �������� � ��������� ������� � ���������� �������� �����
                    el = st.top();//������� - �������� �����
                    if (el->left)//���� � �������� ���� ����� ���� - ������� ���
                    {
                        delete el->left;
                        el->left = nullptr;
                    }
                    else//����� ������
                    {
                        delete el->right;
                        el->right = nullptr;
                    }
                    resort(elnew);//����������������� ����� �������� ������� �����
                }//������������� �������, ����� � ���������� �������� ���� ����
                return true;//� ����� ������ ���������� �����, ����� ����� �������
            }//������������� �������, ����� �� ����� �������
            else//���� �������� ������� ������ value, ���������� � ���� ������� �������, � ����� ��������� �� ������
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