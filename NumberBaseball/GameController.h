#include "GameModel.h"
#include "GameView.h"
#include <fstream>
#include <iostream>

using namespace std;

// Count를 담고 있는 구조체
struct Count
{
	int strike;
	int ball;
	bool out;  // 하나도 안맞음
	bool hit;  // 숫자 맞춤
};

// Controller class
class GameController
{
public:
	int currentNum[3];  // 현재 입력받은 숫자
	Count count;  // 카운트

	int round;  // 현재 진행중인 라운드
	bool win;  // 이겼을때 여부 flag

	GameModel model;  // model
	GameView view;  // view

	GameController();  // 생성자

	void run();  // 게임시작
	
	void inputNum();  // 숫자입력받음

	void compareNum(int* currentNum, int* number);  // 입력받은숫자와 정답 비교함

	void initializeCount();  // 볼카운트 초기화 함수

};