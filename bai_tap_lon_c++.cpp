#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

// cau truc luu thong tin san pham
struct SanPham {
    string maSanPham;
    string tenSanPham;
    string nhaCungCap;
    float donGia;

    SanPham(string maSP, string ten, string nhaCC, float gia) {
        maSanPham = maSP;
        tenSanPham = ten;
        nhaCungCap = nhaCC;
        donGia = gia;
    }
};

// hien thi thong tin san pham
void hienDiSanPham(SanPham sp) {
    cout << "ma san pham: " << sp.maSanPham << endl;
    cout << "ten san pham: " << sp.tenSanPham << endl;
    cout << "nha cung cap: " << sp.nhaCungCap << endl;
    cout << "don gia: " << sp.donGia << " VND" << endl;
    cout << "-------------------------------\n" << endl;
}

// tim kiem san pham theo ma (tim kiem tuyen tinh)
void timKiemSanPhamTheoMa(vector<SanPham> &dsSanPham, string maSP) {
    bool timThay = false;
    for (int i = 0; i < dsSanPham.size(); i++) {
        if (dsSanPham[i].maSanPham == maSP) {
            hienDiSanPham(dsSanPham[i]);
            timThay = true;
            break;
        }
    }
    if (!timThay) {
        cout << "khong tim thay san pham co ma '" << maSP << "'.\n";
    }
}

// tim kiem san pham theo ma va tra ve chi so
int timKiemSanPham(vector<SanPham> &dsSanPham, string maSP) {
    for (int i = 0; i < dsSanPham.size(); i++) {
        if (dsSanPham[i].maSanPham == maSP) {
            return i;
        }
    }
    return -1;
}

// sap xep chen theo don gia
void sapXepChen(vector<SanPham> &dsSanPham) {
    for (int i = 1; i < dsSanPham.size(); i++) {
        SanPham key = dsSanPham[i];
        int j = i - 1;
        while (j >= 0 && dsSanPham[j].donGia > key.donGia) {
            dsSanPham[j + 1] = dsSanPham[j];
            j = j - 1;
        }
        dsSanPham[j + 1] = key;
    }
}

// them san pham vao stack va danh sach, kiem tra trung ma
void themSanPham(stack<SanPham> &spStack, vector<SanPham> &dsSanPham) {
    string maSP, ten, nhaCC;
    float gia;

    cin.ignore();  // bo qua ky tu thua tu nhap truoc do
    bool trungLap;

    // kiem tra trung ma san pham
    do {
        trungLap = false;
        cout << "nhap ma san pham: ";
        getline(cin, maSP);

        if (timKiemSanPham(dsSanPham, maSP) != -1) {
            cout << "ma san pham da ton tai. vui long nhap ma khac.\n";
            trungLap = true;
        }
    } while (trungLap);

    cout << "nhap ten san pham: ";
    getline(cin, ten);
    cout << "nhap nha cung cap: ";
    getline(cin, nhaCC);
    cout << "nhap don gia: ";
    cin >> gia;

    // tao san pham moi va them vao stack va danh sach
    SanPham sp(maSP, ten, nhaCC, gia);
    spStack.push(sp); // them san pham vao stack
    dsSanPham.push_back(sp); // them san pham vao danh sach

    sapXepChen(dsSanPham); // sap xep lai danh sach
    cout << "da them san pham vao danh sach.\n";
    cout << "-----------------------\n";
}

// xoa san pham theo ma
void xoaSanPham(vector<SanPham> &dsSanPham) {
    string maSP;
    int index;

    do {
        cin.ignore();
        cout << "nhap ma san pham muon xoa: ";
        getline(cin, maSP);

        index = timKiemSanPham(dsSanPham, maSP);
        if (index != -1) {
            dsSanPham.erase(dsSanPham.begin() + index);
            cout << "da xoa san pham.\n";
            cout << "----------------------\n";
        } else {
            cout << "khong tim thay san pham. vui long nhap lai.\n";
        }
    } while (index == -1);  // lap lai cho toi khi tim thay maSanPham
}

// sua thong tin san pham theo ma
void suaSanPham(vector<SanPham> &dsSanPham) {
    string maSP;
    bool timThay = false;

    do {
        cout << "nhap ma san pham muon sua: ";
        getline(cin, maSP);

        int index = timKiemSanPham(dsSanPham, maSP);

        if (index != -1) {
            cout << "nhap ten san pham moi: ";
            getline(cin, dsSanPham[index].tenSanPham);

            cout << "nhap nha cung cap moi: ";
            getline(cin, dsSanPham[index].nhaCungCap);

            cout << "nhap don gia moi: ";
            cin >> dsSanPham[index].donGia;
            cin.ignore(); 
            cout << "da sua thong tin san pham.\n";
            timThay = true; // danh dau da tim thay
        } else {
            cout << "khong tim thay san pham co ma '" << maSP << "'. vui long nhap lai.\n";
        }
    } while (!timThay); // lap lai khi k tim thay san pham
}

// hien thi tat ca san pham
void hienThiTatCaSanPham(vector<SanPham> &dsSanPham) {
    for (int i = 0; i < dsSanPham.size(); i++) {
        hienDiSanPham(dsSanPham[i]);
    }
}

// sap xep va hien thi danh sach theo don gia tang dan
void sapXepTangDan(vector<SanPham> &dsSanPham) {
    sapXepChen(dsSanPham);
    cout << "danh sach da duoc sap xep tang dan theo don gia.\n";
    hienThiTatCaSanPham(dsSanPham);
}

int main() {
    stack<SanPham> spStack; // stack luu san pham
    vector<SanPham> dsSanPham; // danh sach cac san pham
    int luaChon;

    do {
        cout << "1. them san pham\n";
        cout << "2. sua san pham\n";
        cout << "3. xoa san pham\n";
        cout << "4. hien thi tat ca san pham\n";
        cout << "5. tim kiem san pham theo ma san pham\n";
        cout << "6. sap xep san pham tang dan theo don gia\n";
        cout << "7. thoat\n";
        cout << "nhap lua chon: ";
        cin >> luaChon;
        cout << "-----------------------\n";

        switch (luaChon) {
            case 1:
                themSanPham(spStack, dsSanPham);
                break;
            case 2:
                suaSanPham(dsSanPham);
                break;
            case 3:
                xoaSanPham(dsSanPham);
                break;
            case 4:
                hienThiTatCaSanPham(dsSanPham);
                break;
            case 5: {
                string maTimKiem;
                cin.ignore();  // bo qua ky tu thua tu nhap truoc do
                cout << "nhap ma san pham can tim: ";
                getline(cin, maTimKiem);
                timKiemSanPhamTheoMa(dsSanPham, maTimKiem);
                break;
            }
            case 6:
                sapXepTangDan(dsSanPham);
                break;
            case 7:
                cout << "thoat chuong trinh.\n";
                break;
            default:
                cout << "lua chon khong hop le. vui long nhap lai.\n";
                break;
        }

    } while (luaChon != 7);

    return 0;
}

