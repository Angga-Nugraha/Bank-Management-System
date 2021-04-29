#include "Account.h"
#include <iostream>
#include <fstream>


using namespace std;


char getOption();
int getDatasize(fstream &iofile);
void loginAkun();


int main(int argc, char const *argv[])
{
    int no_acc,pin;
    fstream iofile;
    Account* account = new Account();
    int size = getDatasize(iofile);
    
    char option = getOption();

    enum {CREAT = 1,LOGIN, ADMIN, EXIT};
    while(option != EXIT){
        if(option == '1')
        {
            system("clear");
            cout << "++++++++++PENDAFTARAN AKUN BANK++++++++++" << endl;
            account->writeRecord(size+1);
            
        }
        else if(option == '2')
        {
            account->readRecord();
            system("clear");
            loginAkun();
        }else if(option == '3'){
            string const admin = "admin";
            string adm;
            string const passAdm = "admin";
            string password;
            system("clear");
            
            cout << "++++++++++LOGIN AKUN ADMIN++++++++++" << endl;
            cout << "Masukan username : ";
            cin >> adm;
            cout << "Password         : ";
            cin >> password;
                if(admin != adm || passAdm != password){
                    cout << "-----------------------------------" << endl;
                    cout << "Username/Password salah" << endl;
                }else{
                    system("clear");
                    account->admLogin();
                }
        }else{
            cout << "Option salah..." << endl;
        }
    label_lanjut :
    char lanjut;
    cout << "-----------------------------------" << endl;
    cout << "Kembali ke menu awal? [y/n]: ";
    cin >> lanjut;
    if(lanjut == 'y' || lanjut == 'Y'){
        option = getOption();
    }else if ((lanjut == 'n') | (lanjut == 'N')){
	    break;
	    }else{
        goto label_lanjut;
        }
    }    
    delete account;
    cin.get();
    
    return 0;
}

char getOption(){
    system("clear");
    char option;
    cout << "+++++SYSTEM MANAGEMENT BANK+++++"    << endl;
    cout << "1. DAFTAR AKUN"                      << endl;
    cout << "2. LOGIN"                            << endl;
    cout << "3. LOGIN ADMIN"                      << endl;
    cout << "--------------------------------"    << endl;
    cout << "Masukan pilihan : ";
    cin >> option;
    cin.ignore();
    return option;
}


int getDatasize(fstream &iofile){
	int start, end;
	iofile.seekg(0,ios::beg); 
	start = iofile.tellg();
	iofile.seekg(0,ios::end);
	end = iofile.tellg();
	return (end-start)/sizeof(Account);
}

void loginAkun(){
    system("clear");
    unsigned long no_acc,pin;
    Account* account = new Account();  
    cout << "++++++LOGIN AKUN BANK+++++++"    << endl;
    cout << "No Akses   : ";
    cin >> no_acc;
    cout << "PIN        : ";
    cin >> pin;
    account->login(no_acc,pin);
}

