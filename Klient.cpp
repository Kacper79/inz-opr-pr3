#include "Klient.h"

Klient::Klient() : Serializowalne() {}
Klient::Klient(int KID, std::string iin, std::string nrr) : KID(KID),ImieINazwisko(iin), NrRejestracji(nrr), Serializowalne() {}
Klient::Klient(Klient&& inny) : KID(inny.KID), ImieINazwisko(inny.ImieINazwisko), NrRejestracji(inny.NrRejestracji),Serializowalne() {}

std::string Klient::zwrocImieINazwisko()
{
	return ImieINazwisko;
}

std::string Klient::zwrocNrRejestracji()
{
	return NrRejestracji;
}

int Klient::zwrocIDKlienta()
{
	return KID;
}

bool sprPoprImINaz(std::string iin)
{
	std::stringstream iss(iin);
	std::string name;
	int nc = 0;
	while (std::getline(iss, name, ' ')) {
		for (unsigned i = 0; i < name.size(); i++) {
			if (!isalnum(name[i]) || isdigit(name[i])) {
				return false;
			}
		}
		nc++;
	}
	if (nc != 2) return false;
	return true;
}

bool sprPopNrRej(std::string nrr)
{
	std::stringstream iss(nrr);
	std::string name;
	int nc = 0;
	while (std::getline(iss, name, ' ')) {
		for (unsigned i = 0; i < nrr.size(); i++) {
			if (!isalnum(nrr[i])) {
				return false;
			}
		}
		nc++;
	}
	if (nc != 1) return false;
	return true;
}
