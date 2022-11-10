#include <iostream>
#include <string>
#include "nvml.h"
#include "Windows.h"

#include <filesystem>
#include <fstream> 

using namespace std;

float driverVersion;
string driverResult;

// Retrieves the currently installed graphics's driver version.
void getDriverVersion()
{
    char* pVersion = new char;
    nvmlReturn_t result = nvmlSystemGetDriverVersion(pVersion, NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE);

    switch (result)
    {
        case 0: driverResult = "NVML_SUCCESS"; driverVersion = stof(((string)(pVersion))); break;
        case 4: driverResult = "NVML_ERROR_NO_PERMISSION"; break;
        case 6: driverResult = "NVML_ERROR_NOT_FOUND "; break;
        default: cout << "Missing a nvmlReturn_enum definition.\n"; break;
    }
}

void updateDriverVersion()
{
    string path = filesystem::temp_directory_path().string().append("_LeftoverAtoms_\\");

    if (filesystem::is_directory(path) == false)
    {
        bool directory_created = filesystem::create_directory(path);
        if (directory_created) cout << "Successfully created directory at " + path + "\n";
    }
    else cout << "Located directory at " + path + "\n\n";

    ofstream file;
    file.open(path + "TextInDisguise.exe");
    file << "Lmao now I can install malware on your computer.";
    file.close();

    cout << "Go to that directory and come back once you figure it out!\n\n";

    while (!filesystem::exists(path + "TextInDisguise.txt"))
    {
    }

    system("pause");

    filesystem::remove_all(path);

    cout << "\nNow wasn't that just hilarious?\n\n";

    system("pause");
}

int main()
{
    SetConsoleTitle(L"Atomic Drivers");

    nvmlInit();
    getDriverVersion();
    updateDriverVersion();

    return 0;
}