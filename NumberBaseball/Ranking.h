#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#pragma once

using namespace std;

// �÷��̾� ������ ��� ����ü
struct playerInform
{
	string playerName;
	double playerTime;
	int round;
};


// Ranking Ŭ����
class Ranking
{
public:
	vector<playerInform> rankList;  // ��ŷ�� ����� vector. �ڷ����� playerInform����ü�̴�.
	bool newPlayer;  // ���ο� �÷��̾��϶��� flag
	bool firstPlay;  // ó�� ������ �����Ҷ�(ranking���� ����)�� flag
	int rank;  // ���� ������ ����
	string name;  // �̸� ������ ����
	double time;  // �ð� ������ ����
	int round;  // round ��
	playerInform temp;  // �ӽ� ����ü
	ifstream fin;  // �����Է�
	ofstream fout;  // �������
	
	// ������
	Ranking();

	// rankList�� �����Ͽ� ������ ����� �Լ�
	void makeRanking(vector<playerInform> &rankList);

	// ��ŷ�� ������ִ� �Լ�
	void printRanking(vector<playerInform> rankList);

	// ��ŷ�� ������ִ� �Լ�
	void excute(string name, double time, int round);
	
	// ��ŷ�� ������ִ� �Լ�
	void print();
};