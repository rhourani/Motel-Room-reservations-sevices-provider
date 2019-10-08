/****************************************************************************
** Motel-Room-reservations-sevices-provider C++ coded program
** Author : Ridvan Alhourani
** Year : 2017
** Copy Rights: Open Source
** 
****************************************************************************/


#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<string>

using namespace std;
//Struct Musteri ve Oda
struct Musteri {
public:
	int Numarasi;
	string adi;
	string Soyadi;
	void setTC(string TC)//get ve set metodlari TC kimlik numarasi icin
	{
		TC_kimlik = TC;
	}
	string GetTC() 
	{
		return TC_kimlik;
	}

private:
	string TC_kimlik;
};
Musteri musteri;

struct Oda {
public:
	int odaNo;
	int odaUcreti;
};
Oda oda;

//prototip fonksiyon tanimlama
void display_menu(void);

void display_odaIslemi(void);
void odaEkle();
void odaSil();
void odalarListele();

void display_musteriIslemi(void);
void musteriEkle();
void musteriSil();
void musteriListele();

void display_odaKayitIslemi(void);
void odaKayitIslemi();
void odaKayidiSil();
void odalarKaydiListele();



//main fonksiyonu
int main()
{
	int secim,secOda,secMusteri,secOdaKayidi;//alan tanimlam
	//do-while dongusu
	do
	{
		display_menu();// display_menu fonksiyon cagirma
		cin >> secim;
		//switch-case Ana menu icin 
		switch (secim)
		{
		case 1:
			display_odaIslemi();
			cin >> secOda;
			//switch-case Oda islemi icin
			switch (secOda)
			{
			case 1:
				odaEkle();
				cout << "Oda Eklendi\n\n";
				break;
			case 2:
				odaSil();
				cout << "Oda Silindi\n\n";
				break;
			case 3:
				odalarListele();
				break;
			case 99:
				system("cls");
				break;
			default:
				cout << "Hatali Secim\n\n";
				system("pause");
				system("cls");
				break;
			}
			break;
		case 2:
			display_musteriIslemi();// display_musteriIslemi fonksiyon cagirma
			cin>>secMusteri;
			//switch-case Musteri islemi icin
				switch (secMusteri)
				{
				case 1:
					musteriEkle();
					cout << "Musteri Eklendi\n\n";
					break;
				case 2:
					musteriSil();
					cout << "Musteri Silindi\n\n";
					break;
				case 3:
					musteriListele();
					break;
				case 99:
					system("cls");
					break;
				default:
					cout << "Hatali Secim\n\n";
					system("pause");
					system("cls");
					break;
				}
			
			break;
		case 3:
			display_odaKayitIslemi();//display_odaKayitIslemi fonksiyon cagirma
			cin >> secOdaKayidi;
			//switch-case Oda kayit islemi icin
			switch (secOdaKayidi)
			{
			case 1:
				odaKayitIslemi();
				cout << "Oda kaydi yapildi\n\n";
				break;
			case 2:
				odaKayidiSil();
				cout << "Oda kaydi silindi\n\n";
				break;
			case 3:
				odalarKaydiListele();
				break;
			case 99:
				system("cls");
				break;
			default:
				cout << "Hatali Secim\n\n";
				system("pause");
				system("cls");
				break;
			}
			break;
		case 99:
			return 0;
			break;
		default:
			system("cls");
			cout << "Hatali Secim\n\n";
			system("pause");
			system("cls");
			break;
		}


	} while (secim != 99);//secim 99 olmadigi surece devam
	return 0;//program dogruca sonlandirdi
}

//oda ekleme metodu
void odaEkle(){

	ofstream OdaBilgisi;//dosya nesne olusturmasi
	system("cls");
	cout << "1-Oda Ekle\n";
	OdaBilgisi.open("OdaBilgisi.txt", ios::app);//dosya ac komutu
	if(OdaBilgisi.is_open())//dosya acksa gir hatalar dusururuz
	{
		//bilgiler kullancidan alip dosyaya yazmak
		cout << "Oda Numarasi: ";
		cin >> oda.odaNo;
		OdaBilgisi << oda.odaNo << endl;

		cout << "\nOda Ucreti: ";
		cin >> oda.odaUcreti;
		OdaBilgisi << oda.odaUcreti << endl;
	}
	else throw "dosya acilmadi";
	OdaBilgisi.close();//dosya kapat

}
//oda silme metodu
void odaSil() {
	system("cls");
	//alanlar tanimlama
	string satir, odaNo;
	ifstream OdaBilgisi;//dosya nesnesi olusturma
	ofstream gecici;//gecici dosya nesnesi olusturma
	cout << "2-Oda Sil\n";
	cout << "silmek istediginiz oda numarasi girin: ";
	cin >> odaNo;
	//dosyalar ac
	OdaBilgisi.open("OdaBilgisi.txt");
	gecici.open("gecici.txt");
	//while dongusu dosya kontrol eder
	//getline metodu OdaBilgisi dosyasi icindeki bilgiler satir satir okuyup
	while (getline(OdaBilgisi, satir))
	{
		if (satir != odaNo)//OdaBilgisi dosyadaki record ve kullancidan girilen deger esit olmadigi surece, OdaBilgisi dosyadaki recordler gecici dosyaya aktar
		{
			gecici << satir << endl;//gecici dosyaya record yaz
		}
		if (satir == odaNo)//girilen oda numarasi ve dosyadaki record esit ise bi satir atla
		{
			getline(OdaBilgisi, satir);//sonraki record alir
		}

	}
	OdaBilgisi.close();//dosya kapat
	gecici.close();//dosya kapat
	remove("OdaBilgisi.txt");//eski OdaBilgisi dosyasi sil
	rename("gecici.txt", "OdaBilgisi.txt");//gecici dosya OdaBilgisi dosyaya adlandir.

}
//odalar lisele metodu
void odalarListele() {
	ifstream OdaBilgisi;//dosya nesnesi olusturma
	string satir;//satir alani string turundan tanimlama
	system("cls");
	cout << "3-Odalari Listele\n";
	OdaBilgisi.open("OdaBilgisi.txt", ios::in);//dosya ac
	cout << "Oda numarasi\t\tOda Ucreti\n";
	while (OdaBilgisi >> satir)//dosya son recorda gelene kadar while dongusu while 0 yada 1 donduruyor ona gore calistirdik
	{
		//OdaBilgisi dosyasindan record okuyup consol ekrana yazar
		cout << satir;
		cout << "\t\t\t";
		OdaBilgisi >> satir;
		cout << satir;
		cout << endl;
		
	}
	OdaBilgisi.close();//dosya kapat
	cout << endl;
}


//musteri Ekle metodu
void musteriEkle() {
	string tcNo;//alan tanimlama
	ofstream musteriKayit;//dosya nesnesi tanimlama
	musteriKayit.open("musteriKayit.txt", ios::app);//dosya ac
	system("cls");
	if(musteriKayit.is_open())//dosya acksa gir hatalar dusururuz
	{
		//kullanicidan veri okumak dosyaya yazmak
		cout << "Musteri islemleri\n------------------\n";

		cout << "Musteri Numarasi: ";
		cin >> musteri.Numarasi;
		musteriKayit << musteri.Numarasi << endl;

		cout << "\nMusteri adi: ";
		cin >> musteri.adi;
		musteriKayit << musteri.adi << endl;

		cout << "\nMusteri Soyadi: ";
		cin >> musteri.Soyadi;
		musteriKayit << musteri.Soyadi << endl;

		cout << "\nMusteri TC kimlik No: ";
		cin >> tcNo;
		musteri.setTC(tcNo);//setTc metodu TC_Kimlik alani private tanimladigim icin
		musteriKayit << musteri.GetTC() << endl;//getTC metodu TC_Kimlik numarasi dosyaya yazmak
	}
	else throw "dosya acilmadi";
	musteriKayit.close();//dosya kapat
}
//musteri sil metodu
void musteriSil() {
	system("cls");
	string satir, musteriNo;//alanlar tanimlama
	ifstream musteriKayit;//dosay nesnesi oludturma
	ofstream gecici;//dosay nesnesi oludturma
	cout << "2-Oda Sil\n";
	cout << "silmek istediginiz musteri numarasi girin: ";
	cin >> musteriNo;//aranack silenecek record
	musteriKayit.open("musteriKayit.txt");//musteriKayit dosyasi ac
	gecici.open("gecici.txt");//gecici dosyasi ac
	// while dongusu dosya kontrol eder
	//getline metodu musteriKayit dosyasi icindeki bilgiler satir satir okuyup
	while (getline(musteriKayit, satir))
	{
		if (satir != musteriNo)//musteriKayit dosyadaki record ve kullancidan girilen deger esit olmadigi surece, musteriKayit dosyadaki recordler gecici dosyaya aktar
		{
			gecici << satir << endl;//gecici dosyaya record yaz
		}
		if (satir == musteriNo)//girilen oda numarasi ve dosyadaki record esit ise bi satir atla
		{
			//sonraki 3 recordu alir(burada sonraki 3 satri atlamak icin cagirdik)
			getline(musteriKayit, satir);
			getline(musteriKayit, satir);
			getline(musteriKayit, satir);
		}

	}
	musteriKayit.close();//dosya kapat
	gecici.close();//dosya kapat
	remove("musteriKayit.txt");//eski musteriKayit dosyasi sil
	rename("gecici.txt", "usteriKayit.txt");//gecici dosya musteriKayit dosyaya adlandir.

}
//musteri listele metodu
void musteriListele() {
	ifstream musteriKayit;//dosya nesnesi olusturma
	string satir;//alan tanimlama
	system("cls");
	cout << "3-Musterileri Listele\n";
	musteriKayit.open("musteriKayit.txt", ios::in);//musteriKayit dosya ac
	cout << "Musteri numarasi\t\tMusterinin adi\t\tMusterinin soyadi\t\tMusterinin TC Kimlik\n\n";
	while (musteriKayit >> satir)//dosya son recorda gelene kadar while dongusu while 0 yada 1 donduruyor ona gore calistirdik
	{
		//musteriKayit dosyasindan record okuyup consol ekrana yazar
		cout << satir;
		cout << "\t\t\t\t";
		musteriKayit >> satir;
		cout << satir;
		cout << "\t\t\t";
		musteriKayit >> satir;
		cout << satir;
		cout << "\t\t\t\t";
		musteriKayit >> satir;
		cout << satir;
		cout << endl;
	}
	cout << endl;
	musteriKayit.close();//musteriKayit dosyayi kapat

}


//odaKayitIslemi metodu
void odaKayitIslemi(){
	ofstream odayaMusteri;//dosya nesne olusturmasi
	system("cls");
	cout << "1-Odaya Musteri Ekle\n";
	odayaMusteri.open("odayaMusteri.txt", ios::app);//dosya ac komutu
	if(odayaMusteri.is_open())//dosya acksa gir hatalar dusururuz
	{
		//bilgiler kullancidan alip dosyaya yazmak
		cout << "Oda Numarasi: ";
		cin >> oda.odaNo;
		odayaMusteri << oda.odaNo << endl;

		cout << "Musteri Numarasi: ";
		cin >> musteri.Numarasi;
		odayaMusteri <<musteri.Numarasi << endl;
	}
	else throw "dosya acilmadi";
	odayaMusteri.close();//dosya kapat
}
//odaKayidiSil metodu
void odaKayidiSil() {
	system("cls");
	string satir, odaKaydiNo;//alanlar tanimlama
	ifstream odayaMusteri;//dosay nesnesi oludturma
	ofstream gecici;//dosay nesnesi oludturma
	cout << "2-Oda Sil\n";
	cout << "silmek istediginiz musteri-oda kaydi numarasi girin: ";
	cin >> odaKaydiNo;//aranack silenecek record
	odayaMusteri.open("odayaMusteri.txt");//odayaMusteri dosyasi ac
	gecici.open("gecici.txt");//gecici dosyasi ac
	// while dongusu dosya kontrol eder
	//getline metodu musteriKayit dosyasi icindeki bilgiler satir satir okuyup
	while (getline(odayaMusteri, satir))
	{
		if (satir != odaKaydiNo)//musteriKayit dosyadaki record ve kullancidan girilen deger esit olmadigi surece, musteriKayit dosyadaki recordler gecici dosyaya aktar
		{
			gecici << satir << endl;//gecici dosyaya record yaz
		}
		if (satir == odaKaydiNo)//girilen oda numarasi ve dosyadaki record esit ise bi satir atla
		{
			//sonraki recordu alir(burada sonraki satri atlamak icin cagirdik)
			getline(odayaMusteri, satir);
		}

	}
	odayaMusteri.close();//dosya kapat
	gecici.close();//dosya kapat
	remove("odayaMusteri.txt");//eski odayaMusteri dosyasi sil
	rename("gecici.txt", "odayaMusteri.txt");//gecici dosya odayaMusteri dosyaya adlandir.

}
//odalarKaydiListele metodu
void odalarKaydiListele() {
	ifstream odayaMusteri;//dosya nesnesi olusturma
	string satir;//alan tanimlama
	system("cls");
	cout << "3-Odalarin kaydi Listele\n";
	odayaMusteri.open("odayaMusteri.txt", ios::in);//odayaMusteri dosya ac
	cout << "Oda numarasi\t\tMusteri numarasi\n";
	while (odayaMusteri >> satir)//dosya son recorda gelene kadar while dongusu while 0 yada 1 donduruyor ona gore calistirdik
	{
		//odayaMusteri dosyasindan record okuyup consol ekrana yazar
		cout << satir;
		cout << "\t\t\t";
		odayaMusteri >> satir;
		cout << satir;
		cout << endl;

	}
	odayaMusteri.close();//odayaMusteri dosyayi kapat
	cout << endl;

}


/*display_menu metodu ana ekran yazdiran metod
display_odaIslemi odaIslemi ekrana yazdiran metod
display_musteriIslemi musteriIslemi ekrana yazdiran metod
display_odaKayitIslemi odaKayitIslemi ekrana yazdiran metod
*/
void display_menu(void)
{
	setlocale(LC_ALL, "Turkish");//turkce karakteri okumak icin
	cout << "Otel islemleri\n------------------\n";
	cout << "1-oda islemleri\n";
	cout << "2-Musteri islemleri\n";
	cout << "3-Oda Kayit islemleri\n";
	cout << "99-Cikis\n";
	cout << "Seciminiz : ";
}
void display_odaIslemi(void)
{
	system("cls");
	setlocale(LC_ALL, "Turkish");//turkce karakteri okumak icin
	cout << "\nOda islemleri\n------------------\n";
	cout << "1-Oda Ekle\n";
	cout << "2-Oda Sil\n";
	cout << "3-Odalari Listele\n";
	cout << "99-Ust Menu\n";
	cout << "Seciminiz :";
}
void display_musteriIslemi(void)
{
	system("cls");
	setlocale(LC_ALL, "Turkish");//turkce karakteri okumak icin
	cout << "\nMusteri islemleri\n------------------\n";
	cout << "1-musteri Ekle\n";
	cout << "2-musteri Sil\n";
	cout << "3-Musterileri Listele\n";
	cout << "99-Ust Menu\n";
	cout << "Seciminiz :";
}
void display_odaKayitIslemi(void)
{
	system("cls");
	setlocale(LC_ALL, "Turkish");//turkce karakteri okumak icin
	cout << "\nOda Kayit islemleri\n------------------\n";
	cout << "1-Odaya Musteri Ekle\n";
	cout << "2-Odadan Musterinin kaydi Sil\n";
	cout << "3-Odalarin kaydi Listele\n";
	cout << "99-Ust Menu\n";
	cout << "Seciminiz :";
}


