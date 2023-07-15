#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>


using namespace std;

struct Location
{
    int left_side_m;
    int left_side_c;
    int right_side_m;
    int right_side_c;
    char boat_side;
    ~Location() {}
    Location& operator= (const Location& obj)
    {
        this->left_side_c = obj.left_side_c;
        this->left_side_m = obj.left_side_m;
        this->right_side_m = obj.right_side_m;
        this->right_side_c = obj.right_side_c;
        this->boat_side = obj.boat_side;
        return *this;
    }
    bool operator== (const Location& obj)
    {
        return  this->left_side_c == obj.left_side_c &&
            this->left_side_m == obj.left_side_m &&
            this->right_side_m == obj.right_side_m &&
            this->right_side_c == obj.right_side_c &&
            this->boat_side == obj.boat_side;
    }
    int what_state() // return 1 good state return 0 you lost -1 you win
    {
        if (boat_side == 'l')
        {
            if (right_side_c > left_side_m)
                return 0;
            else return 1;
        }
        else if (boat_side == 'r')
        {
            if (left_side_c + left_side_m == 0)
                return -1;
            if (left_side_c > left_side_m)
                return 0;
            else return 1;
        }
        return 0;
    }

};



struct Node
{
public:
    Location map;
    char  operation[3];// m_l
    int cost;
    int h;
    Node* parent;


    Node(Location m, const char oper[3] = "__", int cost = 0, Node* p = NULL)
    {
        map = m;
        for (int i = 0; i < 3; i++) operation[i] = oper[i];
        this->cost = cost;
        parent = p;
        h = 0;
    }
    ~Node() {}
    Node(const Node& obj)
    {
        map = obj.map;
        for (int i = 0; i < 3; i++) operation[i] = obj.operation[i];
        cost = obj.cost;
        parent = obj.parent;
        h = obj.h;
    }
    Node& operator=(const Node& obj)
    {
        map = obj.map;
        for (int i = 0; i < 3; i++) operation[i] = obj.operation[i];
        cost = obj.cost;
        parent = obj.parent;
        return *this;
        h = obj.h;
    }
    bool operator==(const Node& obj) {
        return
            map == obj.map &&

            cost == obj.cost &&
            parent == obj.parent;
    }

    int  heuristic()
    {
        if (map.left_side_c + map.left_side_m == 0) return h = 0;

        int min_operation = (map.left_side_c + map.left_side_m + 1);

        if (map.boat_side == 'r') min_operation += 1;

        if (map.boat_side == 'r')
        {
            if (map.right_side_c > map.right_side_m - 1 && map.right_side_m > 1) min_operation++;
        }

        else if (map.boat_side == 'l')
        {

        }


        return h = min_operation;
    }

    vector<Node> expand()
    {
        vector<Node> expading;
        Location tem;
        if (map.boat_side == 'l')
        {
            //move one c
            if (map.left_side_c >= 1)
            {
                tem = map;
                tem.left_side_c -= 1;
                tem.right_side_c += 1;
                tem.boat_side = 'r';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'c','_' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move two c
            if (map.left_side_c >= 2)
            {
                tem = map;
                tem.left_side_c -= 2;
                tem.right_side_c += 2;
                tem.boat_side = 'r';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'c','c' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move one m
            if (map.left_side_m >= 1)
            {
                tem = map;
                tem.left_side_m -= 1;
                tem.right_side_m += 1;
                tem.boat_side = 'r';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'm','_' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move two m
            if (map.left_side_m >= 2)
            {
                tem = map;
                tem.left_side_m -= 2;
                tem.right_side_m += 2;
                tem.boat_side = 'r';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'm','m' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move mc
            if (map.left_side_m >= 1 && map.left_side_c >= 1)
            {
                tem = map;
                tem.left_side_m -= 1;
                tem.right_side_m += 1;
                tem.left_side_c -= 1;
                tem.right_side_c += 1;
                tem.boat_side = 'r';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'm','c' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
        }
        else if (map.boat_side == 'r')
        {
            //move one c
            if (map.right_side_c >= 1)
            {
                tem = map;
                tem.left_side_c += 1;
                tem.right_side_c -= 1;
                tem.boat_side = 'l';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'c','_' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move two c
            if (map.right_side_c >= 2)
            {
                tem = map;
                tem.left_side_c += 2;
                tem.right_side_c -= 2;
                tem.boat_side = 'l';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'c','c' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move one m
            if (map.right_side_m >= 1)
            {
                tem = map;
                tem.left_side_m += 1;
                tem.right_side_m -= 1;
                tem.boat_side = 'l';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'm','_' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move two m
            if (map.right_side_m >= 2)
            {
                tem = map;
                tem.left_side_m += 2;
                tem.right_side_m -= 2;
                tem.boat_side = 'l';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'm','m' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
            //move mc
            if (map.right_side_m >= 1 && map.right_side_c >= 1)
            {
                tem = map;
                tem.left_side_m += 1;
                tem.right_side_m -= 1;
                tem.left_side_c += 1;
                tem.right_side_c -= 1;

                tem.boat_side = 'l';
                if (tem.what_state() != 0)
                {
                    char operation[2] = { 'm','c' };
                    Node* e = new Node(tem, operation, this->cost = 1, this);
                    e->heuristic();
                    expading.push_back(*e);
                    delete e;
                }
            }
        }
        return expading;
    }

};

void printlist(vector<Node>& obj)
{
    vector<Node>::iterator it;
    int count = 0;
    /*
    for (it = obj.begin(); it != obj.end(); it++, it++)
    {
        it->map.print();
        cout << endl;
        count++;
    }
    */
    cout << "\n    ->" << count << endl;
}
Node* best_h_value(vector<Node>& obj)
{
    if (obj.empty())
        return NULL;
    vector<Node>::iterator it = obj.begin(), re = obj.begin();
    Node* tem = &*it; it++;
    while (it != obj.end())
    {
        if (tem->h > it->h)
        {
            tem = &*it;
            re = it;
        }
        it++;
    }
    tem = new Node(*tem);
    obj.erase(re);
    return tem;
}

bool stateExist(vector<Node>& obj, const Node* N)
{
    vector<Node>::iterator it;

    for (it = obj.begin(); it != obj.end(); it++)
    {
        if (it->map == N->map)
            return true;
    }
    return false;
}

void printSoluation(Node* goal)
{
    if (goal)
        printSoluation(goal->parent);
    else return;

    if (goal->map.boat_side == 'r')
        cout << "->";
    else if (goal->map.boat_side == 'l')
        cout << "<-";
    for (int i = 0; i < 2; i++)
        if (goal->operation[i] != '_')
            cout << goal->operation[i];
    cout << "\n";


}

void breadth_first(Node& begain)
{
    vector<Node> open;
    vector<Node> close;
    open.push_back(begain);
    bool goal = false;
    Node* N = NULL;
    while (!open.empty())
    {
        N = new Node(open.front());
        open.erase(open.begin());
        close.push_back(*N);
        if (N->map.what_state() == -1)
        {
            goal = true;
            break;
        }

        vector <Node> E = N->expand();
        vector<Node>::iterator it;

        for (it = E.begin(); it != E.end(); ++it)
        {

            if (!(stateExist(open, &*it) || stateExist(close, &*it)))
                open.push_back(*it);
        }
    }

    if (goal == true)
    {
        cout << "the result by using breadth_first search :\n";
        printSoluation(N);
        
    }
    else
    {
        if (!goal)
        {
            cout << "best first search didn't found the path\n";
            printSoluation(N);
            
        }
    }
    cout << "Number of states expanded using breadth-first = " << close.size()<<endl;
}

void best_first_search(Node& begain)
{
    bool goal = false;
    vector <Node> open;
    vector <Node> close;

    open.push_back(begain);
    Node* N = NULL;

    while (!open.empty())
    {
        N = best_h_value(open);

        close.push_back(*N);

        if (N->map.what_state() == -1)
        {
            goal = true;
            break;
        }

        vector <Node> E = N->expand();
        vector<Node>::iterator it;

        for (it = E.begin(); it != E.end(); ++it)
        {
            if (!(stateExist(open, &*it) || stateExist(close, &*it)))
                open.push_back(*it);
        }
    }

    if (!goal)
    {
        cout << "best first search didn't found the path\n";
        printSoluation(N);
        cout << "Number of states expanded using best-first = " << close.size() << endl;;
        free(N);
        return;
    }

    cout << "the result by using best first search are :\n";
    printSoluation(N);
    cout << "Number of states expanded using best-first = " << close.size()<<endl;
    free(N);
}

int main()
{
    Location start;
    cout << "Enter number of M's on left side of the river: ";
    cin >> start.left_side_m;
    cout << "Enter number of C's on left side of the river: ";
    cin >> start.left_side_c;
    cout << "Enter number of M's on right side of the river: ";
    cin >> start.right_side_m;
    cout << "Enter number of c's on right side of the river: ";
    cin >> start.right_side_c;

    cout << "Enter location of the boat: ";
    cin >> start.boat_side;

    Node* test = new Node(start);
    breadth_first(*test);
    best_first_search(*test);
    delete test;
    return 0;
}