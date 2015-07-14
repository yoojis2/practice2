#include "Ranking.h"

// 생성자
Ranking::Ranking()
{
	round = 0; // 초기화

	// 파일 읽음
	fin.open("rank.txt");
	
	newPlayer = true;  // newPlayer값 초기화
	firstPlay = fin.fail();  // 파일이 없을시 firstPlay flag true로 설정

	// 텍스트 파일(rank)에서 정보 읽어옴
	if (!fin.fail())
		while (!fin.eof())
		{
			// 정보 읽어온 뒤 구조체에 저장
			fin >> rank >> name >> time >> round;

			// 파일의 마지막인지 한번더 확인
			if (fin.eof())
				break;

			temp.playerName = name;
			temp.playerTime = time;
			temp.round = round;

			rankList.push_back(temp);  // rankList에 넣음
		}
}

// sort함수에서 쓰일 함수. (time 오름차순 정렬)
bool Compare(playerInform a, playerInform b)
{
	return a.playerTime < b.playerTime;
}

// rankList를 정렬하여 순위를 만드는 함수
void Ranking::makeRanking(vector<playerInform> &rankList)
{
	// 오름차순 정렬
	sort(rankList.begin(), rankList.end(), Compare);

	// 정렬된 값 txt파일로 내보냄
	fout.open("rank.txt");
	for (int i = 0; i < rankList.size(); i++)
		fout << i + 1 << "	" << rankList[i].playerName << "	" << rankList[i].playerTime << "	" << rankList[i].round << endl;

	fout.close();
}

// 랭킹을 출력해주는 함수
void Ranking::printRanking(vector<playerInform> rankList)
{
	// 상위 5위까지 출력하기위하여 끝값 5로 설정
	int end = 5;

	// 만약 데이터가 5개 이하라면 rankList의 사이즈를 끝값으로 설정
	if (rankList.size() < 5)
		end = rankList.size();

	for (int i = 0; i < end; i++)
	{
		cout << i + 1 << "등: " << rankList[i].playerName << "   " << rankList[i].playerTime << "	" << rankList[i].round <<  endl;
	}
}

// 랭킹을 만들어주는 함수
void Ranking::excute(string name, double time, int round)
{
	// 현재 player의 이름을 data에서 찾고 존재한다면 newPlayer false로만들고
	// 기록이 더 좋다면 갱신
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

	// 만약 새로운 플레이어였다면
	if (newPlayer)
	{
		// 구조체에 이름과 기록 입력 후 rankList에 넣음
		temp.playerName = name;
		temp.playerTime = time;
		temp.round = round;

		rankList.push_back(temp);

	}

	// Ranking 만듦
	makeRanking(rankList);
}

void Ranking::print()
{
	// 만약 처음 시작하거나 rankList의 사이즈가 0이라면 (랭킹데이터 없음)
	if (firstPlay || rankList.size() == 0)
		cout << "랭킹정보가 없습니다" << endl;

	// 그렇지 않다면 랭킹정보 만들고 랭킹 출력
	else
	{
		makeRanking(rankList);
		printRanking(rankList);
	}
}