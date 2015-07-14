#include "GameModel.h"
#include "GameView.h"
#include <fstream>
#include <iostream>

using namespace std;

// Count�� ��� �ִ� ����ü
struct Count
{
	int strike;
	int ball;
	bool out;  // �ϳ��� �ȸ���
	bool hit;  // ���� ����
};

// Controller class
class GameController
{
public:
	int currentNum[3];  // ���� �Է¹��� ����
	Count count;  // ī��Ʈ

	int round;  // ���� �������� ����
	bool win;  // �̰����� ���� flag

	GameModel model;  // model
	GameView view;  // view

	GameController();  // ������

	void run();  // ���ӽ���
	
	void inputNum();  // �����Է¹���

	void compareNum(int* currentNum, int* number);  // �Է¹������ڿ� ���� ����

	void initializeCount();  // ��ī��Ʈ �ʱ�ȭ �Լ�

};