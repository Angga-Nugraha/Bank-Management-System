#ifndef __ACCOUNT
#define __ACCOUNT



class Account{
    private:
        char nama[25];
        unsigned long no_acc;
        unsigned long PIN;
        unsigned long balance;

    public:

        Account();
        void show();
        int setNo_acc() const;
        int setPin() const;
        int setBalance() const;
        void sumBalance(int);
        void minBalance(int);

        void admLogin();
        void daftarAkun();
        void writeRecord(int);
        void readRecord();
        void login(int,int);
        ~Account();
};
#endif