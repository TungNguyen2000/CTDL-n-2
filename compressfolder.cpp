#include"compressfolder.h"


using namespace std;

int fo_count = 0;
Node**fo_Arr;
Node*fo_root;
int fo_frequency[300] = { 0 };

string getfoldername(string path)
{
	string result;
	string t = path;
	if (t[t.size() - 1] == '*')
	{
		t.erase(t.end() - 1);
	}

	if (t[t.size() - 1] == '/')
		t.erase(t.end() - 1);
	if (t[t.size() - 1] == '/')
		t.erase(t.end() - 1);

	int dem = 0;
	for (int i = t.size() - 1; i >= 0; i--)
	{
		if (t[i] == '/')
			return result;
		result = t[i] + result;
	}
	return result;
}

vector<entry> readfolder(string pathname)
{
	vector<entry> out;
	string data, temp = pathname;
	HANDLE hfile;
	WIN32_FIND_DATAA data02;
	if (temp[temp.size() - 1] != '*')
		temp += "*";
	hfile = FindFirstFileA(temp.c_str(), &data02);
	temp.erase(temp.end() - 1);
	if (hfile != INVALID_HANDLE_VALUE)
	{
		do {
			data = temp + data02.cFileName;
			string extension = data.substr(data.size() - 3, data.size() - 1);
			if (extension == "txt")
			{
				entry in(data);
				out.push_back(in);
			}
			data = "";
		} while (FindNextFileA(hfile, &data02));
		FindClose(hfile);
	}
	return out;
}

void fo_SortNodeArr() {
	for (int i = 0; i < fo_count - 2; i++) {
		for (int j = fo_count - 2; j > i; j--) {
			if (fo_Arr[j]->data < fo_Arr[j + 1]->data)
			{
				Node* temp = fo_Arr[j];
				fo_Arr[j] = fo_Arr[j + 1];
				fo_Arr[j + 1] = temp;
			}
		}
	}
}


Node* folder_CreateTree()
{

	while (fo_count > 1) {
		Node* temp = new Node;
		temp->data = fo_Arr[fo_count - 2]->data + fo_Arr[fo_count - 1]->data;
		temp->left = fo_Arr[fo_count - 2];
		temp->right = fo_Arr[fo_count - 1];

		fo_count--;

		fo_Arr[fo_count - 1] = temp;

		if (fo_count == 1) { return temp; }
		fo_SortNodeArr();
	}

}

void fo_createNodeArr() {
	fo_count = 0;
	for (int i = 0; i < 128; i++) {
		if (fo_frequency[i] != 0) { fo_count++; }
	}
	fo_Arr = new Node *[fo_count];


	int j = 0;
	for (int i = 0; i < 128; i++) {
		if (fo_frequency[i] != 0) {
			Node* n = new Node;
			n->data = i;
			n->freq = fo_frequency[i];
			fo_Arr[j] = n;
			j++;
		}
	}
	fo_SortNodeArr();
}

void fo_readFile(ifstream &file) {
	
	while (!file.eof())
	{
		char c;
		c = file.get();
		if (c == -1) { break; }

		fo_frequency[(int)c]++;
	}
}

int fo_findinNodeArr(char c) {
	for (int i = 0; i < fo_count; i++) {
		if (c == fo_Arr[i]->data) { return i; }
	}
	return -1;
}

void fo_ExportEncodeFile(ifstream &fin, ofstream &fout) {
	
	string temp;


	bool flag = true;
	while (1) {
		while (1)
		{
			if (temp.size() > 100) { break; }
			int i = 0;
			int c;
			c = fin.get();

			if (c == EOF) { flag = false; break; }

			//ifile.get
			int k = fo_findinNodeArr(c);
			if (k == -1) { break; }
			temp += fo_Arr[k]->code;
			i++;
		}

		if (flag == false) { break; }

	}
	stringstream geek(temp);
	int n;
	geek >> n;
	char c = BintoDec(n);
	fout << c << "| ";
}

void fo_EncodeNode(Node* p) {
	if (p->left != nullptr) {
		p->left->code = p->code + "0";
		fo_EncodeNode(p->left);
	}
	if (p->right != nullptr) {
		p->right->code = p->code + "1";

		fo_EncodeNode(p->right);
	}
}

void fo_ReCreateNodeArr(Node* p, int flag)
{
	if (p == nullptr) { return; }

	if (flag == 1) { fo_count = 0; }
	if (p->isEndNode()) {
		fo_Arr[fo_count++] = p;
	}

	fo_ReCreateNodeArr(p->left);
	fo_ReCreateNodeArr(p->right);

}


void compressfolder(string filename, string fileout)
{
	vector<entry> vec = readfolder(filename);
	string result = fileout + ".binf";
	int n = vec.size();
	ofstream re; re.open(result, ios::out|ios::binary);
	re << n << " ";
	re << getfoldername(filename) << "| ";

	for (int i = 0; i < n; i++)
	{
		fo_frequency[300] = { 0 };
		fo_Arr = NULL;
		fo_root = NULL;
		fo_count = 0;
		
		string temp1 = vec[i].filename;

		ifstream fin; 
		fin.open(temp1, ios::in);

		fo_readFile(fin);
		fo_createNodeArr();
		fo_SortNodeArr();
		fo_root = folder_CreateTree();
		fo_EncodeNode(fo_root);
		fo_ReCreateNodeArr(fo_root, 1);

		re << getfoldername(temp1) << "| ";
		fo_ExportEncodeFile(fin, re);
		fin.close();
	}
	re.close();
}

void folder_decompression(string filein)
{
	ifstream fi(filein, ios::binary);
	char c;
	int n;
	fi >> n; 
	string filename;
	do {
		c = fi.get();
		filename += c;
	} while (c != '|');
	filename = filename.substr(0, filename.size() - 1);
	string pathname = filein.substr(0,filein.size() - getfoldername(filein).size());
	pathname += filename;
	_mkdir(pathname.c_str()); 
	for (int i = 0; i < n; i++)
	{
		string s1,out,s2;
		do {
			c = fi.get();
			s1 += c;
		} while (c != '|');
		s1.erase(s1.end() - 1);
		ofstream temp(pathname + "//" + s1, ios::out);
		cout << pathname + "//" + s1 << endl;
		do {
			c = fi.get();
			s2 += c;
		} while (c != '|');
		s2.erase(s2.end() - 1);

		for (int j = 0; j < s2.size(); j++)
			out += ChartoBinaryString(s2[j]);
		char c = GetaChar(out);
		temp.close();
	}
	fi.close();
}