#pragma once
#include "Class.h"
#include "Message_Class.h"
#include "Person_Class.h"
#include "print.h"
#include <conio.h>
#include <direct.h> // _mkdir 함수
#include <io.h> // _access 함수
#define _MAX_PATH 260

/*        Manager Class           */

Manager::Manager() {       // 생성자
	char strBuffer[_MAX_PATH] = { 0, };
	char *pstrBuffer = NULL;
	pstrBuffer = _getcwd(strBuffer, _MAX_PATH);
	//             경로    버퍼       버퍼크기

	for (int i = 0; pstrBuffer[i] != '\0'; i++) {
		if (pstrBuffer[i] == '\\') // \문자자체를 사용하기위해 \\사용
			pstrBuffer[i] = '/';
	}

	this->path = pstrBuffer; // 현재 실행된 경로
	this->user = nullptr; // 현재 로그인된 사용자 없음

	if (_access("account_list.txt", 00) == -1) { // 파일이 존재하면 0, 없으면 -1
		out.open("account_list.txt");
		out << "계정 목록" << endl;
		out.close();
	}
}

Manager::~Manager() {       // 소멸자
	delete user;
}

void Manager::login() {      // 로그인
	string _id = "", _pw = "";
	char ch = NULL;

	do {
		_id = _pw = "";
		cout << ">> Login" << endl;
		cout << "ID: ";
		cin >> _id;
		while (getchar() != '\n'); // 띄어쓰기가 입력될 때를 대비해 버퍼를 비운다
		cout << "Password: ";  // password는 *로 출력
		ch = _getch();
		while (ch != 13) {  // ch가 Enter(13)면 종료
			if (ch == 8) {  // ch가 백스페이스(8)이면 지우기
				if (_pw.length() != 0) { // _pw의 길이가 0일때는 지우지않는다
					_pw.pop_back();
					cout << "\b \b";
				}
			}
			else {
				_pw.push_back(ch);
				cout << "*";
			}
			ch = _getch();
		}
		cout << endl;

		if (search(_id, _pw, "", "login")) { // id와 password가 일치하는지 확인
			cout << "로그인 성공! 데이터 로드중.." << endl << endl;
			load_Data(_id);
			break;
		}
		else
			cout << "ID나 비밀번호가 잘못 입력되었습니다." << endl << endl;
	} while (1);

	login_Screen();
}

void Manager::logout() {
	user->save_Data(); // 로그아웃 전에 유저의 데이터를 저장

	delete this->user;
	this->user = nullptr; // user 초기화

	cout << "로그아웃 성공..." << endl;
	cout << "메뉴로 가려면 아무키나 누르세요..";
	getchar();
	beginning_Screen();
}

void Manager::make_Account() {
	string _id = "", _pw = "", _name = "", _ph = "";
	char ch = NULL;

	while (1) {
		_id = _pw = _name = _ph = "";
		cout << ">> Create account" << endl;
		// id
		cout << "ID를 입력하세요: ";
		cin >> _id;
		while (getchar() != '\n');

		// password
		cout << "패스워드를 입력하세요: ";
		ch = _getch();
		while (ch != 13) {  // ch가 Enter(13)면 종료
			if (ch == 8) {  // ch가 백스페이스(8)이면 지우기
				if (_pw.length() != 0) { // _pw의 길이가 0일때는 지우지않는다
					_pw.pop_back();
					cout << "\b \b";
				}
			}
			else {
				_pw.push_back(ch);
				cout << "*";
			}
			ch = _getch();
		}
		cout << endl;

		// name
		cout << "이름을 입력하세요: ";
		cin >> _name;
		while (getchar() != '\n');

		// phone number
		cout << "핸드폰 번호를 입력하세요(띄어쓰기와 -는 제외): ";
		cin >> _ph;
		while (getchar() != '\n');

		if (search(_id, "", _ph, "make"))
			cout << "이미 존재하는 ID이거나 등록된 핸드폰 번호입니다." << endl << endl;
		else
			break;
	}

	out.open("account_list.txt", ios::app); // 이어쓰기
	out << _id << " " << _pw << " " << _name << " " << _ph << endl;
	out.close();

	make_Path(_ph);
}

bool Manager::search(string _id, string _pw, string _ph, string _type) {
	in.open("account_list.txt");
	string search_id = "", search_pw = "", search_name = "", search_ph = "";
	string tem_data = "";
	getline(in, tem_data); // 첫행건너뛰기


	while (!in.eof()) {   //존재 유무 검사
		in >> search_id >> search_pw >> search_name >> search_ph;

		if (_type == "make" && (_id == search_id || _ph == search_ph)) { // 계정 생성시 번호나 아이디가 겹친다면
			in.close();
			return true;
		}
		else if (_type == "login" && _id == search_id && _pw == search_pw) { // 로그인시 id와 password가 일치한다면
			in.close();
			return true;
		}
		else if (_type == "message" && _ph == search_ph) { // 메세지 전송시 번호가 일치한다면
			in.close();
			return true;
		}
	}

	in.close();
	return false;
}

void Manager::make_Path(string _ph) {
	string _path = this->path;
	_path += "/Members/"; // Members 디렉토리 생성경로
	if (_access(_path.c_str(), 00) == -1) // 디렉토리가 존재하면 0, 없으면 -1
		_mkdir(_path.c_str());

	_path += _ph; // 사용자의 디렉토리 생성경로(디렉토리 이름을 id로)
	int making = _mkdir(_path.c_str()); // .c_str(): string -> char* 형변환

	if (making == 0) {
		cout << "계정 생성 완료..." << endl << endl;
		beginning_Screen();
	}
	else
		cout << "[ERROR] 계정 생성 실패" << endl << endl;
}

void Manager::beginning_Screen() {
	int select = 0;

	do {
		print_menu();
		cout << "번호를 입력하세요: ";
		cin >> select;
		cout << endl;
		while (getchar() != '\n');

		if (cin.fail() || select>4) { // 예외처리
			cout << "잘못된 입력입니다." << endl << endl;
			cin.clear();
		}
		else {
			if (select == 3) { // 프로그램 정보
				print_information();
				cout << "메뉴로 가려면 아무키나 누르세요..";
				getchar();
			}
			else break;
		}
	} while (1);

	switch (select) {
	case 1: // 로그인
		system("cls");
		login();
		break;
	case 2: // 회원가입
		system("cls");
		make_Account();
		break;
	case 4: // 종료
		print_exit();
		cout << "종료하려면 아무키나 누르세요..";
		getchar();
		exit(1);
		break;
	}
}

void Manager::login_Screen() {
	int select = 0;
	int del_index = 0;
	string _phonenum;
	do {
		print_myPhone();
		cout << "번호를 입력하세요: ";
		cin >> select;
		while (getchar() != '\n');

		if (cin.fail()) {
			cout << "잘못된 입력입니다." << endl << endl;
			cin.clear();
			continue;
		}

		switch (select) {
		case 1: // 번호추가
			system("cls"); // 화면지우기
			user->addPerson();
			cout << "번호추가 성공.." << endl;
			cout << "메뉴로 가려면 아무키나 누르세요..";
			getchar();
			break;
		case 2: // 번호검색
			system("cls");
			user->search();
			cout << "메뉴로 가려면 아무키나 누르세요..";
			getchar();
			break;
		case 3: // 번호출력
			system("cls");
			user->output();
			cout << endl;
			cout << "메뉴로 가려면 아무키나 누르세요..";
			getchar();
			break;
		case 4: // 번호삭제
			system("cls");
			user->del_Person();
			cout << endl;
			cout << "메뉴로 가려면 아무키나 누르세요..";
			getchar();
			break;
		case 5: // 메세지 보내기
			system("cls");
			while (1) {
				cout << "메세지를 보낼 번호를 입력하세요: ";
				cin >> _phonenum;
				while (getchar() != '\n');
				if (search( "", "", _phonenum, "message")) { // 등록된 사용자인지 검사
					user->send_Message(this->path + "/Members/" + _phonenum); // 메세지를 보낼 경로전달
					break;
				}
				else {
					cout << "없는 번호입니다. 메세지를 보낼 수 없습니다." << endl;
				}
			}
			cout << "메세지 보내기 성공..." << endl;
			cout << "메뉴로 가려면 아무키나 누르세요..";
			getchar();
			break;
		case 6: // 메세지 출력
			system("cls");
			user->outputMessage();
			cout << "메뉴로 가려면 아무키나 누르세요..";
			getchar();
			break;
		case 7: // 메세지 삭제
			system("cls");
			user->outputMessage();
			
			while (1) {
				cout << "삭제할 메세지 번호를 입력해주세요: ";
				cin >> del_index;
				if (cin.fail()) {
					cout << "잘못된 입력입니다." << endl << endl;
					cin.clear();
					while (getchar() != '\n');
					continue;
				}
				else
					break;
			}
			
			while (getchar() != '\n');
			user->delMessage(del_index);
			cout << "메뉴로 가려면 아무키나 누르세요..";
			getchar();
			break;
		case 8: // 로그아웃
			system("cls");
			logout();
			break;
		}
	} while (1);
}

void Manager::load_Data(string _id) {
	in.open("account_list.txt");
	string search_id = "", search_pw = "", search_name = "", search_ph = "", search_de = "";
	string tem_data = "";
	string tem_data2 = "";
	getline(in, tem_data); // 첫행건너뛰기

	while (!in.eof()) { // id 찾기
		in >> search_id >> search_pw >> search_name >> search_ph;
		if (search_id == _id) {
			user = new Member(search_name, search_ph, search_id, search_pw, path);
			break;
		}
	}

	in.close();
	in.open(user->getPath() + "/phonebook.txt"); // 연락처 파일 열기
	getline(in, tem_data);

	search_name = search_ph = search_de = ""; // 초기화
	while (!in.eof()) { // 데이터 불러오기
		in >> search_name >> search_ph >> search_de;

		if (search_name != "") // 빈파일이 아니라면
			user->addPerson(search_name, search_ph, search_de); // 데이터 추가
	}
	in.close();

	in.open(user->getPath() + "/message.txt"); // 연락처 파일 열기
	while (!in.eof()) { // 데이터 불러오기
		getline(in, tem_data);
		getline(in, tem_data2);
		if (tem_data == "") // 빈파일 이라면
			break;
		else {
			user->addMessage(tem_data, tem_data2); // 수신자추가
		}
	}
	in.close();

}