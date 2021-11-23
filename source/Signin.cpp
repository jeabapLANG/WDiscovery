#include "../include/Signin.h" //Include sign in definition
#include "./ui_Signin.h" //Include sign in window interface

Signin::Signin(Database* database, Log* logger) : //Class constructor
    QDialog(nullptr), //Set the parent window
    _interface(new Ui::Signin), //Set the ui interface
    _database(database), //Set the window database
    _logger(logger) { //Set the window logger
        this->_logger->record("Setting up .ui for signIn window ...");
        this->_interface->setupUi(this); //Setup the window interface
        this->_signupWindow = new Signup(this, this->_database, this->_logger); //Create the signup window
        this->_logger->record("UI setup for signIn window !");
}
Signin::~Signin(void) { //Class destructor
    this->_logger->record("Signin::~Signin() called");
    this->_logger->record("Destroying signIn window ...");

    delete this->_interface; //Destroy the window interface
    delete this->_tableWindow; //Delete the table window
    delete this->_signupWindow; //Delete the signup window

    this->_logger->record("SignIn window destroyed !");
}

void Signin::login (User* user) { //Login
    this->_logger->record("Signin::login() called");

    this->_logger->record("Generating table window ...");
    this->_tableWindow = new Table(this, this->_database, this->_logger, user); //Create the signup window
    this->_logger->record("Table window generated !");

    this->_logger->record("Showing table window ...");
    this->_tableWindow->show(); //Show the new window
    this->_logger->record("Table window showed !");

    this->_logger->record("Hidding signIn window ...");
    this->hide(); //Hide the window
    this->_logger->record("SignIn window hidden !");

    this->clear(); //Calling clear method
}

void Signin::clear(void) { //Clear the text fields
    this->_logger->record("Signin::clear() called");

    this->_logger->record("Clearing text fields ...");
    this->_interface->lineEdit_Username->setText(""); //Clear the username
    this->_interface->lineEdit_Password->setText(""); //Clear the password
    this->_logger->record("Text fields cleared ...");
}

void Signin::on_button_SignIn_clicked(void) { //On sign in button clicked
    this->_logger->record("Signin::on_button_SignIn_clicked() called");

    const QString username = this->_interface->lineEdit_Username->text(); //Get the username from the sign in window
    const QString password = this->_interface->lineEdit_Password->text(); //Get the password from the sign in window

    if (username.isEmpty() && password.isEmpty()) { //If the username and the password are empty
        this->_logger->record("Line edits empty warning !");

        QMessageBox::warning(this, "Login", "<FONT COLOR='#ff0000'>Please fill the username and password field !</FONT>"); //Alert
        return; //Stop here
    }
    else if (username.isEmpty()) { //If the username is empty
        this->_logger->record("Username empty warning !");

        QMessageBox::warning(this, "Login", "<FONT COLOR='#ff0000'>Please fill the username field !</FONT>"); //Alert
        return; //Stop here
    }
    else if (password.isEmpty()) { //If the password is empty
        this->_logger->record("Password empty warning !");

        QMessageBox::warning(this, "Login", "<FONT COLOR='#ff0000'>Please fill the password field !</FONT>"); //Alert
        return; //Stop here
    }

    this->_logger->record("Verifying if user already exists ...");
    bool existance = this->_database->userExists(username); //Check if the user already exists*
    this->_logger->record("User existance checked !");

    if(existance == false) { //If the user already exists
        this->_logger->record("The typed user doesn't exists !");

        QMessageBox::warning(this, "Register", "<FONT COLOR='#ff0000'>This user doesn't exists !</FONT>"); //Alert
        return; //Stop here
    }

    User* user = this->_database->getUser(username); //Get the user from its username

    if(user->getPassword() != password) { //If the passwords doesn't match
        this->_logger->record("The passwords are not equals !");

        QMessageBox::warning(this, "Register", "<FONT COLOR='#ff0000'>Incorrect password !</FONT>"); //Alert
        return; //Stop here
    } else { //If the password is correct
        this->_logger->record("The passwords are matching !");
    }

    this->login(user); //Login
}

void Signin::on_button_SignUp_clicked(void) { //On sign up button clicked
    this->_logger->record("Signin::on_button_SignUp_clicked() called");

    this->_logger->record("Showing signUp window ...");
    this->_signupWindow->show(); //Show the new window
    this->_logger->record("SignUp window showed !");

    this->_logger->record("Hidding signIn window ...");
    this->hide(); //Hide the window
    this->_logger->record("SignIn window hidden !");

    this->clear(); //Calling clear method
}

