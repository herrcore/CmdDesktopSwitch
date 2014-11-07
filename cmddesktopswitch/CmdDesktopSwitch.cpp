//////////////////////////////////////////////////////////////////////////////////
//
// CmdDesktopSwitch.cpp
//
//


#include "windows.h"
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> strDesktop;

//Stole this from experts exchange http://www.experts-exchange.com/Programming/Languages/CPP/Q_28266184.html
std::string TstrToStdStr(LPCTSTR psz)
{
    std::string s;
    if (psz == NULL) return s;
    if (sizeof(TCHAR) == sizeof(wchar_t))
    {
          std::wstring ws = psz;
          int wlen = (int)ws.length();
          // get needed space
          int slen  = (int)wcstombs(NULL, &ws[0], 2*wlen);
           
          if (slen > 0) 
          {
              s.resize(slen, '\0'); 
              wcstombs(&s[0], &ws[0], slen);
          }
    }
	//if it's ascii we are doing something wrong
    return s;
}

//Copied from stack overflow (Toran Billups) http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void WINAPI EnumDesktopCallBack(LPTSTR lpszDesktop,LPARAM lParam)
{
	strDesktop.push_back(TstrToStdStr(lpszDesktop));
}

int _tmain(int argc, _TCHAR* argv[])
{

	HWINSTA winsta = GetProcessWindowStation();
    EnumDesktops(winsta,(DESKTOPENUMPROCW)EnumDesktopCallBack,NULL);
    CloseWindowStation(winsta);

	std::cout << "Selection #\tDesktop Name" << std::endl;
	std::cout << "-----------\t------------" << std::endl;
	for(int count=0;count < strDesktop.size(); count++)
	{
		std::cout << count << "\t\t" <<strDesktop.at(count) << std::endl;
	}
	std::cout << "-----------\t------------" << std::endl;
	std::cout << "Enter selection # to view desktop: ";
	int selection;
	std::cin >> selection;

	if(0<= selection && selection < strDesktop.size())
	{
		std::cout << "Switching desktops..." << std::endl;
	}
	else
	{
		std::cout << "Error: Invalid selection." << std::endl;
		return -1;
	}

	std::wstring wdesktopName = s2ws(strDesktop.at(selection));

	HDESK hdeskOriginalThread = GetThreadDesktop(GetCurrentThreadId());
	HDESK hdeskOriginalInput = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);

	HDESK hdeskNewDesktop = CreateDesktop(wdesktopName.c_str(), NULL, NULL, 0, GENERIC_ALL, NULL);
	SetThreadDesktop(hdeskNewDesktop);
	SwitchDesktop(hdeskNewDesktop);
	
	
	MessageBox(NULL, TEXT("Switch back to default desktop?"), TEXT("Desktop Switch"), MB_OK);
	SwitchDesktop(hdeskOriginalInput);
	SetThreadDesktop(hdeskOriginalThread);
	CloseDesktop(hdeskNewDesktop);
	return 0;
}

