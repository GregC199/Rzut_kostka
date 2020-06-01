#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //tworzenie diody
    tworz_diode();

    //tworzenie wykresow
    stworz_wykresy();

    //wywolanie inicjalizacji obslugi komunikacji bluetooth
    obsluga_bt();

    //inicjalizacja danych o local hoscie
    this->host = new QBluetoothLocalDevice;

    inicjalizuj_info();

    //nadpisanie/utworzenie pliku log_polaczenia.txt
    zapis.open("log_polaczenia.txt",std::ios_base::out);
    zapis.close();

    //otwarcie strumienia zapisu danych typu dodawania na koniec pliku
    zapis.open("log_polaczenia.txt", std::ios_base::app);

    //otwarcie czytania z pliku log_polaczenia.txt
    czytanie.open("log_polaczenia.txt",std::ios_base::in);

    //rozpoczecie zliczania czasu dla osi czasu na wykresach
    this->pomiar.start();

    //ustawienie menu glownego jako startowego widgetu
    ui->tabWidget->setCurrentWidget(ui->tab);

}


void MainWindow::inicjalizuj_info(){

    ui->parametry_polaczenia->clear();
    this->adres_local_host = this->host->address().toString();
    this->nazwa_local_host = this->host->name();
    this->adres_polaczanego = "Brak połączenia!";
    this->nazwa_polaczanego = "Brak połączenia!";
    this->uuid_polaczonego = "Brak połączenia!";
    this->typ_polaczenia = "Brak połączenia!";
    this->data_polaczenia = "Brak połączenia!";
    ui->parametry_polaczenia->append("Nazwa lokalnego hosta:");
    ui->parametry_polaczenia->append("Adres lokalnego hosta:");
    ui->parametry_polaczenia->append("Nazwa urządzenia połączonego:");
    ui->parametry_polaczenia->append("Adres urządzenia połączonego:");
    ui->parametry_polaczenia->append("Uuid urządzenia połączonego:");
    ui->parametry_polaczenia->append("Typ połączenia:");
    ui->parametry_polaczenia->append("Czas nawiązania połączenia:");


    informacje_bluetooth();
}

void MainWindow::informacje_bluetooth(){

    ui->informacje_o_polaczeniu->clear();

    ui->informacje_o_polaczeniu->append(this->nazwa_local_host);
    ui->informacje_o_polaczeniu->append(this->adres_local_host);
    ui->informacje_o_polaczeniu->append(this->nazwa_polaczanego);
    ui->informacje_o_polaczeniu->append(this->adres_polaczanego);
    ui->informacje_o_polaczeniu->append(this->uuid_polaczonego );
    ui->informacje_o_polaczeniu->append(this->typ_polaczenia);
    ui->informacje_o_polaczeniu->append(this->data_polaczenia);

}


void MainWindow::wczytanie_danych_z_logu(unsigned long long czas_zmierzony){

    //zmienne pomocnicze do realizacji zczytywania danych
    char a[10],b[10],c[10],d[10],e[10],f[10],g[10],h[10];
    float  acc_x = 0.0;
    float  acc_y = 0.0;
    float  acc_z = 0.0;
    float  gyr_x = 0.0;
    float  gyr_y = 0.0;
    float  gyr_z = 0.0;
    float  roll = 0.0;
    float  pitch = 0.0;

    //zczytywanie kolejnych danych z pliku
    czytanie >> a;
    czytanie >> acc_x;
    czytanie >> b;
    czytanie >> acc_y;
    czytanie >> c;
    czytanie >> acc_z;
    czytanie >> d;
    czytanie >> gyr_x;
    czytanie >> e;
    czytanie >> gyr_y;
    czytanie >> f;
    czytanie >> gyr_z;
    czytanie >> g;
    czytanie >> roll;
    czytanie >> h;
    czytanie >> pitch;


    aktualizuj_wykres(acc_x,acc_y,acc_z,gyr_x,gyr_y,gyr_z,roll,pitch,czas_zmierzony);

}

void MainWindow::aktualizuj_wykres(float a_x,float a_y,float a_z,float g_x,float g_y,float g_z,float rkom,float pkom, unsigned long long czas){

    //os czasu - zmienne pomocnicze sluzace do jej przesuwania
    long double test = ((long double)czas)/1000;
    long double koniec = 0.0;
    long double memory;
    long double poczatek = 0.0;

    //przesuniecie osi czasu
    while(koniec < test){
        memory=koniec;
        koniec=koniec+50;
    }
    if(koniec>50.0)poczatek = ceil(memory);

    //sprawdzenie czy nastąpiła zmiana osi czasy
    if(timeline_acc_x->max() != ceil(koniec)){

        //jesli tak to zmieniamy zakres kazdej z nich
        this->timeline_acc_x->setRange(poczatek,ceil(koniec));
        this->timeline_acc_y->setRange(poczatek,ceil(koniec));
        this->timeline_acc_z->setRange(poczatek,ceil(koniec));
        this->timeline_gyr_x->setRange(poczatek,ceil(koniec));
        this->timeline_gyr_y->setRange(poczatek,ceil(koniec));
        this->timeline_gyr_z->setRange(poczatek,ceil(koniec));
    }

    //dodawanie nowych punktow na wykresie
    //accx
    this->series_acc_wykres_x->append(test,a_x);

    //accy
    this->series_acc_wykres_y->append(test,a_y);

    //accz
    this->series_acc_wykres_z->append(test,a_z);

    //gyrx
    this->series_gyr_wykres_x->append(test,g_x);

    this->series_kom_wykres_x->append(test,rkom);

    //gyry
    this->series_gyr_wykres_y->append(test,g_y);

    this->series_kom_wykres_y->append(test,pkom);

    //gyrz
    this->series_gyr_wykres_z->append(test,g_z);

}

void MainWindow::resizeEvent(QResizeEvent* event){

    QMainWindow::resizeEvent(event);

    //dostosowanie wielkosci wykresow do wielkosci parent widgetu
    //podczas zmiany rozmiaru okienka
    //acc x,y,z
    this->view_acc_wykres_x->resize(this->view_acc_wykres_x->parentWidget()->size());
    this->view_acc_wykres_y->resize(this->view_acc_wykres_y->parentWidget()->size());
    this->view_acc_wykres_z->resize(this->view_acc_wykres_z->parentWidget()->size());

    //gyr x,y,z
    this->view_gyr_wykres_x->resize(this->view_gyr_wykres_x->parentWidget()->size());
    this->view_gyr_wykres_y->resize(this->view_gyr_wykres_y->parentWidget()->size());
    this->view_gyr_wykres_z->resize(this->view_gyr_wykres_z->parentWidget()->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

