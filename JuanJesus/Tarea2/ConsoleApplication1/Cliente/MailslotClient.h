#pragma once
#include <Windows.h>
#include <iostream>
#include <memory>
#include <utility>
#include <string>
#include <string_view>
#include <array>
#include <sstream>
#include <system_error>

namespace Win32::Icp::Mailslot
{
    class MailslotClient
    {
    public:
        explicit MailslotClient(const std::u16string_view slot_name) noexcept(false)
            : m_EnableLogs{ false }
            , m_SlotName{ CreateSlotName(slot_name) }
            , m_SlotFile{ CreateFileW(reinterpret_cast<LPCWSTR>(m_SlotName.data()), GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr), &CloseHandle }
        {
            if (m_SlotFile.get() == INVALID_HANDLE_VALUE)
            {
                std::stringstream message;
                message << "CreateFileW failed with " << GetLastError() << ".";

                throw std::system_error{ std::make_error_code(std::errc::io_error), message.str() };
            }
        }

        bool Write(const std::u16string_view message) const noexcept
        {
            BOOL fResult;
            DWORD cbWritten;

            fResult = WriteFile(m_SlotFile.get(), message.data(), (message.size() + 1) * sizeof(char16_t), &cbWritten, nullptr);

            if (!fResult)
            {
                WriteLog(L"WriteFile failed with ", GetLastError(), L".\n");
                return false;
            }

            WriteLog(L"Slot written to successfully.\n");

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

    private:

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

        bool m_EnableLogs;
        std::u16string m_SlotName;
        std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(&CloseHandle)> m_SlotFile;
        // https://qnaplus.com/custom-deleter-in-std-unique-ptr/
    };
}
