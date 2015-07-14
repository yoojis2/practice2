#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Model class
class GameModel
{
public:
	int number[3];  // 정답이 담긴 배열
	int inputNumber[3];  // 들어온 숫자가 담길 배열(비교대상)

	GameModel();  // 생성자

	void makeNum();  // 정답 숫자 3개를 랜덤으로 만드는 함수

};