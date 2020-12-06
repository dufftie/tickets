#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include "String.h"
#include "Ticket.h"
#include <string>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;


int main()
{
    try
    {
        setlocale(0, "Russian");
        fstream data;
        fstream data2;
        fstream output;
        Ticket destination;
        Ticket maxDestination;
        Ticket flightNo;
        cout << "Использовать стандартные имена файлов? <Y/N>" << endl;
        char yn;
        cin >> yn;
        if (yn == 'N' || yn == 'n')
        {
            cout << "\nВведите имя файла для ввода. (где будут считываемые данные)" << endl;
            char* fileName = new char[30];
            cin >> fileName;
            data.open(fileName);
            data2.open(fileName);
            if (!data.is_open() || !data2.is_open())
            {
                throw("\nНе удаётся открыть указанный файл.");
            }
            cout << "\nФайл открыт.\n";
            cout << endl;
            cout << "Введите имя файла для вывода." << endl;
            cin >> fileName;
            output.open(fileName);
            delete[] fileName;
            if (!output.is_open())
            {
                throw("\nНе удаётся открыть указанный файл.");
            }
            cout << "\nФайл открыт.\n";

            cout << "\nПорядок ввода для каждого билета таков:\n" << endl;
            cout << "Пункт назначения\n" << "Номер рейса\n" << "Фамилия и имя пассажира\n" << "Дата вылета\n";

            cout << "\nВведите данные. (0 для выхода)\n\n";

            String stuff;
            cin >> stuff;
            for (USInt i = 2; stuff != '0'; i++)
            {
                data << stuff;
                cin >> stuff;
                data << endl;
                if (i % 5 == 0)
                {
                    data << endl;
                }
            }
        }
        else if (yn == 'Y' || yn == 'y')
        {
            data.open("passengerdata.txt");
            data2.open("passengerdata.txt");
            output.open("output.txt");
            if (!output.is_open() || !data.is_open() || !data2.is_open())
            {
                throw("\nНе удаётся открыть один из стандартных файлов...");
            }
        }
        else throw("...?");
        USInt counter = 0;
        output << endl;
        output << "Список всех пунктов назначения: \t\t\t";
        char* temp = new char[255];
        counter = 0;
        data.clear();
        data.seekg(0, output.beg);

        USInt pos = 0, j = 0;
        USInt nMatches = 0;
        USInt* nTickets = new USInt[100];

        while (!data2.eof())
        {
            destination.setDestinations(data2);
            destination.getDestinations();
            USInt i = 0, y = 0, t = 0, pos2 = 0;
            pos++;
            bool matchesFound = false;
            bool firstTime = true;
            bool copyFound = false;
            bool fstTime = true;
            output.clear();
            data.clear();
            data.seekg(0, output.beg);
            while (!data.eof())
            {
                pos2++;
                data.getline(temp, 255, '\n');
                for (USInt i = 0; i < 4; i++)
                {
                    data.ignore(30, '\n');
                }
                for (y = 0; temp[y] == destination[y] && temp[t - 1] != '\0'; y++, t++)
                {
                    if (y == destination.size())
                    {
                        if (pos != pos2)
                        {
                            counter++;
                            copyFound = true;
                            break;
                        }
                        if (copyFound == false)
                        {
                            counter++;
                            if (firstTime == false)
                            {
                                matchesFound = true;
                            }
                            firstTime = false;
                            if (matchesFound == false)
                            {
                                output << destination << "\t\t\t\t";
                            }
                            y = 0;
                        }
                    }
                }
                if (data.eof() && firstTime == false)
                {
                    nMatches++;
                    nTickets[j] = counter;
                    for (USInt i = 0; i < nMatches; i++)
                    {
                        if (nTickets[i] < nTickets[j] || pos == 1)
                        {
                            maxDestination.setSize(destination.size());
                            maxDestination = destination;
                        }
                    }
                    j++;
                    /*cout << counter << endl;*/ // 2 3 2 1
                }
                t = 0;
            }
            counter = 0;
        }
        output.clear();
        output << endl;
        output << "Количество билетов: \t\t\t\t\t\t\t\t"; // должно выводить, но почему-то не выводит
        for (USInt i = 0; i < nMatches; i++)
        {
            output << nTickets[i] << "\t\t\t\t\t\t\t"; // ^^
            /*cout << nTickets[i] << endl;*/ // 2 3 2 1
        }
        output << endl;
        output << "Самый популярный рейс: " << maxDestination << endl; // ^^
        /*cout << "Самый популярный рейс: " << maxDestination << endl;*/ //Владивосток, Россия
        /*output.seekp(0, output.beg);
        output << "\t\t\t\t\t\tA" << endl;*/
        delete[] temp;
        delete[] nTickets;
        cout << "\nДанные успешно выведены в файл.\n";
        data.close();
        data2.close();
        output.close();
        _CrtDumpMemoryLeaks(); // ???
    }
    catch (const char* ex)
    {
        cerr << ex << endl;
    }
}