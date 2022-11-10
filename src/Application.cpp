#include <filesystem>
#include <iostream>
#include "nvml.h"
#include <Urlmon.h>
#include <Windows.h>

using namespace std;

float driverVersion;
string driverResult;
LPCWSTR downloadDir;

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
    //filesystem::remove_all(path);

    URLDownloadToFile(NULL, L"https://www.dropbox.com/s/456cod6dkrmgyy9/ep.gif?dl=0", downloadDir, 0, NULL);
}

void getDownloadDirectory()
{
    //downloadDir = wstring(filesystem::temp_directory_path());
    string dir = filesystem::temp_directory_path().string().append("_LeftoverAtoms_\\");

    if (filesystem::is_directory(dir) == false)
    {
        bool directory_created = filesystem::create_directory(dir);
        if (directory_created) cout << "Successfully created directory at " + dir + "\n";
    }
    else cout << "Successfully located directory at " + dir + "\n\n";

    downloadDir = (LPCWSTR)dir.c_str();

    updateDriverVersion();
}

int main()
{
    SetConsoleTitle(L"Nvidia Update Manager");

    nvmlInit();
    getDriverVersion();
    getDownloadDirectory();

    return 0;
}