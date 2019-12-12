#include "compressfile.h"

Node**Arr;
Node*root;
int frequency[300] = { 0 };
int Count = 0;

using namespace std;
string ChartoBinaryString(int c) {
	string s;
	for (int i = 0; i < 7; i++) {
		if (c % 2 == 1) { s = '1' + s; }
		else { s = '0' + s; }
		c /= 2;
	}
	return s;
}


char GetaChar(string &s) {
	for (int i = 0; i < Count; i++) {
		if (s.find(Arr[i]->code) == 0) {
			s = s.substr(Arr[i]->code.size());
			return Arr[i]->data;
		}
	}
}


void AnalysisFile(string filename) {
	readFile(filename);
	createNodeArr();
	SortNodeArr();
	root = CreateTree();
	EncodeNode(root);
	ReCreateNodeArr(root, 1);
}

Node* CreateTree() {

	while (Count > 1) {
		Node* temp = new Node;
		temp->data = Arr[Count - 2]->data + Arr[Count - 1]->data;
		temp->left = Arr[Count - 2];
		temp->right = Arr[Count - 1];

		Count--;

		Arr[Count - 1] = temp;

		if (Count == 1) { return temp; }
		SortNodeArr();
	}

}

void SortNodeArr() {
	for (int i = 0; i < Count - 2; i++) {
		for (int j = Count - 2; j > i; j--) {
			if (Arr[j]->data < Arr[j + 1]->data)
			{
				Node* temp = Arr[j];
				Arr[j] = Arr[j + 1];
				Arr[j + 1] = temp;
			}
		}
	}
}

void createNodeArr() {
	Count = 0;
	for (int i = 0; i < 128; i++) {
		if (frequency[i] != 0) { Count++; }
	}
	Arr = new Node *[Count];


	int j = 0;
	for (int i = 0; i < 128; i++) {
		if (frequency[i] != 0) {
			Node* n = new Node;
			n->data = i;
			n->freq = frequency[i];
			Arr[j] = n;
			j++;
		}
	}
	SortNodeArr();
}

void readFile(string filename) {
	ifstream file;
	file.open(filename, ios::in);
	while (!file.eof())
	{
		char c;
		c = file.get();
		if (c == -1) { break; }

		frequency[(int)c]++;
	}
}

void Decompress(string  filename) {
	ifstream file;
	file.open(filename, ios::binary);
	ofstream ofile;
	string fileout = filename.substr(0, filename.size() - 3) + "txt";
	ofile.open(fileout, ios::out);
	string s;
	while (!file.eof())
	{
		char c;
		c = file.get();
		if (c == EOF) { break; }


		s += ChartoBinaryString(c);
		c = GetaChar(s);
		ofile << c;

	}
}

int findinNodeArr(char c) {
	for (int i = 0; i < Count; i++) {
		if (c == Arr[i]->data) { return i; }
	}
	return -1;
}

void ExportEncodeFile(string filename, string fileoutname) {
	//for (int i = 0; i < Count; i++) {
		//cout << Arr[i]->code << "   " << Arr[i]->data << endl;
	//}
	string temp;
	ifstream ifile;
	ifile.open(filename, ios::in);

	ofstream ofile;
	ofile.open(fileoutname, ios::binary);


	bool flag = true;
	while (1) {
		while (1)
		{
			if (temp.size() > 100) { break; }
			int i = 0;
			int c;
			c = ifile.get();

			if (c == EOF) { flag = false; break; }

			//ifile.get
			int k = findinNodeArr(c);
			if (k == -1) { break; }
			temp += Arr[k]->code;
			i++;
		}

		if (flag == false) { break; }

	}
	stringstream geek(temp);
	int n;
	geek >> n;
	char c = BintoDec(n);
	ofile << c;
}

void EncodeNode(Node* p) {
	if (p->left != nullptr) {
		p->left->code = p->code + "0";
		EncodeNode(p->left);
	}
	if (p->right != nullptr) {
		p->right->code = p->code + "1";

		EncodeNode(p->right);
	}
}

int BintoDec(int n)
{
	int dec_value = 0;
	int base = 1;
	int temp = n;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;
		dec_value += last_digit * base;
		base = base * 2;
	}
	return dec_value;
}

void ReCreateNodeArr(Node* p, int flag) {
	if (p == nullptr) { return; }

	if (flag == 1) { Count = 0; }
	if (p->isEndNode()) {
		Arr[Count++] = p;
	}

	ReCreateNodeArr(p->left);
	ReCreateNodeArr(p->right);

}

