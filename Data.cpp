#include "Data.h"
#pragma warning(disable:4996);

std::string ustalNajblizszaDatePrzyjscia()
{
	char data[20];
	time_t obCzas;
	time(&obCzas);
	tm* timeinfo = localtime(&obCzas);
	strftime(data, sizeof(data), "%Y-%m-%d 9:00", timeinfo);
	return std::string(data);
}
//format YYYY-MM-DD
std::string przesunDateONDni(std::string dataOb, int N)
{
	std::string dniOb;
	std::istringstream iss1(dataOb);
	std::getline(iss1, dniOb, ' ');

	std::tm dataTM;
	memset(&dataTM, 0, sizeof(dataTM));
	std::istringstream iss2(dniOb);
	iss2 >> std::get_time(&dataTM, "%Y-%m-%d");

	/*std::istringstream iss2(dniOb);
	std::string token;
	int czasWart[3]{};
	for (int i = 0; std::getline(iss2, token, '-'); i++) {
		czasWart[i] = atoi(token.c_str());
	}*/
	
	//tm czasPocz;
	//czasPocz.tm_year = czasWart[0] - 1900;
	//czasPocz.tm_mon = czasWart[1] - 1;
	//czasPocz.tm_mday = czasWart[2];

	const time_t ONE_DAY = 24 * 60 * 60;
	//// Seconds since start of epoch
	time_t date_seconds = mktime(&dataTM) + (N * ONE_DAY);
	std::tm* dataTM2 = localtime(&date_seconds); //XO
	char data[20];
	strftime(data, sizeof(data), "%Y-%m-%d", dataTM2); //XO
	dniOb = std::string(data);
	dniOb += " 17:00:00"; //zwroty/przyjecia sa zawsze o 17
	return dniOb;
}
