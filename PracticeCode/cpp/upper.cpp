#include <iostream>
#include <string>
#include <vector>
using namespace std;
string upper(char num)
{
	switch (num)
	{
	case '0':return "零";
	case '1':return "壹";
	case '2':return "贰";
	case '3':return "叁";
	case '4':return "肆";
	case '5':return "伍";
	case '6':return "陆";
	case '7':return "柒";
	case '8':return "捌";
	case '9':return "玖";
	default: return "错误";
	}
}//将单个数字字符转换为银行大写汉字
string firstlevel(int level)
{
	switch (level)
	{
	case 1: return "拾";
	case 2: return "佰";
	case 3: return "仟";
	default: return "";
	}
}
string secondlevel(int level)
{
	switch (level)
	{
	case 0: return "万";
	case 4: return "亿";
	default: return "";
	}
}
int main()
{
	vector<char> floatnum;
	char singlenum = '\0';
	while (singlenum != '.')  //输入整数部分
	{
		cin >> singlenum;
		floatnum.push_back(singlenum);
	}
	for (int i = 0; i < 3; ++i) //输入小数部分,三位即可
	{
		if(i == 0)floatnum.pop_back();  //去除小数点

		cin >> singlenum;
		floatnum.push_back(singlenum);
	}
	if (floatnum[floatnum.size() - 1] >= '5') //末位四舍五入
	{
		floatnum[floatnum.size() - 2] += 1;
	}
	floatnum.pop_back();

	if(floatnum.size() < 3)
	cout<<"数额不足一元"<<endl;

	string endnum = "元";       //先处理不规律的元角分
	if(floatnum[floatnum.size()-2] != '0')
	{
		endnum += upper(floatnum[floatnum.size()-2]) + "角";
	}
	if(floatnum[floatnum.size()-1] != '0')
	{
		endnum += upper(floatnum[floatnum.size()-1]) + "分";
	}
	floatnum.pop_back();
	floatnum.pop_back();

	string frontnum = "";      //然后处理整数部分
	for(int i=0; i < floatnum.size(); i++)
	{
		int j = floatnum.size() - i - 1;
		if(floatnum[i] == '0')
		{
			frontnum += upper(floatnum[i]);
		}
		else
		{
			frontnum += upper(floatnum[i]) + firstlevel(j % 4) + secondlevel((j-4) % 8);
		}

	}
	cout<<frontnum + endnum<<endl;
	system("pause");
	return 0;
}