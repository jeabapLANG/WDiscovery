#ifndef ADD_H //If add not included
    #define ADD_H //Define add

    #include <QDialog> //Include QT dialog class
    #include <QMessageBox> //Include QT message box class

    #include "Database.h" //Include database
    #include "Log.h" //Include log

    QT_BEGIN_NAMESPACE //Begin QT namespace
        namespace Ui { class Add; } //Define add in the Ui namespace
    QT_END_NAMESPACE //End QT namespace

    class Add : public QDialog { //Extends add from the qt dialog class
        Q_OBJECT //Declare QT objects

        public: //Public class members
            explicit Add(QWidget* parent, User* user, Database* database, Log* logger); //Class constructor
            ~Add(void); //Class destructor

            void clear(void); //Clear the text fields

        private slots: //Private slots members
                void on_button_Ok_clicked(); //On button ok clicked
                void on_button_Cancel_clicked(); //On button cancel clicked

        private: //Private class members
                Ui::Add* _interface; //Window interface

                Database* _database; //Application database
                Log* _logger; //Logger
                User* _user; //User
    };

#endif // End if
