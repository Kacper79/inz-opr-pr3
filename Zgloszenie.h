#pragma once
#include <string>
#include <vector>
#include <assert.h>
#include "Serializowalne.h"

enum FORMA_SERWISU { OKRESOWY_PRZEGLAD = 1, NAPRAWA_USTERKI };

class Zgloszenie : public Serializowalne<Zgloszenie>{
public:
	Zgloszenie();
	Zgloszenie(int ZID, int KID, FORMA_SERWISU fs);
	Zgloszenie(Zgloszenie& inny) = delete;
	Zgloszenie(Zgloszenie&& inny);

	void DodajDaneSerwisowe(std::vector<std::string> listaNaprawionychUsterek, bool zdolnyDoJazdy);
	void DopiszUstalonyKosztNaprawy(int kosztObslugi);
	void UstalTerminSpotkania(std::string dataSpotkania);

	int ZwrocIDZgloszenia();
	FORMA_SERWISU ZwrocFormeZgloszenia();
	std::vector<std::string> ZwrocListeUsterek();

	template<typename T>
	void odczytaj(std::string zapisWLinii) {
		std::vector<std::string> pola = odczytajWartosciCSV(zapisWLinii);
		assert(pola.size() == 7);
		ZID = atoi(pola[0].c_str());
		KID = atoi(pola[1].c_str());
		formaSerwisu = (FORMA_SERWISU)atoi(pola[2].c_str());
		przeszedlPrzeglad = atoi(pola[3].c_str()) == 0 ? false : true;
		usterki = odczytajWektorJakoSCSV(pola[4]);
		kosztUslugi = atoi(pola[5].c_str());
		dataSpotkania = pola[6];
	}

	template<typename T>
	std::string zapisz(T* obiektDoZapisania) {
		std::vector<std::string> pola = { std::to_string(obiektDoZapisania->ZID), std::to_string(obiektDoZapisania->KID), std::to_string((int)obiektDoZapisania->formaSerwisu), std::to_string((int)obiektDoZapisania->przeszedlPrzeglad),zapiszWektorJakoSCSV(obiektDoZapisania->usterki), std::to_string(obiektDoZapisania->kosztUslugi), obiektDoZapisania->dataSpotkania };
		return zapiszWartosciCSV(pola);
	}

private:
	std::string dataSpotkania;
	int kosztUslugi;
	std::vector<std::string> usterki;
	bool przeszedlPrzeglad;
	FORMA_SERWISU formaSerwisu;
	int KID;
	int ZID;
};