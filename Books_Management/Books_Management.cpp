#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<set>
#include<map>//dungf ctdl map de dem tan so xuat hien
#include<iomanip>//thu vien nay dung de can chinh dong, tao bang hien thi danh sach
#include<vector>

using namespace std;
set<string> Theloai;//Tao mot set de luu cac the loai cua sach
// tao cau truc sach
struct Sach {
	string MaSach;
	string TenSach;
	string TenTg;
	string Nhaxb;
	int Namxb;
	string TheLoai;
};
//tao danh sach
struct DNode {
	Sach Data;
	DNode* prev;//tro den phan tu truoc
	DNode* next;//tro den phan tu sau
};
struct DList {
	DNode* Head;
	DNode* Tail;
};
void Init_Dlist(DList& dl) {
	dl.Head = dl.Tail = NULL;
}
bool IsEmpty(DList dl) {
	if (dl.Head == NULL) return true;
	return false;
}
//Tao node
DNode* CreateDnode(Sach x) {
	DNode* p = new DNode;
	p->Data = x;
	p->next = p->prev = NULL;
	return p;
}
//them phan tu
void Add_Head(DList& dl, DNode* p) {
	if (p == NULL) {
		cerr << "Cap phat that bai !";
		return;
	}
	if (IsEmpty(dl)) {
		dl.Head = dl.Tail = p;
		return;
	}
	p->next = dl.Head;
	dl.Head->prev = p;
	dl.Head = p;
}
void Add_Tail(DList& dl, DNode* p) {
	if (p == NULL) {
		cerr << "Cap phat that bai !";
		return;
	}
	if (IsEmpty(dl)) {
		dl.Head = dl.Tail = p;
		return;
	}
	dl.Tail->next = p;
	p->prev = dl.Tail;
	dl.Tail = p;
}
//them truoc ten sach
void Add_Before(DList& dl, DNode* p, DNode* q) {//them p truoc q
	if (IsEmpty(dl)) {
		cerr << "Danh sach rong, thao tac that bai!";
		return;
	}
	if (p == NULL || q == NULL) {
		cerr << "Loi khong tim thay du lieu thao tac!";
		return;
	}
	if (dl.Head == q || dl.Tail == q) {
		Add_Head(dl, q);
		return;
	}
	DNode* pr = q->prev;
	pr->next = p;
	p->prev = pr;
	p->next = q;
	q->prev = p;
	return;
}
//them vao vi tri bat ky
//lay node o vi tri bat ky
DNode* GetNodeIdx(DList dl, int n) {
	while (IsEmpty(dl)) return NULL;
	DNode* p = dl.Head;
	while (n - 1) {
		p = p->next;
		n--;
	}
	return p;
}
int Size(DList dl) {
	DNode* p = dl.Head;
	int cnt = 0;
	while (p != NULL) {
		cnt++;
		p = p->next;
	}
	return cnt;
}
void Add_Idx(DList& dl, DNode* q, int n) {
	if (n == 1) {
		Add_Head(dl, q);
		return;
	}
	if (n == Size(dl)) {
		Add_Tail(dl, q);
		return;
	}
	DNode* p = GetNodeIdx(dl, n);
	Add_Before(dl, q, p);
	return;
}
DNode* GetNode(DList dl, string s) {//lay node co ten nao do
	DNode* p = dl.Head;
	while (p != NULL) {
		if (p->Data.TenSach == s) return p;
		p = p->next;
	}
	return NULL;
}
//Nhap Du lieu
Sach InputFromKeyboard() {
	Sach x;
	cout << "\tNhap ma sach: "; getline(cin, x.MaSach);
	cout << "\tNhap ten sach: "; getline(cin, x.TenSach);
	cout << "\tNhap ten tac gia: "; getline(cin, x.TenTg);
	cout << "\tNhap ten nha xuat ban: "; getline(cin, x.Nhaxb);
	cout << "\tNhap nam xuat ban: "; cin >> x.Namxb;
	cin.ignore();//Xu ly troi lenh
	cout << "\tNhap the loai: "; getline(cin, x.TheLoai);
	Theloai.insert(x.TheLoai);//thêm th? lo?i vào set
	return x;
}
void InputFromFile(DList& dl) {
	string s;
	ifstream file("input.txt");
	if (!file.is_open()) {
		cerr << "Mo file that bai!!" << endl;
		return;
	}
	string str;
	while (getline(file, str)) {
		Sach x;
		stringstream ss(str);
		getline(ss, x.MaSach, ',');
		getline(ss, x.TenSach, ',');
		getline(ss, x.TenTg, ',');
		getline(ss, x.Nhaxb, ',');
		ss >> x.Namxb;
		ss.ignore();//xu ly troi lenh trong luong stringstream
		getline(ss, x.TheLoai, ',');
		Add_Tail(dl, CreateDnode(x));
	}
	file.close();
	cout << "Successfully!" << endl;
	return;
}
//xoa
void Dlt_Head(DList& dl) {//xoa dau
	if (IsEmpty(dl)) {
		return;
	}
	DNode* p = dl.Head;
	if (dl.Head == dl.Tail) {
		Init_Dlist(dl);
		delete p;
		return;
	}
	dl.Head = dl.Head->next;
	dl.Head->prev = NULL;
	delete p;
}
void Dlt_Tail(DList& dl) {
	if (IsEmpty(dl)) {
		return;
	}
	DNode* p = dl.Tail;
	if (dl.Head == dl.Tail) {
		Init_Dlist(dl);
		delete p;
		return;
	}
	dl.Tail = dl.Tail->prev;
	dl.Tail->next = NULL;
	delete p;
}
void DLt_Book(DList& dl, DNode* p) {//xoa 1 quyen sach
	if (p == NULL) {
		cerr << "Khong tim thay sach!";
		return;
	}
	if (IsEmpty(dl)) {
		cerr << "Danh sach rong!";
		return;
	}
	if (dl.Head == dl.Tail && dl.Head == p) {
		Init_Dlist(dl);
		cout << "Done!";
		return;
	}
	if (dl.Head == p) {
		Dlt_Head(dl);
		return;
	}
	if (dl.Tail == p) {
		Dlt_Tail(dl);
		return;
	}
	DNode* x = p->prev;
	DNode* y = p->next;
	x->next = y;
	y->prev = x;
	delete p;
}
void Dlt_List(DList& dl) {
	DNode* p = dl.Head;
	while (!IsEmpty(dl)) {
		Dlt_Head(dl);
	}
}
//Sap xep danh dach theo the loai->theo ma sach
void swap(DNode* p, DNode* q) {
	Sach temp = p->Data;
	p->Data = q->Data;
	q->Data = p->Data;
}
void SortbyCtg(DList& dl) {
	for (DNode* p = dl.Head; p != NULL; p = p->next) {
		for (DNode* q = p; q != NULL; q = q->next) {
			if (p->Data.TheLoai < q->Data.TheLoai) swap(p->Data, q->Data);
		}
	}
}
void SortByCode(DList& dl) {
	for (DNode* p = dl.Head; p != NULL; p = p->next) {
		for (DNode* q = p; q != NULL; q = q->next) {
			if (p->Data.MaSach > q->Data.MaSach) swap(p->Data, q->Data);
		}
	}
}
void Sort(DList& dl) {
	SortbyCtg(dl);
	SortByCode(dl);
}
//Tac gia co nhieu sach nhat
void Authors(DList dl) {
	map<string, int> at;//string luu ten tac gia, int luu tan suat
	DNode* p = dl.Head;
	while (p != NULL) {
		at[p->Data.TenTg]++;
		/*duyet danh sach, dua ten tac gia vaof map, neu gap
		lai tac gia do thi tang len so lan trong pt second(tan so)*/
		p = p->next;
	}
	//tim tan so lon nhat
	int frqmax = 0;
	for (auto x : at) {//dyuet map bang auto
		if (frqmax < x.second) frqmax = x.second;
	}
	cout << "Cac tac gia co nhieu sach nhat voi " << frqmax << " quyen sach la: " << endl;
	for (auto x : at) {
		if (x.second == frqmax) {
			cout << "\t" << x.first << endl;
		}
	}
	int z;
	cout << "Ban co muon in ra danh sach khong: " << endl;
	cout << "0. Khong.\n1. Co.\n\tOPTION: "; cin >> z;
	system("cls");
	switch (z) {
	case 0: {
		break;
	}
	case 1: {
		cout << "Danh sach tac gia co nhieu sach nhat nhat: " << endl;
		cout << "************************************************************************************************************************************" << endl;
		cout << setw(18) << left << "Ma Sach" << setw(33) << left << "Ten Sach" << setw(20) << left << "Tac Gia" << setw(27) << left << "Nha Xuat ban" << setw(21) << left << "Nam Xuat Ban" << setw(30) << left << "The Loai" << endl;
		cout << "************************************************************************************************************************************" << endl;
		for (auto x : at) {//dyuet map bang auto
			if (x.second == frqmax) {
				DNode* q = dl.Head;
				while (q != NULL) {
					if (q->Data.TenTg == x.first) {
						cout << setw(13) << left << q->Data.MaSach << setw(35) << left << q->Data.TenSach << setw(20) << left << q->Data.TenTg << setw(34) << left << q->Data.Nhaxb << setw(16) << left << q->Data.Namxb << setw(30) << left << q->Data.TheLoai << endl;
					}
					q = q->next;
				}
			}
		}
		break;
	}
	}

}
//Nha xuat ban co it sach nhat
void Publisher(DList dl) {
	//dung CTDL map tuong tu voi tim tac gia co nhieu sach nhat 
	map<string, int> pl;
	DNode* p = dl.Head;
	while (p != NULL) {//luu tan suat
		pl[p->Data.Nhaxb]++;
		p = p->next;
	}
	//tim tan saut nho nhat
	int frqmin = 999;
	for (auto x : pl) {
		if (frqmin > x.second) frqmin = x.second;
	}
	cout << "Cac nha xuat ban co it sach nhat voi " << frqmin << " quyen sach la: " << endl;
	for (auto x : pl) {
		if (x.second == frqmin) {
			cout << "\t" << x.first << endl;
		}
	}
	int z;
	cout << "Ban co muon in ra danh sach khong: " << endl;
	cout << "0. Khong.\n1. Co.\n\tOPTION: "; cin >> z;
	system("cls");

	switch (z) {
	case 0: {
		break;
	}
	case 1: {
		cout << "Danh sach nha xuat ban co it sach nhat: " << endl;
		cout << "************************************************************************************************************************************" << endl;
		cout << setw(18) << left << "Ma Sach" << setw(33) << left << "Ten Sach" << setw(20) << left << "Tac Gia" << setw(27) << left << "Nha Xuat ban" << setw(21) << left << "Nam Xuat Ban" << setw(30) << left << "The Loai" << endl;
		cout << "************************************************************************************************************************************" << endl;
		for (auto x : pl) {//dyuet map bang auto
			if (x.second == frqmin) {
				DNode* q = dl.Head;
				while (q != NULL) {
					if (q->Data.Nhaxb == x.first) {
						cout << setw(13) << left << q->Data.MaSach << setw(35) << left << q->Data.TenSach << setw(20) << left << q->Data.TenTg << setw(34) << left << q->Data.Nhaxb << setw(16) << left << q->Data.Namxb << setw(30) << left << q->Data.TheLoai << endl;
					}
					q = q->next;
				}
			}
		}
		break;
	}
	}
}
//Thong ke sach theo tung nam
void Years(DList dl) {
	//dungf CTDL set de luu nam
	set<int> yr;
	DNode* p = dl.Head;
	while (p != NULL) {
		yr.insert(p->Data.Namxb);
		p = p->next;
	}
	//CTDL set luon sap sep du lieu theo thu tu tang dan nen không can sap sep
	cout << "************************************************************************************************************************************" << endl;
	cout << setw(18) << left << "Ma Sach" << setw(33) << left << "Ten Sach" << setw(20) << left << "Tac Gia" << setw(27) << left << "Nha Xuat ban" << setw(21) << left << "Nam Xuat Ban" << setw(30) << left << "The Loai" << endl;
	cout << "************************************************************************************************************************************" << endl;
	for (auto x : yr) {
		DNode* q = dl.Head;
		while (q != NULL) {
			if (q->Data.Namxb == x) {
				cout << setw(13) << left << q->Data.MaSach << setw(35) << left << q->Data.TenSach << setw(20) << left << q->Data.TenTg << setw(34) << left << q->Data.Nhaxb << setw(16) << left << q->Data.Namxb << setw(30) << left << q->Data.TheLoai << endl;
			}
			q = q->next;
		}
	}
}

void PrintList(DList dl) {
	if (IsEmpty(dl)) {
		cout << "Danh sach rong !!" << endl;
		return;
	}
	//tao bang
	//dung setw trong thu vien iomanip va left de can chinh ben trai 
	cout << "************************************************************************************************************************************" << endl;
	cout << setw(18) << left << "Ma Sach" << setw(33) << left << "Ten Sach" << setw(20) << left << "Tac Gia" << setw(27) << left << "Nha Xuat ban" << setw(21) << left << "Nam Xuat Ban" << setw(30) << left << "The Loai" << endl;
	cout << "************************************************************************************************************************************" << endl;
	DNode* p = dl.Head;
	while (p != NULL) {
		cout << setw(13) << left << p->Data.MaSach << setw(35) << left << p->Data.TenSach << setw(20) << left << p->Data.TenTg << setw(34) << left << p->Data.Nhaxb << setw(16) << left << p->Data.Namxb << setw(30) << left << p->Data.TheLoai << endl;
		p = p->next;
	}
}
//Dem so luong sach theo tung the loai
void CountBooks(DList dl) {
	map<string, int> Danhsach;
	//dung map de thuc hien bai toan dem tan suat
	DNode* p = dl.Head;
	while (p != NULL) {
		Danhsach[p->Data.TheLoai]++;
		p = p->next;
	}
	for (auto x : Danhsach) {
		cout << "The loai " << x.first << " co " << x.second << " quyen sach." << endl;
	}
}
//kiiem tra 'lap trinh' co trong ten sach hay khong
int CheckString(string str1, string str2) {//str2 cos trong str1 hay khong
	if (str1.find(str2) != std::string::npos) {
		return 1;
	}
	return 0;
}
int CountString(DList dl) {
	DNode* p = dl.Head;
	int cnt = 0;
	while (p != NULL) {
		if (CheckString(p->Data.TenSach, "Lap Trinh") || CheckString(p->Data.TenSach, "Lap trinh") || CheckString(p->Data.TenSach, "lap trinh") || CheckString(p->Data.TenSach, "LAP TRINH")) cnt++;
		p = p->next;
	}
	return cnt;
}
//\"de in dau " ra man hinh console 
void Caseleven(DList dl) {
	int a = CountString(dl);
	cout << "Co " << a << " cuon sach co ten chua chuoi \"lap trinh\"." << endl;
	if (a == 0) return;
	int z;
	cout << "Ban co muon in ra danh sach khong: " << endl;
	cout << "0. Khong.\n1. Co.\n\tOPTION: "; cin >> z;
	system("cls");
	switch (z) {
	case 0: {
		break;
	}
	case 1: {
		cout << "Danh sach nha xuat ban co it sach nhat: " << endl;
		cout << "************************************************************************************************************************************" << endl;
		cout << setw(18) << left << "Ma Sach" << setw(33) << left << "Ten Sach" << setw(20) << left << "Tac Gia" << setw(27) << left << "Nha Xuat ban" << setw(21) << left << "Nam Xuat Ban" << setw(30) << left << "The Loai" << endl;
		cout << "************************************************************************************************************************************" << endl;
		DNode* p = dl.Head;
		while (p != NULL) {
			if (CheckString(p->Data.TenSach, "Lap Trinh") || CheckString(p->Data.TenSach, "Lap trinh") || CheckString(p->Data.TenSach, "lap trinh") || CheckString(p->Data.TenSach, "LAP TRINH")) {
				cout << setw(13) << left << p->Data.MaSach << setw(35) << left << p->Data.TenSach << setw(20) << left << p->Data.TenTg << setw(34) << left << p->Data.Nhaxb << setw(16) << left << p->Data.Namxb << setw(30) << left << p->Data.TheLoai << endl;
			}
			p = p->next;
		}
		system("pause");
		system("cls");
		break;
	}
	}
}
void FindBooks(DList dl, string s) {
	DNode* p = dl.Head;
	int cnt = 0;
	while (p != NULL) {
		if (CheckString(p->Data.TenSach, s)) {
			cnt++;
		}
		p = p->next;
	}
	cout << "Tim duoc " << cnt << " quyen sach." << endl;
	if (cnt == 0) return;
	int z;
	cout << "Ban co muon in ra danh sach khong: " << endl;
	cout << "0. Khong.\n1. Co.\n\tOPTION: "; cin >> z;
	system("cls");
	switch (z) {
	case 0: {
		break;
	}
	case 1: {
		cout << "Danh sach sach tim duoc chua tu khoa: " << s << endl;
		cout << "************************************************************************************************************************************" << endl;
		cout << setw(18) << left << "Ma Sach" << setw(33) << left << "Ten Sach" << setw(20) << left << "Tac Gia" << setw(27) << left << "Nha Xuat ban" << setw(21) << left << "Nam Xuat Ban" << setw(30) << left << "The Loai" << endl;
		cout << "************************************************************************************************************************************" << endl;
		DNode* p = dl.Head;
		while (p != NULL) {
			if (CheckString(p->Data.TenSach, s)) {
				cout << setw(13) << left << p->Data.MaSach << setw(35) << left << p->Data.TenSach << setw(20) << left << p->Data.TenTg << setw(34) << left << p->Data.Nhaxb << setw(16) << left << p->Data.Namxb << setw(30) << left << p->Data.TheLoai << endl;
			}
			p = p->next;
		}
		system("pause");
		system("cls");
		break;
	}
	}
}
void Menu() {
	cout << "+---------------------------------------------------------------+" << endl;
	cout << "|                 CHUONG TRINH QUAN LY SACH                     |" << endl;
	cout << "+---------------------------------------------------------------+" << endl;
	cout << "|  0. Thoat chuong trinh.                                       |" << endl;
	cout << "|  1. Nhap du lieu.                                             |" << endl;
	cout << "|  2. Them phan tu.                                             |" << endl;
	cout << "|  3. Xoa phan tu.                                              |" << endl;
	cout << "|  4. Sap xep danh sach theo the loai va theo ma sach.          |" << endl;
	cout << "|  5. Xuat ra cac tac gia co nhieu sach nhat va sach cua ho.    |" << endl;
	cout << "|  6. Xuat nha xuat ban co it sach nhat va cac quyen sach do.   |" << endl;
	cout << "|  7. Thong ke sach theo tung nam.                              |" << endl;
	cout << "|  8. Thong ke so luong sach theo tung the loai.                |" << endl;
	cout << "|  9. Tim sach co ten chua cum tu \"lap trinh\".                  |" << endl;
	cout << "|  10. (Bonus) Tim sach.                                        |" << endl;
	cout << "|  11. Xuat danh sach.                                          |" << endl;
	cout << "+---------------------------------------------------------------+" << endl;
	cout << "\t\t\t OPTION: ";

}
int main() {
	DList dl;
	Init_Dlist(dl);
	int z;
	do {
		Menu();
		cin >> z;
		system("cls");
		switch (z) {
		case 1: {
			int x;
			cout << "1. Nhap thu cong." << endl;
			cout << "2. Lay du lieu tu file." << endl;
			cout << "          OPTION: "; cin >> x;
			system("cls");
			switch (x) {
			case 1: {
				int n;
				cout << "So luong sach ban muon them vao list: ";
				cin >> n;
				cin.ignore();
				for (int i = 0; i < n; i++) {
					cout << "Sach thu " << i + 1;
					Sach x = InputFromKeyboard();
					Add_Tail(dl, CreateDnode(x));
				}
				break;
			}
			case 2: {
				InputFromFile(dl);
				break;
			}
			}
			system("pause");
			system("cls");
			break;
		}
		case 2: {
			cout << "Ban muon them sach vao vi tri nao? " << endl;
			cout << "0. Thoat." << endl;
			cout << "1. Them dau." << endl;
			cout << "2. Them giua." << endl;
			cout << "3. Them cuoi." << endl;
			cout << "*************" << endl;
			cout << "\tOPTION: ";
			int c; cin >> c;
			switch (c) {
			case 0: {
				system("cls");
				break;
			}
			case 1: {
				cin.ignore();
				Sach x = InputFromKeyboard();
				Add_Head(dl, CreateDnode(x));
				cout << "Done!" << endl;
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				if (IsEmpty(dl)) {
					cerr << "Danh sach rong!!" << endl;
					cout << "Thoat chuong trinh!" << endl;
					system("pause");
					system("cls");
					break;
				}
				cin.ignore();
				Sach x = InputFromKeyboard();
				int n;
				cout << "Nhap vi tri muon them phan tu: "; cin >> n;
				Add_Idx(dl, CreateDnode(x), n);
				cout << "Done!" << endl;
				system("pause");
				system("cls");
				break;
			}
			case 3: {
				cin.ignore();
				Sach x = InputFromKeyboard();
				Add_Tail(dl, CreateDnode(x));
				cout << "Done!" << endl;
				system("pause");
				system("cls");
				break;
			}
			}
			break;
		}
		case 3: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			cout << "Ban muon them sach vao vi tri nao? " << endl;
			cout << "0. Thoat." << endl;
			cout << "1. Xoa quyen sach dau danh sach." << endl;
			cout << "2. Xoa quyen sach bat ky theo ten." << endl;
			cout << "3. Xoa quyen sach cuoi danh sach." << endl;
			cout << "************************************" << endl;
			cout << "\tOPTION: "; int c; cin >> c;
			cin.ignore();
			switch (c) {
			case 0: {
				system("cls");
				break;
			}
			case 1: {
				Dlt_Head(dl);
				cout << "Done!" << endl;
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				string s;
				cout << "Nhap ten cuon sach can xoa: "; getline(cin, s);
				DNode* p = GetNode(dl, s);
				if (p == NULL) {
					cerr << "Khong tim thay sach can xoa !" << endl;;
					break;
				}
				DLt_Book(dl, p);
				cout << "Done!" << endl;
				system("pause");
				system("cls");
				break;
			}
			case 3: {
				Dlt_Tail(dl);
				cout << "Done!" << endl;
				system("pause");
				system("cls");
				break;
			}
			}
			break;
		}
		case 4: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			Sort(dl);
			cout << "Done! " << endl;
			cout << "Pick Option 11 de xem ket qua!" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 5: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			Authors(dl);
			system("pause");
			system("cls");
			cout << "Done!" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 6: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			Publisher(dl);
			system("pause");
			system("cls");
			cout << "Done!" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 7: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			cout << "Danh sach xep theo thu tu tang dan: " << endl;
			Years(dl);
			system("pause");
			system("cls");
			cout << "Done!" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 8: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			CountBooks(dl);
			system("pause");
			system("cls");
			cout << "Done!" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 9: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			Caseleven(dl);
			cout << "Done!" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 10: {
			if (IsEmpty(dl)) {
				cerr << "Danh sach rong!!" << endl;
				cout << "Thoat chuong trinh!" << endl;
				system("pause");
				system("cls");
				break;
			}
			cin.ignore();
			cout << "Tim kiem ten tai day: ";
			string s; getline(cin, s);
			FindBooks(dl, s);
			cout << "Done!" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 11: {
			PrintList(dl);
			system("pause");
			system("cls");
			break;
		}
		}
	} while (z != 0);;
	return 0;
}