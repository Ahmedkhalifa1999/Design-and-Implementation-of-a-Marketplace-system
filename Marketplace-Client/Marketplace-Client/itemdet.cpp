#include "itemdet.h"
#include "shop.h"
#include "ui_itemdet.h"
#include "datamanager.h"
//#include"shop.h"

Itemdet::Itemdet(DataManager *dataManager, unsigned int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Itemdet)
{
    this->dm = dataManager;
    QObject::connect(this->dm, &DataManager::getItemData_signal, this, &Itemdet::getItemData_slot);
    ui->setupUi(this);
    dm->getItemData(ID);

    QList<QString> combolist={"1","2","3","4","5","6","7","8","9","10"};
     ui->comboBox->addItems(combolist);
     c.quantity=1;
     c.ID=ID;
}

Itemdet::~Itemdet()
{
    delete ui;
}

void Itemdet::on_shopButton_clicked()
{
     hide();
}


void Itemdet::on_addCartButton_clicked()
{
    c.quantity=quan;
   dm->addToCart(c);
}

void Itemdet::getItemData_slot(DetailedItem result){
    item_name = result.name;
    item_description = result.description;
    if (!result.images.empty()) item_images.push_back(result.images[0]);
    else item_images.push_back(QPixmap());
    item_price=result.price;

    QLabel* labpic = new QLabel(this);
    labpic->setPixmap(item_images[0].scaled(300,600,Qt::KeepAspectRatio));
    ui->gridLayout->addWidget(labpic,0,0,-1,1);

    QLabel* labname = new QLabel(this);
    labname->setText(item_name);
    labname->setStyleSheet("font: 700 14pt");
    ui->gridLayout->addWidget(labname,0,1);

    QLabel* lab1 = new QLabel(this);
    lab1->setText("Description:");
    lab1->setStyleSheet("font: 700 10pt");
    ui->gridLayout->addWidget(lab1,1,1);

    QLabel* labdis = new QLabel(this);
    labdis->setText(item_description);
    ui->gridLayout->addWidget(labdis,2,1);

    QLabel* lab2 = new QLabel(this);
    lab2->setText("Price:");
    lab2->setStyleSheet("font: 700 10pt");
    ui->gridLayout->addWidget(lab2,3,1);

    QLabel* labprice = new QLabel(this);
    labprice->setText(QString::number(item_price.pounds)+"."+QString::number(item_price.piasters));
    ui->gridLayout->addWidget(labprice,4,1);
}

void Itemdet::on_comboBox_currentTextChanged(const QString &arg1)
{
    quan = arg1.toUInt();
}

