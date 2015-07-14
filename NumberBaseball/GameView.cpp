#include "GameView.h"

// �ٽ� �Է��ش޶�� ������ ���� round�� ���� ���
void GameView::printPlzInput(int round)
{
	cout << "ROUND " << round << " - ���ڸ� �Է����ּ���: ";
}

// �ٽ� �Է��ش޶�� ���ڿ�
void GameView::printPlzInputAgain()
{
	cout << "�Է��� �߸��Ǿ����ϴ� �ٽ� �Է����ּ���" << endl;
}

// ���� ��ī��Ʈ ��� �� ������ out true �����.
// �̰�����(hit == true) true ��ȯ. �ƴҰ�� false ��ȯ
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