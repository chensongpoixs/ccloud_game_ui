﻿/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
************************************************************************************************/
#include "crender_server_mgr.h"
#include "cutil.h"
//#include "pch.h"
//
#include <Windows.h>
#include <tchar.h>
#include <ShlObj_core.h>
#include <Shlwapi.h>
#include <Windows.h>
#pragma comment( lib, "ShLwApi.Lib" ) //PathRemoveFileSpecA
#include <windows.h>
#include "cinjector_util.h"
#include "ccfg.h"
#define ARRAY_SIZE (2048)
namespace chen {
	crender_server_mgr::~crender_server_mgr()
	{
	}

	bool crender_server_mgr::update()
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, false, m_app_info.dwProcessId);
		DWORD exitCode;
		BOOL result = GetExitCodeProcess(hProcess, &exitCode);
		if (result && exitCode == STILL_ACTIVE)
		{
			// 进程正在运行中
			m_process_type = EProcessActive;
		}
		else if (::time(NULL) - m_timestamp < 3)
		{
			m_process_type = EProcessStart;
		}
		else
		{
			m_process_type = EProcessNone;
			// 进程已经结束
		}

		CloseHandle(hProcess);

		//其中，PROCESS_ID为要获取状态的进程ID。通过调用OpenProcess函数打开进程句柄，然后调用GetExitCodeProcess函数获取进程退出码（即状态），如果返回值为TRUE且状态为STILL_ACTIVE，则进程正在运行中；否则进程已经结束。最后需要关闭进程句柄
		return false;
	}

	bool crender_server_mgr::startup(const std::string & render_wan_port, const std::string &media_wan_ip, const std::string & media_wan_port)
	{
		std::string app_path_name = "./RenderServer/render_server.exe";
		//std::string app_path_name = "D:/Work/UE/builder_V4.2_Release_76_202304042038/builderexe/Rte.exe";
		
		FILE * out_file_ptr = ::fopen("./render_server.cfg", "wb+");
		CString str;

		std::string pp = CT2A(str.GetString());
		fprintf(out_file_ptr, "# ^_^ ## \n wan_port = %s\n", render_wan_port.c_str());
		fprintf(out_file_ptr, "gm_cmd_port = %u\n", g_cfg.get_uint32(ECI_GmCmdPort));
		fprintf(out_file_ptr, "global_db_host = %s\n", g_cfg.get_string(ECI_GlobalDbHost).c_str());
		fprintf(out_file_ptr, "global_db_user = %s\n", g_cfg.get_string(ECI_GlobalDbUsername).c_str());
		fprintf(out_file_ptr, "global_db_psd = %s\n", g_cfg.get_string(ECI_GlobalDbPassword).c_str());
		fprintf(out_file_ptr, "global_db_name = %s\n", g_cfg.get_string(ECI_GlobalDbName).c_str());
		fprintf(out_file_ptr, "global_db_port = %s\n", g_cfg.get_string(ECI_GlobalDbPort));

		fprintf(out_file_ptr, "rtc_ip = %s\n", media_wan_ip.c_str());
		fprintf(out_file_ptr, "rtc_port = %s\n", media_wan_port.c_str());
		fflush(out_file_ptr);
		fclose(out_file_ptr);
		out_file_ptr = NULL;
		std::string app_path_param = " ../../render_server.cfg  ../../log";
		std::string app_work_path = get_workdir(app_path_name);
		/*{
			STARTUPINFO si;
			memset(&si, 0, sizeof(si));
			si.cb = sizeof(si);

			PROCESS_INFORMATION pi;
			memset(&pi, 0, sizeof(pi));

			CString commandLine     (app_path_name.c_str()) ;

			BOOL ret = CreateProcess(NULL, commandLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
			if (ret) {
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
		}
		return true;*/
		TCHAR szAppName[ARRAY_SIZE] = { 0 };
		//Get the application full path, so that it can be launch into the switching desktop.
		//GetModuleFileName(GetModuleHandle(NULL), szAppName, ARRAY_SIZE - 1);
		/*ACCESS_MASK desired_access = DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |
			DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |
			DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |
			DESKTOP_SWITCHDESKTOP | GENERIC_WRITE;

*/
//system(app_path_name.c_str());
		CString commandLine(app_path_name.c_str());
		CString path_work(app_path_param.c_str());
		//ShellExecute(NULL, _T("open"), LPCWSTR(app_path_name.c_str()), NULL, NULL, SW_SHOW);
		STARTUPINFO si;
		memset(&si, 0, sizeof(si));
		/*si.cb = sizeof(si);
		si.wShowWindow = SW_HIDE;*/
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		//si.wShowWindow = SW_MINIMIZE;
		si.lpReserved = NULL;
		si.cbReserved2 = 0;
		si.lpReserved2 = NULL;
		GetStartupInfo(&si);

		bool ret = ::CreateProcess(NULL, commandLine.GetBuffer(), NULL, NULL, FALSE, CREATE_NO_WINDOW/*CREATE_NO_WINDOW*/, NULL, NULL, &si, &m_app_info);
		if (ret)
		{
			// 关闭子进程的主线程句柄        
			//WaitForSingleObject(pi.hProcess, INFINITE);
			//// 等待子进程的退出                            
			//GetExitCodeProcess(&pi.hProcess, &dwExitCode);
			//// 获取子进程的退出码
			//CloseHandle(pi.hThread);
			//CloseHandle(pi.hProcess);
				// TODO@chensong 2022-07-27  创建线程关闭  -----后期优化 
			CloseHandle(m_app_info.hThread);
			//m_app_info.hThread = NULL;
			CloseHandle(m_app_info.hProcess);
			//m_app_info.hProcess = NULL;
			m_timestamp = ::time(NULL);
			//process_info.hProcess = virtual_desktop.dwProcessId;
			//process_info.hThread = virtual_desktop.dwThreadId;
			return true;
		}
		return false;
		return true;
		return false;
	}

	void crender_server_mgr::destroy()
	{
		close_app();
	}

	void crender_server_mgr::close_app()
	{
		m_timestamp = 0;

		if (m_app_info.dwProcessId != 0)
		{
			//TODO@chensong 20220309  杀死进程的  -> 
			HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS/*PROCESS_TERMINATE*/, FALSE, m_app_info.dwProcessId);
			if (hProcess)
			{



				WCHAR rtc_load_path[4096] = L"";
				GetCurrentDirectoryW(4096, rtc_load_path);
				wcscat_s(rtc_load_path, L"\\Tools\\");
				wcscat_s(rtc_load_path, L"SendSignal.dll");
				if (GetFileAttributesW(rtc_load_path) == INVALID_FILE_ATTRIBUTES)
				{
					//WARNING_EX_LOG("Failed to find RenderServer\\runtime\\rtc.dll !!!");
					return;
				}
				cinjector_util::inject_library_full(m_app_info.dwProcessId, rtc_load_path);



				//bool ret = AttachConsole(m_app_info.dwProcessId);
				//bool ret = GenerateConsoleCtrlEvent(CTRL_C_EVENT, m_app_info.dwProcessId);
				//
				//if (ret == false)
				//{
				//	DWORD error = GetLastError();
				//	LPSTR messageBuffer = nullptr;
				//	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				//		NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
				//	std::cout << "Failed to send signal. Error code: " << error << ", message: " << messageBuffer << std::endl;
				//	LocalFree(messageBuffer);
				//	printf("======\n");
				//}
				//// 向目标进程发送 CTRL+C 信号
				//std::string path = "D:/Work/cabroad_server/Server/ccloud_render_server/CloudRenderServerMgr/bin/x64/Release/SendSignal.exe";

					//path.append("   ");
				//path.append(std::to_string(m_app_info.dwProcessId));
				//system(path.c_str());
					//GenerateConsoleCtrlEvent(CTRL_C_EVENT, m_app_info.dwProcessId);
				// 向主线程发送WM_QUIT消息
				//PostThreadMessage(m_app_info.dwThreadId, WM_QUIT, 0, 0);
				// 向目标进程发送 CTRL+BREAK 信号
				//GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, 0);
				//::TerminateProcess(hProcess, 15);  //杀死进程
				//::CloseHandle(hProcess);
			}
			::CloseHandle(hProcess);
		}

	}

	EProcessStateType crender_server_mgr::get_render_server_status()
	{
		update();
		return m_process_type;
	}

}