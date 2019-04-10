// block_world.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#define maxn 25
using namespace std;
vector<int> pile[maxn];  //全局
int n;  //全局  n=pile number

void find_num( int a,int &temp_i,int &temp_j) {  //
	for (temp_i = 0; temp_i < n; temp_i++) {
		for (temp_j = 0; temp_j < pile[temp_i].size(); temp_j++) {
			if (pile[temp_i][temp_j] == a) return ;  //0也没有
		}
	}
}

void go_origin(int a,int temp_i,int temp_j) {   //不允许使用引用的数组
	//c++ primer 4 中明确讲到是可以使用数组的引用的函数定义形式： void f((&a)[5])
	int i;
	while (pile[temp_i].back() != a) {
		i = pile[temp_i].back();
		pile[temp_i].pop_back();
		pile[i].push_back(i);//pile[p].resize(h + 1); pile 只应保留下标0~h 的元素,这个也可以用
	}
}

void add_num(int a, int temp_ai,int temp_aj, int temp_bi) {
	int j;
	if (pile[temp_ai].size() == 0) {
		return;
	}
	if (pile[temp_ai].back() == a) {
		pile[temp_bi].push_back(a);
		pile[temp_ai].pop_back();
		return;
	}
	j = pile[temp_ai].size();
	for (int i = temp_aj; i < j; i++) {
		pile[temp_bi].push_back(pile[temp_ai][i]); 
	}
	for (int i = temp_aj; i < j; i++) {
		pile[temp_ai].pop_back();
	}
}

void go_front(int b, int temp_i, vector<int>(&pile)[maxn]) {  //b的位置
	int i2;

	while (pile[temp_i].back() != b) {
		i2 = pile[temp_i].back();
		pile[i2].insert(pile[i2].begin(), i2);
		pile[temp_i].pop_back();
	}
}

int main()
{
	int temp_ai, temp_aj, temp_bi, temp_bj;
	cin >> n;
	char c[5], c2[5];  //cin只能读入char风格字符串，而cin.getline可以读入string
	int a, b;  //可能会有24的两位数
	for (int i = 0; i < n; i++) {
		pile[i].push_back(i);
	}
	while(1) {//实际只能读取size-1个数据 ,while (cin.getline(s, 5))用不了
		cin >> c;
		if (!strcmp(c, "quit")) {
			break;
		}
		cin >> a >> c2 >> b;
		if (a == b) continue;
		find_num(a, temp_ai, temp_aj);
		find_num(b, temp_bi, temp_bj);
		if (temp_ai == temp_bi) continue;
		if (!strcmp(c, "move")) {  //这个为什么不行strcmp(s.substr(0, 3),"move"),
			//因为返回值有问题，需要赋给一个指向常量字符串的指针
			go_origin(a, temp_ai, temp_aj);
			if (!strcmp(c2, "onto")) go_origin(b, temp_bi, temp_bj);
		}
		else {  //
			if (!strcmp(c2, "onto")) go_front(b, temp_bi, pile);
		}
		add_num(a, temp_ai, temp_aj, temp_bi);
	}

	for (int i = 0; i < n; i++) {
		cout << i << ":";
		for (int j = 0; j < pile[i].size(); j++) {
			cout << " " << pile[i][j];
		}
		cout << endl;
	}
	
	return 0;
}
