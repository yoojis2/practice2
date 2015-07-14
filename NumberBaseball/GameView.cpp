#include "GameView.h"

// 다시 입력해달라는 문구를 현재 round와 같이 출력
void GameView::printPlzInput(int round)
{
	cout << "ROUND " << round << " - 숫자를 입력해주세요: ";
}

// 다시 입력해달라는 문자열
void GameView::printPlzInputAgain()
{
	cout << "입력이 잘못되었습니다 다시 입력해주세요" << endl;
}

// 현재 볼카운트 출력 및 졌을땐 out true 만든다.
// 이겼을땐(hit == true) true 반환. 아닐경우 false 반환
bool GameView::printResult(bool hit, bool out, int strike, int ball)
{
	if (hit)
	{
		cout << "YOU WIN!!!!" << endl;
		return true;
	}


	if (out)
		cout << "OUT!!!" << endl;
	else
		cout << ball << " BALL, " << strike << " STRIKE!!!" << endl;

	return false;

}