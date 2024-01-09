#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <limits>
#define NOMINMAX
#include <Windows.h>

#include "Data.h"
#include "KontrolerKlienta.h"
#include "KontrolerZgloszenia.h"

class CLI {
public:
	CLI() : oio(ObslugaIO()), ObecnyKlient(nullptr), ObecneZgloszenie(nullptr) {
		konKlienta = new KontrolerKlienta(oio);
		konZgloszenia = new KontrolerZgloszenia(oio);
	}
	void WybierzOperacjeUI();
	void PodajDaneKlientaUI();
	void WprowadzZadaneUslugeUI();
	void FinalizujZgloszenieUI();
	void DodajDaneSerwisoweUI();
	void FinalizacjaSerwisuUI();

	void CzyscEkran();
	void WykonajFunkcjeUI();

private:
	void CzyscBuforWejscia();

	template <typename T>
	inline bool wprowadzZmienna(T& zmienna) {
		std::cin >> zmienna;
		return std::cin.good();
	}

	template <typename T>
	inline bool wprowadzZmienna(std::istream& istr,T& zmienna) {
		istr >> zmienna;
		return std::cin.good();
	}

	inline void wprowadzTekst(std::string& zmienna) {
		std::getline(std::cin, zmienna);
	}

private:
	void (CLI::*obecnaFunckjaUI)() = &CLI::WybierzOperacjeUI;

	int ObecneIDKlienta = -1;
	Klient* ObecnyKlient;
	int ObecneIDZgloszenia = -1;
	Zgloszenie* ObecneZgloszenie = 0;

	KontrolerZgloszenia* konZgloszenia;
	KontrolerKlienta* konKlienta;
	ObslugaIO oio;
};


