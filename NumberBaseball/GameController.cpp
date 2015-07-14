#include "GameController.h"

// ������
GameController::GameController()
{
	win = false;  // win�� �ʱ�ȭ

	// ���� �Է��� �� ���� �迭 �ʱ�ȭ
	for (int i = 0; i < 3; i++)
		currentNum[i] = -1;

	// ��ī��Ʈ �� out, hit �ʱ�ȭ
	count.strike = 0;
	count.ball = 0;
	count.hit = false;
	count.out = false;

	// round �ʱ�ȭ
	round = 1;
}

// ��ī��Ʈ �ʱ�ȭ�ϴ� �Լ�
void GameController::initializeCount()
{
	count.strike = 0;
	count.ball = 0;
	count.hit = false;
	count.out = false;
}

// �Է¹��� ���ڸ� ����� ���ϴ� �Լ�
void GameController::compareNum(int* currentNum, int* number)
{
	// ��ī��Ʈ �ʱ�ȭ
	initializeCount();

	// �Է¹��� ��(currentNum)�� ����(number)�� ���Ͽ� ���ڰ� ��ġ���� ���ٸ� strike ����
	// ���ڸ� ���� ��ġ�� �ٸ��ٸ� ball ����
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

	// ���� 3��Ʈ����ũ���(hit) �¸��̹Ƿ� hit�� true�� ����
	if (count.strike == 3)
		count.hit = true;
	// ��Ʈ����ũ�� ���� ��� 0�̶�� out�̹Ƿ� out�� true�� ����
	if (count.strike == 0 && count.ball == 0)
		count.out = true;

}

// ���ڸ� �Է¹޴� �Լ�
void GameController::inputNum()
{
	round = 1;  // round �ʱ�ȭ

	// �Է������� ���ѷ���
	while (1)
	{
		view.printPlzInput(round);  // �Է¹ޱ����� ���ڿ� ���� round �Ѱ��༭ ���

		// ���� 3�� �Է¹���
		for (int i = 0; i < 3; i++)
			cin >> model.inputNumber[i];

		// ���� ���ڰ� ��ġ�°����ִٸ� �ٽ��Է��ش޶�� �ϰ� continue������ while���� ������ �ö󰡼� �ٽ� �Է¹���
		// ������ 10���� ū ���ڰ� ���͵� �ٽ��Է��ش޶�� ���Ѵ�.
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

		round++;  // round����
		compareNum(model.inputNumber, model.number);  // �Է¹��� ���ڿ� ������ ����.
		// ���Ͽ� ���� ���� printResult�� ���ڳѰ��༭ ���. ��ȯ���� ���ϰ��� �¸�(hit)�ϴ� �����.
		if (view.printResult(count.hit, count.out, count.strike, count.ball))
		{
			win = true;
			break;
		}

		// round�� 11�� �Ǹ� ����
		if (round == 11)
		{
			//  ��ǻ�Ͱ� �¸��Ѱ��̹Ƿ� ��¹� �����ְ� win false�� ����� break
				cout << "10Round ���� �����߼̽��ϴ�. ��ǻ�Ͱ� �¸��Ͽ����ϴ�." << endl;
				cout << "������ ����˴ϴ�." << endl;
				win = false;
				break;
		}
		
	}

}

// ���� start �Լ�
void GameController::run()
{
	cout << "���ھ߱� ������ �����մϴ�!" << endl;
	model.makeNum();  // ���ڸ� �����.
	inputNum();  // ���ڸ� �Է¹ް� �����Ѵ�.
}