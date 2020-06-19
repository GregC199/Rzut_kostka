#include "mainwindow.h"
/*!
 * \brief Inicjalizacja obsługi bluetooth
 *
 * Funkcje czy też połączenia wywoływane w momencie konstrukcji aplikacji.
 */
void MainWindow::obsluga_bt(){

    //Inicjalizacja modułu służącego do wyszukiwania urządzeń
    this->discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    //Inicjalizacja socketu do nawiązywania połączenia
    this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    //Połączenie sygnału podczas wykrycia nowego urządzenia z zapisaniem jego parametrów
    connect(this->discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(captureDeviceProperties(QBluetoothDeviceInfo)));

    //Połączenie sygnału zakończenia wyszukiwania urządzeń z końcem wyszukiwania
    connect(this->discoveryAgent, SIGNAL(finished()),this, SLOT(searchingFinished()));

    //Sygnały i sockety odpowiedzialne za połączenie, rozłączenie oraz otrzymanie wiadomości
    connect(this->socket, SIGNAL(connected()),this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(disconnected()),this, SLOT(connectionInterrupted()));
    connect(this->socket, SIGNAL(readyRead()),this, SLOT(socketReadyToRead()));

    //Zablokowanie przycisku Rozłącz na początek działania programu
    ui->button_rozlacz->setEnabled(false);
}
/*!
 * \brief Slot odpowiedzialny za obsługę wyszukiwania urządzeń
 *
 * Kolejno czyści listę urządzeń, następnie wyłącza przycisk Wyszukaj urządzenie,
 * potem dodaje informację na temat rozpoczęcia wyszukiwania urządzeń do logu oraz
 * inicjuje samo wyszukiwanie.
 */
void MainWindow::on_button_wyszukaj_clicked()
{
    ui->list_urzadzen->clear();
    ui->button_wyszukaj->setEnabled(false);

    this->addToLogs("Szukam urzadzen...");
    ui->button_wyszukaj->setEnabled(false);

    this->discoveryAgent->start();
}

/*!
 * \brief Funkcja odpowiedzialna za dodanie informacji do pola Log połączenia
 *
 * Dodaje informacje na temat połączenia wraz z bieżącą datą, co do sekundy.
 */
void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->log_polaczenie->append(currentDateTime + "\t" + message);
}

/*!
 * \brief Slot odpowiedzialny za przechwycenie informacji na temat wykrywtego urządzenia
 *
 * Dodaje informacje na temat połączenia do Logu połączenia oraz dodaje go do listy urządzeń.
 */
void MainWindow::captureDeviceProperties(const QBluetoothDeviceInfo &device) {
  ui->list_urzadzen->addItem(device.name() + " " + device.address().toString());
  this->addToLogs("Znaleziono urządzenie o nazwie: " + device.name() + " i adresie: " + device.address().toString());
}

/*!
 * \brief Slot odpowiedzialny za przechwycenie sygnału zakończenia wyszukiwania
 *
 * Odblokowywuje przycisk do wyszukiwania, dodaje informację na temat zakończenia wyszukiwania do Logu połączenia.
 */
void MainWindow::searchingFinished() {
  ui->button_wyszukaj->setEnabled(true);
  this->addToLogs("Wyszukiwanie zakonczone");

}
/*!
 * \brief Slot odpowiedzialny za przechwycenie sygnału inicjacji połączenia
 *
 * Inicjuje połączenie, dodaje informacje na temat nawiązywanego połączenia i dodaje je do
 * pola tekstowego Informacje o połączeniu oraz dodaje informacje na temat wykonywanych akcji
 * do Logu połączenia.
 */
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
/*!
 * \brief Slot odpowiedzialny za przechwycenie sygnału wywołania zakończenia połączenia
 *
 * Wpierw wysyła informację o kończeniu połączenia do urządzenia, a następnie odłącza socket od serwisu.
 */
void MainWindow::on_button_rozlacz_clicked()
{
    QString wyslij_wiad;

    wyslij_wiad = "0\n";

    this->socket->write(wyslij_wiad.toStdString().c_str());

    this->addToLogs("Zamykam polaczenie");
    this->socket->disconnectFromService();
}
/*!
 * \brief Slot nawiązania połączenia
 *
 * Dodaje informację o dacie nawiązania połączenia co do sekundy do Informacji o połączeniu
 * oraz Logu połączenia. Startuje odliczanie dt dla odczytywania wartości z pliku log_polaczenia.txt .
 * Następnnie wyłącza przycisk połącz i aktywuje przycisk rozłącz oraz zapala diody zielone.
 */
void MainWindow::connectionEstablished() {

    //zapis daty nawiazania polaczenia
    this->data_polaczenia = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");

    this->addToLogs("Polaczenie ustanowione");

    QString wyslij_wiad;

    wyslij_wiad = "1\n";

    //rozpoczynamy odliczanie
     dt.start();

    this->socket->write(wyslij_wiad.toStdString().c_str());

    //deaktywacja przycisku połącz
    ui->button_polacz->setEnabled(false);
    ui->button_rozlacz->setEnabled(true);

    //aktualizacja informacji bluetooth
    informacje_bluetooth();

    //zapalanie zielonej
    zapal_zielone();


}
/*!
 *
 *
 */
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
