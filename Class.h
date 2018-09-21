#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class SimplePerson { // 전화번호부에 저장되는 사람
public:
	SimplePerson(string _name, string _ph, string _de = "");
	void output();

	string getName() const {
		return this->name;
	}
	string getPhonenum() const {
		return this->phonenum;
	}
	string getDescription() const {
		return this->description;
	}
private:
	string name;
	string phonenum;
	string description;
};

class PhoneBook { // 전화번호부
public:
	PhoneBook();
	void addPerson(string _name, string _ph, string _de); // 연락처 추가
	void output();
	void search(string _data); // 검색
	void save_Data(string _pa); // 연락처 저장
	void del_Person(string _data); // 연락처 삭제

private:
	map<string, SimplePerson> persons;
};

class Message { // 메세지
public:
	Message(string _addresser, string _document);
	void output();
	string getDocument() {
		return document;
	}

	string getAddresser() {
		return addresser;
	}

private:
	string document;
	string addresser; // 발신인
};

class MessageBox { // 메세지함
public:
	MessageBox();
	void addMessage(Message m);
	void outputMessage();
	void delMessage(int _index);
	void save_Data(string _pa);

private:
	vector<Message> messages;
};

class Member { // 회원
public:
	Member(string _name, string _ph, string _id, string _pw, string _pa);
	Member();
	void addPerson();
	void addPerson(string _name, string _ph, string _de);
	void output();
	void search();
	void save_Data(); // 데이터 저장
	void del_Person();
	void send_Message(string _pa);
	void addMessage(string _na, string _docu);
	void outputMessage();
	void delMessage(int _index);

	string getName() const {
		return this->name;
	}
	string getPhonenum() const {
		return this->phonenum;
	}
	string getId() const {
		return this->id;
	}
	string getPassword() const {
		return this->password;
	}
	string getPath() const {
		return this->path;
	}
private:
	string name;
	string phonenum;
	string id;
	string password;
	string path; // 회원의 개인 디렉토리 경로
	MessageBox messagebox; // 메세지함
	PhoneBook phonebook; // 전화번호부
};

class Manager { // 실행매니저
public:
	Manager();
	~Manager();
	void login();
	void logout();
	void make_Account(); // 회원가입
	void load_Data(string _id); // 회원 데이터를 불러온다
	void make_Path(string _id); // 디렉토리 경로를 만든다
	void beginning_Screen(); // 초기화면
	void login_Screen(); // 로그인 후 화면
	bool search(string _id, string _pw, string _ph, string _type); // 회원검색

private:
	Member* user; // 현재 로그인 하고있는 회원
	string path; // 코드가 실행된 디렉토리 경로
	ofstream out; // 파일입출력
	ifstream in;
};