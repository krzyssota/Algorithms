#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define PII pair<int, int>
#define LL long long

const int mod = 1e9+ 7;
const int mxn = 1e5 + 10; // todo po co
int t[100000];
int n, m;

struct node { // todo na node
    int sz, prior;
    node * lchild, * rchild; // todo na lchild, rchild
    bool rev;
    node() { }
    node (int sz, int prior) : sz(sz), prior(prior), lchild(NULL), rchild(NULL), rev(false) { }
};
typedef node* pnode;

int getSize(pnode t){
    return t ? t->sz : 0;
}

int updateSize(pnode t) { // todo źle
    if(t != NULL){
        if(t) t->sz = getSize(t->lchild) + 1 + getSize(t->rchild);
    }
}

void updateRev(node* node){
    if(node && node->rev){
        pnode tmp = node->lchild;
        node->lchild = node->rchild;
        node->rchild = tmp;

        node->rev = false;
        if(node->lchild) node->lchild->rev ^= true;
        if(node->rchild) node->rchild->rev ^= true;
    }
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}

void recSplitBST(pnode t, pnode &l, pnode &r, int v) {

    if (t == NULL){
        l = r = NULL;
        return;
    }
    updateRev(t);
    if (t->sz <= v) {
        recSplitBST(t->rchild, t->rchild, r, v);
        l = t;
    }
    else {
        recSplitBST(t->lchild, l, t->lchild, v);
        r = t;
    }
    updateSize(t);
}

void reverse(node* root){
    root->rev ^= true;
}

node* join(node* root1, node* root2){

}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void reverseSegment(node* root, int a, int b){
    vector<node*> tmp;
    tmp = recSplitBST(root, a);
    node* t1 = tmp[0];
    node* t2 = tmp[1];
    tmp = recSplitBST(t2, b); // split (t2, t2, t3, r-l+1);
    node* t3 = tmp[0];
    node* t4 = tmp[1];
    t3->rev ^= true;
    join( join(t1, t3), t4 );
}


// https://cp-algorithms.com/data_structures/treap.html

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        char c;
        scanf(" %c", c);
        if(c == 'G') t[i] = 0;
        else t[i] = 1;
    }

    while(m--) {
        char order;
        int a, b;
        scanf(" %c%d%d", &order, &a, &b);
        if(order == '?') {
            int ans = 0;
            printf("%d\n", ans);
        }
        else {
            reverse(a, b);
        }
    }
}