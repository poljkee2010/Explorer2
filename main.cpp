#include <boost/filesystem.hpp>
#include <cstring>
#include <fstream>
#include <future>
#include <iostream>

using namespace std;
namespace fs = boost::filesystem;

string getFileName(string address) //получение имя файла
{
	fs::path filePath = address;
	fs::path textFilename = filePath.filename();
  return textFilename.string();
}

double getFileSize(string address) //получение размера файла
{
	fs::path filePath = address; // Указываем путь к файлу
	return fs::file_size(filePath);
}

string getFileDate(string address) //получение даты модификации файла
{
	fs::path filePath = address;
	time_t ftime = fs::last_write_time(filePath); //получаем время последнего изменения
	return asctime(gmtime(&ftime));
}

void Get(string address)
{
	if (fs::is_directory(address)) 	//Проверка на то,ссылается ли введённый путь на каталог
		throw runtime_error("Type of file - directory");

	if (!fs::exists(address))	//Проверка существования файла по введенному адресу
		throw runtime_error("File does not find!");

	future<string>futureFileName = async(getFileName,address);
	future<double>futureFileSize = async(getFileSize, address);
	future<string>futureFileDate = async(getFileDate, address);

	string FileName = futureFileName.get();
	double FileSize = futureFileSize.get();
	string FileDate = futureFileDate.get();

	ofstream outfile; //Запись информации в файл log.txt
	outfile.open(getenv("EXPLORER_LOG_PATH"), ofstream::out | ofstream::app);
	outfile << "Название файла:\t " << FileName << endl;
	outfile << "Размер:\t " << FileSize << " byte" << endl;
	outfile << "Modification date:\t " << FileDate << endl;
	outfile.close();
}

int main()
{
	try
	{
		string ad;
		cout << "Укажите путь к файлу" << endl;
		cin >> ad; //указываем путь

		Get(ad); //метод получения информации о файле
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
