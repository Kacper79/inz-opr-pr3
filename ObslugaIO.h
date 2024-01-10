#pragma once
#include <string>
#include <sstream>
#include <fstream>

#define NAZWA_TYMCZASOWA "temp.txt"

enum class NAZWA_TABEL {
	BRAK,
	KLIENCI,
	ZGLOSZENIA,
	//WYCENA
};

inline std::string UzyskajNazweTabeli(NAZWA_TABEL nazwaTabeli) {
	switch (nazwaTabeli) {
		case NAZWA_TABEL::KLIENCI:
			return "C:\\Users\\123627\\source\\repos\\INWarsztat\\INWarsztat\\Debug\\klienci.txt";
		break;
		case NAZWA_TABEL::ZGLOSZENIA:
			return "C:\\Users\\123627\\source\\repos\\INWarsztat\\INWarsztat\\Debug\\zgloszenia.txt";
		break;
		/*case NAZWA_TABEL::WYCENA:
			return "F:\\inf\\INWarsztat\\Debug\\wycena.txt";
		break;*/
		default:
			abort();
		break;
	}
}

class ObslugaIO {
public:
	ObslugaIO(){}

	std::fstream& UzyskajPolePliku(NAZWA_TABEL nazwaTabeli);

	void otworzPlik(NAZWA_TABEL nazwaTabeli);
	void zamknijPlik(NAZWA_TABEL nazwaTabeli);

	bool usunRekord(NAZWA_TABEL nazwaTabeli, int ID);
	bool edytujRekord(NAZWA_TABEL nazwaTabeli, std::string zedytowanyRekordSerializowany, int ID);
	bool dodajNowyRekord(NAZWA_TABEL nazwaTabeli, std::string rekordSerializowany, int ID);
	int znajdzNajwyzszeID(NAZWA_TABEL nazwaTabeli);
	std::string szukajRekordu(NAZWA_TABEL nazwaTabeli, int ID);
	std::string szukajRekorduPoPolu(NAZWA_TABEL nazwaTabeli, unsigned kolejWRekord, std::string wartPola);
	std::string zwrocNtePoleRekordu(std::string rekord,unsigned kolejWRekord);


	std::fstream plikKlienci;
	std::fstream plikZgloszenia;
	//std::fstream plikWyceny;
};






