#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int BinarySearch(int *arr, int target, int length){
	int left = 0;
	int right = length - 1;
	while (left <= right){
		int mid = left + (right - left) / 2;
		if (target == arr[mid]){
			return mid;
		}
		else if (target > arr[mid]){
			left = mid + 1;
		}
		else if (target < arr[mid]){
			right = mid - 1;
		}
	}
}

void cariangka(int cari){
	int penanda = 0;
	FILE *fp = fopen ("historyangka.txt", "r");
	if (fp == NULL){
		printf("File isn't exist");
	}
	int his[100000];
	int i = 0;
	int j,k;
	while (fscanf(fp, "%d", &his[i]) == 1) {
        i++;
    }
    for (j = 0; j < i; j++){
		for (k = 0; k < i - j; k++){
			if (his[k] > his[k + 1]){
				int temp = his[k];
				his[k] = his[k + 1];
				his[k + 1] = temp;
			}
		}
	}
	penanda = BinarySearch(his, cari, i + 1);
	if (penanda == 0){
		printf("Angka tidak ditemukan pada history\n");
	}
	else {
		printf("Angka ditemukan pada baris ke-%d\n", penanda);
	}
}
void updateHistory(int result){
	FILE *fp = fopen ("historyangka.txt", "a");
	if(fp==NULL){
		printf("File isn't exist");
	}else{
		fprintf(fp, "%d\n", result);
	}
	fclose(fp);
}

void updateHistoryString(char result[50]){
	FILE *fp = fopen ("history.txt", "a");
	if(fp==NULL){
		printf("File isn't exist'");
	}else{
		fprintf(fp, "%s\n", result);
	}
	fclose(fp);
}

void readHistoryAngka() {
    FILE *fp = fopen("historyangka.txt", "r");
    if (fp == NULL) {
        printf("File historyangka.txt tidak ditemukan!\n");
        return;
    }
    int result;
    while (fscanf(fp, "%d", &result) == 1) {
        printf("Hasil yang ditemukan: %d\n", result);
    }

    fclose(fp);
}

void readHistory(){
	FILE *fp = fopen ("history.txt", "r");
	if(fp==NULL){
		printf("File isn't exist'");
	}else{
		char result[100];
		while (fgets(result, sizeof(result), fp) != NULL) {
    		printf("%s", result);
		}
	}
	fclose(fp);
}

float mean (float *arr, int n){
	float hasil, total;
	total = 0;
	int i;
	for (i = 0; i < n; i++){
		total += arr[i];
	}
	hasil = total / n;
	return hasil;
}

float median (float *arr, int n){
	int ind;
	float has;
	if (n % 2 == 1){
		ind = (n + 1) / 2;
		has = arr[ind - 1];
		return has;
	}
	else {
		ind = n / 2;
		has = (arr[ind - 1] + arr[ind]) / 2;
		return has;
	}
}

float modus (float *arr, int n){
	float angka = arr[0];
	float modus = arr[0];
	int byk = 1;
	int bykmod = 1;
	int i;
	for (i = 1; i < n; i++){
    	if (arr[i] == angka){
    		byk++;
		} 
		else {
			if (byk > bykmod){
				bykmod = byk;
				modus = angka;
			}
			byk = 1;
			angka = arr[i];
		}
	}
	return modus;
}
int fpb (int a, int b){
	int hasil, i;
	for (i = 1; i <= a && i <= b; i++){
		if (a % i == 0 && b % i == 0){
			hasil = i;
		}
	}
	return hasil;
}

int fpbmul (int *arr, int by){
	int i, hasil;
	hasil = arr[0];
	for (i = 1; i < by; i++){
		hasil = fpb(hasil, arr[i]);
	}
	return hasil;
}

int kpk (int a, int b){
	return (a * b) / fpb(a, b);
}

int kpkmul (int *arr, int by){
	int i, hasil;
	hasil = arr[0]; 
    for (i = 1; i < by; i++) {
        hasil = kpk(hasil, arr[i]); 
    }
    return hasil;
}

void euclid (int a, int b){
	int i;
	int j = 1;
	while (j != 0){
		j = a % b;
		i = a / b;
		printf("%d = %d * (%d) + %d\n", a, b, i, j);
		if (j == 0){
			printf("FPB dari kedua bilangan tersebut adalah %d\n", b);
		}
		a = b;
		b = j;
	}
	updateHistory(a);
	printf("");
}

int gcdExtended(int a, int b, int *x, int *y){
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
int kongruensi (int a, int b, int c){
	char result5[50];
	if (a % c == b % c){
		printf("%d kongruen dengan %d dalam modulo %d\n", a, b, c);
		sprintf(result5, "%d kongruen dengan %d dalam modulo %d", a, b, c);
	}
	else {
		printf("%d tidak kongruen dengan %d dalam modulo %d\n", a, b, c);
		sprintf(result5, "%d kongruen dengan %d dalam modulo %d", a, b, c);
	}
	updateHistoryString(result5);
}

int inverse(int a, int b){
    int x, y, p, q;
    int gcd = gcdExtended(a, b, &x, &y);
    if(x < 0){
        p = x / b - 1;
        q = x - b * p;
        return q;
    }
	else{
        return x;
    }
}
int solusi(int a, int b, int c) {
	int inv = inverse(a, b);
	int x = (inv * c) % b;
	printf("Kongruensi linear dari %dx = %d (mod %d) adalah \n x = %d (mod %d)\n", a, c, b, x, b);
	char result7[50];
	sprintf(result7, "x = %d (mod %d)", x, b);
	updateHistoryString(result7);
}
int main (){
	int menu, p, q, by, i;
	char ulang[2], startTime[30], endTime[30];
	ulangcik:
	printf("Selamat datang di Kalkulator FPB dan KPK!\n");
	start:
	printf("Silahkan memilih apa yang ingin dicari :\n");
	printf("1. KPK (Hasil Akhir)\n2. FPB (Hasil Akhir)\n3. Algoritma Euclid\n4. Teorema Bezout\n5. Kongruensi Modulo\n6. Invers\n7. Kongruensi Linier\n8. Mean\n9. Median\n10. Modus\n11. History\n12. History Angka\n13. Mencari Angka pada History Angka\n0. Exit\n>>");
	scanf("%d", &menu);
	system("cls");
	if (menu == 1){
		by = 0;
		printf("Banyak bilangan yang ingin dihitung :");
		scanf("%d", &by);
		int a[by];
		for (i = 0; i < by; i++){
			scanf("%d", &a[i]);
		}
		printf("KPK dari ");
		for (i = 0; i < by; i++){
			printf("%d", a[i]);
			if (i == by - 1){
				printf(" ");
				continue;
			}
			printf(", ");
		}
		printf("adalah %d\n", kpkmul(a, by));
		updateHistory(kpkmul(a, by));
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 2){
		by = 0;
		printf("Banyak bilangan yang ingin dihitung :");
		scanf("%d", &by);
		int a[by];
		for (i = 0; i < by; i++){
			scanf("%d", &a[i]);
		}
		printf("FPB dari ");
		for (i = 0; i < by; i++){
			printf("%d", a[i]);
			if (i == by - 1){
				printf(" ");
				continue;
			}
			printf(", ");
		}
		printf("adalah %d\n", fpbmul(a, by));
		updateHistory(fpbmul(a, by));
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 3){
		printf("Masukkan terlebih dahulu dua bilangan yang ingin dihitung :");
		scanf("%d %d", &p, &q);
		euclid(p, q);
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 4){
		int x, y;
		printf("Masukkan terlebih dahulu dua bilangan yang ingin dihitung :");
		scanf("%d %d", &p, &q);
   		int gcd = gcdExtended(p, q, &x, &y);
	    printf("Koefisien Bezout %d dan %d adalah: %d dan %d\n", p, q, x, y);
	    char result4[50];
	    sprintf(result4, "%d dan %d", x, y);
	    updateHistoryString(result4);
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 5){
		printf("Masukkan terlebih dahulu dua bilangan yang ingin dihitung :");
		scanf("%d %d", &p, &q);
		int m;
		printf("Dalam modulo : ");
		scanf("%d", &m);
		kongruensi(p, q, m);
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 6){
		printf("Masukkan terlebih dahulu bilangan yang ingin diinvers :");
		scanf("%d", &p);
		printf("Dalam modulo :");
		scanf("%d", &q);
		int result;
		if(fpb(p,q) == 1){
        	result = inverse(p, q);
        	printf("Inverse dari %d dalam modulo %d dalam nilai positif terkecil adalah %d\n", p, q, result);
        	updateHistory(result);
    	}
		else {
        	printf("%d dalam modulo %d tidak memiliki inverse", p, q);
			char result6[50];
			sprintf(result6, "%d dalam modulo %d tidak memiliki inverse", p, q); 
			updateHistoryString(result6); 
    	}
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 7){
		int o;
		printf("Masukkan terlebih dahulu nilai a dan b yang ingin dihitung :");
		scanf("%d %d", &p, &q);
		printf("Dalam modulo :");
		scanf("%d", &o);
		solusi(p, o, q);
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 8){
		by = 0;
		int i;
		printf("Banyak bilangan yang ingin dihitung :");
		scanf("%d", &by);
		float a[by];
		for (i = 0; i < by; i++){
			scanf("%f", &a[i]);
		}
		printf("Mean dari ");
		for (i = 0; i < by; i++){
			printf("%.2f", a[i]);
			if (i == by - 1){
				printf(" ");
				continue;
			}
			printf(", ");
		}
		printf("adalah %.2f\n", mean(a, by));
		updateHistory(mean(a, by));
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 9){
		by = 0;
		int i, j;
		printf("Banyak bilangan yang ingin dihitung :");
		scanf("%d", &by);
		float a[by];
		for (i = 0; i < by; i++){
			scanf("%f", &a[i]);
		}
		for (i = 0; i < by - 1; i++){
			for (j = 0; j < by - i - 1; j++){
				if (a[j] > a[j + 1]){
					int temp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = temp;
				}
			}
		}
		printf("Median dari ");
		for (i = 0; i < by; i++){
			printf("%.2f", a[i]);
			if (i == by - 1){
				printf(" ");
				continue;
			}
			printf(", ");
		}
		printf("adalah %.2f\n", median(a, by));
		updateHistory(median(a, by));
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 10){
		by = 0;
		int i, j;
		printf("Banyak bilangan yang ingin dihitung :");
		scanf("%d", &by);
		float a[by];
		for (i = 0; i < by; i++){
			scanf("%f", &a[i]);
		}
		printf("Modus dari ");
		for (i = 0; i < by; i++){
			printf("%.2f", a[i]);
			if (i == by - 1){
				printf(" ");
				continue;
			}
			printf(", ");
		}
		printf("adalah %.2f\n", modus(a, by));
		updateHistory(modus(a, by));
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 0){
		suds:
		system("cls");
		printf("Sampai jumpa dan terima kasih :)");
	}
	else if (menu == 11){
		readHistory();
		system("pause");
		system("cls");
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 12){
		readHistoryAngka();
		system("pause");
		system("cls");
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else if (menu == 13){
		int cari;
		printf("Masukkan bilangan yang ingin dicari : ");
		scanf("%d", &cari);
		cariangka(cari);
		printf("Apakah Anda ingin menghitung kembali (Y / T) :");
		scanf("%s", ulang);
		if (strcmp(ulang, "Y") == 0){
			system("cls");
			goto ulangcik;
		}
		else {
			goto suds;
		}
	}
	else {
		printf ("Menu yang dipilih berada di luar jangkauan\n");
		goto start;
	}
}
