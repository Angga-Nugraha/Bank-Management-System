#include <iostream>
#include <fstream>
#include "Account.h"


Account::Account(){
    this->nama[25] = nama[25];
    this->no_acc = no_acc;
    this->PIN = PIN;
    this->balance = balance;
}

Account::~Account(){
    std::cout << "" << std::endl;
}

void Account::show(){
    std::cout << this->nama << "\t\t" << this->no_acc << "\t" << this->PIN << "\tRp." << this->balance << std::endl; 
}

int Account::setNo_acc() const{
    return no_acc;
}

int Account::setPin() const{
    return PIN;
}
int Account::setBalance() const{
    return balance;
}
void Account::sumBalance(int x){
    this->balance += x;
}
void Account::minBalance(int x){
    this->balance -= x;
}


void Account::daftarAkun(){
    int pin;
    std::cout << "Nama       : ";
    std::cin.getline(nama,sizeof(nama));
    std::cout << "No Akun    : ";
    std::cin >> no_acc;
    std::cout << "Password   : ";
    std::cin >> PIN;
    back:
    std::cout << "Konfirmasi PIN : ";
    std::cin >> pin;
        if(PIN != pin){
            std::cout << "PIN tidak cocok..." << std::endl;
            goto back;
        }else{
            std::cout << "PIN cocok..." << std::endl;
        }
    std::cout << "Balance    : ";
    std::cin >> balance;
    std::cout << std::endl;
    std::cout << std::endl;
}

void Account::writeRecord(int n){
    std::ofstream outfile;
    outfile.open("Data.bin",std::ios::binary | std::ios::app);
    this->daftarAkun();
    outfile.seekp((n-1)*sizeof(this));
    outfile.write(reinterpret_cast<char*>(this),sizeof(*this));
    outfile.close();
    std::cout << "Akun berhasil di daftarkan" << std::endl;
}

void Account::readRecord(){
    std::ifstream infile;
    int index = 1;
    infile.open("Data.bin",std::ios::binary);
    if(!infile){
        std::cout << "Data tidak ditemukan" << std::endl;
        return;
    }
    while(!infile.eof()){        
        if(infile.read(reinterpret_cast<char*>(this),sizeof(*this))){
            std::cout << index << ". ";
            this->show();
        }
        index++;
    }
    infile.close();
}
void Account::admLogin(){
    std::fstream iofile;
    char pilihan;
    int nomor;
    
    iofile.open("Data.bin",std::ios::in | std::ios::binary);
    iofile.seekg(0,std::ios::end);
    int counter = iofile.tellg()/sizeof(*this);
        if(!iofile){
            std::cout << "Database tidak ditemukan" << std::endl;
            return;
        }else{
            std::cout << "+++++++++++++++++++++++DAFTAR NAMA SEMUA AKUN+++++++++++++++++++++++" << std::endl;
            std::cout << "NO NAMA     \t\t\tNO AKSES\tPIN\tSALDO" << std::endl;
            readRecord();
        }
    
        std::cout << "--------------------------------------------------------------------" << std::endl;
        std::cout << "1.Ubah Akun" << std::endl;
        std::cout << "2.Hapus Akun" << std::endl;
        std::cout << "-------------------" << std::endl;
        std::cout << "Masukan pilihan : ";
        std::cin >> pilihan;
        if(pilihan == '1'){ 
            std::cout << "Pilih no akun yang akan diubah : ";
            std::cin >> nomor;
            std::cin.ignore();   
            std::cout << "--------------------------------------------------------------------" << std::endl;
            iofile.seekg((nomor-1)* sizeof(*this));
            iofile.read(reinterpret_cast<char*>(this),sizeof(*this));
            this->show();
            iofile.close();

            iofile.open("Data.bin", std::ios::in | std::ios::out | std::ios::binary);
            iofile.seekp((nomor-1)*sizeof(*this));
            daftarAkun();    
            iofile.write(reinterpret_cast<char *> (this), sizeof(*this));
            iofile.close();
            
            }else if(pilihan == '2'){
                std::fstream tempFile;
                std::cout << "Pilih no akun yang akan dihapus : ";
                std::cin >> nomor;
                std::cin.ignore();
                tempFile.open("tempFile.dat", std::ios::out | std::ios::binary);
                iofile.seekg(0);
                for(int i = 0; i < counter; i++){
                    iofile.read(reinterpret_cast<char*>(this),sizeof(*this));
                    if(i == (nomor-1)){
                        continue;
                    }
                    tempFile.write(reinterpret_cast<char*>(this),sizeof(*this));
                }
                std::cout << std::endl;
                std::cout << "Menghapus akun..." << std::endl;
                iofile.close();
                tempFile.close();
                remove("Data.bin");
                rename("tempFile.dat","Data.bin");
            }else{
                std::cout << "Pilihan tidak ditemukan" << std::endl;
                return;
            }

}

void Account::login(int acc, int pin){
    std::fstream infile;

    bool found = false;
    infile.open("Data.bin",std::ios::in | std::ios::out | std::ios::binary);
    if(!infile){
        std::cout << "Database tidak ditemukan" << std::endl;
        return;
    }
    while(!infile.eof() && found == false){
        if(infile.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(this->setNo_acc() == acc && this->setPin() == pin){
                std::cout << "Selamat Datang " << this->nama << std::endl;
                std::cout << "Detail Account : " << std::endl;
                std::cout << "-------------------------------------------------------------" << std::endl;
                std::cout << "NAMA     \t\tNO AKSES\tPIN\tSALDO" << std::endl;
                this->show();
                std::cout << "-------------------------------------------------------------" << std::endl;

                char pil;
                unsigned long x;
                int saldo;
                std::cout << "1.Tambah Saldo"    << std::endl;
                std::cout << "2.Tarik tunai"     << std::endl;
                std::cout << "3.Edit info akun"  << std::endl;
                std::cout << "-------------------------" << std::endl;
                std::cout << "Pilihan : ";
                std::cin >> pil;
                std::cin.ignore();
                switch(pil){
                    case '1':
                        std::cout << "-------------------------" << std::endl;
                        std::cout << "Tambah saldo : Rp.";
                        std::cin >> x;
                        this->sumBalance(x);
                    break;
                    
                    case '2':
                        std::cout << "-------------------------" << std::endl;
                        std::cout << "Tarik saldo : Rp.";
                        std::cin >> x;
                        saldo = this->setBalance() - x;
                        if(saldo < 0){
                            std::cout << "Saldo anda tidak cukup" << std::endl;
                            break;
                        }else{
                            this->minBalance(x);
                        }
                    break;
                    
                    case '3':
                        int pin;
                        std::cout << "-------------------------" << std::endl;
                        std::cout << "Nama       : ";
                        std::cin.getline(nama,sizeof(nama));
                        std::cout << "No Akun    : ";
                        std::cin >> no_acc;
                        std::cout << "Password   : ";
                        std::cin >> PIN;
                        back:
                        std::cout << "Konfirmasi PIN : ";
                        std::cin >> pin;
                        if(PIN != pin){
                            std::cout << "PIN tidak cocok..." << std::endl;
                            goto back;
                        }else{
                            std::cout << "PIN cocok..." << std::endl;
                        }
                    break;
                    
                    default:
                        std::cout << "Pilihan tidak ditemukan" <<std::endl;
                    return;
                }
            
                int pos=(-1)*static_cast<int>(sizeof(*this));
                infile.seekp(pos,std::ios::cur);
                infile.write(reinterpret_cast<char *> (this), sizeof(*this));
                std::cout << "-------------------------\nTransaksi berhasil\n\n\n" << std::endl;
                std::cout << "\t\t\t\tSisa saldo anda : Rp." << this->balance << std::endl;
                std::cout << "-------------------------------------------------------------" << std::endl;
                found = true;
            }
        }
    }
    infile.close();
    if(found == false){
        std::cout << "Akun tidak ditemukan" << std::endl;
    }
}
