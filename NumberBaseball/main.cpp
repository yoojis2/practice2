#include <iostream>
#include "GameController.h"
#include "Ranking.h"
#include <string>
#include <time.h>

using namespace std;
//�ٲ���ϴ�!!
int main()
{
	Ranking ranking;  // ranking ����
	double time;  // �ð�
	int round;  // �̱� ����
	string name;  // �̸�
	GameController game;  // ������Ʈ�ѷ�
	clock_t begin, end;  // �ð� �Է¹ޱ����� ����

	while (1)
	{
		int menu;  // �޴� ����(1: ���ӽ���,2: ��ŷ����, 3: ��������)
		// �޴� �Է¹���
		cout << "1. ���ӽ���, 2. ��ŷ����, 3. ��������" << endl;
		cin >> menu;

		// �޴��� ���� switch�� 
		switch (menu)
		{
		case 1:  // 1��(���ӽ���)�϶�
		
			ranking.firstPlay = false;  // ���ӽ����� ������ ���������Ƿ� firstPlay false�θ������

			// �̸��� �Է¹���
			cout << "�̸��� �Է��ϼ���: ";
			cin >> name;

			begin = clock();  // �ð� start

			game.run();  // ���� ��ŸƮ

			end = clock();  // �ð� end

			round = game.round - 1;  // ���尪 �޾ƿ�

			// ���� ���ӿ��� �̰�ٸ�
			if (game.win)
			{
				// �ð� ���� �� ���
				time = (double)(end - begin) / CLOCKS_PER_SEC;
				printf("����ð�(��) : %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);

				// ���� �÷��̾��� �̸��� ���, ����� excute�Լ� ���ڷ� �Ѱ��� ��� ���� or �Է�
				ranking.excute(name, time, round);
			}
			break;

		case 2:  // 2��(��ŷ)�϶�
			ranking.print();
			break;
		case 3:  // 3��(����)�϶� ��ȯ �� ����
			return 0;
		}
		
	}
	return 0;
}