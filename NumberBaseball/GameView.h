#include <iostream>

using namespace std;

// View class
class GameView{
public:
	void printPlzInput(int round);  // �Է¹ޱ����� ��¹�
	void printPlzInputAgain();  // �ٽ��Է¹ޱ� ���� ��¹�(����ó��)

	bool printResult(bool hit, bool out, int strike, int ball);  // ���(��ī��Ʈ, �ƿ�, �¸�)�� ����ϱ� ���� �Լ�
};