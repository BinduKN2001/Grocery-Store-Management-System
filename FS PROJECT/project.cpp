#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

class mall
{
    int pno;
    char name[30];
    float price, dis;

public:
    void getdata()
    {
        char ch;

        cout << "\n\tEnter the details of the product...";
        cout << "\n\tProduct No: ";
        cin >> pno;
        cin.get(ch);
        cout << "\n\tProduct Name: ";
        gets(name);
        cout << "\n\tProduct Price: ";
        cin >> price;
        cout << "\n\tProduct Discount(%): ";
        cin >> dis;
    }

    void showdata()
    {
        cout << setw(4) << pno << setw(20) << name << setw(8) << price << setw(10) << dis << "%" << "\n\t";
    }

    int retpno()
    {
        return pno;
    }

    float retprice()
    {
        return price;
    }

    char* retname()
    {
        return name;
    }

    int retdis()
    {
        return dis;
    }
};

fstream f;
mall m;

void menu()
{
    cout << "\n\t";

    cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(8) << "Price" << setw(10) << "Discount";
    cout << "\n\t--------------------------------------------\n\t";
}

void enter()
{
    system("cls");

    f.open("mall.txt", ios::in);
    int pno;
    cout << "\n\n\tEnter the Product No. to check for duplicate: ";
    cin >> pno;

    while (f.read((char*)&m, sizeof(mall)))
    {
        if (m.retpno() == pno)
        {
            cout << "\n\n\tProduct with Product No. " << pno << " already exists.";
            f.close();
            getch();
            return;
        }
    }
    f.close();

    f.open("mall.txt", ios::out | ios::app);
    m.getdata();
    f.write((char*)&m, sizeof(mall));
    f.close();

    cout << "\n\n\tProduct has been created...!!! ";
    getch();
}

void display()
{
    cout << "\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";

    f.open("mall.txt", ios::in);
    menu();

    while (f.peek() != EOF)
    {
        f.read((char*)&m, sizeof(mall));
        m.showdata();
    }
    f.close();
    getch();
}

void search()
{
    int no, flag = 0;
    system("cls");

    cout << "\n\n\tEnter the Product No. of the Product to be searched: ";
    cin >> no;

    f.open("mall.txt", ios::in);
    menu();

    while (f.read((char*)&m, sizeof(mall)))
    {
        if (m.retpno() == no)
        {
            m.showdata();
            flag = 1;
        }
    }
    f.close();

    if (flag == 0)
        cout << "\n\n\tRecord does not exist...!!!";
    getch();
}

void update()
{
    int no, found = 0;
    system("cls");

    cout << "\n\n\tTo Update...Enter The Product No: ";
    cin >> no;

    f.open("mall.txt", ios::in | ios::out);
    menu();

    while (f.read((char*)&m, sizeof(mall)) && found == 0)
    {
        if (m.retpno() == no)
        {
            m.showdata();
            m.getdata();

            int pos = -1 * sizeof(m);
            f.seekp(pos, ios::cur);
            f.write((char*)&m, sizeof(mall));

            cout << "\n\n\t Record has been Updated...!!!";
            found = 1;
        }
    }
    f.close();

    if (found == 0)
        cout << "\n\n\tRecord Not Found ";
    getch();
}

void erase()
{
    int no;
    system("cls");

    cout << "\n\n\n\tTo Delete...Enter The product No: ";
    cin >> no;

    f.open("mall.txt", ios::in | ios::out);
    fstream ft;
    ft.open("temp.txt", ios::out);
    f.seekg(0, ios::beg);

    bool recordDeleted = false; // Flag to check if the record was deleted

    while (f.read((char*)&m, sizeof(mall)))
    {
        if (m.retpno() != no)
        {
            ft.write((char*)&m, sizeof(mall));
        }
        else
        {
            recordDeleted = true;
        }
    }
    ft.close();
    f.close();

    remove("mall.txt");
    rename("temp.txt", "mall.txt");

    if (recordDeleted)
    {
        cout << "\n\n\tRecord has been Deleted...!!!";
        display();
    }
    else
    {
        cout << "\n\n\tRecord Not Found ";
    }
    getch();
}

void place_order()
{
    int order[30], quan[30], i = 0;
    float amt, damt, total = 0;
    char ch = 'Y';

    system("cls");

    display();

    cout << "\n\n\t============================";
    cout << "\n\t      PLACE YOUR ORDER";
    cout << "\n\t============================\n";

    do
    {
        cout << "\n\n\tEnter The Product No: ";
        cin >> order[i];
        cout << "\tQuantity: ";
        cin >> quan[i];

        i++;
        cout << "\n\tDo you want to order another product ?(y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    cout << "\n\n\tThank You...!!!";
    getch();

    system("cls");

    cout << "\n\n\t\t*BILL*\n\n\t\t";
    cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(8) << "Price" << setw(8) << "Amount" << setw(10) << "Discount" << endl;
    cout << "\t\t------------------------------------------------------------\n\t\t";

    for (int x = 0; x < i; x++)
    {
        f.open("mall.txt", ios::in);
        f.read((char*)&m, sizeof(mall));

        while (f)
        {
            if (m.retpno() != order[x])
            {
                amt = 0;
                damt = 0;
            }
            else
            {
                amt = m.retprice() * quan[x];
                damt = amt - (amt * m.retdis() / 100);

                cout << setw(4) << order[x] << setw(20) << m.retname() << setw(10) << quan[x] << setw(8) << m.retprice() << setw(8) << amt << setw(10) << damt << "\n\t\t";
                total += damt;
            }
            f.read((char*)&m, sizeof(mall));
        }
        f.close();
    }

    cout << "\n\t\t--------------------------------------------------------------";
    cout << "\n\t\tThank You...Visit Once Again...............TOTAL = " << "Rs." << total;
    cout << "\n\t\t--------------------------------------------------------------";
    getch();
}

void intro()
{
    cout << "\n\n\n\n\n\n\n\n\n\t\t\t\tGROCERY STORE MANAGEMENT SYSTEM\n\t\t\t\t~~~";
    cout << "\n\n\t\t\t\tMade By: K N BINDU                 10X20IS036\n\t\t\t\t-------------------------";
    cout << "\n\n\t\t\t\t-------- MOHAMMED DANISH SUHAIL    10X20IS046\n\t\t\t\t-------------------------";
    cout << "\n\n\t\t\t\t-------- MOHAMMED TANZIL TOUQUEER  10X20IS048\n\t\t\t\t-------------------------";
    cout << "\n\n\t\t\t\t-------- ALIYA MARIYAM             10X20IS010\n\t\t\t\t-------------------------";
    getch();
}

void welcome()
{
    system("cls");

    cout << "\n\t\t\t\tWelcome to Grocery Nest \n";
    getch();
}

void displayMenu(string role)
{
    cout << "\n\n\tMenu: " << endl;
    if (role == "admin")
    {
        cout << "\n\n\t1.Create Products" << endl;
        cout << "\n\n\t2.Display Products" << endl;
        cout << "\n\n\t3.Search Products" << endl;
        cout << "\n\n\t5.Delete Products" << endl;
        cout << "\n\n\t4.Modify Products" << endl;
        cout << "\n\n\t0. Exit" << endl;
    }
    else
    {
        cout << "\n\n\t2.Display Products" << endl;
        cout << "\n\n\t3.Search Products" << endl;
        cout << "\n\n\t6.Place an Order" << endl;
        cout << "\n\n\t0. Exit" << endl;
    }
}

int main()
{
    system("cls");
    intro();
    welcome();
    char ch;
    string userRole;
    cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\tEnter user role (admin/user): ";
    cin >> userRole;
    if (userRole != "admin" && userRole != "user")
    {
        cout << "\n\n\tInvalid user role. Exiting the program." << endl;
        exit(0);
    }

    if (userRole == "admin")
    {
        string username, password;

        cout << "\n\n\tEnter username: ";
        cin >> username;
        cout << "\n\n\tEnter password: ";
        cin >> password;

        if (username == "admin" && password == "password")
        {
            cout << "\n\n\tAccess granted. You are now logged in as an admin." << endl;
        }
        else
        {
            cout << "\n\n\tAccess denied" << endl;
            exit(0);
        }
    }

    do
    {
        displayMenu(userRole);
        cout << "\n\n\tEnter Your Choice: ";
        ch = getche();

        switch (ch)
        {
        case '1':
            if (userRole == "admin")
            {
                enter();
            }
            else
            {
                cout << "NOT ALLOWED TO ACCESS";
            }
            break;
        case '2':
            system("cls");
            display();
            break;
        case '3':
            search();
            break;
        case '4':
            if (userRole == "admin")
            {
                update();
            }
            else
            {
                cout << "NOT ALLOWED TO ACCESS";
            }
            break;
        case '5':
            if (userRole == "admin")
            {
                erase();
            }
            else
            {
                cout << "NOT ALLOWED TO ACCESS";
            }
            break;
        case '6':
            if (userRole == "user")
            {
                place_order();
            }
            else
            {
                cout << "NOT ALLOWED TO ACCESS";
            }
            break;
        case '0':
            exit(0);
        default:
            cout << "\a";
        }

    } while (ch != '7');

    getch();
    return 0;
}
