#include "LZW.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
string Sequence[100], Sequence1[100];//�����洢������������
LZW* en_root,*de_root, * en_root1, * de_root1;//�������еı����������
fstream in("in2.txt");
fstream out("out2.txt");//���ļ�
int EN_word[100]; int en_num = 0;//����洢����������֣�en_numΪ������
int enword_num = 4,deword_num=4;//��¼���ֱൽ����

void encode(LZW* bt, string s[], int num)//sΪ������������飬numΪ��������еĳ���
{
	LZW* p = NULL,*q=NULL;
	int a = 0;//a����Դ����������±�ָ��
	string i =s[0];//Ĭ����Դ���еĵ�һ��������ֵ��i
	
	cout << "���������£�" << endl;
	out << "���������£�" << endl;
	while (1) 
	{
		p = find_for_word(i, bt);//�ڱ�������Ҵ���Ϊi��Ԫ�أ�����Ҳ����򷵻�p=NULL
		if (p != NULL)//�ҵ��˴���Ϊi�� ����
		{
			q = p;//��p�ĵ�ַ���棬�Ա��������
		
			a++;
			if (a == num)//��������е����е����һ��ʱ��ֱ�����
			{
				out << p->NO<<" ";
				cout << p->NO << " ";
				EN_word[en_num++]=p->NO;
				break;
			}
			i = i + s[a];//i�ͽ�������һ���������������������

		}
		else//�ڱ������û������������Ϊi�����֣�����Ҫ�����µ�����
		{   
			out << q->NO<<" ";//�ȰѾɵģ��Ѿ��ڱ�����е��������
			cout << q->NO << " ";
			EN_word[en_num++] = q->NO;//�����ֱ����ڱ��������У��Ա��������
			enword_num++;
			InserBST(bt, enword_num, i);//��ӵ��������
			i = s[a];//i��Ϊ���������һ����ĸ
			
		}
	}
	out << endl;
	cout << endl;
}

void decode(LZW* bt, int en_num)//����
{
	int a = 0;//�����±�ָ��
	LZW* p = NULL,*q=NULL;
	string i;
	cout << "���������£�" << endl;
	out << "���������£�" << endl;
goon:while (1)
{
	p = find_for_NO(EN_word[a], bt);//�ӱ����������ó���õ����֣���������в���
	if (p != NULL && a == 0)//��һ�����룬���ڱ��뷽�������ʣ���һ��һ�����ҵ�
	{
		out << p->word;
		cout << p->word << " ";
		i = p->word;
		de_root = InserBST(bt, ++deword_num, i);//�����µ����֣��ȰѲ�ȷ���Ĵ���i���룬����������
		a++;
		goto goon;
	}
	if (p != NULL && a != 0)//��2+��������
	{
		string k;
		out << p->word;
		cout << p->word << " ";//�Ƚ��鵽�Ĵ������
		i = p->word;
		k = i.substr(0, 1);//kȡ�����ĵ�һ����ĸ��������ȫ�������в�ȷ���Ĵ���
		q = find_for_NO(deword_num, de_root);//�ҵ������ֵ�λ��
		q->word = q->word + k;//��k�ӵ������ɹ���

		de_root = InserBST(bt, ++deword_num, i);//�ٴδ����µĴ��������ѭ��
		a++;

		if (a == en_num)break;



	}
	if (p == NULL)
	{
		cout << "�������"; break;
	}
}
out << endl;
cout << endl;
}

int main()
{
	
  
	
		cout << "������Ҫ����ķ������У�ͬʱ��@��β" << endl;
		int h = 0;//��Դ���г���
		while (1)//��Ҫ������ַ����뵽����S��
		{
			char cc;
			in >> cc;

			if (cc == '@')
				break;//���ԡ�@��Ϊ��β��ʱ������洢
			string x(1, cc);
			Sequence[h++] = x;
			cout << cc;
		}
		cout << endl;

		en_root = InserBST(en_root, 1, "a");//��ʼ�������ͱ����
		en_root = InserBST(en_root, 2, "b");
		en_root = InserBST(en_root, 3, "c");
		en_root = InserBST(en_root, 4, "d");

		de_root = InserBST(de_root, 1, "a");
		de_root = InserBST(de_root, 2, "b");
		de_root = InserBST(de_root, 3, "c");
		de_root = InserBST(de_root, 4, "d");

		encode(en_root, Sequence, h);
		decode(de_root, en_num);
		cout << endl;
		cout << "�ڶ������У�" << endl;
		//�ڶ������У��Ƚ���һ�������ù��ı�����ʼ��
        en_num = 0;
		enword_num = 4; deword_num = 4;
		cout << "������Ҫ����ķ������У�ͬʱ��@��β" << endl;
		 h = 0;//��Դ���г���
		while (1)//��Ҫ������ַ����뵽����S��
		{
			char cc;
			in >> cc;

			if (cc == '@')
				break;//���ԡ�@��Ϊ��β��ʱ������洢
			string x(1, cc);
			Sequence1[h++] = x;
			cout << cc;
		}
		cout << endl;

		en_root1 = InserBST(en_root1, 1, "a");
		en_root1 = InserBST(en_root1, 2, "b");
		en_root1 = InserBST(en_root1, 3, "c");
		en_root1 = InserBST(en_root1, 4, "d");

		de_root1 = InserBST(de_root1, 1, "a");
		de_root1 = InserBST(de_root1, 2, "b");
		de_root1 = InserBST(de_root1, 3, "c");
		de_root1 = InserBST(de_root1, 4, "d");

		encode(en_root1, Sequence1, h);
		decode(de_root1, en_num);
		
	
	//cout << "��������" << endl;
	//InOrder(en_root);
	//cout << "��������" << endl;
	//InOrder(de_root);
	return 0;
}
