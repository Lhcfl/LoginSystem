#include<bits/stdc++.h>
#include<conio.h>
#include<direct.h>
#include<windows.h>
using namespace std;
struct APPDATA{
    string name;
    string ver;
}APP;
struct USER{
	string name;
	string pswd;
	string label;
}USER_NOW;
string dir;
map<string,USER> name2user;
bool Logined=false;
void load(string s=""){
    cout<<APP.name+"    Version:"<<APP.ver;
    cout<<endl<<s;
    cout<<"\n-------------\n";
}
void getPassword(string *s,int MAXLEN=16){
    char p;
    char a[500];
    int i=0;
    while(1){
        p=getch();
        switch(p){
            case 8:
                if(i!=0){
                    --i;
                    printf("\b \b");
                }
                continue;
            case -32:
                getch();
                continue;
            case 32:
                continue;
            case 13:
                a[i]=0;
                *s=a;
                putchar('\n');
                return;
            default:
                if(i<MAXLEN && i<499){
                    putchar('*');
                    a[i++]=p;
                }
        }
    }
}
void getUsername(string *s,int MAXLEN=16){
    char p;
    char a[500];
    int i=0;
    while(1){
        p=getch();
        switch(p){
            case 8:
                if(i!=0){
                    --i;
                    printf("\b \b");
                }
                continue;
            case -32:
                getch();
                continue;
            case 32:
                continue;
            case 13:
                a[i]=0;
                *s=a;
                putchar('\n');
                return;
            default:
                if(i<MAXLEN && i<499){
                    putchar(p);
                    a[i++]=p;
                }
        }
    }
}
void fprint(ofstream *fout,USER user){
	(*fout)<<endl<<"name: "<<user.name<<endl<<"password: "<<user.pswd<<endl<<"label: "<<user.label<<endl;
	return;
}
int login(){
	string s="";
	ifstream fin;
	fin.open((dir+"\\data\\user").c_str());
	while(fin>>s){
		if(s!="name:"){return 0;}
		string name,pswd,tmp,label;
		fin>>name>>tmp>>pswd;
		fin>>tmp>>label;
		USER tmp_user;
		tmp_user.name=name;
		tmp_user.pswd=pswd;
		tmp_user.label=label;
		name2user.insert(pair<string,USER>(name,tmp_user));
	}
	if(s==""){
		cout<<"There aren't any user. Please sign up first.\n";
		return 2;
	}
	fin.close();
	string username,password;
	cout<<"Username:";
	getUsername(&username);
	cout<<"Password:";
	getPassword(&password);
	USER tmp_user=name2user[username];
	if(tmp_user.pswd==password && password!=""){
		USER_NOW=tmp_user;
		return 1;
	}else{
		cout<<"Wrong password!\n";
		return 0;
	}
	return 0;
}
int signup(){
	bool first=1;
	string s="";
	ifstream fin;
	fin.open((dir+"\\data\\user").c_str());
	while(fin>>s){
		first=0;
		if(s!="name:"){return 0;}
		string name,pswd,tmp,label;
		fin>>name>>tmp>>pswd;
		fin>>tmp>>label;
		USER tmp_user;
		tmp_user.name=name;
		tmp_user.pswd=pswd;
		tmp_user.label=label;
		name2user.insert(pair<string,USER>(name,tmp_user));
	}
	if(!first){
		ofstream fout;
		fout.open((dir+"\\data\\user").c_str(),ios::app);
		cout<<"Do not use spaces in username and password\n";
AGAIN1:
		string username="",password="",pswd_2="";
		while(username==""){
			cout<<"Username:";
			getUsername(&username);
			if(name2user.count(username)!=0){
				cout<<"User name already exists."<<endl;
				goto AGAIN1;
			}
		}
		while(password==""){
			cout<<"Password:";
			getPassword(&password);
		}
		cout<<"Enter your password again:";
		getPassword(&pswd_2);
		if(password==pswd_2 && pswd_2!=""){
			USER tmp_user;
			tmp_user.label="Normal";
			tmp_user.name=username;
			tmp_user.pswd=password;
			fprint(&fout,tmp_user);
			USER_NOW=tmp_user;
			return 1;
		}else{
			cout<<"\nError.\nPlease sign up again.\n";
			goto AGAIN1;
		}
		fout.close();
	}else{
		_mkdir((dir+"\\data").c_str());
		ofstream fout;
		fout.open((dir+"\\data\\user").c_str());
		cout<<"Do not use spaces in username and password\n";
AGAIN2:	
		string username="",password="",pswd_2="";
		while(username==""){
			cout<<"Username:";
			getUsername(&username);
			if(name2user.count(username)!=0){
				cout<<"User name already exists."<<endl;
				goto AGAIN2;
			}
		}
		while(password==""){
			cout<<"Password:";
			getPassword(&password);
		}
		cout<<"Enter your password again:";
		getPassword(&pswd_2);
		if(password==pswd_2 && pswd_2!=""){
			USER tmp_user;
			tmp_user.label="Admin";
			tmp_user.name=username;
			tmp_user.pswd=password;
			fprint(&fout,tmp_user);
			USER_NOW=tmp_user;
			return 1;
		}else{
			cout<<"\nError.\nPlease sign up again.\n";
			goto AGAIN2;
		}
		fout.close();
	}
	Logined=true;
}
int checkmyself(){
	cout<<"Working dir:  "<<dir<<"  ";
	if(dir!=""){
		cout<<"[OK]\n";
	}else{
		cout<<"[ERR]\n";
	}
	return 1;
}
void Aboutme(){
	cout<<"Welcome, "<<USER_NOW.name<<endl;
	cout<<"Your grade: "<<USER_NOW.label<<endl;
	return;
}
int main(){
	APP.name="LoginSystem";
    APP.ver="Alpha";
	char tmp_dir[200];  
    GetCurrentDirectory(200,tmp_dir);
    dir=tmp_dir;
    load("Check myself");
    if(checkmyself()){
    	cout<<"\nAll are OK.\n";
    	_sleep(1000);
    	system("cls");
    }else{
    	cout<<"Program error. Please contact the administrator.\n";
    	system("pause");
    	return 0;
    }
    load("Hello!");
    cout<<"Please login or sign up.\nEnter 'l' to login and 's' to sign up.\n";
    int Login_return;
    char p;
    while(p=getch()){
    	if(p=='l'){
    		goto LOGIN;
    	}
    	if(p=='s'){
    		goto SIGNUP;
    	}
    }
LOGIN:    
	system("cls");
	load("Login");
    Login_return=login();
    switch(Login_return){
    	case 0:
    		cout<<"Login failed!\n";
    		break;
    	case 1:
    		cout<<"Login success!\n";
    		Logined=true;
    		goto LOGINED;
    		break;
    	case 2:
    		system("cls");
    		load("Sign up");
    		signup();
    		goto LOGINED;
    		break;
    }
SIGNUP:
	system("cls");
    load("Sign up");
    signup();
    cout<<"Success!\n";
LOGINED: 
	Logined=true;
	_sleep(2000);
	system("cls");
	load("");
	Aboutme();
    system("pause");
    return 0;
}
