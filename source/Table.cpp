#include "../include/Table.h" //Include table definition
#include "./ui_Table.h" //Include table interface

Table::Table(QWidget *parent, Database* database, Log* logger, User* user) : //Class constructor
    QDialog(parent), //Set the window parent
    _interface(new Ui::Table), //Set the window interface
    _database(database), //Set the window database
    _logger(logger), //Set the window logger
    _user(user) { //Set the window user
    this->_logger->record("Setting up .ui for signIn window ...");
    this->_interface->setupUi(this); //Setup the window interface
    this->_logger->record("UI setup for signIn window !");

    this->_logger->record("Precalculating items ...");
    this->_interface->label_UID->setText("##{" + QString::number(this->_user->getUID()) + "}##"); //Set the user UID
    this->_interface->label_Created->setText(this->_user->getCreated()); //Set the user created date
    this->_interface->label_Username->setText(this->_user->getName()); //Set the username

    this->_interface->label_Date->setText(this->_user->getCreated()); //Get the user created date
    this->_logger->record("Items precalculated !");

    this->updateTable(); //Update for the first time

    this->_logger->record("Setting displayed elements for user ...");
    this->_viewWindow = new View(this, this->_user, this->_database, this->_logger); //Create the new instance
    this->_viewWindow->setModal(true); //Set the window to modal
    this->_addWindow = new Add(this, this->_user, this->_database, this->_logger); //Create the new instance
    this->_addWindow->setModal(true); //Set the window to modal
    this->_deleteWindow = new Delete(this, this->_user, this->_database, this->_logger); //Create the new instance
    this->_deleteWindow->setModal(true); //Set the window to modal
    this->_updateWindow = new Update(this, this->_user, this->_database, this->_logger); //Create the new instance
    this->_updateWindow->setModal(true); //Set the window to modal
    this->_logger->record("Elements displayed !");
}
Table::~Table(void) { //Class destructor
    this->_logger->record("Table::~Table() called");
    this->_logger->record("Destroying table window ...");
    delete this->_interface; //Destroy the interface

    delete this->_addWindow; //Destroy add window
    delete this->_updateWindow; //Destroy update window
    delete this->_deleteWindow; //Destroy delete window

    delete this->_words; //Destroy the words in the table
    delete this->_searchedWords;  //Destory the searched words

    delete this->_user; //Destory the user
    this->_logger->record("Table window destroyed !");
}

void Table::updateTable(void) { //Update the ui objects
    this->_logger->record("Table::update() called");

    this->_interface->label_Words->setText(QString::number(this->_user->getWords())); //Get the user total words

    if(this->_words != nullptr) { //If words were displayed before
        delete this->_words; //Delete the old words
    }

    this->_words = this->_database->getWords(); //Get the words in the database

    this->_interface->listWidget_UID->clear(); //Remove old items
    this->_interface->listWidget_Author->clear(); //Remove old items
    this->_interface->listWidget_Name->clear(); //Remove old items
    this->_interface->listWidget_Type->clear(); //Remove old items
    this->_interface->listWidget_Created->clear(); //Remove old items
    this->_interface->listWidget_Searched->clear(); //Remove old items

    for (int i = 0; i < this->_words->count(); i++) { //For each of the words
        Word word = this->_words->at(i); //Get the word at the current index
        User* user = this->_database->getUser(word.getAuthor()); //Get the user

        this->_interface->listWidget_UID->addItem(QString::number(word.getUID())); //Add the word uid
        this->_interface->listWidget_Author->addItem(user->getName()); //Add the author name
        this->_interface->listWidget_Name->addItem(word.getName()); //Add the word name
        this->_interface->listWidget_Type->addItem(word.getType()); //Add the word type
        this->_interface->listWidget_Created->addItem(word.getDate()); //Add the word date
        this->_interface->listWidget_Searched->addItem(QString::number(word.getSearch())); //Add the word search
    }
}
void Table::updateSearchTable(void) { //Update the search table
    this->_logger->record("Table::updateSearchTable() called");

    this->_interface->listWidget_UID_2->clear(); //Remove old items
    this->_interface->listWidget_Author_2->clear(); //Remove old items
    this->_interface->listWidget_Name_2->clear(); //Remove old items
    this->_interface->listWidget_Type_2->clear(); //Remove old items
    this->_interface->listWidget_Created_2->clear(); //Remove old items
    this->_interface->listWidget_Searched_2->clear(); //Remove old items

    for (int i = 0; i < this->_searchedWords->count(); i++) { //For each of the words
        Word word = this->_searchedWords->at(i); //Get the word at the current index
        User* user = this->_database->getUser(word.getAuthor()); //Get the user

        this->_interface->listWidget_UID_2->addItem(QString::number(word.getUID())); //Add the word uid
        this->_interface->listWidget_Author_2->addItem(user->getName()); //Add the author name
        this->_interface->listWidget_Name_2->addItem(word.getName()); //Add the word name
        this->_interface->listWidget_Type_2->addItem(word.getType()); //Add the word type
        this->_interface->listWidget_Created_2->addItem(word.getDate()); //Add the word date
        this->_interface->listWidget_Searched_2->addItem(QString::number(word.getSearch())); //Add the word search

        this->_database->incrementSearch(word.getUID()); //Increment the search of the word

        delete user; //Delete user
    }

    this->updateTable(); //Update table
}

void Table::on_lineEditSearch_textChanged(QString search) { //On text changed
    this->_logger->record("Table::on_lineEdit_Search_textChanged() called");

    if(this->_searchedWords != nullptr) { //If words were searched before
        delete this->_searchedWords; //Delete the old words
    }

    this->_searchedWords = this->_database->executeSearch(this->_interface->comboBox->currentText(), search); //Get the words matching the typed search
    this->updateSearchTable(); //Calling update
}
void Table::on_comboBox_currentIndexChanged(int index) { //On type changed
    this->_logger->record("Table::on_combo_Search_currentIndexChanged() called");

    if(this->_searchedWords != nullptr) { //If words were searched before
        delete this->_searchedWords; //Delete the old words
    }

    this->_searchedWords = this->_database->executeSearch(this->_interface->comboBox->currentText(), this->_interface->lineEditSearch->text()); //Get the words matching the typed search
    this->updateSearchTable(); //Calling update
}

void Table::on_button_Logout_clicked (void) { //On log out clicked
    this->_logger->record("Table::on_button_Logout_clicked() called");

    this->_logger->record("Showing back signin window ...");
    this->parentWidget()->show(); //Show back signin

    this->_logger->record("Hidding table window ...");
    this->hide(); //Hide the window
    this->_logger->record("Table window hidden !");
}

void Table::on_button_View_clicked() { //On view clicked
    this->_logger->record("Table::on_button_View_clicked() called");

    this->_logger->record("Showing view window ...");
    this->_viewWindow->setList(this->_words); //Set the list of words
    this->_viewWindow->exec(); //Show the new window
    this->_logger->record("View window showed !");

    this->updateTable(); //Update
}
void Table::on_button_Add_clicked (void) { //On add clicked
    this->_logger->record("Table::on_button_Add_clicked() called");

    this->_logger->record("Showing add window ...");
    this->_addWindow->exec(); //Show the new window
    this->_logger->record("Add window showed !");

    this->updateTable(); //Update
}
void Table::on_button_Update_clicked() { //On update button clicked
    this->_logger->record("Table::on_button_Update_clicked() called");

    this->_logger->record("Showing update window ...");
    this->_updateWindow->setList(this->_words); //Set the list of words
    this->_updateWindow->exec(); //Show the new window
    this->_logger->record("Update window showed !");

    this->updateTable(); //Update
}
void Table::on_button_Delete_clicked() { //On delete button clicked
    this->_logger->record("Table::on_button_Delete_clicked() called");

    this->_logger->record("Showing delete window ...");
    this->_deleteWindow->setList(this->_words); //Set the list of words
    this->_deleteWindow->exec(); //Show the new window
    this->_logger->record("Delete window showed !");

    this->updateTable(); //Update
}
void Table::on_button_Refresh_clicked() { //On refresh
    this->updateSearchTable(); //Update the search window
    this->updateTable(); //Update the window
}

