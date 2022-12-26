#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<cctype>
#include<algorithm>
#include<cmath>
#include<vector>
#include<ctime>
#pragma warning(disable:4996)
#define N 200
#define M 2*N-1
#define TOLOWER(p) {transform(p.begin(),p.end(),p.begin(),::tolower);}
typedef char* HuffmanCode[2 * M];//haffman����
//typedef long long LL;
using namespace std;
char x[1024];//�γ̱���
char y[1024];//huff����
fstream in("in3.txt");
fstream out("out3.txt");

void run_encode(char a[1024])//�γ̱���
{
	char yc[1024];
	int i = 0, j = 0, jishu = 1;
	yc[0] = a[0];
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == a[i + 1])
			jishu++;
		else
		{
			yc[j + 1] = jishu + 48;
			j = j + 2;
			yc[j] = a[i + 1];
			jishu = 1;
		}
	}
	yc[j] = '\0';
	cout << "�γ̱����" << yc << endl;
	strcpy_s(x, yc);
}
void run_decode(char a[1024])//�γ�����
{
	char jieya[1024];
	int j, jishu, bz = 0;
	for (int i = 0; a[i] != '\0'; i = i + 2)
	{
		jieya[bz] = a[i];
		for (j = bz, jishu = 1; jishu <= a[i + 1] - 48; jishu++, j++)
			jieya[j] = a[i];
		bz = j;
	}
	jieya[j] = '\0';
	cout << "�γ������" << jieya << endl;
	out << "�γ������" << jieya << endl;
}
typedef struct//�������������ݽṹ����
{
	int weight;//Ȩֵ
	int parent;//���ڽڵ�
	int LChild;//���ӽڵ�
	int RChild;//���ӽڵ�
}HTNode, Huffman[M + 1];//huffman��
typedef struct Node
{
	int weight; //Ҷ�ӽ���Ȩֵ
	char c; //Ҷ�ӽ��
	int num; //Ҷ�ӽ��Ķ�������ĳ���
}WNode, WeightNode[N];

void CreateWeight(char ch[], int* s, WeightNode CW, int* p)//����Ҷ�ӽ����ַ���Ȩֵ
{
	int i, j, k;
	int tag;
	*p = 0;//Ҷ�ӽڵ����
		   //ͳ���ַ����ָ���,����CW
	for (i = 0; ch[i] != '\0'; i++)
	{
		tag = 1;
		for (j = 0; j < i; j++)
			if (ch[j] == ch[i])
			{
				tag = 0;
				break;
			}
		if (tag)
		{
			CW[++ * p].c = ch[i];
			CW[*p].weight = 1;
			for (k = i + 1; ch[k] != '\0'; k++)
				if (ch[i] == ch[k])
					CW[*p].weight++;//Ȩֵ�ۼ�
		}
	}
	*s = i;//�ַ�������
}

void CreateHuffmanTree(Huffman ht, WeightNode w, int n)//������������
{
	int i, j;
	int s1, s2;
	//��ʼ����������
	for (i = 1; i <= n; i++)
	{
		ht[i].weight = w[i].weight;
		ht[i].parent = 0;
		ht[i].LChild = 0;
		ht[i].RChild = 0;
	}
	for (i = n + 1; i <= 2 * n - 1; i++)
	{
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].LChild = 0;
		ht[i].RChild = 0;
	}
	for (i = n + 1; i <= 2 * n - 1; i++)
	{
		for (j = 1; j <= i - 1; j++)
			if (!ht[j].parent)
				break;
		s1 = j; //�ҵ���һ��˫��Ϊ��Ľ��
		for (; j <= i - 1; j++)
			if (!ht[j].parent)
				s1 = ht[s1].weight > ht[j].weight ? j : s1;
		ht[s1].parent = i;
		ht[i].LChild = s1;
		for (j = 1; j <= i - 1; j++)
			if (!ht[j].parent)
				break;
		s2 = j; //�ҵ��ڶ���˫��Ϊ��Ľ��
		for (; j <= i - 1; j++)
			if (!ht[j].parent)
				s2 = ht[s2].weight > ht[j].weight ? j : s2;
		ht[s2].parent = i;
		ht[i].RChild = s2;
		ht[i].weight = ht[s1].weight + ht[s2].weight;//Ȩֵ�ۼ�
	}
}

void CrtHuffmanNodeCode(Huffman ht, char ch[], HuffmanCode h, WeightNode weight, int m, int n)//��Ҷ�ӽ�����
{
	int i, c, p, start;
	char* cd;
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';//����ĩβ
	for (i = 1; i <= n; i++)
	{
		start = n - 1; //cd��ÿ�δ�ĩβ��ʼ
		c = i;
		p = ht[i].parent;//p��n+1��n-1
		while (p) //�ظ��׷������,ֱ��Ϊ
		{
			start--;//������ǰ��ֵ
			if (ht[p].LChild == c)//��������ͬ,��
				cd[start] = '0';
			else//������
				cd[start] = '1';
			c = p;
			p = ht[p].parent;
		}
		weight[i].num = n - start; //��������ĳ���(����ĩβ)
		h[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(h[i], &cd[start]);//���������ַ���������ָ������h��
	}
	free(cd);//�ͷ�cd�ڴ�
	//system("pause");
}

void CrtHuffmanCode(char ch[], HuffmanCode h, HuffmanCode hc, WeightNode weight, int n, int m)//�������ַ��ı���
{
	int i, k;
	for (i = 0; i < m; i++)
	{
		for (k = 1; k <= n; k++) /*��weight[k].c�в�����ch[i]��ȵ��±�K*/
			if (ch[i] == weight[k].c)
				break;
		hc[i] = (char*)malloc((weight[k].num) * sizeof(char));
		strcpy(hc[i], h[k]); //���������Ʊ���
	}
}

void TrsHuffmanTree(Huffman ht, WeightNode w, HuffmanCode hc, int n, int m)//������������
{
	int i = 0, j, p;
	while (i < m)
	{
		p = 2 * n - 1;//�Ӹ��׽ڵ����±���ֱ��Ҷ�ӽڵ�
		for (j = 0; hc[i][j] != '\0'; j++)
		{
			if (hc[i][j] == '0')
				p = ht[p].LChild;
			else
				p = ht[p].RChild;
		}
		printf("%c", w[p].c); /*��ӡԭ��Ϣ*/
		out << w[p].c;
		i++;
	}
	out << endl;
}

void FreeHuffmanCode(HuffmanCode h, HuffmanCode hc, int n, int m)//����������ʹ�����֮���ͷ�huffman�����ڴ�
{
	int i;
	for (i = 1; i <= n; i++)//�ͷ�Ҷ�ӽ��ı���
		free(h[i]);
	for (i = 0; i < m; i++) //�ͷ����н��ı���
		free(hc[i]);
}
int n; //nΪҶ�ӽ��ĸ���
int m; //mΪ�ַ���ch[]�ĳ���
Huffman ht; //Huffman������
HuffmanCode h, hc; //h���Ҷ�ӽ��ı��룬hc ������н��ı���
WeightNode weight; //���Ҷ�ӽ�����Ϣ
void huffman_encode(char* ch)
{
	n = 0;
	int i;
	m = 0;
	printf("\t***HuffmanCoding***\n");
	CreateWeight(ch, &m, weight, &n); /*����Ҷ�ӽ����Ϣ��mΪ�ַ���ch[]�ĳ���
									  */
									  /*printf("***WeightInformation***\n Node ");
									  for (i = 1; i <= n; i++) //���Ҷ�ӽ����ַ���Ȩֵ
										  printf("%c ", weight[i].c);
									  printf("\nWeight ");
									  for (i = 1; i <= n; i++)
										  printf("%d ", weight[i].weight);*/
	CreateHuffmanTree(ht, weight, n); //����Huffman��
	/*printf("\n***HuffamnTreeInformation***\n");
	printf("\ti\tweight\tparent\tLChild\tRChild\n");
	for (i = 1; i <= 2 * n - 1; i++) //��ӡHuffman������Ϣ
		printf("\t%d\t%d\t%d\t%d\t%d\n", i, ht[i].weight, ht[i].parent, ht[i].LChild, ht[i].RChild);*/
	CrtHuffmanNodeCode(ht, ch, h, weight, m, n); //Ҷ�ӽ��ı���
	/*printf(" ***NodeCode***\n"); //��ӡҶ�ӽ��ı���
	for (i = 1; i <= n; i++)
	{
		printf("\t%c:", weight[i].c);
		printf("%s\n", h[i]);
	}*/
	CrtHuffmanCode(ch, h, hc, weight, n, m); /*�����ַ��ı���*/
	printf("Huffman�����"); /*��ӡ�ַ����ı���*/
	for (i = 0; i < m; i++)
	{
		printf("%s", hc[i]);
		strcpy(&y[i], hc[i]);
	}
	//system("pause");
}
void huffman_decode()
{
	cout << "huffman�����";
	TrsHuffmanTree(ht, weight, hc, n, m); //����
	FreeHuffmanCode(h, hc, n, m);
	cout << endl;
	//system("pause");
}
string BinStrToHexStr(string str)//�����ǽ��������������Ķ������ַ���ת��Ϊʮ�����ƣ�����base64����
{
	string str_Hex = "";
	string temp_Hex = "";
	int iHex = 0;
	if (str.size() % 4 != 0)
	{
		int num = 4 - (str.size() % 4);
		for (int i = 0; i < num; i++)
		{
			str = "0" + str;
		}
	}
	for (int i = 0; i < str.size(); i += 4)
	{
		iHex = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;
		if (iHex >= 10)
		{
			int left = iHex % 16;
			temp_Hex = 'A' + left - 10;
		}
		else
		{
			temp_Hex = to_string(iHex);
		}
		str_Hex += temp_Hex;
	}
	return str_Hex;
}
string HexStrToBinStr(string str)//base64����֮���ʮ������ת�ɶ����Ʒ������������
{
	string str_Bin = "";
	int iDec = 0;
	TOLOWER(str);
	sscanf_s(str.c_str(), "%x", &iDec);
	vector<int>vec_remder;
	int remder = 0;
	while (iDec / 2 != 0)
	{
		remder = iDec % 2;
		vec_remder.push_back(remder);
		iDec /= 2;
	}
	remder = iDec % 2;
	vec_remder.push_back(remder);
	reverse(vec_remder.begin(), vec_remder.end());
	for (int i = 0; i < vec_remder.size(); i++)
	{
		str_Bin += to_string(vec_remder[i]);
	}
	return str_Bin;
}


string deciToBin_8bit(int deci) //ʮ����ת�����ƣ���λ�����ƣ�
{
	string hexStr(8, ' ');
	int Value = 0;
	int i = 0;
	for (; deci != 0; ++i, deci /= 2)
	{
		Value = deci % 2;
		hexStr.at(i) = Value + '0';
	}
	hexStr = hexStr.substr(0, i);
	reverse(hexStr.begin(), hexStr.end());
	if (hexStr.length() < 8)
	{
		string add(8 - hexStr.length(), '0');
		hexStr = add + hexStr;
	}
	return hexStr;
}
string deciToBin_6bit(int deci)//10����ת2���ƺ�����6λ��
{
	string hexStr(6, ' ');
	int Value = 0;
	int i = 0;
	for (; deci != 0; ++i, deci /= 2)
	{
		Value = deci % 2;
		hexStr.at(i) = Value + '0';
	}
	hexStr = hexStr.substr(0, i);
	reverse(hexStr.begin(), hexStr.end());
	if (hexStr.length() < 6)
	{
		string add(6 - hexStr.length(), '0');
		hexStr = add + hexStr;
	}
	return hexStr;
}
string base64_encode(const string in)
{
	int i = 0, k = 0;//i�ܱ��� k24λ���Ʊ���
	const int n = in.length();
	string subs;//����Ӵ�
	string out;//���
	string value("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
	while (n - i >= 24)
	{
		for (k = 0; k < 4; ++k)
		{
			subs = in.substr(i + k * 6, 6);
			int sum = 0;
			int j = 0;
			for (auto& x : subs)
			{
				sum += (x - '0') * pow(2, 5 - j);
				++j;
			}
			out += value.at(sum);
		}
		i += 24;
		if (i % 76 == 0)cout << endl;
	}
	if (i != n)//����ʣ�µĲ���24λ����
	{
		int charlen;  //ʣ�µĳ���
		if ((n - i) % 6 == 0)charlen = (n - i) / 6;
		else charlen = (n - i) / 6 + 1;
		for (k = 0; k < charlen; ++k)
		{
			subs = in.substr(i + k * 6, i + (k + 1) * 6 - 1);  //ȡ��6λ

			int sum = 0;
			int j = 0;

			for (auto& x : subs)
			{
				sum += (x - '0') * pow(2, 5 - j);
				++j;
			}     //�õ��±�                                                                       

			out += value.at(sum); //�����Ӧ�ַ�
		}
		if ((n - i) % 16 == 0)out += "=";
		else out += "==";
	}
	return out;
}
string base64_decode(const string in)
{
	string value("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
	string out0;
	string out1;
	string deciToBin_6bit(int);
	for (auto x = in.cbegin(); (*x) != '=' && x != in.cend(); ++x)    //�ų��Ⱥ�
		out0 += deciToBin_6bit(value.find(*x));
	const int n = out0.length();
	for (int i = 0; i < n; i += 8)           //ÿ8λ��ȡһ��
	{
		string subs = out0.substr(i, 8);    //��ȡ8λ
		int j = 0;
		int sum = 0;
		for (auto& x : subs)
		{
			sum += (x - '0') * pow(2, 7 - j);
			++j;
		}                                   //��Ȩչ�����õ�ASCII��
		out1 += static_cast<char>(sum);     //ת��Ϊ��Ӧ�ַ�
	}
	return out1;
}


int G[4][3];//�����Ǳ�׼���ɾ�������ʡ����ǰ���еĵ�λ��,�˾���4��3��
string S[8][16];//��������������ڣ�7��4��ϵͳѭ������С���d=3����������t=1����������ֻ��8��

void create_G()
{
	//��ʼ�����ɾ���ͬʱ���������ת��Ϊ�ල��
	G[0][0] = 1; G[0][1] = 0; G[0][2] = 1;//��һ��  1 0 1
	G[1][0] = 1; G[1][1] = 1; G[1][2] = 1;//�ڶ���  1 1 1
	G[2][0] = 1; G[2][1] = 1; G[2][2] = 0;//������  1 1 0
	G[3][0] = 0; G[3][1] = 1; G[3][2] = 1;//������  0 1 1

}
void create_S()
{
	//��ʼ��������һ��,��һ�ж�Ϊ��������
	S[0][0] = "0000000"; S[0][1] = "1111111"; S[0][2] = "0001011"; S[0][3] = "0010110";
	S[0][4] = "0101100"; S[0][5] = "1011000"; S[0][6] = "0110001"; S[0][7] = "1100010";
	S[0][8] = "1000101"; S[0][9] = "0011101"; S[0][10] = "0111010"; S[0][11] = "1110100";
	S[0][12] = "1101001"; S[0][13] = "1010011"; S[0][14] = "0100111"; S[0][15] = "1001110";
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 16; j++)//ѭ���������п��Ծ����ͼ��
		{
			int x = 0; string s = "", befor = "", after = "";
			befor = S[0][j].substr(0, i);
			after = S[0][j].substr(i + 1, (S[0][j].length()) - i - 1);
			s = S[0][j].substr(i, 1);
			x = stoi(s);//stringתint
			x = (x + 1) % 2;
			s = std::to_string(x);//intתstring

			S[i + 1][j] = befor + s + after;
		}
	}
}
int bin_to_deci(string inin)//�������ַ���ת10���ƣ���Ҫ��ʹ�ŵ�����֮����ַ������ASCII����ַ���������ת��Ϊbase64����
{

	int len = inin.length();
	int n = 0;
	for (int i = 0; i < len; ++i)
	{
		//����ע��if���ж�����������ȵķ���
		if (inin.substr(i, 1) == "1")
			n += pow(2, len - 1 - i);
	}
	return n;
}


string channel_encode(string infomation)//�ŵ����룬�����infomation��8λ������
{
	string info, e_info = "", v1, v2, v3, v4;
	int n1 = 0, n2 = 0, n3 = 0;

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)info = infomation.substr(0, 4);
		if (i == 1)info = infomation.substr(4, 4);

		v1 = info.substr(0, 1);
		v2 = info.substr(1, 1);
		v3 = info.substr(2, 1);
		v4 = info.substr(3, 1);
		if (v1 == "1") { n1 += G[0][0]; n2 += G[0][1]; n3 += G[0][2]; }
		if (v2 == "1") { n1 += G[1][0]; n2 += G[1][1]; n3 += G[1][2]; }
		if (v3 == "1") { n1 += G[2][0]; n2 += G[2][1]; n3 += G[2][2]; }
		if (v4 == "1") { n1 += G[3][0]; n2 += G[3][1]; n3 += G[3][2]; }

		n1 = n1 % 2; n2 = n2 % 2; n3 = n3 % 2;
		v1 = std::to_string(n1); v2 = std::to_string(n2); v3 = std::to_string(n3);
		e_info = e_info + info + v1 + v2 + v3;
		n1 = 0; n2 = 0; n3 = 0;
	}
	return e_info;//���14λ��Ҳ�����������ֺϲ�
}

string channel_decode(string infomation)//����14λ����������
{
	string info, de_info = "";

	for (int x = 0; x < 2; x++)
	{

		if (x == 0)info = infomation.substr(0, 7);
		if (x == 1)info = infomation.substr(7, 14);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (S[i][j] == info)
				{
					de_info += info.substr(0, 4);
					goto goon;
				}
			}

		}

	goon:;
	}
	return de_info;//8λ������������λ��ϢԴ��������λУ��λ�Ѿ�ɾȥ
}
string BSC(string infomation)//ģ��BSC�ŵ�����
{
	srand((int)time(0));
	string output = "", x;
	for (int i = 0; i < infomation.length(); i++)//һ���ַ�һ���ַ��ж�
	{
		x = infomation.substr(i, 1);
		if (x == "0")
		{
			if (1 == rand() % 100)//p=10�ĸ�2��
				x = "1";
			goto gon;//��ֹ�˴�x���¸�ֵΪ1����뵽��һ���ж�
		}
		if (x == "1")
		{
			if (1 == rand() % 100)//p=10�ĸ�2��
				x = "0";
			goto gon;
		}
	gon:output += x;
	}
	return output;
}
void string_to_ascii(string info, string a[])//��base64����ת��λASCII�뷽���ŵ�����
{
	string output = "", x;
	char c; int n;
	for (int i = 0; i < info.length(); i++)
	{
		c = info[i];
		n = (int)c;
		output = deciToBin_8bit(n);
		a[i] = output;
	}
}

int main()
{
	char s[1024];
	string input0;//��������
	string input1;//����������
	string bin;//ת���Ķ���������
	string hex;//ת����ʮ����������
	string deciToBin_8bit(int);//����������ʮ����ת������
	string base64_encode(const string);
	string base64_decode(const string);//base64����
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	while (!in.eof()) {
		in.getline(s, 1024);
		cout << s << endl;
		cout << endl;
		run_encode(s);
		out << "�γ̱����" << x << endl;
		cout << endl;
		huffman_encode(x);
		out << "Huffman�����" << y << endl;
		cout << endl;
		hex = BinStrToHexStr(y);//��תʮ��
		cout << "Bin_to_Hex:" << hex << endl;
		out << "Bin_to_Hex:" << hex << endl;
		cout << endl;
		input0 = hex;
		for (auto& x : input0)input1 += deciToBin_8bit(static_cast<int>(x));//����������
		string out0 = base64_encode(input1);
		cout << "base64���ܺ�" << out0 << endl;
		out << "base64���ܺ�" << out0 << endl;
		cout << endl;

		create_G();//���ɾ���
		create_S();//�����
		int lenth = out0.length();
		string* a = new string[lenth];
		string* output = new string[lenth];
		string_to_ascii(out0, a);//����ת��ΪASCII�봮
		string  output1 = "";
		//��ʵ����һ��ѭ������������й�������������ŵ�������ʱ��û�п�����������⣬����Ϊ������ŵ�����������Ľ��
		//ֻ�ܽ�һ��ѭ���������
		/*for (int i = 0; i < lenth; i++)
		{
			int f = 0;
			output[i] = channel_encode(a[i]);
			output[i] = BSC(output[i]);
			output[i] = channel_decode(output[i]);
			f = bin_to_deci(output[i]);
			output1 += (char)f;
		}*/

		cout << "�ŵ����룺";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = channel_encode(a[i]);//�ŵ�����
			cout << output[i];
		}
		cout << endl; cout << endl; cout << "ģ�⴫�ݴ���";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = BSC(output[i]);//�ŵ�����
			cout << output[i];
		}
		cout << endl; cout << endl; cout << "�ŵ����룺";
		for (int i = 0; i < lenth; i++)
		{
			output[i] = channel_decode(output[i]);//�ŵ�����
			cout << output[i];
			int f = 0;
			f = bin_to_deci(output[i]);//��������ת��ʮ����
			output1 += (char)f;//���ASCII���Ӧ���ַ�����base64������

		}cout << endl; cout << endl;




		string out1 = base64_decode(output1);
		cout << "base64���ܺ�" << out1 << endl;
		out << "base64���ܺ�" << out1 << endl;
		cout << endl;
		bin = HexStrToBinStr(out1);
		cout << "Hex_to_Bin:" << y << endl;
		out << "Hex_to_Bin:" << y << endl;
		cout << endl;
		strcpy(y, bin.c_str());
		out << "huffman�����";
		huffman_decode();
		cout << endl;
		run_decode(x);
	}
	in.close();
	out.close();
	return 0;
}
