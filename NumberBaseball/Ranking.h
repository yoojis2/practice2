#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#pragma once

using namespace std;

// 플레이어 정보가 담길 구조체
struct playerInform
{
	string playerName;
	double playerTime;
	int round;
};


// Ranking 클래스
class Ranking
{
public:
	vector<playerInform> rankList;  // 랭킹이 저장될 vector. 자료형은 playerInform구조체이다.
	bool newPlayer;  // 새로운 플레이어일때의 flag
	bool firstPlay;  // 처음 게임을 시작할때(ranking정보 없음)의 flag
	int rank;  // 순위 저장할 변수
	string name;  // 이름 저장할 변수
	double time;  // 시간 저장할 변수
	int round;  // round 수
	playerInform temp;  // 임시 구조체
	ifstream fin;  // 파일입력
	ofstream fout;  // 파일출력
	
	// 생성자
	Ranking();

	// rankList를 정렬하여 순위를 만드는 함수
	void makeRanking(vector<playerInform> &rankList);

	// 랭킹을 출력해주는 함수
	void printRanking(vector<playerInform> rankList);

	// 랭킹을 만들어주는 함수
	void excute(string name, double time, int round);
	
	// 랭킹을 출력해주는 함수
	void print();
};