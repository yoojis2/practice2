#include <iostream>

using namespace std;

// View class
class GameView{
public:
	void printPlzInput(int round);  // 입력받기위한 출력문
	void printPlzInputAgain();  // 다시입력받기 위한 출력문(예외처리)

	bool printResult(bool hit, bool out, int strike, int ball);  // 결과(볼카운트, 아웃, 승리)를 출력하기 위한 함수
};