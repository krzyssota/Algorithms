#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define PLL pair<ULL, ULL>
#define ULL unsigned long long
#define mtx pair<PLL, PLL>
#define gg first.first
#define gr first.second
#define rg second.first
#define rr second.second

const int mod = 1e9 + 7;

struct node {
    int sz;
    char id;
    node *lchild;
    node *rchild;
    node *parent;
    bool rev;
    mtx m;

    node(char type) : lchild(nullptr), rchild(nullptr),
                      parent(nullptr), rev(false) {
        sz = 0;
        id = type;
        m.gg = (id == 'G' ? 1 : 0);
        m.gr = 0;
        m.rg = 0;
        m.rr = (id == 'R' ? 1 : 0);
    }
};

typedef node *pnode;

int getSize(pnode t) {
    return t ? t->sz : 0;
}

void pushDownRev(pnode node) {
    if (node && node->rev) {
        pnode tmp = node->lchild;
        node->lchild = node->rchild;
        node->rchild = tmp;

        node->rev = false;
        if (node->lchild) node->lchild->rev ^= true;
        if (node->rchild) node->rchild->rev ^= true;
    }
}

void updateSize(pnode t) {
    if (t) t->sz = getSize(t->lchild) + 1 + getSize(t->rchild);

}

ULL sumMatrix(pnode t) {
    if (t) {
        return ((((((t->m.gg + t->m.gr) % mod) + t->m.rg) % mod) + t->m.rr) % mod);
    } else {
        return 0;
    }
}

mtx addMatrix(mtx m1, mtx m2) {
    return {{m1.gg + m2.gg, m1.gr + m2.gr},
            {m1.rg + m2.rg, m1.rr + m2.rr}};
}

void recountMatrix(pnode t) {
    if (t) {
        t->m = {{0, 0},
                {0, 0}};

        mtx m1;
        if (t->lchild) m1 = t->lchild->m;
        else
            m1 = {{0, 0},
                  {0, 0}};
        mtx m2;
        if (t->rchild) m2 = t->rchild->m;
        else
            m2 = {{0, 0},
                  {0, 0}};

        if (t->id == 'G') {
            t->m.gg = 1;
            // GG
            t->m.gg += m1.gr // GR|G
                       + m2.rg // G|RG
                       + m1.gr * m2.rg; // GR|G|RG
            // GR
            t->m.gr += m2.rr // G|RR
                       + m1.gr * m2.rr; // GR|G|RR
            // RG
            t->m.rg += m1.rr // RR|G
                       + m1.rr * m2.rg; // RR|G|RG
            // RR
            t->m.rr += m1.rr * m2.rr; // RR|G|RR

            t->m = addMatrix(t->m, m1);
            t->m = addMatrix(t->m, m2);
        } else {
            t->m.rr = 1;
            //GG
            t->m.gg += m1.gg * m2.gg // GG|R|GG
                       + m1.gg * m2.rg // GG|R|RG
                       + m1.gr * m2.gg // GR|R|GG
                       + m1.gr * m2.rg; // GR|R|RG

            // GR
            t->m.gr += m1.gg * m2.rr // GG|R|RR
                       + m1.gg * m2.gr // GG|R|GR
                       + m1.gr * m2.rr // GR|R|RR
                       + m1.gr * m2.gr // GR|R|GR
                       + m1.gg // GG|R
                       + m1.gr; // GR|R
            // RG
            t->m.rg += m1.rg * m2.rr // RG|R|RR
                       + m1.rg * m2.gr // RG|R|GR
                       + m1.rr * m2.rr // RR|R|RR
                       + m1.rr * m2.gr // RR|R|GR
                       + m2.gg // R|GG
                       + m2.rg; // R|RG
            // RR
            t->m.rr += m1.rr * m2.rr // RR|R|RR
                       + m1.rr * m2.gr // RR|R|GR
                       + m1.rg * m2.rr // RG|R|RR
                       + m1.rg * m2.gr // RG|R|GR
                       + m2.rr // R|RR
                       + m2.rg // R|RG
                       + m1.rr // RR|R
                       + m1.rg; // RG|R

            t->m = addMatrix(t->m, m1);
            t->m = addMatrix(t->m, m2);
        }
    }
}

void leftRotate(pnode x);

void rightRotate(pnode y) {
    if (y) {
        if (y->rev) {
            pushDownRev(y);
            leftRotate(y);
            return;
        }
        pnode x = y->lchild;
        if (x) {
            if (x->rev) pushDownRev(x);

            pnode grandparent = y->parent;
            if (grandparent && y == grandparent->lchild) { // y is an lchild
                grandparent->lchild = x;
            } else if (grandparent) {
                grandparent->rchild = x;
            }
            x->parent = grandparent;

            pnode xrchild = x->rchild;
            y->lchild = xrchild;
            if (xrchild) xrchild->parent = y;

            y->parent = x;
            x->rchild = y;

            updateSize(y);
            updateSize(x);

            x->m = y->m;
            recountMatrix(y);
        }
    }
}

void leftRotate(pnode x) {
    if (x) {
        if (x->rev) {
            pushDownRev(x);
            rightRotate(x);
            return;
        }
        pnode y = x->rchild;
        if (y) {
            if (y->rev) pushDownRev(y);

            pnode grandparent = x->parent;
            if (grandparent && x == grandparent->lchild) { // x is x lchild
                grandparent->lchild = y;
            } else if (grandparent) {
                grandparent->rchild = y;
            }
            y->parent = grandparent; // y's grandparent becomes parent

            pnode ylchild = y->lchild;
            x->rchild = ylchild;
            if (ylchild) ylchild->parent = x; // y's left subtree becomes x's right subtree

            x->parent = y;
            y->lchild = x;

            updateSize(x);
            updateSize(y);

            y->m = x->m;
            recountMatrix(x);
        }
    }
}

void splay(pnode t) {
    if (t) {
        while (t->parent != nullptr) {
            if (t->parent->parent == nullptr) { // parent is a root
                if (t == t->parent->lchild) {
                    rightRotate(t->parent);
                } else {
                    leftRotate(t->parent);
                }
            } else { // parent and grandparent exist
                if (t->parent == t->parent->parent->lchild
                    && t == t->parent->lchild) { // both are left children
                    rightRotate(t->parent->parent);
                    rightRotate(t->parent);
                } else if (t->parent == t->parent->parent->rchild
                           && t == t->parent->rchild) { // both are right children
                    leftRotate(t->parent->parent);
                    leftRotate(t->parent);
                } else if (t->parent == t->parent->parent->rchild
                           && t == t->parent->lchild) { // parent is a right child, t is a left child
                    rightRotate(t->parent);
                    leftRotate(t->parent);
                } else if (t->parent == t->parent->parent->lchild
                           && t == t->parent->rchild) { // parent is a left child, t is a right child
                    leftRotate(t->parent);
                    rightRotate(t->parent);
                }
            }
        }
    }
}

pnode find(pnode t, int x) {
    if (t) {
        if (getSize(t->lchild) + 1 > x) {
            return find(t->lchild, x);
        } else if (getSize(t->lchild) + 1 == x) {
            return t;
        } else {
            return find(t->rchild, x - (getSize(t->lchild) + 1));
        }
    } else {
        return nullptr;
    }
}

pair<pnode, pnode> split(pnode t, int x) {
/*
 t:=     x
     y       z
   /\ /\   /\ /\


           t2:= x
t1:=   y         \
     /\ /\        z
                /\ /\
*/

    pnode tmp = find(t, x);
    splay(tmp);
    pnode newRoot = tmp;
    if (!newRoot) {
        return {t, nullptr};
    }

    pnode t2 = newRoot;

    pnode t1 = t2->lchild;
    t2->lchild = nullptr;

    if (t1) t1->parent = nullptr;

    updateSize(t1);
    updateSize(t2);
    recountMatrix(t2);

    return {t1, t2};
}

pnode findLast(pnode t) {
    if (t) {
        pnode res = (t->rev ? findLast(t->lchild) : findLast(t->rchild));
        return res != nullptr ? res : t;
    }
}

pnode join(pnode t1, pnode t2) {
    if (!t1) return t2;
    if (!t2) return t1;

    pnode max1 = findLast(t1);
    splay(max1);
    //assert(max1->rchild == nullptr);
    if (max1) max1->rchild = t2;
    t2->parent = max1;
    updateSize(max1);
    recountMatrix(max1);
    return max1;
}

/*void recReverse(pnode t) {
    if(t) {
        pnode tmp = t->lchild;
        t->lchild = t->rchild;
        t->rchild = tmp;
        recReverse(t->lchild);
        recReverse(t->rchild);
    }
}*/

pnode reverseSegment(pnode root, int a, int b) {
    if (root) {

        pair<pnode, pnode> tmp = split(root, a);
        pnode t1 = tmp.fi;
        pnode t2 = tmp.se;

        tmp = split(t2, (b - a + 1) + 1);

        pnode t3 = tmp.fi;
        pnode t4 = tmp.se;

        if (t3) t3->rev ^= true;

        return join(join(t1, t3), t4);
    } else {
        return nullptr;
    }
}

pnode howMany(pnode root, int a, int b, ULL *ans) {
    if (root) {
        pair<pnode, pnode> tmp = split(root, a);
        pnode t1 = tmp.fi;
        pnode t2 = tmp.se;

        tmp = split(t2, (b - a + 1) + 1);

        pnode t3 = tmp.fi;
        pnode t4 = tmp.se;

        if (t3 && t3->rev) pushDownRev(t3);
        recountMatrix(t3);

        (*ans) = sumMatrix(t3);

        return join(join(t1, t3), t4);
    } else {
        return nullptr;
    }
}

int setSizes(pnode t) {
    if (t) {
        t->sz = setSizes(t->lchild) + setSizes(t->rchild) + 1;
        return t->sz;
    }
    return 0;
}

/*void printRec(pnode t) {
    if (t) {
        printRec(t->lchild);
        std::cout << t->id << ',' << t->sz << ',' << ((t->rev) ? "rev" : "not") << ' ';
        printRec(t->rchild);
    }
}*/

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    pnode prev = nullptr, tmp = nullptr;
    for (int i = 1; i <= n; i++) {
        char c;
        scanf(" %c", &c);
        tmp = new node(c);
        if (i != 1) {
            prev->parent = tmp;
            tmp->lchild = prev;
            recountMatrix(tmp);
        }
        prev = tmp;
    }

    pnode root = tmp;
    setSizes(root);

    while (m--) {
        char order;
        int a, b;
        scanf(" %c%d%d", &order, &a, &b);
        if (order == '?') {
            ULL ans;
            root = howMany(root, a, b, &ans);
            printf("%llu\n", ans);

        } else {
            root = reverseSegment(root, a, b);
        }
    }
    //printf("6\n5\n");
    return 0;

}