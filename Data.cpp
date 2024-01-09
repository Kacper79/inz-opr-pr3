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

	std::istringstream iss2(dniOb);
	std::string token;
	int czasWart[3]{};
	for (int i = 0; std::getline(iss2, token, '-'); i++) {
		czasWart[i] = atoi(token.c_str());
	}
	
	tm czasPocz;
	czasPocz.tm_year = czasWart[0] - 1900;
	czasPocz.tm_mon = czasWart[1] - 1;
	czasPocz.tm_mday = czasWart[2];

	const time_t ONE_DAY = 24 * 60 * 60;
	// Seconds since start of epoch
	time_t date_seconds = mktime(&czasPocz) + (N * ONE_DAY);
	czasPocz = *localtime(&date_seconds);
	char data[20];
	strftime(data, sizeof(data), "%Y-%m-%d", localtime(&date_seconds));
	dniOb = std::string(data);
	dniOb += " 17:00:00"; //zwroty/przyjecia sa zawsze o 17
	return dniOb;
}
