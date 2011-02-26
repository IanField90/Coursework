#ifndef PIGGYBANK_H
#define PIGGYBANK_H
class PiggyBank{
public:
	// default balance is 0
	PiggyBank(float = 0);
	float getBalance () const {return balance;};
	int getAccountNo() const {return AccountNo;};
	void withdraw(float);
	void deposit(float);
	void transfer(float amount, PiggyBank &, PiggyBank &);
protected:
	float balance;
private:
	int AccountNo;
	static int count;
};

#endif