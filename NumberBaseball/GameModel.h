#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Model class
class GameModel
{
public:
	int number[3];  // ������ ��� �迭
	int inputNumber[3];  // ���� ���ڰ� ��� �迭(�񱳴��)

	GameModel();  // ������

	void makeNum();  // ���� ���� 3���� �������� ����� �Լ�

};