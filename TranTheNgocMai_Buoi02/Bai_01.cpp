#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

void taoMangNgauNhien(int a[], int *n) {
	printf("Nhap so phan tu cua mang (>= 15): ");
	scanf("%d", n);
	if (*n < 15) {
		printf("So phan tu phai lon hon hoac bang 15.\n");
		return;
	}
	srand(time(NULL));
	for (int i = 0; i < *n; i++) {
		a[i] = rand() % 101; // Gia tri ngau nhien tu 0 den 100
	}
}

void taoMangSoChan(int a[], int b[], int n, int *m) {
	*m = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] % 2 == 0) {
			b[*m] = a[i];
			(*m)++;
		}
	}
}

int timKiemTuyenTinh(int a[], int n, int x) {
	for (int i = 0; i < n; i++) {
		if (a[i] == x) {
			return i;
		}
	}
	return -1;
}

void interchangeSort(int a[], int n, int tangDan) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((tangDan && a[i] > a[j]) || (!tangDan && a[i] < a[j])) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

int binarySearch(int a[], int n, int x) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (a[mid] == x) {
			return mid;
		}
		else if (a[mid] < x) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}

void selectionSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[minIdx]) {
				minIdx = j;
			}
		}
		int temp = a[minIdx];
		a[minIdx] = a[i];
		a[i] = temp;
	}
}

void quickSort(int a[], int left, int right) {
	int i = left, j = right;
	int pivot = a[(left + right) / 2];
	while (i <= j) {
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;
		if (i <= j) {
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}
	if (left < j) quickSort(a, left, j);
	if (i < right) quickSort(a, i, right);
}

void inMang(int a[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main() {
	int a[MAX], b[MAX], n, m, x, choice, result;
	do {
		printf("\nMenu:\n");
		printf("1. Tao mang ngau nhien\n");
		printf("2. Tao mang so chan\n");
		printf("3. Tim kiem tuyen tinh\n");
		printf("4. Sap xep tang dan/giam dan (Interchange Sort)\n");
		printf("5. Tim kiem nhi phan\n");
		printf("6. Sap xep tang dan (Selection Sort)\n");
		printf("7. Sap xep tang dan (Quick Sort)\n");
		printf("0. Thoat\n");
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			taoMangNgauNhien(a, &n);
			printf("Mang ngau nhien: ");
			inMang(a, n);
			break;
		case 2:
			taoMangSoChan(a, b, n, &m);
			printf("Mang so chan: ");
			inMang(b, m);
			break;
		case 3:
			printf("Nhap gia tri x can tim: ");
			scanf("%d", &x);
			result = timKiemTuyenTinh(a, n, x);
			if (result != -1) {
				printf("Tim thay x tai vi tri %d\n", result);
			}
			else {
				printf("Khong tim thay x\n");
			}
			break;
		case 4:
			printf("Nhap 1 de sap xep tang dan, 0 de sap xep giam dan: ");
			int tangDan;
			scanf("%d", &tangDan);
			interchangeSort(a, n, tangDan);
			printf("Mang sau khi sap xep: ");
			inMang(a, n);
			break;
		case 5:
			printf("Nhap gia tri x can tim: ");
			scanf("%d", &x);
			interchangeSort(a, n, 1); // Sap xep tang dan truoc khi tim kiem nhi phan
			result = binarySearch(a, n, x);
			if (result != -1) {
				printf("Tim thay x tai vi tri %d\n", result);
			}
			else {
				printf("Khong tim thay x\n");
			}
			break;
		case 6:
			selectionSort(a, n);
			printf("Mang sau khi sap xep (Selection Sort): ");
			inMang(a, n);
			break;
		case 7:
			quickSort(a, 0, n - 1);
			printf("Mang sau khi sap xep (Quick Sort): ");
			inMang(a, n);
			break;
		case 0:
			printf("Thoat chuong trinh.\n");
			break;
		default:
			printf("Lua chon khong hop le. Vui long chon lai.\n");
		}
	} while (choice != 0);

	return 0;
}
