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
        fstream inputData;
        fstream data2;
        fstream output;
        Ticket destination;
        Ticket maxDestination;
        Ticket flightNo;
        string inputDataFile = "passengerData.txt";
        string outputDataFile = "output.txt";
        bool useDefaultFileName;
        bool correctResponseEntered = false;

        while (!correctResponseEntered)
        {
            cout << "Использовать стандартные имена файлов? <Y/N>" << endl;
            string userResponse; cin >> userResponse;

            switch (toupper(userResponse[0]))
            {
                case 'N':
                    useDefaultFileName = false;
                    correctResponseEntered = true;
                    break;
                case 'Y':
                    useDefaultFileName = true;
                    correctResponseEntered = true;
                    break;
                default:
                    cout << "Некорректный ответ.\n";
            }
        }


        if (!useDefaultFileName)
        {
            while (true)
            {
                cout << "\nВведите название файла с вводными данными:" << endl;
                cin >> inputDataFile;

                inputData.open(inputDataFile);
                if (inputData.is_open())
                {
                    cout << "\nФайл открыт.\n";
                    break;
                }

                throw("\nНе удаётся открыть указанный файл.");
            }

            while (true)
            {
                cout << "\nВведите имя файла для вывода:" << endl;
                cin >> inputDataFile;

                output.open(inputDataFile);
                if (output.is_open())
                {
                    cout << "\nФайл открыт.\n";
                    break;
                }

                throw("\nНе удаётся открыть указанный файл.");
            }    

            cout << "\nФормат билета:\n" << endl;
            cout << "Пункт назначения; Номер рейса; Фамилия и имя пассажира; Дата вылета" << endl;
            cout << "Таллин, Эстония; 512412523; Латин Артем; 21.09.2020 " << endl;
            cout << "Введите данные:(ctrl+c для выхода)\n\n";

            String stuff; cin >> stuff;

            for (USInt i = 2; stuff != '0'; i++)
            {
                inputData << stuff;
                cin >> stuff;
                inputData << endl;
                if (i % 5 == 0)
                {
                    inputData << endl;
                }
            }
        }

        inputData.open(inputDataFile);
        output.open(outputDataFile);
        if (!output.is_open() || !inputData.is_open())
        {
            throw("\nНе удаётся открыть один из файлов.");
        }


        USInt counter = 0;
        output << endl;
        output << "Список всех пунктов назначения: \t\t\t";
        char* temp = new char[255];
        counter = 0;
        inputData.clear();
        inputData.seekg(0, output.beg);

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
            inputData.clear();
            inputData.seekg(0, output.beg);
            while (!inputData.eof())
            {
                pos2++;
                inputData.getline(temp, 255, '\n');
                for (USInt i = 0; i < 4; i++)
                {
                    inputData.ignore(30, '\n');
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
                if (inputData.eof() && firstTime == false)
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
        inputData.close();
        data2.close();
        output.close();
        _CrtDumpMemoryLeaks(); // ???
    }
    catch (const char* ex)
    {
        cerr << ex << endl;
    }
}