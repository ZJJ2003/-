#pragma once
#include<iostream>
using namespace std;
struct LZW
{  
	string word;//����
     int NO;//����
	LZW* lchild,* rchild;
}; 
LZW* InserBST(LZW* bt, int k,string word)  //����ڵ�����and������
{
	if (bt == NULL)
	{
		bt = new LZW;
		bt->NO = k; bt->word = word;
		bt->lchild = bt->rchild = NULL;
	}
	else if (k < bt->NO)
		bt->lchild = InserBST(bt->lchild, k,word);
	else if (k > bt->NO)
		bt->rchild = InserBST(bt->rchild, k,word);

	return bt;
}



void InOrder(LZW* b) //��������ݹ�
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		cout << b->NO << " " << b->word << endl;
		InOrder(b->rchild);
	}
}

LZW* find_for_word(const string& word, LZW* bt)
{
	LZW* p = bt;
	LZW* f = NULL;//��ʼ��
	while (p != NULL && p->word != word) {//��������
		
			f = p;
			p = p->rchild;
		
	}
	return p;//����ֵ�����ڣ���ָ��NULL��㱻����
}
LZW* find_for_NO(const int& NO, LZW* bt)
{
	LZW* p = bt;
	LZW* f = NULL;//��ʼ��
	while (p != NULL && p->NO != NO) {//��������

		f = p;
		p = p->rchild;

	}
	return p;//����ֵ�����ڣ���ָ��NULL��㱻����
}
void Delete(const int& k, LZW*& p) {
	//��pΪ���Ķ�����������ɾ���ؼ���Ϊk�Ľ��
	LZW* s, * temp;
	if (p != NULL)
		if (k < p->NO)//��û�ҵ�p
			Delete(k, p->lchild);//�ݹ����p����������ɾ���ؼ���Ϊk�Ľ��
		else if (k > p->NO)
			Delete(k, p->rchild);//�ݹ����p����������ɾ���ؼ���Ϊk�Ľ��
		else if (p->lchild != NULL && p->rchild != NULL) {//�ҵ�p,����p���������������� 
			//s = Min(p->rchild);
			temp = p->rchild;
			while (temp->lchild != NULL) {
				temp = temp->lchild;
			}//�ҵ�p������������С����s���滻��p��Ȼ��ɾ��s
			s = temp;
			p->NO = s->NO;//��p�滻��s
			Delete(s->NO, p->rchild);//�ݹ��ɾ��s
		}
		else {//����ҵ�,���������Ϊ��
			temp = p;
			if (p->lchild == NULL)       p = p->rchild;//�������գ���p�滻Ϊ�������ϵ�һ�����
			else if (p->rchild == NULL)  p = p->lchild;//�������գ���p�滻Ϊ�������ϵ�һ�����
			delete temp;
		}
}

