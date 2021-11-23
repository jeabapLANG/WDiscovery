#include "../include/Signup.h" //Include sign up definition
#include "./ui_Signup.h" //Include sign in window interface

Signup::Signup(QWidget* parent, Database* database, Log* logger) : //Class constructor
    QDialog(parent), //Set the parent window
    _interface(new Ui::Signup), //Set the ui interface
    _database(database), //Set the window database
    _logger(logger) {  //Set the window logger
        this->_logger->record("Setting up .ui for signUp window ...");
        this->_interface->setupUi(this); //Setup the window interface
        this->_logger->record("UI setup for signUp window !");
}
Signup::~Signup(void) { //Class destructor
    this->_logger->record("Signup::~Signup() called");
    this->_logger->record("Destroying signUp window ...");
    delete this->_interface; //Destroy the interface
    this->_logger->record("SignUp window destroyed !");
}

void Signup::clear(void) { //Clear the text fields
    this->_logger->record("Signin::clear() called");

    this->_logger->record("Clearing text fields ...");
    this->_interface->label_Username->setText(""); //Clear the username
    this->_interface->label_Password->setText(""); //Clear the password
    this->_logger->record("Text fields cleared ...");
}

void Signup::on_button_SignUp_clicked(void) { //On sign up button clicked
    this->_logger->record("Signup::on_button_SignUp_clicked() called");

    const QString username = this->_interface->lineEdit_Username->text(); //Get the username from the sign in window
    const QString password = this->_interface->lineEdit_Password->text(); //Get the password from the sign in window

    if (username.isEmpty() && password.isEmpty()) { //If the username and the password are empty
        this->_logger->record("Line edits empty warning !");

        QMessageBox::warning(this, "Register", "<FONT COLOR='#ff0000'>Please fill the username and password field !</FONT>"); //Alert
        return; //Stop here
    }
    else if (username.isEmpty()) { //If the username is empty
        this->_logger->record("Username empty warning !");

        QMessageBox::warning(this, "Register", "<FONT COLOR='#ff0000'>Please fill the username field !</FONT>"); //Alert
        return; //Stop here
    }
    else if (password.isEmpty()) { //If the password is empty
        this->_logger->record("Password empty warning !");

        QMessageBox::warning(this, "Register", "<FONT COLOR='#ff0000'>Please fill the password field !</FONT>"); //Alert
        return; //Stop here
    }

    this->_logger->record("Verifying if user already exists ...");
    bool existance = this->_database->userExists(username); //Check if the user already exists*
    this->_logger->record("user existance checked !");

    if(existance == true) { //If the user already exists
        this->_logger->record("The typed user already exists !");

        QMessageBox::warning(this, "Register", "<FONT COLOR='#ff0000'>This user already exists !</FONT>"); //Alert
        return; //Stop here
    } else { //If the user doesn't exist
        this->_logger->record("Creating new user in database ...");
        this->_database->addUser(username, password); //Adding new user to the database
        this->_logger->record("New user created in database !");
    }

    this->on_button_SignIn_clicked(); //Show back the signin window
}
void Signup::on_button_SignIn_clicked(void) { //On sign in button clicked
    this->_logger->record("Signup::on_button_SignIn_clicked() called");

    this->_logger->record("Showing back signin window ...");
    this->parentWidget()->show(); //Show back signin

    this->_logger->record("Hidding signUp window ...");
    this->hide(); //Hide the current signup window
    this->_logger->record("SignUp window hidden !");
}

