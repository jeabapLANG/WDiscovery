#include "../include/Update.h" //Include update definition
#include "./ui_Update.h" //Include update interface

Update::Update(QWidget* parent, User* user, Database* database, Log* logger) : //Class constructor
    QDialog(parent), //Set the parent window
    _interface(new Ui::Update), //Set the ui interface
    _database(database), //Set the window database
    _user(user), //Set the window user
    _logger(logger){ //Set the window logger
        this->_logger->record("Setting up .ui for add window ...");
        this->_interface->setupUi(this); //Setup the window interface
        this->_logger->record("UI setup for add window !");
}
Update::~Update(void) { //Class destructor
    this->_logger->record("Delete::~Delete() called");
    this->_logger->record("Destroying delete window ...");
    delete this->_interface; //Destroy the interface
    delete this->_words; //Clean the list of words
    this->_logger->record("Delete window destroyed !");
}

void Update::setList(QList<Word>* words) { //Set the list of words
    this->_words = words; //Set the words

    this->_interface->comboBox_UID->clear(); //Clear the combo box

    for (int i = 0; i < this->_words->count(); i++) {
        Word word = this->_words->at(i); //Get the word at the current index

        if (word.getAuthor() == this->_user->getUID()) { //If the user is the author of the word
            this->_interface->comboBox_UID->addItem(QString::number(word.getUID())); //Add the word name to the box
        }
    }
}

void Update::on_button_Ok_clicked() { //On button ok clicked
    this->_logger->record("Delete::on_button_Ok_clicked() called");

    int uid = this->_interface->comboBox_UID->currentText().toInt(); //Get the current selected uid

    const QString name = this->_interface->lineEdit_Name->text(); //Get the current name
    const QString type = this->_interface->lineEdit_Type->text(); //Get the current type
    const QString description = this->_interface->textEdit_Description->toPlainText(); //Get the current description

    this->_database->updateWord(uid, name, type, description); //Add the word to the database

    QMessageBox::information(this, "Updated", "<FONT COLOR='#ffffff'>The word named " + name + " with the uid " + QString::number(uid) + " was updated !</FONT>"); //Alert

    this->_logger->record("Hidding delete window ...");
    this->hide(); //Hide the window
    this->_interface->comboBox_UID->clear(); //Clear the combo box
    this->_logger->record("Delete window hidden !");
}
void Update::on_button_Cancel_clicked() {  //On button cancel clicked
    this->_logger->record("Delete::on_button_Cancel_clicked() called");

    this->_logger->record("Hidding delete window ...");
    this->hide(); //Hide the window
    this->_logger->record("Delete window hidden !");
}

void Update::on_comboBox_UID_currentIndexChanged(int index) { //On index changed
    this->_logger->record("Update::on_comboBox_UID_currentIndexChanged() called");

    if(index < 0) return; //Correction

    Word word = this->_words->at(index); //Get the selected word

    this->_interface->lineEdit_Name->setText(word.getName()); //Update the word name
    this->_interface->lineEdit_Type->setText(word.getType()); //Update the word type
    this->_interface->textEdit_Description->setText(word.getDescription()); //Update the word description
}
