//-----------------------------------------------------------------------------
//
// file emacsrun.cpp
//
// compiling with MinGW-w64:
// c++ emacsrun.cpp --static -std=c++17 -mwindows -Wl,-subsystem,windows -o emacsrun.exe
//
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>

#ifdef _WIN32_WINNT
#include <windows.h>
#define ERR_MSG err_mswin
#define SYSTEM system_mswin
#else
#define ERR_MSG err_linux
#define SYSTEM system_linux
#endif

//## Message from MS-Windows
//
void err_mswin(const char *msg)
{
  MessageBox (NULL, msg, "Error", MB_ICONSTOP);
  return;
}

//## Message from Linux
//
void err_linux(const char *msg)
{
  std::cout << "Error: " << msg << "\n";
  return;
}

//## Exec subprocess on Linux system
//
int system_linux(const std::string& cmd)
{
  std::string app = cmd + " &";
  return std::system(app.data());
}

//## Exec subprocess on MS-Windows system
//
int system_mswin(const std::string& cmd)
{
  STARTUPINFO si;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  si.wShowWindow = SW_HIDE;

  PROCESS_INFORMATION pi;
  ZeroMemory(&pi, sizeof(pi));

  if (!CreateProcess(
    NULL,                          // the path
    const_cast<char*>(cmd.data()), // exec command
    NULL,                          // Process handle not inheritable
    NULL,                          // Thread handle not inheritable
    FALSE,                         // Set handle inheritance to FALSE
    CREATE_UNICODE_ENVIRONMENT,    // creation flags
    NULL,                          // Use parent's environment block
    NULL,                          // Use parent's starting directory
    &si,                           // Pointer to STARTUPINFO structure
    &pi                            // Pointer to PROCESS_INFORMATION structure
  ))
  {
    std::string msg = "Could not exec:\n\n" + cmd;
    err_mswin(msg.data());
    return 0;
  }
  return 1;
}

//## Main here
//
int main(int argc, char* argv[])
{
  std::string ini_fname = argv[0];
  ini_fname += ".ini";

  std::string cmd {};

  std::ifstream myfile (ini_fname);
  if (myfile.is_open())
  {
    // Read the first line from the ini-file
    std::getline (myfile, cmd);
    myfile.close();
  } else {
    std::string msg = "Could not open INI file:\n\n" + ini_fname;
    ERR_MSG(msg.data());
    return EXIT_FAILURE;
  }

  // Append passed parameters (keys) for the Application
  for(auto i = 1; i < argc; ++i)
  {
    cmd += " ";
    cmd += argv[i];
  }

  if(0 == SYSTEM(cmd)) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
