#include "Project.h"

void HospitalHandler::ShowMenu()
{
	cout << "Menu------" << endl;
	cout << "1. 환자" << endl;
	cout << "2. 병원" << endl;
	cout << "3. 관리자" << endl;
	cout << "4. 종료" << endl;
}

void HospitalHandler::ShowPatientMenu()
{
	cout << "환자------" << endl;
	cout << "1. 환자등록" << endl;
	cout << "2. 진료예약" << endl;
	cout << "3. 환자검색" << endl;
	cout << "4. 진료완료" << endl;
	cout << "5. 뒤로가기" << endl;
}

void HospitalHandler::ShowHospitalMenu()
{
	cout << "병원------" << endl;
	cout << "1. 병원등록" << endl;
	cout << "2. 병원검색" << endl;
	cout << "3. 뒤로가기" << endl;
}

void HospitalHandler::ShowManagerMenu()
{
	cout << "관리자------" << endl;
	cout << "1. 전체 환자 출력" << endl;
	cout << "2. 전체 병원 출력" << endl;
	cout << "3. 통계 확인" << endl;
	cout << "4. 뒤로가기" << endl;
}

void HospitalHandler::RegisterPatient()
{
	char name[20], phone[20], abroad[20];
	int prereser, hos_index, preabroad, Patdata;
	string tmp;//

	cout << "\n성명을 입력해 주세요(end : 입력 종료) : ";
	cin >> name;
	if (strcmp(name, "end") == 0) {
		return;
	}

	cout << "전화번호(숫자만 입력해주세요) : ";
	//cin >> phone;
	cin >> tmp;

	for (int i = 0; i < tmp.length(); i++) {
		char c = tmp.at(i);
		if (c < 48 || c> 57) {//숫자가 아닌 경우
			cout << "잘못된 번호 형식입니다. 다시 입력해주세요" << endl;
			cout << "메뉴로 돌아갑니다" << endl;
			return;
		}
	}
	if (tmp.size() != 11) {
		cout << "잘못된 번호 형식입니다. 다시 입력해주세요" << endl;
		cout << "메뉴로 돌아갑니다" << endl;
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
				cout << "이미 등록하신 환자입니다.\n";
				cout << "======================================== \n";
				cout << "";

				return;
			}
		}
	}
	cout << "\n해외 입국자 이신가요? \n";
	cout << "맞으면 0, 아니면 1을 입력해 주세요 : ";
	cin >> preabroad;

	if (preabroad == 0)
	{
		cout << "\n방문한 나라를 적어주세요: ";
		cin >> abroad;
		cout << "======================================== \n";
		cout << "해외 환자로 등록이 완료되었습니다. \n";
		cout << "추후 병원예약을 원할 시 환자 목록에서 [2.진료예약]으로 가주십시오.\n";
		cout << "목록으로 돌아갑니다. \n";
		cout << "======================================== \n";
		cout << "\n";
		expatListFile[expatNumFile] = patNum;	//파일입출력 위한 배열에 추가
		expatNumFile++;
		patList[patNum] = new ExternalPatient(name, phone, abroad);
	}
	else
	{
		cout << "======================================== \n";
		cout << "국내 환자로 등록이 완료되었습니다. \n";
		cout << "추후 병원예약을 원할 시 환자 목록에서 [2.진료예약]으로 가주십시오.\n";
		cout << "목록으로 돌아갑니다. \n";
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
	cout << "이름을 입력하시오 : ";
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
	int num = 0;	//해당 이름이 몇명인지 확인
	int patTmp;
	char yesnoTmp;
	int sameName[5];	//동명이인 체크

	cout << "이름을 입력하시오 : ";
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
		cout << "본인이 맞으신가요? (y/n) ";
		cin >> yesnoTmp;
		if (yesnoTmp == 'y') {
			ReservationHosSelect(0, sameName);
		}
		else {
			cout << "다시 입력해주세요" << endl;
		}
	}
	else {
		cout << "같은 이름이 여러명 있습니다" << endl;
		for (int i = 0; i < num; i++) {
			cout << i << "번 : ";
			(*(patList[sameName[i]])).showInfoRestrict();
		}
		cout << "본인에 해당하는 번호를 골라주세요 : ";
		cin >> patTmp;
		ReservationHosSelect(patTmp, sameName);
	}
}

void HospitalHandler::ReservationHosSelect(int _patTmp, int* sameName)
{
	int hosTmp;
	int validTmp = 1;	//유효한 병원번호인지 확인
	if ((*(patList[sameName[_patTmp]])).getReser() == true) {	//이미 예약한 사람인지 체크
		cout << "이미 예약하셨습니다." << endl;
		cout << "목록으로 돌아갑니다." << endl;
		return;
	}

	for (int i = 0; i < hosNum; i++) {
		cout << i << "번 - ";
		(*(hosList[i])).showInfo();
	}

	while (validTmp) {
		cout << "예약하실 병원번호를 골라주세요 : ";
		cin >> hosTmp;
		if (hosTmp >= 0 && hosTmp < hosNum) {		//병원번호 오류처리
			cout << (*(patList[sameName[_patTmp]])).getNames() << " - " << (*(hosList[hosTmp])).getName() << " : 예약되었습니다" << endl;
			(*(patList[sameName[_patTmp]])).setReser(true);
			(*(patList[sameName[_patTmp]])).setHosIndex(hosTmp);
			(*(hosList[hosTmp])).plusPatNum();
			validTmp = 0;	//반복문 나감
		}
		else {
			cout << "유효한 병원번호를 입력해주세요" << endl;
		}
	}
}

void HospitalHandler::BeTreated()
{
	char name[20];
	int num = 0;
	int patTmp;
	char yesnoTmp;
	int sameName[5];	//동명이인 체크
	bool reserTmp;		//예약여부 확인

	cout << "이름을 입력하시오 : ";
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
		cout << "본인이 맞으신가요? (y/n) ";
		cin >> yesnoTmp;
		if (yesnoTmp == 'y') {
			reserTmp = BeTreatedNotReser(0, sameName);	//예약했는지 확인
			if (reserTmp == false) {
				return;
			}
			BeTreatedResult(0, sameName);
		}
		else {
			cout << "다시 입력해주세요" << endl;
		}
	}
	else {
		for (int i = 0; i < num; i++) {
			cout << i << "번 : ";
			(*(patList[sameName[i]])).showInfo();
		}
		cout << "본인에 해당하는 번호를 골라주세요 : ";
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
		cout << "예약을 하신분만 진료를 받을 수 있습니다." << endl;
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

	cout << "결과를 확인중입니다." << endl;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, 1);
	int positive = dist(gen);

	if (positive == 0) {
		cout << "음성입니다." << endl;
		cost = 10000 * ((*(patList[sameName[_patTmp]])).getDisRate());
		cout << "진료비는 " << cost << "원 입니다" << endl;
	}
	else {
		cout << "양성입니다." << endl;
		(*(hosList[hosTmp])).plusInfectThisHos();

		infectNum++;
		cost = 30000 * ((*(patList[sameName[_patTmp]])).getDisRate());
		cout << "진료비는 " << cost << "원 입니다" << endl;
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

void HospitalHandler::RegisterHospital() //1.병원등록 
{
	char name[20];
	int pcrNum;

	cout << "등록 하실 병원명을 입력하세요" << endl;
	cin >> name;
	if (strcmp(name, "뒤로가기") == 0)
	{
		//return ;
	}
	cout << "초기 보유 신속 항원 검사 키트 개수" << endl;
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
		cout << "\n신속 항원 검사 가능 병원 조회 (검색종료:end) ";
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

	}//while (1) end예외 발생(0x00ECC3F0, Team_project1.exe): 0xC0000005: 0x00E0B1B8 위치를 읽는 동안 액세스 위반이 발생했습니다..
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
	cout << "등록된 총 환자 수 : " << patNum << endl;
	cout << "등록된 총 병원 수 : " << hosNum << endl;
	cout << "총 누적 확진자 수 : " << infectNum << endl;
	cout << "병원 별 확진자 수" << endl;
	for (int i = 0; i < hosNum; i++) {
		cout << (*(hosList[i])).getName() << " : " << (*(hosList[i])).getInfectThisHos() << "명" << endl;
	}
}

void HospitalHandler::SaveData()
{
	const char* file = "emps.dat";

	ofstream fout;
	fout.open(file, ios::out | ios::binary); // 읽기모드

	if (!fout)
	{
		cout << "SaveData() 파일 열기 오류" << endl;
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
	fin.open(file, ios::in | ios::binary); // 읽기모드

	if (!fin)
	{
		cout << "LoadData() 파일 없음" << endl;
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