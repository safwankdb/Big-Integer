#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

struct bigInt
{
	vector<int> v;
	int length;
	bigInt()
	{

	}
	bigInt(long n)
	{
		length=0;
		while(n!=0)
		{
			v.push_back(n%10);
			n/=10;
			length++;
		}
	}
	bigInt(string s)
	{
		for (int i = 0; i < s.length(); ++i)
		{
			v.push_back(int (s[s.length()-1-i]) - 48);
		}
		length=v.size();
	}
	bigInt(int n)
	{
		length=0;
		while(n!=0)
		{
			v.push_back(n%10);
			n/=10;
			length++;
		}
	}
	void print(bool a =true)
	{
		for(int i=0;i<v.size();i++)
			cout<<v[v.size()-1-i];
		if(a)
			cout<<endl;
	}
	int operator[](int i)
	{
		if(i>=0&&i<v.size())
			return v[i];
		else return 0;
	}
	bigInt operator+(bigInt a)
	{
		bigInt x;
		int carry=0;
		for (int i = 0; i < max(v.size(),a.v.size()); ++i)
		{
			x.v.push_back((a[i]+(*this)[i]+carry)%10);
			carry=(a[i]+(*this)[i]+carry)/10;
		}
		if(carry!=0)
		{
			x.v.push_back(carry);
		}
		x.length=x.v.size();
		return x;
	}
	bigInt operator+(int a)
	{
		return *this + bigInt(a);
	}
	int operator%(int a)
	{
		if(a==0)
			return int(0);
		if(a==1)
			return 0;
		int t=v[length-1];
		int i=0;
		int r=0;
		while(i<length)
		{
			if(i==length-1)
			{
				r=t;
			}
			while(a>t&&i<length)
			{
				if(i==length-1)
				{
					r=t;
				}
				i++;
				t=t*10+v[length-1-i];
			}
			t=t%a;
			if(i==length-1)
			{
				r=t;
				break;
			}
			i++;
			t=t%a*10+v[length-1-i];
		}
		return r;
	}
	bigInt operator/(int a)
	{
		if(a==0)
			return bigInt(0);
		if(a==1)
			return *this;
		bigInt x;
		int t=v[length-1];
		int i=0;
		bool flag=false;
		while(i<length)
		{
			while(a>t)
			{
				if(flag)
					x.v.insert(x.v.begin(),0);
				i++;
				t=t*10+v[length-1-i];
			}
			x.v.insert(x.v.begin(),t/a);
			flag=true;
			i++;
			t=t%a*10+v[length-1-i];
		}
		x.length=x.v.size();
		return x;
	}
	bigInt operator*(int a)
	{
		bigInt x=*this;
		for(int i=1;i<a;i++)
		{
			x=x+*this;
		}
		return x;
	}
	bigInt operator*(bigInt a)
	{
		bigInt t(1),s(0);
		for(int i=0;i<length;i++)
		{
			s=s+(a*(*this)[i])*t;
		}
		return s;
	}
	bool operator<(bigInt a)
	{
		if (length!=a.length)
		{
			return length<a.length;
		}
		int i=length-1;
		while(i>0)
		{
			if(v[i]!=a[i])
				return v[i]<a[i];
			i--;
		}
		return
			v[0]<a[0];
	}
};
int sumOfDigits(bigInt a,int base=10)
{
	int s=0;
	for (int i = 0; i < a.length; ++i)
	{
		s+=a[i];
	}
	return s;
}
int main()
{
	int m=0;
	int base; cin>>base;
	vector<bigInt> s;
	for(int i=2;i<300;i++)
	{
		if(m>=150)
			break;
		bigInt x(i);
		while(x.length<25)
		{
			if(m>=150)
				break;
			x=x*i;
			if(sumOfDigits(x,base)==i)
			{
				m++;
				s.push_back(x);
				cout<<m<<" "<<i<<" ";
				x.print();
			}
		}
	}
	sort(s.begin(),s.end());
	s[29].print();
	return 0;
}