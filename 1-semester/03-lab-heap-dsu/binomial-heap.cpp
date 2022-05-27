#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>

using namespace std;

#define size(a) (int) a.size()

const int MAXH = 1e3 + 47;
const int MAXN = 1e6 + 27;
const int CHILD = 20;
const int last = 1e3 + 13;

struct node {
	int key, degree, heap_id, element_id;
	node *parent, *child[CHILD];

	node() {}
	node(int _key, int _element_id) {
		key = _key;
		degree = 0;
		heap_id = -1;
		element_id = _element_id;
		parent = nullptr;
		fill(child, child + CHILD, nullptr);
	}
};

node *heap[MAXH][CHILD], *nodes[MAXN];

void merge_heaps(int a, int b) {
	vector<node*> merged;
	for (int i = 0; i < CHILD; i++) {
		if (heap[a][i]) {
			merged.push_back(heap[a][i]);
		}
		if (heap[b][i]) {
			merged.push_back(heap[b][i]);
		}
	}

	fill(heap[a], heap[a] + CHILD, nullptr);
	fill(heap[b], heap[b] + CHILD, nullptr);

	for (int i = 1; i < size(merged); i++) {
		if (merged[i - 1]->degree != merged[i]->degree) {
			continue;
		}

		if (merged[i - 1]->key < merged[i]->key) {
			swap(merged[i - 1], merged[i]);
		}

		merged[i]->degree++;
		merged[i]->child[merged[i - 1]->degree] = merged[i - 1];
		merged[i - 1]->parent = merged[i];
		merged[i - 1] = nullptr;

		if (i + 1 < size(merged) && merged[i]->degree > merged[i + 1]->degree) {
			swap(merged[i], merged[i + 1]);
		}
	}

	for (int i = 0; i < size(merged); i++) {
		if (merged[i]) {
			heap[a][merged[i]->degree] = merged[i];
			heap[a][merged[i]->degree]->heap_id = a;
		}
	}
}

void add_element(int v, int a, int &element_id) {
	nodes[element_id] = new node(v, element_id);
	heap[last][0] = nodes[element_id++];
	merge_heaps(a, last);
}

int get_heap_id(node *t) {
	while (t->parent) {
		t = t->parent;
	}
	return t->heap_id;
}

void swap_nodes(node *a, node *b) {
	swap(a->key, b->key);
	swap(a->element_id, b->element_id);
	swap(nodes[a->element_id], nodes[b->element_id]);
}

void sift_up(node *t) {  // O(log(n))
	while (t->parent && t->key < t->parent->key) {
		swap_nodes(t, t->parent);
		t = t->parent;
	}
}

void sift_down(node *t) {
	while (true) {
		int min_val = INT_MAX;
		node *son = nullptr;
		for (int i = 0; i < CHILD; i++) {
			if (t->child[i] && t->child[i]->key < min_val) {
				min_val = t->child[i]->key;
				son = t->child[i];
			}
		}

		if (son && son->key < t->key) {
			swap_nodes(t, son);
			t = son;
		} else {
			break;
		}
	}
}

void set_key(int id, int key) {
	nodes[id]->heap_id = get_heap_id(nodes[id]);
	nodes[id]->key = key;
	sift_up(nodes[id]);
	sift_down(nodes[id]);
}

void extract_min(int heap_id) {
	int min_val = INT_MAX;
	int id = -1;
	for (int i = 0; i < CHILD; i++) {
		if (heap[heap_id][i] && heap[heap_id][i]->key < min_val) {
			min_val = heap[heap_id][i]->key;
			id = i;
		}
	}

	node *son = heap[heap_id][id];

	for (int i = 0; i < CHILD; i++) {
		if (son->child[i]) {
			son->child[i]->parent = nullptr;
			heap[last][i] = son->child[i];
		}
	}
	heap[heap_id][id] = nullptr;
	merge_heaps(heap_id, last);
}

void delete_element(int id) {
	set_key(id, INT_MIN);
	extract_min(nodes[id]->heap_id);
}

int get_min(int heap_id) {
	int res = INT_MAX;
	for (int i = 0; i < CHILD; i++) {
		if (heap[heap_id][i]) {
			res = min(res, heap[heap_id][i]->key);
		}
	}
	return res;
}

void print_node(node *t) {
	if (!t) {
		return;
	}
	cout << "+" << t->key << ' ' << t->element_id << '\n';
	for (int i = 0; i < CHILD; i++) {
		if (t->child[i]) {
			cout << t->key << ' ' << t->child[i]->key << '\n';
			print_node(t->child[i]);
		}
	}
}

void print_heap(int id) {
	for (int i = 0; i < CHILD; i++) {
		print_node(heap[id][i]);
		cout << '\n';
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	int element_id = 1;
	while (m--) {
		int type;
		cin >> type;

		switch(type) {
			int v, a, b, id;
			case 0:
				cin >> a >> v;
				add_element(v, --a, element_id);
				break;
			case 1:
				cin >> a >> b;
				merge_heaps(--b, --a);
				break;
			case 2:
				cin >> id;
				delete_element(id);
				break;
			case 3:
				cin >> id >> v;
				set_key(id, v);
				break;
			case 4:
				cin >> a;
				cout << get_min(--a) << '\n';
				break;
			case 5:
				cin >> a;
				extract_min(--a);
		}
	}
}
