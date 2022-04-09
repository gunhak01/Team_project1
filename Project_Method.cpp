#include "Project.h"

void HospitalHandler::ShowMenu()
{
	cout << "Menu------" << endl;
	cout << "1. ȯ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. ������" << endl;
	cout << "4. ����" << endl;
}

void HospitalHandler::ShowPatientMenu()
{
	cout << "ȯ��------" << endl;
	cout << "1. ȯ�ڵ��" << endl;
	cout << "2. ���Ό��" << endl;
	cout << "3. ȯ�ڰ˻�" << endl;
	cout << "4. ����Ϸ�" << endl;
	cout << "5. �ڷΰ���" << endl;
}

void HospitalHandler::ShowHospitalMenu()
{
	cout << "����------" << endl;
	cout << "1. �������" << endl;
	cout << "2. �����˻�" << endl;
	cout << "3. �ڷΰ���" << endl;
}

void HospitalHandler::ShowManagerMenu()
{
	cout << "������------" << endl;
	cout << "1. ��ü ȯ�� ���" << endl;
	cout << "2. ��ü ���� ���" << endl;
	cout << "3. ��� Ȯ��" << endl;
	cout << "4. �ڷΰ���" << endl;
}

void HospitalHandler::RegisterPatient()
{
	char name[20], phone[20], abroad[20];
	int prereser, hos_index, preabroad, Patdata;
	string tmp;//

	cout << "\n������ �Է��� �ּ���(end : �Է� ����) : ";
	cin >> name;
	if (strcmp(name, "end") == 0) {
		return;
	}

	cout << "��ȭ��ȣ(���ڸ� �Է����ּ���) : ";
	//cin >> phone;
	cin >> tmp;

	for (int i = 0; i < tmp.length(); i++) {
		char c = tmp.at(i);
		if (c < 48 || c> 57) {//���ڰ� �ƴ� ���
			cout << "�߸��� ��ȣ �����Դϴ�. �ٽ� �Է����ּ���" << endl;
			cout << "�޴��� ���ư��ϴ�" << endl;
			return;
		}
	}
	if (tmp.size() != 11) {
		cout << "�߸��� ��ȣ �����Դϴ�. �ٽ� �Է����ּ���" << endl;
		cout << "�޴��� ���ư��ϴ�" << endl;
		return;
	}
	tmp.insert(3, "-");
	tmp.insert(8, "-");
	strcpy(phone, tmp.c_str());

	for (int i = 0; i < patNum; i++) {
		if (strcmp(name, (*(patList[i])).getNames()) == 0) {
			if (strcmp(phone, (*(patList[i])).getPhones()) == 0) {
				cout << "";
				cout << "======================================== \n";
				cout << "�̹� ����Ͻ� ȯ���Դϴ�.\n";
				cout << "======================================== \n";
				cout << "";

				return;
			}
		}
	}
	cout << "\n�ؿ� �Ա��� �̽Ű���? \n";
	cout << "������ 0, �ƴϸ� 1�� �Է��� �ּ��� : ";
	cin >> preabroad;

	if (preabroad == 0)
	{
		cout << "\n�湮�� ���� �����ּ���: ";
		cin >> abroad;
		cout << "======================================== \n";
		cout << "�ؿ� ȯ�ڷ� ����� �Ϸ�Ǿ����ϴ�. \n";
		cout << "���� ���������� ���� �� ȯ�� ��Ͽ��� [2.���Ό��]���� ���ֽʽÿ�.\n";
		cout << "������� ���ư��ϴ�. \n";
		cout << "======================================== \n";
		cout << "\n";
		expatListFile[expatNumFile] = patNum;	//��������� ���� �迭�� �߰�
		expatNumFile++;
		patList[patNum] = new ExternalPatient(name, phone, abroad);
	}
	else
	{
		cout << "======================================== \n";
		cout << "���� ȯ�ڷ� ����� �Ϸ�Ǿ����ϴ�. \n";
		cout << "���� ���������� ���� �� ȯ�� ��Ͽ��� [2.���Ό��]���� ���ֽʽÿ�.\n";
		cout << "������� ���ư��ϴ�. \n";
		cout << "======================================== \n";
		cout << "\n";
		inpatListFile[inpatNumFile] = patNum;
		inpatNumFile++;
		patList[patNum] = new InternalPatient(name, phone);
	}

	patNum++;
}

void HospitalHandler::FindPatient()
{
	char name[20];
	int sameName[5];
	int num = 0;
	int patTmp;
	char yesnoTmp;
	cout << "�̸��� �Է��Ͻÿ� : ";
	cin >> name;
	for (int i = 0; i < patNum; i++) {
		if (strcmp(name, (*(patList[i])).getNames()) == 0) {
			sameName[num] = i;
			num++;
		}
	}
	if (num == 0) {
		cout << name << ", Not found!!!" << endl;
	}
	else {
		for (int i = 0; i < num; i++) {
			(*(patList[sameName[i]])).showInfo();
		}
	}
}

void HospitalHandler::Reservation()
{
	char name[20];
	int num = 0;	//�ش� �̸��� ������� Ȯ��
	int patTmp;
	char yesnoTmp;
	int sameName[5];	//�������� üũ

	cout << "�̸��� �Է��Ͻÿ� : ";
	cin >> name;
	cout << endl;
	for (int i = 0; i < patNum; i++) {
		if (strcmp(name, (*(patList[i])).getNames()) == 0) {
			sameName[num] = i;
			num++;
		}
	}
	if (num == 0) {
		cout << name << ", Not found!!!" << endl;
	}
	else if (num == 1) {
		(*(patList[sameName[0]])).showInfoRestrict();
		cout << "������ �����Ű���? (y/n) ";
		cin >> yesnoTmp;
		if (yesnoTmp == 'y') {
			ReservationHosSelect(0, sameName);
		}
		else {
			cout << "�ٽ� �Է����ּ���" << endl;
		}
	}
	else {
		cout << "���� �̸��� ������ �ֽ��ϴ�" << endl;
		for (int i = 0; i < num; i++) {
			cout << i << "�� : ";
			(*(patList[sameName[i]])).showInfoRestrict();
		}
		cout << "���ο� �ش��ϴ� ��ȣ�� ����ּ��� : ";
		cin >> patTmp;
		ReservationHosSelect(patTmp, sameName);
	}
}

void HospitalHandler::ReservationHosSelect(int _patTmp, int* sameName)
{
	int hosTmp;
	int validTmp = 1;	//��ȿ�� ������ȣ���� Ȯ��
	if ((*(patList[sameName[_patTmp]])).getReser() == true) {	//�̹� ������ ������� üũ
		cout << "�̹� �����ϼ̽��ϴ�." << endl;
		cout << "������� ���ư��ϴ�." << endl;
		return;
	}

	for (int i = 0; i < hosNum; i++) {
		cout << i << "�� - ";
		(*(hosList[i])).showInfo();
	}

	while (validTmp) {
		cout << "�����Ͻ� ������ȣ�� ����ּ��� : ";
		cin >> hosTmp;
		if (hosTmp >= 0 && hosTmp < hosNum) {		//������ȣ ����ó��
			cout << (*(patList[sameName[_patTmp]])).getNames() << " - " << (*(hosList[hosTmp])).getName() << " : ����Ǿ����ϴ�" << endl;
			(*(patList[sameName[_patTmp]])).setReser(true);
			(*(patList[sameName[_patTmp]])).setHosIndex(hosTmp);
			(*(hosList[hosTmp])).plusPatNum();
			validTmp = 0;	//�ݺ��� ����
		}
		else {
			cout << "��ȿ�� ������ȣ�� �Է����ּ���" << endl;
		}
	}
}

void HospitalHandler::BeTreated()
{
	char name[20];
	int num = 0;
	int patTmp;
	char yesnoTmp;
	int sameName[5];	//�������� üũ
	bool reserTmp;		//���࿩�� Ȯ��

	cout << "�̸��� �Է��Ͻÿ� : ";
	cin >> name;
	for (int i = 0; i < patNum; i++) {
		if (strcmp(name, (*(patList[i])).getNames()) == 0) {
			sameName[num] = i;
			num++;
		}
	}
	if (num == 0) {
		cout << name << ", Not found!!!" << endl;
	}
	else if (num == 1) {
		(*(patList[sameName[0]])).showInfo();
		cout << "������ �����Ű���? (y/n) ";
		cin >> yesnoTmp;
		if (yesnoTmp == 'y') {
			reserTmp = BeTreatedNotReser(0, sameName);	//�����ߴ��� Ȯ��
			if (reserTmp == false) {
				return;
			}
			BeTreatedResult(0, sameName);
		}
		else {
			cout << "�ٽ� �Է����ּ���" << endl;
		}
	}
	else {
		for (int i = 0; i < num; i++) {
			cout << i << "�� : ";
			(*(patList[sameName[i]])).showInfo();
		}
		cout << "���ο� �ش��ϴ� ��ȣ�� ����ּ��� : ";
		cin >> patTmp;
		reserTmp = BeTreatedNotReser(patTmp, sameName);
		if (reserTmp == false) {
			return;
		}
		BeTreatedResult(patTmp, sameName);
	}
}

bool HospitalHandler::BeTreatedNotReser(int _patTmp, int* sameName)
{
	if ((*(patList[sameName[_patTmp]])).getReser() == false)
	{
		cout << "========================================" << endl;
		cout << "������ �Ͻźи� ���Ḧ ���� �� �ֽ��ϴ�." << endl;
		cout << "========================================" << endl;
		return false;
	}
	else
		return true;
}

void HospitalHandler::BeTreatedResult(int _patTmp, int* sameName)
{
	int cost;
	int hosTmp;
	hosTmp = (*(patList[sameName[_patTmp]])).getHosIndex();

	cout << "����� Ȯ�����Դϴ�." << endl;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, 1);
	int positive = dist(gen);

	if (positive == 0) {
		cout << "�����Դϴ�." << endl;
		cost = 10000 * ((*(patList[sameName[_patTmp]])).getDisRate());
		cout << "������ " << cost << "�� �Դϴ�" << endl;
	}
	else {
		cout << "�缺�Դϴ�." << endl;
		(*(hosList[hosTmp])).plusInfectThisHos();

		infectNum++;
		cost = 30000 * ((*(patList[sameName[_patTmp]])).getDisRate());
		cout << "������ " << cost << "�� �Դϴ�" << endl;
	}
	(*(hosList[hosTmp])).minusPcrNum();
	(*(hosList[hosTmp])).minusPatNum();
	(*(patList[sameName[_patTmp]])).setCost(cost);
	(*(patList[sameName[_patTmp]])).setReser(false);

}

void HospitalHandler::Infected()
{
	infectNum++;
}

void HospitalHandler::RegisterHospital() //1.������� 
{
	char name[20];
	int pcrNum;

	cout << "��� �Ͻ� �������� �Է��ϼ���" << endl;
	cin >> name;
	if (strcmp(name, "�ڷΰ���") == 0)
	{
		//return ;
	}
	cout << "�ʱ� ���� �ż� �׿� �˻� ŰƮ ����" << endl;
	cin >> pcrNum;

	hosList[hosNum] = new Hospital(name, pcrNum);
	hosNum++;

}

void HospitalHandler::FindHospital()
{
	int i, found;
	char name[20];
	int num = 0;

	while (1)
	{
		cout << "\n�ż� �׿� �˻� ���� ���� ��ȸ (�˻�����:end) ";
		cin >> name;
		if (strcmp(name, "end") == 0)
			break;

		found = 1;

		for (i = 0; i < hosNum; i++)
		{
			if (strcmp(name, (*(hosList[i])).getName()) == 0)
			{
				found = 0;
				(*(hosList[i])).showInfo();

			}
		}

		if (found)
			cout << name << ", Not found !!! " << endl;

	}//while (1) end���� �߻�(0x00ECC3F0, Team_project1.exe): 0xC0000005: 0x00E0B1B8 ��ġ�� �д� ���� �׼��� ������ �߻��߽��ϴ�..
}

void HospitalHandler::ShowAllPatient()
{
	for (int i = 0; i < patNum; i++)
	{
		(*(patList[i])).showInfo();
	}
}

void HospitalHandler::ShowAllHospital()
{
	for (int i = 0; i < hosNum; i++)
	{
		(*(hosList[i])).showInfo();
	}
}

void HospitalHandler::Stats()
{
	cout << "��ϵ� �� ȯ�� �� : " << patNum << endl;
	cout << "��ϵ� �� ���� �� : " << hosNum << endl;
	cout << "�� ���� Ȯ���� �� : " << infectNum << endl;
	cout << "���� �� Ȯ���� ��" << endl;
	for (int i = 0; i < hosNum; i++) {
		cout << (*(hosList[i])).getName() << " : " << (*(hosList[i])).getInfectThisHos() << "��" << endl;
	}
}

void HospitalHandler::SaveData()
{
	const char* file = "emps.dat";

	ofstream fout;
	fout.open(file, ios::out | ios::binary); // �б���

	if (!fout)
	{
		cout << "SaveData() ���� ���� ����" << endl;
		return;
	}

	fout.write((char*)&patNum, sizeof(patNum));
	fout.write((char*)&hosNum, sizeof(hosNum));
	fout.write((char*)&infectNum, sizeof(infectNum));

	for (int i = 0; i < patNum; i++) {
		(*(patList[i])).save(fout, patList, i);
	}
	for (int i = 0; i < hosNum; i++) {
		fout.write((char*)(hosList[i]), sizeof(Hospital));
	}

	fout.close();

	printf("ems.dat Save !!! \n");
}

void HospitalHandler::LoadData()
{
	const char* file = "emps.dat";
	Patient* ptr;

	ifstream fin;
	fin.open(file, ios::in | ios::binary); // �б���

	if (!fin)
	{
		cout << "LoadData() ���� ����" << endl;
		return;
	}

	fin.read((char*)&patNum, sizeof(patNum));
	fin.read((char*)&hosNum, sizeof(hosNum));
	fin.read((char*)&infectNum, sizeof(infectNum));

	int size = 0;

	for (int i = 0; i < patNum; i++)
	{
		fin.read((char*)&size, sizeof(int));
		if (size == sizeof(InternalPatient)) {
			patList[i] = new InternalPatient;
			fin.read((char*)(patList[i]), sizeof(InternalPatient));
		}
		else if (size == sizeof(ExternalPatient)) {
			patList[i] = new ExternalPatient;
			fin.read((char*)(patList[i]), sizeof(ExternalPatient));
		}
	}
	for (int i = 0; i < hosNum; i++)
	{
		hosList[i] = new Hospital;
		fin.read((char*)(hosList[i]), sizeof(Hospital));
	}

	fin.close();

	printf("ems.dat Load!!! \n");
}