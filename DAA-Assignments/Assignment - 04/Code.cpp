#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void findShortestPath(
    int start,
    const vector<vector<pair<int, int>>> &roads,
    vector<int> &distance,
    vector<int> &previous)
{
    int vertices = roads.size();

    distance.assign(vertices, INT_MAX);
    previous.assign(vertices, -1);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int currentDistance = pq.top().first;
        int currentNode = pq.top().second;

        pq.pop();

        if (currentDistance > distance[currentNode])
            continue;

        for (auto road : roads[currentNode])
        {
            int nextNode = road.first;
            int travelTime = road.second;

            if (distance[nextNode] >
                distance[currentNode] + travelTime)
            {
                distance[nextNode] =
                    distance[currentNode] + travelTime;

                previous[nextNode] = currentNode;

                pq.push({
                    distance[nextNode],
                    nextNode
                });
            }
        }
    }
}

void showPath(
    int start,
    int destination,
    const vector<int> &previous)
{
    vector<int> route;
    int node = destination;

    while (node != -1)
    {
        route.push_back(node);
        node = previous[node];
    }

    reverse(route.begin(), route.end());

    if (route.empty() || route[0] != start)
    {
        cout << "No route available.\n";
        return;
    }

    cout << "Optimal Route: ";

    for (int i = 0; i < route.size(); i++)
    {
        cout << route[i];

        if (i < route.size() - 1)
            cout << " -> ";
    }

    cout << endl;
}

void changeTraffic(
    vector<vector<pair<int, int>>> &roads,
    int start,
    int end,
    int newTime)
{
    bool roadFound = false;

    for (auto &road : roads[start])
    {
        if (road.first == end)
        {
            road.second = newTime;
            roadFound = true;
        }
    }

    for (auto &road : roads[end])
    {
        if (road.first == start)
            road.second = newTime;
    }

    if (roadFound)
        cout << "Traffic updated successfully.\n";
    else
        cout << "Road not found!\n";
}

int main()
{
    int vertices, roadsCount;

    cout << " SMART TRAFFIC MANAGEMENT SYSTEM\n";
    cout << " Emergency Vehicle Route Optimization\n\n";

    cout << "Enter number of intersections: ";
    cin >> vertices;

    cout << "Enter number of roads: ";
    cin >> roadsCount;

    vector<vector<pair<int, int>>> roads(vertices);

    cout << "\nEnter road details:\n";
    cout << "Format: Start_Node End_Node Travel_Time\n\n";

    for (int i = 0; i < roadsCount; i++)
    {
        int start, end, time;

        cout << "Road " << i + 1 << ": ";
        cin >> start >> end >> time;

        roads[start].push_back({end, time});
        roads[end].push_back({start, time});
    }

    int ambulanceStart;

    cout << "\nEnter ambulance starting location: ";
    cin >> ambulanceStart;

    int hospitalCount;

    cout << "Enter number of hospitals: ";
    cin >> hospitalCount;

    vector<int> hospitals(hospitalCount);

    cout << "Enter hospital node numbers:\n";

    for (int i = 0; i < hospitalCount; i++)
        cin >> hospitals[i];

    vector<int> distance;
    vector<int> previous;

    findShortestPath(
        ambulanceStart,
        roads,
        distance,
        previous
    );

    int bestHospital = -1;
    int shortestTime = INT_MAX;

    cout << "\n INITIAL HOSPITAL DISTANCES\n\n";

    for (int hospital : hospitals)
    {
        if (distance[hospital] == INT_MAX)
        {
            cout << "Hospital " << hospital
                 << " : Not Reachable\n";
        }
        else
        {
            cout << "Hospital " << hospital
                 << " : " << distance[hospital]
                 << " minutes\n";

            if (distance[hospital] < shortestTime)
            {
                shortestTime = distance[hospital];
                bestHospital = hospital;
            }
        }
    }

    if (bestHospital == -1)
    {
        cout << "\nNo hospital is reachable.\n";
        return 0;
    }

    cout << "\n BEST HOSPITAL\n\n";

    cout << "Nearest Hospital : "
         << bestHospital << endl;

    cout << "Minimum Travel Time : "
         << shortestTime << " minutes\n";

    showPath(
        ambulanceStart,
        bestHospital,
        previous
    );

    char answer;

    cout << "\nDo you want to update traffic conditions? (y/n): ";
    cin >> answer;

    while (answer == 'y' || answer == 'Y')
    {
        int start, end, newTime;

        cout << "\nEnter road whose traffic changed:\n";

        cout << "Start node: ";
        cin >> start;

        cout << "End node: ";
        cin >> end;

        cout << "New travel time: ";
        cin >> newTime;

        changeTraffic(
            roads,
            start,
            end,
            newTime
        );

        findShortestPath(
            ambulanceStart,
            roads,
            distance,
            previous
        );

        bestHospital = -1;
        shortestTime = INT_MAX;

        cout << "\n UPDATED HOSPITAL DISTANCES\n\n";

        for (int hospital : hospitals)
        {
            if (distance[hospital] == INT_MAX)
            {
                cout << "Hospital " << hospital
                     << " : Not Reachable\n";
            }
            else
            {
                cout << "Hospital " << hospital
                     << " : " << distance[hospital]
                     << " minutes\n";

                if (distance[hospital] < shortestTime)
                {
                    shortestTime = distance[hospital];
                    bestHospital = hospital;
                }
            }
        }

        cout << "\n UPDATED OPTIMAL ROUTE\n\n";

        if (bestHospital != -1)
        {
            cout << "Nearest Hospital : "
                 << bestHospital << endl;

            cout << "Minimum Travel Time : "
                 << shortestTime
                 << " minutes\n";

            showPath(
                ambulanceStart,
                bestHospital,
                previous
            );
        }
        else
        {
            cout << "No hospital is reachable.\n";
        }

        cout << "\nDo you want to update traffic again? (y/n): ";
        cin >> answer;
    }

    cout << "\n SYSTEM FINISHED\n";

    return 0;
}