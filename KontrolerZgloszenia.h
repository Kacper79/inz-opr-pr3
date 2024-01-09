#pragma once
#include "Zgloszenie.h"
#include "ObslugaIO.h"

class KontrolerZgloszenia {
public:
	KontrolerZgloszenia(ObslugaIO& oio);
	~KontrolerZgloszenia();
	Zgloszenie* StworzNoweZgloszenie(int KID, FORMA_SERWISU fs);
	Zgloszenie* SzukajZgloszeniaPoZID(int ZID);
	Zgloszenie* SzukajZgloszeniaPoKID(int KID);
	void DodajDaneSerwisowe(Zgloszenie*& zgloszenie,std::vector<std::string> listaNaprawionychUsterek, bool zdolnyDoJazdy);
	void DopiszUstalonyKosztNaprawy(Zgloszenie*& zgloszenie,int kosztObslugi);
	void UstalTerminSpotkania(Zgloszenie*& zgloszenie,std::string dataSpotkania);
	void UsunZgloszenie(Zgloszenie*& zgloszenie);
private:
	std::vector<Zgloszenie*> stworzoneZgloszenia;
	int licznikZID;
	ObslugaIO& oio;
};
