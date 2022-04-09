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
		cout << "������ ��ȣ�� �Է����ּ��� : ";
		cin >> select;

		if (select == 1) {			//patient �޴�
			handler.ShowPatientMenu();
			cout << "������ ��ȣ�� �Է����ּ��� : ";
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
				cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�" << endl;
				break;
			}
		}
		else if (select == 2) {			//hospital �޴�
			handler.ShowHospitalMenu();
			cout << "������ ��ȣ�� �Է����ּ��� : ";
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
				cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�" << endl;
				break;
			}
		}
		else if (select == 3) {			//������ �޴�
			handler.ShowManagerMenu();
			cout << "������ ��ȣ�� �Է����ּ��� : ";
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
				cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�" << endl;
				break;
			}
		}
		else if (select == 4) {
			cout << "�����ϰڽ��ϴ�" << endl;
			stop = 0;
		}
		else {
			cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�" << endl;
			cin.clear();	//�߸��� �Է����� cin ���ΰ� false�� �����Ǿ��ִ� �κ� �ʱ�ȭ
			cin.ignore(100, '\n');
		}
	}	//while(1) end

	handler.SaveData();
}