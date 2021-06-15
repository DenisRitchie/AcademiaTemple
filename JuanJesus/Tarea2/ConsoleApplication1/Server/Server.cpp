// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MailslotServer.h"
#include <thread>
#include <chrono>
#include <locale>

void ReadEvent(
  Win32::Icp::Mailslot::MailslotServer&,
  const Win32::Icp::Mailslot::MailslotServer::MailslotServerReadEventArgs& info)
{
  // stdout
  HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  WriteConsoleW(hOutputConsole,
    info.Message.data(),
    info.Message.length(),
    nullptr,
    nullptr);
  std::wcout.put(u'\n');
}

int32_t main()
{
  Win32::Icp::Mailslot::MailslotServer server{ u"EjemploComunicacionProcesos" };
  //server.EnableLogs = true;
  server.MailslotServerRead += ReadEvent;
  
  int32_t cont = 0;

  while (cont < 30)
  {
    server.Read();
    std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
    cont++;
  }

  return 0;
}
