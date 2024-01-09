#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>
#include "Serializowalne.h"

bool sprPoprImINaz(std::string iin);
bool sprPopNrRej(std::string nrr);

class Klient : public Serializowalne<Klient>{
public:
	Klient();
	Klient(int KID, std::string iin, std::string nrr);
	Klient(Klient& inny) = delete;
	Klient(Klient&& inny);
	
	std::string zwrocImieINazwisko();
	std::string zwrocNrRejestracji();
	int zwrocIDKlienta();

	template<typename T>
	void odczytaj(std::string zapisWLinii){
		std::vector<std::string> pola = odczytajWartosciCSV(zapisWLinii);
		assert(pola.size() == 3);
		KID = atoi(pola[0].c_str());
		ImieINazwisko = pola[1];
		NrRejestracji = pola[2];
	}

	template<typename T>
	std::string zapisz(T* obiektDoZapisania){
		std::vector<std::string> pola = { std::to_string(obiektDoZapisania->KID), obiektDoZapisania->ImieINazwisko, obiektDoZapisania->NrRejestracji};
		return zapiszWartosciCSV(pola);
	}
private:
	std::string ImieINazwisko;
	std::string NrRejestracji;
	int KID;
};