
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

typedef struct tree {
    int root;
    std::vector<int> children;
} tree;

tree& Union(tree& x, tree& y) {
    if (x.root < y.root) {
        y.children.insert(y.children.end(), x.children.begin(), x.children.end());
        y.children.push_back(x.root);
        return y;
    } else  {
        x.children.insert(x.children.end(), y.children.begin(), y.children.end());
        x.children.push_back(y.root);
        return x;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<tree> trees;

    while (n--) {
        int x;
        cin >> x;
        tree t;
        t.root = x;
        while (!trees.empty() && x < trees.back().root) {
            tree to_unite = trees.back();
            trees.pop_back();
            t = Union(t, to_unite);
        }
        trees.push_back(t);
    }

    size_t trees_cnt = trees.size();
    cout << trees_cnt << endl;

    for (auto t:trees) {
        t.children.push_back(t.root);
        sort(t.children.begin(), t.children.end());
        cout << t.children.size() << ' ';
        for (int j : t.children) {
            cout << j << ' ';
        }
        cout << endl;
    }
    return 0;
}


/*#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

typedef struct tree {
    int root;
    size_t sz;
    std::vector<tree> children;
} tree;

tree& Union(tree& x, tree& y) {
    if (x.sz < y.sz) {
        y.children.push_back(x);
        y.sz += x.sz;
        return y;
    } else  {
        x.children.push_back(y);
        x.sz += y.sz;
        return x;
    }
}

void rec_push_back(vector<int>& vector, const tree& tree) {
    vector.push_back(tree.root);
    for(const auto& c : tree.children) {
        rec_push_back(vector, c);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<tree> trees;

    while (n--) {
        int x;
        cin >> x;
        tree t;
        t.root = x;
        t.sz = 1;
        while (!trees.empty() && x < trees.back().root) {
            tree to_unite = trees.back();
            trees.pop_back();
            t = Union(t, to_unite);
        }
        trees.push_back(t);
    }

    size_t trees_cnt = trees.size();
    cout << trees_cnt << endl;



    for (int i = 0; i < trees_cnt; ++i) {
        vector<int> flat_tree;
        rec_push_back(flat_tree, trees[i]);
        sort(flat_tree.begin(), flat_tree.end());
        cout << flat_tree.size() << ' ';
        for (int j : flat_tree) {
            cout << j << ' ';
        }
        cout << endl;
    }

    return 0;
}*/
