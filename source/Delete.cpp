#include "../include/Delete.h" //Include delete definition
#include "./ui_Delete.h" //Include delete interface

Delete::Delete(QWidget* parent, User* user, Database* database, Log* logger) : //Class constructor
    QDialog(parent), //Set the parent window
    _interface(new Ui::Delete), //Set the ui interface
    _database(database), //Set the window database
    _logger(logger), //Set the window logger
    _user(user) { //Set the window logger
        this->_logger->record("Setting up .ui for add window ...");
        this->_interface->setupUi(this); //Setup the window interface
        this->_logger->record("UI setup for add window !");
}
Delete::~Delete(void) { //Class destructor
    this->_logger->record("Delete::~Delete() called");
    this->_logger->record("Destroying delete window ...");
    delete this->_interface; //Destroy the interface
    this->_logger->record("Delete window destroyed !");
}

void Delete::setList(QList<Word>* words) { //Set the list of words
    this->_words = words; //Set the words

    for (int i = 0; i < this->_words->count(); i++) {
        Word word = this->_words->at(i); //Get the word at the current index
        if (word.getAuthor() == this->_user->getUID()) { //If the user is the author of the word
            this->_interface->comboBox_UID->addItem(QString::number(word.getUID())); //Add the word name to the box
        }
    }
}

void Delete::on_button_Ok_clicked() { //On button ok clicked
    this->_logger->record("Delete::on_button_Ok_clicked() called");

    int uid = this->_interface->comboBox_UID->currentText().toInt(); //Get the current selected uid

    this->_database->deleteWord(uid, this->_user->getUID()); //Add the word to the database
    this->_user->decrementWord(); //Add one word to the user

    QMessageBox::information(this, "Deleted", "<FONT COLOR='#ffffff'>The word named " + this->_interface->lineEdit_Name->text() + " with the uid " + QString::number(uid) + " was deleted !</FONT>"); //Alert

    this->_logger->record("Hidding delete window ...");
    this->hide(); //Hide the window
    this->_interface->comboBox_UID->clear(); //Clear the combo box
    this->_logger->record("Delete window hidden !");
}
void Delete::on_button_Cancel_clicked() {  //On button cancel clicked
    this->_logger->record("Delete::on_button_Cancel_clicked() called");

    this->_logger->record("Hidding delete window ...");
    this->hide(); //Hide the window
    this->_logger->record("Delete window hidden !");
}

void Delete::on_comboBox_UID_currentIndexChanged(int index) { //On index changed
    this->_logger->record("Delete::on_comboBox_UID_currentIndexChanged() called");

    if(index < 0) return; //Correction

    Word word = this->_words->at(index); //Get the selected word

    this->_interface->lineEdit_Name->setText(word.getName()); //Update the word name
    this->_interface->lineEdit_Type->setText(word.getType()); //Update the word type
    this->_interface->textEdit_Description->setText(word.getDescription()); //Update the word description
}

