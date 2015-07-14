#include "Ranking.h"

// ������
Ranking::Ranking()
{
	round = 0; // �ʱ�ȭ

	// ���� ����
	fin.open("rank.txt");
	
	newPlayer = true;  // newPlayer�� �ʱ�ȭ
	firstPlay = fin.fail();  // ������ ������ firstPlay flag true�� ����

	// �ؽ�Ʈ ����(rank)���� ���� �о��
	if (!fin.fail())
		while (!fin.eof())
		{
			// ���� �о�� �� ����ü�� ����
			fin >> rank >> name >> time >> round;

			// ������ ���������� �ѹ��� Ȯ��
			if (fin.eof())
				break;

			temp.playerName = name;
			temp.playerTime = time;
			temp.round = round;

			rankList.push_back(temp);  // rankList�� ����
		}
}

// sort�Լ����� ���� �Լ�. (time �������� ����)
bool Compare(playerInform a, playerInform b)
{
	return a.playerTime < b.playerTime;
}

// rankList�� �����Ͽ� ������ ����� �Լ�
void Ranking::makeRanking(vector<playerInform> &rankList)
{
	// �������� ����
	sort(rankList.begin(), rankList.end(), Compare);

	// ���ĵ� �� txt���Ϸ� ������
	fout.open("rank.txt");
	for (int i = 0; i < rankList.size(); i++)
		fout << i + 1 << "	" << rankList[i].playerName << "	" << rankList[i].playerTime << "	" << rankList[i].round << endl;

	fout.close();
}

// ��ŷ�� ������ִ� �Լ�
void Ranking::printRanking(vector<playerInform> rankList)
{
	// ���� 5������ ����ϱ����Ͽ� ���� 5�� ����
	int end = 5;

	// ���� �����Ͱ� 5�� ���϶�� rankList�� ����� �������� ����
	if (rankList.size() < 5)
		end = rankList.size();

	for (int i = 0; i < end; i++)
	{
		cout << i + 1 << "��: " << rankList[i].playerName << "   " << rankList[i].playerTime << "	" << rankList[i].round <<  endl;
	}
}

// ��ŷ�� ������ִ� �Լ�
void Ranking::excute(string name, double time, int round)
{
	// ���� player�� �̸��� data���� ã�� �����Ѵٸ� newPlayer false�θ����
	// ����� �� ���ٸ� ����
	for (int i = 0; i < rankList.size(); i++)
	{
		if (rankList[i].playerName == name)
		{
			newPlayer = false;
			if (rankList[i].playerTime > time)
				rankList[i].playerTime = time;
			break;
		}
	}

	// ���� ���ο� �÷��̾�ٸ�
	if (newPlayer)
	{
		// ����ü�� �̸��� ��� �Է� �� rankList�� ����
		temp.playerName = name;
		temp.playerTime = time;
		temp.round = round;

		rankList.push_back(temp);

	}

	// Ranking ����
	makeRanking(rankList);
}

void Ranking::print()
{
	// ���� ó�� �����ϰų� rankList�� ����� 0�̶�� (��ŷ������ ����)
	if (firstPlay || rankList.size() == 0)
		cout << "��ŷ������ �����ϴ�" << endl;

	// �׷��� �ʴٸ� ��ŷ���� ����� ��ŷ ���
	else
	{
		makeRanking(rankList);
		printRanking(rankList);
	}
}