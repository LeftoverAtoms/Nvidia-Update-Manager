#include <filesystem>
#include <iostream>
#include "nvml.h"
#include "Windows.h"

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

    //filesystem::remove_all(path);
}

int main()
{
    SetConsoleTitle(L"Nvidia Update Manager");

    nvmlInit();
    getDriverVersion();
    updateDriverVersion();

    return 0;
}