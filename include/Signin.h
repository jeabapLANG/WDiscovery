#ifndef SIGNIN_H //If sign in not included
    #define SIGNIN_H //Define sign in

    #include <QDialog> //Include QT dialog class
    #include <QMessageBox> //Include QT message box class

    #include "Signup.h" //Include signup window
    #include "Table.h" //Include table window

    #include "Database.h" //Include database
    #include "Log.h" //Include log

    QT_BEGIN_NAMESPACE //Begin QT namespace
        namespace Ui { class Signin; } //Define Signin in the Ui namespace
    QT_END_NAMESPACE //End QT namespace

    class Signin : public QDialog { //Extends sign in from the qt dialog class
        Q_OBJECT //Declare QT objects

        public: //Public class members
            explicit Signin(Database* database, Log* logger); //Class constructor
            ~Signin(void); //Class destructor

            void login(User* user); //Login

            void clear(void); //Clear the text fields

        private slots : //Private class slots
            void on_button_SignIn_clicked(void); //On sign in button clicked
            void on_button_SignUp_clicked(void); //On sign up button clicked

        private: //Private class members
                Ui::Signin* _interface; //Window interface
                Signup* _signupWindow; //Signup window

                Database* _database; //Application database
                Log* _logger; //Logger

                Table* _tableWindow; //Table window
    };

#endif // End if
