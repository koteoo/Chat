#include "pch.h"

#include<iostream>
#include <string>
#include <vector>
using namespace std;

class Message {
public: 
	Message(string m, string l_from) :mes(m),login_from(l_from){}
	Message(string m,string l_to,string l_from):mes(m),login_to(l_to),login_from(l_from){}
	~Message() = default;

		string show_message() {
			return mes;
		}
		string getlf() {
			return login_from;
		}
		string get_lt() {
			return login_to;
		}
		void show_mes_all() {
			cout << "--------------------------" << endl;
			cout << "From: " << login_from << "\nTo: " << login_to << "\n" << mes << endl;
			cout << "--------------------------" << endl;
		}
		void show_mes_public() {
			cout << "--------------------------" << endl;
			cout << "From: " << login_from << "\n" << mes << endl;
			cout << "--------------------------" << endl;
		}
private:
	string mes;
	string login_from;
	string login_to;
};
class User {
public:
	User() = default;
	User(string n, string l, string p) :name(n), login(l), password(p) {}
	~User() {}
	void setname(string n) { name = n; }
	void setlogin(string l) { login = l; }
	void setpassword(string p) { password = p; }
	string getname()const { return name; }
	string getlogin()const { return login; }
	string getpass()const { return password; }
	void recieve_message(Message &m) {
		Messages_of_user.push_back(m);
	}
	void show_message(string user) {
	
		for (int i = 0; i < Messages_of_user.size();i++) {
			if(Messages_of_user[i].getlf() == user || Messages_of_user[i].get_lt()== user) {
				Messages_of_user[i].show_mes_all();
			}

		}

	}

private:

	string name;
	string login;
	string password;

	vector <Message> Messages_of_user;//Private messages
};
class Session {
public:
	Session() = default;
	~Session() = default;

	void set_login(string l) {
		login = l;
	}
	string getlogin() {
		return login;
	}

private:
	string login;

};
class Login {
public:
	Login() = default;
	~Login() = default;

	bool login_exist(string l) {//Проверка на существование юзера
		for (int i = 0; i < users.size(); i++) {
			if (users[i].getlogin() == l) {
				return true;
			}
		}
		return false;
	}
	bool login(string l, string p) {//Вход в сессию
		for (int i = 0; i < users.size(); i++) {
			if (users[i].getlogin() == l && users[i].getpass() == p) {
				Session s;
				s.set_login(l);
				logThis = l;
				sessions.push_back(s);
				return true;
			}
		}
		return false;
	}
	bool reg_login() {//Регистрация юзера
		string name, login, pass;
		cout << "Enter your name:" << endl;
		cin >> name;
		cout << "Enter your login:" << endl;
		cin >> login;
		cout << "Enter your password: " << endl;
		cin >> pass;
		if (login_exist(login)) {
			return false;
		}
		User u(name, login, pass);
		users.push_back(u);

		cout << "\nYou succefully REG.\nEnter your data again." << endl;
		return true;
	}
	void show_sessions() {//Show  Online users

		for (int i = 0; i < sessions.size(); i++) {
			cout << "Online: " << sessions[i].getlogin() << endl;
		}
	}
	void show_users() {//Show  Reg users

		for (int i = 0; i < users.size(); i++) {
			cout << "REG users: " << users[i].getlogin() << endl;
		}
	}
	void show_this_user() {
		cout<<logThis<<endl;
	}
	void show_private_messages(string u) {
		for (int i = 0; i < users.size(); i++) {
			if (users[i].getlogin() == logThis) {
				users[i].show_message(u);
			}
		}
	}
	void show_public_messages() {
		for (int i = 0; i < public_messages.size();i++) {
			public_messages[i].show_mes_public();
		}
	}
	void sending_message(){
		short ch;
		string Mes;
		
		bool exit_to_session_menu = false;
		while (!exit_to_session_menu) {
			cout << "1. Private message." << endl;
			cout << "2. Public message." << endl;
			cout << "0. Back." << endl;
			cin >> ch;
			switch (ch) {
			case 0:
				cout << "Back" << endl;
				exit_to_session_menu = true;
				break;

			case 1: {
					cout << "Text to: " << endl;
					string log_to;
					cin >> log_to;
					if (login_exist(log_to)) {
						cout << "It's OK." << endl;
						cout << "Your message: " << endl;
						getline(cin >> ws, Mes);
						Message m(Mes,log_to,logThis);
						for (int i = 0; i < users.size();i++) {
							if (users[i].getlogin() == log_to) {
								users[i].recieve_message(m);
							}
						}
					}
					else {
						cout << "Such User doesn't exist." << endl;
					}
				
				break;
			}
			case 2: {
				cout << "Public message: " << endl;
				//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   ЛИБО ЭТО ПОМОЖЕТ
				getline(cin >> ws, Mes);
				
				Message m(Mes,logThis);
				public_messages.push_back(m);
				break;
			}
			default:
				exit_to_session_menu = true;
				break;

			}
		}
	}

private:
	vector <User> users;//Users which were REGestrated
	vector <Session> sessions;// Online users В данном случае, ЧАТЕ будет пока один залогинный ЮЗЕР, в случае разлогивания удалить из вектора сессий
	vector <Message> public_messages;
	string logThis;//логин пользователя, который в данный момент использует чат(ВЫ).
};
class Chat {
public:
	Chat() { 
		cout << "Welcome to My console Chat Dude!" << endl; 
		chat_menu();
	}
	~Chat() {}
	void chat_menu() {
		bool quit = false;
		short ch;
		string name, login, pass;
		while (!quit) {
			cout << "-----Menu-----" << endl;
			cout << "1. Login." << endl;
			cout << "2. Registration." << endl;
			cout << "0. QUIT." << endl;
			cout << "--------------" << endl;
			cin >> ch;
			switch (ch) {
			case 0:
				cout << "Goodbye!" << endl;
				quit = true;
				break;
			case 1:
				/*cout << "Enter your name:" << endl;
				cin >> name;*/
				cout << "Enter login: " << endl;
				cin >> login;
				if (chat_login.login_exist(login)){
					cout << "Entrance into session menu." << endl;
					cout << "Enter your password: " << endl;
					cin >> pass;
					if (chat_login.login(login, pass)) {
						chat_menu2();
					}
					else {
						cout << "Login or password incorect!." << endl;
					}
					
				}
				else {
					char c;
					cout << "Such login doesn't exist.\nDo You want to REG the NEW LOGIN (y/n)?" << endl;
					cin >> c;
					if (c == 'y') {
						//Переход к регистрации
						chat_login.reg_login();
					}
				}
				break;
			case 2:
				cout << "Registration your account..." << endl;
				chat_login.reg_login();
				break;
			default:
				cout << "ERR!" << endl;
				
				break;
			}
		}
	}
	void chat_menu2() {
		short ch;
		bool quit_session_menu = false;
		while (!quit_session_menu) {
			cout << "-------Sessions' Menu------" << endl;
			cout << "1. To write a message." << endl;// В ОБЩИЙ или Приватный чат
			cout << "2. Incoming messages." << endl;//Показ сообщений(ОБЩИЙ, ПРИВАТНЫЙ чат) ВХОДЯЩИЕ
			cout << "3. To change a user." << endl;//Смена пользователя но НЕ РАЗЛОГИВАНИЕ
			cout << "0. Log out (EXIT)" << endl; //Разлогиниться и выход в главное меню !!!
			cout << "--------------------------" << endl;
			cin >> ch;
			switch (ch) {
				case 0: cout << "Exit to MAIN menu." << endl; //Разлогинить
					quit_session_menu = true;
					break;
				case 1:cout << "Write a message." << endl;
					chat_login.sending_message();
					break;
				case 2: {
					cout << "Show incoming messages." << endl;
					bool exit_to_session_menu = false;
					while (!exit_to_session_menu) {
						short ch;
						cout << "1. Private." << endl;
						cout << "2. Public messages." << endl;
						cout << "0. Cancel." << endl;
						cin >> ch;
						switch (ch) {
						case 0:
							exit_to_session_menu = true;
							break;
						case 1: {
							cout << "1. Private messages: " << endl;///////
							cout << "Login from: " << endl;
							string log_from;
							cin >> log_from;
							chat_login.show_private_messages(log_from);
							break;
						}
						case 2:
							cout << "2. Public messages: " << endl;
							chat_login.show_public_messages();
							break;
						default:
							cout << "ERR" << endl;
							exit_to_session_menu = true;
							break;
						}

					}
					break; 
				}
				case 3: cout << "Change a User." << endl; //Не разлогинивать
					quit_session_menu = true;
				break;
			default:
				cout << "ERROR" << endl;
				quit_session_menu = true;
				break;
			}
		}
	}

private:
	Login chat_login;
};
int main() {

	Chat chat;

}
