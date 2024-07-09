#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <exception>

using namespace std;

class Location
{
public:
    string name;
    double latitude;
    double longitude;

    Location(const string &name, double latitude, double longitude)
        : name(name), latitude(latitude), longitude(longitude) {}
};

class LocationManager
{
private:
    vector<Location> locations;

public:
    void addLocation(const string &name, double latitude, double longitude)
    {
        locations.push_back(Location(name, latitude, longitude));
    }

    void removeLocation(const string &name)
    {
        locations.erase(remove_if(locations.begin(), locations.end(),
                                  [&name](const Location &loc)
                                  { return loc.name == name; }),
                        locations.end());
    }

    void listLocations() const
    {
        for (const auto &loc : locations)
        {
            cout << "Name: " << loc.name << ", Latitude: " << loc.latitude << ", Longitude: " << loc.longitude << endl;
        }
    }
};

class WeatherVariable
{
public:
    string variableName;
    double value;

    WeatherVariable(const string &variableName, double value)
        : variableName(variableName), value(value) {}
};

class WeatherVariableManager
{
private:
    vector<WeatherVariable> variables;

public:
    void addVariable(const string &variableName, double value)
    {
        variables.push_back(WeatherVariable(variableName, value));
    }

    void removeVariable(const string &variableName)
    {
        variables.erase(remove_if(variables.begin(), variables.end(),
                                  [&variableName](const WeatherVariable &var)
                                  { return var.variableName == variableName; }),
                        variables.end());
    }

    void listVariables() const
    {
        for (const auto &var : variables)
        {
            cout << "Variable: " << var.variableName << ", Value: " << var.value << endl;
        }
    }
};

class WeatherSystem
{
protected:
    string apiKey;
    string baseUrl;

public:
    WeatherSystem(const string &apiKey, const string &baseUrl)
        : apiKey(apiKey), baseUrl(baseUrl) {}

    virtual string fetchData(const string &endpoint, const map<string, string> &params)
    {
        return "API response"; 
    }

    virtual void handleApiResponse(const string &response) = 0; // Pure virtual function
};

class WeatherForecastingSystem : public WeatherSystem
{
public:
    WeatherForecastingSystem(const string &apiKey, const string &baseUrl)
        : WeatherSystem(apiKey, baseUrl) {}

    string fetchForecast(const Location &location)
    {
        return "Forecast data"; 
    }

    void handleApiResponse(const string &response) override
    {
        cout << response << endl;
    }
};

class HistoricalWeatherSystem : public WeatherSystem
{
public:
    HistoricalWeatherSystem(const string &apiKey, const string &baseUrl)
        : WeatherSystem(apiKey, baseUrl) {}

    string fetchHistoricalData(const Location &location, const string &startDate, const string &endDate)
    {
        return "Historical data"; 
    }

    void handleApiResponse(const string &response) override
    {
        cout << response << endl;
    }
};

class DataExporter
{
public:
    static void exportToCSV(const string &data, const string &filename)
    {
        ofstream file(filename);
        file << data;
        file.close();
    }

    static void exportToJSON(const string &data, const string &filename)
    {
        ofstream file(filename);
        file << data;
        file.close();
    }
};

class CloudStorageSystem
{
private:
    string cloudServiceCredentials;

public:
    CloudStorageSystem(const string &cloudServiceCredentials)
        : cloudServiceCredentials(cloudServiceCredentials) {}

    // void saveToCloud(const string &data)
    // {
    //     // Implement cloud saving functionality
    // }

    string retrieveFromCloud(const string &filters)
    {
        return "Cloud data"; 
    }

    void saveLocally(const string &data)
    {
        ofstream file("local_data.txt");
        file << data;
        file.close();
    }

    string retrieveLocally(const string &filters)
    {
        ifstream file("local_data.txt");
        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        return data;
    }
};

class APIClient
{
public:
    string fetchData(const string &endpoint, const map<string, string> &params)
    {
        return "API response"; 
    }

};

class UserInterface
{
public:
    string getUserInput()
    {
        string input;
        getline(cin, input);
        return input;
    }

    bool validateInput(const string &input)
    {
        return true; 
    }

    void handleExceptions(const exception &exception)
    {
        cerr << "Error: " << exception.what() << endl;
    }
};

int main()
{
    LocationManager locationManager;
    WeatherVariableManager weatherVariableManager;
    WeatherForecastingSystem weatherForecastingSystem("api_key", "https://api.weather.com");
    HistoricalWeatherSystem historicalWeatherSystem("api_key", "https://api.weather.com");
    UserInterface ui;

    while (true)
    {
        cout << "Menu:\n";
        cout << "1. Add Location\n";
        cout << "2. Remove Location\n";
        cout << "3. List Locations\n";
        cout << "4. Add Weather Variable\n";
        cout << "5. Remove Weather Variable\n";
        cout << "6. List Weather Variables\n";
        cout << "7. Fetch Weather Forecast\n";
        cout << "8. Fetch Historical Weather Data\n";
        cout << "9. Export Data to CSV\n";
        cout << "10. Export Data to JSON\n";
        cout << "11. Exit\n";
        cout << "Enter choice: ";
        string choice = ui.getUserInput();

        try
        {
            if (choice == "1")
            {
                cout << "Enter location name: ";
                string name = ui.getUserInput();
                cout << "Enter latitude: ";
                double latitude;
                cin >> latitude;
                cout << "Enter longitude: ";
                double longitude;
                cin >> longitude;
                cin.ignore();
                locationManager.addLocation(name, latitude, longitude);
            }
            else if (choice == "2")
            {
                cout << "Enter location name to remove: ";
                string name = ui.getUserInput();
                locationManager.removeLocation(name);
            }
            else if (choice == "3")
            {
                locationManager.listLocations();
            }
            else if (choice == "4")
            {
                cout << "Enter weather variable name: ";
                string variableName = ui.getUserInput();
                cout << "Enter value: ";
                double value;
                cin >> value;
                cin.ignore();
                weatherVariableManager.addVariable(variableName, value);
            }
            else if (choice == "5")
            {
                cout << "Enter weather variable name to remove: ";
                string variableName = ui.getUserInput();
                weatherVariableManager.removeVariable(variableName);
            }
            else if (choice == "6")
            {
                weatherVariableManager.listVariables();
            }
            else if (choice == "7")
            {
                cout << "Enter location name for forecast: ";
                string locationName = ui.getUserInput();
                Location location(locationName, 0.0, 0.0);
                string forecast = weatherForecastingSystem.fetchForecast(location);
                weatherForecastingSystem.handleApiResponse(forecast);
            }
            else if (choice == "8")
            {
                cout << "Enter location name for historical data: ";
                string locationName = ui.getUserInput();
                cout << "Enter start date (YYYY-MM-DD): ";
                string startDate = ui.getUserInput();
                cout << "Enter end date (YYYY-MM-DD): ";
                string endDate = ui.getUserInput();
                Location location(locationName, 0.0, 0.0);
                string historicalData = historicalWeatherSystem.fetchHistoricalData(location, startDate, endDate);
                historicalWeatherSystem.handleApiResponse(historicalData);
            }
            else if (choice == "9")
            {
                cout << "Enter data to export: ";
                string data = ui.getUserInput();
                cout << "Enter filename: ";
                string filename = ui.getUserInput();
                DataExporter::exportToCSV(data, filename);
            }
            else if (choice == "10")
            {
                cout << "Enter data to export: ";
                string data = ui.getUserInput();
                cout << "Enter filename: ";
                string filename = ui.getUserInput();
                DataExporter::exportToJSON(data, filename);
            }
            else if (choice == "11")
            {
                break;
            }
            else
            {
                cout << "Invalid choice, please try again." << endl;
            }
        }
        catch (const exception &ex)
        {
            ui.handleExceptions(ex);
        }
    }

    return 0;
}