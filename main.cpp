#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int T, temp, key, min = 0;
    cin >> T;
    vector <int> v;
    priority_queue <int> pq;
    while ( T-- )
    {
        cin >> key;
        switch(key)
        {
        case 1:
            cin >> temp;
            pq.push(temp);
            if ( temp < min || min == 0 )
            {
                min = temp;
            }
            break;
        case 2:
            cin >> temp;
            while ( !pq.empty() && pq.top() != temp )
            {
                v.push_back(pq.top());
                pq.pop();
            }
            if(pq.empty())
            {
                cout << "-1" << endl;
            }
            else 
            {
                pq.pop();
            }
            while (!v.empty())
            {
                if ( min == temp && pq.empty())
                {
                    min = v.back();
                }
                pq.push(v.back());
                v.pop_back();
            }
            break;
        case 3:
            if (!pq.empty())
            {
                cout << pq.top() << endl;
            }
            else
            {
                cout << "-1" << endl;
            }
            break;
        case 4:
            if (!pq.empty())
            {
                cout << min << endl;
            }
            else
            {
                cout << "-1" << endl;
            }
            break;
        }
    }
    system ("pause");
    return 0;
}
