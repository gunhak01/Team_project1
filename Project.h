#ifndef _PROJECT_
#define _PROJECT_

#include "vld.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>

using namespace std;

#define PAT_SZ 50
#define HOS_SZ 50

class Patient
{
private:
	char name[20];
	char phone[20];
	int cost;					//병원비
	bool reser;					//예약중이면 true, 아니면 false
	int hos_index;				//어떤 병원에 예약했는지
public:
	Patient() { }
	Patient(const char* _name, const char* _phone)
	{
		cost = 0;
		hos_index = -1;
		reser = false;
		strcpy(name, _name);
		strcpy(phone, _phone);
	}
	virtual void showInfo()
	{
		cout << "이름 : " << name << " 번호 : " << phone << " 예약여부 : " << (reser ? "예약함" : "예약안함");
	}
	void showInfoRestrict()		//제한된 정보만 출력
	{
		cout << "이름 : " << name << " 번호 : " << phone << endl;
	}
	char* getNames()
	{
		return name;
	}
	char* getPhones()
	{
		return phone;
	}
	void setReser(bool _reser)
	{
		reser = _reser;
	}
	void setHosIndex(int _index)
	{
		hos_index = _index;
	}
	void setCost(int _cost)
	{
		cost = _cost;
	}
	int getHosIndex()
	{
		return hos_index;
	}
	bool getReser()
	{
		return reser;
	}
	virtual double getDisRate() = 0;
	virtual void save(ofstream& fout, Patient* patList[], int i) = 0;
};

class ExternalPatient : public Patient
{
private:
	char country[20];			//해외국가
	double dis_rate;			//병원비 공제율
	int size;					//객체크기(save, load)
public:
	ExternalPatient()
	{
		dis_rate = 0.3;
	}
	ExternalPatient(const char* _name, const char* _phone, const char* _country) : Patient(_name, _phone)
	{
		dis_rate = 0.3;
		strcpy(country, _country);
	}
	void showInfo()
	{
		Patient::showInfo();
		cout << " 해외입국자 - 국가 : " << country << endl;
	}
	double getDisRate()
	{
		return dis_rate;
	}
	void save(ofstream& fout, Patient* patList[], int i)
	{
		size = sizeof(ExternalPatient);
		fout.write((char*)&size, sizeof(int));
		fout.write((char*)patList[i], size);
	}
};

class InternalPatient : public Patient
{
private:
	double dis_rate;
	int size;
public:
	InternalPatient()
	{
		dis_rate = 0.5;
	}
	InternalPatient(const char* _name, const char* _phone) : Patient(_name, _phone)
	{
		dis_rate = 0.5;
	}
	void showInfo()
	{
		Patient::showInfo();
		cout << " 국내거주자" << endl;
	}
	double getDisRate()
	{
		return dis_rate;
	}
	void save(ofstream& fout, Patient* patList[], int i)
	{
		size = sizeof(InternalPatient);
		fout.write((char*)&size, sizeof(int));
		fout.write((char*)patList[i], size);
	}
};


class Hospital
{
private:
	char name[20];
	int treatTime;	//1명당 소요시간
	int pcrNum;		//진단키트 수
	int patNum;		//예약중인 환자수
	int patID[50];	//몇번 환자가 예약했는지 저장
	int infectThisHos;	//해당병원의 확진자수
public:
	Hospital()
	{
		treatTime = 15;
		patNum = 0;
		infectThisHos = 0;
	}
	Hospital(const char* _name, int _pcrNum)
	{
		treatTime = 15;
		patNum = 0;
		infectThisHos = 0;
		strcpy(name, _name);
		pcrNum = _pcrNum;
	}
	void showInfo()
	{
		cout << "병원명 : " << name << " " << "소요시간 : " << treatTime * (patNum + 1) << " " << "진단키드 수 : " << pcrNum << " " << "예약자 수 : " << patNum << endl;
	}
	void plusPatNum()
	{
		patNum++;
	}
	void minusPatNum()
	{
		patNum--;
	}
	void minusPcrNum()
	{
		pcrNum--;
	}
	char* getName()
	{
		return name;
	}
	void plusInfectThisHos()
	{
		infectThisHos++;
	}
	int getInfectThisHos()
	{
		return infectThisHos;
	}
};

class HospitalHandler
{
private:
	Patient* patList[PAT_SZ];
	Hospital* hosList[HOS_SZ];
	int patNum;		//환자수
	int hosNum;		//병원수
	int infectNum;
	int expatListFile[PAT_SZ];
	int inpatListFile[PAT_SZ];
	int expatNumFile;
	int inpatNumFile;
public:
	HospitalHandler()
	{
		patNum = 0;
		hosNum = 0;
		infectNum = 0;
		expatNumFile = 0;
		inpatNumFile = 0;
	}
	~HospitalHandler()
	{
		cout << "~HospitalHandler()" << endl;
		for (int i = 0; i < patNum; i++)
		{
			delete patList[i];
		}
		for (int i = 0; i < hosNum; i++)
		{
			delete hosList[i];
		}
	}
	void ShowMenu();
	void ShowPatientMenu();
	void ShowHospitalMenu();
	void ShowManagerMenu();
	void RegisterPatient();
	void FindPatient();
	void Reservation();
	void ReservationHosSelect(int _patTmp, int* sameName);
	void BeTreated();
	bool BeTreatedNotReser(int _patTmp, int* sameName);
	void BeTreatedResult(int _patTmp, int* sameName);
	void Infected();
	void RegisterHospital();
	void FindHospital();
	void ShowAllPatient();
	void ShowAllHospital();
	void Stats();
	void SaveData();
	void LoadData();
};

#endif