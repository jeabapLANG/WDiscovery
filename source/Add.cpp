#include "../include/Add.h" //Include add definition
#include "./ui_Add.h" //Include add interface

Add::Add(QWidget* parent, User* user, Database* database, Log* logger) : //Class constructor
    QDialog(parent), //Set the parent window
    _interface(new Ui::Add), //Set the ui interface
    _database(database), //Set the window database
    _logger(logger), //Set the window logger
    _user(user) { //Set the window user
        this->_logger->record("Setting up .ui for add window ...");
        this->_interface->setupUi(this); //Setup the window interface
        this->_logger->record("UI setup for add window !");
}
Add::~Add(void) { //Class destructor
    this->_logger->record("Add::~Add() called");
    this->_logger->record("Destroying add window ...");
    delete this->_interface; //Destroy the interface
    this->_logger->record("Add window destroyed !");
}

void Add::clear(void) { //Clear the text fields
    this->_logger->record("Add::clear() called");

    this->_logger->record("Clearing text fields ...");
    this->_interface->lineEdit_Name->setText(""); //Clear
    this->_interface->lineEdit_Type->setText(""); //Clear
    this->_interface->textEdit_Description->setText(""); //Clear
    this->_logger->record("Text fields cleared !");
}

void Add::on_button_Ok_clicked() { //On button ok clicked
    this->_logger->record("Add::on_button_Ok_clicked() called");

    const QString name = this->_interface->lineEdit_Name->text(); //Get the name for the word
    const QString type = this->_interface->lineEdit_Type->text(); //Get the type for the word
    const QString description = this->_interface->textEdit_Description->toPlainText(); //Get the description for the word

    this->_database->addWord(this->_user->getUID(), name, type, description); //Add the word to the database
    this->_user->incrementWord(); //Add one word to the user

    QMessageBox::information(this, "Added", "<FONT COLOR='#ffffff'>The word named " + name + " was added !</FONT>"); //Alert

    this->_logger->record("Hidding add window ...");
    this->hide(); //Hide the window
    this->_logger->record("Add window hidden !");

    this->clear(); //Clear the text fields
}
void Add::on_button_Cancel_clicked() {  //On button cancel clicked
    this->_logger->record("Add::on_button_Cancel_clicked() called");

    this->_logger->record("Hidding add window ...");
    this->hide(); //Hide the window
    this->_logger->record("Add window hidden !");
}

