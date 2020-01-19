#include<iostream>
#include <time.h>
//#include"DATHUC.h"
#include<fstream>
using namespace std;
#define e 0.0001
class DATHUC
{
public:
	int n;
	float* heso;
public:
	DATHUC();
	DATHUC(int b, float hs[]);
	DATHUC(const DATHUC& dt);
	~DATHUC();
	friend ostream& operator << (ostream&, DATHUC&);
	friend istream& operator >> (istream&, DATHUC&);
	float operator[] (int) const;
	float operator() (float i) const;
};
DATHUC::DATHUC()
{
	this->n = -1;
	this->heso = NULL;
}

DATHUC::DATHUC(int b, float hs[])
{
	this->n = b;
	this->heso = new float[b + 1];
	for (int i = 0; i <= n; i++)
	{
		this->heso[i] = hs[i];
	}
}

DATHUC::DATHUC(const DATHUC& dt)
{
	this->n = dt.n;
	this->heso = new float[n + 1];
	for (int i = 0; i <= n; i++)
	{
		this->heso[i] = dt[i];
	}
}

DATHUC::~DATHUC()
{
	delete[] heso;
}

float DATHUC::operator[](int i) const
{
	if (i >= 0 && i <= n)
		return heso[i];
	return 0.0f;
}

float DATHUC::operator()(float x) const
{
	float tam = heso[0];
	int i;
	for (i = 1; i <= n; i++)
		tam = tam * x + heso[i];
	return tam;
}

ostream& operator<<(ostream& o, DATHUC& dt)
{

	for (int i = 0; i < dt.n; i++)
	{
		if (0.0f != dt[i])
		{
			o << dt[i] << "x^" << dt.n - i;
			if (dt[i + 1] > 0)
				o << " +";
			else
				o << " ";
		}
	}
	o << dt[dt.n];
	return o;
}

istream& operator>>(istream& in, DATHUC& dt)
{

	cout << "Nhap bac da thuc:";
	in >> dt.n;
	if (dt.heso)
		delete[] dt.heso;
	dt.heso = new float[dt.n + 1];
	for (int i = 0; i <= dt.n; i++)
	{
		cout << "Nhap he so bac" << i << ":";
		in >> dt.heso[i];
	}
	return in;
}

void Menu();
float Fabs(float temp);
float ppdaycung(DATHUC& f, float a, float b);
bool Nhapkhoangnghiem(DATHUC& f, float& a, float& b);
void randomfloat(DATHUC& dt);
void randomint(DATHUC& dt);
float rdfloat(float min, float max);
int rdint(int min, int max);
float tronso(float x);
int main()
{
	float a, b, x;
	int chose;
	bool kt = false;
	DATHUC f;
	int lc, tt;
	do {
		Menu();
		ofstream file2("C:\\Users\\Admin\\Desktop\\output.txt", ios_base::app);
		do {
			cout << "Nhap lenh ban muon thuc hien: ";
			cin >> lc;
			switch (lc)
			{
			case 1:
			{
				cout << endl << "----->Lay du lieu tu File.txt" << endl;
				ifstream file1;
				file1.open("C:\\Users\\Admin\\Desktop\\input.txt");
				file1 >> f.n;
				//cout << f.n;
				if (f.heso)
					delete[] f.heso;
				f.heso = new float[f.n + 1];
				for (int i = 0; i <= f.n; i++)
				{
					file1 >> f.heso[i];
				}
				cout << "Phuong trinh la : ";
				cout << f << endl;
				file1.close();
				do
				{
					if (Nhapkhoangnghiem(f, a, b) == false) cout << "\n----->Khong tim dc nghiem!!" << endl;
					else
					{
						kt = true;
						x = ppdaycung(f, a, b);
						cout << "Nghiem la: " << x << endl;
						file2 << "Nghiem la: " << x << endl;
					}
					fflush(stdin);
					cout << "Tiep tuc nhap khoang nghiem ? " << endl << "yes(1), no(0): ";
					cin >> tt;
				} while (tt == 1);
				if (kt == false) file2 << "Khong tim thay nghiem!!!" << endl;
				break;
			}
			case 2:
			{
				cout << "\n----->Tao bo so ngau nhien!!!" << endl;
				cout << "Nhap lua chon tiep theo:" << endl;
				cout << "1.Bo so thuc ngau nhien." << endl;
				cout << "2.Bo so nguyen ngau nhien." << endl;
				int chose;
				do {
					cout << "Lua chon cua ban la: ";
					cin >> chose;
					if ((chose != 1) && (chose != 2))
					{
						cout << "Ban da nhap sai lenh!!" << endl << "Hay nhap lai!!";
						cout << endl << endl;
					}
				} while ((chose != 1) && (chose != 2));
				cout << "Nhap bac cua phuong trinh: "; cin >> f.n;
				if (chose == 1) randomfloat(f);
				else randomint(f);
				cout << f;
				do
				{
					if (Nhapkhoangnghiem(f, a, b) == false) cout << "\n----->Khong tim dc nghiem!!" << endl;
					else
					{
						kt = true;
						x = ppdaycung(f, a, b);
						cout << "Nghiem la: " << x << endl;
						file2 << "Nghiem la: " << x << endl;
					}
					fflush(stdin);
					cout << "Tiep tuc nhap khoang nghiem ? " << endl << "yes(1), no(0): ";
					cin >> tt;
				} while (tt == 1);
				if (kt == false) file2 << "Khong tim thay nghiem!!!" << endl;
				break;
			}
			case 3:
			{
				cout << "\n----->Nhap du lieu tu ban phim!!\n";
				cin >> f;
				cout << f << endl;
				do
				{
					if (Nhapkhoangnghiem(f, a, b) == false) cout << "\n---->Khong tim dc nghiem!!" << endl;
					else
					{
						kt = true;
						x = ppdaycung(f, a, b);
						cout << "Nghiem la: " << x << endl;
						file2 << "Nghiem la: " << x << endl;
					}
					fflush(stdin);
					cout << "Tiep tuc nhap khoang nghiem ? " << endl << "yes(1), no(0): ";
					cin >> tt;
				} while (tt == 1);
				if (kt == false) file2 << "Khong tim thay nghiem!!!" << endl;
				break;
			}
			case 4:
			{
				cout << "Xin cam on!!" << endl;
				break;
			}
			} //file2.close();
			if ((lc != 1) && (lc != 2) && (lc != 3) && (lc != 4))
				cout << "Ban da nhap sai lenh!!!" << endl << "Ban can nhap lai!!" << endl << endl;
		} while ((lc != 1) && (lc != 2) && (lc != 3) && (lc != 4));
		for (int i = 0; i <= 20; i++) cout << "**";
		cout << "\nBan co muon thuc hien lenh khac khong???" << endl;
		cout << "1.Co" << endl << "2.Ko" << endl;
		cout << "Nhap lenh ban muon thuc hien: ";
		cin >> chose;
		if (chose == 1) { system("cls"); cin.ignore(); }
	} while (chose == 1);

	system("pause");
	return 0;
}
void Menu()
{
	for (int i = 1; i < 7; i++) cout << " ";
	cout << "DO AN CO SO\n";
	for (int i = 0; i <= 20; i++) cout << "**"; cout << "\n";
	cout << "Ten: Nguyen Ba Huy\n     Nguyen Quang Huy\n";
	cout << "Nhom: 18NH13\n";
	cout << "De tai: 203\n";
	cout << "--->Tim nghiem da thuc:\nP(x)=f(x) = a0*x^n + a1*x^(n-1) + ... + a(n-1)*x + an\n(Phuong phap day cung)\n";
	cout << endl;
	for (int i = 1; i < 15; i++) cout << "**"; cout << endl;
	cout << "Nhap cac so cua lenh ma ban muon thuc hien: \n";
	cout << "1. Lay du lieu tu File.\n";
	cout << "2. Tao ngau nhien.\n";
	cout << "3. Nhap tu ban phim.\n";
	cout << "4. Thoat.\n";
	for (int i = 0; i <= 20; i++) cout << "**"; cout << "\n";
}
float Fabs(float temp)
{
	if (temp >= 0) return temp;
	else return (-temp);
}
float ppdaycung(DATHUC& f, float a, float b)
{
	if ((f(a) == 0) || (f(b) == 0))
	{
		if (f(a) == 0) return a;
		else return b;
	}
	else {
		float x;
		x = a - (b - a) * f(a) / (f(b) - f(a));
		if (f(x) * f(a) < 0)
		{
			do
			{
				b = x;
				x = a - (b - a) * f(a) / (f(b) - f(a));
			} while (Fabs(x - b) > e);
		}
		else
		{
			do
			{
				a = x;
				x = a - (b - a) * f(a) / (f(b) - f(a));
			} while (Fabs(x - a) > e);
		}
		return x;
	}
}
bool Nhapkhoangnghiem(DATHUC& f, float& a, float& b)
{
	cout << endl;
	for (int i = 0; i <= 20; i++) cout << "**";
	cout << endl;
	int dem = 1;
	fflush(stdin);
	do {
		do {
			cout << endl;
			cout << "Nhap khoang nghiem (a,b)!!! " << endl;
			cout << "Nhap a: "; cin >> a;
			cout << "Nhap b: "; cin >> b;
			if (a > b) cout << "Ban phai nhap a<b !!!" << endl;
		} while (a > b);
		if (f(a) * f(b) > 0) {
			cout << "Khoang Nghiem khong hop le!!!" << endl;
			dem++;
		}
	} while ((dem <= 5) && (f(a) * f(b) > 0));
	if (dem > 5) return false;
	else return true;
}
void randomfloat(DATHUC& dt)
{
	if (dt.heso)
		delete[] dt.heso;
	dt.heso = new float[dt.n + 1];
	for (int i = 0; i <= dt.n; i++)
	{
		dt.heso[i] = rdfloat(-5.5, 5);
		dt.heso[i] = tronso(dt.heso[i]);
	}
}
void randomint(DATHUC& dt)
{
	if (dt.heso)
		delete[] dt.heso;
	dt.heso = new float[dt.n + 1];
	for (int i = 0; i <= dt.n; i++)
	{
		dt.heso[i] = rdint(-5, 5);
	}
}
float rdfloat(float min, float max)
{
	float scare = rand() / (float)RAND_MAX;
	return min + scare * (max - min);
}
float tronso(float x)
{
	int y = (int)x;
	x -= y;
	if (x > 0) x = x * 1000 + 0.5;
	else x = x * 1000 - 0.5;
	x = (int)x;
	x /= 1000;
	x = x + y;
	return x;
}
int rdint(int min, int max)
{
	int r;
	r = min + rand() % (max - min + 1);
	return r;
}