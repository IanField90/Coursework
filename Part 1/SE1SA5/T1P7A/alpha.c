#define NAME_MAXLEN 16
#define NUM_OF_CURRENCIES 4
#define STERLING 0
#define USDOLLAR 1
#define EURO 2
#define KRONA 3
#include <stdio.h>

/* global variables */
float exchangeRateTable[NUM_OF_CURRENCIES][NUM_OF_CURRENCIES];
char currencyNames[NUM_OF_CURRENCIES][NAME_MAXLEN];//= {"GBP", "USD", "EURO", "KRONA"};
int amountOfCurrencies;

/* This function sets the exchange rate for a pair of currencies.
   It sets two values in the exchangeRateTable:
      from currency1 to currency2: rate
      from currency2 to currency1: 1 / rate
*/
void setExchangeRate(int currency1, int currency2, float rate){
	exchangeRateTable[currency1][currency2] = rate;
	exchangeRateTable[currency2][currency1] = 1 / rate;
	exchangeRateTable[currency1][currency1] = 1;
	exchangeRateTable[currency2][currency2] = 1;
}


/* This function sets the exchange rates for the currencies (and in 
   the alpha sting their names as well). 
   It uses the global variables and the constants defined above. 
   It initialises the array of floats exchangeRateTable with the exchange rates
   by calling the function setExchangeRate.
   In the basic assignment these values are hard-coded in this function (defined 
   at compilation time). In the alpha sting exchangeRateTable and currencyNames 
   are read from standard input (keyboard).
*/
void initCurrencies(){
	int i, j;
	float convRate;

	printf("Please input the number of currencies you require 4 max:\n");
	scanf("%d", &amountOfCurrencies);

	for (i = 0; i < amountOfCurrencies; i++)
	{
		printf("Please input the name of currency %d\n",i + 1);
		scanf("%s", &currencyNames[i]);
	}
	for (i = 0; i < amountOfCurrencies; i++)
	{
		for (j = 0; j < amountOfCurrencies; j++)
		{
			if ( i != j){
			printf("Please input conversion from %s to %s \n", currencyNames[i], currencyNames[j]);
			scanf("%f", &convRate);
			}
			else
				convRate = 1;
			setExchangeRate(i, j, convRate);
		}
	}

	
	/**************************
	 * USED IN NORMAL VERSION *
	 **************************/
	////GBP to USD, EURO, KRONA
	//setExchangeRate(0, 1, 0.6037);
	//setExchangeRate(0, 2, 0.9014);
	//setExchangeRate(0, 3, 0.0872);
	////USD to EURO, KRONA
	//setExchangeRate(1, 2, 0.6680);
	//setExchangeRate(1, 3, 6.8906);
	////EURO to KRONA
	//setExchangeRate(2, 3, 10.3146);
}

/* This function prints on screen the list of available currencies
    and asks the user to enter a choice. The selected currency is returned
    as an integer value (one of the defined constants). 
*/
int selectCurrencyFromList(){
	int input, valid = 0, i;
	for (i = 0; i < amountOfCurrencies; i++)
	{
		printf("%d) %s ", i, currencyNames[i]);
	}
	printf("\n");
	while(valid == 0){
		scanf("%d", &input);
		if(0 <= input && input <=3)
			valid = 1;
		else
			printf("Incorrect please re-enter\n");
	}	
	return input;
}


/* This function converts a monetary value (amount) from a currency to another.
   It returns the converted value. */
float convertCurrency(float amount, int fromCurrency, int toCurrency){
	float result;
		printf("Converting...\n");
	result = exchangeRateTable[fromCurrency][toCurrency] * amount;
	return result;
}

int main(){
	int selectedFromCurrency, selectedToCurrency;
	float value, answer;
	//initialise currencies
	initCurrencies();

	//Get from currency
	printf("Please select a currency: \n");
	selectedFromCurrency = selectCurrencyFromList();
	//Get value
	printf("Please input the value you want to convert:\n");
	scanf("%f", &value);
	//Get To currency
	printf("Please select a currency to convert to: \n");
	selectedToCurrency = selectCurrencyFromList();
	
	
	answer = convertCurrency(value, selectedFromCurrency, selectedToCurrency);
	
	printf("Answer is: %8.2f\n", answer);

	system("PAUSE");
	return 0;
}