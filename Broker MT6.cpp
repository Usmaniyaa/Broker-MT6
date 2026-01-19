#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Trade {
    string type;
    string symbol;
    double price;
    int quantity;
};

class BrokerMT6 {
private:
    double balance;
    vector<Trade> tradeHistory;

public:
    BrokerMT6(double initialBalance) {
        balance = initialBalance;
    }

    void showBalance() {
        cout << fixed << setprecision(2);
        cout << "\nCurrent Balance: $" << balance << "\n";
    }

    void buy(string symbol, double price, int quantity) {
        double cost = price * quantity;
        if(cost > balance) {
            cout << "Insufficient balance to buy " << quantity << " of " << symbol << "\n";
            return;
        }
        balance -= cost;
        tradeHistory.push_back({"Buy", symbol, price, quantity});
        cout << "Bought " << quantity << " of " << symbol << " at $" << price << " each.\n";
    }

    void sell(string symbol, double price, int quantity) {
        double revenue = price * quantity;
        balance += revenue;
        tradeHistory.push_back({"Sell", symbol, price, quantity});
        cout << "Sold " << quantity << " of " << symbol << " at $" << price << " each.\n";
    }

    void showTradeHistory() {
        if(tradeHistory.empty()) {
            cout << "No trades yet.\n";
            return;
        }
        cout << "\n--- Trade History ---\n";
        for(size_t i = 0; i < tradeHistory.size(); i++) {
            Trade t = tradeHistory[i];
            cout << i+1 << ". " << t.type << " " << t.quantity << " of " << t.symbol
                 << " at $" << t.price << " each\n";
        }
    }
};

int main() {
    BrokerMT6 account(10000.0);
    int choice;
    string symbol;
    double price;
    int quantity;

    do {
        cout << "\n--- Broker MT6 Trading System ---\n";
        cout << "1. Show Balance\n";
        cout << "2. Buy\n";
        cout << "3. Sell\n";
        cout << "4. Trade History\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                account.showBalance();
                break;
            case 2:
                cin >> symbol >> price >> quantity;
                account.buy(symbol, price, quantity);
                break;
            case 3:
                cin >> symbol >> price >> quantity;
                account.sell(symbol, price, quantity);
                break;
            case 4:
                account.showTradeHistory();
                break;
            case 5:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while(choice != 5);

    return 0;
}
