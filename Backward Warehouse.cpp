// Lab 5 Mohammadzadeh,Hiva Thursday
// BackWard Warehouse- stacks

#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>

using namespace std;

class WidgetType {
    
private:
    int quantity;
    double cost;
    WidgetType *next;
    
public:
    WidgetType();
    ~WidgetType();

    void SetCost(double newCost) {
        cost = newCost;
    }
    
    void SetQuantity(int newQuantity) {
        quantity = newQuantity;
    }
    
    void SetNext(WidgetType * newNext) {
        next = newNext;
    }
    
    WidgetType *GetNext() {
        return next;
    }
    
    double GetCost() {
        return cost;
    }
    
    int GetQuantity() {
        return quantity;
    }

};

WidgetType::WidgetType() {
    //Constructor
    quantity = 0;
    cost = 0;
    next = nullptr;
}

WidgetType::~WidgetType() {
    //Destructor
    quantity = 0;
    cost = 0;
    next = nullptr;
}


class StackType {
    
private:
    WidgetType * top;

public:
    StackType();
    ~StackType();

    bool isEmpty();
    void Push(int quantity, double cost);
    void Pop();
    WidgetType *Peek();
    void MakeEmpty();
    void Inventory(int, double);
    void Ship(int);
    void Print();
};

void SellOrders(StackType&, StackType&);

enum Option { Inventory = 1, Order, Current, Quit };

StackType::StackType() {
    top = nullptr;
}

StackType::~StackType() {
    MakeEmpty();
}

void StackType::MakeEmpty() {
    while (top != nullptr){
        Pop();
    }
}

bool StackType::isEmpty() {
    return (top == nullptr);
}

void StackType::Push(int quantity, double cost = 0) {
    
    WidgetType *newItem = new (nothrow) WidgetType;
    
    if (newItem == nullptr) {
        cout << "ERROR: Item was not created. There is not enough memory." << endl;
        MakeEmpty();
        system("pause");
        exit(1);
    }
    
    newItem->SetCost(cost);
    newItem->SetQuantity(quantity);
    newItem->SetNext(top);
    top = newItem;
}

void StackType::Pop() {
    
    WidgetType * temp = nullptr;
    
    if (top != nullptr) {
        temp = top;
        top = top->GetNext();
        delete temp;
    }
    
    temp = nullptr;
}

WidgetType* StackType::Peek() {
    return top;
}

void StackType::Print() {
    WidgetType *temp = top;
    
    while (temp != nullptr) {
        
        if (temp->GetCost() != 0) {
            
            cout << "Widget Price: $" << temp->GetCost() << "\t\t" << "In Stock: " << temp->GetQuantity() << endl;
        }
        
        else {
            
            cout << "Number of widgets backlogged: " << temp->GetQuantity() << endl;
        }
        
        temp = temp->GetNext();
    }
}

void StackType::Inventory(int quantity, double cost) {
    
    cout << "\nDELIVERY\nPlease enter the amount of orders: ";
    cin >> quantity;
    
    while (quantity < 1 || cin.fail()) {
        
        cout << "\nERROR: Quantity must be a positive whole number. Please try again.\n" << endl;
        cout << "Please enter the amount of orders: ";
        cin >> quantity;
        cin.clear();
        cin.ignore(200, '\n');
    }

    cout << "Please enter the cost: $";
    cin >> cost;
    
    while (cost < 0.01 || cin.fail()) {
        
        cout << "\nERROR: Cost must be a positive number. Please try again.\n" << endl;
        cout << "Please enter the cost: $";
        cin >> cost;
        cin.clear();
        cin.ignore(200, '\n');
    }

    Push(quantity, cost);
}

void StackType::Ship(int quantity) {
    
    cout << "\nPlease enter the amount of orders: ";
    cin >> quantity;

    while (quantity < 1 || cin.fail()) {
        
        cout << "\nERROR: Orders must be a positive whole number. Please try again.\n" << endl;
        cout << "Please enter the amount of orders: ";
        cin >> quantity;
        cin.clear();
        cin.ignore(200, '\n');
    }

    Push(quantity);
}


int main() {
    
    int userInput = 0;
    StackType Widgets;
    StackType Orders;
    double cost = 0;
    int quantity = 0;
    int orderNumber = 1000;

    cout << showpoint << fixed << setprecision(2);
    cout << "WELCOME!" << endl;
    
    do {
        cout << "\nEnter 1 to add new widgets to the inventory.\n"
            << "Enter 2 to place an order.\n"
            << "Enter 3 to print the current inventory.\n"
            << "Enter 4 to quit the program.\n" << endl;
        cin >> userInput;

        switch (userInput) {
                
            case Inventory:
                
                cout << "\n====================================" << endl;
                Widgets.Inventory(quantity, cost);
                SellOrders(Widgets, Orders);
                cout << "====================================" << endl;
                break;
                
            case Order:
                
                cout << "\n====================================" << endl;
                cout << "\nORDER #" << orderNumber;
                orderNumber++;
                Orders.Ship(quantity);
                SellOrders(Widgets, Orders);
                cout << "\n====================================" << endl;
                break;
                
            case Current:
                
                cout << "\n====================================" << endl;
                if (Widgets.isEmpty() && !(Orders.isEmpty()))
                    Orders.Print();
                else if (Orders.isEmpty() && !(Widgets.isEmpty()))
                    Widgets.Print();
                else
                    cout << "\nInventory is empty and no widgets have been backlogged." << endl;
                    cout << "\n====================================" << endl;
                break;
                
            case Quit:
                
                cout << "Program is now terminating..." << endl;
                break;
        
            default:
                cout << "\nERROR: Input must be between 1 and 4. Please try again." << endl;
                cin.clear();
                cin.ignore(200, '\n');
                break;
            }
        
    }while (userInput != Quit);

    system("pause");
    return 0;
}

void SellOrders(StackType & Widgets, StackType & Orders) {
    
    StackType *TempStack = new StackType;
    int quantityShipped = 0;
    double costToWarehouse = 0, costToCustomer = 0, totalProfit = 0;
    int i = 0;
    
    while (!(Widgets.isEmpty()) && !(Orders.isEmpty())) {
        
        if (Widgets.Peek()->GetQuantity() >= Orders.Peek()->GetQuantity()) {
            
            if (i == 0) {
                
                cout << "\nSHIPMENT DETAILS" << endl;
                cout << right << setw(15) << "QTY. SHIPPED" << setw(15) << "UNIT PRICE" << setw(20) << "COST TO WAREHOUSE" << setw(20) << "COST TO CUSTOMER" << endl;
            }
            
            quantityShipped += Orders.Peek()->GetQuantity();
            totalProfit = costToCustomer + 1.5 * Widgets.Peek()->GetCost() *    Orders.Peek()->GetQuantity() - (costToWarehouse + Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost());
            
            cout << right << setw(15) << Orders.Peek()->GetQuantity() << setw(15) <<    Widgets.Peek()->GetCost() << setw(20) << Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost() << setw(20) << Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost() * 1.5 << endl;
            
            cout << "\nSHIPMENT SUMMARY" << "\nQTY. ORDERED" << right << setw(15) << quantityShipped << endl
                 << "QTY. SHIPPED" << setw(15) << quantityShipped << endl
                 << "QTY. TO BE SHIPPED" << setw(9) << "0" << endl
                 << "COST TO WAREHOUSE" << setw(10) << costToWarehouse + Orders.Peek()->GetQuantity() * Widgets.Peek()->GetCost() << endl
                 << "COST TO CUSTOMER" << setw(11) << costToCustomer + 1.5 * Widgets.Peek()->GetCost() * Orders.Peek()->GetQuantity() << endl
                 << "TOTAL PROFIT" << setw(15) << totalProfit << endl;
            
            Widgets.Peek()->SetQuantity(Widgets.Peek()->GetQuantity() - Orders.Peek()->GetQuantity());
            Orders.Pop();
            
            if (Widgets.Peek()->GetQuantity() == 0)
                Widgets.Pop();
        }
        
        else {
            
            if (i == 0) {
                
                cout << "\nSHIPMENT DETAILS" << endl;
                cout << right << setw(15) << "QTY. SHIPPED" << setw(15) << "UNIT PRICE" << setw(20) << "COST TO WAREHOUSE" << setw(20) << "COST TO CUSTOMER" << endl;
                i++;
            }
            
            cout << right << setw(15) << Widgets.Peek()->GetQuantity() << setw(15) << Widgets.Peek()->GetCost() << setw(20) << Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost() << setw(20) << Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost() * 1.5 << endl;
            
            quantityShipped += Widgets.Peek()->GetQuantity();
            costToWarehouse += Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost();
            costToCustomer += Widgets.Peek()->GetQuantity() * Widgets.Peek()->GetCost() * 1.5;
            Orders.Peek()->SetQuantity(Orders.Peek()->GetQuantity() - Widgets.Peek()->GetQuantity());
            Widgets.Pop();
        }
    }
    
    if (Orders.isEmpty() && !(Widgets.isEmpty())) {
        
        int totalWidgets = 0;
        
        while (!(Widgets.isEmpty())) {
            
            totalWidgets += Widgets.Peek()->GetQuantity();
            TempStack->Push(Widgets.Peek()->GetQuantity(), Widgets.Peek()->GetCost());
            Widgets.Pop();
        }
        
        while (!(TempStack->isEmpty())) {
            
            Widgets.Push(TempStack->Peek()->GetQuantity(), TempStack->Peek()->GetCost());
            TempStack->Pop();
        }
        
        cout << "\nNo current orders. Widgets in stock: " << totalWidgets << "\n" << endl;
        delete TempStack;
    }
    
    else if (Widgets.isEmpty() && !(Orders.isEmpty())) {
        
        cout << "\nInventory is empty. " << Orders.Peek()->GetQuantity() << " orders of widgets will be backlogged.\n" << endl;
    }
}

/*

TEST DATA FOR LABS 5 & 6

1. Add 0 new widgets -> ERROR
2. Add -5 new widgets -> ERROR
3. Add ABC new widgets -> ERROR
4. Add 4 new widgets at a price of $-4.00 -> ERROR - > price of $4.00
5. Add 3 new widgets at a price of ABC -> ERROR -> $3.00
6. Print Current Inventory
7. Place an order for 2 widgets
8. Place an order for 3 widgets
9. Add 5 new widgets for $5.00
10. Place an order for 9 widgets -> 2 should be backlogged
11. Add 3 new widgets for $3.00
12. Print Current Inventory
13. Place an order for 5 widgets -> 4 should be backlogged
14. Print Current Inventory
15. Place an order for -5 widgets -> ERROR -> 4 widgets
16. Quit the Program
*/
 
 /*
WELCOME!

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

dhajsd

ERROR: Input must be between 1 and 4. Please try again.

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

23

ERROR: Input must be between 1 and 4. Please try again.

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 0

ERROR: Quantity must be a positive whole number. Please try again.

Please enter the amount of orders: -5

ERROR: Quantity must be a positive whole number. Please try again.

Please enter the amount of orders: hjsdj

ERROR: Quantity must be a positive whole number. Please try again.

Please enter the amount of orders: 4
Please enter the cost: $-4

ERROR: Cost must be a positive number. Please try again.

Please enter the cost: $4

No current orders. Widgets in stock: 4

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 3
Please enter the cost: $jdh

ERROR: Cost must be a positive number. Please try again.

Please enter the cost: $
ERROR: Cost must be a positive number. Please try again.

Please enter the cost: $3

No current orders. Widgets in stock: 7

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================
Widget Price: $3.00        In Stock: 3
Widget Price: $4.00        In Stock: 4

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1000
Please enter the amount of orders: 2

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              2           3.00                6.00                9.00

SHIPMENT SUMMARY
QTY. ORDERED              2
QTY. SHIPPED              2
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE      6.00
COST TO CUSTOMER       9.00
TOTAL PROFIT           3.00

No current orders. Widgets in stock: 5


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1001
Please enter the amount of orders: 3

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              1           3.00                3.00                4.50
              2           4.00                8.00               12.00

SHIPMENT SUMMARY
QTY. ORDERED              3
QTY. SHIPPED              3
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE     11.00
COST TO CUSTOMER      16.50
TOTAL PROFIT           5.50

No current orders. Widgets in stock: 2


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 5
Please enter the cost: $5

No current orders. Widgets in stock: 7

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1002
Please enter the amount of orders: 9

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              5           5.00               25.00               37.50
              2           4.00                8.00               12.00

Inventory is empty. 2 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 3
Please enter the cost: $3

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              2           3.00                6.00                9.00

SHIPMENT SUMMARY
QTY. ORDERED              2
QTY. SHIPPED              2
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE      6.00
COST TO CUSTOMER       9.00
TOTAL PROFIT           3.00

No current orders. Widgets in stock: 1

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================
Widget Price: $3.00        In Stock: 1

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1003
Please enter the amount of orders: 5

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              1           3.00                3.00                4.50

Inventory is empty. 4 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================
Number of widgets backlogged: 4

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1004
Please enter the amount of orders: -5

ERROR: Orders must be a positive whole number. Please try again.

Please enter the amount of orders: 4

Inventory is empty. 4 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 5
Please enter the cost: $1

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              4           1.00                4.00                6.00

SHIPMENT SUMMARY
QTY. ORDERED              4
QTY. SHIPPED              4
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE      4.00
COST TO CUSTOMER       6.00
TOTAL PROFIT           2.00

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              1           1.00                1.00                1.50

Inventory is empty. 3 orders of widgets will be backlogged.

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 4
Please enter the cost: $2

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              3           2.00                6.00                9.00

SHIPMENT SUMMARY
QTY. ORDERED              3
QTY. SHIPPED              3
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE      6.00
COST TO CUSTOMER       9.00
TOTAL PROFIT           3.00

No current orders. Widgets in stock: 1

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1005
Please enter the amount of orders: 1

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              1           2.00                2.00                3.00

SHIPMENT SUMMARY
QTY. ORDERED              1
QTY. SHIPPED              1
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE      2.00
COST TO CUSTOMER       3.00
TOTAL PROFIT           1.00

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================

Inventory is empty and no widgets have been backlogged.

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 5
Please enter the cost: $1

No current orders. Widgets in stock: 5

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 4
Please enter the cost: $2

No current orders. Widgets in stock: 9

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 3
Please enter the cost: $3

No current orders. Widgets in stock: 12

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================
Widget Price: $3.00        In Stock: 3
Widget Price: $2.00        In Stock: 4
Widget Price: $1.00        In Stock: 5

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1006
Please enter the amount of orders: 3

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              3           3.00                9.00               13.50

SHIPMENT SUMMARY
QTY. ORDERED              3
QTY. SHIPPED              3
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE      9.00
COST TO CUSTOMER      13.50
TOTAL PROFIT           4.50

No current orders. Widgets in stock: 9


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1007
Please enter the amount of orders: 7

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              4           2.00                8.00               12.00
              3           1.00                3.00                4.50

SHIPMENT SUMMARY
QTY. ORDERED              7
QTY. SHIPPED              7
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE     11.00
COST TO CUSTOMER      16.50
TOTAL PROFIT           5.50

No current orders. Widgets in stock: 2


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

32

ERROR: Input must be between 1 and 4. Please try again.

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1008
Please enter the amount of orders: 3

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              2           1.00                2.00                3.00

Inventory is empty. 1 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================
Number of widgets backlogged: 1

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1009
Please enter the amount of orders: 5

Inventory is empty. 5 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================
Number of widgets backlogged: 5
Number of widgets backlogged: 1

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 6
Please enter the cost: $2

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              5           2.00               10.00               15.00

SHIPMENT SUMMARY
QTY. ORDERED              5
QTY. SHIPPED              5
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE     10.00
COST TO CUSTOMER      15.00
TOTAL PROFIT           5.00

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              1           2.00                2.00                3.00

SHIPMENT SUMMARY
QTY. ORDERED              6
QTY. SHIPPED              6
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE      2.00
COST TO CUSTOMER       3.00
TOTAL PROFIT           1.00
====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================

Inventory is empty and no widgets have been backlogged.

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1010
Please enter the amount of orders: 4

Inventory is empty. 4 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1011
Please enter the amount of orders: 5

Inventory is empty. 5 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

2

====================================

ORDER #1012
Please enter the amount of orders: 6

Inventory is empty. 6 orders of widgets will be backlogged.


====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================
Number of widgets backlogged: 6
Number of widgets backlogged: 5
Number of widgets backlogged: 4

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

1

====================================

DELIVERY
Please enter the amount of orders: 15
Please enter the cost: $4

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              6           4.00               24.00               36.00

SHIPMENT SUMMARY
QTY. ORDERED              6
QTY. SHIPPED              6
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE     24.00
COST TO CUSTOMER      36.00
TOTAL PROFIT          12.00

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              5           4.00               20.00               30.00

SHIPMENT SUMMARY
QTY. ORDERED             11
QTY. SHIPPED             11
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE     20.00
COST TO CUSTOMER      30.00
TOTAL PROFIT          10.00

SHIPMENT DETAILS
   QTY. SHIPPED     UNIT PRICE   COST TO WAREHOUSE    COST TO CUSTOMER
              4           4.00               16.00               24.00

SHIPMENT SUMMARY
QTY. ORDERED             15
QTY. SHIPPED             15
QTY. TO BE SHIPPED        0
COST TO WAREHOUSE     16.00
COST TO CUSTOMER      24.00
TOTAL PROFIT           8.00
====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

3

====================================

Inventory is empty and no widgets have been backlogged.

====================================

Enter 1 to add new widgets to the inventory.
Enter 2 to place an order.
Enter 3 to print the current inventory.
Enter 4 to quit the program.

4
Program is now terminating...
sh: pause: command not found
Program ended with exit code: 0
*/
