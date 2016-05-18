#include <stdio.h>
#include <string.h>


typedef struct Transaction {
	int day;
	int month;
	int year;
	int amount;
	char currency[3];
} transaction;

int main() {
	int n, i, total = 0;
	scanf("%d", &n);
	transaction transactions[500];
	for (i = 0; i<n; i++) {
		scanf("%d/%d/%d %d %s", &transactions[i].day, &transactions[i].month, &transactions[i].year, &transactions[i].amount, transactions[i].currency);
	}
	int k = 1;
	for (i = 0; i<n; i++) {
		if (!strcmp(transactions[i].currency, "MKD")) {
			if (transactions[i].amount>1000) {
				if (transactions[i].year>2013 && transactions[i].year<2015) {
					printf("%d. %02d/%02d/%d %d %s\n", k++, transactions[i].day, transactions[i].month, transactions[i].year, transactions[i].amount, transactions[i].currency);
					total += transactions[i].amount;
				}if (transactions[i].year == 2013) {
					if (transactions[i].month > 1) {
						printf("%d. %02d/%02d/%d %d %s\n", k++, transactions[i].day, transactions[i].month, transactions[i].year, transactions[i].amount, transactions[i].currency);
						total += transactions[i].amount;
					}
					else if (transactions[i].day > 1) {
						printf("%d. %02d/%02d/%d %d %s\n", k++, transactions[i].day, transactions[i].month, transactions[i].year, transactions[i].amount, transactions[i].currency);
						total += transactions[i].amount;
					}
				}if (transactions[i].year == 2015) {
					if (transactions[i].month < 12) {
						printf("%d. %02d/%02d/%d %d %s\n", k++, transactions[i].day, transactions[i].month, transactions[i].year, transactions[i].amount, transactions[i].currency);
						total += transactions[i].amount;
					}
					else if (transactions[i].day < 31) {
						printf("%d. %02d/%02d/%d %d %s\n", k++, transactions[i].day, transactions[i].month, transactions[i].year, transactions[i].amount, transactions[i].currency);
						total += transactions[i].amount;
					}
				}
			}
		}
	}

	printf("Total: %d MKD", total);
	return 0;
}
