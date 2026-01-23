#include <iomanip>
#include <iostream>
#include <windows.h>

int main () {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    SIZE_T pageSize = si.dwPageSize;
    SIZE_T reserveSize = pageSize * 2;

    void* region1 = VirtualAlloc(
        nullptr,
        reserveSize,
        MEM_RESERVE,
        PAGE_NOACCESS
        );

    void* region2 = VirtualAlloc(
       nullptr,
       reserveSize,
       MEM_RESERVE,
       PAGE_NOACCESS
       );

    if (region1 && region2) {
        std::cout << "Регион 1 " << region1 << std::endl;
        std::cout << "Регион 2 " << region2 << std::endl;
        std::cout << "Размер страницы " << pageSize << " байт" << std::endl;
        std::cout << std::endl;

        // Задание 3: Обнулить регион 1
        void* committed1 = VirtualAlloc(
            region1,
            reserveSize,
            MEM_COMMIT,
            PAGE_READWRITE
            );

        if (committed1) {
            std::cout << "Память региона 1 выделена (committed)" << std::endl;

            ZeroMemory(region1, reserveSize);

            std::cout << "Данные региона 1 обнулены с помощью ZeroMemory" << std::endl;
            std::cout << "Обнулено байт: " << reserveSize << std::endl;
        } else {
            std::cout << "Ошибка выделения памяти для региона 1!" << std::endl;
        }

        // Задание 4: Заполнить регион 2
        void* committed2 = VirtualAlloc(
            region2,
            reserveSize,
            MEM_COMMIT,
            PAGE_READWRITE
            );

        if (committed2) {
            std::cout << "Память региона 2 выделена (committed)" << std::endl;

            int fillValue;
            std::cout << "Введите целое число (0..127) для заполнения региона 2: ";
            std::cin >> fillValue;

            if (fillValue < 0 || fillValue > 127) {
                std::cout << "Ошибка. Число должно быть в диапазоне 0..127!" << std::endl;
                fillValue = 0;
            }

            FillMemory(region2, reserveSize, static_cast<BYTE>(fillValue));

            std::cout << "Регион 2 заполнен значением: " << fillValue << std::endl;
            std::cout << "Заполнено байт: " << reserveSize << std::endl;

        } else {
            std::cout << "Ошибка выделения памяти для региона 2!" << std::endl;
        }

        // Задание 5
        std::cout << "Содержимое регионов" << std::endl;
        std::cout << std::endl;

        // Отображение региона 1
        std::cout << "Регион 1" << std::endl;
        BYTE* bytes1 = static_cast<BYTE*>(region1);
        for (size_t i = 0; i < 64 && i < reserveSize; i++) {
            if (i % 16 == 0) {
                std::cout << std::hex << std::setw(4) << std::setfill('0') << i << ": ";
            }

            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes1[i]) << " ";
            if ((i + 1) % 16 == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::dec << std::endl;

        // Отображение региона 2
        std::cout << "Регион 2" << std::endl;
        BYTE* bytes2 = static_cast<BYTE*>(region2);
        for (size_t i = 0; i < 64 && i < reserveSize; i++) {
            if (i % 16 == 0) {
                std::cout << std::hex << std::setw(4) << std::setfill('0') << i << ": ";
            }

            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes2[i]) << " ";
            if ((i + 1) % 16 == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::dec << std::endl;

        // Статистика
        std::cout << "Статистика" << std::endl;
        std::cout << "Общий размер каждого региона: " << reserveSize << " байт (" << reserveSize / 1024 << " КБ" << std::endl;

        VirtualFree(region1, 0, MEM_RELEASE);
        VirtualFree(region2, 0, MEM_RELEASE);
    }

    return 0;
}