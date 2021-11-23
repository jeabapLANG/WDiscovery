#ifndef SIGNUP_H //If sign up not included
    #define SIGNUP_H //Define sign up

    #include <QDialog> //Include QT dialog class
    #include <QMessageBox> //Include QT message box class

    #include "Database.h" //Include database
    #include "Log.h" //Include log

    QT_BEGIN_NAMESPACE //Begin QT namespace
        namespace Ui { class Signup; } //Define Signup in the Ui namespace
    QT_END_NAMESPACE //End QT namespace

    class Signup : public QDialog { //Extends sign up from the qt dialog class
        Q_OBJECT //Declare QT objects

        public: //Public class members
            explicit Signup(QWidget* parent, Database* database, Log* logger); //Class constructor
            ~Signup(void); //Class destructor

            void clear(void); //Clear the text fields

        private slots : //Private class slots
            void on_button_SignUp_clicked(); //On sign up button clicked
            void on_button_SignIn_clicked(); //On sign in button clicked

        private: //Private class members
                Ui::Signup* _interface; //Window interface

                Database* _database; //Application database
                Log* _logger; //Logger
    };

#endif // End if
