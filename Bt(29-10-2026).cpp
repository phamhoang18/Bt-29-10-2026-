#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>
using namespace std;

struct HH{
	int mahh, ngay, thang, nam;
	string ten;
	float giaxuat;
};

void td(){
	cout << left << setw(20) << "Ma hang hoa" << setw(20) << "Ten hang hoa" << setw(20) << "Ngay xuat" << setw(20) << "Gia xuat hang hoa" << endl;
	cout << string(80, '-') << endl;
}

void nhap(HH *h, int n){
	for (int i = 0; i < n; i++){
		cout << "- Nhap thong tin hang hoa thu " << i+1 << ": " << endl;
		cout << "	+ Ma hang hoa: "; cin >> h[i].mahh;
		cout << "	+ Ten hang hoa: "; getline (cin >> ws, h[i].ten);
		do{
			cout << "	+ Ngay xuat hang: "; cin >> h[i].ngay;
		}while (h[i].ngay <= 0 || h[i].ngay > 31);
		do{
			cout << "	+ Thang xuat hang: "; cin >> h[i].thang;
		}while (h[i].thang <= 0 || h[i].thang > 12);
		do{
			cout << "	+ Nam xuat hang: "; cin >> h[i].nam;
		}while (h[i].nam <= 0);
		do{
			cout << "	+ Gia xuat hang: "; cin >> h[i].giaxuat;
		}while (h[i].giaxuat <= 0);
	}
}

void xuat(HH *h, int n){
	for (int i = 0; i < n; i++){
		string ngayxuat = to_string(h[i].ngay) + "/" + to_string(h[i].thang) + "/" + to_string(h[i].nam);
		cout << left << setw(20) << h[i].mahh << setw(20) << h[i].ten << setw(20) << ngayxuat << setw(20) << fixed << setprecision(2) << h[i].giaxuat << endl;
		cout << string (80, '-') << endl;
	}
}

int partition(HH *h, int left, int right) {
    int i = left, j = right;
    float x = h[(left + right) / 2].giaxuat;  

    while (i <= j) {
        while (h[i].giaxuat < x) i++;
        while (h[j].giaxuat > x) j--;
        if (i <= j) {
            swap(h[i], h[j]);
            i++;
            j--;
        }
    }
    return i; 
}

void quickSort(HH *h, int left, int right) {
    if (left >= right) return;

    int i = partition(h, left, right);

    if (left < i - 1) quickSort(h, left, i - 1);
    if (i < right)    quickSort(h, i, right);
}

void Find(int n, HH *h, float x){
	int left = 0;
	int right = n - 1;
	int found = -1;
	while (left <= right){
		int mid = (left + right) / 2;
		if (abs(h[mid].giaxuat - x) < 0.00001){
			found = mid;
			break;
		}
		if (h[mid].giaxuat > x){
			right = mid - 1;
		}else{
			left = mid + 1;
		}
	}
	if(found == -1){
		cout << "=> Khong tim thay hang hoa co gia xuat " << x << " trong danh sach!" << endl;
		return;
	}
	
	int first = found;
	while (first > 0 && abs(h[first - 1].giaxuat - x) < 0.0001){
		first--;
	}
	int last = found;
	while (last < n - 1 && abs(h[last + 1].giaxuat - x) < 0.0001){
		last++;
	}
	cout << "\n- Danh sach hang hoa co gia xuat la " << x << ": " << endl;
	td();
	for (int i = first; i <= last; i++){
		xuat(&h[i], 1);
	}
}

int main(){
	int n;
	do{
		cout << "- Nhap so luong nhan vien: "; cin >> n; cin.ignore();
	}while (n <= 0);
	
	HH *h = new HH[n];
	
	nhap(h, n);
	
	cout << "\n- Danh sach hang hoa sau khi nhap: " << endl;
	td();
	xuat(h, n);
	
	cout << "\n Danh sach hang hoa sau khi co su sap xep: " << endl;
	quickSort(h, 0, n - 1);
	td();
	xuat(h, n);
	
	float x;
	do{
		cout << "\n- Nhap gia xuat hang hoa can tim kiem: "; cin >> x; cin.ignore();
	}while (x <= 0);
	Find(n, h, x);
	delete[] h;
	return 0;
}
