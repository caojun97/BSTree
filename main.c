#include <stdio.h>
#include <stdlib.h>

typedef struct BSTreeNode
{
	int    key;                 // �ؼ���(��ֵ)
	struct BSTreeNode *left;    // ����
	struct BSTreeNode *right;   // �Һ���
	struct BSTreeNode *parent;  // �����
}Node, *BSTree;

/* ������� */
static Node* bstree_node_create(int key, Node *parent, Node *left, Node *right)
{
	Node *p = (Node *)malloc(1*sizeof(Node));
	if (NULL == p)
	{
		return NULL;
	}
	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;
	return p;
}

/* ���ٶ����� */
static void bstree_destroy(BSTree tree)
{
	if (NULL != tree)
	{
		if (tree->left != NULL)
		{
			bstree_destroy(tree->left);
		}
		if (tree->right != NULL)
		{
			bstree_destroy(tree->right);
		}
		free(tree);
	}
}

/* ������ */
static Node* bstree_node_insert(BSTree tree, Node *node)
{
	Node *p = NULL;
	Node *q = tree;

	// find the last node(as the new node's parent)
	while (q != NULL)
	{
		p = q;
		if (node->key < q->key)
		{
			q = q->left;
		}
		else
		{
			q = q->right;
		}
	}
	node->parent = p;
	if (NULL == p)
	{
		tree = node;
	}
	else if (node->key < p->key)
	{
		p->left = node;
	}
	else
	{
		p->right = node;
	}
	return tree;
}

/* ͨ��ָ��keyֵ������ */
static Node* bstree_insert_with_key(BSTree tree, int key)
{
	Node *p = bstree_node_create(key, NULL, NULL, NULL);
	if (NULL == p)
	{
		return tree;
	}
	Node *q = bstree_node_insert(tree, p);
	return q;
}

/* ����keyֵ���Ľ�� */
static Node* bstree_node_maximum_find(BSTree tree)
{
	if (NULL == tree)
	{
		return NULL;
	}
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;
}

/* ����keyֵ��С�Ľ�� */
static Node* bstree_node_minimum_find(BSTree tree)
{
	if (NULL == tree)
	{
		return NULL;
	}
	while (tree->left != NULL)
	{
		tree = tree->left;
	}
	return tree;
}

/* �ݹ���ҷ� ͨ��ָ��keyֵ������� */
static Node* bstree_node_search_with_key(BSTree tree, int key)
{
	if (NULL == tree || tree->key == key)
	{
		return tree;
	}
	if (key < tree->key)
	{
		return bstree_node_search_with_key(tree->left, key);
	}
	else
	{
		return bstree_node_search_with_key(tree->right, key);
	}
}

/* ���ҽ��node�ĺ�̽�㣬������"������������ֵ���ڸý�����С���" */
static Node* bstree_successor(Node *node)
{
	// ���ý������Һ��ӣ���������Һ���Ϊ��������������С���
	if (node->right != NULL)
	{
		return bstree_node_minimum_find(node->right);
	}
	// ���ý��û���Һ��ӡ���ý�������ֿ��ܣ�
	// 01) �ý����һ�����ӣ���ý��ĺ�̽��������ĸ����
	// 02) �ý����һ���Һ��ӣ�����Ҹý�����͸���㣬�Ҹø����ӵ�����ӣ�������������͸������ǽ��node�ĺ�̽��
	Node *p = node->parent;
	while (p != NULL && node == p->right)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

/* ���ҽ��node��ǰ����㣬������"������������ֵС�ڸý��������" */
static Node* bstree_predecessor(Node *node)
{
	// ���ý��������ӣ������������Ϊ�����������������
	if (node->left != NULL)
	{
		return bstree_node_maximum_find(node->left);
	}
	// ���ý��û�����ӡ���ý�������ֿ��ܣ�
	// 01) �ý����һ�����ӣ�����Ҹý�����͸���㣬�Ҹø����ӵ���Һ��ӣ�������������͸������ǽ���ǰ�����
	// 02) �ý����һ���Һ��ӣ���ý���ǰ�����������ĸ����
	Node *p = node->parent;
	while (p != NULL && node == p->left)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

/* ɾ����� */
static Node* bstree_node_delete(BSTree tree, Node *node)
{
	Node *p = NULL, *q = NULL;
	// �жϽ��node�Ƿ�������ӻ��Һ��ӣ����ý��û�����Һ��ӣ�����Ҹý��ĺ�̽��
	if (node->left == NULL || node->right == NULL)
	{
		q = node;
	}
	else
	{
		q = bstree_successor(node);
	}
	if (q->left != NULL)
	{
		p = q->left;
	}
	else
	{
		p = q->right;
	}

	if (p != NULL)
	{
		p->parent = q->parent;
	}

	if (q->parent == NULL)
	{
		tree = p;
	}
	else if (q == q->parent->left)
	{
		q->parent->left = p;
	}
	else
	{
		q->parent->right = p;
	}

	if (q != node)
	{
		node->key = q->key;
	}
	if (q != NULL)
	{
		free(q);
	}
	return tree;
}

/* ͨ��ָ��keyֵ�Ľ�� */
static Node* bstree_delete_with_key(BSTree tree, int key)
{
	Node *p = bstree_node_search_with_key(tree, key);
	if (p != NULL)
	{
		tree = bstree_node_delete(tree, p);
	}
	return tree;
}

/* ǰ����� */
static void bstree_preorder(BSTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->key);
		bstree_preorder(tree->left);
		bstree_preorder(tree->right);
	}
}


/* ������� */
static void bstree_midorder(BSTree tree)
{
	if (tree != NULL)
	{ 
		bstree_midorder(tree->left);
		printf("%d ", tree->key);
		bstree_midorder(tree->right);
	}
}


/* ������� */
static void bstree_postorder(BSTree tree)
{
	if (tree != NULL)
	{
		bstree_postorder(tree->left);
		bstree_postorder(tree->right);
		printf("%d ", tree->key);
	}
}

int main(int argc, const char *argv[])
{
	BSTree root = NULL;
	//int number_list[] = {1, 5, 4, 3, 2, 6};
	int number_list[] = { 2, 1, 4, 3, 5};
	int list_num = sizeof(number_list) / sizeof(number_list[0]);
	
	printf("Insert number:");
	for (int i = 0; i < list_num; i++)
	{
		printf("%d ", number_list[i]);
		root = bstree_insert_with_key(root, number_list[i]);
	}
	printf("\n\n");

	// ǰ�����
	printf("Preorder BSTree:");
	bstree_preorder(root);
	printf("\n");
	// �������
	printf("Midorder BSTree:");
	bstree_midorder(root);
	printf("\n");
	// �������
	printf("Posorder BSTree:");
	bstree_postorder(root);
	printf("\n\n");
	
	// ����keyֵ��С�Ľ��
	Node *p = bstree_node_minimum_find(root);
	if (NULL != p)
	{
		printf("the key minimum: %d\n", p->key);
	}
	else
	{
		printf("the key minimum not exist.\n");
	}
	
	// ����keyֵ���Ľ��
	p = bstree_node_maximum_find(root);
	if (NULL != p)
	{
		printf("the key maximum: %d\n", p->key);
	}
	else
	{
		printf("the key maximum not exist.\n\n");
	}

	// ����ָ��keyֵ�Ľ��
	int key = 3;
	p = bstree_node_search_with_key(root, key);
	if (NULL != p)
	{
		printf("the key:%d node exist.\n", key);
	}
	else
	{
		printf("the key:%d node not exist.\n", key);
	}
	// ����ָ��keyֵ�Ľ���ǰ�����
	if (NULL != p)
	{
		Node *r = bstree_predecessor(p);
		printf("���(key=%d)��ǰ�����:key=", p->key);
		if (r != NULL)
		{
			printf("%d", r->key);
		}
		else
		{
			printf("not exist.");
		}
		printf("\n");
	}

	// ����ָ��keyֵ�Ľ��ĺ�̽��
	if (NULL != p)
	{
		Node *r = bstree_successor(p);
		printf("���(key=%d)�ĺ�̽��:key=", p->key);
		if (r != NULL)
		{
			printf("%d", r->key);
		}
		else
		{
			printf("not exist.");
		}
		printf("\n\n");
	}


	// ɾ��ָ��keyֵ�Ľ��
	key = 5;
	p = bstree_delete_with_key(root, key);
	printf("ɾ��key=%d�Ľ��\n\n", key);

	// ǰ�����
	printf("Preorder BSTree:");
	bstree_preorder(root);
	printf("\n");
	// �������
	printf("Midorder BSTree:");
	bstree_midorder(root);
	printf("\n");
	// �������
	printf("Posorder BSTree:");
	bstree_postorder(root);
	printf("\n\n");

	bstree_destroy(root);
	return 0;
}