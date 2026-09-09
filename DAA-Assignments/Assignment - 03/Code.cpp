#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item
{
    string itemName;
    double weight;
    double value;
    bool canDivide;
    int priority;

    Item(string n, double w, double v, bool d, int p)
        : itemName(n), weight(w), value(v), canDivide(d), priority(p) {}

    double ratio() const
    {
        return value / weight;
    }
};

bool sortItems(const Item &a, const Item &b)
{
    if (a.priority == b.priority)
        return a.ratio() > b.ratio();

    return a.priority < b.priority;
}

double fillBoat(vector<Item> &items, double capacity, double &usedWeight)
{
    sort(items.begin(), items.end(), sortItems);

    cout << "\nSorted Relief Items:\n";

    cout << left
         << setw(20) << "Item"
         << setw(10) << "Weight"
         << setw(10) << "Value"
         << setw(10) << "Priority"
         << setw(15) << "Value/Weight"
         << setw(15) << "Type" << endl;

    for (const auto &item : items)
    {
        cout << left
             << setw(20) << item.itemName
             << setw(10) << item.weight
             << setw(10) << item.value
             << setw(10) << item.priority
             << setw(15) << fixed << setprecision(2) << item.ratio()
             << setw(15) << (item.canDivide ? "Divisible" : "Indivisible")
             << endl;
    }

    double totalValue = 0;
    usedWeight = 0;

    cout << "\nSelected Items:\n";

    for (const auto &item : items)
    {
        if (capacity <= 0)
            break;

        if (item.canDivide)
        {
            double weightTaken = min(item.weight, capacity);
            double valueTaken = item.ratio() * weightTaken;

            totalValue += valueTaken;
            capacity -= weightTaken;
            usedWeight += weightTaken;

            cout << " - " << item.itemName
                 << ": " << weightTaken << " kg"
                 << ", Value = " << valueTaken
                 << ", Priority = " << item.priority
                 << ", Type = Divisible" << endl;
        }
        else
        {
            if (item.weight <= capacity)
            {
                totalValue += item.value;
                capacity -= item.weight;
                usedWeight += item.weight;

                cout << " - " << item.itemName
                     << ": " << item.weight << " kg"
                     << ", Value = " << item.value
                     << ", Priority = " << item.priority
                     << ", Type = Indivisible" << endl;
            }
        }
    }

    return totalValue;
}

int main()
{
    int numberOfItems;

    cout << "Enter number of relief items: ";
    cin >> numberOfItems;

    vector<Item> items;

    for (int i = 0; i < numberOfItems; i++)
    {
        string name;
        double weight, value;
        int divideOption, priority;

        cout << "\nEnter details for Item " << i + 1 << ":\n";

        cout << "Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Weight (kg): ";
        cin >> weight;

        cout << "Utility Value: ";
        cin >> value;

        cout << "Is it divisible? (1 = Yes, 0 = No): ";
        cin >> divideOption;

        cout << "Priority (1 = High, 2 = Medium, 3 = Low): ";
        cin >> priority;

        items.emplace_back(
            name,
            weight,
            value,
            divideOption == 1,
            priority
        );
    }

    double boatCapacity;

    cout << "\nEnter maximum capacity of the boat (kg): ";
    cin >> boatCapacity;

    double usedWeight;

    double totalValue = fillBoat(
        items,
        boatCapacity,
        usedWeight
    );

    cout << "\n===== Final Report =====\n";

    cout << "Total weight carried: "
         << fixed << setprecision(2)
         << usedWeight << " kg" << endl;

    cout << "Total utility value: "
         << fixed << setprecision(2)
         << totalValue << " units" << endl;

    return 0;
}