#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int phanNguyen;
	int tuSo;
	int mauSo;
} HonSo;

#define MAX 100

int ucln(int a, int b) {
	if (b == 0)
		return a;
	return ucln(b, a % b);
}

void toiGianPhanSo(int *tu, int *mau) {
	int gcd = ucln(abs(*tu), abs(*mau));
	*tu /= gcd;
	*mau /= gcd;
}

void taoMangHonSoNgauNhien(HonSo b[], int *n) {
	printf("Nhap so phan tu cua mang (>= 15): ");
	scanf("%d", n);
	if (*n < 15) {
		printf("So phan tu phai lon hon hoac bang 15.\n");
		return;
	}
	srand(time(NULL));
	for (int i = 0; i < *n; i++) {
		b[i].phanNguyen = rand() % 21 - 10; // Phan nguyen tu -10 den 10
		b[i].tuSo = rand() % 21 - 10; // Tu so tu -10 den 10
		do {
			b[i].mauSo = rand() % 19 + 1; // Mau so tu 1 den 20
		} while (b[i].mauSo == 0);
		toiGianPhanSo(&b[i].tuSo, &b[i].mauSo);
	}
}

void xuatHonSo(HonSo hs) {
	printf("%d %d/%d", hs.phanNguyen, hs.tuSo, hs.mauSo);
}

void xuatMangHonSo(HonSo b[], int n) {
	for (int i = 0; i < n; i++) {
		xuatHonSo(b[i]);
		if (i < n - 1) {
			printf(", ");
		}
	}
	printf("\n");
}

int soSanhHonSo(HonSo a, HonSo b) {
	int phanSo1Tu = a.phanNguyen * a.mauSo + a.tuSo;
	int phanSo2Tu = b.phanNguyen * b.mauSo + b.tuSo;
	if (phanSo1Tu * b.mauSo > phanSo2Tu * a.mauSo) return 1;
	if (phanSo1Tu * b.mauSo < phanSo2Tu * a.mauSo) return -1;
	return 0;
}

HonSo chuyenHonSoThanhPhanSo(HonSo hs) {
	HonSo phanSo;
	phanSo.phanNguyen = 0;
	phanSo.tuSo = hs.phanNguyen * hs.mauSo + hs.tuSo;
	phanSo.mauSo = hs.mauSo;
	toiGianPhanSo(&phanSo.tuSo, &phanSo.mauSo);
	return phanSo;
}

HonSo chuyenPhanSoThanhHonSo(HonSo ps) {
	HonSo honSo;
	honSo.phanNguyen = ps.tuSo / ps.mauSo;
	honSo.tuSo = ps.tuSo % ps.mauSo;
	honSo.mauSo = ps.mauSo;
	return honSo;
}

HonSo tongHonSo(HonSo a, HonSo b) {
	HonSo ps1 = chuyenHonSoThanhPhanSo(a);
	HonSo ps2 = chuyenHonSoThanhPhanSo(b);
	HonSo ketQua;
	ketQua.phanNguyen = 0;
	ketQua.tuSo = ps1.tuSo * ps2.mauSo + ps2.tuSo * ps1.mauSo;
	ketQua.mauSo = ps1.mauSo * ps2.mauSo;
	toiGianPhanSo(&ketQua.tuSo, &ketQua.mauSo);
	return chuyenPhanSoThanhHonSo(ketQua);
}

HonSo hieuHonSo(HonSo a, HonSo b) {
	HonSo ps1 = chuyenHonSoThanhPhanSo(a);
	HonSo ps2 = chuyenHonSoThanhPhanSo(b);
	HonSo ketQua;
	ketQua.phanNguyen = 0;
	ketQua.tuSo = ps1.tuSo * ps2.mauSo - ps2.tuSo * ps1.mauSo;
	ketQua.mauSo = ps1.mauSo * ps2.mauSo;
	toiGianPhanSo(&ketQua.tuSo, &ketQua.mauSo);
	return chuyenPhanSoThanhHonSo(ketQua);
}

HonSo tichHonSo(HonSo a, HonSo b) {
	HonSo ps1 = chuyenHonSoThanhPhanSo(a);
	HonSo ps2 = chuyenHonSoThanhPhanSo(b);
	HonSo ketQua;
	ketQua.phanNguyen = 0;
	ketQua.tuSo = ps1.tuSo * ps2.tuSo;
	ketQua.mauSo = ps1.mauSo * ps2.mauSo;
	toiGianPhanSo(&ketQua.tuSo, &ketQua.mauSo);
	return chuyenPhanSoThanhHonSo(ketQua);
}

HonSo thuongHonSo(HonSo a, HonSo b) {
	HonSo ps1 = chuyenHonSoThanhPhanSo(a);
	HonSo ps2 = chuyenHonSoThanhPhanSo(b);
	HonSo ketQua;
	ketQua.phanNguyen = 0;
	ketQua.tuSo = ps1.tuSo * ps2.mauSo;
	ketQua.mauSo = ps1.mauSo * ps2.tuSo;
	toiGianPhanSo(&ketQua.tuSo, &ketQua.mauSo);
	return chuyenPhanSoThanhHonSo(ketQua);
}

void interchangeSort(HonSo b[], int n, int tangDan) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((tangDan && soSanhHonSo(b[i], b[j]) > 0) || (!tangDan && soSanhHonSo(b[i], b[j]) < 0)) {
				HonSo temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		}
	}
}

void selectionSort(HonSo b[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (soSanhHonSo(b[j], b[minIdx]) < 0) {
				minIdx = j;
			}
		}
		HonSo temp = b[minIdx];
		b[minIdx] = b[i];
		b[i] = temp;
	}
}

void quickSort(HonSo b[], int left, int right) {
	int i = left, j = right;
	HonSo pivot = b[(left + right) / 2];
	while (i <= j) {
		while (soSanhHonSo(b[i], pivot) < 0) i++;
		while (soSanhHonSo(b[j], pivot) > 0) j--;
		if (i <= j) {
			HonSo temp = b[i];
			b[i] = b[j];
			b[j] = temp;
			i++;
			j--;
		}
	}
	if (left < j) quickSort(b, left, j);
	if (i < right) quickSort(b, i, right);
}

int main() {
	HonSo b[MAX];
	int n, choice;
	do {
		printf("\nMenu:\n");
		printf("1. Tao mang hon so ngau nhien\n");
		printf("2. Xuat danh sach hon so\n");
		printf("3. So sanh 2 hon so\n");
		printf("4. Chuyen hon so thanh phan so\n");
		printf("5. Chuyen phan so thanh hon so\n");
		printf("6. Tinh tong, hieu, tich, thuong 2 hon so\n");
		printf("7. Sap xep tang/giam theo 3 giai thuat sap xep\n");
		printf("0. Thoat\n");
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			taoMangHonSoNgauNhien(b, &n);
			printf("Mang hon so ngau nhien: \n");
			xuatMangHonSo(b, n);
			break;
		case 2:
			printf("Danh sach hon so: \n");
			xuatMangHonSo(b, n);
			break;
		case 3: {
					HonSo a, c;
					printf("Nhap hon so thu nhat (phan nguyen tu so mau so): ");
					scanf("%d %d %d", &a.phanNguyen, &a.tuSo, &a.mauSo);
					printf("Nhap hon so thu hai (phan nguyen tu so mau so): ");
					scanf("%d %d %d", &c.phanNguyen, &c.tuSo, &c.mauSo);
					int kq = soSanhHonSo(a, c);
					if (kq > 0)
						printf("Hon so thu nhat lon hon hon so thu hai\n");
					else if (kq < 0)
						printf("Hon so thu nhat nho hon hon so thu hai\n");
					else
						printf("Hai hon so bang nhau\n");
					break;
		}
		case 4: {
					HonSo hs;
					printf("Nhap hon so (phan nguyen tu so mau so): ");
					scanf("%d %d %d", &hs.phanNguyen, &hs.tuSo, &hs.mauSo);
					HonSo ps = chuyenHonSoThanhPhanSo(hs);
					printf("Phan so: %d/%d\n", ps.tuSo, ps.mauSo);
					break;
		}
		case 5: {
					HonSo ps;
					printf("Nhap phan so (tu so mau so): ");
					scanf("%d %d", &ps.tuSo, &ps.mauSo);
					HonSo hs = chuyenPhanSoThanhHonSo(ps);
					printf("Hon so: %d %d/%d\n", hs.phanNguyen, hs.tuSo, hs.mauSo);
					break;
		}
		case 6: {
					HonSo a, c;
					printf("Nhap hon so thu nhat (phan nguyen tu so mau so): ");
					scanf("%d %d %d", &a.phanNguyen, &a.tuSo, &a.mauSo);
					printf("Nhap hon so thu hai (phan nguyen tu so mau so): ");
					scanf("%d %d %d", &c.phanNguyen, &c.tuSo, &c.mauSo);
					HonSo tong = tongHonSo(a, c);
					HonSo hieu = hieuHonSo(a, c);
					HonSo tich = tichHonSo(a, c);
					HonSo thuong = thuongHonSo(a, c);
					printf("Tong: %d %d/%d\n", tong.phanNguyen, tong.tuSo, tong.mauSo);
					printf("Hieu: %d %d/%d\n", hieu.phanNguyen, hieu.tuSo, hieu.mauSo);
					printf("Tich: %d %d/%d\n", tich.phanNguyen, tich.tuSo, tich.mauSo);
					printf("Thuong: %d %d/%d\n", thuong.phanNguyen, thuong.tuSo, thuong.mauSo);
					break;
		}
		case 7:
			printf("Nhap 1 de sap xep tang dan, 0 de sap xep giam dan: ");
			int tangDan;
			scanf("%d", &tangDan);
			interchangeSort(b, n, tangDan);
			printf("Mang sau khi sap xep (Interchange Sort): \n");
			xuatMangHonSo(b, n);
			selectionSort(b, n);
			printf("Mang sau khi sap xep (Selection Sort): \n");
			xuatMangHonSo(b, n);
			quickSort(b, 0, n - 1);
			printf("Mang sau khi sap xep (Quick Sort): \n");
			xuatMangHonSo(b, n);
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
