#pragma once

#include <Windows.h>
#include <string>
#include <string_view>
#include <memory>
#include <utility>
#include <sstream>
#include <list>
#include <functional>
#include <iostream>

namespace Win32::Icp::Mailslot
{
    class MailslotServer
    {
    public:
        class MailslotServerReadEventArgs
        {
        public:

            explicit MailslotServerReadEventArgs(const std::u16string_view message) noexcept : m_Message{ message } { }

#pragma push_macro("GetMessage")
#undef GetMessage

            std::u16string_view GetMessage() const noexcept
            {
                return m_Message;
            }

            __declspec(property(get = GetMessage)) std::u16string_view Message;

#pragma pop_macro("GetMessage")

        private:
            std::u16string_view m_Message;
        };

        class MailslotServerReadEventHandler
        {
        public:
            using delegate_t = void(MailslotServer&, const MailslotServerReadEventArgs&);

            MailslotServerReadEventHandler() noexcept = default;
            MailslotServerReadEventHandler(const MailslotServerReadEventHandler&) = delete;
            MailslotServerReadEventHandler(MailslotServerReadEventHandler&&) = delete;
            MailslotServerReadEventHandler& operator=(const MailslotServerReadEventHandler&) = delete;
            MailslotServerReadEventHandler& operator=(MailslotServerReadEventHandler&&) = delete;

            void operator+=(std::function<delegate_t> event_function) noexcept
            {
                m_Delegates.push_back(event_function);
            }

            void operator()(MailslotServer& sender, const MailslotServerReadEventArgs& event_info) const noexcept
            {
                for (const auto& event_function : m_Delegates)
                    event_function(sender, event_info);
            }

        private:
            std::list<std::function<delegate_t>> m_Delegates;
        };

        explicit MailslotServer(const std::u16string_view slot_name) noexcept(false)
            : m_EnableLogs{ false }
            , m_SlotName{ CreateSlotName(slot_name) }
            , m_SlotHandle{ MakeSlot() }
        {
        }

        bool Read() noexcept
        {
            BOOL fResult = true;
            HANDLE hEvent = nullptr;
            OVERLAPPED ov = { };
            DWORD cbMessage = 0, cMessage = 0, cbRead = 0;

            hEvent = CreateEventW(nullptr, false, false, reinterpret_cast<LPCWSTR>(NewGuid().data()));

            if (nullptr == hEvent)
                return false;

            ov.Offset = 0;
            ov.OffsetHigh = 0;
            ov.hEvent = hEvent;

            fResult = GetMailslotInfo(/*mailslot handle*/ m_SlotHandle, /*no maximum message size*/ nullptr, /*size of next message*/ &cbMessage, /*number of messages*/ &cMessage, /*no read time-out*/ nullptr);

            if (!fResult)
            {
                WriteLog(L"GetMailslotInfo failed with ", GetLastError(), L".\n");
                return false;
            }

            if (cbMessage == MAILSLOT_NO_MESSAGE)
            {
                WriteLog(L"Waiting for a message...\n");
                return true;
            }

            while (cMessage != 0) // retrieve all messages
            {
                std::u16string buffer(cbMessage, u'\0');

                fResult = ReadFile(m_SlotHandle, buffer.data(), cbMessage, &cbRead, &ov);

                if (!fResult)
                {
                    WriteLog(L"ReadFile failed with ", GetLastError(), L".\n");
                    return false;
                }

                MailslotServerRead(*this, MailslotServerReadEventArgs{ buffer });

                fResult = GetMailslotInfo(/*mailslot handle*/ m_SlotHandle, /*no maximum message size*/ nullptr, /*size of next message*/ &cbMessage, /*number of messages*/ &cMessage, /*no read time-out*/ nullptr);

                if (!fResult)
                {
                    WriteLog(L"GetMailslotInfo failed (", GetLastError(), L")\n");
                    return false;
                }
            }

            CloseHandle(hEvent);
            return true;
        }

        void SetEnableLogs(const bool value) noexcept
        {
            m_EnableLogs = value;
        }

        bool GetEnableLogs() const noexcept
        {
            return m_EnableLogs;
        }

        __declspec(property(get = GetEnableLogs, put = SetEnableLogs)) bool EnableLogs;

        MailslotServerReadEventHandler MailslotServerRead;

    private:
        HANDLE WINAPI MakeSlot() noexcept(false)
        {
            HANDLE hSlot = CreateMailslotW(reinterpret_cast<LPCWSTR>(m_SlotName.data()), /*no maximum message size*/0, /*no time-out for operations*/ MAILSLOT_WAIT_FOREVER, /*default security*/ nullptr);

            if (hSlot == INVALID_HANDLE_VALUE)
            {
                std::stringstream message;
                message << "CreateMailslotW failed with " << GetLastError() << ".";
                throw std::system_error{ std::make_error_code(std::errc::operation_canceled), message.str() };
            }

            return hSlot;
        }

        inline static std::u16string CreateSlotName(const std::u16string_view slot_name) noexcept
        {
            using namespace std;
            return u"\\\\.\\mailslot\\"s + slot_name.data();
        }


        template<typename ...Args>
        inline void WriteLog(Args &&...args) const noexcept
        {
            if (m_EnableLogs)
            {
                (std::wclog << ... << args);
            }
        }

        static std::u16string NewGuid() noexcept
        {
            std::u16string result;

#pragma warning(disable: 6031)

            GUID guid;
            CoCreateGuid(&guid);

            OLECHAR* guid_string;
            StringFromCLSID(guid, &guid_string);

            result.assign(reinterpret_cast<const char16_t* const>(guid_string));

            ::CoTaskMemFree(guid_string);

#pragma warning(default: 6031)

            return std::move(result);
        }

        bool m_EnableLogs;
        std::u16string m_SlotName;
        HANDLE m_SlotHandle;
    };
}
