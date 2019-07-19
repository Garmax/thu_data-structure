// OJ Problem #6
// Employee Management

#include <cstdio>
#include <cstdlib>
#include <algorithm>

const int MAXN = 200009;

struct Node{
	Node *f, *ch[2];
	int size, v;

	Node (): f(NULL) {
        ch[0] = ch[1] = NULL;
        size = v = 0;
    }
	void update();
}*root, tr[MAXN * 2];
int trs = 0;

void Node::update() {
	size = 1;
    for (int i = 0; i < 2; ++i)
        if (ch[i] != NULL) size += ch[i]->size;
}
 
void rotate(Node *u, bool p) {
	Node *v = u->f;
	if (v->f != NULL) v->f->ch[v->f->ch[1] == v] = u;
    else root = u;
	u->f = v->f;
	if (u->ch[p ^ 1] != NULL) u->ch[p ^ 1]->f = v;
	v->ch[p] = u->ch[p ^ 1];
	u->ch[p ^ 1] = v;
	v->f = u;
	v->update();
	return ;
}
 
void splay(Node *u, Node *un = NULL) {
    if (u == NULL) return ;
	while (u->f != un) {
		Node *v = u->f;
		if (v->f == un) {
			rotate(u, v->ch[1] == u);
		}
		else {
			bool p = (v->ch[1] == u);
			if ((v->f->ch[1] == v) == p) {
				rotate(v, p);
				rotate(u, p);
			}
			else {
				rotate(u, p);
				rotate(u, p ^ 1);
			}
		}
	}
	u->update();
	return ;
}

Node* newNode(int k, Node *f = NULL) {
    tr[trs].v = k;
    tr[trs].size = 1;
    tr[trs].f = f;
    return &tr[trs++];
}

void insert(int k) {
    if (root == NULL) root = newNode(k);
    Node *u = root;
    while (u->v != k) {
        if (u->v > k) {
            if (u->ch[0] == NULL) 
                u->ch[0] = newNode(k, u);
            u = u->ch[0];
        }
        else {
            if (u->ch[1] == NULL) 
                u->ch[1] = newNode(k, u);
            u = u->ch[1];
        }
    }
    splay(u);
}

Node* get(int k) {
    Node *u = root;
    while (u->v != k) 
        u = u->ch[u->v < k];
    return u;
}

void del(int k) {
    Node *u = get(k);
    splay(u);
    if (u->ch[1] == NULL) {
        root = u->ch[0];
        if (u->ch[0] != NULL) u->ch[0]->f = NULL;
        return ;
    }
    Node *v = u->ch[1];
    while (v->ch[0] != NULL) v = v->ch[0];
    splay(v, u);
    root = v;
    v->ch[0] = u->ch[0];
    if (u->ch[0] != NULL) u->ch[0]->f = v;
    v->f = NULL;
    splay(v);
}

int query(int k) {
    Node *u = root;
    while (true) {
        int cnt = 0;
        if (u->ch[0] != NULL) {
            cnt += u->ch[0]->size;
            if (cnt >= k) {
                u = u->ch[0];
                continue;
            }
        }
        ++cnt;
        if (cnt == k) return u->v;
        k -= cnt;
        u = u->ch[1];
    }
}

int count(int k) {
    Node *u = get(k);
    splay(u);
    if (u->ch[0]) return u->ch[0]->size + 1;
    else return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char s[13];
        int k;
        scanf("%s%d", s, &k);
        if (s[0] == 'I') insert(k);
        else if (s[0] == 'D') del(k);
        else if (s[0] == 'Q') printf("%d\n", query(k));
        else if (s[0] == 'S') printf("%d\n", count(k));
    }
    return 0;
}