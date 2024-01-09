#include "ObslugaIO.h"
#include <iostream>

void ObslugaIO::otworzPlik(NAZWA_TABEL nazwaTabeli)
{
	std::string nazwaTabeliSTR = UzyskajNazweTabeli(nazwaTabeli);
	switch (nazwaTabeli) {
	case NAZWA_TABEL::KLIENCI:
		plikKlienci = std::fstream(nazwaTabeliSTR, std::fstream::in | std::fstream::out);
		if (!plikKlienci) plikKlienci = std::fstream(nazwaTabeliSTR, std::fstream::in | std::fstream::out | std::fstream::trunc);
		break;
	//case NAZWA_TABEL::WYCENA:
	//	plikWyceny = std::fstream(nazwaTabeliSTR, std::fstream::in | std::fstream::out);
	//	if (!plikWyceny) plikWyceny = std::fstream(nazwaTabeliSTR, std::fstream::in | std::fstream::out | std::fstream::trunc);
	//	break;
	case NAZWA_TABEL::ZGLOSZENIA:
		plikZgloszenia = std::fstream(nazwaTabeliSTR, std::fstream::in | std::fstream::out);
		if (!plikZgloszenia) plikZgloszenia = std::fstream(nazwaTabeliSTR, std::fstream::in | std::fstream::out | std::fstream::trunc);
		break;
	default:
		abort();
	}
}

void ObslugaIO::zamknijPlik(NAZWA_TABEL nazwaTabeli)
{
	switch (nazwaTabeli) {
	case NAZWA_TABEL::KLIENCI:
		plikKlienci.flush();
		plikKlienci.close();
		break;
	/*case NAZWA_TABEL::WYCENA:
		plikWyceny.flush();
		plikWyceny.close();
		break;*/
	case NAZWA_TABEL::ZGLOSZENIA:
		plikZgloszenia.flush();
		plikZgloszenia.close();
		break;
	default:
		abort();
	}
}

bool ObslugaIO::usunRekord(NAZWA_TABEL nazwaTabeli, int ID)
{
	std::string currLine;
	std::fstream& plik = UzyskajPolePliku(nazwaTabeli);
	otworzPlik(nazwaTabeli);
	std::fstream plikNowy(NAZWA_TYMCZASOWA, std::ios::out);
	if (!plikNowy) return false;
	std::string token;
	while (std::getline(plik, currLine)) {
		std::istringstream iss(currLine);
		std::getline(iss, token, ',');
		if (atoi(token.c_str()) != ID) {
			plikNowy << currLine;
		}
	}
	plikNowy.close();
	zamknijPlik(nazwaTabeli);
	if (remove(UzyskajNazweTabeli(nazwaTabeli).c_str())) return false;
	if (rename(NAZWA_TYMCZASOWA, UzyskajNazweTabeli(nazwaTabeli).c_str())) return false;
	return true;
}

bool ObslugaIO::edytujRekord(NAZWA_TABEL nazwaTabeli, std::string zedytowanyRekordSerializowany, int ID)
{
	std::string currLine;
	std::fstream& plik = UzyskajPolePliku(nazwaTabeli);
	otworzPlik(nazwaTabeli);
	std::fstream plikNowy(NAZWA_TYMCZASOWA, std::ios::out);
	if (!plikNowy) return false;
	std::string token;
	while (std::getline(plik, currLine)) {
		std::istringstream iss(currLine);
		std::getline(iss, token, ',');
		if (atoi(token.c_str()) != ID) {
			plikNowy << currLine;
		}
		else {
			plikNowy << zedytowanyRekordSerializowany;
		}
	}
	plikNowy.close();
	zamknijPlik(nazwaTabeli);
	if(remove(UzyskajNazweTabeli(nazwaTabeli).c_str())) return false;
	if(rename(NAZWA_TYMCZASOWA, UzyskajNazweTabeli(nazwaTabeli).c_str())) return false;
	return true;
}

bool ObslugaIO::dodajNowyRekord(NAZWA_TABEL nazwaTabeli, std::string rekordSerializowany, int ID)
{
	std::fstream& plik = UzyskajPolePliku(nazwaTabeli);
	otworzPlik(nazwaTabeli);
	//if (!plik) return false;
	bool otwarty = plik.is_open();
	std::cout << otwarty;
	plik << rekordSerializowany;
	zamknijPlik(nazwaTabeli);
	return true;
}

int ObslugaIO::znajdzNajwyzszeID(NAZWA_TABEL nazwaTabeli)
{
	std::string currLine;
	std::fstream& plik = UzyskajPolePliku(nazwaTabeli);
	otworzPlik(nazwaTabeli);
	std::string token;
	int maxID = 0;
	while (std::getline(plik, currLine)) {
		std::istringstream iss(currLine);
		std::getline(iss, token, ',');
		int ID = atoi(token.c_str());
		if (ID > maxID) {
			maxID = ID;
		}
	}
	zamknijPlik(nazwaTabeli);
	return maxID;
}

std::string ObslugaIO::szukajRekordu(NAZWA_TABEL nazwaTabeli, int ID)
{
	std::string currLine;
	std::fstream& plik = UzyskajPolePliku(nazwaTabeli);
	otworzPlik(nazwaTabeli);
	std::string token;
	while (std::getline(plik, currLine)) {
		std::istringstream iss(currLine);
		std::getline(iss, token, ',');
		if (atoi(token.c_str()) == ID) {
			zamknijPlik(nazwaTabeli);
			return currLine;
		}
	}
	zamknijPlik(nazwaTabeli);
	return "";
}

std::string ObslugaIO::szukajRekorduPoPolu(NAZWA_TABEL nazwaTabeli, unsigned kolejWRekord, std::string wartPola)
{
	std::string currLine;
	std::fstream& plik = UzyskajPolePliku(nazwaTabeli);
	otworzPlik(nazwaTabeli);
	std::string token;
	while (std::getline(plik, currLine)) {
		std::istringstream iss(currLine);
		for (unsigned i = 0; std::getline(iss, token, ','); i++) {
			if (i == kolejWRekord && token == wartPola) {
				zamknijPlik(nazwaTabeli);
				return currLine;
			}
		}
	}
	zamknijPlik(nazwaTabeli);
	return "";
}

std::string ObslugaIO::zwrocNtePoleRekordu(std::string rekord,unsigned kolejWRekord)
{
	std::string token;
	std::istringstream iss(rekord);
	for (unsigned i = 0; std::getline(iss, token, ','); i++) {
		if (i == kolejWRekord) {
			return token;
		}
	}
}


std::fstream& ObslugaIO::UzyskajPolePliku(NAZWA_TABEL nazwaTabeli)
{
	switch (nazwaTabeli) {
	case NAZWA_TABEL::KLIENCI:
		return plikKlienci;
	case NAZWA_TABEL::ZGLOSZENIA:
		return plikZgloszenia;
	/*case NAZWA_TABEL::WYCENA:
		return plikWyceny;*/
	default:
		abort();
	}
}
