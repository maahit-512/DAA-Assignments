#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order
{
    string id;
    string customer;
    string timestamp;
};

void mergeOrders(vector<Order> &orders, int start, int mid, int end)
{
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    vector<Order> leftPart(leftSize);
    vector<Order> rightPart(rightSize);

    for (int i = 0; i < leftSize; i++)
        leftPart[i] = orders[start + i];

    for (int i = 0; i < rightSize; i++)
        rightPart[i] = orders[mid + 1 + i];

    int i = 0, j = 0, k = start;

    while (i < leftSize && j < rightSize)
    {
        if (leftPart[i].timestamp <= rightPart[j].timestamp)
            orders[k++] = leftPart[i++];
        else
            orders[k++] = rightPart[j++];
    }

    while (i < leftSize)
        orders[k++] = leftPart[i++];

    while (j < rightSize)
        orders[k++] = rightPart[j++];
}

void sortOrders(vector<Order> &orders, int start, int end)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;

    sortOrders(orders, start, mid);
    sortOrders(orders, mid + 1, end);

    mergeOrders(orders, start, mid, end);
}

int main()
{
    vector<Order> orders;

    ifstream inputFile("olist_orders_dataset.csv");

    if (!inputFile)
    {
        cout << "Unable to open file." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);

    while (getline(inputFile, line))
    {
        stringstream data(line);

        Order order;
        string status;

        getline(data, order.id, ',');
        getline(data, order.customer, ',');
        getline(data, status, ',');
        getline(data, order.timestamp, ',');

        if (!order.timestamp.empty())
            orders.push_back(order);
    }

    inputFile.close();

    cout << "Number of Orders: " << orders.size() << endl;

    if (!orders.empty())
        sortOrders(orders, 0, orders.size() - 1);

    cout << "\nFirst 20 Orders After Sorting:\n\n";

    int count = min(20, (int)orders.size());

    for (int i = 0; i < count; i++)
    {
        cout << orders[i].id << "    "
             << orders[i].customer << "    "
             << orders[i].timestamp << endl;
    }

    return 0;
}