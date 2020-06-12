#include "mainwindow.h"

void MainWindow::obsluga_bt(){

    this->discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(this->discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(captureDeviceProperties(QBluetoothDeviceInfo)));

    connect(this->discoveryAgent, SIGNAL(finished()),this, SLOT(searchingFinished()));

    connect(this->socket, SIGNAL(connected()),this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(disconnected()),this, SLOT(connectionInterrupted()));
    connect(this->socket, SIGNAL(readyRead()),this, SLOT(socketReadyToRead()));
    ui->button_rozlacz->setEnabled(false);
}

void MainWindow::on_button_wyszukaj_clicked()
{
    ui->list_urzadzen->clear();
    ui->button_wyszukaj->setEnabled(false);

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
  ui->button_wyszukaj->setEnabled(true);

}

void MainWindow::on_button_polacz_clicked()
{
    QString comboBoxQString = ui->list_urzadzen->currentText();
    QStringList portList = comboBoxQString.split(" ");
    QString deviceAddres = portList.last();
    QString deviceName = portList.first();

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));

    //zapis danych do informacji o polaczeniu
    this->uuid_polaczonego = serviceUuid;
    this->adres_polaczanego = deviceAddres;
    this->typ_polaczenia = "Read/Write";
    this->nazwa_polaczanego = deviceName;

    this->socket->connectToService(QBluetoothAddress(deviceAddres),QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);
    this->addToLogs("Laczenie z urządzeniem o nazwie: " + deviceName + " i adresie: " + deviceAddres);

}

void MainWindow::on_button_rozlacz_clicked()
{
    this->addToLogs("Zamykam polaczenie");
    this->socket->disconnectFromService();
}

void MainWindow::connectionEstablished() {

    //zapis daty nawiazania polaczenia
    this->data_polaczenia = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");

    this->addToLogs("Polaczenie ustanowione");

    //deaktywacja przycisku połącz
    ui->button_polacz->setEnabled(false);
    ui->button_rozlacz->setEnabled(true);

    //aktualizacja informacji bluetooth
    informacje_bluetooth();

    //zapalanie zielonej
    zapal_zielone();


}

void MainWindow::connectionInterrupted() {
    this->addToLogs("Polaczenie przerwane");
    ui->button_polacz->setEnabled(true);
    ui->button_rozlacz->setEnabled(false);

    //reset informacji o polaczeniu do poczatkowych wartosci
    inicjalizuj_info();

    zapal_czerwone();
}

void MainWindow::socketReadyToRead() {

    unsigned long long zmierzony;
    while(this->socket->canReadLine()) {

        //zapis ilosci milisekund uplynietych od startu programu
        zmierzony = (unsigned long long) this->pomiar.elapsed();

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
