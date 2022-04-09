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
	int cost;					//������
	bool reser;					//�������̸� true, �ƴϸ� false
	int hos_index;				//� ������ �����ߴ���
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
		cout << "�̸� : " << name << " ��ȣ : " << phone << " ���࿩�� : " << (reser ? "������" : "�������");
	}
	void showInfoRestrict()		//���ѵ� ������ ���
	{
		cout << "�̸� : " << name << " ��ȣ : " << phone << endl;
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
	char country[20];			//�ؿܱ���
	double dis_rate;			//������ ������
	int size;					//��üũ��(save, load)
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
		cout << " �ؿ��Ա��� - ���� : " << country << endl;
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
		cout << " ����������" << endl;
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
	int treatTime;	//1��� �ҿ�ð�
	int pcrNum;		//����ŰƮ ��
	int patNum;		//�������� ȯ�ڼ�
	int patID[50];	//��� ȯ�ڰ� �����ߴ��� ����
	int infectThisHos;	//�ش纴���� Ȯ���ڼ�
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
		cout << "������ : " << name << " " << "�ҿ�ð� : " << treatTime * (patNum + 1) << " " << "����Ű�� �� : " << pcrNum << " " << "������ �� : " << patNum << endl;
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
	int patNum;		//ȯ�ڼ�
	int hosNum;		//������
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