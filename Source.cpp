#include "compressfile.h"
#include "compressfolder.h"
#include "app.h"
#include <conio.h>
using namespace std;

int main()
{
	while (1) {
		int flag = 0;
		int n = App();
		system("cls");
		switch (n)
		{
		case 1:
		{
			cout << "\nnen file .txt. " << endl << " Nhan r de thoat." << endl << "Nhap phim bat ki de tiep tuc" << endl;
			while (1)
			{
				if (_kbhit())
				{
					int h = _getch();
					if (h == 114)
						break;
					else {
						cout << "\n nhap file .txt can nen.";
						string s1; cin >> s1;
						cout << "\n nhap ten file nen.";
						string s2; cin >> s2;
						
						AnalysisFile(s1);
						ExportEncodeFile(s1, s2);
					}
					cout << "Nhap 0 de thoat !" << endl;
					cout << "Nhap 1 de hien Menu" << endl;
					int o;
					cin >> o;
					if (o == 0)
						break;
					else
						if (o == 1)
						{
							flag = 1;
							break;
						}
				}
			}
			if (flag)
			{
				flag = 0;
				continue;
			}
			break;
		}
		case 2:
		{
			cout << "\ngiai nen file .bin" << endl << " Nhan r de thoat." << endl << "Nhap phim bat ki de tiep tuc" << endl;
			while (1)
			{

				if (_kbhit())
				{
					int h = _getch();
					if (h == 114)
						break;
					else
					{
						cout << "nhap ten file can giai nen ";
						string s; cin >> s;
						Decompress(s);
					}
					cout << "Nhap 0 de thoat !" << endl;
					cout << "Nhap 1 de hien Menu" << endl;
				}
			}
			if (flag)
			{
				flag = 0;
				continue;
			}
			break;
		}
		case 3:
		{
			cout << "\nnen folder. " << endl << " Nhan r de thoat." << endl << "Nhap phim bat ki de tiep tuc" << endl;
			while (1)
			{
				if (_kbhit())
				{
					int h = _getch();
					if (h == 114)
						break;
					else {
						cout << "\nten folder can nen: ";
						string s; cin >> s;
						cout << "\n ten folder nen ra: ";
						string s1; cin >> s1;
						compressfolder(s, s1);
					}
				}
			}
			if (flag)
			{
				flag = 0;
				continue;
			}
			break;
		}
		
		case 4:
		{
			cout << "\ngiai nen file .binf " << endl << " Nhan r de thoat." << endl << "Nhap phim bat ki de tiep tuc" << endl;
			while (1)
			{
				if (_kbhit())
				{
					int h = _getch();
					if (h == 114)
						break;
					else {
						cout << "\nten file can giai nen: ";
						string s; cin >> s;
						folder_decompression(s);
					}
				}
			}
			if (flag)
			{
				flag = 0;
				continue;
			}
			break;
		}
		default:
			return 0;
		}
	}
	return 0;
}