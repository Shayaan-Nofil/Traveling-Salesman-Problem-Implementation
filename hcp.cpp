#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct pai {
    char a; int b;
};

class node
{
public:
    int data;
    char name;
    node* next;

    node()
    {
        data = 0;
        name = '\0';
        next = NULL;
    }

    node(int d, char a, node* n)
    {
        name = a;
        data = d;
        next = n;
    }
    node(int d, char a) {
        name = a;
        data = d;
        next = NULL;
    }
};

class list {
public:
    node* head;
    int num;

    list()
    {
        head = NULL;
        num = 0;
    }
    void insert(int d, char a) {

        node* q = new node{ d, a };

        if (head != NULL) {
            node* p = head;

            while (p->next != NULL) {
                p = p->next;
            }
            p->next = q;

        }
        else {

            head = q;
        }
        num++;
        q = NULL;
        delete q;
    }

    bool searchfirst(char find) {

        if (head != NULL) {

            if (head->name == find) {
                return true;
            }
            return false;
        }
        else {

            return false;
        }
    }

    char getname(int ind) {
        node* temp = head;

        if (head != NULL) {
            for (int i = 0; i < ind; i++) {

                temp = temp->next;
                               
            }
            return temp->name;
        }      
    }

    int getind(char nam) {
        node* temp = head;

        if (head != NULL) {
            int ind = 0;
            while (temp->next != NULL) {
                if (temp->name == nam) {
                    return ind;
                }
                temp = temp->next;
                ind++;
            }
            if (temp->name == nam) {
                return ind;
            }
        }
        return -1;
    }

    int getlength() {
        return num;
    }

    int getweight(int ind) {
        node* temp = head;

        if (head != NULL) {
            for (int i = 0; i < ind; i++) {
                temp = temp->next;
            }
            return temp->data;
        }
    }

    pai getsmallest(list fname) {
        pai min;
        min.a = 'a';
        min.b = 999999;
        node* temp = head;

        if (head != NULL) {
            temp = temp->next;
            for (int i = 0; i < num - 1; i++) {
                if (min.b > temp->data && fname.getind(temp->name) == -1) {
                    min.b = temp->data;
                    min.a = temp->name;
                }
                temp = temp->next;
            }
        }
        
        return min;
    }

    void print() {
        node* q = head;
        if (head != NULL) {
            while (q->next != NULL) {
                cout << q->name << " ,";
                q = q->next;
            }
            cout << q->name;
        }
    }
};

class Graph
{
public:
    list* adj;
    int am;

    Graph() {
        adj = new list[27];
        am = 0;
    }

    Graph(int a) {
        adj = new list[a];
        am = 0;
    }

    void addnode(char a) {
        adj[am].insert(0, a);
        am++;
    }
    
    void addedge(char start, char name, int weight) {
        for (int i = 0; i < am; i++) {
            if (adj[i].searchfirst(start)) {
                adj[i].insert(weight, name);
                break;
            }
        }
        for (int i = 0; i < am; i++) {
            if (adj[i].searchfirst(name)) {
                adj[i].insert(weight, start);
                break;
            }
        }        
    }

    void printadjlist() {
        for (int i = 0; i < am; i++) {
            adj[i].print();
        }
    }

    int getind(char a) {
        for (int i = 0; i < am; i++) {
            if (adj[i].head->name == a) {
                return i;
            }
        }
    }
};

Graph* readfromfile(string str, int &timerem, int &waitime) {
    Graph* gr;
    ifstream mfile(str);
    string s;
    list temp;

    //adding vertices
    getline(mfile, s);
    int i = 0;
    for (i = 0; s[i] != '{'; i++);
    i++;
    int amount = 0;
    for (i; i < s.length(); i++) {
        if (s[i] == '}') {
            break;
        }
        else if (s[i] != ',') {
            temp.insert(0, s[i]);
        }
    }
    gr = new Graph(temp.num);

    for (int i = 0; i < temp.num; i++) {
        gr->addnode(temp.getname(i));
    }

    cout << "Vectices: {"; 
    temp.print();
    cout << "}" << endl;
    
    /// Adding edges
    string t, t2,t3, stemp;
    getline(mfile, stemp);
    s = stemp;
    getline(mfile, stemp);
    t = stemp;
    getline(mfile, stemp);
    t2 = stemp;
    getline(mfile, stemp);
    t3 = stemp;
    char a, b;
    int x = 0;
    for (i = 0; s[i] != '{'; i++);
    for (x = 0; t[x] != '{'; x++);
    i++; x++;

    for (i; i < s.length(); i++) {
        if (s[i] == '}') {
            break;
        }
        else if (s[i-1] == '(') {
            a = s[i];
            b = s[i + 2];

            string wtemp = "";

            while (t[x] != ',' && t[x] != '}') {
                wtemp += t[x];
                x++;
            }
            x++;         
            gr->addedge(a, b, stoi(wtemp));

            cout << "Edge added: " << a << b << wtemp << endl;
        }
    }

    int totalwait = 0; timerem = 0;
    for (i = 0; i < t2.length(); i++) {
        if (i > 0 && t2[i - 1] == '=') {
            x = i;
            string numtemp = "";
            while (t2[x] != ',' && x < t2.length()) {
                numtemp += t2[x];
                x++;
            }
            totalwait += stoi(numtemp);
        }
    }
    for (int i = 0; i < t3.length(); i++) {
        if (i > 0 && t3[i - 1] == '=') {
            x = i;
            string numtemp = "";
            while ( x < t3.length()) {
                numtemp += t3[x];
                x++;
            }
            timerem = stoi(numtemp);
        }
    }
    timerem -= totalwait;
    waitime = totalwait;

    return gr;
    mfile.close();
}

void gethamilton(Graph* gra, pai** graph, int start, int timerem, int waitime) {
    vector<int> arr, suparr;

    int max = 0;
    for (int i = 0; i < gra->am; i++) {
        if (gra->adj[i].getlength() > max) {
            max = gra->adj[i].getlength();
        }
    }

    for (int i = 0; i < max; i++) {
        if (i != 0) {
            suparr.push_back(i);
        }        
    }
    for (int i = 0; i < gra->am; i++) {
        arr.push_back(i);
    }
    
    list min; string mindispath;
    int intmin = INT_MAX;
    do {
            list path;
            int intpath = 0;
            string dispath = "";

            path.insert(0, graph[start][0].a);
            dispath += graph[start][0].a;
            dispath += "->";

            int x = 0, row = start, count = 1;
            for (int i = 0; i < gra->am; i++) {
                    if (i != gra->am - 1) {
                        if (path.getind(graph[arr[row]][suparr[x]].a) == -1 && graph[arr[row]][suparr[x]].a > 0) {
                            path.insert(graph[arr[row]][suparr[x]].b, graph[arr[row]][suparr[x]].a);
                            dispath += graph[arr[row]][suparr[x]].a;
                            dispath += "->";
                            intpath += graph[arr[row]][suparr[x]].b;
                            count++;
                        }
                        else {
                            if (x < gra->adj[row].getlength() - 2) {
                                x++;
                                i--;
                            }
                            else {
                                break;
                            }
                            
                            continue;
                        }
                        int ind = 0;
                        for (int i = 0; i < arr.size(); i++) {
                            if (i != 0) {
                                if (graph[arr[i]][0].a == graph[arr[row]][suparr[x]].a) {
                                    ind = i;
                                    break;
                                }
                            }                           
                        }
                        row = ind;
                        x = 0;
                    }
                    else {
                        for (int i = 0; i < suparr.size(); i++) {
                            if (graph[arr[row]][suparr[i]].a == graph[start][0].a) {
                                path.insert(graph[arr[row]][suparr[i]].b, graph[arr[row]][suparr[i]].a);
                                dispath += graph[arr[row]][suparr[i]].a;
                                intpath += graph[arr[row]][suparr[i]].b;
                                count++;
                            }
                        }
                        if (intpath < intmin && count == gra->am + 1) {
                            intmin = intpath;
                            min = path;
                            mindispath = dispath;
                        }
                        break;
                    }                
            }
    } while (next_permutation(suparr.begin(), suparr.end()));


    if (intmin < timerem) {
        cout << "Path exists: " << mindispath << endl;
        cout << "Total time taken: " << intmin + waitime << endl;
    }
    else {
        cout << "NO FEASIBLE CIRCUIT" << endl;
    }
}

void findminhamil(char startpos, string str) {
    Graph* gr; 
    int timerem, waitime;
    gr = readfromfile(str, timerem, waitime);

    pai** gra = new pai * [gr->am];


    for (int i = 0; i < gr->am; i++) {
        gra[i] = new pai[gr->adj[i].getlength()];

        for (int x = 0; x < gr->adj[i].getlength(); x++) {
            gra[i][x].a = gr->adj[i].getname(x);
            gra[i][x].b = gr->adj[i].getweight(x);
        }
    }

    gethamilton(gr, gra, 0, timerem, waitime);
    delete gr;
}

int main() {
    cout << "Test 1" << endl;
    findminhamil('h', "P2_test1.txt");
    cout << endl << "Test 2" << endl;
    findminhamil('h', "P2_test2.txt");
}
