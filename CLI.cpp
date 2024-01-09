#include "CLI.h"

constexpr auto RozmiarSTDIN = std::numeric_limits<std::streamsize>::max();

void CLI::WybierzOperacjeUI() {
	std::cout << "Operacje do wybrania\n";
	std::cout << "\t1. Podaj dane klienta\n";
	//std::cout << "\t2. Wprowadz zgloszenie serwisowe\n";
	std::cout << "\t3. Dodaj dane serwisowe do zgloszenia\n";
	std::cout << "\t4. Wyjdz z programu\n";
	std::cout << "Wybierz operacje: ";
	int nrOperacji = -1;
	if (std::cin >> nrOperacji) {
		switch (nrOperacji) {
		case 1:
			obecnaFunckjaUI = &CLI::PodajDaneKlientaUI;
			break;
		//case 2:
		//	obecnaFunckjaUI = &CLI::WprowadzZadaneUslugeUI;
		//	break;
		case 3:
			obecnaFunckjaUI = &CLI::DodajDaneSerwisoweUI;
			break;
		case 4:
			exit(0);
			break;
		default:
			std::cout << "Podano bledna opcje, sprobuj ponownie\n";
			break;
		}
	}
	else {
		std::cout << "To nie jest cyfra, sprobuj ponownie\n";
	}
}

void CLI::PodajDaneKlientaUI() {
	CzyscBuforWejscia();
	
	std::string iin = "";
	std::string nrr = "";

	std::cout << "Podaj imie i nazwisko klienta oddzielone spacja: ";
	wprowadzTekst(iin);
	while (!sprPoprImINaz(iin)) {
		iin = "";
		std::cout << "To nie jest poprawne imie i nazwisko, podaj ponownie\n";
		wprowadzTekst(iin);
	}

	std::cout << "Podaj nr rejestracji badanego samochodu: ";
	wprowadzTekst(nrr);
	while (!sprPopNrRej(nrr)) {
		nrr = "";
		std::cout << "To nie jest poprawny nr rejestracji, podaj ponownie: ";
		wprowadzTekst(nrr);
	}
	//capitalize letters
	for (auto it = iin.begin(); it != iin.end(); it++) {
		if (isalpha(*it)) *it = toupper(*it);
	}
	for (auto it = nrr.begin(); it != nrr.end(); it++) {
		if (isalpha(*it)) *it = toupper(*it);
	}
	ObecnyKlient = konKlienta->StworzNowegoKlienta(iin,nrr);
	ObecneIDKlienta = ObecnyKlient->zwrocIDKlienta();

	obecnaFunckjaUI = &CLI::WprowadzZadaneUslugeUI;
}

void CLI::WprowadzZadaneUslugeUI() {
	
	FORMA_SERWISU fs;
	std::cout << "Uslugi oferowane przez serwis:\n";
	std::cout << "\t1. Badanie okresowe\n";
	std::cout << "\t2. Przeglad z podejrzenia usterki\n";
	std::cout << "Wybierz opcje (cyfra): ";
	int nrOperacji;
	if (wprowadzZmienna(nrOperacji)) {
		switch (nrOperacji) {
		case 1:
			fs = FORMA_SERWISU::OKRESOWY_PRZEGLAD;
			break;
		case 2:
			fs = FORMA_SERWISU::NAPRAWA_USTERKI;
			break;
		default:
			std::cout << "To nie jest poprawna usluga";
			CzyscBuforWejscia();
			return;
		}
	}
	else {
		std::cout << "To nie jest cyfra";
		CzyscBuforWejscia();
		return;
	}
	ObecneZgloszenie = konZgloszenia->StworzNoweZgloszenie(ObecneIDKlienta, fs);
	ObecneIDZgloszenia = ObecneZgloszenie->ZwrocIDZgloszenia();

	obecnaFunckjaUI = &CLI::FinalizujZgloszenieUI;
}

void CLI::FinalizujZgloszenieUI() {
	CzyscBuforWejscia();
	std::string dataSpot = ustalNajblizszaDatePrzyjscia();
	std::cout << "Potwierdznie przyjscia\n";
	std::cout << "Klient " << ObecnyKlient->zwrocImieINazwisko() << " ma umowiona wizyte dnia(YYYY-MM-DD): " << dataSpot << "\n";
	std::cout << "Auto bedzie oczekiwalo na wizyte mechanika\n";
	konZgloszenia->UstalTerminSpotkania(ObecneZgloszenie, dataSpot);
	getchar();
	obecnaFunckjaUI = &CLI::WybierzOperacjeUI;
}

void CLI::DodajDaneSerwisoweUI() {
	int KID = -1;
	
	std::cout << "Podaj numer klienta, ktorego auto jest serwisowane";
	if (ObecneIDKlienta > -1) std::cout << "(domyslny wybor- " << ObecneIDKlienta << ")";
	std::cout << ": ";
	if (wprowadzZmienna(KID)) {
		ObecnyKlient = konKlienta->SzukajKlientaPoKID(KID);
		if (ObecnyKlient == nullptr) {
			std::cout << "To nie jest poprawny numer klienta";
			CzyscBuforWejscia();
			return;
		}
		ObecneIDKlienta = ObecnyKlient->zwrocIDKlienta();
		ObecneZgloszenie = konZgloszenia->SzukajZgloszeniaPoKID(KID);
		if (ObecneZgloszenie == nullptr) {
			std::cout << "Nie ma zgloszenia klienta o takim ID";
			CzyscBuforWejscia();
			return;
		}
		ObecneIDZgloszenia = ObecneZgloszenie->ZwrocIDZgloszenia();
	}
	else {
		std::cout << "To nie jest poprawny numer klienta";
		CzyscBuforWejscia();
		return;
	}

	CzyscBuforWejscia();
	
	if (ObecneZgloszenie->ZwrocFormeZgloszenia() == FORMA_SERWISU::OKRESOWY_PRZEGLAD) {
		char znak;
		bool przeszedl;
		std::cout << "Czy przeszdl przeglad(t/n): ";
		while (true) {
			if (wprowadzZmienna(znak)) {
				if (znak == 't') {
					przeszedl = true;
					break;
				}
				else if (znak == 'n') {
					przeszedl = false;
					break;
				}
				else {
					std::cout << "To nie jest znak t lub n\n";
					CzyscBuforWejscia();
				}
			}
			else {
				std::cout << "To nie jest znak t lub n\n";
				CzyscBuforWejscia();
			}
		}
		konZgloszenia->DodajDaneSerwisowe(ObecneZgloszenie,std::vector<std::string>(0), przeszedl);
	}
	else {
		std::vector<std::string> usterki;
		while (true) {
			std::string usterka;
			std::cout << "Wpisz koniec, zeby zakonczyc wpisywanie\n";
			std::cout << "Podaj liste naprawionych usterek\n";
			wprowadzTekst(usterka);
			if (usterka == "koniec") break;
			usterki.push_back(usterka);
		}
		konZgloszenia->DodajDaneSerwisowe(ObecneZgloszenie,usterki, false);
	}

	std::cout << "Podaj cene uslugi do faktury/rachunku: ";
	int cena;
	while (true) {
		if (wprowadzZmienna(cena)) {
			if (cena <= 0) {
				printf("To nie jest poprawna cena\n");
				CzyscBuforWejscia();
			}
			else {
				break;
			}
		}
		else {
			printf("To nie jest liczba\n");
			CzyscBuforWejscia();
		}
	}
	konZgloszenia->DopiszUstalonyKosztNaprawy(ObecneZgloszenie, cena);
	
	
	obecnaFunckjaUI = &CLI::FinalizacjaSerwisuUI;
}

void CLI::FinalizacjaSerwisuUI() {

	std::cout << "Potwierdznie przyjscia\n";
	std::string dataPrzyjscia = ustalNajblizszaDatePrzyjscia();
	dataPrzyjscia = przesunDateONDni(dataPrzyjscia, rand() % 28);
	std::cout << "Klient " << ObecnyKlient->zwrocImieINazwisko() << " ma umowiona wizyte dnia(YYYY-MM-DD): " << dataPrzyjscia << "\n";
	std::cout << "Auto bedzie oczekiwalo na odbior od mechanika\n";
	konZgloszenia->UstalTerminSpotkania(ObecneZgloszenie,dataPrzyjscia);
	Sleep(3000);

	std::cout << "Czy usunac zgloszenie(domyslnie - tak, wpisz t lub n): ";
	char usunCh;
	while (true) {
		if (wprowadzZmienna(usunCh)) {
			if (usunCh == 't' || usunCh == 'n') {
				break;
			}
			else {
				printf("To nie jest poprawna opcja\n");
				CzyscBuforWejscia();
			}
		}
		else {
			printf("To nie jest znak opcji\n");
			CzyscBuforWejscia();
		}
	}
	if (usunCh == 't') konZgloszenia->UsunZgloszenie(ObecneZgloszenie);

	
	ObecneIDZgloszenia = -1;
	ObecneZgloszenie = nullptr;
	ObecneIDKlienta = -1;
	ObecnyKlient = nullptr;

	obecnaFunckjaUI = &CLI::WybierzOperacjeUI;
}

void CLI::CzyscEkran()
{
	Sleep(1000);
	//CzyscBuforWejscia();
	std::system("cls");
}

void CLI::WykonajFunkcjeUI()
{
	(*this.*obecnaFunckjaUI)();
}

void CLI::CzyscBuforWejscia()
{
	std::cin.clear();
	std::cin.ignore(RozmiarSTDIN, '\n');
}
