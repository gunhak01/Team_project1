#include "Project.h"

int main()
{
	int select = 0;
	int stop = 1;
	HospitalHandler handler;
	
	handler.LoadData();

	while (stop)
	{
		handler.ShowMenu();
		cout << "선택할 번호를 입력해주세요 : ";
		cin >> select;

		if (select == 1) {			//patient 메뉴
			handler.ShowPatientMenu();
			cout << "선택할 번호를 입력해주세요 : ";
			cin >> select;
			switch (select)
			{
			case 1:
				handler.RegisterPatient();
				break;
			case 2:
				handler.Reservation();
				break;
			case 3:
				handler.FindPatient();
				break;
			case 4:
				handler.BeTreated();
			case 5:
				continue;
			default:
				cout << "잘못된 번호를 입력하셨습니다" << endl;
				break;
			}
		}
		else if (select == 2) {			//hospital 메뉴
			handler.ShowHospitalMenu();
			cout << "선택할 번호를 입력해주세요 : ";
			cin >> select;
			switch (select)
			{
			case 1:
				handler.RegisterHospital();
				break;
			case 2:
				handler.FindHospital();
				break;
			case 3:
				continue;
			default:
				cout << "잘못된 번호를 입력하셨습니다" << endl;
				break;
			}
		}
		else if (select == 3) {			//관리자 메뉴
			handler.ShowManagerMenu();
			cout << "선택할 번호를 입력해주세요 : ";
			cin >> select;
			switch (select)
			{
			case 1:
				handler.ShowAllPatient();
				break;
			case 2:
				handler.ShowAllHospital();
				break;
			case 3:
				handler.Stats();
				break;
			case 4:
				continue;
			default:
				cout << "잘못된 번호를 입력하셨습니다" << endl;
				break;
			}
		}
		else if (select == 4) {
			cout << "종료하겠습니다" << endl;
			stop = 0;
		}
		else {
			cout << "잘못된 번호를 입력하셨습니다" << endl;
			cin.clear();	//잘못된 입력으로 cin 내부가 false로 설정되어있는 부분 초기화
			cin.ignore(100, '\n');
		}
	}	//while(1) end

	handler.SaveData();
}