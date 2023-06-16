#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<vector>
using namespace std;
#define inf 2147483647
#define sqr(x) (x)*(x)
int toInt(string a)
{
	int p = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] >= '0' && a[i] <= '9')
		{
			p = 10 * p + (a[i] - '0');
		}
	}
	return p;
}
class City
{
	int num;							//���б��
	string name;						//��������
	int x, y;							//��������
public:
	City(int num1 = 0, string name1 = "δ��������", int a = 0, int b = 0)
	{
		num = num1;
		name = name1;
		x = a;
		y = a;
	}
	void show()
	{
		cout << left << setw(8) << num << setw(12) << name << setw(6) << x << setw(6) << y << endl;
	}
	void setNum(int n)
	{
		num = n;
	}
	void setName(string na)
	{
		name = na;
	}
	void setPosition(int xp, int yp)
	{
		x = xp, y = yp;
	}
	string getName()
	{
		return name;
	}
	int getNum()
	{
		return num;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
};
class Map
{
	City* cities;						//ָ�����Ա��ָ��
	int curCounter, maxCounter;			//���г��м�¼�������Ա���󳤶�
public:
	Map(int maxc = 200)
	{
		cities = new City[maxc];
		curCounter = 0;
		maxCounter = maxc;
	}
	Map(Map& m)
	{
		this->cities = m.cities;
		this->curCounter = m.curCounter;
		this->maxCounter = m.maxCounter;
	}
	~Map()
	{
		if (cities) delete[] cities;
	}
	double Dist(int x1, int y1, int x2, int y2)		//������м����
	{
		double d;
		d = sqrt(sqr(x1 - x2) + sqr(y1 - y2));
		return d;
	}
	void AddCity(int n, string na, int x, int y)	//���ӳ���
	{
		cities[curCounter].setNum(n);
		cities[curCounter].setName(na);
		cities[curCounter].setPosition(x, y);
		curCounter++;
	}
	void DeletCity(int num)			//ɾ������
	{
		for (int i = 0; i < curCounter; i++)
		{
			if (cities[i].getNum() == num)
			{
				char Bool = NULL;
				cout << "��ǰ����Ϊ��" << endl;
				cities[i].show();
				cout << "ȷ��ɾ���˳�����    ��(y) ��(n)" << endl;
				cin >> Bool;
				if (Bool == 'y')
				{
					curCounter--;
					for (int j = i; j < curCounter; j++)
					{
						cities[j] = cities[j + 1];
					}
					break;
				}
				else break;
			}
		}
	}
	void UpdCity(int num)			//�޸ĳ�����Ϣ
	{
		for (int i = 0; i < curCounter; i++)
		{
			if (cities[i].getNum() == num)
			{
				cout << "��ǰ����Ϊ��" << endl;
				cities[i].show();

				string na;
				int nu, x, y;
				cout << "�����������޸ĺ�ı�š����ƺ����꣺" << endl;
				cin >> nu >> na >> x >> y;

				char Bool = NULL;
				cout << "ȷ�ϸ��Ĵ˳�����Ϣ��    ��(y) ��(n)" << endl;
				cin >> Bool;
				if (Bool == 'y')
				{
					cities[i].setNum(nu);
					cities[i].setName(na);
					cities[i].setPosition(x, y);
					break;
				}
				else break;
			}
		}
	}
	void ShowAlCity()				//��ʾȫ��������Ϣ
	{
		if (curCounter)
		{
			cout << "��ǰ����������" << curCounter << endl;
			for (int i = 0; i < curCounter; i++)
			{
				cities[i].show();
			}
		}
		else
		{
			cout << "��ǰ�޳�����Ϣ��" << endl;
		}
	}
	bool AskCity(int num)		//��ѯ�����Ƿ����
	{
		bool tag = false;
		for (int i = 0; i < curCounter; i++)
		{
			if (num == cities[i].getNum())
			{
				tag = true;
			}
		}
		return tag;
	}
	void showCity(int i)
	{
		cities[i].show();
	}
	string GtCity(int num)
	{
		string hak;
		for (int i = 0; i < curCounter; i++)
		{
			if (cities[i].getNum() == num)
			{
				hak = cities[i].getName();
			}
		}
		return hak;
	}
	int GtCurCounter()				//��ȡ��ǰ��������
	{
		return curCounter;
	}
	int GtPostX(int i)			//��ǰ��������x
	{
		return cities[i].getX();
	}
	int GtPostY(int i)			//��ǰ��������y
	{
		return cities[i].getY();
	}
	void SaveCity()		//�洢�ļ�
	{
		ofstream out;
		out.open("map_output.txt");
		out << left << setw(8) << curCounter << endl;
		for (int i = 0; i < curCounter; i++)
		{
			out << left << setw(8) << cities[i].getNum() << setw(12) << cities[i].getName() << setw(6) << cities[i].getX() << setw(6) << cities[i].getY() << '\n';
		}
		out.close();
		cout << "�ѽ�������Ϣ�洢����map_output.txt��" << endl;
	}
	void ReadCity()		//��ȡ�ļ�
	{
		char ch1;
		char file[100] = { 0 };
		int top, chx, chy, flag = 0, i = 0, num;
		string temp(8, 0), temp1(8, 0), temp2(12, ' '), temp3(6, 0), temp4(6, 0);

		cout << "�������ļ�����";
		cin >> file;

		fstream infile(file, ios::in);
		if (!infile)
		{
			cout << "�Ҳ���ָ���ļ� " << file << endl;
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				infile.get(ch1);
				if (ch1 != ' ')
					temp[i] = ch1;
			}
			infile.get();
			top = toInt(temp);
			for (flag; flag < top; flag++)
			{
				for (int i = 0; i < 8; i++)				//��ȡ���
				{
					infile.get(ch1);
					if (ch1 != ' ')
						temp1[i] = ch1;
					else continue;
				}
				num = toInt(temp1);
				for (int i = 0; i < 12; i++)			//��ȡ����
				{
					infile.get(ch1);
					if (ch1 != ' ')
						temp2[i] = ch1;
					else continue;
				}
				for (int i = 0; i < 6; i++)				//��ȡ����X
				{
					infile.get(ch1);
					if (ch1 != ' ')
						temp3[i] = ch1;
					else continue;
				}
				chx = toInt(temp3);
				for (int i = 0; i < 6; i++)				//��ȡ����Y
				{
					infile.get(ch1);
					if (ch1 != ' ')
						temp4[i] = ch1;
					else continue;
				}
				infile.get();
				chy = toInt(temp4);
				bool tag = true;
				for (int i = 0; i < curCounter; i++)
				{
					if (num == cities[i].getNum())
					{
						cities[i].setName(temp2);
						cities[i].setPosition(chx, chy);
						tag = false;
					}
				}
				if (tag)
				{
					cities[curCounter].setNum(num);
					cities[curCounter].setName(temp2);
					cities[curCounter].setPosition(chx, chy);
					curCounter++;
				}
			}
			cout << "����ɹ���" << endl;
		}
		infile.close();
	}
	void CtyDist()
	{
		for (int i = 0; i < curCounter; i++)
		{
			for (int j = i; j < curCounter; j++)
			{
				if (i != j)
					cout << left << setw(12) << cities[i].getName() << "��" << setw(12) << cities[j].getName() << "|" << Dist(cities[i].getX(), cities[i].getY(), cities[j].getX(), cities[j].getY()) << endl;
			}
		}
		char b = NULL;
		cout << "�Ƿ�洢������Ϣ��    ��(y) ��(n)" << endl;
		cin >> b;
		if (b == 'y')
		{
			ofstream outfile;
			outfile.open("city_distance.txt");
			for (int i = 0; i < curCounter; i++)
			{
				for (int j = i; j < curCounter; j++)
				{
					if (i != j)
						outfile << left << setw(12) << cities[i].getName() << "��" << setw(12) << cities[j].getName() << "|" << Dist(cities[i].getX(), cities[i].getY(), cities[j].getX(), cities[j].getY()) << endl;
				}
			}
			cout << "�ѽ�������Ϣ�洢����city_distance.txt��" << endl;
		}
	}
	void permute(vector<int>& nums, vector<vector<int>>& res, int pos, int n)
	{
		if (pos == n) 
		{							// �����ǰλ�õ������鳤�ȣ�˵���Ѿ��������һ��Ԫ��
			res.push_back(nums);	// ����ǰ�����н�������ά������
			return;					// �����ݹ�
		}
		for (int i = pos; i < n; i++) 
		{										// �����ӵ�ǰλ�õ����һ��Ԫ�ص�����Ԫ��
			swap(nums[pos], nums[i]);			// ������ǰλ�ú͵�i��λ�õ�Ԫ��
			permute(nums, res, pos + 1, n);		// �ݹ�ض���һ��λ�ý���ȫ����
			swap(nums[pos], nums[i]);			// �ָ�ԭ����˳���Ա������һ�ν���
		}
	}
	void Route(int* num, int max)
	{
		double dist = inf;
		int maxc = 1, flag = 0;
		for (int i = 1; i < max; ++i) maxc *= i;

		vector<int> nums(max);
		for (int i = 0; i < max; i++) nums[i] = num[i];
		vector<vector<int>> res;			// ����һ����ά���飬�������ȫ���еĽ��
		permute(nums, res, 0, max);			// ���õݹ麯�����ӵ�0��λ�ÿ�ʼ����ȫ����
		
		for (int i = 0; i < maxc; i++)
		{
			double d = 0;
			for (int j = 0; j < max-1; j++)
			{
				if (res[i][0] == num[0] && res[i][max - 1] == num[max - 1])
				{
					d += edge(res[i][j], res[i][j + 1]);
				}
				else
				{
					d = inf;
				}
			}
			if (d < dist)
			{
				dist = d;
				flag = i;
			}
		}
		cout << "���·��Ϊ��" << endl;
		for (int i = 0; i < max; i++)
		{
			cout << setw(12) << GtCity(res[flag][i]);
			if (i != max - 1)
			{
				cout << "---��";
			}
		}
		cout << endl << "·��Ϊ��" << dist << endl;
	}
	double edge(int num1, int num2)
	{
		int i = 0, j = 0;
		for (i; i < curCounter; i++)
		{
			if (cities[i].getNum() == num1)
				break;
		}
		for (j; j < curCounter; j++)
		{
			if (cities[j].getNum() == num2)
				break;
		}
		return Dist(cities[i].getX(), cities[i].getY(), cities[j].getX(), cities[j].getY());
	}
};
class Plane
{
	string num;
	string name;
	int x, y;
	double weight;
	bool flag;		  //flag�����жϵ�ǰ�Ƿ������˷ɻ�
public:
	Plane(string num1 = "AA0000", string name1 = "δ�����ɻ�", int a = 0, int b = 0, int c = 0)
	{
		name = name1;
		num = num1;
		x = a;
		y = b;
		weight = c;
		flag = false;
	}
	bool ReadFlag()   //���ص�ǰflagֵ
	{
		return flag;
	}
	void show()										//��ʾ�ɻ���Ϣ
	{
		cout << left << setw(8) << num << setw(11) << name << setw(6) << x << setw(6) << y << setw(6) << weight << endl;
	}
	int CanBrake(double sp, double reDist)			//�жϵ�ǰ�Ƿ����ɲ��
	{
		if (weight * sp / 5 < reDist) return 1;
		else return 0;
	}
	void RadarFind(double Ra, Map& m)				//���ҷɻ��״�뾶�ڵĳ���
	{
		int cur = m.GtCurCounter();
		if (cur)
		{
			bool flag = false;
			for (int i = 0; i < cur; i++)
			{
				if (m.Dist(x, y, m.GtPostX(i), m.GtPostY(i)) < Ra)
				{
					m.showCity(i);
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "�״�δ���ֳ���" << endl;
			}
		}
		else
		{
			cout << "�״�δ���ֳ���" << endl;
		}
	}
	void SetPlane(string n, string na, double w, int xpos, int ypos)	//����һ�ܷɻ�
	{
		name = na;
		num = n;
		weight = w;
		x = xpos;
		y = ypos;
		flag = true;
	}
};

void appendCity(Map& mapObj)				//���ӳ��м�¼
{
	string name;
	int x, y, num;
	cout << "��������б�ţ�" << endl;
	cin >> num;
	if (mapObj.AskCity(num))
	{
		cout << "*�ó����Ѵ���*" << endl;
	}
	else
	{
		cout << "������������ƺ����꣺" << endl;
		cin >> name >> x >> y;
		mapObj.AddCity(num, name, x, y);
	}
}
void delCity(Map& mapObj)					//ɾ�����м�¼
{
	int num;
	cout << "������Ҫɾ�����еı�ţ�" << endl;
	cin >> num;
	if (mapObj.AskCity(num))
	{
		mapObj.DeletCity(num);
	}
	else
	{
		cout << "*�ó��в�����*" << endl;
	}
}
void updCity(Map& mapObj)					//�޸ĳ�����Ϣ
{
	int num;
	cout << "������Ҫ�޸ĳ��еı�ţ�" << endl;
	cin >> num;
	if (mapObj.AskCity(num))
	{
		mapObj.UpdCity(num);
	}
	else
	{
		cout << "*�ó��в�����*" << endl;
	}
}
void SaveToFile(Map& mapObj)				//���������Ϣ��д������ļ�
{
	mapObj.SaveCity();
}
void ReadFromFile(Map& mapObj)				//�Ӵ����ļ���ȡ������Ϣ
{
	mapObj.ReadCity();
}
void ShowAllCities(Map& mapObj)				//��ʾ���г�����Ϣ
{
	mapObj.ShowAlCity();
}
void AddPlane(Plane& planeObj)				//����ɻ���Ϣ
{
	string num, name;
	int w, x, y;
	cout << "������ɻ���ź����ƣ�" << endl;
	cin >> num >> name;
	cout << "������ɻ��������֣���" << endl;
	cin >> w;
	cout << "������ɻ���ǰ���꣺" << endl;
	cin >> x >> y;
	planeObj.SetPlane(num, name, w, x, y);
}
void ShowPlane(Plane& planeObj)							//��ʾ�ɻ���Ϣ
{
	if (planeObj.ReadFlag())
	{
		planeObj.show();
	}
	else
	{
		cout << "�������÷ɻ���Ϣ" << endl;
	}
}
void Brake(Plane& planeObj)								//�жϷɻ����ʱ�Ƿ����ɲ��
{
	if (planeObj.ReadFlag())
	{
		double v, d;
		cout << "�����뵱ǰ�ٶȣ�����/Сʱ����" << endl;
		cin >> v;
		cout << "������ʣ���ܵ����ȣ��ף���" << endl;
		cin >> d;
		if (planeObj.CanBrake(v, d))
		{
			cout << "��ǰ����ɲ��" << endl;
		}
		else
		{
			cout << "��ǰ����ɲ��" << endl;
		}
	}
	else
	{
		cout << "�������÷ɻ���Ϣ" << endl;
	}
}
void RaderSearch(Plane& planeObj, Map& m)				//��ʾ�ڷɻ��״ﷶΧ�ڵĳ�����Ϣ
{
	if (planeObj.ReadFlag())
	{
		double ra;
		cout << "������ɻ��״�뾶��" << endl;
		cin >> ra;
		cout << "�������У�" << endl;
		planeObj.RadarFind(ra, m);
	}
	else
	{
		cout << "�������÷ɻ���Ϣ" << endl;
	}
}
void CityDist(Map& m)									//������м����
{
	if (m.GtCurCounter())
	{
		m.CtyDist();
	}
	else
	{
		cout << "��ǰ�޳�����Ϣ��" << endl;
	}
}
void Route(Map& m)										//����·��
{
	int i = 0, startnum, endnum, * city;
	city = new int[200];
	string midnum(8, 0);
	if (m.GtCurCounter())
	{
		m.ShowAlCity();
		cout << "�����������б�ţ�" << endl;
		for (;;)
		{
			cin >> startnum;
			if (m.AskCity(startnum))
			{
				city[i] = startnum;
				i++;
				break;
			}
			else
			{
				cout << "�ó��в����ڣ����������룡" << endl;
				continue;
			}
		}
		cout << "�����;�����б�ţ���ֹ��������롰s����" << endl;
		for (;;)
		{
			cin >> midnum;
			if (midnum == "s" || midnum == "S")
			{
				break;
			}
			else
			{
				int mid = toInt(midnum);
				bool flag1 = true;
				for (int j = 0; j < 200; j++)
				{
					if (mid == city[j]) 
						flag1 = false;
				}
				if (flag1)
				{
					if (m.AskCity(mid))
					{
						city[i] = mid;
						i++;
					}
					else
					{
						cout << "�ó��в����ڣ����������룡" << endl;
					}
					continue;
				}
				else
				{
					cout << "����Ӹó��У����������룡" << endl;
				}
			}
		}
		cout << "�������յ���б�ţ�" << endl;
		for (;;)
		{
			cin >> endnum;
			bool flag2 = true;
			for (int j = 0; j < 200; j++)
			{
				if (endnum == city[j]) 
					flag2 = false;
			}
			if (flag2)
			{
				if (m.AskCity(endnum))
				{
					city[i] = endnum;
					i++;
					break;
				}
				else
				{
					cout << "�ó��в����ڣ����������룡" << endl;
					continue;
				}
			}
			else
			{
				cout << "����Ӹó��У����������룡" << endl;
			}
		}
		m.Route(city, i);
	}
	else
	{
		cout << "��ǰ�޳�����Ϣ��" << endl;
	}
}
char Quit(Map& mapObj)									//�˳�
{
	char a;
	cout << "ȷ���˳���    ��(y) ��(n)" << '\n' << "*�˳�ʱ���Ὣ�洢��ǰ������Ϣ*" << endl;
	cin >> a;
	if (a == 'y')
	{
		mapObj.SaveCity();
		return 'y';
	}
	else
	{
		return 'n';
	}
}
void main()
{
	int menu_select();
	Map mapObj;
	Plane planeObj;
	int sel;

	for ( ; ; )
	{
		switch (sel = menu_select())
		{
		case 1:	appendCity(mapObj);
				system("pause"); break;
		case 2:	delCity(mapObj);
				system("pause"); break;
		case 3:	updCity(mapObj);
				system("pause"); break;
		case 4:	SaveToFile(mapObj);
				system("pause"); break;
		case 5: ReadFromFile(mapObj);
				system("pause"); break;
		case 6: ShowAllCities(mapObj);
				system("pause"); break;
		case 7: AddPlane(planeObj);
				system("pause"); break;
		case 8: ShowPlane(planeObj);
				system("pause"); break;
		case 9: Brake(planeObj);
				system("pause"); break;
		case 10:RaderSearch(planeObj, mapObj);
				system("pause"); break;
		case 11:CityDist(mapObj);
				system("pause"); break;
		case 12:Route(mapObj);
				system("pause"); break;
		case 0:
			if (Quit(mapObj) != 'y')
				continue;
		}
		if (sel == 0) break;
	}
}
int menu_select()
{
	const char* m[14] = 
	{
		"1.���ӳ��м�¼",
		"2.ɾ�����м�¼",
		"3.�޸ĳ��м�¼",
		"4.���������Ϣ���ļ�",
		"5.���ļ���ȡ������Ϣ",
		"6.��ʾ���г�����Ϣ",
		"7.���÷ɻ���Ϣ",
		"8.��ʾ�ɻ���Ϣ",
		"9.�ж���ɷɻ��Ƿ����ɲ��",
		"10.��ѯ�ɻ��״ﷶΧ�����г�����Ϣ",
		"11.����������м�ľ���",
		"12.�滮·��",
		"0.�˳�"
	};
	int i, choice;
	string ch;
	do {
		system("cls");	//����
		for (i = 0; m[i]; i++)
		{
			cout << m[i] << endl;
		}
		cout << "\n";
		cout << "������ѡ��";
		cin >> ch;
		choice = toInt(ch);
	} while (choice < 0 || choice>12);
	return(choice);
}