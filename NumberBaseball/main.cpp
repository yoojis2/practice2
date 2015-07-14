#include <iostream>
#include "GameController.h"
#include "Ranking.h"
#include <string>
#include <time.h>

using namespace std;
//바꿨습니당!!
int main()
{
	Ranking ranking;  // ranking 선언
	double time;  // 시간
	int round;  // 이긴 라운드
	string name;  // 이름
	GameController game;  // 게임컨트롤러
	clock_t begin, end;  // 시간 입력받기위한 변수

	while (1)
	{
		int menu;  // 메뉴 변수(1: 게임시작,2: 랭킹보기, 3: 게임종료)
		// 메뉴 입력받음
		cout << "1. 게임시작, 2. 랭킹보기, 3. 게임종료" << endl;
		cin >> menu;

		// 메뉴에 따른 switch문 
		switch (menu)
		{
		case 1:  // 1번(게임시작)일때
		
			ranking.firstPlay = false;  // 게임실행후 게임을 시작했으므로 firstPlay false로만들어줌

			// 이름을 입력받음
			cout << "이름을 입력하세요: ";
			cin >> name;

			begin = clock();  // 시간 start

			game.run();  // 게임 스타트

			end = clock();  // 시간 end

			round = game.round - 1;  // 라운드값 받아옴

			// 만약 게임에서 이겼다면
			if (game.win)
			{
				// 시간 저장 및 출력
				time = (double)(end - begin) / CLOCKS_PER_SEC;
				printf("수행시간(초) : %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);

				// 현재 플레이어의 이름과 기록, 라운드수 excute함수 인자로 넘겨줘 기록 갱신 or 입력
				ranking.excute(name, time, round);
			}
			break;

		case 2:  // 2번(랭킹)일때
			ranking.print();
			break;
		case 3:  // 3번(종료)일때 반환 및 종료
			return 0;
		}
		
	}
	return 0;
}