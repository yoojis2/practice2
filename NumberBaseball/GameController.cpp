#include "GameController.h"

// 생성자
GameController::GameController()
{
	win = false;  // win값 초기화

	// 현재 입력한 값 받을 배열 초기화
	for (int i = 0; i < 3; i++)
		currentNum[i] = -1;

	// 볼카운트 및 out, hit 초기화
	count.strike = 0;
	count.ball = 0;
	count.hit = false;
	count.out = false;

	// round 초기화
	round = 1;
}

// 볼카운트 초기화하는 함수
void GameController::initializeCount()
{
	count.strike = 0;
	count.ball = 0;
	count.hit = false;
	count.out = false;
}

// 입력받은 숫자를 정답과 비교하는 함수
void GameController::compareNum(int* currentNum, int* number)
{
	// 볼카운트 초기화
	initializeCount();

	// 입력받은 수(currentNum)과 정답(number)을 비교하여 숫자가 위치까지 같다면 strike 증가
	// 숫자만 같고 위치는 다르다면 ball 증가
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (currentNum[i] == number[j])
			{
				if (i == j)
				{
					count.strike++;
					break;
				}
				else
				{
					count.ball++;
					break;
				}
			}

	// 만약 3스트라이크라면(hit) 승리이므로 hit을 true로 변경
	if (count.strike == 3)
		count.hit = true;
	// 스트라이크와 볼이 모두 0이라면 out이므로 out을 true로 변경
	if (count.strike == 0 && count.ball == 0)
		count.out = true;

}

// 숫자를 입력받는 함수
void GameController::inputNum()
{
	round = 1;  // round 초기화

	// 입력을위한 무한루프
	while (1)
	{
		view.printPlzInput(round);  // 입력받기위한 문자열 현재 round 넘겨줘서 출력

		// 숫자 3개 입력받음
		for (int i = 0; i < 3; i++)
			cin >> model.inputNumber[i];

		// 만약 숫자가 겹치는것이있다면 다시입력해달라고 하고 continue를통해 while문의 맨위로 올라가서 다시 입력받음
		// 음수나 10보다 큰 숫자가 들어와도 다시입력해달라고 말한다.
		if (model.inputNumber[0] == model.inputNumber[1] ||
			model.inputNumber[1] == model.inputNumber[2] ||
			model.inputNumber[2] == model.inputNumber[0] ||
			model.inputNumber[0] >= 10 || model.inputNumber[0] < 0 ||
			model.inputNumber[1] >= 10 || model.inputNumber[1] < 0 ||
			model.inputNumber[2] >= 10 || model.inputNumber[2] < 0
			)
		{
			view.printPlzInputAgain();
			continue;
		}

		round++;  // round증가
		compareNum(model.inputNumber, model.number);  // 입력받은 숫자와 정답을 비교함.
		// 비교하여 나온 값을 printResult에 인자넘겨줘서 출력. 반환값이 참일경우는 승리(hit)하는 경우임.
		if (view.printResult(count.hit, count.out, count.strike, count.ball))
		{
			win = true;
			break;
		}

		// round가 11이 되면 종료
		if (round == 11)
		{
			//  컴퓨터가 승리한것이므로 출력문 보여주고 win false로 만들고 break
				cout << "10Round 까지 못맞추셨습니다. 컴퓨터가 승리하였습니다." << endl;
				cout << "게임이 종료됩니다." << endl;
				win = false;
				break;
		}
		
	}

}

// 게임 start 함수
void GameController::run()
{
	cout << "숫자야구 게임을 시작합니다!" << endl;
	model.makeNum();  // 숫자를 만든다.
	inputNum();  // 숫자를 입력받고 시작한다.
}