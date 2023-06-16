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
	int num;							//城市编号
	string name;						//城市名称
	int x, y;							//城市坐标
public:
	City(int num1 = 0, string name1 = "未命名城市", int a = 0, int b = 0)
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
	City* cities;						//指向线性表的指针
	int curCounter, maxCounter;			//现有城市记录数，线性表最大长度
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
	double Dist(int x1, int y1, int x2, int y2)		//计算城市间距离
	{
		double d;
		d = sqrt(sqr(x1 - x2) + sqr(y1 - y2));
		return d;
	}
	void AddCity(int n, string na, int x, int y)	//增加城市
	{
		cities[curCounter].setNum(n);
		cities[curCounter].setName(na);
		cities[curCounter].setPosition(x, y);
		curCounter++;
	}
	void DeletCity(int num)			//删除城市
	{
		for (int i = 0; i < curCounter; i++)
		{
			if (cities[i].getNum() == num)
			{
				char Bool = NULL;
				cout << "当前城市为：" << endl;
				cities[i].show();
				cout << "确认删除此城市吗？    是(y) 否(n)" << endl;
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
	void UpdCity(int num)			//修改城市信息
	{
		for (int i = 0; i < curCounter; i++)
		{
			if (cities[i].getNum() == num)
			{
				cout << "当前城市为：" << endl;
				cities[i].show();

				string na;
				int nu, x, y;
				cout << "请依次输入修改后的编号、名称和坐标：" << endl;
				cin >> nu >> na >> x >> y;

				char Bool = NULL;
				cout << "确认更改此城市信息吗？    是(y) 否(n)" << endl;
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
	void ShowAlCity()				//显示全部城市信息
	{
		if (curCounter)
		{
			cout << "当前城市数量：" << curCounter << endl;
			for (int i = 0; i < curCounter; i++)
			{
				cities[i].show();
			}
		}
		else
		{
			cout << "当前无城市信息！" << endl;
		}
	}
	bool AskCity(int num)		//查询城市是否存在
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
	int GtCurCounter()				//读取当前城市数量
	{
		return curCounter;
	}
	int GtPostX(int i)			//当前城市坐标x
	{
		return cities[i].getX();
	}
	int GtPostY(int i)			//当前城市坐标y
	{
		return cities[i].getY();
	}
	void SaveCity()		//存储文件
	{
		ofstream out;
		out.open("map_output.txt");
		out << left << setw(8) << curCounter << endl;
		for (int i = 0; i < curCounter; i++)
		{
			out << left << setw(8) << cities[i].getNum() << setw(12) << cities[i].getName() << setw(6) << cities[i].getX() << setw(6) << cities[i].getY() << '\n';
		}
		out.close();
		cout << "已将城市信息存储到“map_output.txt”" << endl;
	}
	void ReadCity()		//读取文件
	{
		char ch1;
		char file[100] = { 0 };
		int top, chx, chy, flag = 0, i = 0, num;
		string temp(8, 0), temp1(8, 0), temp2(12, ' '), temp3(6, 0), temp4(6, 0);

		cout << "请输入文件名：";
		cin >> file;

		fstream infile(file, ios::in);
		if (!infile)
		{
			cout << "找不到指定文件 " << file << endl;
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
				for (int i = 0; i < 8; i++)				//读取编号
				{
					infile.get(ch1);
					if (ch1 != ' ')
						temp1[i] = ch1;
					else continue;
				}
				num = toInt(temp1);
				for (int i = 0; i < 12; i++)			//读取名称
				{
					infile.get(ch1);
					if (ch1 != ' ')
						temp2[i] = ch1;
					else continue;
				}
				for (int i = 0; i < 6; i++)				//读取坐标X
				{
					infile.get(ch1);
					if (ch1 != ' ')
						temp3[i] = ch1;
					else continue;
				}
				chx = toInt(temp3);
				for (int i = 0; i < 6; i++)				//读取坐标Y
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
			cout << "导入成功！" << endl;
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
					cout << left << setw(12) << cities[i].getName() << "→" << setw(12) << cities[j].getName() << "|" << Dist(cities[i].getX(), cities[i].getY(), cities[j].getX(), cities[j].getY()) << endl;
			}
		}
		char b = NULL;
		cout << "是否存储距离信息？    是(y) 否(n)" << endl;
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
						outfile << left << setw(12) << cities[i].getName() << "→" << setw(12) << cities[j].getName() << "|" << Dist(cities[i].getX(), cities[i].getY(), cities[j].getX(), cities[j].getY()) << endl;
				}
			}
			cout << "已将距离信息存储到“city_distance.txt”" << endl;
		}
	}
	void permute(vector<int>& nums, vector<vector<int>>& res, int pos, int n)
	{
		if (pos == n) 
		{							// 如果当前位置等于数组长度，说明已经到达最后一个元素
			res.push_back(nums);	// 将当前的排列结果存入二维数组中
			return;					// 结束递归
		}
		for (int i = pos; i < n; i++) 
		{										// 遍历从当前位置到最后一个元素的所有元素
			swap(nums[pos], nums[i]);			// 交换当前位置和第i个位置的元素
			permute(nums, res, pos + 1, n);		// 递归地对下一个位置进行全排列
			swap(nums[pos], nums[i]);			// 恢复原来的顺序，以便进行下一次交换
		}
	}
	void Route(int* num, int max)
	{
		double dist = inf;
		int maxc = 1, flag = 0;
		for (int i = 1; i < max; ++i) maxc *= i;

		vector<int> nums(max);
		for (int i = 0; i < max; i++) nums[i] = num[i];
		vector<vector<int>> res;			// 创建一个二维数组，用来存放全排列的结果
		permute(nums, res, 0, max);			// 调用递归函数，从第0个位置开始进行全排列
		
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
		cout << "最短路径为：" << endl;
		for (int i = 0; i < max; i++)
		{
			cout << setw(12) << GtCity(res[flag][i]);
			if (i != max - 1)
			{
				cout << "---→";
			}
		}
		cout << endl << "路程为：" << dist << endl;
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
	bool flag;		  //flag用于判断当前是否设置了飞机
public:
	Plane(string num1 = "AA0000", string name1 = "未命名飞机", int a = 0, int b = 0, int c = 0)
	{
		name = name1;
		num = num1;
		x = a;
		y = b;
		weight = c;
		flag = false;
	}
	bool ReadFlag()   //返回当前flag值
	{
		return flag;
	}
	void show()										//显示飞机信息
	{
		cout << left << setw(8) << num << setw(11) << name << setw(6) << x << setw(6) << y << setw(6) << weight << endl;
	}
	int CanBrake(double sp, double reDist)			//判断当前是否可以刹车
	{
		if (weight * sp / 5 < reDist) return 1;
		else return 0;
	}
	void RadarFind(double Ra, Map& m)				//查找飞机雷达半径内的城市
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
				cout << "雷达未发现城市" << endl;
			}
		}
		else
		{
			cout << "雷达未发现城市" << endl;
		}
	}
	void SetPlane(string n, string na, double w, int xpos, int ypos)	//设置一架飞机
	{
		name = na;
		num = n;
		weight = w;
		x = xpos;
		y = ypos;
		flag = true;
	}
};

void appendCity(Map& mapObj)				//增加城市记录
{
	string name;
	int x, y, num;
	cout << "请输入城市编号：" << endl;
	cin >> num;
	if (mapObj.AskCity(num))
	{
		cout << "*该城市已存在*" << endl;
	}
	else
	{
		cout << "请输入城市名称和坐标：" << endl;
		cin >> name >> x >> y;
		mapObj.AddCity(num, name, x, y);
	}
}
void delCity(Map& mapObj)					//删除城市记录
{
	int num;
	cout << "请输入要删除城市的编号：" << endl;
	cin >> num;
	if (mapObj.AskCity(num))
	{
		mapObj.DeletCity(num);
	}
	else
	{
		cout << "*该城市不存在*" << endl;
	}
}
void updCity(Map& mapObj)					//修改城市信息
{
	int num;
	cout << "请输入要修改城市的编号：" << endl;
	cin >> num;
	if (mapObj.AskCity(num))
	{
		mapObj.UpdCity(num);
	}
	else
	{
		cout << "*该城市不存在*" << endl;
	}
}
void SaveToFile(Map& mapObj)				//保存城市信息并写入磁盘文件
{
	mapObj.SaveCity();
}
void ReadFromFile(Map& mapObj)				//从磁盘文件读取城市信息
{
	mapObj.ReadCity();
}
void ShowAllCities(Map& mapObj)				//显示所有城市信息
{
	mapObj.ShowAlCity();
}
void AddPlane(Plane& planeObj)				//输入飞机信息
{
	string num, name;
	int w, x, y;
	cout << "请输入飞机编号和名称：" << endl;
	cin >> num >> name;
	cout << "请输入飞机重量（吨）：" << endl;
	cin >> w;
	cout << "请输入飞机当前坐标：" << endl;
	cin >> x >> y;
	planeObj.SetPlane(num, name, w, x, y);
}
void ShowPlane(Plane& planeObj)							//显示飞机信息
{
	if (planeObj.ReadFlag())
	{
		planeObj.show();
	}
	else
	{
		cout << "请先设置飞机信息" << endl;
	}
}
void Brake(Plane& planeObj)								//判断飞机起飞时是否可以刹车
{
	if (planeObj.ReadFlag())
	{
		double v, d;
		cout << "请输入当前速度（公里/小时）：" << endl;
		cin >> v;
		cout << "请输入剩余跑道长度（米）：" << endl;
		cin >> d;
		if (planeObj.CanBrake(v, d))
		{
			cout << "当前可以刹车" << endl;
		}
		else
		{
			cout << "当前不可刹车" << endl;
		}
	}
	else
	{
		cout << "请先设置飞机信息" << endl;
	}
}
void RaderSearch(Plane& planeObj, Map& m)				//显示在飞机雷达范围内的城市信息
{
	if (planeObj.ReadFlag())
	{
		double ra;
		cout << "请输入飞机雷达半径：" << endl;
		cin >> ra;
		cout << "附近城市：" << endl;
		planeObj.RadarFind(ra, m);
	}
	else
	{
		cout << "请先设置飞机信息" << endl;
	}
}
void CityDist(Map& m)									//计算城市间距离
{
	if (m.GtCurCounter())
	{
		m.CtyDist();
	}
	else
	{
		cout << "当前无城市信息！" << endl;
	}
}
void Route(Map& m)										//输入路线
{
	int i = 0, startnum, endnum, * city;
	city = new int[200];
	string midnum(8, 0);
	if (m.GtCurCounter())
	{
		m.ShowAlCity();
		cout << "请输入起点城市编号：" << endl;
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
				cout << "该城市不存在，请重新输入！" << endl;
				continue;
			}
		}
		cout << "请添加途经城市编号，终止添加请输入“s”：" << endl;
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
						cout << "该城市不存在，请重新输入！" << endl;
					}
					continue;
				}
				else
				{
					cout << "已添加该城市，请重新输入！" << endl;
				}
			}
		}
		cout << "请输入终点城市编号：" << endl;
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
					cout << "该城市不存在，请重新输入！" << endl;
					continue;
				}
			}
			else
			{
				cout << "已添加该城市，请重新输入！" << endl;
			}
		}
		m.Route(city, i);
	}
	else
	{
		cout << "当前无城市信息！" << endl;
	}
}
char Quit(Map& mapObj)									//退出
{
	char a;
	cout << "确认退出？    是(y) 否(n)" << '\n' << "*退出时将会将存储当前城市信息*" << endl;
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
		"1.增加城市记录",
		"2.删除城市记录",
		"3.修改城市记录",
		"4.保存城市信息至文件",
		"5.从文件读取城市信息",
		"6.显示所有城市信息",
		"7.设置飞机信息",
		"8.显示飞机信息",
		"9.判断起飞飞机是否可以刹车",
		"10.查询飞机雷达范围内所有城市信息",
		"11.输出各个城市间的距离",
		"12.规划路线",
		"0.退出"
	};
	int i, choice;
	string ch;
	do {
		system("cls");	//清屏
		for (i = 0; m[i]; i++)
		{
			cout << m[i] << endl;
		}
		cout << "\n";
		cout << "请输入选择：";
		cin >> ch;
		choice = toInt(ch);
	} while (choice < 0 || choice>12);
	return(choice);
}