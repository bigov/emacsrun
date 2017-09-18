//-----------------------------------------------------------------------------
//
// file emacsrun.cpp
//
// Testing with MinGW-w64
//
//-----------------------------------------------------------------------------

#include <windows.h>
#include <iostream>
#include <fstream>

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
  } 
  else return EXIT_FAILURE;

  // Append passed parameters (keys) for the Application
  for(auto i = 1; i < argc; ++i)
  {
    cmd += " ";
    cmd += argv[i];
  }

  PROCESS_INFORMATION pi;
  STARTUPINFO si;
  SecureZeroMemory(&si, sizeof(STARTUPINFO));

  if (!CreateProcess( NULL, const_cast<char*>(cmd.data()), NULL, NULL, FALSE,
    CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &si, &pi )) return EXIT_FAILURE;
	
  return EXIT_SUCCESS;
}
