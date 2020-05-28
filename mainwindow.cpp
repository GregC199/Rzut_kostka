#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //tworzenie wykresow
    stworz_wykresy();

    //wywolanie inicjalizacji obslugi komunikacji bluetooth
    obsluga_bt();

    //nadpisanie/utworzenie pliku log_polaczenia.txt
    zapis.open("log_polaczenia.txt",std::ios_base::out);
    zapis.close();

    //otwarcie strumienia zapisu danych typu dodawania na koniec pliku
    zapis.open("log_polaczenia.txt", std::ios_base::app);

    //otwarcie czytania z pliku log_polaczenia.txt
    czytanie.open("log_polaczenia.txt",std::ios_base::in);

    //rozpoczecie zliczania czasu dla osi czasu na wykresach
    this->pomiar.start();

}
void MainWindow::obsluga_bt(){

    this->discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(this->discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(captureDeviceProperties(QBluetoothDeviceInfo)));

    connect(this->discoveryAgent, SIGNAL(finished()),this, SLOT(searchingFinished()));

    connect(this->socket, SIGNAL(connected()),this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(disconnected()),this, SLOT(connectionInterrupted()));
    connect(this->socket, SIGNAL(readyRead()),this, SLOT(socketReadyToRead()));
}

void MainWindow::on_button_wyszukaj_clicked()
{
    ui->list_urzadzen->clear();

    this->addToLogs("Szukam urzadzen...");
    ui->button_wyszukaj->setEnabled(false);

    this->discoveryAgent->start();
}

void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->log_polaczenie->append(currentDateTime + "\t" + message);
}

void MainWindow::captureDeviceProperties(const QBluetoothDeviceInfo &device) {
  ui->list_urzadzen->addItem(device.name() + " " + device.address().toString());
  this->addToLogs("Znaleziono urządzenie o nazwie: " + device.name() + " i adresie: " + device.address().toString());
}
void MainWindow::searchingFinished() {
  ui->button_wyszukaj->setEnabled(true);
  this->addToLogs("Wyszukiwanie zakonczone");
}

void MainWindow::on_button_polacz_clicked()
{
    QString comboBoxQString = ui->list_urzadzen->currentText();
    QStringList portList = comboBoxQString.split(" ");
    QString deviceAddres = portList.last();

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    this->socket->connectToService(QBluetoothAddress(deviceAddres),QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);
    this->addToLogs("Laczenie z urządzeniem o nazwie: " + portList.first() + " i adresie: " + deviceAddres);

}

void MainWindow::on_button_rozlacz_clicked()
{
    this->addToLogs("Zamykam polaczenie");
    this->socket->disconnectFromService();
}

void MainWindow::connectionEstablished() {
  this->addToLogs("Polaczenie ustanowione");
}

void MainWindow::connectionInterrupted() {
  this->addToLogs("Polaczenie przerwane");
}

void MainWindow::socketReadyToRead() {

    unsigned long long zmierzony;
    while(this->socket->canReadLine()) {

        //zapis ilosci milisekund uplynietych od startu programu
        zmierzony = (unsigned long long) this->pomiar.elapsed();
        //std::cout<<zmierzony<<std::endl;

        //zczytanie danych z socketu bluetooth
        QString line = this->socket->readLine();

        //zmienna pomocniczna do zapisu danych do logu polaczenia
        std::string zczytanie;

        //przeksztalcenie QString do std::string
        zczytanie = line.toStdString();

        //zapis danych z bluetooth do pliku
        zapis << zczytanie<<std::endl;

        wczytanie_danych_z_logu(zmierzony);


        //dodanie terminatora na koniec
        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);

        this->addToLogs(line.left(pos));
      }
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

    //sscanf(zczytanie.c_str(),"%3s %lf %3s %lf %3s %lf %3s %lf %3s %lf %3s %lf %5s %lf %5s %lf", a,&acc_x,b,&acc_y,c,&acc_z,d,&gyr_x,e,&gyr_y,f,&gyr_z,g,&roll,h,&pitch);

    //sscanf(zczytanie,"Xg: %f Yg: %f Zg: %f Xa: %f Ya: %f Za: %f Rkom: %f Pkom: %f", &acc_x,&acc_y,&acc_z,&gyr_x,&gyr_y,&gyr_z,&roll,&pitch);

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
    //std::cout<<"test: "<<test<<" ax: "<<a_x<<" "<<std::endl;

    //sprawdzenie czy nastąpiła zmiana osi czasy
    if(timeline_acc_x->max() != ceil(koniec)){

        //std::cout<<"zmieniam wielkosc!\n";
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

void MainWindow::stworz_wykresy(){

    //tworzenie serii
    //acc x,y,z
    this->series_acc_wykres_x = new QLineSeries();
    this->series_acc_wykres_x->append(0,0);

    this->series_acc_wykres_y = new QLineSeries();
    this->series_acc_wykres_y->append(0,0);

    this->series_acc_wykres_z = new QLineSeries();
    this->series_acc_wykres_z->append(0,0);

    //gyr x, roll, y, pitch, z
    this->series_gyr_wykres_x = new QLineSeries();
    this->series_gyr_wykres_x->append(0,0);

    this->series_kom_wykres_x = new QLineSeries();
    this->series_kom_wykres_x->append(0,0);

    this->series_gyr_wykres_y = new QLineSeries();
    this->series_gyr_wykres_y->append(0,0);


    this->series_kom_wykres_y = new QLineSeries();
    this->series_kom_wykres_y->append(0,0);

    this->series_gyr_wykres_z = new QLineSeries();
    this->series_gyr_wykres_z->append(0,0);


    //tworzenie osi czasu acc x,y,z
    this->timeline_acc_x = new QValueAxis;
    this->timeline_acc_x->setLabelFormat("%.2f");
    this->timeline_acc_x->setRange(0,10);
    this->timeline_acc_x->setTickCount(6);


    this->timeline_acc_y = new QValueAxis;
    this->timeline_acc_y->setLabelFormat("%.2f");
    this->timeline_acc_y->setRange(0,10);
    this->timeline_acc_y->setTickCount(6);


    this->timeline_acc_z = new QValueAxis;
    this->timeline_acc_z->setLabelFormat("%.2f");
    this->timeline_acc_z->setRange(0,10);
    this->timeline_acc_z->setTickCount(6);

    //tworzenie osi czasu gyr x,y,z
    this->timeline_gyr_x = new QValueAxis;
    this->timeline_gyr_x->setLabelFormat("%.2f");
    this->timeline_gyr_x->setRange(0,10);
    this->timeline_gyr_x->setTickCount(6);


    this->timeline_gyr_y = new QValueAxis;
    this->timeline_gyr_y->setLabelFormat("%.2f");
    this->timeline_gyr_y->setRange(0,10);
    this->timeline_gyr_y->setTickCount(6);


    this->timeline_gyr_z = new QValueAxis;
    this->timeline_gyr_z->setLabelFormat("%.2f");
    this->timeline_gyr_z->setRange(0,10);
    this->timeline_gyr_z->setTickCount(6);


    //tworzenie osi wartosci acc x,y,z
    QValueAxis* acc_x_wartosci_y = new QValueAxis;
    acc_x_wartosci_y->setLabelFormat("%.3f");
    acc_x_wartosci_y->setRange(-4,4);
    acc_x_wartosci_y->setTickCount(9);


    QValueAxis* acc_y_wartosci_y = new QValueAxis;
    acc_y_wartosci_y->setLabelFormat("%.3f");
    acc_y_wartosci_y->setRange(-4,4);
    acc_y_wartosci_y->setTickCount(9);


    QValueAxis* acc_z_wartosci_y = new QValueAxis;
    acc_z_wartosci_y->setLabelFormat("%.3f");
    acc_z_wartosci_y->setRange(-4,4);
    acc_z_wartosci_y->setTickCount(9);


    //tworzenie osi wartosci gyr x,y,z
    QValueAxis* gyr_x_wartosci_y = new QValueAxis;
    gyr_x_wartosci_y->setLabelFormat("%.2f");
    gyr_x_wartosci_y->setRange(-360,360);
    gyr_x_wartosci_y->setTickCount(9);

    QValueAxis* gyr_y_wartosci_y = new QValueAxis;
    gyr_y_wartosci_y->setLabelFormat("%.2f");
    gyr_y_wartosci_y->setRange(-360,360);
    gyr_y_wartosci_y->setTickCount(9);



    QValueAxis* gyr_z_wartosci_y = new QValueAxis;
    gyr_z_wartosci_y->setLabelFormat("%.2f");
    gyr_z_wartosci_y->setRange(-360,360);
    gyr_z_wartosci_y->setTickCount(9);


    //stworzenie wykresu liniowego z serii - acc_x
    this->line_acc_wykres_x = new QChart();

    //dodanie osi
    this->line_acc_wykres_x->addAxis(acc_x_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_x->addAxis(this->timeline_acc_x,Qt::AlignBottom);

    //dodanie serii danych
    this->line_acc_wykres_x->addSeries(this->series_acc_wykres_x);

    //dodanie tytulu wykresu
    this->line_acc_wykres_x->setTitle("Zczytania wzdłuż osi X");

    //wylaczenie legendy
    this->line_acc_wykres_x->legend()->hide();
    //this->line_acc_wykres_x-> createDefaultAxes();



    //kolejne tworzenia wykresow liniowych dla kolejnych zczytan osi - acc_y
    this->line_acc_wykres_y = new QChart();

    this->line_acc_wykres_y->addAxis(acc_y_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_y->addAxis(this->timeline_acc_y,Qt::AlignBottom);

    this->line_acc_wykres_y->addSeries(this->series_acc_wykres_y);

    this->line_acc_wykres_y->setTitle("Zczytania wzdłuż osi Y");

    this->line_acc_wykres_y->legend()->hide();

    //this->line_acc_wykres_y->createDefaultAxes();


    //acc_z
    this->line_acc_wykres_z = new QChart();

    this->line_acc_wykres_z->addAxis(acc_z_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_z->addAxis(this->timeline_acc_z,Qt::AlignBottom);

    this->line_acc_wykres_z->addSeries(this->series_acc_wykres_z);

    this->line_acc_wykres_z->setTitle("Zczytania wzdłuż osi Z");

    this->line_acc_wykres_z->legend()->hide();

    //this->line_acc_wykres_z->createDefaultAxes();


    //gyr_x
    this->line_gyr_wykres_x = new QChart();

    this->line_gyr_wykres_x->addAxis(gyr_x_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_x->addAxis(this->timeline_gyr_x,Qt::AlignBottom);

    this->line_gyr_wykres_x->addSeries(this->series_gyr_wykres_x);
    this->line_gyr_wykres_x->addSeries(this->series_kom_wykres_x);

    this->line_gyr_wykres_x->setTitle("Zczytania wzdłuż osi X");

    this->line_gyr_wykres_x->legend()->hide();

    //this->line_gyr_wykres_x->createDefaultAxes();




    //gyr_y
    this->line_gyr_wykres_y = new QChart();

    this->line_gyr_wykres_y->addAxis(gyr_y_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_y->addAxis(this->timeline_gyr_y,Qt::AlignBottom);

    this->line_gyr_wykres_y->addSeries(this->series_gyr_wykres_y);
    this->line_gyr_wykres_y->addSeries(this->series_kom_wykres_y);

    this->line_gyr_wykres_y->setTitle("Zczytania wzdłuż osi Y");

    this->line_gyr_wykres_y->legend()->hide();

    //this->line_gyr_wykres_y->createDefaultAxes();




    //gyr_z
    this->line_gyr_wykres_z = new QChart();

    this->line_gyr_wykres_z->addAxis(gyr_z_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_z->addAxis(this->timeline_gyr_z,Qt::AlignBottom);

    this->line_gyr_wykres_z->addSeries(this->series_gyr_wykres_z);

    this->line_gyr_wykres_z->setTitle("Zczytania wzdłuż osi Z");

    this->line_gyr_wykres_z->legend()->hide();

    //this->line_gyr_wykres_z->createDefaultAxes();




    //laczenie osi czasu z seriami danych
    this->series_acc_wykres_x->attachAxis(this->timeline_acc_x);
    this->series_acc_wykres_y->attachAxis(this->timeline_acc_y);
    this->series_acc_wykres_z->attachAxis(this->timeline_acc_z);
    this->series_gyr_wykres_x->attachAxis(this->timeline_gyr_x);
    this->series_kom_wykres_x->attachAxis(this->timeline_gyr_x);
    this->series_gyr_wykres_y->attachAxis(this->timeline_gyr_y);
    this->series_kom_wykres_y->attachAxis(this->timeline_gyr_y);
    this->series_gyr_wykres_z->attachAxis(this->timeline_gyr_z);

    //laczenie osi wartosci z seriami danych
    this->series_acc_wykres_x->attachAxis(acc_x_wartosci_y);
    this->series_acc_wykres_y->attachAxis(acc_y_wartosci_y);
    this->series_acc_wykres_z->attachAxis(acc_z_wartosci_y);
    this->series_gyr_wykres_x->attachAxis(gyr_x_wartosci_y);
    this->series_kom_wykres_x->attachAxis(gyr_x_wartosci_y);
    this->series_gyr_wykres_y->attachAxis(gyr_y_wartosci_y);
    this->series_kom_wykres_y->attachAxis(gyr_y_wartosci_y);
    this->series_gyr_wykres_z->attachAxis(gyr_z_wartosci_y);

    //wyswietlanie utworzonych wykresow - acc_x
    this->view_acc_wykres_x = new QChartView(this->line_acc_wykres_x);
    this->view_acc_wykres_x->setRenderHint(QPainter::Antialiasing);
    this->view_acc_wykres_x->setParent(ui->acc_wykres_x);

    //acc_y
    this->view_acc_wykres_y = new QChartView(this->line_acc_wykres_y);
    this->view_acc_wykres_y->setRenderHint(QPainter::Antialiasing);
    this->view_acc_wykres_y->setParent(ui->acc_wykres_y);

    //acc_z
    this->view_acc_wykres_z = new QChartView(this->line_acc_wykres_z);
    this->view_acc_wykres_z->setRenderHint(QPainter::Antialiasing);
    this->view_acc_wykres_z->setParent(ui->acc_wykres_z);

    //gyr_x
    this->view_gyr_wykres_x = new QChartView(this->line_gyr_wykres_x);
    this->view_gyr_wykres_x->setRenderHint(QPainter::Antialiasing);
    this->view_gyr_wykres_x->setParent(ui->gyr_wykres_x);

    //gyr_y
    this->view_gyr_wykres_y = new QChartView(this->line_gyr_wykres_y);
    this->view_gyr_wykres_y->setRenderHint(QPainter::Antialiasing);
    this->view_gyr_wykres_y->setParent(ui->gyr_wykres_y);

    //gyr_z
    this->view_gyr_wykres_z = new QChartView(this->line_gyr_wykres_z);
    this->view_gyr_wykres_z->setRenderHint(QPainter::Antialiasing);
    this->view_gyr_wykres_z->setParent(ui->gyr_wykres_z);

    /*
    //dostosowanie startowego rozmiaru wykresow
    //QResizeEvent* start1;
    //start1 = new QResizeEvent(view_acc_wykres_x->parentWidget()->size(),view_acc_wykres_x->size());
    this->view_acc_wykres_x->setGeometry(this->view_acc_wykres_x->parentWidget()->geometry());

    //QResizeEvent* start2;
    //start2 = new QResizeEvent(view_acc_wykres_y->parentWidget()->size(),view_acc_wykres_y->size());
    this->view_acc_wykres_y->setGeometry(this->view_acc_wykres_y->parentWidget()->geometry());

    //QResizeEvent* start3;
    //start3 = new QResizeEvent(view_acc_wykres_z->parentWidget()->size(),view_acc_wykres_z->size());
    this->view_acc_wykres_z->setGeometry(this->view_acc_wykres_z->parentWidget()->geometry());

    //QResizeEvent* start4;
    //start4 = new QResizeEvent(view_gyr_wykres_x->parentWidget()->size(),view_gyr_wykres_x->size());
    this->view_gyr_wykres_x->setGeometry(this->view_gyr_wykres_x->parentWidget()->geometry());

    //QResizeEvent* start5;
    //start5 = new QResizeEvent(view_gyr_wykres_y->parentWidget()->size(),view_gyr_wykres_y->size());
    this->view_gyr_wykres_y->setGeometry(this->view_gyr_wykres_y->parentWidget()->geometry());

    //QResizeEvent* start6;
    //tart6 = new QResizeEvent(view_gyr_wykres_z->parentWidget()->size(),view_gyr_wykres_z->size());
    this->view_gyr_wykres_z->setGeometry(this->view_gyr_wykres_z->parentWidget()->geometry());
    QResizeEvent* start;
    start = new QResizeEvent(this->size(),this->size());
    QMainWindow::resizeEvent(start);*/
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

