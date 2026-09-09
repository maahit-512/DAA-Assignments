#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Movie
{
    string name;
    float rating;
    int releaseYear;
    long long views;
};

vector<Movie> movieList;

int partitionMovies(vector<Movie> &data, int low, int high, int option)
{
    Movie pivot = data[high];
    int index = low - 1;

    for (int j = low; j < high; j++)
    {
        bool check = false;

        if (option == 1)
            check = data[j].rating > pivot.rating;
        else if (option == 2)
            check = data[j].releaseYear > pivot.releaseYear;
        else if (option == 3)
            check = data[j].views > pivot.views;

        if (check)
        {
            index++;
            swap(data[index], data[j]);
        }
    }

    swap(data[index + 1], data[high]);

    return index + 1;
}

void quickSortMovies(vector<Movie> &data, int low, int high, int option)
{
    if (low < high)
    {
        int position = partitionMovies(data, low, high, option);

        quickSortMovies(data, low, position - 1, option);
        quickSortMovies(data, position + 1, high, option);
    }
}

void readMovies(string fileName)
{
    ifstream input(fileName);

    if (!input)
    {
        cout << "Error: Unable to open dataset!" << endl;
        return;
    }

    string line;
    getline(input, line);

    while (getline(input, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        Movie movie;
        string ratingValue;
        string yearValue;
        string popularityValue;

        getline(ss, movie.name, ',');
        getline(ss, ratingValue, ',');
        getline(ss, yearValue, ',');
        getline(ss, popularityValue, ',');

        if (movie.name.empty() || ratingValue.empty() ||
            yearValue.empty() || popularityValue.empty())
            continue;

        try
        {
            movie.rating = stof(ratingValue);
            movie.releaseYear = stoi(yearValue);
            movie.views = stoll(popularityValue);

            movieList.push_back(movie);
        }
        catch (...)
        {
        }
    }

    input.close();
}

void showMovies(int total)
{
    cout << left
         << setw(5) << "No."
         << setw(42) << "Movie"
         << setw(10) << "Rating"
         << setw(8) << "Year"
         << setw(15) << "Popularity"
         << endl;

    for (int i = 0; i < total && i < movieList.size(); i++)
    {
        cout << left
             << setw(5) << i + 1
             << setw(42) << movieList[i].name.substr(0, 40)
             << setw(10) << fixed << setprecision(1) << movieList[i].rating
             << setw(8) << movieList[i].releaseYear
             << setw(15) << movieList[i].views
             << endl;
    }
}

int main()
{
    readMovies("movies_clean.csv");

    if (movieList.empty())
    {
        cout << "No movie data available!" << endl;
        return 0;
    }

    int option;
    int number;

    cout << "       STREAMFLIX MOVIE RECOMMENDATION\n\n";

    cout << "Select Recommendation Option\n";
    cout << "1. IMDb Rating\n";
    cout << "2. Release Year\n";
    cout << "3. Popularity\n";

    cout << "\nEnter option: ";
    cin >> option;

    if (option < 1 || option > 3)
    {
        cout << "Invalid option!" << endl;
        return 0;
    }

    cout << "Enter number of movies to display: ";
    cin >> number;

    quickSortMovies(movieList, 0, movieList.size() - 1, option);

    cout << "\n";
    showMovies(number);

    return 0;
}