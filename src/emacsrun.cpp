//-----------------------------------------------------------------------------
//
// file emacsrun.cpp
//
// Testing with MinGW-w64
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
/*
#include <windows.h>

int system-mswin( const std::string& cmd ){

  STARTUPINFO si;
  SecureZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(si);

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
	)) return 0;
	
	return 1;
}
*/

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

	cmd += " &";
	std::system(cmd.data());
	//system_posix(cmd);
	
  return EXIT_SUCCESS;
}

